#ifndef ServoController_h
#define ServoController_h

#include "Arduino.h"
#include "Servo.h"
#include "PWMReader.h"

class ServoController {
  private:
    Up *up = NULL;
    
    Servo aileronsServo;
    Servo elevatorServo;
    Servo throttleServo;
    Servo rudderServo;

    const static short AILERONS_PIN = A3;
    const static short ELEVATOR_PIN = A2;
    const static short THROTTLE_PIN = A1;
    const static short RUDDER_PIN = A0;
  public:
    void initialize(const Up* up);
    void setAilerons(const short pwm);
    void setElevator(const short pwm);
    void setThrottle(const short pwm);
    void setRudder(const short pwm);
};

#endif
