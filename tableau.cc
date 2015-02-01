/**
 * \file tableau.cc
 * \brief Gère tous nos déplacements
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include "tableau.h"

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 * \brief regarde le nombre restant de monstres endormis
 *
 * \param[in] lvl niveau nommé lvl
 * \return true s'il y en a moins que un
 */
bool passageNiveausup( niveau lvl ) {
    ///On met les nombres de monstres qui dorment à zéro
    int nbMonstresDo = 0;

    ///On parcourt tout notre tableau
    for ( int i = 0; i < NB_LIGNE; i++ ) {
        for ( int j = 0; j< NB_COLONNE; j++ ) {
            ///Si l'on rencontre un monstre qui dort on incrémente le nombre de dormeur
            if ( lvl.grille[i][j] == DO ) {
                nbMonstresDo++;
            }
        }
    }
    ///Si le nombre de monstre qui dorment est inférieur à un on dit que l'on peut changer de niveau
    return ( nbMonstresDo < 1 );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 * \brief Fonction qui regarde le nombre restant de monstres vivant
 *
 * \param[in] lvl niveau nommé lvl
 * \return true s'il y en a plus que un
 */
bool checkMonstreVivant( niveau lvl ) {
    int nbMonstreVi = 0;

    ///On parcourt tout dans notre tableau
    for ( int i = 0; i < NB_LIGNE; i++ ) {
        for ( int j = 0; j < NB_COLONNE; j++ ) {
            ///Si l'on rencontre un monstre qui est vivant on met ++
            if ( lvl.grille[i][j] == VI ) {
                nbMonstreVi++;
            }
        }
    }
    ///Si le nombre de monstre qui dorment est supérieur à un on dit que ce n'est pas le dernier
    return ( nbMonstreVi > 1 );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 * \brief Fonction qui regarde le contenu de la case d'à côté et voit si on ne sort pas du tableau
 *
 * \param[in] lvl niveau nommé lvl
 * \param[in] y la ligne
 * \param[in] x la colonne
 * \return true s'il y en a plus
 */
int scanCase( niveau lvl, int y, int x ) {
    if ( ( x == -1 ) || ( x == NB_COLONNE ) ) {
        return -1;
    }
    if ( ( y == -1 ) || ( y == NB_LIGNE ) ) {
        return -1;
    }
    return lvl.grille[y][x];
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 * \brief regarde si le contenu de la case est déplaçable
 *
 * \param[in] lvl niveau nommé lvl
 * \param[in] y la ligne où est situé le monstre que l'on souhaite scanner
 * \param[in] x la colonne où est situé le monstre que l'on souhaite scanner
 * \return true si la case scanné contient un monstre déplaçable et false sinon
 */

bool caseValide( niveau lvl, int y, int x ) {
    return ( ( lvl.grille[y][x] == VI ) || ( lvl.grille[y][x] == FM ) );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 * \brief fonction qui reveille un monstre endormis et passe au niveau supérieur
 *
 * \param[in,out] lvl niveau nommé lvl
 * \param[in,out] no niveau où l'on est
 * \param[in] y la ligne où est situé le monstre que l'on souhaite scanner
 * \param[in] x la colonne où est situé le monstre que l'on souhaite scanner
 * \param[in] parentSurface surface de l'écran
 * \return le niveau dans lequel on est situé dans le jeu après être passé au niveau supérieur
 */

int reveilleMonstre( niveau &lvl, int &currentLevel, int y, int x, SDL_Surface *parentSurface ) {

    ///On scan à gauche et si c'est un dormeur on le réveille
    if ( ( scanCase( lvl, y, x - 1 ) ) == DO ) {
        lvl.grille[y][x - 1 ] = VI;
        updateNiveau( lvl );
    }

    ///On scan à droite et si c'est un dormeur on le réveille
    if ( ( scanCase( lvl, y, x + 1 ) ) == DO) {
        lvl.grille[y][x + 1] = VI;
        updateNiveau( lvl );
    }

    ///On scan en haut et si c'est un dormeur on le réveille
    if ( ( scanCase( lvl, y - 1, x ) ) == DO ) {
        lvl.grille[y - 1][x] = VI;
        updateNiveau( lvl );
    }

    ///On scan en bas et si c'est un dormeur on le réveille
    if ( ( scanCase( lvl, y + 1, x ) ) == DO ) {
        lvl.grille[y + 1][x] = VI;
        updateNiveau( lvl );
    }

    ///On regarde si il reste des monstres endormis
    if ( passageNiveausup( lvl ) && currentLevel < NBNIVEAU ) {
        cout << "nouveau level"<< endl;
        monsterprint( "nouveau level", 15);
        ///Si on est en dessous du nombre de niveau on passe au suivant
        currentLevel++;
        ///On l'initialise
        initNiveau( lvl, currentLevel );
        ///On affiche le screen du fin de niveau
        afficheWithDelay( parentSurface, "Images/winSprite.bmp", 3 );
    }
    ///On affiche le nouveau niveau
    plateauAfficheNiveau( lvl, parentSurface );
    ///On renvoit le numéro du niveau sur lequel on joue
    return currentLevel;
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 16 décembre 2013
 * \brief Action qui casse la glace à côté d'un monstre donné
 *
 * \param[in,out] lvl niveau nommé lvl
 * \param[in,out] no niveau où l'on est
 * \param[in] y la ligne où est situé le monstre que l'on souhaite scanner
 * \param[in] x la colonne où est situé le monstre que l'on souhaite scanner
 * \param[in] deltaX le déplacement que l'on fait en colonne
 * \param[in] deltaY le déplacement que l'on fait en ligne
 * \param[in] parentSurface surface de l'écran
 */
void gestionGlace( niveau &lvl, int &currentLevel, int y, int x, int deltaX, int deltaY, SDL_Surface *parentSurface ) {
    ///On vide la case où la glace était présente
    lvl.grille[y + deltaY][x + deltaX] = RI;
    ///On met à jour notre lvl
    updateNiveau( lvl );
    ///On affiche le level
    plateauAfficheNiveau( lvl , parentSurface );
    ///Si c'était une flèche monstre, on continu le mouvement dans le sens de la flèche
    if (lvl.grille[y][x]==FM) {
        deplacement( lvl, currentLevel, y , x, deltaX, deltaY, parentSurface );
    }
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 16 décembre 2013
 * \brief Action qui tue notre monstre si on touche le pesticide
 *
 * \param[in,out] lvl niveau nommé lvl
 * \param[in,out] no niveau où l'on est
 * \param[in] y la ligne où est situé le monstre que l'on souhaite scanner
 * \param[in] x la colonne où est situé le monstre que l'on souhaite scanner
 * \param[in] deltaX le déplacement que l'on fait en colonne
 * \param[in] deltaY le déplacement que l'on fait en ligne
 * \param[in] parentSurface surface de l'écran
 */
void gestionPesticide( niveau &lvl, int &currentLevel, int y, int x, int deltaX, int deltaY, SDL_Surface *parentSurface ) {
    ///On regarde combien il nous reste de vivant et si ce n'est pas le dernier, on le tue, sinon on recommence le niveau
    if ( checkMonstreVivant( lvl ) ) {
        lvl.grille[y][x] = RI;
    } else {
        initNiveau( lvl, currentLevel );
    }
    updateNiveau( lvl );
    plateauAfficheNiveau( lvl, parentSurface );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 16 décembre 2013
 * \brief Action qui clone un monstre donné en entrée
 *
 * \param[in,out] lvl niveau nommé lvl
 * \param[in,out] no niveau où l'on est
 * \param[in] y la ligne où est situé le monstre que l'on souhaite scanner
 * \param[in] x la colonne où est situé le monstre que l'on souhaite scanner
 * \param[in] deltaX le déplacement que l'on fait en colonne
 * \param[in] deltaY le déplacement que l'on fait en ligne
 * \param[in] parentSurface surface de l'écran
 */
void gestionCloneur( niveau &lvl, int &currentLevel, int y, int x, int deltaX, int deltaY, SDL_Surface *parentSurface ) {
    ///On met tous nos déplacement à faut
    bool isDroite = false;
    bool isGauche = false;
    bool isHaut = false;
    bool isBas = false;

    /// droite
    if ( deltaX == 1  && deltaY == 0 )  { isDroite = true; }
    /// gauche
    if ( deltaX == -1 && deltaY == 0 ) { isGauche = true; }
    /// haut
    if ( deltaX == 0  && deltaY == -1 ) { isHaut = true; }
    /// bas
    if ( deltaX == 0  && deltaY == 1 )  { isBas = true; }

    ///On met que l'on a pas cloné
    bool hasCloned = false;
    ///On regarde ce qu'il se passe selon le déplacement en entrée (même schéma pour les 4).
    if ( isDroite ) {
        /// droite
        if ( RI == scanCase( lvl, y + deltaY, x + deltaX + 1 ) ) {
            lvl.grille[y + deltaY][x + deltaX + 1] = VI;
            hasCloned = true;
        }

        /// bas
        if ( RI == scanCase( lvl, y + deltaY + 1, x + deltaX ) ) {
            lvl.grille[y + deltaY + 1][x + deltaX] = VI;
            hasCloned = true;
        }

        /// haut
        if ( RI == scanCase( lvl, y + deltaY - 1, x + deltaX ) ) {
            lvl.grille[y + deltaY - 1][x + deltaX] = VI;
            hasCloned = true;
        }


        ///Si l'on a cloné
        if ( hasCloned ) {
            /// on vide la case courante
            lvl.grille[y][x] = RI;
            updateNiveau( lvl );
            plateauAfficheNiveau( lvl, parentSurface );

            /// deplacement checkera la validite
            /// case de droite vers la droite
            deplacement( lvl, currentLevel, y + deltaY , x + deltaX + 1, 1, 0, parentSurface );
            /// case du bas vers le bas
            deplacement( lvl, currentLevel, y + deltaY + 1 , x + deltaX, 0, 1, parentSurface );
            /// case du haut vers le haut
            deplacement( lvl, currentLevel, y + deltaY - 1 , x + deltaX, 0, -1, parentSurface );
        }
    }

    ///Si c'est gauche
    if ( isGauche ) {
        /// gauche
        if ( RI == scanCase( lvl, y + deltaY, x + deltaX - 1 ) ) {
            lvl.grille[y + deltaY][x + deltaX - 1] = VI;
            hasCloned = true;
        }

        /// bas
        if ( RI == scanCase( lvl, y + deltaY + 1, x + deltaX ) ) {
            lvl.grille[y + deltaY + 1][x + deltaX] = VI;
            hasCloned = true;
        }

        /// haut
        if ( RI == scanCase( lvl, y + deltaY - 1, x + deltaX ) ) {
            lvl.grille[y + deltaY - 1][x + deltaX] = VI;
            hasCloned = true;
        }
        if ( hasCloned ) {
            /// on vide la case courante
            lvl.grille[y][x] = RI;
            updateNiveau( lvl );
            plateauAfficheNiveau( lvl, parentSurface );
            /// deplacement checkera la validite
            /// case de gauche vers la gauche
            deplacement( lvl, currentLevel, y + deltaY , x + deltaX - 1, -1, 0, parentSurface );
            /// case du bas vers le bas
            deplacement( lvl, currentLevel, y + deltaY + 1 , x + deltaX, 0, 1, parentSurface );
            /// case du haut vers le haut
            deplacement( lvl, currentLevel, y + deltaY - 1 , x + deltaX, 0, -1, parentSurface );
        }
    }

    ///Si c'est haut
    if ( isHaut ) {
        /// gauche
        if ( RI == scanCase( lvl, y + deltaY, x + deltaX - 1 ) ) {
            lvl.grille[y + deltaY][x + deltaX - 1] = VI;
            hasCloned = true;
        }

        /// droite
        if ( RI == scanCase( lvl, y + deltaY, x + deltaX + 1 ) ) {
            lvl.grille[y + deltaY][x + deltaX + 1] = VI;
            hasCloned = true;
        }
        /// haut
        if ( RI == scanCase( lvl, y + deltaY - 1, x + deltaX ) ) {
            lvl.grille[y + deltaY - 1][x + deltaX] = VI;
            hasCloned = true;
        }
        if ( hasCloned ) {
            /// on vide la case courante
            lvl.grille[y][x] = RI;
            updateNiveau( lvl );
            plateauAfficheNiveau( lvl, parentSurface );
            /// deplacement checkera la validite
            /// case de gauche vers la gauche
            deplacement( lvl, currentLevel, y + deltaY , x + deltaX - 1, -1, 0, parentSurface );
            /// case de droite vers la droite
            deplacement( lvl, currentLevel, y + deltaY , x + deltaX + 1, 1, 0, parentSurface );
            /// case du haut vers le haut
            deplacement( lvl, currentLevel, y + deltaY - 1 , x + deltaX, 0, -1, parentSurface );
        }
    }

    ///Si c'est bas
    if ( isBas ) {
        /// gauche
        if ( RI == scanCase( lvl, y + deltaY, x + deltaX - 1 ) ) {
            lvl.grille[y + deltaY][x + deltaX - 1] = VI;
            hasCloned = true;
        }

        /// droite
        if ( RI == scanCase( lvl, y + deltaY, x + deltaX + 1 ) ) {
            lvl.grille[y + deltaY][x + deltaX + 1] = VI;
            hasCloned = true;
        }
        /// bas
        if ( RI == scanCase( lvl, y + deltaY + 1, x + deltaX ) ) {
            lvl.grille[y + deltaY + 1][x + deltaX] = VI;
            hasCloned = true;
        }
        if ( hasCloned ) {
            /// on vide la case courrante
            lvl.grille[y][x] = RI;
            updateNiveau( lvl );
            plateauAfficheNiveau( lvl, parentSurface );
            /// deplacement checkera la validite
            /// case de gauche vers la gauche
            deplacement( lvl, currentLevel, y + deltaY , x + deltaX - 1, -1, 0, parentSurface );
            /// case de droite vers la droite
            deplacement( lvl, currentLevel, y + deltaY , x + deltaX + 1, 1, 0, parentSurface );
            /// case du bas vers le bas
            deplacement( lvl, currentLevel, y + deltaY + 1 , x + deltaX, 0, 1, parentSurface );
        }
    }
}


/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 02 décembre 2013
 * \brief Action qui regarde si la case est valide, si oui, déplace la case que l'on choisi
 * vers la direction deltaX/deltaY, réveille le monstre. Ou recommence le niveau si on dépasse le tableau.
 *
 * \param[in,out] lvl niveau nommé lvl
 * \param[in,out] no niveau où l'on est
 * \param[in] y la ligne où est situé le monstre que l'on souhaite scanner
 * \param[in] x la colonne où est situé le monstre que l'on souhaite scanner

 * \param[in] deltaX le déplacement que l'on fait en colonne
 * \param[in] deltaY le déplacement que l'on fait en ligne
 * \param[in] parentSurface surface de l'écran
 */

void deplacement( niveau &lvl, int &currentLevel, int y, int x, int deltaX, int deltaY, SDL_Surface *parentSurface ) {

    ///On initialise nos déplacements
    bool isDroite = false;
    bool isGauche = false;
    bool isHaut = false;
    bool isBas = false;

    ///On paramètre nos modes de déplacements

    /// droite
    if ( deltaX == 1  && deltaY == 0 )  { isDroite = true; }
    /// gauche
    if ( deltaX == -1 && deltaY == 0 ) { isGauche = true; }
    /// haut
    if ( deltaX == 0  && deltaY == -1 ) { isHaut = true; }
    /// bas
    if ( deltaX == 0  && deltaY == 1 )  { isBas = true; }

    ///On check la validité de notre case
    if ( caseValide( lvl, y, x ) ) {
        ///On regarde la case suivante selon le mouvement d'entrée
        int nextCase = scanCase( lvl, y + deltaY, x + deltaX );
        ///On inclut un compteur de coup pour pouvoir briser la glace
        int cptcoup = 0;
        ///Tant que la case suivante est vide
        while ( nextCase == RI ) {
            /// on increment le nb coup
            cptcoup++;

            ///Si notre case était une flèche monstre, on remet la flèche correspondante (évidente selon le déplacement d'entrée)
            ///Sinon on vide notre case courante
            if ( lvl.grille[y][x] == FM ) {
                if ( isDroite ) {
                    lvl.grille[y][x] = FD;
                }
                if ( isGauche ) {
                    lvl.grille[y][x] = FG;
                }
                if ( isHaut ) {
                    lvl.grille[y][x] = FH;
                }
                if ( isBas ) {
                    lvl.grille[y][x] = FB;
                }
            } else {
                /// on vide celle courante
                lvl.grille[y][x] = RI;
            }

            /// On met donc à l'état vivant notre case de destination
            lvl.grille[y + deltaY][x + deltaX] = VI;

            ///On update
            updateNiveau( lvl );
            ///On affiche
            plateauAfficheNiveau( lvl, parentSurface );
            ///On met à jour la case avec laquelle on joue
            x = x + deltaX;
            y = y + deltaY;
            ///On scan la case suivante selon le déplacement de départ
            nextCase = scanCase( lvl, y + deltaY, x + deltaX );
        }

        ///Gestion des flèches selon ce qui est notre prochaine case
        if ( nextCase == FG || nextCase == FD || nextCase == FB || nextCase == FH ) {
            ///On met la case sur laquelle on était l'état initiale de la grille de ce niveau (si c'est deux flèches côte à côte)
            ///Sinon on met un cloneur si c'était un cloneur sinon un case vide
            if ( ( lvl.grilleInitiale[y][x] == FG ) || ( lvl.grilleInitiale[y][x] == FD )  || ( lvl.grilleInitiale[y][x] == FB )  || ( lvl.grilleInitiale[y][x] == FH ) ) {
                lvl.grille[y][x] = lvl.grilleInitiale[y][x];
            } else if ( lvl.grilleInitiale[y][x] == CL ){
                lvl.grille[y][x] = lvl.grilleInitiale[y][x];
            } else {
                lvl.grille[y][x] = RI;
            }
            lvl.grille[y + deltaY][x + deltaX] = FM;
            updateNiveau( lvl );
            plateauAfficheNiveau( lvl, parentSurface );
        }


        /// On rencontre un flèche sur la prochaine case, on lance la procédure de déplacement pour cette case
        if ( nextCase == FG ) {
            deplacement( lvl, currentLevel, y + deltaY , x + deltaX, -1, 0, parentSurface );
        }
        if ( nextCase == FD ) {
            deplacement( lvl, currentLevel, y + deltaY, x + deltaX, 1, 0, parentSurface );
        }
        if ( nextCase == FH ) {
            deplacement( lvl, currentLevel, y + deltaY, x + deltaX, 0, -1, parentSurface );
        }
        if ( nextCase == FB ) {
            deplacement( lvl, currentLevel, y + deltaY, x + deltaX, 0, 1, parentSurface );
        }


        ///On peut briser la glace seulement si notre pion s'est déjà déplacé dans le même sens, attention si
        ///On appelle la fonction de gestion de la glace
        if ( nextCase == GL && ( cptcoup > 0 || lvl.grille[y][x] == FM) ) {
            gestionGlace( lvl, currentLevel, y, x, deltaX, deltaY, parentSurface );
        }

        ///Si l'on rencontre un pesticide on appelle la gestion pesticide
        if ( nextCase == PI ) {
            gestionPesticide( lvl, currentLevel, y, x, deltaX, deltaY, parentSurface );
        }

        ///Si l'on rencontre un cloneur, on appelle la gestion de cloneur
        if ( nextCase == CL ) {
            gestionCloneur( lvl, currentLevel, y, x, deltaX, deltaY, parentSurface );
        }

        ///Si on dépasse le tableau dans la direction dans laquelle on va, on recommence notre niveau
        ///Sinon on lance la procédure de réveille
        if ( nextCase == -1 ) {
            initNiveau( lvl, currentLevel );
            plateauAfficheNiveau( lvl, parentSurface );
        } else if ( lvl.grille[y][x] == VI ) {
            reveilleMonstre( lvl, currentLevel, y, x, parentSurface );
        }

    }
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 16 décembre 2013
 * \brief Sucre pour se déplacer à gauche ( deltaX -1, deltaY 0, voir la methode deplacement()
 * \see deplacement
 */
void deplacementGauche( niveau &lvl, int &currentLevel, int y, int x, SDL_Surface *parentSurface ) {
    deplacement(lvl, currentLevel, y, x, -1, 0, parentSurface );
}


/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 16 décembre 2013
 * \brief Sucre pour se déplacer à droite ( deltaX 1, deltaY 0, voir la methode deplacement()
 * \see deplacement
 */
void deplacementDroite( niveau &lvl, int &currentLevel, int y, int x, SDL_Surface *parentSurface ) {
    deplacement(lvl, currentLevel, y, x, 1, 0, parentSurface );
}
/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 16 décembre 2013
 * \brief Sucre pour se déplacer en haut ( deltaX 0, deltaY -1, voir la methode deplacement()
 * \see deplacement
 */

void deplacementHaut(niveau &lvl, int&currentLevel, int y, int x, SDL_Surface *parentSurface) {
    deplacement(lvl, currentLevel, y, x, 0, -1, parentSurface );
}

/*!
 * \author Daurient Chloe et Chardan Anael
 * \date 16 décembre 2013
 * \brief Sucre pour se déplacer en bas ( deltaX 1, deltaY 1, voir la methode deplacement()
 * \see deplacement
 */
void deplacementBas(niveau &lvl, int&currentLevel, int y, int x, SDL_Surface *parentSurface) {
    deplacement(lvl, currentLevel, y, x, 0, 1, parentSurface );
}
