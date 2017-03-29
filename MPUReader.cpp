#include "MPUReader.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPUReader::MPUReader(const OrientationProvider *orientationProvider) {
  this->orientationProvider = orientationProvider;

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
  }

  devStatus = mpu.dmpInitialize();

  mpu.setXGyroOffset(X_GYRO_OFFSET);
  mpu.setYGyroOffset(Y_GYRO_OFFSET);
  mpu.setZGyroOffset(Z_GYRO_OFFSET);
  mpu.setXAccelOffset(X_ACCEL_OFFSET);
  mpu.setYAccelOffset(Y_ACCEL_OFFSET);
  mpu.setZAccelOffset(Z_ACCEL_OFFSET);

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    mpu.setDMPEnabled(true);

    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}

void MPUReader::loop() {
  if (!dmpReady) return;

  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) ;
  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    mpu.dmpGetGyro(&gyro, fifoBuffer);
    
    float yawRate = constrain(gyro.z, -RATE_CHANGE, RATE_CHANGE);
    yawRate = map(yawRate, -RATE_CHANGE, RATE_CHANGE, OrientationProvider::YAW_MIN_ANGLE, OrientationProvider::YAW_MAX_ANGLE);
    orientationProvider->setYawRate(yawRate);
    orientationProvider->setYaw(radsToDegrees(ypr[0]));
    
    float pitchRate = constrain(gyro.y, -RATE_CHANGE, RATE_CHANGE);
    pitchRate = map(pitchRate, -RATE_CHANGE, RATE_CHANGE, OrientationProvider::PITCH_MIN_ANGLE, OrientationProvider::PITCH_MAX_ANGLE);
    orientationProvider->setPitchRate(pitchRate);
    orientationProvider->setPitch(radsToDegrees(ypr[1]));
    
    float rollRate = constrain(gyro.x, -RATE_CHANGE, RATE_CHANGE);
    rollRate = map(rollRate, -RATE_CHANGE, RATE_CHANGE, OrientationProvider::ROLL_MIN_ANGLE, OrientationProvider::ROLL_MAX_ANGLE);
    orientationProvider->setRollRate(rollRate);
    orientationProvider->setRoll(radsToDegrees(ypr[2]));
  }
}

void MPUReader::dmpDataReady() {
  mpuInterrupt = true;
}

float MPUReader::radsToDegrees(const float rads) {
  return rads * 180 / M_PI;
}

