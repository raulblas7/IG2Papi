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
	AnimationState* animationState5;
	bool baile = false;
	bool dcha = true;
	int duracion = 6;
	int longDesplazamiento = 300;
public:
	Simbad(Ogre::SceneNode* node) : EntidadIG(node) {
		entSin = mSM->createEntity("Sinbad.mesh");
		mNode->attachObject(entSin);
		mNode->scale(30, 30, 30);
		mNode->translate(-600, -190, 600);
		//mNode->rotate(Quaternion(Degree(135.0), Vector3(0, 1, 0)));
		//apartado 32
		//animacion de baile
		animationState = entSin->getAnimationState("Dance");
		animationState->setEnabled(false);
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

		//animacion IdleTop
		animationState5 = entSin->getAnimationState("IdleTop");
		animationState5->setEnabled(false);
		animationState5->setLoop(true);


		//apartado35
		//espada
		espadica = mSM->createEntity("Sword.mesh");
		entSin->attachObjectToBone("Handle.R", espadica);

		//animacion caminar por agua
		Animation* animation = mSM->createAnimation("caminaAgua", duracion);
		NodeAnimationTrack* track = animation->createNodeTrack(0);
		track->setAssociatedNode(mNode);

		Real durPaso = duracion / 5.0;
		mNode->setInitialState();
		Vector3 keyframePos(600,0,-600);
		double g=135.0 ;
		
		TransformKeyFrame* kf; // 4 keyFrames: origen(0), abajo, arriba, origen(3)
		kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
		
		kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 2: centro plano
		kf->setRotation(Quaternion(Degree(g), Vector3(0, 1, 0))); // Yaw(45)

		kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: centro plano
		kf->setTranslate(keyframePos); // Abajo
		kf->setRotation(Quaternion(Degree(g), Vector3(0, 1, 0)));


		kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: gira
		g += 180.0;
		kf->setRotation(Quaternion(Degree(g), Vector3(0, 1, 0)));
		kf->setTranslate(keyframePos); // Abajo

		kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 3: gira
		kf->setRotation(Quaternion(Degree(g), Vector3(0, 1, 0)));

		kf = track->createNodeKeyFrame(durPaso * 5); // Keyframe 4: origen


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
		if (animationState->getEnabled()) {
			animationState->addTime(evt.timeSinceLastFrame);
		}
		else if(animationState2->getEnabled()) {
			//apartado 33
			//run base
			animationState2->addTime(evt.timeSinceLastFrame);
			//run top
			animationState3->addTime(evt.timeSinceLastFrame);
			//run across rio
			animationState4->addTime(evt.timeSinceLastFrame);
		}
		else {
			animationState5->addTime(evt.timeSinceLastFrame);
		}
	};

	virtual void receiveEvent(MessageType message) {
		if (message == MessageType::C && !animationState->getEnabled()) {
			animationState->setEnabled(true);
		    animationState2->setEnabled(false);
			animationState3->setEnabled(false);
			animationState4->setEnabled(false);
			animationState5->setEnabled(false);

		}
		else if (message == MessageType::C && animationState->getEnabled()) {
			animationState->setEnabled(false);
			animationState2->setEnabled(true);
			animationState3->setEnabled(true);
			animationState4->setEnabled(true);
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
		else if (message == MessageType::R && !animationState5->getEnabled()) 
		{
				animationState5->setEnabled(true);
				animationState4->setEnabled(false);
				animationState3->setEnabled(false);
				animationState2->setEnabled(false);
				animationState->setEnabled(false);
				//simbad se cae bocarriba
				mNode->pitch(Ogre::Degree(90.0));
				mNode->yaw(Ogre::Degree(180.0));
				mNode->translate(Vector3(0, -150, 0));

		}
		
	};
};

