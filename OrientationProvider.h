#ifndef OrientationProvider_h
#define OrientationProvider_h

#include "Arduino.h"
#include "Up.h"
#include "MPUReader.h"

class Up;
class MPUReader;

class OrientationProvider {
  private:
    Up *up = NULL;
    MPUReader *mpuReader = NULL;
  public:
    void initialize(const Up *up);
    void loop();
    const MPUReader* getMPUReader() const;
};

#endif

