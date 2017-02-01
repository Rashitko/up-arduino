#include "LocationCommandHandler.h"

void LocationCommandHandler::initialize() {
  flightController = up->getFlightController();
  flightController->setLatitude(0);
  flightController->setLongitude(0);
}

bool LocationCommandHandler::canHandle(const byte commandType) {
  return commandType == COMMAND_TYPE;
}

int LocationCommandHandler::getPayloadSize() {
  return PAYLOAD_SIZE;
}

bool LocationCommandHandler::hasExecuted(byte payload[], const int payloadSize) {
  const unsigned char latPayload[] = {payload[0], payload[1], payload[2], payload[3]};
  const float latitude = ConversionUtils::floatFromBytes(latPayload);
  flightController->setLatitude(latitude);
  const unsigned char lonPayload[] = {payload[4], payload[5], payload[6], payload[7]};
  const float longitude = ConversionUtils::floatFromBytes(lonPayload);
  flightController->setLongitude(longitude);
  return true;
}

void LocationCommandHandler::executeConfirm() {
  unsigned char data[PAYLOAD_SIZE];

  unsigned char latData[ConversionUtils::FLOAT_SIZE];
  ConversionUtils::floatToBytes(flightController->getLatitude(), latData);
  for (int i = 0; i < PAYLOAD_SIZE / 2; i++) {
    data[i] = latData[i];
  }

  unsigned char lonData[ConversionUtils::FLOAT_SIZE];
  ConversionUtils::floatToBytes(flightController->getLongitude(), lonData);
  const int offset = (PAYLOAD_SIZE / 2);
  for (int i = 0; i < PAYLOAD_SIZE / 2; i++) {
    data[offset + i] = lonData[i];
  }
  unsigned char response[PAYLOAD_SIZE + 1];
  ConversionUtils::packCommandWithPayload(COMMAND_TYPE, data, PAYLOAD_SIZE, response);
  Serial.write(response, PAYLOAD_SIZE + 1);
}

