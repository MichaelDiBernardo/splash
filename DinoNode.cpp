#include "DinoNode.h"
#include <math.h>
#include "Animation.h"
#include "AquaDino.h"
#include "BodyPartNode.h"
#include "Config.h"
#include "DinoState.h"
#include "Frame.h"
#include "JointNode.h"
#include "Orientation.h"
#include "SceneNode.h"
#include "SpikeNode.h"
#include "TranslationNode.h"
#include "os.h"

DinoNode::DinoNode(const string& id, const DinoState& myState) 
  : SceneNode(id), state_(myState) {
  dinoRoot_ = buildDino();
  mf_ = new Animation("mf.txt"); mf_->startPaused();
  mb_ = new Animation("mb.txt"); mb_->startPaused();
  tr_ = new Animation("tr.txt"); tr_->startPaused();
  tl_ = new Animation("tl.txt"); tl_->startPaused();
  currentAnimation_ = NULL;
}

DinoNode::~DinoNode() {
  delete mf_;
  delete mb_;
  delete tr_;
  delete tl_;
}

const Orientation& DinoNode::getOrientation() const {
  return state_.getOrientation();
}

void DinoNode::render() {
  // Dino is reverse of how we want him facing when he's built, so
  // we turn him 180. Then we have to figure out how to turn him so that
  // he's facing the right way based on orientation.
  const Orientation& o = state_.getOrientation();

  // Orientation angles are in radians (durnit).
  double aInDegrees = (o.getAngle() / M_PI) * 180;
  double degreesToTurn = 180 - aInDegrees;

  glPushMatrix();
  glTranslated(o.getX(), 0, o.getY());
  glRotated(degreesToTurn, 0, 1, 0);
  glScaled(0.025, 0.025, 0.025);

  animate();

  dinoRoot_->render();

  glPopMatrix();
  SceneNode::render();
}

void DinoNode::animate() {
  //if we're moving, the motion animations get priority
  if (state_.getMotionState() != NOT_ACCELERATING) {
    if (state_.getMotionState() == ACCELERATING_FORWARD && 
        currentAnimation_ != mf_) {
      if (currentAnimation_ != NULL) currentAnimation_->pause(); 
      currentAnimation_ = mf_; 
      mf_->unpause();
    }
    else if (state_.getMotionState() == ACCELERATING_BACKWARD &&
           currentAnimation_ != mb_) {
      if (currentAnimation_ != NULL) currentAnimation_->pause();
      currentAnimation_ = mb_; mb_->unpause();
    }
    // All other cases, we were already using the right animation.
  } else if (state_.getTurningState() != NOT_TURNING) {
    if (state_.getTurningState() == TURNING_LEFT && 
        currentAnimation_ != tl_) {
      if (currentAnimation_ != NULL) currentAnimation_->pause();
      currentAnimation_ = tl_; tl_->unpause();
    } else if (state_.getTurningState() == TURNING_RIGHT && 
               currentAnimation_ != tr_) {
      if (currentAnimation_ != NULL) currentAnimation_->pause(); 
        currentAnimation_ = tr_;  tr_->unpause();
    }
  } else {
    // We're not moving and not turning. We should not be animating.
    if (currentAnimation_ != NULL) currentAnimation_->pause();
    currentAnimation_ = NULL;
  }

  if (currentAnimation_ == NULL) {
    for (int i = 0; i < AQUA_DINO_NUM_JOINTS; ++i) joints_[i]->straighten();
  } else {
    const Frame& f = currentAnimation_->getCurrentFrame();
    const double* params = f.getFields();

    joints_[J_NECK_1]    ->  bend(params[P_NECK_1_SEG_UP_DOWN], ABOUT_Z);
    joints_[J_NECK_1]    ->  bend(params[P_NECK_1_SEG_LEFT_RIGHT], ABOUT_Y);
    joints_[J_NECK_1]    ->  bend(params[P_NECK_1_SEG_MED_LAT], ABOUT_X);
    joints_[J_NECK_2]    ->  bend(params[P_NECK_2_SEG_UP_DOWN], ABOUT_Z);
    joints_[J_NECK_2]    ->  bend(params[P_NECK_2_SEG_LEFT_RIGHT], ABOUT_Y);
    joints_[J_NECK_2]    ->  bend(params[P_NECK_2_SEG_MED_LAT], ABOUT_X);
    joints_[J_NECK_3]    ->  bend(params[P_NECK_3_SEG_UP_DOWN], ABOUT_Z);
    joints_[J_NECK_3]    ->  bend(params[P_NECK_3_SEG_LEFT_RIGHT], ABOUT_Y);
    joints_[J_NECK_3]    ->  bend(params[P_NECK_3_SEG_MED_LAT], ABOUT_X);
    joints_[J_HEAD]      ->  bend(params[P_HEAD_UP_DOWN], ABOUT_Z);
    joints_[J_HEAD]      ->  bend(params[P_HEAD_LEFT_RIGHT], ABOUT_Y);
    joints_[J_TAIL_1]    ->  bend(params[P_TAIL_1_SEG_UP_DOWN], ABOUT_Z);
    joints_[J_TAIL_1]    ->  bend(params[P_TAIL_1_SEG_LEFT_RIGHT], ABOUT_Y);
    joints_[J_TAIL_1]    ->  bend(params[P_TAIL_1_SEG_TWIST], ABOUT_X);
    joints_[J_TAIL_2]    ->  bend(params[P_TAIL_2_SEG_UP_DOWN], ABOUT_Z);
    joints_[J_TAIL_2]    ->  bend(params[P_TAIL_2_SEG_LEFT_RIGHT], ABOUT_Y);
    joints_[J_TAIL_2]    ->  bend(params[P_TAIL_2_SEG_TWIST], ABOUT_X);
    joints_[J_TAIL_3]    ->  bend(params[P_TAIL_3_SEG_UP_DOWN], ABOUT_Z);
    joints_[J_TAIL_3]    ->  bend(params[P_TAIL_3_SEG_LEFT_RIGHT], ABOUT_Y);
    joints_[J_TAIL_3]    ->  bend(params[P_TAIL_3_SEG_TWIST], ABOUT_X);
    //back hips
    joints_[J_LEG_BL_1]  ->  bend(params[P_BL_HIP_UP_DOWN], ABOUT_X);
    joints_[J_LEG_BL_1]  ->  bend(params[P_BL_HIP_LEFT_RIGHT], ABOUT_Y);
    joints_[J_LEG_BL_1]  ->  bend(params[P_BL_HIP_TWIST], ABOUT_Z);
    joints_[J_LEG_BR_1]  ->  bend(params[P_BR_HIP_UP_DOWN], ABOUT_X);
    joints_[J_LEG_BR_1]  ->  bend(params[P_BR_HIP_LEFT_RIGHT], ABOUT_Y);
    joints_[J_LEG_BR_1]  ->  bend(params[P_BR_HIP_TWIST], ABOUT_Z);
    //back leg knees
    joints_[J_LEG_BL_2]  ->  bend(params[P_BL_KNEE_UP_DOWN], ABOUT_X);
    joints_[J_LEG_BL_2]  ->  bend(params[P_BL_KNEE_LEFT_RIGHT], ABOUT_Y);
    joints_[J_LEG_BL_2]  ->  bend(params[P_BL_KNEE_TWIST], ABOUT_Z);
    joints_[J_LEG_BR_2]  ->  bend(params[P_BR_KNEE_UP_DOWN], ABOUT_X);
    joints_[J_LEG_BR_2]  ->  bend(params[P_BR_KNEE_LEFT_RIGHT], ABOUT_Y);
    joints_[J_LEG_BR_2]  ->  bend(params[P_BR_KNEE_TWIST], ABOUT_Z);
    //front hips
    joints_[J_LEG_FL_1]  ->  bend(params[P_FL_HIP_UP_DOWN], ABOUT_X);
    joints_[J_LEG_FL_1]  ->  bend(params[P_FL_HIP_LEFT_RIGHT], ABOUT_Y);
    joints_[J_LEG_FL_1]  ->  bend(params[P_FL_HIP_TWIST], ABOUT_Z);
    joints_[J_LEG_FR_1]  ->  bend(params[P_FR_HIP_UP_DOWN], ABOUT_X);
    joints_[J_LEG_FR_1]  ->  bend(params[P_FR_HIP_LEFT_RIGHT], ABOUT_Y);
    joints_[J_LEG_FR_1]  ->  bend(params[P_FR_HIP_TWIST], ABOUT_Z);
    //front leg knees
    joints_[J_LEG_FL_2]  ->  bend(params[P_FL_KNEE_UP_DOWN], ABOUT_X);
    joints_[J_LEG_FL_2]  ->  bend(params[P_FL_KNEE_LEFT_RIGHT], ABOUT_Y);
    joints_[J_LEG_FL_2]  ->  bend(params[P_FL_KNEE_TWIST], ABOUT_Z);
    joints_[J_LEG_FR_2]  ->  bend(params[P_FR_KNEE_UP_DOWN], ABOUT_X);
    joints_[J_LEG_FR_2]  ->  bend(params[P_FR_KNEE_LEFT_RIGHT], ABOUT_Y);
    joints_[J_LEG_FR_2]  ->  bend(params[P_FR_KNEE_TWIST], ABOUT_Z);

    joints_[J_LEFT_EYE]  ->  bend(params[P_LEFT_EYE_UP_DOWN], ABOUT_Z);
    joints_[J_LEFT_EYE]  ->  bend(params[P_LEFT_EYE_LEFT_RIGHT], ABOUT_Y);

    joints_[J_RIGHT_EYE]  ->  bend(params[P_RIGHT_EYE_UP_DOWN], ABOUT_Z);
    joints_[J_RIGHT_EYE]  ->  bend(params[P_RIGHT_EYE_LEFT_RIGHT], ABOUT_Y);
  }
}

SceneNode* DinoNode::buildDino() {
  const ColorSpec* BODY_COLOR;
  const ColorSpec* HEAD_COLOR;
  const ColorSpec* SPIKE_COLOR;
  const ColorSpec* NECK_COLOR;
  const ColorSpec* TAIL_COLOR;
  const ColorSpec* LEG_COLOR;
  const ColorSpec* EYE_COLOR;
  const ColorSpec* PUPIL_COLOR;
  const ColorSpec* TONGUE_COLOR;

  if (state_.getType() == CHAR_PC) {
    BODY_COLOR = Config::PLAYER_BODY_COLOR;
    HEAD_COLOR = Config::PLAYER_HEAD_COLOR;
    SPIKE_COLOR = Config::PLAYER_SPIKE_COLOR;
    NECK_COLOR = Config::PLAYER_NECK_COLOR;
    TAIL_COLOR = Config::PLAYER_TAIL_COLOR;
    LEG_COLOR = Config::PLAYER_LEG_COLOR;
    EYE_COLOR = Config::PLAYER_EYE_COLOR;
    PUPIL_COLOR = Config::PLAYER_PUPIL_COLOR;
    TONGUE_COLOR = Config::PLAYER_TONGUE_COLOR;
  } else { 
    BODY_COLOR = Config::BOT_BODY_COLOR;
    HEAD_COLOR = Config::BOT_HEAD_COLOR;
    SPIKE_COLOR = Config::BOT_SPIKE_COLOR;
    NECK_COLOR = Config::BOT_NECK_COLOR;
    TAIL_COLOR = Config::BOT_TAIL_COLOR;
    LEG_COLOR = Config::BOT_LEG_COLOR;
    EYE_COLOR = Config::BOT_EYE_COLOR;
    PUPIL_COLOR = Config::BOT_PUPIL_COLOR;
    TONGUE_COLOR = Config::BOT_TONGUE_COLOR;
  }

  // Build neck and head 
  JointNode* neck1J = new JointNode("neck1J", -10, 0, 0, 0, 4, 0);
  BodyPartNode* neck1 = new BodyPartNode("neck1", 2, 4, 2, NECK_COLOR);
  TranslationNode* neck1Up = new TranslationNode("neck1UpT", 0, 1, 0);
  TranslationNode* neck1Down = new TranslationNode("neck1DownT", 0, -1, 0);
  SpikeNode* neckSpike = new SpikeNode("neckSpike", 1.5, 3, SPIKE_HORIZONTAL, SPIKE_COLOR);

  JointNode* neck2J = new JointNode("neck2J", 0, 4, 0, 0, 4, 0);
  BodyPartNode* neck2 = new BodyPartNode("neck2", 1.75, 4, 2, NECK_COLOR);

  JointNode* neck3J = new JointNode("neck3J", 0, 4, 0, 0, 4, 0);
  BodyPartNode* neck3 = new BodyPartNode("neck3", 1.5, 4, 2, NECK_COLOR);

  JointNode* headJ = new JointNode("headJ", 0, 5.5, 0, -2.5, 0, 0);
  BodyPartNode* head = new BodyPartNode("head", 4, 3, 3, HEAD_COLOR);
  SpikeNode* leftHeadSpike = new SpikeNode("leftHeadSpike", 1.5, 7, SPIKE_DIAG_LEFT, SPIKE_COLOR);
  SpikeNode* rightHeadSpike = new SpikeNode("rightHeadSpike", 1.5, 6, SPIKE_DIAG_RIGHT, SPIKE_COLOR);

  JointNode* leftEyeJ = new JointNode("leftEyeJ", -1, 1.5,  1.8, 0, 0, 0);
  BodyPartNode* leftEye = new BodyPartNode("leftEye", 1, 1, 1, EYE_COLOR);
  BodyPartNode* leftPupil = new BodyPartNode("leftPupil", 0.5, 0.5, 0.5, PUPIL_COLOR);
  TranslationNode* leftPupilT = new TranslationNode("leftPupilT", -0.5, 0.5,  0.5);

  JointNode* rightEyeJ = new JointNode("rightEyeJ", -1, 1.5, -1.8, 0, 0, 0);
  BodyPartNode* rightEye = new BodyPartNode("rightEye", 1, 1, 1, EYE_COLOR);
  BodyPartNode* rightPupil = new BodyPartNode("rightPupil", 0.5, 0.5, 0.5, PUPIL_COLOR);
  TranslationNode* rightPupilT = new TranslationNode("rightPupilT", -0.5, 0.5, -0.5);

  TranslationNode* tongueT = new TranslationNode("tongueT", -4, -1, 0); 
  BodyPartNode* tongue = new BodyPartNode("tongue", 1, 0.15, 1, TONGUE_COLOR);

  neck1J->addChild(neck1);
  neck1->addChild(neck2J);
  neck2J->addChild(neck2);
  neck2->addChild(neck3J);
  neck3J->addChild(neck3);
  neck3->addChild(headJ);
  headJ->addChild(head);
  head->addChild(leftHeadSpike);
  head->addChild(rightHeadSpike);
  head->addChild(leftEyeJ);
  leftEyeJ->addChild(leftEye);
  leftEye->addChild(leftPupilT);
  leftPupilT->addChild(leftPupil);
  head->addChild(rightEyeJ);
  rightEyeJ->addChild(rightEye);
  rightEye->addChild(rightPupilT);
  rightPupilT->addChild(rightPupil);

  head->addChild(tongueT);
  tongueT->addChild(tongue);

  // spikes on neck
  neck1->addChild(neck1Up);
  neck1Up->addChild(neckSpike);
  neck1->addChild(neck1Down);
  neck1Down->addChild(neckSpike);

  neck2->addChild(neck1Up);
  neck2->addChild(neck1Down);

  neck3->addChild(neck1Up);
  neck3->addChild(neck1Down);

  // build tail
  JointNode* tail1J = new JointNode("tail1J", 9, 0, 0, 3, 0, 0);
  BodyPartNode* tail1 = new BodyPartNode("tail1", 3, 1.5, 3.5, TAIL_COLOR);
  SpikeNode* tailSpike1 = new SpikeNode("tailSpike1", 1, 3, SPIKE_VERTICAL, SPIKE_COLOR);

  JointNode* tail2J = new JointNode("tail2J", 3, 0, 0, 2, 0, 0);
  BodyPartNode* tail2 = new BodyPartNode("tail2", 2, 1.25, 2.5, TAIL_COLOR);
  SpikeNode* tailSpike2 = new SpikeNode("tailSpike2", 0.75, 2.5, SPIKE_VERTICAL, SPIKE_COLOR);

  JointNode* tail3J = new JointNode("tail3J", 2, 0, 0, 1.5, 0, 0);
  BodyPartNode* tail3 = new BodyPartNode("tail3", 1.5, 1.0, 1.5, TAIL_COLOR);
  SpikeNode* tailSpike3 = new SpikeNode("tailSpike3", 0.5, 2, SPIKE_VERTICAL, SPIKE_COLOR);

  tail1J->addChild(tail1);
  tail1->addChild(tail2J);
  tail1->addChild(tailSpike1);
  tail2J->addChild(tail2);
  tail2->addChild(tail3J);
  tail2->addChild(tailSpike2);
  tail3J->addChild(tail3);
  tail3->addChild(tailSpike3);


  // build legs
  JointNode* legBL1J   = new JointNode("legBL1J", 7, -2, 4.0, 0, 0, 1.5);
  BodyPartNode* legBL1 = new BodyPartNode("legBL1", 1.5, 1.0, 1.5, LEG_COLOR);
  JointNode* legBL2J   = new JointNode("legBL2J", 0, 0, 1.5, 0, 0, 4);
  BodyPartNode* legBL2 = new BodyPartNode("legBL2", 2.5, 1.0, 4, LEG_COLOR);

  JointNode* legBR1J   = new JointNode("legBR1J", 7, -2, -4.0, 0, 0, -1.5);
  BodyPartNode* legBR1 = new BodyPartNode("leg1BR", 1.5, 1.0, 1.5, LEG_COLOR);
  JointNode* legBR2J   = new JointNode("legBR2J", 0, 0, -1.5, 0, 0, -4);
  BodyPartNode* legBR2 = new BodyPartNode("legBR2", 2.5, 1.0, 4, LEG_COLOR);

  JointNode* legFL1J   = new JointNode("legFL1J", -7, -2, 4.0, 0, 0, 1.5);
  BodyPartNode* legFL1 = new BodyPartNode("legFL1", 1.5, 1.0, 1.5, LEG_COLOR);
  JointNode* legFL2J   = new JointNode("legFL2J", 0, 0, 1.5, 0, 0, 4);
  BodyPartNode* legFL2 = new BodyPartNode("legFL2", 2.5, 1.0, 4, LEG_COLOR);

  JointNode* legFR1J   = new JointNode("legFR1J", -7, -2, -4.0, 0, 0, -1.5);
  BodyPartNode* legFR1 = new BodyPartNode("leg1FR", 1.5, 1.0, 1.5, LEG_COLOR);
  JointNode* legFR2J   = new JointNode("legFR2J", 0, 0, -1.5, 0, 0, -4);
  BodyPartNode* legFR2 = new BodyPartNode("legFR2", 2.5, 1.0, 4, LEG_COLOR);

  legBL1J->addChild(legBL1);
  legBL1->addChild(legBL2J);
  legBL2J->addChild(legBL2);

  legBR1J->addChild(legBR1);
  legBR1->addChild(legBR2J);
  legBR2J->addChild(legBR2);

  legFL1J->addChild(legFL1);
  legFL1->addChild(legFL2J);
  legFL2J->addChild(legFL2);

  legFR1J->addChild(legFR1);
  legFR1->addChild(legFR2J);
  legFR2J->addChild(legFR2);


  // build body
  TranslationNode* bodyT = new TranslationNode("bodyT", 0, 0, 0);
  BodyPartNode* body = new BodyPartNode("body", 10, 4, 6, BODY_COLOR);

  SpikeNode* bodySpike = new SpikeNode("bodySpike", 3, 10, SPIKE_VERTICAL, SPIKE_COLOR);

  // TREMENDOUS HACK: Rotation of the entire dino is facilitated by rotating the torso before
  // the rest of the hierarchy is rendered, so we create a "joint" about the centre of the body
  // that has no incoming or outgoing limb. 

  JointNode* bodyJ = new JointNode("bodyJ", 0, 0, 0, 0, 0, 0);

  // Attach all parts to body
  bodyT->addChild(bodyJ);
  bodyJ->addChild(body);

  body->addChild(neck1J);
  body->addChild(tail1J);
  body->addChild(legBL1J);
  body->addChild(legFL1J);
  body->addChild(legBR1J);
  body->addChild(legFR1J);
  body->addChild(bodySpike);

  // Fill joint array
  joints_[J_NECK_1]   = neck1J;
  joints_[J_NECK_2]   = neck2J;
  joints_[J_NECK_3]   = neck3J;
  joints_[J_HEAD]     = headJ;
  joints_[J_TAIL_1]   = tail1J;
  joints_[J_TAIL_2]   = tail2J;
  joints_[J_TAIL_3]   = tail3J;
  joints_[J_LEG_BL_1] = legBL1J;
  joints_[J_LEG_BL_2] = legBL2J;
  joints_[J_LEG_BR_1] = legBR1J;
  joints_[J_LEG_BR_2] = legBR2J;
  joints_[J_LEG_FL_1] = legFL1J;
  joints_[J_LEG_FL_2] = legFL2J;
  joints_[J_LEG_FR_1] = legFR1J;
  joints_[J_LEG_FR_2] = legFR2J;
  joints_[J_BODY]     = bodyJ;
  joints_[J_LEFT_EYE] = leftEyeJ;
  joints_[J_RIGHT_EYE] = rightEyeJ;

  return bodyT;
}
