#include "Up.h"

Up::Up() {
  commandExecutor = new BaseCommandExecutor();
  flightController = new BaseFlightController();
  rxForwarder = new RXForwarder();
  pwmReader = new PWMReader();
  orientationProvider = new OrientationProvider();
}

Up::Up(BaseCommandExecutor *commandExecutor, BaseFlightController *flightController, RXForwarder *rxForwarder, PWMReader *pwmReader, OrientationProvider* orientationProvider) {
  this->commandExecutor = commandExecutor;
  this->flightController = flightController;
  this->rxForwarder = rxForwarder;
  this->pwmReader = pwmReader;
  this->orientationProvider = orientationProvider;
}

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

const OrientationProvider* Up::getOrientationProvider() const {
  return orientationProvider;
}

void Up::initialize() {
  initializeSerial();
}

void Up::setup() {
  getCommandExecutor()->setUp(this);
  getCommandExecutor()->initialize();
  getOrientationProvider()->initialize(this);
}

void Up::loop() {
  getCommandExecutor()->loop();
  getOrientationProvider()->loop();
  getPWMReader()->loop();
  getRXForwarder()->loop();
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

void Up::initializeSerial() {
  Serial.begin(9600);
  while (!Serial) ;
}


