#include "RXForwarder.h"

void RXForwarder::loop() {
  if (enabled) {
    const unsigned long currentTime = millis();
    const unsigned long timeDiff = currentTime - prevSentStamp;
    if (timeDiff >= this->getDelay()) {
      sendRXData();
      prevSentStamp = currentTime;
    }
  }
}

void RXForwarder::sendRXData() {
  unsigned char data[PAYLOAD_SIZE];

  data[AILERONS_POSITION] = this->ailerons;
  data[ELEVATOR_POSITION] = this->elevator;
  data[THROTTLE_POSITION] = this->throttle;
  data[RUDDER_POSITION] = this->rudder;
  data[AUX1_POSITION] = this->aux1;
  data[AUX2_POSITION] = this->aux2;

  unsigned char response[PAYLOAD_SIZE + 1];
  ConversionUtils::packCommandWithPayload(COMMAND_TYPE, data, PAYLOAD_SIZE, response);
  Serial.write(response, PAYLOAD_SIZE + 1);
}

const int RXForwarder::getDelay() const {
  return this->forwardDelay;
}

void RXForwarder::setDelay(const int forwardDelay) {
  this->forwardDelay = forwardDelay;
}

void RXForwarder::setEnabled(const bool enabled) {
  this->enabled = enabled;
}

const bool RXForwarder::isEnabled() const {
  return enabled;
}

void RXForwarder::setAilerons(const int pwm) {
  ailerons = pwm;
}

void RXForwarder::setElevator(const int pwm) {
  elevator = pwm;
}

void RXForwarder::setThrottle(const int pwm) {
  throttle = pwm;
}

void RXForwarder::setRudder(const int pwm) {
  rudder = pwm;
}

void RXForwarder::setAUX1(const int pwm) {
  aux1 = pwm;
}

void RXForwarder::setAUX2(const int pwm) {
  aux2 = pwm;
}

const short RXForwarder::getAilerons() const {
  return ailerons;
}

const short RXForwarder::getElevator() const {
  return elevator;
}

const short RXForwarder::getThrottle() const {
  return throttle;
}
const short RXForwarder::getRudder() const {
  return rudder;
}

const short RXForwarder::getAUX1() const {
  return aux1;
}

const short RXForwarder::getAUX2() const {
  return aux2;
}


