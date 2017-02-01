#include "Up.h"

const BaseCommandExecutor* Up::getCommandExecutor() const {
  return commandExecutor;
}

const BaseFlightController* Up::getFlightController() const {
  return flightController;
}

void Up::initialize() {
  this->commandExecutor = new BaseCommandExecutor();
  this->flightController = new BaseFlightController();
}

void Up::setup() {
  getCommandExecutor()->setUp(this);
  getCommandExecutor()->initialize();
}

void Up::loop() {
  getCommandExecutor()->loop();
}
