#ifndef BaseFlightController_h
#define BaseFlightController_h

#include "Arduino.h"

#include "PID_v1.h"
#include "Up.h"
#include "OrientationProvider.h"
#include "PWMReader.h"
#include "ServoController.h"

class Up;
class OrientationProvider;
class PWMReader;
class ServoController;

class BaseFlightController {
  private:
    Up *up = NULL;
    OrientationProvider *orientationProvider = NULL;
    ServoController *servoController = NULL;
    PWMReader *pwmReader = NULL;
    byte mode = FLIGHT_MODE_RATE;
    short altitude = 0;
    short actualHeading = 0;
    short requiredHeading = 0;
    float latitude = -1;
    float longitude = -1;

    double aileronsRXPWM = 1500;
    double elevatorRXPWM = 1500;
    double throttleRXPWM = 1000;
    double rudderRXPWM = 1500;

    double aileronsRXAngle = 0;
    double rollAngle = 0;
    PID *aileronsStabPID = NULL;
    double aileronsStabOutput = 0;
    double rollRate = 0;
    PID *aileronsRatePID = NULL;
    double aileronsRateOutput = 0;

    double elevatorRXAngle = 0;
    double pitchAngle = 0;
    PID *elevatorStabPID = NULL;
    double elevatorStabOutput = 0;
    double pitchRate = 0;
    PID *elevatorRatePID = NULL;
    double elevatorRateOutput = 0;

    void readRX();
  public:
    const static byte FLIGHT_MODE_RATE = 'r';
    const static byte FLIGHT_MODE_FBW = 'f';
    const static byte FLIGHT_MODE_RTH = 'h';

    const static int SAMPLE_TIME = 10;

    const static float DEFAULT_STAB_KP = 4.5;
    const static float DEFAULT_STAB_KI = 0;
    const static float DEFAULT_STAB_KD = 0;
    
    const static float DEFAULT_RATE_KP = 0.7;
    const static float DEFAULT_RATE_KI = 0;
    const static float DEFAULT_RATE_KD = 0;
    
    const static int PWM_CHANGE_LIMIT = 500;

    const static int PID_ELEMENTS_COUNT = 3;

    BaseFlightController();
    ~BaseFlightController();
  
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
    const bool setAileronsRatePIDs(const float pids[PID_ELEMENTS_COUNT]);
    void getAileronsRatePIDs(float pids[PID_ELEMENTS_COUNT]);
    const bool setElevatorRatePIDs(const float pids[PID_ELEMENTS_COUNT]);
    void getElevatorRatePIDs(float pids[PID_ELEMENTS_COUNT]);
    const bool setAileronsStabPIDs(const float pids[PID_ELEMENTS_COUNT]);
    void getAileronsStabPIDs(float pids[PID_ELEMENTS_COUNT]);
    const bool setElevatorStabPIDs(const float pids[PID_ELEMENTS_COUNT]);
    void getElevatorStabPIDs(float pids[PID_ELEMENTS_COUNT]);
    void initialize(const Up *up);
    void loop();
};

#endif

