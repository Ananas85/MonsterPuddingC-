
#ifndef _DEBUGUTILS_H
#define _DEBUGUTILS_H

/**
 * \file debugUtils.h
 * \brief gère nos debugs
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */
#include <iostream>
#include <string>

using namespace std;

///Constante uniquement utilisé pour cette méthode
const int DEBUG_LVL = 10;

void monsterprint( string message, int lvl );

#endif
