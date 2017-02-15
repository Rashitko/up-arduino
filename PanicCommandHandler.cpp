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
  return true;
}

void PanicCommandHandler::executeConfirm() {
  
}

