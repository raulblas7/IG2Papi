#pragma once
#include "AspasMolino.h"

class Molino
{
private:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* sphereNode = nullptr;
	Ogre::SceneNode* cilindroNode = nullptr;
	Ogre::SceneNode* padreFicticio = nullptr;
	AspasMolino* aspas = nullptr;
	Ogre::SceneNode* aspasN;
	Ogre::SceneManager* mSM;
	
public:
	Molino(Ogre::SceneManager* mng, int asps) : mSM(mng) {
		mNode = mSM->getRootSceneNode()->createChildSceneNode("molino");

		//comentar esta primera linea de aspasN = ... si queremos hacer la rotacion ficticia y descomentar las lineas 25 y 26
		aspasN = mSM->getSceneNode("molino")->createChildSceneNode("aspas");
		sphereNode = mSM->getSceneNode("molino")->createChildSceneNode("techo");
		cilindroNode = mSM->getSceneNode("molino")->createChildSceneNode("cuerpo");

		//uso de padre ficticio para rotacion usando nodo ficticio descomentar aqui y en aspasRotando para probar rotacion usando ficticio
		/*padreFicticio = mSM->getSceneNode("techo")->createChildSceneNode("ficticio");
		aspasN = mSM->getSceneNode("ficticio")->createChildSceneNode("aspas");*/
	

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
		aspasN->translate(0, 350, 180);
		sphereNode->translate(0, 350, 0);
	}

	void keyPressed() {
		aspas->keyPressed();
	};

	void cilindroHaciaDentro() {
		aspas->cilindroHaciaDentro();
	};

	void aspasRotando() {
		//usando padreficticio
		//padreFicticio->yaw(Ogre::Degree(3));

		//usando truco
		aspasN->translate(0, -350, -180, Ogre::Node::TS_LOCAL);
		aspasN->yaw(Ogre::Degree(3));
		aspasN->translate(0, 350, 180, Ogre::Node::TS_LOCAL);
	};
};

