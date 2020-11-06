#pragma once
#include "Aspa.h"
#include <string>
#include "EntidadIG.h"
using namespace std;
class AspasMolino : public EntidadIG
{
private:
	//Ogre::SceneNode* aspasNode = nullptr;
	Ogre::SceneNode* aspa = nullptr;
	Ogre::SceneNode* tablero = nullptr;
	Ogre::SceneNode* adorno = nullptr;
	Ogre::SceneNode* cilindroNode = nullptr;
	int numAspas = 0;
	Aspa** arrayAspas;
	Ogre::SceneManager* mSM;
	bool metido = false;
public:
	AspasMolino(Ogre::SceneNode* asp, int num) : EntidadIG(asp), numAspas(num) {
		mSM = mNode->getCreator();
		//creacion del cilindro central
		string aspasName = mNode->getName();
		string cadaaspa = "aspa_";
		if (aspasName == "helice1") {
			cilindroNode = mSM->getSceneNode(aspasName)->createChildSceneNode("cilindro1");
			cadaaspa = "aspahel1_";
		}
		else if (aspasName == "helice2") {
			cilindroNode = mSM->getSceneNode(aspasName)->createChildSceneNode("cilindro2");
			cadaaspa = "aspahel2_";
		}
		else cilindroNode = mSM->getSceneNode(aspasName)->createChildSceneNode("cilindro");

		Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
		cilindroNode->attachObject(cil);
		cilindroNode->setScale(25.0, 8.0, 25.0);
		cilindroNode->pitch(Ogre::Degree(90));
		//creacion de las aspas
		arrayAspas = new Aspa * [num];
		for (int i = 0; i < numAspas; i++) {
			string n;
			string n2;
			string n3;
			if (aspasName == "helice1") {
				n = "tablerohel1_" + to_string(i);
				n2 = "adornohel1_" + to_string(i);
				n3 = "aspahel1_" + to_string(i);
			}
			else if (aspasName == "helice2") {
				n = "tablerohel2_" + to_string(i);
				n2 = "adornohel2_" + to_string(i);
				n3 = "aspahel2_" + to_string(i);
			}
			else {
				n = "tablero_" + to_string(i); n2 = "adorno_" + to_string(i); n3 = "aspa_" + to_string(i);
			}
			aspa = mSM->getSceneNode(aspasName)->createChildSceneNode(n3);
			tablero = mSM->getSceneNode(n3)->createChildSceneNode(n);
			adorno = mSM->getSceneNode(n3)->createChildSceneNode(n2);
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
	~AspasMolino() {
		delete[] arrayAspas;
		arrayAspas = nullptr;
	};

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		if (evt.keysym.sym == SDLK_g) {
			mNode->roll(Ogre::Degree(10));
		}
		else if (evt.keysym.sym == SDLK_c) {
			//evento que hace el que el cilindro central de las aspas del molino se mete hacia adentro y salga, descomentar aqui y la region Molino de la linea 187
			cilindroHaciaDentro();
		}
		return true;
	};

	void rotaAspas(int angle) {
		mNode->roll(Ogre::Degree(angle));
	}
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
};

