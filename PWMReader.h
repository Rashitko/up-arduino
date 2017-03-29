#ifndef PWMReader_h
#define PWMReader_h

#include "Arduino.h"
#include "Up.h"
#include "LowPassFilter.h"

class Up;

class PWMReader {
  private:
    Up *up = NULL;
    
    volatile uint8_t updateFlagsShared;

    short ailInShared;
    short eleInShared;
    short thrInShared;
    short rudInShared;
    short aux1InShared;
    short aux2InShared;

    uint32_t ailStart;
    uint32_t eleStart;
    uint32_t thrStart;
    uint32_t rudStart;
    uint32_t aux1Start;
    uint32_t aux2Start;

    short ailPWM = PWM_DEFAULT;
    short elePWM = PWM_DEFAULT;
    short thrPWM = PWM_THROTTLE_DEFAULT;
    short rudPWM = PWM_DEFAULT;
    short aux1PWM = PWM_DEFAULT;
    short aux2PWM = PWM_DEFAULT;

    LowPassFilter aileronsFilter = LowPassFilter(0.4, PWM_DEFAULT);
    LowPassFilter elevatorFilter = LowPassFilter(0.4, PWM_DEFAULT);
    LowPassFilter throttleFilter = LowPassFilter(0.4, PWM_THROTTLE_DEFAULT);
    LowPassFilter rudderFilter = LowPassFilter(0.4, PWM_DEFAULT);

    const bool shouldFilter(const short prevPWM, const short currentPWM) const;
    
  public:
    const static byte AIL_FLAG = 1;
    const static byte ELE_FLAG = 2;
    const static byte THR_FLAG = 4;
    const static byte RUD_FLAG = 8;
    const static byte AUX1_FLAG = 16;
    const static byte AUX2_FLAG = 32;

    const static byte THROTTLE_PIN = 6;
    const static byte AILERONS_PIN = 8;
    const static byte ELEVATOR_PIN = 9;
    const static byte RUDDER_PIN = 10;
    const static byte AUX1_PIN = 11;
    const static byte AUX2_PIN = 12;

    const static byte THROTTLE_PCINT_PIN = 22;
    const static byte AILERONS_PCINT_PIN = 0;
    const static byte ELEVATOR_PCINT_PIN = 1;
    const static byte RUDDER_PCINT_PIN = 2;
    const static byte AUX1_PCINT_PIN = 3;
    const static byte AUX2_PCINT_PIN = 4;

    const static int MIN_PWM = 1000;
    const static int MAX_PWM = 2000;   
    const static int PWM_DEFAULT = 1500;
    const static int PWM_THROTTLE_DEFAULT = 1000;

    const static byte FILTER_CHANGE_LIMIT = 20;

    void initialize(const Up *up);

    const int getAileronsPin() const;
    const int getElevatorPin() const;
    const int getThrottlePin() const;
    const int getRudderPin() const;
    const int getAUX1Pin() const;
    const int getAUX2Pin() const;

    const int getAileronsPCINTPin() const;
    const int getElevatorPCINTPin() const;
    const int getThrottlePCINTPin() const;
    const int getRudderPCINTPin() const;
    const int getAux1PCINTPin() const;
    const int getAux2PCINTPin() const;

    const int getAilerons() const;
    const int getElevator() const;
    const int getThrottle() const;
    const int getRudder() const;
    const int getAUX1() const;
    const int getAUX2() const;

    void calcCh1();
    void calcCh2();
    void calcCh3();
    void calcCh4();
    void calcAux1();
    void calcAux2();
    void loop();
};

#endif

