#include "ChaserAgent.h"
#include <math.h>
#include "Config.h"
#include "DinoState.h"
#include "EngineInput.h"
#include "Level.h"
#include "Orientation.h"

ChaserAgent::ChaserAgent(const DinoState& target_, DinoState* slave)
  : target_(target_), controlled_(slave) {
}

ChaserAgent::~ChaserAgent() {
}

void ChaserAgent::control() {
  const Orientation& chaserO = controlled_->getOrientation();
  const Orientation& target_O = target_.getOrientation();

  // Find slave's direction vector.
  double curDirX = cos(chaserO.getAngle());
  double curDirY = sin(chaserO.getAngle());

  // Find direction to target_.
  double tDirX = target_O.getX() - chaserO.getX();
  double tDirY = target_O.getY() - chaserO.getY();

  // Take "cross product": If z component positve, we're to the right, so turn
  // left, and vice versa

  double normalZ = curDirX*tDirY - curDirY*tDirX;

  // Always gun it.
  controlled_ -> setMovingForward();
  controlled_ -> stopTurning();

  if (normalZ < 0) {
    controlled_->setTurningLeft();
  }
  else {
    controlled_->setTurningRight();
  }
}
