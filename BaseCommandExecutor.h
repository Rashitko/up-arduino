#ifndef BaseCommandExecutor_h
#define BaseCommandExecutor_h

#include "Arduino.h"
#include "Up.h"
#include "BaseCommandHandler.h"

class Up;

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
