#ifndef PWMReader_h
#define PWMReader_h

#include "Arduino.h"
#include "Up.h"

class PWMReader {
  private:
    volatile uint8_t updateFlagsShared;

    uint16_t ailInShared;
    uint16_t eleInShared;
    uint16_t thrInShared;
    uint16_t rudInShared;
    uint16_t aux1InShared;
    uint16_t aux2InShared;

    uint32_t ailStart;
    uint32_t eleStart;
    uint32_t thrStart;
    uint32_t rudStart;
    uint32_t aux1Start;
    uint32_t aux2Start;

    int ailPin = AIL_PIN_DEFAULT;
    int elePin = ELE_PIN_DEFAULT;
    int thrPin = THR_PIN_DEFAULT;
    int rudPin = RUD_PIN_DEFAULT;
    int aux1Pin = AUX1_PIN_DEFAULT;
    int aux2Pin = AUX2_PIN_DEFAULT;
  public:
    const static byte AIL_FLAG = 1;
    const static byte ELE_FLAG = 2;
    const static byte THR_FLAG = 4;
    const static byte RUD_FLAG = 8;
    const static byte AUX1_FLAG = 16;
    const static byte AUX2_FLAG = 32;

    const static byte THR_PIN_DEFAULT = 6;
    const static byte AIL_PIN_DEFAULT = 8;
    const static byte ELE_PIN_DEFAULT = 9;
    const static byte RUD_PIN_DEFAULT = 10;
    const static byte AUX1_PIN_DEFAULT = 11;
    const static byte AUX2_PIN_DEFAULT = 12;

    const int getAileronsPin() const;
    const int getElevatorPin() const;
    const int getThrottlePin() const;
    const int getRudderPin() const;
    const int getAUX1Pin() const;
    const int getAUX2Pin() const;
    void setAileronsPin(const int pin);
    void setElevatorPin(const int pin);
    void setThrottlePin(const int pin);
    void setRudderPin(const int pin);
    void setAUX1Pin(const int pin);
    void setAUX2Pin(const int pin);

    void calcCh1();
    void calcCh2();
    void calcCh3();
    void calcCh4();
    void calcAux1();
    void calcAux2();
    void loop();
};

#endif

