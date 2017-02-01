#include "ConversionUtils.h"

const short ConversionUtils::shortFromBytes(const unsigned char data[]) {
  ShortBytes u;
  for (int i = 0; i < SHORT_SIZE; i++) {
    const int dataIndex = SHORT_SIZE - 1 - i;
    u.asBytes[i] = data[dataIndex];
  }
  return u.asShort;
}

const int ConversionUtils::shortToBytes(const short value, unsigned char data[]) {
  ShortBytes u;
  u.asShort = value;
  for (int i = 0; i < SHORT_SIZE; i++) {
    const int dataIndex = SHORT_SIZE - 1 - i;
    data[dataIndex] = u.asBytes[i];
  }
  return SHORT_SIZE;
}

const float ConversionUtils::floatFromBytes(const unsigned char data[]) {
  FloatBytes u;
  for (int i = 0; i < FLOAT_SIZE; i++) {
    const int dataIndex = FLOAT_SIZE - 1 - i;
    u.asBytes[i] = data[dataIndex];
  }
  return u.asFloat;
}

const int ConversionUtils::floatToBytes(const float value, unsigned char data[]) {
  FloatBytes u;
  u.asFloat = value;
  for (int i = 0; i < FLOAT_SIZE; i++) {
    const int dataIndex = FLOAT_SIZE - 1 - i;
    data[dataIndex] = u.asBytes[i];
  }
  return FLOAT_SIZE;
}

const void ConversionUtils::packCommandWithPayload(const char cmdType, const unsigned char data[], const int dataSize, unsigned char result[]) {
  result[0] = cmdType;
  for (int i = 0; i < dataSize; i++) {
    result[i + 1] = data[i];
  }
}

