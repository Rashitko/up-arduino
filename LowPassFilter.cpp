#include "LowPassFilter.h"

LowPassFilter::LowPassFilter(const float alpha, const short initialValue) {
  this->alpha = alpha;
  reset(initialValue);
}

const float LowPassFilter::getAlpha() const {
  return alpha;
}

void LowPassFilter::setAlpha(const float alpha) {
  this->alpha = alpha;
}

const short LowPassFilter::calculate(const short newRawValue) {
  float previousSum = 0.0;
  for (int i = 0; i < PREVIOUS_RESULTS_SIZE; i++) {
    previousSum += previousResults[i];
  }
  previousSum /= PREVIOUS_RESULTS_SIZE;
  previousResult = previousSum + alpha * (newRawValue - previousSum);
  for (int i = 1; i < PREVIOUS_RESULTS_SIZE; i++) {
    previousResults[i - 1] = previousResults[i];
  }
  previousResults[PREVIOUS_RESULTS_SIZE - 1] = previousResult;
  return previousResult;
}

void LowPassFilter::reset(const short initialValue) {
  previousResult = initialValue;
  for (int i = 0; i < PREVIOUS_RESULTS_SIZE; i++) {
    previousResults[i] = initialValue;
  }
}

