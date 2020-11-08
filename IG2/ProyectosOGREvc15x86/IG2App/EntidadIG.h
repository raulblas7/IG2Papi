#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreFrameListener.h>
#include <SDL_keycode.h>

class EntidadIG :public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* node/*, ...*/);
	~EntidadIG() {};
	//Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad) { 
		appListeners.push_back(entidad); };
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt)
	{
		if (evt.keysym.sym == SDLK_r) {
			sendEvent(this);
		}
		return false;
	};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {};

	virtual void receiveEvent(EntidadIG* entidad) {
		
	};

	void sendEvent(EntidadIG* entidad) {
		for (EntidadIG* e : appListeners)
			e->receiveEvent(this);
	};
};

