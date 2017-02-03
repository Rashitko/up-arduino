#include "OrientationProvider.h"

void OrientationProvider::initialize(const Up* up) {
  this->up = up;
  this->mpuReader = new MPUReader(up);
}

void OrientationProvider::loop() {
  this->mpuReader->loop();
}

const MPUReader* OrientationProvider::getMPUReader() const {
  return mpuReader;
}

