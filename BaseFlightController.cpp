#include "BaseFlightController.h"

BaseFlightController::BaseFlightController() {
  aileronsRXPWM = PWMReader::PWM_DEFAULT;
  elevatorRXPWM = PWMReader::PWM_DEFAULT;
  throttleRXPWM = PWMReader::PWM_THROTTLE_DEFAULT;
  rudderRXPWM = PWMReader::PWM_DEFAULT;

  aileronsStabPID = new PID(&rollAngle, &aileronsStabOutput, &aileronsRXAngle, DEFAULT_STAB_KP, DEFAULT_STAB_KI, DEFAULT_STAB_KD, DIRECT);
  aileronsStabPID->SetMode(AUTOMATIC);
  aileronsStabPID->SetOutputLimits(-PID_STAB_LIMIT, PID_STAB_LIMIT);
  aileronsStabPID->SetSampleTime(SAMPLE_TIME);

  aileronsRatePID = new PID(&rollRate, &aileronsRateOutput, &aileronsStabOutput, DEFAULT_RATE_KP, DEFAULT_RATE_KI, DEFAULT_RATE_KD, DIRECT);
  aileronsRatePID->SetMode(AUTOMATIC);
  aileronsRatePID->SetOutputLimits(-PID_RATE_LIMIT, PID_RATE_LIMIT);
  aileronsRatePID->SetSampleTime(SAMPLE_TIME);

  elevatorStabPID = new PID(&pitchAngle, &elevatorStabOutput, &elevatorRXAngle, DEFAULT_STAB_KP, DEFAULT_STAB_KI, DEFAULT_STAB_KD, DIRECT);
  elevatorStabPID->SetMode(AUTOMATIC);
  elevatorStabPID->SetOutputLimits(-PID_STAB_LIMIT, PID_STAB_LIMIT);
  elevatorStabPID->SetSampleTime(SAMPLE_TIME);

  elevatorRatePID = new PID(&pitchRate, &elevatorRateOutput, &elevatorStabOutput, DEFAULT_RATE_KP, DEFAULT_RATE_KI, DEFAULT_RATE_KD, DIRECT);
  elevatorRatePID->SetMode(AUTOMATIC);
  elevatorRatePID->SetOutputLimits(-PID_RATE_LIMIT, PID_RATE_LIMIT);
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
  if (aux1RXPWM > AUX_LOW_END) {
    mode = FLIGHT_MODE_FBW;
  } else {
    mode = FLIGHT_MODE_RATE;
  }
  short ailOut = aileronsRXPWM;
  short eleOut = elevatorRXPWM;
  if (mode == FLIGHT_MODE_FBW) {
    rollAngle = orientationProvider->getRoll();
    aileronsStabPID->Compute();
    rollRate = orientationProvider->getRollRate();
    aileronsRatePID->Compute();
    ailOut = PWMReader::PWM_DEFAULT + map((int) aileronsRateOutput, -PID_RATE_LIMIT, PID_RATE_LIMIT, -PWM_CHANGE_LIMIT, PWM_CHANGE_LIMIT);

    pitchAngle = orientationProvider->getPitch();
    elevatorStabPID->Compute();
    pitchRate = orientationProvider->getPitchRate();
    elevatorRatePID->Compute();
    eleOut = PWMReader::PWM_DEFAULT + map((int) elevatorRateOutput, -PID_RATE_LIMIT, PID_RATE_LIMIT, -PWM_CHANGE_LIMIT, PWM_CHANGE_LIMIT);
  }
  servoController->setAilerons(ailOut);
  servoController->setElevator(eleOut);
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
  aux1RXPWM = pwmReader->getAUX1();
  aux2RXPWM = pwmReader->getAUX2();
}

