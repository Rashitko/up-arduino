#include "Up.h"

const BaseCommandExecutor* Up::getCommandExecutor() const {
  return commandExecutor;
}

const BaseFlightController* Up::getFlightController() const {
  return flightController;
}

const RXForwarder* Up::getRXForwarder() const {
  return rxForwarder;
}

const PWMReader* Up::getPWMReader() const {
  return pwmReader;
}

void Up::initialize() {
  Serial.begin(9600);
  while (!Serial) ;
  
  commandExecutor = new BaseCommandExecutor();
  flightController = new BaseFlightController();
  rxForwarder = new RXForwarder();
  pwmReader = new PWMReader();
}

void Up::setup() {
  getCommandExecutor()->setUp(this);
  getCommandExecutor()->initialize();
}

void Up::loop() {
  getCommandExecutor()->loop();
  getRXForwarder()->loop();
  getPWMReader()->loop();
}

Up::~Up() {
  if (this->commandExecutor != NULL) {
    delete this->commandExecutor;
  }
  if (this->flightController != NULL) {
    delete this->flightController;
  }
  delete this->rxForwarder;
  delete this->pwmReader;
}


