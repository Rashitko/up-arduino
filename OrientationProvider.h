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
    
    int forwardDelay = DEFAULT_DELAY;
    bool enabled = true;

    unsigned long prevSentStamp = 0;
    
    float yaw = 0;
    float pitch = 0;
    float roll = 0;
    void forwardOrientation();
  public:
    const static int DEFAULT_DELAY = 100;
    const static byte COMMAND_TYPE = 'o';
    const static byte PAYLOAD_SIZE = 12;
    
    void initialize(const Up *up);
    void loop();
    const MPUReader* getMPUReader() const;
    int getDelay() const;
    void setDelay(const int newDelay);
    void setYaw(const float yaw);
    void setPitch(const float pitch);
    void setRoll(const float roll);
    float getYaw() const;
    float getPitch() const;
    float getRoll() const;
};

#endif

