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

void setup() {
  up = new Up();
  up->initialize();
  
  // Set various options
  up->getRXForwarder()->setEnabled(false);
  up->getOrientationProvider()->setEnabled(true);
  up->getCommandExecutor()->setConfirmsEnabled(true);

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
//  pinMode(up->getPWMReader()->getAileronsPin(), INPUT_PULLUP);
//  attachPinChangeInterrupt(up->getPWMReader()->getAileronsPin(), calcCh1, CHANGE);
//  pinMode(up->getPWMReader()->getElevatorPin(), INPUT_PULLUP);
//  attachPinChangeInterrupt(up->getPWMReader()->getElevatorPin(), calcCh2, CHANGE);
//  pinMode(up->getPWMReader()->getThrottlePin(), INPUT_PULLUP);
//  attachPinChangeInterrupt(up->getPWMReader()->getThrottlePin(), calcCh3, CHANGE);
//  pinMode(up->getPWMReader()->getRudderPin(), INPUT_PULLUP);
//  attachPinChangeInterrupt(up->getPWMReader()->getRudderPin(), calcCh4, CHANGE);
//  pinMode(up->getPWMReader()->getAUX1Pin(), INPUT_PULLUP);
//  attachPinChangeInterrupt(up->getPWMReader()->getAUX1Pin(), calcAux1, CHANGE);
//  pinMode(up->getPWMReader()->getAUX2Pin(), INPUT_PULLUP);
//  attachPinChangeInterrupt(up->getPWMReader()->getAUX2Pin(), calcAux2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MPUReader::INTERRUPT_PIN), dmpDataReady, RISING);
}
