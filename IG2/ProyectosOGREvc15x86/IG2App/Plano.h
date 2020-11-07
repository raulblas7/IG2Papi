#pragma once
#include "EntidadIG.h"
#include <OgreMeshManager.h>
#include "IG2App.h"
#include <OgreEntity.h>
#include <string>
using namespace std;
using namespace Ogre;

class Plano : public EntidadIG
{
private:
	Ogre::Entity* plane;
public:
	Plano(Ogre::SceneNode* mNode, int i) : EntidadIG(mNode) {
		MeshManager::getSingleton().createPlane("mPlane2080x1800" + to_string(i),
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Plane(Vector3::UNIT_Y, 0),
			2080, 1800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
		 plane = mSM->createEntity("mPlane2080x1800" + to_string(i));
		mNode->attachObject(plane);
		mNode->translate(0, -365, 0);
	}
	Entity* getEntity() { return plane; }
};

