#include "PIDsTuningsHandler.h"

void PIDsTuningsHandler::initialize() {
  flightController = up->getFlightController();
}

bool PIDsTuningsHandler::canHandle(const byte commandType) {
  if (commandType == REQUEST_COMMAND_TYPE || commandType == COMMAND_TYPE) {
    isRequest = commandType == REQUEST_COMMAND_TYPE;
    return true;
  }
  return false;
}

int PIDsTuningsHandler::getPayloadSize() {
  if (isRequest) {
    return REQUEST_COMMAND_SIZE;
  }
  return COMMAND_SIZE;
}

bool PIDsTuningsHandler::hasExecuted(byte payload[], const int payloadSize) {
  return true;
}

void PIDsTuningsHandler::executeConfirm() {
  if (isRequest) {
    
  } else {
    
  }
}

