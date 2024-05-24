/**
 * @file    TRAMWAY.cpp
 * @brief   Fonctions de la classe Tramway
 * @author  Noé Game
 * @date    june 2024
 * @carte : Uno ou Nano
 **/

#include "TRAMWAY.h"

void Tramway::tramway() // Constructeur de la classe Tramway.
{
	distance = 0;
	color = {0, 0, 0, 0};
	state = MOOVING;
	dureeDepuisGare = 0;
	countDownBegin = 0;
	tension = SLOW;
}

void Tramway::init() // Initialisation des ports de la carte.
{
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(buzzerPin, OUTPUT);

	pinMode(pinRotation1, OUTPUT);
	pinMode(pinRotation2, OUTPUT);
	pinMode(pinVitesse, OUTPUT);

	servo.attach(servoPin);

	digitalWrite(pinRotation1, LOW); // on met les moteurs à l'arrêt.
	digitalWrite(pinRotation2, LOW);

	// Initialisation du capteur APDS-9960 (configuration I2C et valeurs initiales)
	if (colorSensor.init())
	{
		Serial.println(("Initialisation du capteur APDS-9960 réussie"));
	}
	else
	{
		Serial.println(("Une erreur s'est produite lors de l'initialisation du capteur APDS-9960!"));
	}

	// Démarrage du capteur de lumière APDS-9960 (sans interruptions)
	if (colorSensor.enableLightSensor(false))
	{
		Serial.println(("Le capteur de lumière est maintenant en marche"));
	}
	delay(500); // Attente de la fin de l'initialisation et de l'étalonnage du capteur.
}

void Tramway::depart() // Départ du tramway.
{
	playSound();	// départ : on préviens de la fermeture des porte.
	setDoor(CLOSE); // départ : on ferme les portes.
	state = MOOVING;
	tension = SLOW;
	dureeDepuisGare = millis();
}

void Tramway::getDistance() // Retourne la distance de l'obstacle détecté par le capteur.
{
	long dureeEcho = 0;
	// Émission d'un signal de durée 10 microsecondes
	digitalWrite(trigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	// Écoute de l'écho
	dureeEcho = pulseIn(echoPin, HIGH);
	// Calcul de la distance
	distance = dureeEcho * 0.034 / 2; // distance = 1/2 vitesse du son fois la durée
}

void Tramway::affichage() // Affiche les valeurs pour déboggage en console.
{
	Serial.print("Distance : ");
	Serial.print(distance);
	Serial.print(" | ");

	Serial.print("Etat : ");
	Serial.print(state);
	Serial.print(" | ");

	Serial.print("Tension : ");
	Serial.print(tension);
	Serial.print(" | ");

	Serial.print("r = ");
	Serial.print(color.r);
	Serial.print(" | ");

	Serial.print("g = ");
	Serial.print(color.g);
	Serial.print(" | ");

	Serial.print("b = ");
	Serial.print(color.b);
	Serial.println();
}

void Tramway::setMotor(MOTOR_ORDER order) // Contrôle les moteurs en fonction de l'ordre reçu.
{
	if (order == STOP) // on s'arrête.
	{
		digitalWrite(pinRotation1, LOW);
		digitalWrite(pinRotation2, LOW);
		analogWrite(pinVitesse, NUL);
	}
	else if (order == FORWARD) // on avance.
	{
		digitalWrite(pinRotation1, HIGH);
		digitalWrite(pinRotation2, LOW);
		analogWrite(pinVitesse, tension);
		state = MOOVING;
	}
	else if (order == BACKWARD) // on recule.
	{
		digitalWrite(pinRotation1, LOW);
		digitalWrite(pinRotation2, HIGH);
		analogWrite(pinVitesse, tension);
		state = MOOVING;
	}
	else if (order == ACCELERATE) // on accèlère
	{
		for (int i = 1; i <= 255; i++)
		{
			tension = i;
			setMotor(FORWARD);
			state = MOOVING;
		}
	}
	else if (order == DECELERATE) // on freine
	{
		for (int i = 255; i >= 0; i--)
		{
			tension = i;
			setMotor(BACKWARD);
			state = MOOVING;
		}
	}
}

void Tramway::setDoor(DOOR_ORDER order) // Contrôle les portes en fonction de l'ordre reçu.
{
	if (order == CLOSE) // on ferme les portes.
	{
		servo.write(DOOR_POSITION_CLOSE);
	}
	else if (order == OPEN) // on ouvre les portes.
	{
		servo.write(DOOR_POSITION_OPEN);
	}
}

void Tramway::playSound() // Contrôle le buzzer en fonction de l'ordre reçu.
{
	// unsigned long countdownBegin = 0;
	const int notes[] = {261, 392, 415, 311}; // Do, Sol, La bémol, Mi bémol

	for (int i = 0; i < 4; i++)
	{
		tone(buzzerPin, notes[i], 550); // 550 ms la durée de la note
										/*
										countdownBegin = millis();
										while ((millis() - countdownBegin) < noteDuration)
										{
											// On attend 5 secondes.
										}
										*/
	}
}

void Tramway::getColor() // Retourne la couleur détectée par le capteur.
{
	// Lecture des niveaux de lumière (ambiante, rouge, verte, bleue)
	if (!colorSensor.readAmbientLight(color.l) || !colorSensor.readRedLight(color.r) || !colorSensor.readGreenLight(color.g) || !colorSensor.readBlueLight(color.b))
	{
		Serial.println("Erreur de lecture des valeurs de lumière");
	}
	else
	{
		// Serial.println("Lecture des valeurs de lumière réussie.");
	}
}

bool Tramway::isStation() // Retourne True si on est en gare et False sinon.
{
	if ((color.r > 4) and (color.b > 4) and (color.g > 4) and (millis() - dureeDepuisGare > 4000))
	{
		return true;
	}
	return false;
}

bool Tramway::isFastRails() // Retourne True si on est en gare et False sinon.
{
	if ((color.r > 4) and (color.b > 4) and (color.g > 4))
	{
		return true;
	}
	return false;
}

bool Tramway::isSlowRails() // Retourne True si on est en gare et False sinon.
{
	if ((color.r > 4) and (color.b > 4) and (color.g > 4))
	{
		return true;
	}
	return false;
}

void Tramway::sendMessageToStation(String message) // Envoie un message à la station.
{
	Serial.println("Tramway : " + message);
}
