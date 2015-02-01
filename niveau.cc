/**
 * \file niveau.cc
 * \brief initialise le niveau et le met à jour
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include "niveau.h"

/*!
* \author Daurient Chloe et Chardan Anael
* \date 30 novembre 2013
* \brief Action qui crée le niveau
* On met à jour la grille, en fonction
* du niveau dans lequel on est.
* \param[in,out] n la structure niveau
* \param[in] gr la grille du jeu de type TGrille
*
*/

void createGrille( niveau &n, TGrille gr ) {
    ///Savoir dans quelle case du tableau on est en train d'écrire, et les indices pour le tableau de monstres
    int indiceMonstres = 0;
    int indiceObstacle = 0;
    ///On parcours tout notre tableau
    for( int i = 0; i < NB_LIGNE; i++ ) {
        for( int j = 0; j < NB_COLONNE; j++ ) {
            ///On prend chaque élément de notre grille graphique
            int element = gr[i][j];
            ///on met a jour la grille de notre niveau
            n.grille[i][j] = element;
            ///On conserve une copie que l'on ne touchera pas (pour checker les flèches surtout)
            n.grilleInitiale[i][j] = element;
            if ( ( element >= 10 ) && ( element < 20 ) ) {
                /// on est sur un monstre, élément - 10 sert à ce que l'on se repère dans nos états dans notre structure
                initMonstre( n.listeMonstre[indiceMonstres++], j, i, element - 10 );
            }
            if ( ( element >= 20 ) && ( element < 30 ) ) {
                /// on est sur un obstacle
                initObstacle( n.listeObstacle[indiceObstacle++], j, i, element - 20 );
            }
        }
    }
    ///On sait combien de monstre et d'obstacle l'on à dans notre niveau
    n.nbMonstres = indiceMonstres;
    n.nbObstacles = indiceObstacle;
}

/*!
* \author Daurient Chloe et Chardan Anael
* \date 30 novembre 2013
* \brief Action qui initialise le niveau
*
* \param[in,out] n la structure niveau
* \param[in,out] currentLvel niveau où l'on est
*
*/

void initNiveau( niveau &n, int &currentLevel ) {


    ///On check le niveau du level et on l'affecte à une grille
    if ( currentLevel == 1 ) {
        TGrille gr = {
            {DO, RI, RI, FG, RI},
            {RI, RI, RI, RI, RI},
            {RI, RI, RI, RI, RI},
            {RI, LI, RI, RI, RI},
            {RI, VI, RI, DO, RI},
            {RI, RI, RI, RI, RI},
            {RI, RI, RI, RI, RI},
            {RI, RI, RI, RI, RI},
            {RI, DO, RI, RI, RI}
        };
        createGrille( n, gr );
    }
    else if ( currentLevel == 2 ) {
        TGrille gr = {
            {RI, RI, RI, RI, RI},
            {RI, RI, RI, RI, RI},
            {RI, RI, RI, RI, RI},
            {RI, RI, RI, DO, RI},
            {RI, VI, RI, GL, DO},
            {RI, RI, RI, DO, RI},
            {RI, RI, RI, RI, RI},
            {RI, RI, RI, RI, RI},
            {RI, RI, RI, RI, RI}
        };
        createGrille( n,gr );
    }
    else if ( currentLevel == 3 ) {
        TGrille gr = {
            {VI, FD, FD, FD, FB},
            {FD, FD, FD, FB, FB},
            {FH, FD, FB, FB, FB},
            {FH, FH, RI, FB, FB},
            {FH, FH, RI, FB, FB},
            {FH, FH, RI, FB, FB},
            {FH, FH, DO, FB, FB},
            {FH, FH, FG, FG, FB},
            {FH, FG, FG, FG, FG}
        };
        createGrille( n,gr );
    }

    else if ( currentLevel == 4 ) {
        TGrille gr = {
            {LI, RI, VI, LI, DO},
            {DO, GL, RI, RI, GL},
            {FB, LI, LI, RI, RI},
            {GL, RI, LI, RI, RI},
            {RI, RI, LI, RI, RI},
            {DO, GL, LI, RI, RI},
            {LI, RI, RI, LI, RI},
            {RI, RI, LI, RI, FH},
            {RI, DO, RI, RI, LI}
        };
        createGrille( n,gr );
    }
    else if ( currentLevel == 5 ) {
        TGrille gr = {
            {DO, RI, RI, RI, DO},
            {FD, RI, DO, LI, RI},
            {RI, FB, RI, RI, RI},
            {RI, RI, RI, RI, RI},
            {PI, VI, RI, VI, RI},
            {RI, GL, RI, RI, FH},
            {LI, CL, RI, CL, LI},
            {PI, RI, RI, LI, RI},
            {RI, DO, RI, RI, DO}
        };
        createGrille( n, gr );
    }
    else if ( currentLevel == 6 ) {
        TGrille gr = {
            {RI, DO, LI, LI, RI},
            {LI, RI, RI, FD, FB},
            {RI, DO, RI, RI, RI},
            {PI, PI, FH, RI, RI},
            {VI, VI, GL, CL, LI},
            {RI, RI, LI, RI, RI},
            {RI, RI, DO, RI, FB},
            {RI, DO, RI, LI, RI},
            {DO, RI, RI, RI, FG}
        };
        createGrille( n,gr );
    }
}

/*!
* \author Daurient Chloe et Chardan Anael
* \date 30 novembre 2013
* \brief Action qui met à jour le niveau quand on joue (de la même manière que createGrille
*
*
* \param[in,out] n la structure niveau
*
*/
void updateNiveau( niveau &n ) {

    int indiceMonstres = 0;
    int indiceObstacle = 0;
    for( int i = 0; i < NB_LIGNE; i++ ) {
        for( int j = 0; j < NB_COLONNE; j++ ) {
            int element = n.grille[i][j];

            if ( ( element >= 10 ) && ( element < 20 ) ) {
                /// on est sur un monstre
                initMonstre( n.listeMonstre[indiceMonstres++], j, i, element - 10 );
            }
            if ( ( element >= 20 ) && ( element < 30 ) ) {
                /// on est sur un obstacle
                initObstacle( n.listeObstacle[indiceObstacle++], j, i, element - 20 );
            }
        }
    }
    n.nbMonstres = indiceMonstres;
    n.nbObstacles = indiceObstacle;
}

