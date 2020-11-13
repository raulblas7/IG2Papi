#pragma once

#include "EntidadIG.h"
#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

class OgreAnimation;
class OgreKeyFrame;
class Simbad:public EntidadIG
{
private:
	Ogre::Entity* entSin;
	Ogre::Entity* espadica;
	AnimationState* animationState;
	AnimationState* animationState2;
	AnimationState* animationState3;
	AnimationState* animationState4;
	bool baile = false;
	bool dcha = true;
	int duracion = 16;
	int longDesplazamiento = 300;
public:
	Simbad(Ogre::SceneNode* node) : EntidadIG(node) {
		entSin = mSM->createEntity("Sinbad.mesh");
		mNode->attachObject(entSin);
		mNode->scale(30, 30, 30);
		mNode->translate(-600, -190, 600);
		mNode->rotate((Ogre::Quaternion(sqrt(0.25),0, sqrt(0.25), 0)));
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

		Animation* animation = mSM->createAnimation("caminaAgua", duracion);
		NodeAnimationTrack* track = animation->createNodeTrack(0);
		track->setAssociatedNode(mNode);

		Real durPaso = duracion / 5.0;
		mNode->setInitialState();
		Vector3 keyframePos; 
		Ogre::Vector3 src(0, 0, 1);
		TransformKeyFrame* kf; // 4 keyFrames: origen(0), abajo, arriba, origen(3)
		kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
		//kf->setRotation(src.getRotationTo(Vector3(1, 0, -1))); // Yaw(45)
		
		//kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: gira


		kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: centro plano
		keyframePos = Vector3(600,0,-600);
		kf->setTranslate(keyframePos); // Abajo

		//kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: gira
		//kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(45)

		kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: origen

		animationState4 = mSM->createAnimationState("caminaAgua");
		animationState4->setLoop(true);
		animationState4->setEnabled(true);
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
			//run across rio
			animationState4->addTime(evt.timeSinceLastFrame);

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

