#ifndef ServoController_h
#define ServoController_h

#include "Arduino.h"
#include "Servo.h"
#include "PWMReader.h"

class ServoController {
  private:
    Servo aileronsServo;
    Servo elevatorServo;
    Servo throttleServo;
    Servo rudderServo;

    int aileronsPin;
    int elevatorPin;
    int throttlePin;
    int rudderPin;
  public:
    void initialize();
    void setAilerons(const int pwm);
    void setElevator(const int pwm);
    void setThrottle(const int pwm);
    void setRudder(const int pwm);
    const int getAileronsPin() const;
    const int getElevatorPin() const;
    const int getThrottlePin() const;
    const int getRudderPin() const;
};

#endif
