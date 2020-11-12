#pragma once

#include "EntidadIG.h"
#include <OgreEntity.h>

class Simbad:public EntidadIG
{
private:
	Ogre::Entity* entSin;
	Ogre::Entity* espadica;
	AnimationState* animationState;
	AnimationState* animationState2;
	AnimationState* animationState3;
	bool baile = false;
	bool dcha = true;
public:
	Simbad(Ogre::SceneNode* node) : EntidadIG(node) {
		entSin = mSM->createEntity("Sinbad.mesh");
		mNode->attachObject(entSin);
		mNode->scale(30, 30, 30);
		mNode->translate(-600, -190, 600);
		//apartado 32
		//animacion de baile
		animationState = entSin->getAnimationState("Dance");
		animationState->setEnabled(true);
		animationState->setLoop(true);

		//apartado 33
		//animacion run base
		animationState2 = entSin->getAnimationState("RunBase");
		animationState2->setEnabled(true);
		animationState2->setLoop(true);

		//animacion run top
		animationState3 = entSin->getAnimationState("RunTop");
		animationState3->setEnabled(true);
		animationState3->setLoop(true);

		//apartado35
		//espada
		espadica = mSM->createEntity("Sword.mesh");
		entSin->attachObjectToBone("Handle.R", espadica);
		
	}

	~Simbad() {
		delete entSin; entSin = nullptr;
		delete espadica; espadica = nullptr;
		delete animationState; animationState = nullptr;
		delete animationState2; animationState2 = nullptr;
		delete animationState3; animationState3 = nullptr;
	}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override {
		if (evt.keysym.sym == SDLK_c) {
			sendEvent(MessageType::C);
		}
		else if (evt.keysym.sym == SDLK_e) {
			sendEvent(MessageType::E);
		}
		return true;
	};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {
		//apartado 32
		//dance
		if (baile) {
			animationState->addTime(evt.timeSinceLastFrame);
		}
		else {
			//apartado 33
			//run base
			animationState2->addTime(evt.timeSinceLastFrame);

			//run top
			animationState3->addTime(evt.timeSinceLastFrame);
		}
	};

	virtual void receiveEvent(MessageType message) {
		if (message == MessageType::C && !baile) {
			baile = true;
		}
		else if (message == MessageType::C && baile) {
			baile = false;
		}
		else if (message == MessageType::E) {
			entSin->detachObjectFromBone(espadica);
			if (dcha) {
				entSin->attachObjectToBone("Handle.L", espadica);
				dcha = false;
			}
			else {
				entSin->attachObjectToBone("Handle.R", espadica);
				dcha = true;
			}
		}
	};
};

