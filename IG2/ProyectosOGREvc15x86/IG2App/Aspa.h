#pragma once
#include "EntidadIG.h"
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>

class Aspa : public EntidadIG
{
private:
	//Ogre::SceneNode* aspaNode;
	Ogre::SceneNode* tableroNode;
	Ogre::SceneNode* cilindroNode;
	Ogre::SceneManager* mSM;
public:
	Aspa(Ogre::SceneNode* aspaNode_, Ogre::SceneNode* tableroNode_, Ogre::SceneNode* cilindroNode_) : EntidadIG(aspaNode_),
		tableroNode(tableroNode_), cilindroNode(cilindroNode_) {
		mSM = mNode->getCreator();
		Ogre::Entity* tab = mSM->createEntity("cube.mesh");
		Ogre::Entity* ador = mSM->createEntity("Barrel.mesh");
		tableroNode->attachObject(tab);
		cilindroNode->attachObject(ador);
		tableroNode->setScale(5.0, 0.8, 0.1);
		cilindroNode->setScale(3.0, 5.0, 3.0);
	};
	Ogre::SceneNode* getTablero() { return tableroNode; };
	Ogre::SceneNode* getAdorno() { return cilindroNode; };
};

