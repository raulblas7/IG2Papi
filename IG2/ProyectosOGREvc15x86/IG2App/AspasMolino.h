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
	int numAspas = 0;
	Aspa** arrayAspas;
	Ogre::SceneManager* mSM;
public:
	AspasMolino(Ogre::SceneNode* asp, int num) :aspasNode(asp), numAspas(num) {
		mSM = aspasNode->getCreator();
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
		float angle = 0;
		float angleToAdd = 360 / 12;  //30 grados
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
		aspasNode->roll(Ogre::Degree(3));
	}
};

