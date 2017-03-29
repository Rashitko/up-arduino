#include "Up.h"
#include "AltitudeCommandHandler.h"
#include "HeadingCommandHandler.h"
#include "LocationCommandHandler.h"
#include "PanicCommandHandler.h"
#include "PIDsTuningsHandler.h"

Up *up = NULL;
AltitudeCommandHandler altitudeHandler;
HeadingCommandHandler headingHandler;
LocationCommandHandler locationHandler;
PanicCommandHandler panicHandler;
PIDsTuningsHandler pidsHandler;
long start = 0;

const static boolean FORWARD = true;

void setup() {
  up = new Up();
  up->initialize();
  // Set various options
  up->getRXForwarder()->setEnabled(FORWARD);
  up->getOrientationProvider()->setEnabled(FORWARD);
  up->getCommandExecutor()->setConfirmsEnabled(false);
  // Register handlers
  up->getCommandExecutor()->addHandler(&altitudeHandler);
  up->getCommandExecutor()->addHandler(&headingHandler);
  up->getCommandExecutor()->addHandler(&locationHandler);
  up->getCommandExecutor()->addHandler(&panicHandler);
  up->getCommandExecutor()->addHandler(&pidsHandler);
  // Setup Up
  up->setup();
  // Attach interrupts for the PWMReader
  attachInterrupts();
}

void loop() {
  up->loop();
}

// ================================================================
// ===                    MPU INTERRUPTS                        ===
// ================================================================
void dmpDataReady() {
  up->getOrientationProvider()->getMPUReader()->dmpDataReady();
}

// ================================================================
// ===                    PWM READINGS                          ===
// ================================================================
void calcCh1() {
  up->getPWMReader()->calcCh1();
}
void calcCh2() {
  up->getPWMReader()->calcCh2();
}
void calcCh3() {
  up->getPWMReader()->calcCh3();
}
void calcCh4() {
  up->getPWMReader()->calcCh4();
}
void calcAux1() {
  up->getPWMReader()->calcAux1();
}
void calcAux2() {
  up->getPWMReader()->calcAux1();
}
void attachInterrupts() {
  setPinMode(up->getPWMReader()->getAileronsPin());
  attachPinChangeInterrupt(up->getPWMReader()->getAileronsPCINTPin(), calcCh1, CHANGE);
  setPinMode(up->getPWMReader()->getElevatorPin());
  attachPinChangeInterrupt(up->getPWMReader()->getElevatorPCINTPin(), calcCh2, CHANGE);
  setPinMode(up->getPWMReader()->getThrottlePin());
  attachPinChangeInterrupt(up->getPWMReader()->getThrottlePCINTPin(), calcCh3, CHANGE);
  setPinMode(up->getPWMReader()->getRudderPin());
  attachPinChangeInterrupt(up->getPWMReader()->getRudderPCINTPin(), calcCh4, CHANGE);
  setPinMode(up->getPWMReader()->getAUX1Pin());
  attachPinChangeInterrupt(up->getPWMReader()->getAux1PCINTPin(), calcAux1, CHANGE);
  //  setPinMode(up->getPWMReader()->getAUX2Pin());
  //  attachPinChangeInterrupt(up->getPWMReader()->getAux1PCINTPin(), calcAux2, CHANGE);
  setPinMode(3);
  attachInterrupt(digitalPinToInterrupt(MPUReader::INTERRUPT_PIN), dmpDataReady, RISING);
}

void setPinMode(const int pin) {
  pinMode(pin, INPUT_PULLUP);
}

