#ifndef RXForwarder_h
#define RXForwarder_h

#include "Arduino.h"
#include "Up.h"
#include "ConversionUtils.h"

class RXForwarder {
  private:
    int forwardDelay = DEFAULT_DELAY;
    bool enabled = true;
    
    short ailerons = DEFAULT_PWM_CHANNEL;
    short elevator = DEFAULT_PWM_CHANNEL;
    short throttle = DEFAULT_PWM_THROTTLE;
    short rudder = DEFAULT_PWM_CHANNEL;
    short aux1 = DEFAULT_PWM_CHANNEL;
    short aux2 = DEFAULT_PWM_CHANNEL;
    
    unsigned long prevSentStamp = 0;
    
    void sendRXData();
   public:
    const static byte DEFAULT_DELAY = 50;
    const static short DEFAULT_PWM_CHANNEL = 1500;
    const static short DEFAULT_PWM_THROTTLE = 1000;
    
    const static byte AILERONS_POSITION = 0;
    const static byte ELEVATOR_POSITION = 1;
    const static byte THROTTLE_POSITION = 2;
    const static byte RUDDER_POSITION = 3;
    const static byte AUX1_POSITION = 4;
    const static byte AUX2_POSITION = 5;
 
    const static byte COMMAND_TYPE = 'r';
    const static byte PAYLOAD_SIZE = 8;
    
    void loop();
    const int getDelay() const;
    void setDelay(const int forwardDelay);
    void setEnabled(const bool enabled);
    const bool isEnabled() const;

    void setAilerons(const int pwm);
    void setElevator(const int pwm);
    void setThrottle(const int pwm);
    void setRudder(const int pwm);
    void setAUX1(const int pwm);
    void setAUX2(const int pwm);

    const short getAilerons() const;
    const short getElevator() const;
    const short getThrottle() const;
    const short getRudder() const;
    const short getAUX1() const;
    const short getAUX2() const;
    
};

#endif
