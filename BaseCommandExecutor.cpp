#include "Up.h"

void BaseCommandExecutor::setUp(Up *up) {
  this->up = up;
}

void BaseCommandExecutor::addHandler(BaseCommandHandler *handler) {
  BaseCommandHandler **newHandlers = new BaseCommandHandler* [handlersSize + 1];
  newHandlers[handlersSize] = handler;
  if (handlers != 0) {
    for (int i = 0; i < handlersSize; i++) {
     newHandlers[i] = handlers[i];
    }
    delete [] handlers;
  }
  handlers = newHandlers;
  handlersSize++;
}

void BaseCommandExecutor::initialize() {
  for (int i = 0; i < handlersSize; i++) {
    handlers[i]->setUp(up);
    handlers[i]->initialize();
  }
}

void BaseCommandExecutor::handleCommandHeader(const byte commandType) {
  bool wasFound = false;
//  if (startHandler.canHandle(commandType)) {
//    state = STATE_RECEIVING_COMMAND;
//    receivingHandler = &startHandler;
//    receiveStart = millis();
//    wasFound = true;
//  } else if (startHandler.isStarted()) {
    for (int i = 0; i < handlersSize; i++) {
      if (handlers[i]->canHandle(commandType)) {
        receivingHandler = handlers[i];
        state = STATE_RECEIVING_COMMAND;
        receiveStart = millis();
        wasFound = true;
        break;
      }
    }
//  }
  if (!wasFound) {
    Serial.write('!');
    Serial.write(commandType);
  }
}

void BaseCommandExecutor::loop() {
  const int available = Serial.available();
  if (available > 0) {
    if (state == STATE_AVAITING_COMMAND) {
      const byte commandType = Serial.read();
      handleCommandHeader(commandType);
    }
    if (state == STATE_RECEIVING_COMMAND) {
      const unsigned long currentTime = millis();
      const unsigned long timeDiff = currentTime - receiveStart;
      if (timeDiff >= BaseCommandExecutor::COMMAND_RECEIVE_TIMEOUT) {
        state = STATE_AVAITING_COMMAND;
        receivingHandler == NULL;
        Serial.print("!");
      } else {
        const int available = Serial.available();
        const int requestedPayloadSize = receivingHandler->getPayloadSize();
        if (available >= requestedPayloadSize) {
          byte payload[requestedPayloadSize];
          Serial.readBytes(payload, requestedPayloadSize);
          bool executed = receivingHandler->hasExecuted(payload, requestedPayloadSize);
          if (executed) {
            if (confirmsEnabled) {
              receivingHandler->executeConfirm();
            }
            state = STATE_AVAITING_COMMAND;
            receivingHandler == NULL;
          }
        }
      }
    }
  }
}

void BaseCommandExecutor::setConfirmsEnabled(bool enabled) {
  confirmsEnabled = enabled;
}

