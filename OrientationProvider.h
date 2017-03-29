#ifndef OrientationProvider_h
#define OrientationProvider_h

#include "Arduino.h"
#include "Up.h"
#include "MPUReader.h"

class Up;
class MPUReader;

class OrientationProvider {
  private:
    Up *up = NULL;
    MPUReader *mpuReader = NULL;
    
    short forwardDelay = DEFAULT_DELAY;
    bool enabled = true;

    unsigned long prevSentStamp = 0;
    
    float yaw = 0;
    float yawRate = 0;
    float pitch = 0;
    float pitchRate = 0;
    float roll = 0;
    float rollRate = 0;
    void forwardOrientation();
  public:
    const static short DEFAULT_DELAY = 100;
    const static byte COMMAND_TYPE = 'o';
    const static byte PAYLOAD_SIZE = 12;

    const static int ROLL_MAX_ANGLE = 90;
    const static int ROLL_MIN_ANGLE = -ROLL_MAX_ANGLE;
    
    const static int PITCH_MAX_ANGLE = 45;
    const static int PITCH_MIN_ANGLE = -PITCH_MAX_ANGLE;
    
    const static int YAW_MAX_ANGLE = 180;
    const static int YAW_MIN_ANGLE = -YAW_MAX_ANGLE;
    
    void initialize(const Up *up);
    void loop();
    const MPUReader* getMPUReader() const;
    void setEnabled(const bool enabled);
    int getDelay() const;
    void setDelay(const int newDelay);
    void setYaw(const float yaw);
    void setPitch(const float pitch);
    void setRoll(const float roll);
    void setYawRate(const float yaw);
    void setPitchRate(const float pitch);
    void setRollRate(const float roll);
    float getYaw() const;
    float getPitch() const;
    float getRoll() const;
    float getYawRate() const;
    float getPitchRate() const;
    float getRollRate() const;
};

#endif

