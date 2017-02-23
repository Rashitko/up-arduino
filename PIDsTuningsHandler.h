#ifndef PIDsTuningsHandler_h
#define PIDsTuningsHandler_h

#include "Arduino.h"

#include "Up.h"

class PIDsTuningsHandler: public BaseCommandHandler {
  private:
    static const byte COMMAND_TYPE = 't';
    static const byte REQUEST_COMMAND_TYPE = 'T';
    static const byte CHANNELS_COUNT = 2; // ail, ele
    static const byte PIDS_COUNT = 2; // rate, stab
    
    BaseFlightController *flightController;
    bool isRequest = false;

    const bool setAileronsRate(byte payload[]);
    const bool setElevatorRate(byte payload[]);
    const bool setAileronsStab(byte payload[]);
    const bool setElevatorStab(byte payload[]);
    void packPIDs(unsigned char *data, const float *pids, const unsigned int offset) const;
    void packPID(unsigned char *data, const float pidParam, const unsigned int dataOffset) const;
    void PIDsTuningsHandler::sendPIDs(const byte responseCommandType) const;
  public:
    static const byte PID_ELEMENTS_COUNT = 3; // P, I, D
    static const byte COMMAND_SIZE = PID_ELEMENTS_COUNT * CHANNELS_COUNT * PIDS_COUNT * sizeof(float);
    static const byte REQUEST_COMMAND_SIZE = 0;
    
    void initialize();
    bool canHandle(const byte commandType);
    int getPayloadSize();
    bool hasExecuted(byte payload[], const int payloadSize);
    void executeConfirm();
};

#endif
