#ifndef Up_h
#define Up_h

#include "Arduino.h"

#include "BaseFlightController.h"

class BaseCommandExecutor;
class BaseCommandHandler;

class Up {
  private:
    BaseCommandExecutor *commandExecutor = NULL;
    BaseFlightController *flightController = NULL;
  public:
    const BaseCommandExecutor* getCommandExecutor() const;
    const BaseFlightController* getFlightController() const;
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
