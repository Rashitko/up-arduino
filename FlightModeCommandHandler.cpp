#include "FlightModeCommandHandler.h"

void FlightModeCommandHandler::initialize() {
  flightController = up->getFlightController();
}

bool FlightModeCommandHandler::canHandle(const byte commandType){
  if (commandType == REQUEST_COMMAND_TYPE || commandType == MODE_CHANGE_COMMAND_TYPE) {
    receivedCommandType = commandType;
    return true;
  }
  return false;
}

int FlightModeCommandHandler::getPayloadSize() {
  if (receivedCommandType == REQUEST_COMMAND_TYPE) {
    return REQUEST_COMMAND_SIZE;
  }
  if (receivedCommandType == MODE_CHANGE_COMMAND_TYPE) {
    return MODE_CHANGE_COMMAND_SIZE;
  }
  return 0;
}

bool FlightModeCommandHandler::hasExecuted(byte payload[], const int payloadSize){
  if (receivedCommandType == MODE_CHANGE_COMMAND_TYPE) {
    const bool wasSet = flightController->setMode(payload[0]);
    if (!wasSet) {
      Serial.write("!");
      Serial.write(MODE_CHANGE_COMMAND_TYPE);
    }
    return true;
  }
  if (receivedCommandType == REQUEST_COMMAND_TYPE) {
    Serial.write(REQUEST_COMMAND_TYPE);
    Serial.write(flightController->getMode());
    return true;
  }
  return false;
}

