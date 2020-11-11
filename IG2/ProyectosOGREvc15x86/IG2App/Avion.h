#pragma once
#include "AspasMolino.h"

class Avion : public EntidadIG
{
private:
	//Ogre::SceneNode* mNode;
	Ogre::SceneNode* heliceNode1;
	Ogre::SceneNode* heliceNode2;
	Ogre::SceneNode* frenteNode;
	Ogre::SceneNode* pilotoNode;
	Ogre::SceneNode* alaINode;
	Ogre::SceneNode* alaDNode;
	Ogre::SceneNode* cuerpoNode;
	Ogre::SceneNode* luzNode;
	AspasMolino* helice1;
	AspasMolino* helice2;
	Ogre::Light* foco;
	bool moveAround = false;
	//Ogre::SceneManager* mSM;
public:
	Avion(Ogre::SceneNode* mNode): EntidadIG(mNode) {
		//inicializando los SceneNode
		cuerpoNode = mNode->createChildSceneNode("cuerpoav");
		alaDNode = mNode->createChildSceneNode("alaD");
		alaINode = mNode->createChildSceneNode("alaI");
		pilotoNode = mNode->createChildSceneNode("piloto");
		frenteNode = mNode->createChildSceneNode("frente");
		heliceNode1 = mNode->createChildSceneNode("helice1");
		heliceNode2 = mNode->createChildSceneNode("helice2");
		luzNode = mNode->createChildSceneNode("luzAvion");

		//creacion del avion
		Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
		cil->setMaterialName("Practica1/naranja");

		frenteNode->attachObject(cil);

		Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
		cuerpo->setMaterialName("Practica1/rojo");

		cuerpoNode->attachObject(cuerpo);

		Ogre::Entity* alaizq = mSM->createEntity("cube.mesh");
		alaizq->setMaterialName("Practica1/alas");

		alaINode->attachObject(alaizq);

		Ogre::Entity* alader = mSM->createEntity("cube.mesh");
		alader->setMaterialName("Practica1/alas");

		alaDNode->attachObject(alader);

		Ogre::Entity* piloto = mSM->createEntity("ninja.mesh");
		piloto->setMaterialName("Practica1/amarillo");

		pilotoNode->attachObject(piloto);

		helice1 = new AspasMolino(heliceNode1, 6);
		helice2 = new AspasMolino(heliceNode2, 6);

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

		//luz
		foco = mSM->createLight("Luz Foco");
		foco->setType(Ogre::Light::LT_SPOTLIGHT);
		foco->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
		foco->setDirection(Ogre::Vector3(1, -1, 0));
		foco->setSpotlightInnerAngle(Ogre::Degree(5.0f));
		foco->setSpotlightOuterAngle(Ogre::Degree(45.0f));
		foco->setSpotlightFalloff(0.0f);
		
		luzNode->attachObject(foco);
		luzNode->translate(0, -50, 0);
	}
	~Avion() {
		delete helice1; helice1 = nullptr;
		delete helice2; helice2 = nullptr;
	};

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		if (evt.keysym.sym == SDLK_g) {
			helice1->keyPressed(evt);
			helice2->keyPressed(evt);
		}
		return true;
	};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {
		Ogre::Real time = evt.timeSinceLastFrame;
		int angle = 800 * time;
		helice1->rotaAspas(angle);
		helice2->rotaAspas(angle);
		if (!moveAround) {
			mNode->translate(1200, 0, 0, Ogre::Node::TS_LOCAL);
			mNode->yaw(Ogre::Degree(3));
			mNode->translate(-1200, 0, 0, Ogre::Node::TS_LOCAL);
		}
	};

	virtual void receiveEvent(EntidadIG* entidad) {
		/*moveAround = true;
		foco->setVisible(false);*/
	};
};

