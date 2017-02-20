#include "OrientationProvider.h"

void OrientationProvider::initialize(const Up* up) {
  this->up = up;
  this->mpuReader = new MPUReader(this);
}

void OrientationProvider::loop() {
  this->mpuReader->loop();
  
  const unsigned long currentTime = millis();
  const unsigned long timeDiff = currentTime - prevSentStamp;
  if (timeDiff >= this->getDelay()) {
      forwardOrientation();
      prevSentStamp = currentTime;
    }
}

const MPUReader* OrientationProvider::getMPUReader() const {
  return mpuReader;
}

void OrientationProvider::setEnabled(const bool enabled) {
  this->enabled = enabled;
}

int OrientationProvider::getDelay() const {
  return forwardDelay;
}

void OrientationProvider::setDelay(const int newDelay) {
  forwardDelay = newDelay;
}

void OrientationProvider::setYaw(const float yaw) {
  this->yaw = yaw;
}

void OrientationProvider::setPitch(const float pitch) {
  this->pitch = pitch;
}

void OrientationProvider::setRoll(const float roll) {
  this->roll = roll;
}

void OrientationProvider::setYawRate(const float yawRate) {
  this->yawRate = yawRate;
}

void OrientationProvider::setPitchRate(const float pitchRate) {
  this->pitchRate = pitchRate;
}

void OrientationProvider::setRollRate(const float rollRate) {
  this->rollRate = rollRate;
}

float OrientationProvider::getYaw() const {
  return yaw;
}

float OrientationProvider::getPitch() const {
  return pitch;
}

float OrientationProvider::getRoll() const {
  return roll;
}

float OrientationProvider::getYawRate() const {
  return yawRate;
}

float OrientationProvider::getPitchRate() const {
  return pitchRate;
}

float OrientationProvider::getRollRate() const {
  return rollRate;
}

void OrientationProvider::forwardOrientation() {
  if (!enabled) {
    return;
  }
  unsigned char data[PAYLOAD_SIZE];

  unsigned char yawData[ConversionUtils::FLOAT_SIZE];
  ConversionUtils::floatToBytes(getYaw(), yawData);
  int offset = 0;
  for (int i = 0; i < PAYLOAD_SIZE / 3; i++) {
    data[offset + i] = yawData[i];
  }

  unsigned char pitchData[ConversionUtils::FLOAT_SIZE];
  ConversionUtils::floatToBytes(getPitch(), pitchData);
  offset = (PAYLOAD_SIZE / 3);
  for (int i = 0; i < PAYLOAD_SIZE / 3; i++) {
    data[offset + i] = pitchData[i];
  }

  unsigned char rollData[ConversionUtils::FLOAT_SIZE];
  ConversionUtils::floatToBytes(getRoll(), rollData);
  offset = (PAYLOAD_SIZE / 3) * 2;
  for (int i = 0; i < PAYLOAD_SIZE / 3; i++) {
    data[offset + i] = rollData[i];
  }
  
  unsigned char response[PAYLOAD_SIZE + 1];
  ConversionUtils::packCommandWithPayload(COMMAND_TYPE, data, PAYLOAD_SIZE, response);
  Serial.write(response, PAYLOAD_SIZE + 1);
}

