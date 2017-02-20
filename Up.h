#ifndef Up_h
#define Up_h

#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

#include "Arduino.h"

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

class BaseCommandHandler {
  protected:
    Up *up = NULL;
  public:
    void setUp(Up *up) {
      this->up = up;
    }
    virtual void initialize() = 0;
    virtual bool canHandle(const byte commandType) = 0;
    virtual int getPayloadSize() = 0;
    virtual bool hasExecuted(byte payload[], const int payloadSize) = 0;
    virtual void executeConfirm() {
      
    };
};


typedef enum {
  STATE_AVAITING_COMMAND, STATE_RECEIVING_COMMAND
} InputState;

class BaseCommandExecutor {
  private:
    // HANDLERS RELATED FIELDS
    Up *up = NULL;
    BaseCommandHandler **handlers = 0;
    int handlersSize = 0;

    // RECEIVE RELATED FIELDS
    InputState state = STATE_AVAITING_COMMAND;
    BaseCommandHandler *receivingHandler = NULL;
    unsigned long receiveStart = millis();

    // DEBUG FIELDS
    bool confirmsEnabled = false;

    // METHODS
    void handleCommandHeader(const byte commandType);
  public:
    // CONSTS
    static const int COMMAND_RECEIVE_TIMEOUT = 100;

    // METHODS
    void setUp(Up *up);
    void initialize();
    void addHandler(BaseCommandHandler *handler);
    void loop();
    void setConfirmsEnabled(bool enabled);
};

#endif
