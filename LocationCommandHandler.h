#ifndef LocationCommandHandler_h
#define LocationCommandHandler_h

#include "Arduino.h"

#include "Up.h"
#include "ConversionUtils.h"

class LocationCommandHandler: public BaseCommandHandler {
  private:
    const static byte COMMAND_TYPE = 'l';
    const static byte PAYLOAD_SIZE = 8;
    BaseFlightController *flightController = NULL;
  public:
    void initialize();
    bool canHandle(const byte commandType);
    int getPayloadSize();
    bool hasExecuted(byte payload[], const int payloadSize);
    void executeConfirm();
};

#endif
