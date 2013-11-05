// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// 
// A simple low resolution timer. The current implementation uses
// gettimeofday() to compute elapsed time, so the granularity of the timer
// depends on the granularity of that call. See 'man gettimeofday' for more
// information.
#ifndef __TIMER_H__
#define __TIMER_H__
#include <sys/time.h>

#include "Basics.h"

class Timer {
 public:
  // Create a new timer. A timer starts in the 'paused' state.
  Timer();
  
  // Free resources used by this timer.
  ~Timer();
  
  // Start the timer running. It is an error to call 'start' on an
  // already-running timer: This will cause an assertion to fail.
  void start();

  // Pause a running timer. It is an error to call 'pause' on an already-paused
  // timer: This will cause an assertion to fail.
  void pause();

  // Reset the timer to 0. You can call this at any time: A running timer will
  // start over at 0 and immediately begin recording time, whereas a paused
  // timer will just start at 0.
  void reset();

  // Get the time elapsed from the first 'start' call after the most recent
  // reset (or instantiation) in milliseconds.
  long getTimeInMilliseconds() const;

  // Get the time elapsed from the first 'start' call after the most recent
  // reset (or instantiation) in microseconds.
  long getTimeInMicroseconds() const;

  // Is this timer running?
  bool running() const;

 private:
  // The last 'gettimeofday' call result. This is mutable because it is updated
  // when 'getTimeIn*' is called. 
  // TODO: This is completely unnecessary, refactor so that mutations are only
  // done on reset.
  mutable timeval lastTick_;
  // The total recorded number of microseconds that have elapsed since the last
  // reset.
  mutable long uSecsElapsed_;
  // Is this timer running?
  bool started_;
  // Helper function to update the elapsed time.
  void updateTime() const;

  DISALLOW_EVIL_CONSTRUCTORS(Timer);
};

#endif
