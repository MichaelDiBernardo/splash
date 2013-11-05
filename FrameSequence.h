// A sequence of key frames that can be iterated through like a 
// slideshow.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
//  None.
#ifndef __FRAME_SEQUENCE_H__
#define __FRAME_SEQUENCE_H__

#include <vector>
using std::vector;
#include "Basics.h"

class Frame;

class FrameSequence {
 public:
  // Create a frame sequence from a sequence of keyframes specified in a sequence file.
  // Initializes the current frame to the first frame in the given sequence file.
  explicit FrameSequence(const char* filename);

  // Destructor. Does nothing for now.
  virtual ~FrameSequence();

  // Advances to the next frame in the sequence. If this is called when the current
  // frame is the last frame in the sequence, the next frame will be the first in the
  // sequence (ie this call 'wraps around' if the end of the sequence is reached).
  virtual void nextFrame();

  // Gets the current frame as a list of real-numbered fields that can be used to
  // manipulate a model. Frame is produced as interpolated values between the
  // two closest key frames in time. Interpolation is linear.
  //
  // If this is called before the animation is started, it will return the first
  // keyframe.
  //
  // If there is only one frame in the given animation, will return just that frame.
  virtual const Frame& getCurrentFrame() const;

  // 'Fast forwards' the slideshow to the frame that occurs at the given time in MS.
  // If there is no frame that occurs at exactly this time, returns the frame that
  // occurs right after it.
  void fastForwardTo(unsigned long timeInMS);

  // Returns the number of frames in the sequence.
  virtual unsigned int getNumFrames() const;

  // Character used for comments in sequence file.
  static const char SEQUENCE_FILE_COMMENT_CHARACTER = '#';

 protected:
  // Keyframes in animation.
  vector<Frame*> frames_;

 private:
  // The current frame that we're on.
  unsigned int currentFrame_;

  DISALLOW_EVIL_CONSTRUCTORS(FrameSequence);
};
#endif
