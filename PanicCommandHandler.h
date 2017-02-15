#ifndef PanicCommandHandler_h
#define PanicCommandHandler_h

#include "Arduino.h"

#include "Up.h"

#include "BaseFlightController.h"
#include "ConversionUtils.h"

class PanicCommandHandler: public BaseCommandHandler {
  private:
    static const byte PANIC_COMMAND_TYPE = 'p';
    static const byte PANIC_COMMAND_SIZE = 3;
    bool inPanic = false;
    bool requiredDelay = 0;
    OrientationProvider *orientationProvider = NULL;
  public:
    void initialize();
    bool canHandle(const byte commandType);
    int getPayloadSize();
    bool hasExecuted(byte payload[], const int payloadSize);
    void executeConfirm();
    const bool isArmed();
};

#endif
