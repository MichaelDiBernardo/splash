#include "SceneNode.h"
#include <iostream>
using std::cerr;
using std::endl;

SceneNode::SceneNode(const string& id_) : id_(id_) {
#ifdef __debug
  cerr << "CONSTRUCTED: \t" << id_ << endl;
#endif
}

SceneNode::~SceneNode() {
  STLDeleteContainerPointers(children_.begin(), children_.end());

  children_.clear();

  #ifdef __debug
  cerr << "DESTROYED: \t" << id_ << endl;
  #endif
}

const string& SceneNode::getID() const {
  return id_;
}

void SceneNode::render() {
  #ifdef __debug
  cerr << "RENDERING: \t" << id_ << endl;
  #endif
  for (list<SceneNode*>::iterator it = children_.begin(); 
      it != children_.end(); 
      ++it) 
      (*it)->render();
}

void SceneNode::addChild(SceneNode* child) {
  children_.push_back(child);
}

int SceneNode::getNumChildren() const {
  return children_.size();
}
