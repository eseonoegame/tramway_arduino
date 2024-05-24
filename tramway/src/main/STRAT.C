
/**
 * @brief Stratégie des différents comportement du tramway.
 * @author Noé Game
 **/

#include "STRAT.h"

void strat1(Tramway &tramway) // Stratégie 1 : avance.
{
    tramway.setMotor(FORWARD);
}

void strat2(Tramway &tramway) // Stratégie 2 : accèlère, avance, décèlère, s'arrête.
{
    tramway.setMotor(ACCELERATE);
    delay(1000);

    tramway.setMotor(FORWARD);
    delay(1000);

    tramway.setMotor(DECELERATE);
    delay(1000);

    tramway.setMotor(STOP);
    delay(1000);
}

void strat3(Tramway &tramway) // Stratégie 3 : avance et s'arrête si voit balise de couleur.
{
    tramway.getColor();
    tramway.affichage();
    if (tramway.isStation() == true) // si on est en gare.
    {
        tramway.setMotor(STOP);
    }
    else
    {
        tramway.setMotor(FORWARD);
    }
}

void strat4(Tramway &tramway) // Stratégie 4 : affiche juste les couleurs détecter.
{
    tramway.getColor();
    tramway.affichage();
}

void strat5(Tramway &tramway) // Stratégie 5 : avance et s'arrête si voit obstacle sur la voie.
{
    tramway.getDistance();
    tramway.affichage();
    if (tramway.distance < STOP_DISTANCE)
    {
        tramway.setMotor(STOP);
    }
    else
    {
        tramway.setMotor(FORWARD);
    }
}

void strategie(Tramway &tramway)
{
    tramway.getDistance();
    tramway.getColor();
    tramway.affichage();
    // Serial.println(millis());

    if (tramway.isStation() == true) // si on est en gare.
    {
        tramway.setMotor(STOP);               // on s'arrête.
        tramway.state = STATION;              // on est en gare.
        tramway.sendMessageToStation("gare"); // on envoie un message à la station.
        tramway.setDoor(OPEN);                // ouverture des portes

        tramway.countDownBegin = millis();
        while (millis() - tramway.countDownBegin < 5000)
        {
            // On attend 5 secondes que les gens descende du train.
        }

        tramway.playSound();    // joue son SNCF pour signaler la fermeture des portes.
        tramway.setDoor(CLOSE); // fermeture des portes

        tramway.countDownBegin = millis();
        while (millis() - tramway.countDownBegin < 5000)
        {
            // Attend 5 secondes pour que les portes se ferment.
        }

        // on repart.
        tramway.dureeDepuisGare = millis();
        tramway.state = MOOVING;
        tramway.sendMessageToStation("mooving.");
        tramway.setMotor(FORWARD);
    }

    else if (tramway.distance < STOP_DISTANCE) // si obstacle sur la voie.
    {
        tramway.setMotor(STOP);
        tramway.playSound(); // On fait sonner le buzzer pour signaler l'obstacle.
        tramway.sendMessageToStation("retardé");
        tramway.state = RAIL_STOP;
        while (tramway.distance < STOP_DISTANCE)
        {
            // Serial.print("Tramway : je suis bloqué par un obstacle.");
            //  on attend que l'obstacle soit enlevé.
            //  messageToStation("Je suis bloqué sur les rails");
        }
        tramway.setMotor(FORWARD); // on repart.
        tramway.sendMessageToStation("mooving.");
    }

    else if (tramway.isFastRails() == true) // si on est sur les rails rapides.
    {
        tramway.tension = FAST;
    }

    else if (tramway.isSlowRails() == true) // si on est sur les rails lents.
    {
        tramway.tension = SLOW;
    }

    else
    {
        tramway.setMotor(FORWARD); // tout va bien, on avance.
    }
}
