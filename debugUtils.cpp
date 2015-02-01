/**
 * \file debugUtils.cc
 * \brief methode pour afficher des choses dans le terminal (en cours)
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

#include "debugUtils.h"

    /*!
     * \author Daurient Chloe et Chardan Anael
     * \date 16 décembre 2013
     * \brief Méthode de débug
     * Avec des Niveau de débugage pour ne pas afficher tout le temps des cout.
     *
     * \param[in] message Chaine de caractères
     * \param[in] lvl importance de notre message
     */
void monsterprint( string message, int lvl ) {
    ///Constantes pour les niveaux d'importance
    if ( DEBUG_LVL >= lvl ) {
        cout    << message << endl;
    }
}
