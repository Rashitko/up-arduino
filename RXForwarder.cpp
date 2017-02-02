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

const bool RXForwarder::isEnabled() const{
  return enabled;
}

