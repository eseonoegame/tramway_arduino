/**
 * @file    main.cpp
 * @brief   Main file for the Tramway
 * @author  Noé Game
 * @date    june 2024
 * @carte : Uno ou Nano
 */

// #include "TRAMWAY.h"
#include "STRAT.h"

Tramway tramway;
SparkFun_APDS9960 colorSensor = SparkFun_APDS9960();
Servo servo;

void loop()
{
	//  strat1(tramway); // avance.
	//  strat2(tramway); // accèlère, avance, décèlère, s'arrête.
	//  strat3(tramway); // avance et s'arrête si voit balise de couleur.
	strat4(tramway); // affiche juste les couleurs détecter.
					 // strat5(tramway); // avance et s'arrête si voit obstacle sur la voie.
					 // strat6(tramway); // fait sonner le buzzer plusieurs fois.
					 // strategie(tramway); // fonctionnement final du train.
}

void setup()
{
	Serial.begin(9600);
	Serial.println("initialisation");

	tramway.init();
	tramway.depart();

	delay(5000);
}
