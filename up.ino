#include "Up.h"
#include "AltitudeCommandHandler.h"
#include "HeadingCommandHandler.h"
#include "LocationCommandHandler.h"

Up up;

void setup() {
  Serial.begin(9600);
  while (!Serial) ;

  up.initialize();
  up.getCommandExecutor()->setConfirmsEnabled(true);

  AltitudeCommandHandler altitudeHandler;
  up.getCommandExecutor()->addHandler(&altitudeHandler);

  HeadingCommandHandler headingHandler;
  up.getCommandExecutor()->addHandler(&headingHandler);

  LocationCommandHandler locationHandler;
  up.getCommandExecutor()->addHandler(&locationHandler);
  
  up.setup();
}

void loop() {
  up.loop();
}
