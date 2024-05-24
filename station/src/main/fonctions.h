/*
Projet :  Tramway Arduino.
Carte : arduino UNO.
Cible : Gare.
*/

// ---- LIBRAIRIES ----

#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include <Wire.h>
// #include "src\main\Servo-1.2.1\src\Servo.h" // Include the Servo library
#include <Servo.h>

#ifndef FONCTIONS_H
#define FONCTIONS_H

// ---- CONSTANTES préprocesseur -----

#define ledPin 9    // pin de la led "lampadaire"
#define lumPin 10   // pin de la led "photo-resistance"
#define servoPin 11 // pin du servo moteur
#define OPEN 90
#define CLOSE 0

// ---- OBJETS ----

extern LiquidCrystal_I2C lcd;
extern Servo servo;

// ---- VARIABLES ----

typedef enum MESSAGE // typedef enum MESSAGE
{
    NONE = 0,
    IN_STATION = 1,
    MOOVING = 2,
    DELAYED = 3
};

// ---- CLASSES ----

class Station
{
public:
    int ledTension = 0;
    int sunLight = 0;
    int railSwitchPostion = 0;
    MESSAGE lastMessage = NONE;
    MESSAGE message = NONE;
    int servoPosition = CLOSE;

    // Station(); // Constructeur

    void init(); // Initialisation de l'écran.

    void display(String message); // Affiche un message sur l'écran.

    void listenMessage(); // Ecoute les messages envoyés par le tramway.

    void setLigth(); // allume la led "lampadaire" plus ou moins fortement selon la lumière présente. (compris entre 1030 (noir dehors) et 850)

    void setRailSwitch(int position); // Change la position de l'aiguillage selon la position donnée en paramètre.

private:
};

// ---- FONCTIONS ----

void stratTest(Station &station);
void strategie(Station &station);
MESSAGE randomMessage();

#endif
