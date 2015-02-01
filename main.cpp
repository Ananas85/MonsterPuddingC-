/**
 * \file main.cpp
 * \brief main
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "constantes.h"
#include "niveau.h"
#include "plateau.h"
#include "konamicode.h"
#include "debugUtils.h"
#include "tableau.h"

using namespace std;

int main( int argc, char* args[] ) {
    ///Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    ///On déclare la surface de notre jeu
    SDL_Surface *screen;

    ///On initialise les événements
    SDL_Event event;

    ///On crée notre écran
    screen = SDL_SetVideoMode( ECRAN_WIDTH, ECRAN_HEIGHT, 32, SDL_DOUBLEBUF );

    ///Le titre de notre jeu
    SDL_WM_SetCaption( "..:: MONSTER ::..", NULL );

    ///On affiche notre menu
    afficheWithDelay( screen, "Images/menu.bmp", 0 );


    ///On initialise le bouton play
    SDL_Rect play; play.x = PLAYX; play.y = PLAYY; play.h = PLAYH; play.w = PLAYW;
    ///On initialise le bouton règle
    SDL_Rect regle; regle.x = REGLEX; regle.y = REGLEY; regle.h = REGLEH; regle.w = REGLEW;
    ///On initialise le bouton menu
    SDL_Rect menu; menu.x = MENUX; menu.y = MENUY; menu.h = MENUH; menu.w = MENUW;
    ///On initialise le bouton recommencer
    SDL_Rect restart; restart.x = RESTARTX; restart.y = RESTARTY; restart.h = RESTARTH; restart.w = RESTARTW;
    ///On initialise le bouton retour
    SDL_Rect before; before.x = BEFOREX; before.y = BEFOREY; before.h = BEFOREH; before.w = BEFOREW;


    ///On rafraichit l'écran
    SDL_Flip( screen );

    ///Création d'un niveau nommé level
    niveau lvl;

    ///Le premier niveau est 1
    int currentLevel=1;

    ///On fait des booléens pour savoir si on est dans la boucle de jeu ou pas, dans le jeu ou dans le menu, si l'on se déplace...
    bool isRunning = true;
    bool isPlaying = false;
    bool isMoving = false;
    bool isMotion = false;
    bool godeplace=false;


    ///Tout ce qui nous servira pour le code konami
    ///Initialisation du tableau userEntry de taille 10
    konamicode userEntry = {0,0,0,0,0,0,0,0,0,0};
    ///Initialisation du tableau userEntryDebut
    konamicodeDebut userEntryDebut = {0,0};

    ///Initialisation de l'indice de notre tableau du code Konami
    int keyIndice = 0;

    ///Initialisation de nos variables pour les cases
    int caseX = 0, caseY = 0, caseXDelta = 0, caseYDelta = 0;

    /*!
     * \author Daurient Chloe et Chardan Anael
     * \date 30 novembre 2013
     * \brief Lecture du jeu
     * Tant que le booléen isRunning à la valeur true, le jeu fonctionne.
     * Lorsque le bolléen aura la valeur false, le jeu se terminera.
     *
     * \param[in] isRunning la boucle de jeu
     */

    ///Quand le jeu est commencé
    while( isRunning ) {
        ///On met en place la boucle d'évènement
        while( SDL_PollEvent( &event ) ) {

            /// Quand on clique sur la croix, le jeu s'arrête
            if ( event.type == SDL_QUIT ){
                isRunning = false;
            }

            /// Quand on fait rien, on gere l'aide si l'on survole à la bonne place
            if ( event.type == SDL_MOUSEMOTION ) {
                if ( ! isPlaying ) {
                    if ( (event.motion.x > regle.x ) && ( event.motion.x < regle.x + regle.w ) && ( event.motion.y > regle.y ) && ( event.motion.y < regle.y + regle.h ) ) {
                        afficheWithDelay( screen, "Images/regle.bmp", 0 );
                    }
                    else{
                        afficheWithDelay( screen, "Images/menu.bmp", 0);
                    }
                }
            }

            /// Code de triche KONAMI pour pouvoir passer au niveau suivant, on écoute le clavier
            if ( event.type == SDL_KEYUP ) {
                ///Si l'on joue
                if ( isPlaying ) {
                    ///On remplit un tableau avec 10 valeurs
                    userEntry[keyIndice++ % 10] = event.key.keysym.sym;
                    ///On regarde si le début de ce que l'on a tapé est le début du code
                    userEntryDebut[keyIndice % 2] = event.key.keysym.sym;
                    ///Si l'on a correctement tapé le code
                    if ( checkKonamiCodeDebut( userEntryDebut ) ) {
                        ///On passe l'indice de notre tableau à deux et on le remplit avec le début du code
                        keyIndice = 2;
                        userEntry[0] = 273;
                        userEntry[1] = 273;
                    }
                    ///Si notre tableau est remplit et correct et que l'on est pas au niveau max, on passe au supérieur avec une animation
                    if ( checkKonamiCode( userEntry ) && currentLevel < NBNIVEAU ) {
                        afficheTricheur( screen );
                        currentLevel++;
                        initNiveau( lvl, currentLevel );
                        plateauAfficheNiveau( lvl, screen );
                    }
                }
            }

            ///Si l'événement est le bouton gauche de la souris appuyé
            if ( ( event.type == SDL_MOUSEBUTTONDOWN ) && ( event.button.button == SDL_BUTTON_LEFT ) ) {
                /// on recupère les coordonnées de la souris
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                ///Si nous entrons dans le carré de play et que nous cliquons, on peut jouer
                if ( ( !isPlaying ) && ( ( mouseX > play.x ) && ( mouseX < play.x + play.w ) && ( mouseY > play.y ) && ( mouseY < play.y + play.h ) ) ) {
                    monsterprint( "Go !", 30 );
                    initNiveau( lvl, currentLevel );
                    plateauAfficheNiveau( lvl, screen );
                    isPlaying = true;
                }

                ///Le retour menu quand on joue
                if ( ( isPlaying ) && ( mouseX > menu.x ) && ( mouseX < menu.x + menu.w ) && ( mouseY > menu.y ) && ( mouseY < menu.y + menu.h ) ) {
                    monsterprint( "retour menu", 30 );
                    currentLevel = 1;
                    afficheWithDelay( screen, "Images/menu.bmp", 0 );
                    isPlaying = false;
                }

                ///Le restart level
                if ( ( isPlaying ) && ( mouseX > restart.x ) && ( mouseX < restart.x + restart.w ) && ( mouseY > restart.y ) && (mouseY < restart.y + restart.h ) ) {
                    initNiveau( lvl, currentLevel );
                    plateauAfficheNiveau( lvl, screen );
                }

                ///Le before, on retourne au niveau inférieur
                if ( ( isPlaying ) && ( mouseX > before.x ) && ( mouseX < before.x + before.w ) && ( mouseY > before.y ) && ( mouseY < before.y + before.h ) && currentLevel > 1 ) {
                    currentLevel--;
                    initNiveau( lvl, currentLevel );
                    plateauAfficheNiveau( lvl, screen );
                }
            }

            ///Si l'on fait un mouvement de type drag and drop
            else if ( ( event.type == SDL_MOUSEMOTION ) && ( event.button.button == SDL_BUTTON_LEFT ) ) {
                ///On regarde si notre souris se déplace déjà en cliquer glisser
                if ( !isMotion ) {
                    ///La case que l'on veut déplacer
                    caseX = convertXPixel( event.button.x );
                    caseY = convertYPixel( event.button.y );
                    monsterprint( "mouvement en cours", 10 );
                    ///On dit que l'on se déplace
                    isMotion = true;
                    ///On met qu'une procédure de déplacement pourra être lancée
                    godeplace = true;
                }
                ///On regarde où est que l'on est sur le plateau pour pouvoir comparer quand on relachera notre bouton
                caseXDelta = convertXPixel( event.button.x );
                caseYDelta = convertYPixel( event.button.y );
            }

            ///Si l'on relache notre bouton de la souris gauche
            if ( ( event.type == SDL_MOUSEBUTTONUP ) && ( event.button.button == SDL_BUTTON_LEFT ) ) {
                ///On calcule la différence entre les deux mouvements
                int mouseXrel = caseXDelta - caseX;
                int mouseYrel = caseYDelta - caseY;

                if ( isPlaying ) {
                    if ( !isMoving ) {
                        if ( godeplace ) {
                            isMoving = true;
                            ///On regarde si la valeur absolue de notre déplacement en X est plus grande que celle en Y (on se déplacera en colonne), sinon en ligne
                            ///On lance les procédures de déplacement correspondant à notre mouvement de la souris
                            if ( abs( mouseXrel ) > abs( mouseYrel ) ) {
                                if ( mouseXrel > 0 ) {
                                    deplacementDroite( lvl, currentLevel, caseY, caseX, screen );
                                } else if (mouseXrel < 0) {
                                    deplacementGauche( lvl, currentLevel, caseY, caseX, screen );
                                }
                            } else {
                                if ( mouseYrel > 0 ) {
                                    deplacementBas( lvl, currentLevel, caseY, caseX, screen );
                                }
                                else if ( mouseYrel < 0) {
                                    deplacementHaut( lvl, currentLevel, caseY, caseX, screen );
                                }
                            }
                            ///On test si l'on est au dernier niveau et que l'on a gagné pour réinitialiser les niveaux et afficher le nécessaire, on met que l'on ne joue plus
                            if ( passageNiveausup( lvl ) == true && ( currentLevel == NBNIVEAU ) ) {
                                currentLevel = 1;
                                afficheWithDelay( screen, "Images/winEndSprite.bmp", 3 );
                                afficheWithDelay( screen, "Images/menu", 3 );
                                isPlaying = false;
                            }
                        }
                    }
                }
                ///On remet nos booléens à faux puisque le déplacement est effectué
                isMoving = false;
                isMotion = false;
                godeplace = false;
            }
        }
    }
    SDL_FreeSurface( screen );
    SDL_Quit();
    return EXIT_SUCCESS;
}
