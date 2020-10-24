#pragma once
#include "Aspa.h"
#include <string>
using namespace std;
class AspasMolino
{
private:
	Ogre::SceneNode* aspasNode = nullptr;
	Ogre::SceneNode* aspa = nullptr;
	Ogre::SceneNode* tablero = nullptr;
	Ogre::SceneNode* adorno = nullptr;
	Ogre::SceneNode* cilindroNode = nullptr;
	int numAspas = 0;
	Aspa** arrayAspas;
	Ogre::SceneManager* mSM;
	bool metido = false;
public:
	AspasMolino(Ogre::SceneNode* asp, int num) :aspasNode(asp), numAspas(num) {
		mSM = aspasNode->getCreator();
		//creacion del cilindro central
		cilindroNode = mSM->getSceneNode("aspas")->createChildSceneNode("cilindro");
		Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
		cilindroNode->attachObject(cil);
		cilindroNode->setScale(25.0, 8.0, 25.0);
		cilindroNode->pitch(Ogre::Degree(90));
		//creacion de las aspas
		arrayAspas = new Aspa*[num];
		for (int i = 0; i < numAspas; i++) {
			string n = "tablero_" + to_string(i);
			string n2 = "adorno_" + to_string(i);
			string n3 = "aspa_" + to_string(i);
			aspa = mSM->getSceneNode("aspas")->createChildSceneNode(n3);
			tablero = mSM->getSceneNode("aspa_" + to_string(i))->createChildSceneNode(n);
			adorno = mSM->getSceneNode("aspa_" + to_string(i))->createChildSceneNode(n2);
			arrayAspas[i] = new Aspa(aspa, tablero, adorno);
		}
		//colocacion aspas y adornos
		float angle = 0;
		float angleToAdd = 360 / numAspas;  //30 grados
		//Distancia con la que se multiplica el seno y coseno
		float distance = 220;
		for (int j = 0; j < numAspas; j++) {
			arrayAspas[j]->getTablero()->setPosition(Ogre::Math::Cos(Ogre::Degree(angle)) * distance, Ogre::Math::Sin(Ogre::Degree(angle)) * distance, 0);
			arrayAspas[j]->getAdorno()->setPosition(Ogre::Math::Cos(Ogre::Degree(angle)) * distance * 2, Ogre::Math::Sin(Ogre::Degree(angle)) * distance * 2, 12.5);
			arrayAspas[j]->getTablero()->roll(Ogre::Degree(angle));
			angle += angleToAdd;
		}
	};

	void keyPressed() {
		aspasNode->roll(Ogre::Degree(10));
	};

	void cilindroHaciaDentro() {
		if (!metido)
		{
			cilindroNode->translate(0, 0, -40);
			metido = true;

		}
		else
		{
			cilindroNode->translate(0, 0, 40);
			metido = false;
		}
	}

	void aspasRotate() {
		//aspasNode->translate(Ogre::Math::Cos(Ogre::Radian(0.1))* 20, 1, Ogre::Math::Sin(Ogre::Radian(0.1)) * 20);
		//aspasNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(0.1),Ogre::Node::TS_WORLD);

		
		aspasNode->translate(10, 0, 0);
		aspasNode->rotate(Ogre::Quaternion(Ogre::Degree(10), Ogre::Vector3(1, 0, 0)), Ogre::Node::TransformSpace::TS_WORLD);
	};
};

