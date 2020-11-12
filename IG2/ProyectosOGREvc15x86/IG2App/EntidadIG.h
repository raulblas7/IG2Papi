#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreFrameListener.h>
#include <SDL_keycode.h>

enum class MessageType
{
	R, C, E, NONE
};

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
		return false;
	};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {};

	void sendEvent(MessageType message) {

		if (message == MessageType::NONE) return;

		for (EntidadIG* e : EntidadIG::appListeners) {
			e->receiveEvent(message);
		}
	}
	virtual void receiveEvent(MessageType msg) {};
};

