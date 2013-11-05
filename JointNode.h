// A node that will rotate the coordinate frame to approximate a 
// joint in the model. 
//
// Author:      Michael DiBernardo
//
// REFERENCES:
// 1. Angel, Edward. "Interactive Computer Graphics", third ed., 444-62. 
// 2. Foster, Garret. "Understanding and Implementing Scene Graphs."
//    Available online at http://www.gamedev.net/reference/programming/features/scenegraph/
#ifndef __JOINT_NODE_H__
#define __JOINT_NODE_H__

#include "SceneNode.h"
#include <string>
using std::string;

// Axis about which something is to be rotated -- sorry, this enum is horribly named
enum MotionType {ABOUT_X, ABOUT_Y, ABOUT_Z};

class JointNode : public SceneNode {
 public:

  // Creates a rotatable joint.
  //
  // The first three parameters describe the displacement from the previous link
  // in the hierarchy (parent) to the joint, and the second three parameters describe
  // the required displacement to the next link.
  //    
  //                 1st displacement
  //   parent link ------------------- O
  //                                   |
  //                                   |
  //                                   |  2nd displacement
  //                                   |
  //                                   |
  //                               child link
  JointNode(const string& id, double xToJoint, double yToJoint, double zToJoint, 
            double xFromJoint, double yFromJoint, double zFromJoint);

  // Purge the subtree rooted at this node, including this node.
  virtual ~JointNode();
  
  // Changes the angle of the joint in the given direction.
  void bend(double angle, MotionType direction);

  // Straighten the joint back to it's 'normal' conformation.
  //  --------O---------
  void straighten();

  // Apply this rotation, and then update child.
  virtual void render();

  // Add a child. This will cause an assertion to fail if more than one child
  // is added.
  virtual void addChild(SceneNode* child);

 private:
  // Angles about X, Y, Z respectively.
  double angle_[3];
      
  // coordinates of displacement vector from parent body part
  double displacementFromParent_[3];

  // coordinates of displacement vector to child body part
  double displacementToChild_[3];
};

#endif
