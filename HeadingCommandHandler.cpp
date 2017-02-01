#include "HeadingCommandHandler.h"

void HeadingCommandHandler::initialize() {
  flightController = up->getFlightController();
  flightController->setActualHeading(0);
  flightController->setRequiredHeading(0);
}

bool HeadingCommandHandler::canHandle(const byte commandType) {
  const bool canHandle = commandType == CURRENT_HEADING_COMMAND_TYPE || commandType == REQUIRED_HEADING_COMMAND_TYPE;
  if (canHandle) {
    receivedCommandType = commandType;
  }
  return canHandle;
}
int HeadingCommandHandler::getPayloadSize() {
  return PAYLOAD_SIZE;
}
bool HeadingCommandHandler::hasExecuted(byte payload[], const int payloadSize) {
  const short heading = ConversionUtils::shortFromBytes(payload);
  if (receivedCommandType == CURRENT_HEADING_COMMAND_TYPE) {
    flightController->setActualHeading(heading);
  } else if (receivedCommandType == REQUIRED_HEADING_COMMAND_TYPE) {
    flightController->setRequiredHeading(heading);
  } else {
    // receivedCommandType is set to unsupported value
    return false;
  }
  return true;
}

void HeadingCommandHandler::executeConfirm() {
  short heading = 0;
  if (receivedCommandType == CURRENT_HEADING_COMMAND_TYPE) {
    heading = flightController->getActualHeading();
  } else if (receivedCommandType == REQUIRED_HEADING_COMMAND_TYPE) {
    heading = flightController->getRequiredHeading();
  } else {
    // receivedCommandType is set to unsupported value
    return;
  }
  unsigned char data[ConversionUtils::SHORT_SIZE];
  ConversionUtils::shortToBytes(heading, data);
  unsigned char response[PAYLOAD_SIZE + 1];
  ConversionUtils::packCommandWithPayload(receivedCommandType, data, PAYLOAD_SIZE, response);
  Serial.write(response, PAYLOAD_SIZE + 1);
}

