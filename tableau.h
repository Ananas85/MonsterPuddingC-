#ifndef TABLEAU_H_INCLUDED
#define TABLEAU_H_INCLUDED

/**
 * \file tableau.h
 * \brief Gêre tous nos déplacements
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include "constantes.h"
#include "niveau.h"
#include "plateau.h"
#include "debugUtils.h"

bool passageNiveausup( niveau lvl );

void deplacementGauche( niveau &lvl, int &currentLevel, int y, int x, SDL_Surface *parentSurface );
void deplacementDroite( niveau &lvl, int &currentLevel, int y, int x, SDL_Surface *parentSurface );
void deplacementBas( niveau &lvl, int &currentLevel, int y, int x, SDL_Surface *parentSurface );
void deplacementHaut( niveau &lvl, int &currentLevel, int y, int x, SDL_Surface *parentSurface );
void deplacement( niveau &lvl, int &currentLevel, int y, int x, int deltaX, int deltaY, SDL_Surface *parentSurface );

#endif
