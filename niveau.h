#ifndef _NIVEAU_H_
#define _NIVEAU_H_

/**
 * \file niveau.h
 * \brief gère les niveaux
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include <iostream>
#include "constantes.h"
#include "monster.h"
#include "obstacle.h"

typedef int TGrille[NB_LIGNE][NB_COLONNE];

/*!
* \author Daurient Chloe et Chardan Anael
* \date 30 novembre 2013
* \struct niveau niveau.h
* \brief structure du niveau
* Voici la structure d'un niveau, composé d'une grille de jeu,
* d'un tableau de monstres, d'un tableau d'obstacles, d'un nombre de monstre,
* d'un nombre d'obstacles.
*
*/

//Voici la structure d'un niveau, composé d'une grille de jeu, d'un tableau de monstres, d'un tableau d'obstacles, d'un nombre de monstre, d'un nombre d'obstacles
struct niveau {
    // definition de la grille du jeu de type TGrille qui s'appelle grille
    TGrille grille;
    //Un tableau de monstre pour savoir combien de monstre maximum on à le droit par niveau
    monstre listeMonstre[NB_MONSTRE_MAX_PAR_NIVEAU];
    //Pareil pour les obstacles
    obstacle listeObstacle[NB_OBSTACLE_MAX_PAR_NIVEAU];
    
    TGrille grilleInitiale; ///Grille du niveau que l'on ne modifie jamais juste pour les flèches

    //Il à donc un nombre de monstre que l'on prédéfini
    int nbMonstres;
    //Il à dont un nombre d'obstacle que l'on prédéfini
    int nbObstacles;
};

void initNiveau( niveau &n, int &no );
void updateNiveau( niveau &n );

#endif

