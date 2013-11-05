// A sequence of key frames and the operations required to interpolate
// and switch between these frames. Also operates as a slideshow when
// paused, to fulfill the requirements of the assignment.
//
// TODO: Refactor to use Timer
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// 1. Assignment spec.
// 2. Foster, Garret. "Understanding and Implementing Scene Graphs."
//    Available online at http://www.gamedev.net/reference/programming/features/scenegraph/
#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Basics.h"
#include "FrameSequence.h"
class Animation : public FrameSequence {
 public:
  // Create an animation from a sequence of keyframes specified in an animation file.
  Animation(const char* filename);

  virtual ~Animation();

  // Starts the animation. Once the animation is started, frames can be retrieved
  // using the getCurrentFrame() member.
  void start();

  // Starts the animation and instantaneously pauses it on the first keyframe. 
  void startPaused();

  // Pauses the animation. Any frames retrieved while paused will be the last frame
  // before animation was paused.
  //
  // The animation MUST BE started before this method is called. Otherwise, this
  // thing will blow up on you.
  void pause();

  // Unpauses the animation. 
  //
  // The animation MUST BE started before this method is called. Otherwise, this
  // thing will blow up on you.
  void unpause();

  // Returns true if the animation is currently paused, false otherwise. Animation
  // should be started for this to make sense.
  bool isPaused() const;

  virtual void nextFrame();

  // Gets the current frame as a list of real-numbered fields that can be used to
  // manipulate a model. Frame is produced as interpolated values between the
  // two closest key frames in time. Interpolation is linear.
  //
  // Animation MUST be started before you call this. If the animation is paused, it
  // will return the current keyframe as determined by the time that stuff was paused,
  // or by calls to 'nextFrame'.
  //
  // This does potentially change some internal state, so it cannot be labelled
  // as 'const'.
  virtual Frame getCurrentFrame();

  // Identifies whether this animation has looped or not.
  bool hasLooped() const;

private:
  bool started_;
  bool paused_;

  // Time that the current loop of animation has spent running in milliseconds.
  unsigned long timePassed_;

  // Last time a frame was retrieved from this animation.
  timeval lastTick_;

  // The running time of the animation loop in milliseconds.
  unsigned long runningTime_;

  // Has the animation looped.
  bool looped_;

  // Helper function to play with time difference stuff.
  void updateTime();

  DISALLOW_EVIL_CONSTRUCTORS(Animation);
};
#endif
