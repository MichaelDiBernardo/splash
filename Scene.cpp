#include "Scene.h"
#include <iostream>
#include <string>
using std::cerr;
using std::endl;
using std::string;
#include "os.h"
#include "CameraNode.h"
#include "Config.h"
#include "DinoNode.h"
#include "Engine.h"
#include "EnvironmentalLightNode.h"
#include "HUDNode.h"
#include "Level.h"
#include "Orientation.h"
#include "PropNodeFactory.h"
#include "PropNode.h"
#include "PropSpec.h"
#include "SceneNode.h"
#include "SettingNode.h"
#include "readtex.h"

//------------------------------------------------------------------------------
// Helper methods for construction: Implementation of Scene.h is below.
//------------------------------------------------------------------------------
void createTextureList(GLuint* texNames) {
  glGenTextures(3, texNames);

  glBindTexture(GL_TEXTURE_2D, texNames[0]);
  LoadRGBMipmaps(Config::OCEAN_FLOOR_TEXTURE, 3);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, texNames[1]);
  LoadRGBMipmaps(Config::WALL_TEXTURE, 1);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  // There used to be a third texture for the skybox but I couldn't make it
  // look nice so I quit... maybe next time.
}

void addNPCs(const vector<DinoState*>& npcs, SceneNode* node) {
  for (vector<DinoState*>::const_iterator it = npcs.begin();
       it != npcs.end();
       ++it) {
    DinoNode* npc = new DinoNode("NPC", **it);
    node->addChild(npc);
  }
}

void addProps(const list<PropSpec*>& props, const PropNodeFactory& factory, SceneNode* node) {
  for (list<PropSpec*>::const_iterator it = props.begin();
       it != props.end();
       ++it) {
    const PropSpec& p = **it;
    node->addChild(factory.createNodeFor(p));
  }
}

//------------------------------------------------------------------------------
// Implementation of Scene.h.
//------------------------------------------------------------------------------
Scene::Scene(const Engine& model, const Timer& startupTimer) {
  const Level& initialState = model.getCurrentLevel();

  // Create root.
  sceneGraphRoot_ = new EnvironmentalLightNode("ENVIRO_LIGHT", 
                                              initialState.getWidth()/2, 
                                              initialState.getHeight()/2);

  // Create player.
  DinoNode* player = new DinoNode("PLAYER_ROOT", initialState.getPCStateConst());


  // Toss camera into scene, with it watching the player.
  camera_ = new CameraNode("CAMERA", *player);
  camera_->addChild(player);
  
  sceneGraphRoot_->addChild(camera_);

  // Add NPCs to scene
  addNPCs(initialState.getNPCStatesConst(), camera_);

  // Create list of textures.
  GLuint texNames[3];
  createTextureList(texNames);

  // Factory for props.
  PropNodeFactory factory(texNames[0], texNames[1]);

  // Add props to scene.
  addProps(initialState.getPropsConst(), factory, camera_);

  // Add dots to scene.
  addProps(initialState.getDotsConst(), factory, camera_);
  
  // Add powerups to scene.
  addProps(initialState.getPowerupsConst(), factory, camera_);
  
  // Add the setting.
  camera_->addChild(new SettingNode("SETTING", 
                               initialState.getWidth(), 
                               initialState.getHeight(), 
                               texNames[0], 
                               texNames[2]));

  // Add the HUD.
  sceneGraphRoot_->addChild(new HUDNode("HUD", model, startupTimer));
}

Scene::~Scene() {
  // Blast the scene graph.
  delete sceneGraphRoot_;
}

void Scene::render() {
  sceneGraphRoot_->render();
  #ifdef __debug
  cerr << "Done rendering!!" << endl;
  #endif

}

void Scene::zoomIn() {
  camera_->zoomIn();
}

void Scene::liftCam() {
  camera_->raise();
}

void Scene::dropCam() {
  camera_->lower();
}

void Scene::zoomOut() {
  camera_->zoomOut();
}
