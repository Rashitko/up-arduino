#include "PWMReader.h"

const int PWMReader::getAileronsPin() const {
  return ailPin;
}

const int PWMReader::getElevatorPin() const {
  return elePin;
}

const int PWMReader::getThrottlePin() const {
  return thrPin;
}

const int PWMReader::getRudderPin() const {
  return rudPin;
}

const int PWMReader::getAUX1Pin() const {
  return aux1Pin;
}

const int PWMReader::getAUX2Pin() const {
  return aux2Pin;
}

void PWMReader::setAileronsPin(const int pin) {
  ailPin = pin;
}

void PWMReader::setElevatorPin(const int pin) {
  elePin = pin;
}

void PWMReader::setThrottlePin(const int pin) {
  thrPin = pin;
}

void PWMReader::setRudderPin(const int pin) {
  rudPin = pin;
}

void PWMReader::setAUX1Pin(const int pin) {
  aux1Pin = pin;
}

void PWMReader::setAUX2Pin(const int pin) {
  aux2Pin = pin;
}

void PWMReader::calcCh1() {
  if (digitalRead(getAileronsPin()) == HIGH) {
    ailStart = micros();
  } else {
    ailInShared = (uint16_t)(micros() - ailStart);
    updateFlagsShared |= AIL_FLAG;
  }
}

void PWMReader::calcCh2() {
  if (digitalRead(getElevatorPin()) == HIGH) {
    eleStart = micros();
  } else {
    eleInShared = (uint16_t)(micros() - eleStart);
    updateFlagsShared |= ELE_FLAG;
  }
}

void PWMReader::calcCh3() {
  if (digitalRead(getThrottlePin()) == HIGH) {
    thrStart = micros();
  } else {
    thrInShared = (uint16_t)(micros() - thrStart);
    updateFlagsShared |= THR_FLAG;
  }
}

void PWMReader::calcCh4() {
  if (digitalRead(getRudderPin()) == HIGH) {
    rudStart = micros();
  } else {
    rudInShared = (uint16_t)(micros() - rudStart);
    updateFlagsShared |= RUD_FLAG;
  }
}

void PWMReader::calcAux1() {
  if (digitalRead(getAUX1Pin()) == HIGH) {
    aux1Start = micros();
  } else {
    aux1InShared = (uint16_t)(micros() - aux1Start);
    updateFlagsShared |= AUX1_FLAG;
  }
}

void PWMReader::calcAux2() {
  if (digitalRead(getAUX2Pin()) == HIGH) {
    aux2Start = micros();
  } else {
    aux2InShared = (uint16_t)(micros() - aux2Start);
    updateFlagsShared |= AUX2_FLAG;
  }
}

void PWMReader::loop() {
  static uint16_t ailIn;
  static uint16_t eleIn;
  static uint16_t thrIn;
  static uint16_t rudIn;
  static uint16_t aux1In;
  static uint16_t aux2In;

  static uint8_t updateFlags;
  if (updateFlagsShared) {
    noInterrupts();

    updateFlags = updateFlagsShared;
    updateFlagsShared = 0;

    ailIn = ailInShared;
    eleIn = eleInShared;
    thrIn = thrInShared;
    rudIn = rudInShared;
    aux1In = aux1InShared;
    aux2In = aux2InShared;

    interrupts();
  }

  if (updateFlags) {
//    pwmReader.setAilerons(ailIn);
//    pwmReader.setElevator(eleIn);
//    pwmReader.setThrottle(thrIn);
//    pwmReader.setRudder(rudIn);
//    pwmReader.setAux1(aux1In);
//    pwmReader.setAux2(aux2In);
  }
  updateFlags = 0;
}

