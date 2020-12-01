#pragma once
#include "EntidadIG.h"
#include <OgreMeshManager.h>
#include "IG2App.h"
#include <OgreEntity.h>
#include <string>
#include <OgreCameraMan.h>
#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreRenderTexture.h>
#include <OgreViewport.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreSubEntity.h>
#include <OgreMaterial.h>
#include <OgreTechnique.h>
#include <OgrePass.h>
#include <OgreRenderTargetListener.h>
using namespace std;
using namespace Ogre;

class Plano : public EntidadIG , RenderTargetListener
{
private:
	Ogre::Entity* plane;
	MovablePlane* mpRef = nullptr;
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

	~Plano() {
		delete plane; plane = nullptr;
		delete mpRef; mpRef = nullptr;
	}

	Entity* getEntity() { return plane; }

	virtual void receiveEvent(MessageType message) {
		if (message == MessageType::R) {
			plane->setMaterialName("Practica1/seco");
		}
	}
	void setReflejo(Camera* cam)
	{
		mpRef = new MovablePlane(Plane(Vector3::UNIT_Y, 0));                           // creamos el panel sobre el que se quiere realizar el reflejo
		mNode->attachObject(mpRef);                          // lo adjuntamos al nodo

		cam->enableReflection(mpRef);                          // configuramos el reflejo sobre el plano
		cam->enableCustomNearClipPlane(mpRef);

		// añadimos una textura, en el mismo grupo de recursos que la malla del panel, para usarla de RenderTarget y de textura del panel

		TexturePtr rttRef = TextureManager::getSingleton().createManual(
			"rttReflejo", // nombre que le damos
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			TEX_TYPE_2D,
			//(Real)mWindow->getViewport(0)->getActualWidth(), // widht ejemplo
			1080,
			/*(Real)cam->getViewport()->getActualHeight()*/800, // height ejemplo
			0, PF_R8G8B8, TU_RENDERTARGET);

		// añadimos un puerto de vista al RenderTarget con la nueva cámara
		RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
		Viewport* vpt = renderTexture->addViewport(cam);
		vpt->setClearEveryFrame(true);
		vpt->setBackgroundColour(ColourValue::White);           // color de fondo blanco (asi el reflejo se vera oscuro)

		// añadimos la nueva unidad de textura al material del panel
		TextureUnitState* tu = plane->getSubEntity(0)->getMaterial()->
			getTechnique(0)->getPass(0)->
			createTextureUnitState("rttReflejo"); 		
		tu->setColourOperation(LBO_MODULATE);                   // multiplicar->el reflejo tendera a ser mas oscuro
		// LBO_ADD / LBO_ALPHA_BLEND / LBO_REPLACE              // añadir->el reflejo tendera a ser mas claro
		//tu->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
		tu->setProjectiveTexturing(true, cam);

		renderTexture->addListener(this);
	}

	// nos avisa antes del renderizado
	 virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) {
		plane->setVisible(false);                               // oculta el panel (la entidad) y pone luz ambiente
		mNode->getCreator()->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	}

	// nos avisa despues del renderizado
	 virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt) {
		plane->setVisible(true);                                // restablece los cambios
		mNode->getCreator()->setAmbientLight(ColourValue(0, 0, 0));
	}

};
