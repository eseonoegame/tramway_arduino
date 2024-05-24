/*
Projet :  Tramway Arduino.
Carte : arduino UNO.
Cible : Gare.
*/

// ---- Inclusion des modules ----

#include "fonctions.h"

// ---- Déclaration des variables ----

Station station;
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---- Déclaration des fonctions ----

void setup() // Initialisation des ports et des objets.
{
  Serial.begin(9600); // Initialize Serial port
  Serial.println("initialisation du programme.");
  station.init();
  delay(2000);
}

void loop()
{
  // stratTest(station); // Test de la communication avec le tramway.
  strategie(station); // Pass the 'station' object as a const reference.
  delay(1000);
}
