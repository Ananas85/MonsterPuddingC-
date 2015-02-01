#ifndef _PLATEAU_H_
#define _PLATEAU_H_

/**
 * \file plateau.h
 * \brief gère l'affichage
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include <SDL.h>
#include <iostream>
#include "constantes.h"
#include "surfaceUtils.h"
#include "niveau.h"
#include "monster.h"
#include <math.h>

void plateauAfficheNiveau( niveau &n, SDL_Surface *parentSurface );
void afficheTricheur( SDL_Surface *parentSurface );
void afficheWithDelay( SDL_Surface *parentSurface, string filename, int second );

int convertIndiceX( int x );
int convertIndiceY( int y );
int convertXPixel( int xpixel );
int convertYPixel( int ypixel );


#endif

