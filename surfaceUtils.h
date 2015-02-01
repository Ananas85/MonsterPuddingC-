

#ifndef _SURFACEUTILS_H
#define _SURFACEUTILS_H

/**
 * \file surfaceUtils.h
 * \brief gère nos fonctions d'affichage des images
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

void blitClipSurface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip );
void blitSurface( SDL_Surface *source, SDL_Surface *destination );

SDL_Surface* loadBMPImageWithWhitetransparent( string filename );
SDL_Surface* cloneSurface( SDL_Surface *source );

#endif
