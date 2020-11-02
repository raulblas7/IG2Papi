#pragma once
#include "AspasMolino.h"

class Molino : public EntidadIG
{
private:
	//Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* sphereNode = nullptr;
	Ogre::SceneNode* cilindroNode = nullptr;
	Ogre::SceneNode* padreFicticio = nullptr;
	AspasMolino* aspas = nullptr;
	Ogre::SceneNode* aspasN;
	//Ogre::SceneManager* mSM;
	
public:
	Molino(int asps, Ogre::SceneNode* mNode) : EntidadIG(mNode) {

		//aspasN = mSM->getSceneNode("molino")->createChildSceneNode("aspas");
		sphereNode = mSM->getSceneNode("molino")->createChildSceneNode("techo");
		cilindroNode = mSM->getSceneNode("molino")->createChildSceneNode("cuerpo");

		padreFicticio = mSM->getSceneNode("techo")->createChildSceneNode("ficticio");
		aspasN = mSM->getSceneNode("ficticio")->createChildSceneNode("aspas");
	

		//creacion del molino
		aspas = new AspasMolino(aspasN, asps);
		Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
		cilindroNode->attachObject(cil);
		Ogre::Entity* tech = mSM->createEntity("sphere.mesh");
		sphereNode->attachObject(tech);
		//ajustes de tamaño y posicion
		cilindroNode->setScale(65.0, 120.0, 65.0);
		sphereNode->setScale(1.7, 1.7, 1.7);
		aspasN->setScale(0.8, 0.8, 0.8);
		aspasN->translate(0, 0, 100);
		sphereNode->translate(0, 350, 0);
	}
	~Molino() { delete aspas; aspas = nullptr; };

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override {
		if (evt.keysym.sym == SDLK_h) {
			aspasRotando();
		}
		else {
			aspas->keyPressed(evt);
		}
		return true;
	};

	void aspasRotando() {
		//usando padreficticio
		padreFicticio->yaw(Ogre::Degree(3));
	};
};

