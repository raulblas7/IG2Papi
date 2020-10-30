#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreFrameListener.h>

class EntidadIG :public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* node/*, ...*/);
	~EntidadIG() {};
	//Vector est�tico de listeners
	static std::vector<EntidadIG*> appListeners;
	//A�adir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad) { appListeners.push_back(entidad); };
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt)
	{
		return true;
	};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {
		Ogre::Real time = evt.timeSinceLastFrame;

	};

	virtual void receiveEvent(EntidadIG* entidad) {};

	void sendEvent(EntidadIG* entidad) {
		for (EntidadIG* e : appListeners)
			e->receiveEvent(this);
	};
};

