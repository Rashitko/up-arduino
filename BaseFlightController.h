#ifndef BaseFlightController_h
#define BaseFlightController_h

#include "Arduino.h"

class BaseFlightController {
  private:
    byte mode = FLIGHT_MODE_RATE;
    short altitude = 0;
    short actualHeading = 0;
    short requiredHeading = 0;
    float latitude = -1;
    float longitude = -1;
  public:
    const static byte FLIGHT_MODE_RATE = 'r';
    const static byte FLIGHT_MODE_FBW = 'f';
    const static byte FLIGHT_MODE_RTH = 'h';
  
    void setAltitude(const short altitude);
    const short getAltitude();
    void setActualHeading(const short heading);
    const short getActualHeading();
    void setRequiredHeading(const short heading);
    const short getRequiredHeading();    
    void setLatitude(const float latitude);
    const float getLatitude();
    void setLongitude(const float longitude);
    const float getLongitude();
    bool setMode(const byte mode);
    const byte getMode(); 
  
};

#endif

