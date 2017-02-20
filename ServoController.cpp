#include "ServoController.h"

void ServoController::initialize() {
  aileronsServo.attach(getAileronsPin(), PWMReader::MIN_PWM, PWMReader::MAX_PWM);
  elevatorServo.attach(getElevatorPin(), PWMReader::MIN_PWM, PWMReader::MAX_PWM);
  throttleServo.attach(getThrottlePin(), PWMReader::MIN_PWM, PWMReader::MAX_PWM);
  rudderServo.attach(getRudderPin(), PWMReader::MIN_PWM, PWMReader::MAX_PWM);
}

void ServoController::setAilerons(const int pwm) {
  aileronsServo.writeMicroseconds(constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM));
}

void ServoController::setElevator(const int pwm) {
  elevatorServo.writeMicroseconds(constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM));

}

void ServoController::setThrottle(const int pwm) {
  throttleServo.writeMicroseconds(constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM));
}

void ServoController::setRudder(const int pwm) {
  rudderServo.writeMicroseconds(constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM));
}
const int ServoController::getAileronsPin() const {
  return aileronsPin;
}

const int ServoController::getElevatorPin() const {
  return elevatorPin;
}

const int ServoController::getThrottlePin() const {
  return throttlePin;
}

const int ServoController::getRudderPin() const {
  return rudderPin;
}

