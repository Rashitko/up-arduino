#ifndef ConversionUtils_h
#define ConversionUtils_h

#include "Arduino.h"

union FloatBytes {
  float asFloat;
  unsigned char asBytes[sizeof(float)];
};

union ShortBytes {
  short asShort;
  unsigned char asBytes[sizeof(short)];
};

union IntBytes {
  int asInt;
  unsigned char asBytes[sizeof(int)];
};

union BoolBytes {
  bool asBool;
  unsigned char asBytes[sizeof(bool)];
};

class ConversionUtils {
  public:
    const static int SHORT_SIZE = sizeof(short);
    const static int FLOAT_SIZE = sizeof(float);
    const static int BOOL_SIZE = sizeof(bool);
    
    const static short shortFromBytes(const unsigned char data[]);
    const static int shortToBytes(const short value, unsigned char data[]);
    const static float floatFromBytes(const unsigned char data[]);
    const static int floatToBytes(const float value, unsigned char data[]);
    const static bool boolFromBytes(const unsigned char data[]);
    const static int boolToBytes(const bool value, unsigned char data[]);
    const static void packCommandWithPayload(const char cmdType, const unsigned char data[], const int dataSize, unsigned char result[]);
};

#endif
