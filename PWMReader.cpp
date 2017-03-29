#include "PWMReader.h"

void PWMReader::initialize(const Up *up) {
  this->up = up;
}

const int PWMReader::getAileronsPin() const {
  return AILERONS_PIN;
}

const int PWMReader::getElevatorPin() const {
  return ELEVATOR_PIN;
}

const int PWMReader::getThrottlePin() const {
  return THROTTLE_PIN;
}

const int PWMReader::getRudderPin() const {
  return RUDDER_PIN;
}

const int PWMReader::getAUX1Pin() const {
  return AUX1_PIN;
}

const int PWMReader::getAUX2Pin() const {
  return AUX2_PIN;
}

const int PWMReader::getAileronsPCINTPin() const {
  return AILERONS_PCINT_PIN;
}

const int PWMReader::getElevatorPCINTPin() const {
  return ELEVATOR_PCINT_PIN;
}

const int PWMReader::getThrottlePCINTPin() const {
  return THROTTLE_PCINT_PIN;
}

const int PWMReader::getRudderPCINTPin() const {
  return RUDDER_PCINT_PIN;
}

const int PWMReader::getAux1PCINTPin() const {
  return AUX1_PCINT_PIN;
}

const int PWMReader::getAux2PCINTPin() const {
  return AUX2_PCINT_PIN;
}

const int PWMReader::getAilerons() const {
  return ailPWM;
}

const int PWMReader::getElevator() const {
  return elePWM;
}

const int PWMReader::getThrottle() const {
  return thrPWM;
}

const int PWMReader::getRudder() const {
  return rudPWM;
}

const int PWMReader::getAUX1() const {
  return aux1PWM;
}

const int PWMReader::getAUX2() const {
  return aux2PWM;
}

void PWMReader::calcCh1() {
  if (digitalRead(getAileronsPin()) == HIGH) {
    ailStart = micros();
  } else {
    ailInShared = constrain(micros() - ailStart, MIN_PWM, MAX_PWM);
    updateFlagsShared |= AIL_FLAG;
  }
}

void PWMReader::calcCh2() {
  if (digitalRead(getElevatorPin()) == HIGH) {
    eleStart = micros();
  } else {
    eleInShared = constrain(micros() - eleStart, MIN_PWM, MAX_PWM);
    updateFlagsShared |= ELE_FLAG;
  }
}

void PWMReader::calcCh3() {
  if (digitalRead(getThrottlePin()) == HIGH) {
    thrStart = micros();
  } else {
    thrInShared = (micros() - thrStart);
    updateFlagsShared |= THR_FLAG;
  }
}

void PWMReader::calcCh4() {
  if (digitalRead(getRudderPin()) == HIGH) {
    rudStart = micros();
  } else {
    rudInShared = (micros() - rudStart);
    updateFlagsShared |= RUD_FLAG;
  }
}

void PWMReader::calcAux1() {
  if (digitalRead(getAUX1Pin()) == HIGH) {
    aux1Start = micros();
  } else {
    aux1InShared = (micros() - aux1Start);
    updateFlagsShared |= AUX1_FLAG;
  }
}

void PWMReader::calcAux2() {
  if (digitalRead(getAUX2Pin()) == HIGH) {
    aux2Start = micros();
  } else {
    aux2InShared = (micros() - aux2Start);
    updateFlagsShared |= AUX2_FLAG;
  }
}

void PWMReader::loop() {
  static uint8_t updateFlags;
  if (updateFlagsShared) {
    noInterrupts();

    updateFlags = updateFlagsShared;
    updateFlagsShared = 0;

    const short newAilPWM = ailInShared;
    const short newElePWM = eleInShared;
    const short newThrPWM = thrInShared;
    const short newRudPWM = rudInShared;
    aux1PWM = aux1InShared;
    aux2PWM = aux2InShared;

    interrupts();
    if (shouldFilter(ailPWM, newAilPWM)) {
      ailPWM = aileronsFilter.calculate(newAilPWM);
    } else {
      ailPWM = newAilPWM;
      aileronsFilter.reset(ailPWM);
    }
    if (shouldFilter(elePWM, newElePWM)) {
      elePWM = elevatorFilter.calculate(newElePWM);
    } else {
      elePWM = newElePWM;
      elevatorFilter.reset(elePWM);
    }
    if (shouldFilter(thrPWM, newThrPWM)) {
      thrPWM = throttleFilter.calculate(newThrPWM);
    } else {
      thrPWM = newThrPWM;
      throttleFilter.reset(thrPWM);
    }
    if (shouldFilter(rudPWM, newRudPWM)) {
      rudPWM = rudderFilter.calculate(newRudPWM);
    } else {
      rudPWM = newRudPWM;
      rudderFilter.reset(rudPWM);
    }
  }
  updateFlags = 0;
}

const bool PWMReader::shouldFilter(const short prevPWM, const short currentPWM) const {
  return abs(prevPWM - currentPWM) < FILTER_CHANGE_LIMIT;
}

