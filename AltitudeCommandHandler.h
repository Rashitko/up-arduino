#ifndef AltitudeCommandHandler_h
#define AltitudeCommandHandler_h

#include "Arduino.h"

#include "Up.h"

#include "BaseFlightController.h"
#include "ConversionUtils.h"

class AltitudeCommandHandler: public BaseCommandHandler {
  private:
    static const byte ALTITUDE_COMMAND_TYPE = 'h';
    static const byte ALTITUDE_COMMAND_SIZE = 2;
    short altitude = 0;
    BaseFlightController *flightController;
  public:
    void initialize();
    bool canHandle(const byte commandType);
    int getPayloadSize();
    bool hasExecuted(byte payload[], const int payloadSize);
    void executeConfirm();
    const bool isArmed();
};

#endif
