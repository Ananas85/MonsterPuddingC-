/**
 * \file monster.cc
 * \brief initialise les monstres
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */


#include "monster.h"

/*!
* \author Daurient Chloe et Chardan Anael
* \date 03 décembre 2013
* \brief Action qui initialisent des monstres,  c'est à dire leur position dans la grille (x et y)
* et leur état.
*
* \param[in,out] c la structure monstre
* \param[in] y la ligne où on initialise le monstre
* \param[in] x la colonne où on initialise le monstre
* \param[in] etat l'énumeration contenant les différents états que peut prendre un monstre
*/

void initMonstre( monstre &c, int x, int y, int etat ) {
    c.x = x;
    c.y = y;
    if ( etat == 0 ) {
        c.etat = STANDARD;
    } else {
        c.etat = DORMEUR;
    }
}

