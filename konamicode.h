

#ifndef _KONAMICODE_H__
#define _KONAMICODE_H_

/**
 * \file konamicode.h
 * \brief notre code konami
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */
#include <iostream>

///Définition de nouveau type
typedef int konamicode[10];
typedef int konamicodeDebut[2];

bool checkKonamiCode( konamicode entry );
bool checkKonamiCodeDebut( konamicodeDebut entry );

#endif
