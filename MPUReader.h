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
#include "Up.h"

class Up;

class MPUReader {
  private:
    Up *up = NULL;
    MPU6050 mpu;
    
    bool dmpReady = false;
    uint8_t mpuIntStatus;
    uint8_t devStatus;
    uint16_t packetSize;
    uint16_t fifoCount;
    uint8_t fifoBuffer[64];

    Quaternion q;
    VectorFloat gravity;    // [x, y, z]            gravity vector
    float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
    
    volatile bool mpuInterrupt = false;

    int xGyroOffset = X_GYRO_OFFSET_DEFAULT;
    int yGyroOffset = Y_GYRO_OFFSET_DEFAULT;
    int zGyroOffset = Z_GYRO_OFFSET_DEFAULT;
    int xAccelOffset = X_ACCEL_OFFSET_DEFAULT;
    int yAccelOffset = Y_ACCEL_OFFSET_DEFAULT;
    int zAccelOffset = Z_ACCEL_OFFSET_DEFAULT;
  public:
    const static int INTERRUPT_PIN = 7;
    
    const static int X_GYRO_OFFSET_DEFAULT = 36;
    const static int Y_GYRO_OFFSET_DEFAULT = -23;
    const static int Z_GYRO_OFFSET_DEFAULT = 17;
    const static int X_ACCEL_OFFSET_DEFAULT = -735;
    const static int Y_ACCEL_OFFSET_DEFAULT = -283;
    const static int Z_ACCEL_OFFSET_DEFAULT = 814;
    
    MPUReader(const Up *up);
    void loop();
    
    void setXGyroOffset(const int offset);
    void setYGyroOffset(const int offset);
    void setZGyroOffset(const int offset);
    void setXAccelOffset(const int offset);
    void setYAccelOffset(const int offset);
    void setZAccelOffset(const int offset);
    
    void dmpDataReady();
};

#endif
