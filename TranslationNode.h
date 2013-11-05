// A node that will shift the coordinate frame for all child geometry
// nodes that are drawn below it.
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// 1. Angel, Edward. "Interactive Computer Graphics", third ed., 444-62. 
// 2. Foster, Garret. "Understanding and Implementing Scene Graphs."
//    Available online at http://www.gamedev.net/reference/programming/features/scenegraph/
#ifndef __TRANSLATION_NODE_H__
#define __TRANSLATION_NODE_H__

#include <string>
using std::string;

#include "Basics.h"
#include "SceneNode.h"

class TranslationNode : public SceneNode {
 public:
  // Creates a translation of given magnitude.
  TranslationNode(const string& id, double xDisplacement, double yDisplacement, double zDisplacement);

  // Purge the subtree rooted at this node, including this node.
  virtual ~TranslationNode();

  // Sets the translation to be applied by this node.
  void setTranslation(double xDisplacement, double yDisplacement, double zDisplacement);

  // Gets the X component of this translation.
  double getX() const;

  // Gets the Y component of this translation.
  double getY() const;

  // Gets the Z component of this translation.
  double getZ() const;

  // Apply this translation, and then update all of its children. 
  virtual void render();

 private:
  double xdis_;
  double ydis_;
  double zdis_;

  DISALLOW_EVIL_CONSTRUCTORS(TranslationNode);
};

#endif
