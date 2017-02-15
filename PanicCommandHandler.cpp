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
  if (inPanic) {
    Serial.println('Panic Entered');
    orientationProvider->setDelay(requiredDelay);
  } else {
    Serial.println('Panic Leaved');
  }
  return true;
}

void PanicCommandHandler::executeConfirm() {
  unsigned char data[PANIC_COMMAND_SIZE];
  ConversionUtils::boolToBytes(inPanic, data);
  unsigned char response[PANIC_COMMAND_SIZE + 1];
  ConversionUtils::packCommandWithPayload(PANIC_COMMAND_TYPE, data, PANIC_COMMAND_SIZE, response);
  const int responseSize = sizeof(response) / sizeof(unsigned char);
  Serial.write(response, responseSize);
}

