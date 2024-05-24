/**
 * @file    TRAMWAY.h
 * @brief   Déclaration de la classe Tramway
 * @author  Noé Game
 * @date    june 2024
 * @carte : Uno ou Nano
 **/

#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_APDS9960.h"
#include <Servo.h>

#ifndef TRAMWAY_H
#define TRAMWAY_H

// ---- Déclaration des broches de la carte. ----

#define pinRotation1 2 // Port de la carte pour : Sens de rotation 1.
#define pinRotation2 4 // Port de la carte pour : Sens de rotation 2.
#define pinVitesse 5   // Port de la carte pour : PWM vitesse.
#define trigPin 7	   // Port de la carte pour : PWM capteur ultrason
#define echoPin 6	   // Port de la carte pour : PWM capteur ultrason.
#define servoPin 10	   // Port de la carte pour : PWM servo de la porte.
#define buzzerPin 0	   // Port de la carte pour : PWM buzzer.
#define RX_Pin 8	   // Port de la carte pour : broche RX HC-05
#define TX_Pin 9	   // Port de la carte pour : broche TX HC-05

// ---- Déclaration des constantes. ----

#define NUL 0 // définition des vitesses associées au valeurs possibles du PWM.
#define SLOW 50
#define FAST 80
#define STOP_DISTANCE 15 // distance d'arrêt du tramway.

#define DOOR_POSITION_OPEN 0   // position de la porte ouverte.
#define DOOR_POSITION_CLOSE 90 // position de la porte fermée.

extern SparkFun_APDS9960 colorSensor; // Création d'un objet de type SparkFun_APDS9960.
extern Servo servo;					  // Création d'un objet de type Servo.

struct COLOR
{
	uint16_t l; // ambiant light.
	uint16_t r;
	uint16_t g;
	uint16_t b;
};

typedef enum MOTOR_ORDER
{
	STOP = 0,
	FORWARD = 1,
	BACKWARD = 2,
	ACCELERATE = 3,
	DECELERATE = 4
};

typedef enum DOOR_ORDER
{
	CLOSE = 0,
	OPEN = 1
};

typedef enum STATE
{
	STATION = 0,
	MOOVING = 1,
	RAIL_STOP = 2
};

// ---- Déclaration des fonctions. ----

class Tramway
{
public:
	void tramway();							   // constructeur.
	void init();							   // initialisation.
	void depart();							   // départ du tramway.
	void getDistance();						   // retourne la distance de l'obstacle détecté par le capteur.
	void setMotor(MOTOR_ORDER order);		   // contrôle les moteurs en fonction de l'ordre reçu.
	void setDoor(DOOR_ORDER order);			   // contrôle les portes en fonction de l'ordre reçu.
	void playSound();						   // fait sonner le buzzer.
	void affichage();						   // affiche les valeurs pour déboggage en console.
	void getColor();						   // récupère les valeurs de couleur du capteur.
	void sendMessageToStation(String message); // envoie un message à la station.

	bool isStation();	// retourne vrai si le tramway est à la station.
	bool isFastRails(); // retourne vrai si le tramway est en zone rapide.
	bool isSlowRails(); // retourne vrai si le tramway est en zone lente.

	int distance;
	STATE state;
	unsigned long dureeDepuisGare;
	unsigned long countDownBegin;
	int tension;

private:
	COLOR color;
};

#endif
