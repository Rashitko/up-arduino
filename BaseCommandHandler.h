#ifndef BaseCommandHandler_h
#define BaseCommandHandler_h

#include "Arduino.h"
#include "Up.h"

class Up;

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

#endif
