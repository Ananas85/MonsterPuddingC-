/**
 * \file surfaceUtils.cpp
 * \brief gère nos fonctions d'affichage d'image
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include "surfaceUtils.h"
using namespace std;


/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief Action qui applique un rectangle de lecture sur une surface
 *
 * \param[in] x l'abscisse de notre image
 * \param[in] y l'ordonné de notre image
 * \param[in] source la source de notre image
 * \param[in] destination la destination de notre image
 * \param[in] clip notre rectangle que l'on veut appliqué
 */

void blitClipSurface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip ) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    offset.w = clip->w;
    offset.h = clip->h;
    SDL_BlitSurface( source, clip, destination, &offset );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief Action qui blit
 *
 * \param[in] source la source de notre image
 * \param[in] destination la destination de notre image
 */
void blitSurface( SDL_Surface *source, SDL_Surface *destination ) {
    SDL_BlitSurface( source, NULL, destination, NULL );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief Action qui crée une image avec un couleur transparente blanche
 *
 * \param[in] filename le nom de notre image
 */
SDL_Surface *loadBMPImageWithWhitetransparent( string filename ) {
    SDL_Surface *img = SDL_LoadBMP( filename.c_str() );
    SDL_Surface *optimizedImage = SDL_DisplayFormat( img );
    SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 255,255,255 ) );
    SDL_FreeSurface( img );
    return optimizedImage;
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief Action qui copie une surface en mémoire
 *
 * \param[in] source notre image à copier
 */
SDL_Surface *cloneSurface( SDL_Surface *source ) {
    return SDL_ConvertSurface( source, source->format, source->flags );
}


