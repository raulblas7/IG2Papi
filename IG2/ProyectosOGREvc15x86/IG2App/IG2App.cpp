#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <string>
#include "Molino.h"
#include "Avion.h"

using namespace std;
using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_g) {
	  molinete->keyPressed();
  }
  else if (evt.keysym.sym == SDLK_c) {
	  molinete->cilindroHaciaDentro();
  }
  else if (evt.keysym.sym == SDLK_h) {
	  //molinete->aspasRotando();
	  /*mSecondsNode->translate(0, 50, 50, Ogre::Node::TS_LOCAL);
	  mSecondsNode->roll(Ogre::Degree(-3));
	  mSecondsNode->translate(0, -50, -50, Ogre::Node::TS_LOCAL);*/
  }
  else if (evt.keysym.sym == SDLK_j) {
	  Tierra->translate(-350, 0, -350, Ogre::Node::TS_LOCAL);
	  Tierra->yaw(Ogre::Degree(-3));
	  Tierra->translate(350, 0, 350, Ogre::Node::TS_LOCAL);

	  Ficticio->yaw(Ogre::Degree(10));
  }

  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render
  //escenas sinbad y baño
#pragma region sinbadybaño
  /*Ogre::Entity* ent = mSM->createEntity("RomanBathLower.mesh");
  Ogre::Entity* ent1 = mSM->createEntity("RomanBathUpper.mesh");
  Ogre::Entity* ent2 = mSM->createEntity("Sinbad.mesh");
  Ogre::Entity* ent3 = mSM->createEntity("Columns.mesh");

  mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
  mBathNode = mSM->getRootSceneNode()->createChildSceneNode("nBath");
  mBathNode->attachObject(ent);
  mBathNode->attachObject(ent1);
  mBathNode->attachObject(ent3);
  mSinbadNode->attachObject(ent2);

  mSinbadNode->setScale(20, 20, 20);
  mSinbadNode->setPosition(0, 20, 0);*/
#pragma endregion

#pragma region reloj
  //Clock = mSM->getRootSceneNode()->createChildSceneNode("nClock");
  //Spheres = mSM->getSceneNode("nClock")->createChildSceneNode("nSpheres");
  //for (int i = 0; i < 12; i++) {
	 // Ogre::Entity* sph = mSM->createEntity("sphere.mesh");
	 // string n = "Hora " + to_string(i);
	 // mHourNode[i] = mSM->getSceneNode("nSpheres")->createChildSceneNode(n);
	 // mHourNode[i]->attachObject(sph);
  //}

  //float angle = 0;
  //float angleToAdd = 360 / 12;  //30 grados
  ////Distancia con la que se multiplica el seno y coseno
  //float distance = 250;
  //for (int i = 0; i < 12; i++) {
	 // //Se cambia la escala de las esferas
	 // mHourNode[i]->setScale(0.25, 0.25, 0.25);
	 // mHourNode[i]->setPosition(Ogre::Math::Cos(Ogre::Degree(angle)) * distance, Ogre::Math::Sin(Ogre::Degree(angle)) * distance, 0);
	 // angle += angleToAdd;
  //}
  //angle = 0;
  //for (int i = 0; i < 12; i += 2) {
	 // mSM->getSceneNode("Hora " + to_string(i))->setScale(0.1, 0.1, 0.1);
  //}

  //Ogre::Entity* h = mSM->createEntity("cube.mesh");
  //mHoursNode = mSM->getSceneNode("nClock")->createChildSceneNode("nHour");
  //Ogre::Entity* m = mSM->createEntity("cube.mesh");
  //mMinuteNode = mSM->getSceneNode("nClock")->createChildSceneNode("nMinute");
  //Ogre::Entity* s = mSM->createEntity("cube.mesh");
  //mSecondsNode = mSM->getSceneNode("nClock")->createChildSceneNode("nSeconds");

  //mHoursNode->attachObject(h);
  //mMinuteNode->attachObject(m);
  //mSecondsNode->attachObject(s);

  //mMinuteNode->translate(0, 100, 0);
  //mHoursNode->translate(60, 5, 0);
  //mSecondsNode->translate(-50, -50, 0);

  //mHoursNode->roll(Ogre::Degree(-90));
  //mSecondsNode->roll(Ogre::Degree(-45));

  //mHoursNode->setScale(0.1, 1.5, 0.1);
  //mMinuteNode->setScale(0.05, 2, 0.05);
  //mSecondsNode->setScale(0.02, 2.0, 0.02);

#pragma endregion

#pragma region Molino
  //molinete = new Molino(mSM, 6);

#pragma endregion

#pragma region TierraySol

	  /*Sol = mSM->getRootSceneNode()->createChildSceneNode("sol");
	  Tierra = mSM->getRootSceneNode()->createChildSceneNode("tierra");
	  Ficticio = mSM->getSceneNode("tierra")->createChildSceneNode("fict");
	  Luna = mSM->getSceneNode("fict")->createChildSceneNode("luna");


	   Ogre::Entity* solito = mSM->createEntity("sphere.mesh");
	   Sol->attachObject(solito);
	   Ogre::Entity* tierraplana = mSM->createEntity("sphere.mesh");
	   Tierra->attachObject(tierraplana);
	   Ogre::Entity* lunalunera = mSM->createEntity("sphere.mesh");
	   Luna->attachObject(lunalunera);

	   Sol->setScale(2, 2, 2);
	   Tierra->setScale(1, 1, 1);
	   Luna->setScale(0.3, 0.3, 0.3);
	   Tierra->translate(350, 0, 350);
	   Luna->translate(90, 0, 120);*/

#pragma endregion

#pragma region avion
	avioncete = new Avion(mSM);
#pragma endregion

  //mSinbadNode->setScale(20, 20, 20);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

