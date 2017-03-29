#ifndef Up_h
#define Up_h

#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

#include "Arduino.h"

#include "BaseCommandExecutor.h"
#include "BaseFlightController.h"
#include "ConversionUtils.h"
#include "RXForwarder.h"
#include "PWMReader.h"
#include "OrientationProvider.h"
#include "ServoController.h"

class BaseCommandExecutor;
class BaseCommandHandler;
class RXForwarder;
class PWMReader;
class OrientationProvider;
class BaseFlightController;
class ServoController;

class Up {
  private:
    BaseCommandExecutor *commandExecutor = NULL;
    BaseFlightController *flightController = NULL;
    RXForwarder *rxForwarder = NULL;
    ServoController *servoController = NULL;
    PWMReader *pwmReader = NULL;
    OrientationProvider* orientationProvider = NULL;

    void initializeSerial();
  public:
    const static long SERIAL_INIT_DELAY = 100;
    Up();
    Up(BaseCommandExecutor *commandExecutor, BaseFlightController *flightController, RXForwarder *rxForwarder, PWMReader *pwmReader, ServoController *servoController, OrientationProvider* orientationProvider);
    ~Up();
    const BaseCommandExecutor* getCommandExecutor() const;
    const BaseFlightController* getFlightController() const;
    const RXForwarder* getRXForwarder() const;
    const ServoController* getServoController() const;
    const PWMReader* getPWMReader() const;
    const OrientationProvider* getOrientationProvider() const;
    void initialize();
    void setup();
    void loop();
};

#endif
