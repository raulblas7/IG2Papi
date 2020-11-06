#pragma once

#include "EntidadIG.h"
#include <OgreEntity.h>

class Simbad:public EntidadIG
{
public:
	Simbad(Ogre::SceneNode* node) : EntidadIG(node) {
		Ogre::Entity* entSin = mSM->createEntity("Sinbad.mesh");
		mNode->attachObject(entSin);
		mNode->scale(30, 30, 30);
		mNode->translate(-600, -200, 600);
	}
};

