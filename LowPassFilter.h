#ifndef LowPassFilter_h
#define LowPassFilter_h

#include "Arduino.h"

class LowPassFilter {

  private:
    const static byte PREVIOUS_RESULTS_SIZE = 10;
   
    short previousResults[PREVIOUS_RESULTS_SIZE];
    short previousResult;
    float alpha = DEFAULT_ALPHA;
  
  public:
    const static float DEFAULT_ALPHA = 0.9;
    LowPassFilter(const float alpha, const short initialValue);
    const float getAlpha() const;
    void setAlpha(const float alpha);
    const short calculate(const short newRawValue);
    void reset(const short initialValue);
};

#endif

