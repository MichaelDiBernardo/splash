#include "FrameSequence.h"
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

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std; // Wince

#include "Frame.h"
FrameSequence::FrameSequence(const char *filename) : currentFrame_(0) {
  ifstream fp(filename);
  if (!fp.is_open())  {
    cerr << "File " << filename << " could not be opened." << endl;
    exit(-1);
  }

  const int kNumCharsToIgnoreOnComment = 65536;
  while(!fp.eof()) {
    if (fp.peek() == SEQUENCE_FILE_COMMENT_CHARACTER) 
      fp.ignore(kNumCharsToIgnoreOnComment, '\n');
    frames_.push_back(new Frame(&fp));
  }
  fp.close();
}

FrameSequence::~FrameSequence() {
}

void FrameSequence::nextFrame() {
  currentFrame_ = (currentFrame_ + 1) % frames_.size();
}

const Frame& FrameSequence::getCurrentFrame() const {
    return *(frames_[currentFrame_]);
}

void FrameSequence::fastForwardTo(unsigned long t) {
  unsigned int index;
  for (index = 0; index < frames_.size(); index++) {
    if (frames_[index]->getTimeInMS() > t)  
      break;
  }
  currentFrame_ = index % frames_.size();
}

unsigned int FrameSequence::getNumFrames() const {
  return frames_.size();
}
