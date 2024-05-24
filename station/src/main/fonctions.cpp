#include "Arduino.h"
/*
Projet :  Tramway Arduino.
Carte : arduino UNO.
Cible : Tramway.
*/

// ---- Inclusion des modules ----

#include "fonctions.h"

// ---- Déclaration des variables ----

// ---- Déclaration des fonctions ----

void Station::init()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Attend des infos");
    ledTension = 0;
    sunLight = 0;
    railSwitchPostion = 0;
    lastMessage = NONE;
    servo.attach(servoPin);
}

void Station::display(String message)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
}

MESSAGE randomMessage()
{
    int number = random(0, 4);
    if (number == 0)
    {
        return NONE;
    }
    else if (number == 1)
    {
        return IN_STATION;
    }
    else if (number == 2)
    {
        return MOOVING;
    }
    else if (number == 3)
    {
        return DELAYED;
    }
    else
    {
        return NONE;
        Serial.print("Erreur dans la génération du message aléatoire.");
    }
}

void Station::listenMessage()
{
    lastMessage = message;
    message = randomMessage();
}

void Station::setLigth() // allume la led "lampadaire" plus ou moins fortement selon la lumière présente. (compris entre 1030 (noir dehors) et 850)
{
    sunLight = int(analogRead(lumPin));
    ledTension = map(sunLight, 925, 1023, 0, 255); // 1,417 * lum - 1204,17;
    if (sunLight < 925)
    {
        analogWrite(ledPin, 0);
    }
    else
    {
        analogWrite(ledPin, ledTension);
    }
}

void Station::setRailSwitch(int position) // Change la position de l'aiguillage selon la position donnée en paramètre.
{
    servo.write(position);
}

// ---- FONCTIONS ----

void stratTest(Station &station) // Permet de tester l'écran LCD.
{
    lcd.setCursor(0, 0);      // tell the lcd to write on the top row
    lcd.print("Hello, From"); // tell the lcd to write “hello, from” on the top  row
    lcd.setCursor(0, 1);      // tell the lcd to write on the bottom  row
    lcd.print("Arduino_uno_guy");
    delay(1000); // wait  for a second
    lcd.clear(); // clear the lcd

    station.setRailSwitch(OPEN);
    delay(1000);
    station.setRailSwitch(CLOSE);
    delay(1000);
}

void strategie(Station &station)
{
    station.setLigth();
    station.listenMessage();

    if (station.message == IN_STATION and station.lastMessage != IN_STATION)
    {
        Serial.println("Train en gare");
        station.display("Train en gare");
        if (station.servoPosition == CLOSE)
        {
            station.setRailSwitch(OPEN);
            station.servoPosition = OPEN;
        }
        else
        {
            station.setRailSwitch(CLOSE);
            station.servoPosition = CLOSE;
        }
        // station.railSwitchPostion += 1;
        // station.railSwitchPostion = station.railSwitchPostion % 2;
        // station.setRailSwitch(station.railSwitchPostion);
    }
    else if (station.message == MOOVING and station.lastMessage != MOOVING)
    {
        Serial.println("Le train avance");
        station.display("Le train avance");
    }
    else if (station.lastMessage == DELAYED and station.lastMessage != DELAYED)
    {
        Serial.println("Train retardé");
        station.display("Train retardé");
    }
    else if (station.message == NONE and station.lastMessage != NONE)
    {
        Serial.println("No information");
        station.display("No information");
    }
}
