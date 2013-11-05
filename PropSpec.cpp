#include "PropSpec.h"
#include "os.h"
#include "Orientation.h"
#include "Config.h"

PropSpec::PropSpec(int id, PropType p, double xPos, double yPos, double xDim, double yDim)
  : myID_(id), myType_(p), myXPos_(xPos), myYPos_(yPos), myXDim_(xDim), myYDim_(yDim), active_(true) {
}

PropSpec::~PropSpec() {
}

int PropSpec::getID() const {
  return myID_;
}

PropType PropSpec::getType() const {
  return myType_;
}

double PropSpec::getXPos() const {
  return myXPos_;
}

double PropSpec::getYPos() const {
  return myYPos_;
}

double PropSpec::getXDim() const {
  return myXDim_;
}

double PropSpec::getYDim() const {
  return myYDim_;
}

bool PropSpec::contains(const Orientation& o) const {
  double x = o.getX();
  double y = o.getY();

  double txDim, tyDim;
  if(myType_ == BOX_PROP) {    
    txDim = myXDim_/2 + Config::BOX_OFFSET;
    tyDim = myYDim_/2 + Config::BOX_OFFSET;
  }
  else if (myType_ == DOT_PROP) {
    txDim = myXDim_*6;
    tyDim = myYDim_*6;
  }
  else {
    txDim = myXDim_;
    tyDim = myYDim_;
  }

  if ( (myXPos_ - txDim) < x && x < (myXPos_ + txDim) &&
       (myYPos_ - tyDim) < y && y < (myYPos_ + tyDim))
    return true;
  else
    return false;
}

Orientation PropSpec::clip(const Orientation& toClip) const {
  double txDim, tyDim;
  if (myType_ == BOX_PROP) {    
    txDim = myXDim_/2 + Config::BOX_OFFSET;
    tyDim = myYDim_/2 + Config::BOX_OFFSET;
  }
  else {
    txDim = myXDim_;
    tyDim = myYDim_;
  }

  double leftDist = toClip.getX() - (myXPos_ - txDim);
  double rightDist =  (myXPos_ + txDim) - toClip.getX();
  double botDist = toClip.getY() - (myYPos_ - tyDim);
  double topDist = (myYPos_ + tyDim) - toClip.getY();

  Orientation newO(toClip);
  if (leftDist < rightDist && leftDist < botDist && leftDist < topDist)
    newO.setX(myXPos_ - txDim);
  else if (rightDist < leftDist && rightDist < botDist && rightDist < topDist)
    newO.setX(myXPos_ + txDim);
  else if (botDist < leftDist && botDist < rightDist && botDist < topDist)
    newO.setY(myYPos_ - tyDim);
  else
    newO.setY(myYPos_ + tyDim);

  return newO;
}

void PropSpec::setActive(bool flag) {
  active_ = flag;
}

bool PropSpec::isActive() const {
  return active_;
}
