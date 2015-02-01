/**
 * \file monster.cc
 * \brief initialise les monstres
 * \author Daurient Chloe et Chardan Anael
 * \date 10 décembre 2013
 *
 */


#include "konamicode.h"


/*!
* \author Daurient Chloe et Chardan Anael
* \date 03 décembre 2013
* \brief Fonction qui regarde la validité de notre code Konami
*
* \param[in] entry le tableau d'entrée de type Konamicode
*/

bool checkKonamiCode( konamicode entry ) {
    ///A quelle touche correspond le code Konami selon la table ascii
    konamicode trueCode = {273,273,274,274,276,275,276,275,98,97};

    ///On parcourt le tableau
    for(int i=0;i<10;i++) {
        if ( entry[i] != trueCode[i] ) {
            return false;
        }
    }

    /// On remet notre tableau à zéro
    for( int i=0; i<10; i++ ) {
        entry[i] = 0;
    }
    return true;
}

/*!
* \author Daurient Chloe et Chardan Anael
* \date 03 décembre 2013
* \brief Fonction qui regarde  si l'on a tapé le bon début
*
* \param[in] entry le tableau d'entrée de début de type KonamicodeDebut

*/bool checkKonamiCodeDebut( konamicodeDebut entry ) {
    konamicodeDebut trueCode = {273,273};
    for( int i=0; i<2; i++ ) {
        if ( entry[i] != trueCode[i] ) {
            return false;
        }
    }

    entry[0] = 0;
    entry[1] = 0;
    return true;
}
