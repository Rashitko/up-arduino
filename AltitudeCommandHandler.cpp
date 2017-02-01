#include "AltitudeCommandHandler.h"

void AltitudeCommandHandler::initialize() {
  flightController = up->getFlightController();
  flightController->setAltitude(0);
}

bool AltitudeCommandHandler::canHandle(const byte commandType) {
  return commandType == ALTITUDE_COMMAND_TYPE;
}

int AltitudeCommandHandler::getPayloadSize() {
  return ALTITUDE_COMMAND_SIZE;
}

bool AltitudeCommandHandler::hasExecuted(byte payload[], const int payloadSize) {
  const short altitude = ConversionUtils::shortFromBytes(payload);
  flightController->setAltitude(altitude);
  return true;
}

void AltitudeCommandHandler::executeConfirm() {
  const int altitude = flightController->getAltitude();
  unsigned char data[ALTITUDE_COMMAND_SIZE];
  ConversionUtils::shortToBytes(altitude, data);
  unsigned char response[ALTITUDE_COMMAND_SIZE + 1];
  ConversionUtils::packCommandWithPayload(ALTITUDE_COMMAND_TYPE, data, ALTITUDE_COMMAND_SIZE, response);
  const int responseSize = sizeof(response) / sizeof(unsigned char);
  Serial.write(response, responseSize);
}

