/**
 * \file plateau.cc
 * \brief gère entièrment l'affichage de notre jeu
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include "plateau.h"


/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief fonction qui convertit une case donnée en pixel
 *
 * \param[in] x la colonne de la case que l'on veut convertir
 * \return les pixels
 */

int convertIndiceX( int x ) {
    return  CASEW * x  + MARGINLEFT + PADDINGRIGHT * x;
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief fonction qui convertit une case donnée en pixel
 *
 * \param[in] y la ligne de la case que l'on veut convertir
 * \return les pixels
 */
int convertIndiceY( int y ) {
    return  CASEH * y  + MARGINTOP + PADDINGBOTTOM * y;
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief fonction qui convertit un pixel donnée en une case
 *
 * \param[in] x la position sur l'axe des ordonnés du pixel que l'on veut convertir
 * \return la valeur arrondie inférieur de la case
 */
int convertXPixel( int xpixel ) {
    return  ceil( ( xpixel - MARGINLEFT ) / ( CASEW  + PADDINGRIGHT ) );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief fonction qui convertit un pixel donnée en une case
 * \param[in] y la position sur l'axe des abscisses du pixel que l'on veut convertir
 * \return la valeur arrondie inférieur de la case
 */

int convertYPixel( int ypixel ) {
    return  ceil( ( ypixel - MARGINTOP ) / ( CASEH  + PADDINGBOTTOM ) );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief Action qui affiche un niveau, c'est à dire les sprites des montres vivants
 * ou endormis ainsi que ceux des obstacles de type glace, livre, flèche
 *
 * \param[in,out] n la structure niveau
 * \param[in] parentSurface surface où l'on affiche le niveau
 */

void plateauAfficheNiveau( niveau &n, SDL_Surface *parentSurface ) {
    ///On crée une surface pour le fond du jeu
    SDL_Surface *background = SDL_LoadBMP( "Images/background.bmp" );

    ///On l'affiche
    blitSurface( background, parentSurface );

    ///Notre surface pour les sprites
    SDL_Surface *sprites = loadBMPImageWithWhitetransparent("Images/sprite.bmp");

    ///Monstres que l'on initialise avec leur position et leur taille sur le sprite
    SDL_Rect monstreVivant; monstreVivant.x = VIVANTX; monstreVivant.y = VIVANTY; monstreVivant.h = CASEH; monstreVivant.w = CASEW;
    SDL_Rect monstreDort; monstreDort.x = DODOX; monstreDort.y = DODOY; monstreDort.h = CASEH; monstreDort.w = CASEW;
    SDL_Rect livre; livre.x = LIVREX; livre.y = LIVREY; livre.h = CASEH; livre.w = CASEW;
    SDL_Rect glace; glace.x = GLACEX; glace.y = GLACEY; glace.h = CASEH; glace.w = CASEW;
    SDL_Rect flecheg; flecheg.x = FLECHEGX; flecheg.y = FLECHEGY; flecheg.h = CASEH; flecheg.w = CASEW;
    SDL_Rect fleched; fleched.x = FLECHEDX; fleched.y = FLECHEDY; fleched.h = CASEH; fleched.w = CASEW;
    SDL_Rect flecheh; flecheh.x = FLECHEHX; flecheh.y = FLECHEHY; flecheh.h = CASEH; flecheh.w = CASEW;
    SDL_Rect flecheb; flecheb.x = FLECHEBX; flecheb.y = FLECHEBY; flecheb.h = CASEH; flecheb.w = CASEW;
    SDL_Rect pesticide; pesticide.x = PESTIX; pesticide.y = PESTIY; pesticide.h = CASEH; pesticide.w = CASEW;
    SDL_Rect cloneur; cloneur.x = CLONEX; cloneur.y = CLONEY; cloneur.h = CASEH; cloneur.w = CASEW;

    /// On crée le rectangle clip
    SDL_Rect clip;

    ///On parcourt la liste de monstres que l'on à jusqu'au nombre de monstres que l'on a vraiment
    for( int i = 0; i < n.nbMonstres; i++ ) {
        ///On crée un monstre nommé monstre qui est situé dans notre tableau de monstre de notre level
        monstre monstre = n.listeMonstre[i];
        if ( monstre.etat == STANDARD ) { clip = monstreVivant; }
        if ( monstre.etat == DORMEUR  ) { clip = monstreDort;   }
        ///On affiche notre clip
        blitClipSurface( convertIndiceX( monstre.x ), convertIndiceY( monstre.y ), sprites, parentSurface, &clip );
    }

    ///On parcourt la liste d'obstacles que l'on à jusqu'au nombre d'obstacle que l'on a vraiment
    for( int i = 0; i < n.nbObstacles; i++ ) {
        ///On, créé un obstacle qui correspond à celui de l'indice de nos obstacles
        obstacle obstacle = n.listeObstacle[i];

        if ( obstacle.type == LIVRE ) { clip = livre; }
        if ( obstacle.type == GLACE ) { clip = glace; }
        if ( obstacle.type == FLECHEG ) { clip = flecheg; }
        if ( obstacle.type == FLECHED ) { clip = fleched; }
        if ( obstacle.type == FLECHEH ) { clip = flecheh; }
        if ( obstacle.type == FLECHEB ) { clip = flecheb; }
        if ( obstacle.type == PESTI ) { clip = pesticide; }
        if ( obstacle.type == CLONE ) { clip = cloneur; }
        if ( obstacle.type == FLECHEM ) { clip = flecheb; }

        blitClipSurface( convertIndiceX( obstacle.x ), convertIndiceY( obstacle.y ), sprites, parentSurface, &clip );
        ///Si c'était une flèche monstre, on affiche les deux
        if ( obstacle.type == FLECHEM ) {
            blitClipSurface( convertIndiceX(obstacle.x), convertIndiceY(obstacle.y), sprites, parentSurface, &monstreVivant );
        }

    }

    ///On rafraichit l'écran parent, en libérante les surfaces...
    SDL_FreeSurface( sprites );
    SDL_Flip( parentSurface );
    SDL_FreeSurface( background );
    SDL_Delay( 40 );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief Action qui affiche une surface avec un délai s'il est donné
 * \param[in] parentSurface la surface parent
 * \param[in] filename le nom de notre image
 * \param[in] second le délai que l'on veut
 */
void afficheWithDelay( SDL_Surface *parentSurface, string filename, int second ) {
    SDL_Surface *presentSurface = SDL_LoadBMP( filename.c_str() );
    blitSurface( presentSurface, parentSurface );
    SDL_FreeSurface( presentSurface );
    SDL_Flip( parentSurface );
    if ( second > 0 ) {
        SDL_Delay( second * 1000 );
    }
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 04 décembre 2013
 * \brief Action qui anime notre tricheur
 * \param[in] parentSurface la surface parent
 */
void afficheTricheur( SDL_Surface *parentSurface ) {
    ///On crée la surface de notre tricheur
    SDL_Surface *tricheurSurface = loadBMPImageWithWhitetransparent( "Images/tricheur.bmp" );
    ///On clone notre surface parent
    SDL_Surface *parentDollySurface = cloneSurface( parentSurface );

    ///On gère l'emplacement de notre tricheur sur notre image
    SDL_Rect tricheurClipOrigin;
    tricheurClipOrigin.x = 56;
    tricheurClipOrigin.y = 251;
    tricheurClipOrigin.w = 251;
    tricheurClipOrigin.h = 280;

    int deltaY = 280;
    int tX = ceil( ECRAN_WIDTH / 2 - tricheurClipOrigin.w / 2  + 20 );

    ///On fait monté le tricheur
    for( int i = 0; i < 20; i++ ) {
        deltaY -= i;
        ///On affiche notre copie de l'écran parent sur l'écran parent
        blitSurface( parentDollySurface, parentSurface );
        ///On affiche notre tricheur
        blitClipSurface( tX, deltaY, tricheurSurface, parentSurface, &tricheurClipOrigin );
        SDL_Flip( parentSurface );
        SDL_Delay( 30 );
    }
    ///On fait descendre le tricheur (même principe)
    for( int i = 0; i < 10; i++ ) {
        deltaY += i;
        blitSurface( parentDollySurface, parentSurface);
        blitClipSurface( tX, deltaY, tricheurSurface, parentSurface, &tricheurClipOrigin );
        SDL_Flip( parentSurface );
        SDL_Delay( 30 );
    }
    SDL_Delay( 2000 );
    blitSurface( parentDollySurface, parentSurface );
    SDL_FreeSurface( parentDollySurface );
    SDL_FreeSurface( tricheurSurface );

}

