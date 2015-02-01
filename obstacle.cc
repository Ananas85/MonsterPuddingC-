/**
 * \file obstacle.cc
 * \brief initialise les obstacles
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include "obstacle.h"

/*!
* \author Daurient Chloe et Chardan Anael
* \date 03 décembre 2013
* \brief Actions qui initialisent des obstacles, c'est à dire leur position dans la grille (x et y)
* et leur type.
*
* \param[in,out] o la structure obstacle
* \param[in] y la ligne où on initialise l'obstacle
* \param[in] x la colonne où on initialise l'obstacle
* \param[in] type l'énumeration contenant les différents états que peut prendre un obstacle
*/

void initObstacle( obstacle &o, int x, int y, int type ) {
    o.x = x;
    o.y = y;
    if ( type == 0 ) {
        o.type = LIVRE;
    } else if ( type == 1 ) {
        o.type = GLACE;
    } else if ( type == 2 ) {
        o.type = FLECHEG;
    } else if ( type == 3 ) {
        o.type = FLECHED;
    } else if ( type == 4 ) {
        o.type = FLECHEH;
    } else if ( type == 5 ) {
        o.type = FLECHEB;
    } else if ( type == 6 ) {
        o.type = FLECHEM;
    } else if ( type == 7 ) {
        o.type = PESTI;
    } else if ( type == 8) {
        o.type = CLONE;
    }
}

