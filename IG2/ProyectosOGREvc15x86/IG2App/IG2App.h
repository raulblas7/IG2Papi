#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
class Molino;

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
  
  Molino* molinete = nullptr;
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;
  Ogre::SceneNode* mBathNode = nullptr;
  Ogre::SceneNode* mHourNode[12];
  Ogre::SceneNode* Clock;
  Ogre::SceneNode* aspaNode;
  Ogre::SceneNode* aspasN;
  Ogre::SceneNode* aspas[12];
  Ogre::SceneNode* tableros[12];
  Ogre::SceneNode* adornos[12];
  Ogre::SceneNode* tableroNode;
  Ogre::SceneNode* cilindroNode;
  Ogre::SceneNode* Spheres;
  Ogre::SceneNode* mMinuteNode = nullptr;
  Ogre::SceneNode* mHoursNode = nullptr;
  Ogre::SceneNode* mSecondsNode = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;
  
};

#endif
