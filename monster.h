#ifndef _MONSTER_H
#define _MONSTER_H

/**
 * \file monster.h
 * \brief initialise le monstre
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include <iostream>

using namespace std;

/*!
* \author Daurient Chloe et Chardan Anael
* \date 04 décembre 2013
* \enum etatMonstre
* \brief enumeration des etats du monstre
* Voici l'énumeration des différents états
* que peut prendre un monstre (standard (c'est à dire vivant), dormeur ou mort)
*
*/

enum etatMonstre {STANDARD, DORMEUR, DEAD};

/*!
* \author Daurient Chloe et Chardan Anael
* \date 02 décembre 2013
* \struct monstre monster.h
* \brief structure du monstre
* Voici la structure d'un monstre, d'un enum contenant l'état du monstre et
* de sa position dans le tableau (dans quelle ligne il est : "x" et dans quelle colonne : "y")
*
*/

struct monstre
{
    etatMonstre etat; ///L'état que le monstre peut prendre
    int x;
    int y;

};

void initMonstre( monstre &c, int x, int y, int etat );

#endif

