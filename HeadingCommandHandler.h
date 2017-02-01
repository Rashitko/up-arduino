#ifndef HeadingCommandHandler_h
#define HeadingCommandHandler_h

#include "Arduino.h"

#include "Up.h"
#include "ConversionUtils.h"

class HeadingCommandHandler: public BaseCommandHandler {
  private:
    static const byte CURRENT_HEADING_COMMAND_TYPE = 'b';
    static const byte REQUIRED_HEADING_COMMAND_TYPE = 'B';
    static const byte PAYLOAD_SIZE = 2;
    byte receivedCommandType = 0;
    BaseFlightController *flightController = NULL;
  public:
    void initialize();
    bool canHandle(const byte commandType);
    int getPayloadSize();
    bool hasExecuted(byte payload[], const int payloadSize);
    void executeConfirm();
};

#endif
