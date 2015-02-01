#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

/**
 * \file obstacle.h
 * \brief initialise les obstacles
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include <iostream>


using namespace std;

/*!
* \author Daurient Chloe et Chardan Anael
* \date 04 décembre 2013
* \enum typeObstacle
* \brief enumeration du type d'obstacle
* Voici l'énumeration des différents type que peut prendre un obstacle (livre, glace, ...)
*
*/

enum typeObstacle{ LIVRE, GLACE, FLECHEG, FLECHED, FLECHEH, FLECHEB, FLECHEM, PESTI, CLONE};

/*!
* \author Daurient Chloe et Chardan Anael
* \date 03 décembre 2013
* \struct obstacle obstacle.h
* \brief structure d'un obstacle
* Voici la structure d'un obstacle, d'un enum contenant l'état de l'obstacle et
* de sa position dans le tableau (dans quelle ligne il est : "x" et dans quelle colonne : "y")
*
*/

struct obstacle {
    typeObstacle type;
    int x;
    int y;

};

void initObstacle( obstacle &c, int x, int y, int type );


#endif

