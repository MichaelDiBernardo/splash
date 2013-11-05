// A node that represents a single piece of geometry (an ellipsoid)
// that makes up a single 'part' or 'link' of our dinosaur.
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
#ifndef __BODY_PART_NODE_H__
#define __BODY_PART_NODE_H__

#include "Basics.h"
#include "SceneNode.h"
class ColorSpec;

class BodyPartNode : public SceneNode {
 public:
  // Creates an ellipsoid with the given radii and colour values.
  BodyPartNode(const string& id, double xRadius, double yRadius, double zRadius, 
               const ColorSpec* c);

  // Purge the subtree rooted at this node, including this node.
  virtual ~BodyPartNode();

  // Draw this node, and then update all of its children. 
  //
  // NOTE:
  // This is my equivalent to the drawEllipsoid() function that was
  // outlined in the assignment spec. 
  virtual void render();

  // Number of slices and stacks that form the body part ellipsoids.
  static const int NUM_SLICES = 20;
  static const int NUM_STACKS = 20;

 private:
  // Dimensions and color of the part.
  double xrad_;
  double yrad_;
  double zrad_;
  const ColorSpec* myC_;

  DISALLOW_EVIL_CONSTRUCTORS(BodyPartNode);
};

#endif
