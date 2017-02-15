#include "PanicCommandHandler.h"

void PanicCommandHandler::initialize() {
  orientationProvider = up->getOrientationProvider();
}

bool PanicCommandHandler::canHandle(const byte commandType) {
  return commandType == PANIC_COMMAND_TYPE;
}

int PanicCommandHandler::getPayloadSize() {
  return PANIC_COMMAND_SIZE;
}

bool PanicCommandHandler::hasExecuted(byte payload[], const int payloadSize) {
  const unsigned char panicData[] = {payload[0]};
  inPanic = ConversionUtils::boolFromBytes(panicData);
  const unsigned char delayData[] = {payload[1], payload[2]};
  requiredDelay = ConversionUtils::shortFromBytes(delayData);
  orientationProvider->setDelay(requiredDelay);
  return true;
}

void PanicCommandHandler::executeConfirm() {
  unsigned char panicData[sizeof(bool)];
  ConversionUtils::boolToBytes(inPanic, panicData);
  unsigned char delayData[2 * sizeof(short)];
  ConversionUtils::shortToBytes(requiredDelay, delayData);
  unsigned char data[PANIC_COMMAND_SIZE];
  data[0] = panicData[0];
  data[1] = delayData[0];
  data[2] = delayData[1];
  unsigned char response[PANIC_COMMAND_SIZE + 1];
  ConversionUtils::packCommandWithPayload(PANIC_COMMAND_TYPE, data, PANIC_COMMAND_SIZE, response);
  const int responseSize = sizeof(response) / sizeof(unsigned char);
  Serial.write(response, responseSize);
}

