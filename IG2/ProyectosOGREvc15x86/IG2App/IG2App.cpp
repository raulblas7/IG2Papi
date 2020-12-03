#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <string>
#include "Molino.h"
#include "Avion.h"
#include "Plano.h"
#include "EntidadIG.h"
#include "Simbad.h"
#include "Boya.h"

using namespace std;
using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_h) {
	  //evento para que el segundero del reloj rote en sentido horario, descomentar aqui y la region reloj de la linea 138
	  /*mSecondsNode->translate(0, 100, 0, Ogre::Node::TS_LOCAL);
	  mSecondsNode->roll(Ogre::Degree(-3));
	  mSecondsNode->translate(0, -100, 0, Ogre::Node::TS_LOCAL);*/
  }
  else if (evt.keysym.sym == SDLK_j) {
	  //evento de movimiento de rotacion de la tierra alrededor del sol y de la luna alrededor de la tierra, descomentar aqui y region TierraySol linea 192
	  /*Tierra->translate(-350, 0, -350, Ogre::Node::TS_LOCAL);
	  Tierra->yaw(Ogre::Degree(-3));
	  Tierra->translate(350, 0, 350, Ogre::Node::TS_LOCAL);

	  Ficticio->yaw(Ogre::Degree(10))*/;
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
  delete avioncete; avioncete = nullptr;
  delete molinete; molinete = nullptr;
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
  vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));

  //CAMARA REFLEJO

  Camera* camRef = mSM->createCamera("CamRef");     // camara para hacer el reflejo
  camRef->setNearClipDistance(1);                   // mismo frustum y mismo nodo que la camara principal
  camRef->setFarClipDistance(10000);                // asi actualiza su posicion en funcion de como movamos la principal
  camRef->setAutoAspectRatio(true);

  mCamNode->attachObject(camRef);

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);
  // mCamMgr->setTarget(mSinbadNode);
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);
  //------------------------------------------------------------------------

  // without light we would just get a black screen 
  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(/*0.75*/ 1.0, /*0.75*/ 1.0,/* 0.75*/ 1.0);
  luz->setCastShadows(false);
  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
 // mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
  //sombras
 // mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
  //------------------------------------------------------------------------

  // finally something to render

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

  //mHoursNode->roll(Ogre::Degree(-90));

  /*mHoursNode->setScale(0.1, 1.5, 0.1);
  mMinuteNode->setScale(0.05, 2, 0.05);
  mSecondsNode->setScale(0.02, 2.0, 0.02);

  mSecondsNode->roll(Ogre::Degree(-45));

  mSecondsNode->translate(0, -100, 0, Ogre::Node::TS_LOCAL);*/

#pragma endregion

#pragma region Molino
 /* molinoNode = mSM->getRootSceneNode()->createChildSceneNode("molino");
  molinete = new Molino(6, molinoNode);
  addInputListener(molinete);
  EntidadIG::addListener(molinete);*/
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
	/*avionNode = mSM->getRootSceneNode()->createChildSceneNode("Avion");
	avioncete = new Avion(mSM, avionNode);*/
  //addInputListener(avioncete);
  //EntidadIG::addListener(avioncete);
#pragma endregion

#pragma region Apartado18-Plano
	/*planoNode = mSM->getRootSceneNode()->createChildSceneNode("plano");
	planete = new Plano(planoNode, 0);
	EntidadIG::addListener(planete);*/
#pragma endregion

#pragma region Apartado23

	//SkyPlane
	mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -80), "practicaGLSL/spaceGLSL", 1, 1, true, 1.0, 10, 10);

	//linea comentada para que el plano este a 200 de distancia y sin curvatura
	//mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -200), "IG2App/space", 1, 1, true, 0.0, 10, 10);

	//Planos
	planoNode = mSM->getRootSceneNode()->createChildSceneNode("plano");
	
	planete = new Plano(planoNode, 0);
	planete->getEntity()->setMaterialName("IG2App/reflejo");
	EntidadIG::addListener(planete);

	planete->setReflejo(camRef);


	planoMolNode = mSM->getRootSceneNode()->createChildSceneNode("planoMolino");

	planeteMolino = new Plano(planoMolNode, 1);
	planeteMolino->getEntity()->setMaterialName("Practica1/naranja");

	/*planoSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("planoSinbad");

	planeteSinbad = new Plano(planoSinbadNode, 2);
	planeteSinbad->getEntity()->setMaterialName("Practica1/rojo");*/

	planoMolNode->setScale(0.2, 0.2, 0.2);
	//planoSinbadNode->setScale(0.4, 0.4, 0.4);
	planoMolNode->translate(700, 20, -700);
	//planoSinbadNode->translate(-600, 20, 520);
	//Molino
	molinoNode = mSM->getRootSceneNode()->createChildSceneNode("molino");
	molinete = new Molino(6, molinoNode);
	addInputListener(molinete);
	EntidadIG::addListener(molinete);
	molinoNode->translate(700, -50, -700);
	molinoNode->setScale(0.8, 0.8, 0.8);
	//Sinbad
	mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	simbadete = new Simbad(mSinbadNode);
	addInputListener(simbadete);
	EntidadIG::addListener(simbadete);
	//Avion
	avionNode = mSM->getRootSceneNode()->createChildSceneNode("Avion");
	avioncete = new Avion(avionNode);
	addInputListener(avioncete);
	EntidadIG::addListener(avioncete);
	avionNode->translate(-1000, 900, 0);
	//cabeza
	cabezaNode = mSM->getRootSceneNode()->createChildSceneNode("Cabeza");
	Ogre::Entity* cabeza= mSM->createEntity("sphere.mesh");
	cabezaNode->attachObject(cabeza);
	cabeza->setMaterialName("Practica1/cabeza");
	cabezaNode->translate(805,-300,-550);
	cabezaNode->setScale(0.5, 0.5, 0.5);
	//Boya
	boyaNode = mSM->getRootSceneNode()->createChildSceneNode("Boya");
	boyete = new Boya(boyaNode);
	
	addInputListener(boyete);

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

