/**
 * @brief   Déclaration des stratégies du tramway
 * @author  Noé Game
 * @date    june 2024
 * @carte : Uno ou Nano
 **/

#include "TRAMWAY.h"

#ifndef STRAT_H
#define STRAT_H

void strat1(Tramway &tramway);    // avance.
void strat2(Tramway &tramway);    // accèlère, avance, décèlère, s'arrête.
void strat3(Tramway &tramway);    // avance et s'arrête si voit balise de couleur.
void strat4(Tramway &tramway);    // affiche juste les couleurs détecter.
void strat5(Tramway &tramway);    // avance et s'arrête si voit obstacle sur la voie.
void strategie(Tramway &tramway); // fonctionnement final du train.

#endif
