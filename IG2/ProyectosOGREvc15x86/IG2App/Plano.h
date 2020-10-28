#pragma once
#include "EntidadIG.h"

class Plano : public EntidadIG
{
private:
	
public:
	Plano(Ogre::SceneNode* mNode) : EntidadIG(mNode) {
		MeshManager::getSingleton().createPlane("mPlane2080x1800",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Plane(Vector3::UNIT_Y, 0),
			2080, 1800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
		Ogre::Entity* plane = mSM->createEntity("mPlane2080x1800");
		mNode->attachObject(plane);
		mNode->translate(0, -365, 0);
	}
};

