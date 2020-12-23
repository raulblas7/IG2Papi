#pragma once
#include "EntidadIG.h"
#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

class OgreAnimation;
class OgreKeyFrame;
class Boya : public EntidadIG
{
private:
	Ogre::Entity* entBoya;
	int duracion = 16;
	AnimationState* animationState;
	int  longDesplazamiento=100;
public:
	Boya(Ogre::SceneNode* node) : EntidadIG(node) {
		entBoya = mSM->createEntity("uv_sphere.mesh");
		entBoya->setMaterialName("practicaGLSL/Holes");
		mNode->attachObject(entBoya);

		Animation* animation = mSM->createAnimation("animVV", duracion);
		NodeAnimationTrack* track = animation->createNodeTrack(0);
		track->setAssociatedNode(mNode);

		Real durPaso = duracion / 4.0;
		mNode->setInitialState();
		Vector3 keyframePos(0,-175,0); Vector3 src(0, 0, 1); // posición y orientación iniciales
		TransformKeyFrame* kf; // 4 keyFrames: origen(0), abajo, arriba, origen(3)
		kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen

		kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: abajo
		keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
		kf->setTranslate(keyframePos); // Abajo
		kf->setRotation(src.getRotationTo(Vector3(1, 0, 1))); // Yaw(45)

		kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 2: arriba
		keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
		kf->setTranslate(keyframePos); // Arriba
		kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(-45)

		kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 3: origen

		animationState = mSM->createAnimationState("animVV");
		animationState->setLoop(true);
		animationState->setEnabled(true);
	}
	~Boya() {
		delete entBoya; entBoya = nullptr;
	}

	virtual void frameRendered(const Ogre::FrameEvent& evt) {
		animationState->addTime(evt.timeSinceLastFrame);
	};
	virtual void receiveEvent(MessageType message) {
		if (message == MessageType::R) {

			entBoya->setMaterialName("practicaGLSL/ExplotaGS");

		}
	}
};

