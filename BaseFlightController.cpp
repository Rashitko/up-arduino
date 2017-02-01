#include "BaseFlightController.h"

void BaseFlightController::setAltitude(const short altitude) {
  this->altitude = altitude;
}

const short BaseFlightController::getAltitude() {
  return altitude;
}

void BaseFlightController::setActualHeading(const short heading) {
  this->actualHeading = heading;
}

const short BaseFlightController::getActualHeading() {
  return actualHeading;
}

void BaseFlightController::setRequiredHeading(const short heading) {
  this->requiredHeading = heading;
}

const short BaseFlightController::getRequiredHeading() {
  return requiredHeading;
}

void BaseFlightController::setLatitude(const float latitude) {
  this->latitude = latitude;
}

const float BaseFlightController::getLatitude() {
  return latitude;
}

void BaseFlightController::setLongitude(const float longitude) {
  this->longitude = longitude;
}

const float BaseFlightController::getLongitude() {
  return longitude;
}

bool BaseFlightController::setMode(const byte mode){
  switch (mode) {
    case BaseFlightController::FLIGHT_MODE_RATE:
      this->mode = mode;
      return true;
    case BaseFlightController::FLIGHT_MODE_FBW:
      this->mode = mode;
      return true;
    case BaseFlightController::FLIGHT_MODE_RTH:
      this->mode = mode;
      return true;
    default:
      Serial.println(mode);
      Serial.println(BaseFlightController::FLIGHT_MODE_RATE);
      Serial.println(BaseFlightController::FLIGHT_MODE_FBW);
      Serial.println(BaseFlightController::FLIGHT_MODE_RTH);
      return false;
  }
}

const byte BaseFlightController::getMode() {
  return mode;
}

