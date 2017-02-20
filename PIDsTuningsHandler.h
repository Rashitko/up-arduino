#ifndef PIDsTuningsHandler_h
#define PIDsTuningsHandler_h

#include "Arduino.h"

#include "Up.h"

class PIDsTuningsHandler: public BaseCommandHandler {
  private:
    static const byte COMMAND_TYPE = 'p';
    static const byte REQUEST_COMMAND_TYPE = 'P';
    static const byte COMMAND_SIZE = 27 * sizeof(float);
    static const byte REQUEST_COMMAND_SIZE = 0;
    BaseFlightController *flightController;
    bool isRequest = false;
  public:
    void initialize();
    bool canHandle(const byte commandType);
    int getPayloadSize();
    bool hasExecuted(byte payload[], const int payloadSize);
    void executeConfirm();
};

#endif
