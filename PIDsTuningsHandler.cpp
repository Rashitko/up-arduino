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
  if (isRequest) {
    sendPIDs(REQUEST_COMMAND_TYPE);
  } else {
    if (!setAileronsRate(payload)) {
      return false;
    }
    if (!setElevatorRate(payload)) {
      return false;
    }
    if (!setAileronsStab(payload)) {
      return false;
    }
    if (!setElevatorStab(payload)) {
      return false;
    }
  }
  return true;
}

void PIDsTuningsHandler::executeConfirm() {
  if (!isRequest) {
    sendPIDs(COMMAND_TYPE);
  }
}

const bool PIDsTuningsHandler::setAileronsRate(byte payload[]) {
  float aileronsRatePIDs[PID_ELEMENTS_COUNT];
  for (unsigned int elem = 0; elem < PID_ELEMENTS_COUNT; elem++) {
    unsigned int payloadIndex = elem * sizeof(float);
    unsigned char buff[sizeof(float)];
    for (unsigned int i = 0; i < sizeof(float); i++) {
      buff[i] = payload[payloadIndex + i];
    }
    aileronsRatePIDs[elem] = ConversionUtils::floatFromBytes(buff);
  }
  return flightController->setAileronsRatePIDs(aileronsRatePIDs);
}

const bool PIDsTuningsHandler::setElevatorRate(byte payload[]) {
  float elevatorRatePIDs[PID_ELEMENTS_COUNT];
  const unsigned int payloadOffset = PID_ELEMENTS_COUNT * sizeof(float);
  for (unsigned int elem = 0; elem < PID_ELEMENTS_COUNT; elem++) {
    const unsigned int payloadIndex = (elem * sizeof(float)) + payloadOffset;
    unsigned char buff[sizeof(float)];
    for (unsigned int i = 0; i < sizeof(float); i++) {
      buff[i] = payload[payloadIndex + i];
    }
    elevatorRatePIDs[elem] = ConversionUtils::floatFromBytes(buff);
  }
  return flightController->setElevatorRatePIDs(elevatorRatePIDs);
}

const bool PIDsTuningsHandler::setAileronsStab(byte payload[]) {
  float aileronsStabPIDs[PID_ELEMENTS_COUNT];
  const unsigned int payloadOffset = 2 * PID_ELEMENTS_COUNT * sizeof(float);
  for (unsigned int elem = 0; elem < PID_ELEMENTS_COUNT; elem++) {
    const unsigned int payloadIndex = (elem * sizeof(float)) + payloadOffset;
    unsigned char buff[sizeof(float)];
    for (unsigned int i = 0; i < sizeof(float); i++) {
      buff[i] = payload[payloadIndex + i];
    }
    aileronsStabPIDs[elem] = ConversionUtils::floatFromBytes(buff);
  }
  return flightController->setAileronsStabPIDs(aileronsStabPIDs);
}

const bool PIDsTuningsHandler::setElevatorStab(byte payload[]) {
  float elevatorStabPIDs[PID_ELEMENTS_COUNT];
  const unsigned int payloadOffset = 3 * PID_ELEMENTS_COUNT * sizeof(float);
  for (unsigned int elem = 0; elem < PID_ELEMENTS_COUNT; elem++) {
    const unsigned int payloadIndex = (elem * sizeof(float)) + payloadOffset;
    unsigned char buff[sizeof(float)];
    for (unsigned int i = 0; i < sizeof(float); i++) {
      buff[i] = payload[payloadIndex + i];
    }
    elevatorStabPIDs[elem] = ConversionUtils::floatFromBytes(buff);
  }
  return flightController->setElevatorStabPIDs(elevatorStabPIDs);
}

void PIDsTuningsHandler::packPIDs(unsigned char *data, const float *pids, const unsigned int dataOffset) const {
  for (unsigned int i = 0; i < PID_ELEMENTS_COUNT; i++) {
    const unsigned int offset = dataOffset + (i * sizeof(float));
    packPID(data, pids[i], offset);
  }
}

void PIDsTuningsHandler::packPID(unsigned char *data, const float pidParam, const unsigned int dataOffset) const {
  unsigned char pidParamData[sizeof(float)];
  ConversionUtils::floatToBytes(pidParam, pidParamData);
  for (unsigned int i = 0; i < sizeof(float); i++) {
    const unsigned int dataIndex = i + dataOffset;
    data[dataIndex] = pidParamData[i];
  }
}

void PIDsTuningsHandler::sendPIDs(const byte responseCommandType) const {
  unsigned char data[COMMAND_SIZE];
  float ailRate[PID_ELEMENTS_COUNT];
  flightController->getAileronsRatePIDs(ailRate);
  packPIDs(data, ailRate, 0);

  float eleRate[PID_ELEMENTS_COUNT];
  flightController->getElevatorRatePIDs(eleRate);
  packPIDs(data, eleRate, PID_ELEMENTS_COUNT * sizeof(float));

  float ailStab[PID_ELEMENTS_COUNT];
  flightController->getAileronsStabPIDs(ailStab);
  packPIDs(data, ailStab, 2 * PID_ELEMENTS_COUNT * sizeof(float));

  float eleStab[PID_ELEMENTS_COUNT];
  flightController->getElevatorStabPIDs(eleStab);
  packPIDs(data, eleStab, 3 * PID_ELEMENTS_COUNT * sizeof(float));

  unsigned char response[COMMAND_SIZE + 1];
  ConversionUtils::packCommandWithPayload(responseCommandType, data, COMMAND_SIZE, response);
  Serial.write(response, COMMAND_SIZE + 1);
}

