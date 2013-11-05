// A node that represents a single piece of geometry (a cone)
// that makes up a single decorative spike on our dinosaur.
//
// Note that this geometry is not drawn at a fixed coordinate. In order
// to place the ellipsoid somewhere in the world, a translation 
// must have first been done by a parent TranslationNode.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// 1. Angel, Edward. "Interactive Computer Graphics", third ed., 444-62. 
// 2. Foster, Garret. "Understanding and Implementing Scene Graphs."
//    Available online at http://www.gamedev.net/reference/programming/features/scenegraph/
#ifndef __SPIKE_NODE_H__
#define __SPIKE_NODE_H__

#include <string>
using std::string;

#include "Basics.h"
#include "SceneNode.h"

class ColorSpec;

enum SpikeOrientation { 
  SPIKE_VERTICAL, 
  SPIKE_HORIZONTAL,
  SPIKE_DIAG_LEFT, 
  SPIKE_DIAG_RIGHT 
};

class SpikeNode : public SceneNode {
 public:
  // Creates a spike with the given dimension and colour values.
  SpikeNode(const string& id, double base, double height, SpikeOrientation o, const ColorSpec* c);

  // Purge the subtree rooted at this node, including this node.
  virtual ~SpikeNode();

  // Draw this node, and then update all of its children. 
  virtual void render();

  static const int NUM_SLICES = 10;
  static const int NUM_STACKS = 10;

 private:
  // Width of the base of the spike cone.
  double base_;
  // Height of the spike cone.
  double height_;
  // Orientation of the spike.
  SpikeOrientation o_;
  // Color of the spike.
  const ColorSpec* myC_;

  DISALLOW_EVIL_CONSTRUCTORS(SpikeNode);
};

#endif
