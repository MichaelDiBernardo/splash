#include "Animation.h"
#ifdef WIN32
#include <windows.h>
#endif

#ifdef __mac
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef __debug
#include <assert.h>
#endif

#include <math.h>
#include <sys/time.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "Frame.h"

Animation::Animation(const char* filename) 
  : FrameSequence(filename), started_(false), paused_(false), looped_(false) {
  // Compute running time in ms, given the time of the last frame in sec.
  runningTime_ = frames_[frames_.size() - 1]->getTimeInMS();
}

Animation::~Animation() {
}

void Animation::start() {
  #ifdef __debug
  assert(!started_);
  #endif
  started_ = true;
  timePassed_ = 0;
  gettimeofday(&lastTick_, NULL);
}

void Animation::startPaused() {
  #ifdef __debug
  assert(!started_);
  #endif
  paused_ = true;
  start();
}

void Animation::pause() {
  #ifdef __debug
  assert(!paused_);    
  assert(started_);
  #endif
  paused_ = true;
}

void Animation::unpause() {
  #ifdef __debug
  assert(paused_);    
  assert(started_);
  #endif
  paused_ = false;

  gettimeofday(&lastTick_, NULL);
  timePassed_ = getCurrentFrame().getTimeInMS();
}

void Animation::nextFrame() {
    FrameSequence::fastForwardTo(timePassed_);
    timePassed_ = FrameSequence::getCurrentFrame().getTimeInMS();
}

bool Animation::isPaused() const {
    return paused_;
}

Frame Animation::getCurrentFrame() {
  #ifdef __debug
  assert(started_);
  #endif
  // If we're not paused_, update the time that's passed.
  if (!paused_) updateTime();
  if (runningTime_ == 0) return FrameSequence::getCurrentFrame();

  // Find the keyframe that occurs after the currently elapsed time.  This full
  // search probably isn't needed, but I haven't experienced any real slowdown,
  // so I'm just gonna keep it :)
  unsigned int afterIndex;
  for (afterIndex = 0; afterIndex < frames_.size(); ++afterIndex) {   
      if (frames_[afterIndex]->getTimeInMS() == timePassed_) return *(frames_[afterIndex]);
      if (frames_[afterIndex]->getTimeInMS() > timePassed_) break;
  }

  #ifdef __debug
  assert(afterIndex != frames_.size());
  #endif

  // Calculation for interpolation taken from [2] (see header for citations),
  // but the math really isn't that hard...
  long firstTimeInMS = frames_[afterIndex-1]->getTimeInMS();
  long secondTimeInMS = frames_[afterIndex]->getTimeInMS();
  
  double frameTimeDifference = static_cast<double>(secondTimeInMS - firstTimeInMS);
  double timePastLastFrame = static_cast<double>(timePassed_ - firstTimeInMS);
  
  #ifdef __debug
  cerr << "TIME ELAPSED " << timePassed_ << "\tPF=" << afterIndex -1 << "\tNF=" << afterIndex << endl;
  #endif
  
  const Frame& previous = *(frames_[afterIndex-1]);
  const Frame& current = *(frames_[afterIndex]);

  return (previous + (current - previous) * (timePastLastFrame / frameTimeDifference));
}


bool Animation::hasLooped() const {
  return looped_;
}

void Animation::updateTime() {
  // Compute how much time passed since the last time this was called.
  long timePassedSinceLastTick = 0;
  timeval currentTick;
  gettimeofday(&currentTick, NULL);

  const int kNumUSecsInSec = 1000000;
  const int kNumMSInSec = 1000;

  timePassedSinceLastTick = (currentTick.tv_sec - lastTick_.tv_sec) * kNumUSecsInSec + (currentTick.tv_usec - lastTick_.tv_usec);
  timePassedSinceLastTick = timePassedSinceLastTick / kNumMSInSec;
  timePassed_ += timePassedSinceLastTick;

  lastTick_ = currentTick;
  
  // If the animation has wrapped, reset the loop.
  if (timePassed_ > runningTime_) looped_ = true;
  while (runningTime_ > 0 && timePassed_ > runningTime_) timePassed_ -= runningTime_;
}
