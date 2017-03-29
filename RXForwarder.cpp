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

  unsigned char channelData[sizeof(short)];
  
  ConversionUtils::shortToBytes(ailerons, channelData);
  data[0] = channelData[0];
  data[1] = channelData[1];
  
  ConversionUtils::shortToBytes(elevator, channelData);
  data[2] = channelData[0];
  data[3] = channelData[1];
  
  ConversionUtils::shortToBytes(throttle, channelData);
  data[4] = channelData[0];
  data[5] = channelData[1];
  
  ConversionUtils::shortToBytes(rudder, channelData);
  data[6] = channelData[0];
  data[7] = channelData[1];

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
  ailerons = constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
}

void RXForwarder::setElevator(const int pwm) {
  elevator = constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
}

void RXForwarder::setThrottle(const int pwm) {
  throttle = constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
}

void RXForwarder::setRudder(const int pwm) {
  rudder = constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
}

void RXForwarder::setAUX1(const int pwm) {
  aux1 = constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
}

void RXForwarder::setAUX2(const int pwm) {
  aux2 = constrain(pwm, PWMReader::MIN_PWM, PWMReader::MAX_PWM);
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


