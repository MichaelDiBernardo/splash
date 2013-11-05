// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class Timer and related constructs.
#include "Timer.h"
#include <assert.h>

static const int kNumUSecsInMS = 1000;
static const int kNumUSecsInSec = 1000000;

Timer::Timer() : uSecsElapsed_(0), started_(false) {
}

Timer::~Timer() {
}

void Timer::start() {
  assert(!started_);
  gettimeofday(&lastTick_, NULL);
  started_ = true;
}

void Timer::pause() {
  assert(started_);
  updateTime();
  started_ = false;
}

void Timer::reset() {
  if (started_ == true) updateTime();
  uSecsElapsed_ = 0;
}

long Timer::getTimeInMilliseconds() const {
  return (getTimeInMicroseconds() / kNumUSecsInMS);
}

long Timer::getTimeInMicroseconds() const {
  if (started_) updateTime();
  return uSecsElapsed_;
}

void Timer::updateTime() const {
  long timePassedSinceLastTick = 0;
  timeval currentTick;
  gettimeofday(&currentTick, NULL);

  timePassedSinceLastTick = (currentTick.tv_sec - lastTick_.tv_sec) * kNumUSecsInSec + 
                            (currentTick.tv_usec - lastTick_.tv_usec);
  uSecsElapsed_ += timePassedSinceLastTick;
  lastTick_ = currentTick;
}

bool Timer::running() const {
  return started_;
}
