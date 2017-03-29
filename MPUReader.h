#ifndef MPUReader_h
#define MPUReader_h

#include "I2Cdev.h"
#include "helper_3dmath.h"
#define MPU6050_INCLUDE_DMP_MOTIONAPPS20
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif


#include "Arduino.h"
#include "OrientationProvider.h"

class OrientationProvider;

class MPUReader {
  private:
    OrientationProvider *orientationProvider = NULL;
    MPU6050 mpu;
    
    bool dmpReady = false;
    uint8_t mpuIntStatus;
    uint8_t devStatus;
    uint16_t packetSize;
    uint16_t fifoCount;
    uint8_t fifoBuffer[64];

    Quaternion q;
    VectorFloat gravity;
    VectorInt16 gyro;
    float ypr[3];
    float maxGyroX = 0;
    
    volatile bool mpuInterrupt = false;

    float radsToDegrees(const float rads);
  public:
    const static int INTERRUPT_PIN = 3;
    
    const static int X_GYRO_OFFSET = 36;
    const static int Y_GYRO_OFFSET = -23;
    const static int Z_GYRO_OFFSET = 17;
    const static int X_ACCEL_OFFSET = -735;
    const static int Y_ACCEL_OFFSET = -283;
    const static int Z_ACCEL_OFFSET = 814;

    const static int RATE_CHANGE = 500;
    
    MPUReader(const OrientationProvider *orientationProvider);
    void loop();
    void dmpDataReady();
};

#endif
