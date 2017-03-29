#include "ServoController.h"

void ServoController::initialize(const Up* up) {
  this->up = up;
  aileronsServo.attach(AILERONS_PIN, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
  elevatorServo.attach(ELEVATOR_PIN, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
  throttleServo.attach(THROTTLE_PIN, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
  rudderServo.attach(RUDDER_PIN, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
}

void ServoController::setAilerons(const short pwm) {
  aileronsServo.writeMicroseconds(constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM));
  up->getRXForwarder()->setAilerons(pwm);
}

void ServoController::setElevator(const short pwm) {
  elevatorServo.writeMicroseconds(constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM));
  up->getRXForwarder()->setElevator(pwm);
}

void ServoController::setThrottle(const short pwm) {
  throttleServo.writeMicroseconds(constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM));
  up->getRXForwarder()->setThrottle(pwm);
}

void ServoController::setRudder(const short pwm) {
  rudderServo.writeMicroseconds(constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM));
  up->getRXForwarder()->setRudder(pwm);
}
