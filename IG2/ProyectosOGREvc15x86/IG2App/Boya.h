#pragma once
#include "EntidadIG.h"
#include <OgreEntity.h>

class Boya : public EntidadIG
{
private:
	Ogre::Entity* entBoya;
public:
	Boya(Ogre::SceneNode* node) : EntidadIG(node) {
		entBoya = mSM->createEntity("Barrel.mesh");
		entBoya->setMaterialName("Practica1/alas");
		mNode->attachObject(entBoya);
		mNode->scale(30, 30, 30);
		mNode->translate(0, -275, 0);
	}
	~Boya() {
		delete entBoya; entBoya = nullptr;
	}
};

