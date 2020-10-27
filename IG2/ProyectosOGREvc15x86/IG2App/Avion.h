#pragma once
#include "AspasMolino.h"

class Avion
{
private:
	Ogre::SceneNode* mNode;
	Ogre::SceneNode* heliceNode1;
	Ogre::SceneNode* heliceNode2;
	Ogre::SceneNode* frenteNode;
	Ogre::SceneNode* pilotoNode;
	Ogre::SceneNode* alaINode;
	Ogre::SceneNode* alaDNode;
	Ogre::SceneNode* cuerpoNode;
	AspasMolino* helice1;
	AspasMolino* helice2;
	Ogre::SceneManager* mSM;
public:
	Avion(Ogre::SceneManager* mSM_):mSM(mSM_) {
		//inicializando los SceneNode
		mNode = mSM->getRootSceneNode()->createChildSceneNode("Avion");
		cuerpoNode = mSM->getSceneNode("Avion")->createChildSceneNode("cuerpo");
		alaDNode = mSM->getSceneNode("Avion")->createChildSceneNode("alaD");
		alaINode = mSM->getSceneNode("Avion")->createChildSceneNode("alaI");
		pilotoNode = mSM->getSceneNode("Avion")->createChildSceneNode("piloto");
		frenteNode = mSM->getSceneNode("Avion")->createChildSceneNode("frente");
		heliceNode1 = mSM->getSceneNode("Avion")->createChildSceneNode("helice1");
		heliceNode2 = mSM->getSceneNode("Avion")->createChildSceneNode("helice2");

		//creacion del avion
		Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
		frenteNode->attachObject(cil);

		Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
		cuerpoNode->attachObject(cuerpo);

		Ogre::Entity* alaizq = mSM->createEntity("cube.mesh");
		alaINode->attachObject(alaizq);
		Ogre::Entity* alader = mSM->createEntity("cube.mesh");
		alaDNode->attachObject(alader);

		Ogre::Entity* piloto = mSM->createEntity("ninja.mesh");
		pilotoNode->attachObject(piloto);

		helice1 = new AspasMolino(heliceNode1, 6,1);
		helice2 = new AspasMolino(heliceNode2, 6,2);

		alaINode->translate(-300, 0, 0);
		alaDNode->translate(300, 0, 0);
		alaINode->setScale(5, 0.2, 1.5);
		alaDNode->setScale(5, 0.2, 1.5);
		frenteNode->translate(0, 0, 100);
		frenteNode->pitch(Ogre::Degree(90.0));
		frenteNode->setScale(10, 1, 10);

		pilotoNode->yaw(Ogre::Degree(180));
		pilotoNode->translate(0, -50, 0);

		heliceNode1->setScale(0.3, 0.3, 0.3);
		heliceNode1->translate(-300, 0, 100);

		heliceNode2->setScale(0.3, 0.3, 0.3);
		heliceNode2->translate(300, 0, 100);

	}
	~Avion() {};
	void keyPressed() {
		heliceNode1->roll(Ogre::Degree(10));
		heliceNode2->roll(Ogre::Degree(10));
	};
};

