#include "BaseFlightController.h"

BaseFlightController::BaseFlightController() {
  aileronsRXPWM = PWMReader::PWM_DEFAULT;
  elevatorRXPWM = PWMReader::PWM_DEFAULT;
  throttleRXPWM = PWMReader::PWM_THROTTLE_DEFAULT;
  rudderRXPWM = PWMReader::PWM_DEFAULT;

  aileronsStabPID = new PID(&rollAngle, &aileronsStabOutput, &aileronsRXAngle, DEFAULT_STAB_KP, DEFAULT_STAB_KI, DEFAULT_STAB_KD, DIRECT);
  aileronsStabPID->SetMode(AUTOMATIC);
  aileronsStabPID->SetOutputLimits(OrientationProvider::ROLL_MIN_ANGLE, OrientationProvider::ROLL_MAX_ANGLE);
  aileronsStabPID->SetSampleTime(SAMPLE_TIME);

  aileronsRatePID = new PID(&rollRate, &aileronsRateOutput, &aileronsStabOutput, DEFAULT_RATE_KP, DEFAULT_RATE_KI, DEFAULT_RATE_KD, DIRECT);
  aileronsRatePID->SetMode(AUTOMATIC);
  aileronsRatePID->SetOutputLimits(OrientationProvider::ROLL_MIN_ANGLE, OrientationProvider::ROLL_MAX_ANGLE);
  aileronsRatePID->SetSampleTime(SAMPLE_TIME);

  elevatorStabPID = new PID(&pitchAngle, &elevatorStabOutput, &elevatorRXAngle, DEFAULT_STAB_KP, DEFAULT_STAB_KI, DEFAULT_STAB_KD, DIRECT);
  elevatorStabPID->SetMode(AUTOMATIC);
  elevatorStabPID->SetOutputLimits(OrientationProvider::PITCH_MIN_ANGLE, OrientationProvider::PITCH_MAX_ANGLE);
  elevatorStabPID->SetSampleTime(SAMPLE_TIME);

  elevatorRatePID = new PID(&pitchRate, &elevatorRateOutput, &elevatorStabOutput, DEFAULT_RATE_KP, DEFAULT_RATE_KI, DEFAULT_RATE_KD, DIRECT);
  elevatorRatePID->SetMode(AUTOMATIC);
  elevatorRatePID->SetOutputLimits(OrientationProvider::PITCH_MIN_ANGLE, OrientationProvider::PITCH_MAX_ANGLE);
  elevatorRatePID->SetSampleTime(SAMPLE_TIME);
}

BaseFlightController::~BaseFlightController() {
  delete aileronsRatePID;
}

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

bool BaseFlightController::setMode(const byte mode) {
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

const bool BaseFlightController::setAileronsRatePIDs(const float pids[PID_ELEMENTS_COUNT]) {
  if (aileronsRatePID != NULL) {
    aileronsRatePID->SetTunings(pids[0], pids[1], pids[2]);
    return true;
  }
  return false;
}

void BaseFlightController::getAileronsRatePIDs(float pids[PID_ELEMENTS_COUNT]) {
  pids[0] = -1;
  pids[1] = -1;
  pids[2] = -1;
  if (aileronsRatePID != NULL) {
    pids[0] = aileronsRatePID->GetKp();
    pids[1] = aileronsRatePID->GetKi();
    pids[2] = aileronsRatePID->GetKd();
  }
}

const bool BaseFlightController::setElevatorRatePIDs(const float pids[PID_ELEMENTS_COUNT]) {
  if (elevatorRatePID != NULL) {
    elevatorRatePID->SetTunings(pids[0], pids[1], pids[2]);
    return true;
  }
  return false;
}

void BaseFlightController::getElevatorRatePIDs(float pids[PID_ELEMENTS_COUNT]) {
  pids[0] = -1;
  pids[1] = -1;
  pids[2] = -1;
  if (elevatorRatePID != NULL) {
    pids[0] = elevatorRatePID->GetKp();
    pids[1] = elevatorRatePID->GetKi();
    pids[2] = elevatorRatePID->GetKd();
  }
}

const bool BaseFlightController::setAileronsStabPIDs(const float pids[PID_ELEMENTS_COUNT]) {
  if (aileronsStabPID != NULL) {
    aileronsStabPID->SetTunings(pids[0], pids[1], pids[2]);
    return true;
  }
  return false;
}

void BaseFlightController::getAileronsStabPIDs(float pids[PID_ELEMENTS_COUNT]) {
  pids[0] = -1;
  pids[1] = -1;
  pids[2] = -1;
  if (aileronsStabPID != NULL) {
    pids[0] = aileronsStabPID->GetKp();
    pids[1] = aileronsStabPID->GetKi();
    pids[2] = aileronsStabPID->GetKd();
  }
}

const bool BaseFlightController::setElevatorStabPIDs(const float pids[PID_ELEMENTS_COUNT]) {
  if (elevatorStabPID != NULL) {
    elevatorStabPID->SetTunings(pids[0], pids[1], pids[2]);
    return true;
  }
  return false;
}

void BaseFlightController::getElevatorStabPIDs(float pids[PID_ELEMENTS_COUNT]) {
  pids[0] = -1;
  pids[1] = -1;
  pids[2] = -1;
  if (elevatorStabPID != NULL) {
    pids[0] = elevatorStabPID->GetKp();
    pids[1] = elevatorStabPID->GetKi();
    pids[2] = elevatorStabPID->GetKd();
  }
}

void BaseFlightController::initialize(const Up *up) {
  this->up = up;
  orientationProvider = up->getOrientationProvider();
  servoController = up->getServoController();
  pwmReader = up->getPWMReader();
}

void BaseFlightController::loop() {
  readRX();
  //  if (mode == FLIGHT_MODE_FBW) {
  rollAngle = orientationProvider->getRoll();
  aileronsStabPID->Compute();
  rollRate = orientationProvider->getRollRate();
  aileronsRatePID->Compute();
  const double aileronsOutput = PWMReader::PWM_DEFAULT + map(aileronsRateOutput, OrientationProvider::ROLL_MIN_ANGLE, OrientationProvider::ROLL_MAX_ANGLE, -PWM_CHANGE_LIMIT, PWM_CHANGE_LIMIT);
  servoController->setAilerons(aileronsOutput);

  pitchAngle = orientationProvider->getPitch();
  elevatorStabPID->Compute();
  pitchRate = orientationProvider->getPitchRate();
  elevatorRatePID->Compute();
  const double elevatorOutput = PWMReader::PWM_DEFAULT + map(elevatorRateOutput, OrientationProvider::PITCH_MIN_ANGLE, OrientationProvider::PITCH_MAX_ANGLE, -PWM_CHANGE_LIMIT, PWM_CHANGE_LIMIT);
  servoController->setElevator(elevatorOutput);
  //  } else {
  //      servoController.setAilerons(aileronsRXPWM);
  //      servoController.setElevator(elevatorRXPWM);
  //  }
  servoController->setThrottle(throttleRXPWM);
  servoController->setRudder(rudderRXPWM);
}

void BaseFlightController::readRX() {
  aileronsRXPWM = pwmReader->getAilerons();
  aileronsRXAngle = map(aileronsRXPWM, PWMReader::MIN_PWM, PWMReader::MAX_PWM, OrientationProvider::ROLL_MIN_ANGLE, OrientationProvider::ROLL_MAX_ANGLE);
  elevatorRXPWM = pwmReader->getElevator();
  elevatorRXAngle = map(elevatorRXPWM, PWMReader::MIN_PWM, PWMReader::MAX_PWM, OrientationProvider::PITCH_MIN_ANGLE, OrientationProvider::PITCH_MAX_ANGLE);
  throttleRXPWM = pwmReader->getThrottle();
  rudderRXPWM = pwmReader->getRudder();
}

