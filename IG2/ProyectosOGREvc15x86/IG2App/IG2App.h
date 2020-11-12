#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
class Avion;
class Molino;
class Plano;
class EntidadIG;
class Simbad;
class Boya;

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
  
  Avion* avioncete = nullptr;
  Molino* molinete = nullptr;
  Plano* planete = nullptr;
  Plano* planeteMolino = nullptr;
  Plano* planeteSinbad = nullptr;
  Simbad* simbadete = nullptr;
  Boya* boyete = nullptr;
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;
  Ogre::SceneNode* mBathNode = nullptr;
  Ogre::SceneNode* Tierra;
  Ogre::SceneNode* Sol;
  Ogre::SceneNode* Luna;
  Ogre::SceneNode* Ficticio;
  Ogre::SceneNode* mHourNode[12];
  Ogre::SceneNode* Clock;
  Ogre::SceneNode* Spheres;
  Ogre::SceneNode* mMinuteNode = nullptr;
  Ogre::SceneNode* mHoursNode = nullptr;
  Ogre::SceneNode* mSecondsNode = nullptr;
  Ogre::SceneNode* planoNode = nullptr;
  Ogre::SceneNode* planoMolNode = nullptr;
  Ogre::SceneNode* planoSinbadNode = nullptr;
  Ogre::SceneNode* molinoNode = nullptr;
  Ogre::SceneNode* avionNode = nullptr;
  Ogre::SceneNode* cabezaNode = nullptr;
  Ogre::SceneNode* boyaNode = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;
  
};

#endif
