#pragma once
#include "AspasMolino.h"

class Molino
{
private:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* sphereNode = nullptr;
	Ogre::SceneNode* cilindroNode = nullptr;
	AspasMolino* aspas = nullptr;
	Ogre::SceneNode* aspasN;
	Ogre::SceneManager* mSM;
	
public:
	Molino(Ogre::SceneManager* mng, int asps) : mSM(mng) {
		mNode = mSM->getRootSceneNode()->createChildSceneNode("molino");
		aspasN = mSM->getSceneNode("molino")->createChildSceneNode("aspas");
		sphereNode = mSM->getSceneNode("molino")->createChildSceneNode("techo");
		cilindroNode = mSM->getSceneNode("molino")->createChildSceneNode("cuerpo");
		//creacion del molino
		aspas = new AspasMolino(aspasN, asps);
		Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
		cilindroNode->attachObject(cil);
		Ogre::Entity* tech = mSM->createEntity("sphere.mesh");
		sphereNode->attachObject(tech);
		//ajustes de tamaño y posicion
		cilindroNode->setScale(65.0, 120.0, 65.0);
		sphereNode->setScale(1.7, 1.7, 1.7);
		aspasN->translate(0, 300, 200);
		sphereNode->translate(0, 350, 0);
	}

	void keyPressed() {
		aspas->keyPressed();
	};

	void cilindroHaciaDentro() {
		aspas->cilindroHaciaDentro();
	};

	void aspasRotando() {
		aspas->aspasRotate();
	};
};

