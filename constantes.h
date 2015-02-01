#ifndef _CONSTANTES_H
#define _CONSTANTES_H

/**
 * \file constantes.h
 * \brief initialise le niveau et le met à jour
 * \author Daurient Chloe et Chardan Anael
 * \date 30 novembre 2013
 *
 */

///La taille de notre écran
const int ECRAN_WIDTH = 320;
const int ECRAN_HEIGHT = 568;

///une case vide
const int RI = 00;
///un vivant
const int VI = 10;
///un dormeur
const int DO = 11;
///un livre
const int LI = 20;
///une glace
const int GL = 21;
///une fleche gauche
const int FG = 22;
///une fleche droite
const int FD = 23;
///une fleche haute
const int FH = 24;
///une fleche bas
const int FB = 25;
///monstre qui survole une fleche
const int FM = 26;
///Le pesticide
const int PI = 27;
///Le cloneur
const int CL = 28;

///Notre bouton play
const int PLAYX = 126;
const int PLAYY = 271;
const int PLAYW = 75;
const int PLAYH = 65;

///Notre bouton menu
const int MENUX = 18;
const int MENUY = 533;
const int MENUW = 35;
const int MENUH = 35;

///Notre bouton restart
const int RESTARTX = 200;
const int RESTARTY = 533;
const int RESTARTW = 35;
const int RESTARTH = 35;

///Notre bouton before
const int BEFOREX = 130;
const int BEFOREY = 533;
const int BEFOREW = 35;
const int BEFOREH = 35;

///Notre bouton rêgle
const int REGLEX = 16;
const int REGLEY = 509;
const int REGLEW = 35;
const int REGLEH = 35;

///Notre monstre vivant
const int VIVANTX = 5;
const int VIVANTY = 185;

///Notre monstre qui dort
const int DODOX = 5;
const int DODOY = 125;

///Notre livre
const int LIVREX = 5;
const int LIVREY = 65;

///Notre glace
const int GLACEX = 5;
const int GLACEY = 5;

///Notre fleche gauche
const int FLECHEGX = 65;
const int FLECHEGY = 245;

///Notre fleche droite
const int FLECHEDX = 5;
const int FLECHEDY = 245;

///Notre fleche haut
const int FLECHEHX = 125;
const int FLECHEHY = 245;

///Notre fleche bas
const int FLECHEBX = 183;
const int FLECHEBY = 245;

///Notre pesticide
const int PESTIX = 80;
const int PESTIY = 185;

///Notre cloneur
const int CLONEX = 183;
const int CLONEY = 185;

///Dimensions d'une case
const int CASEW = 55;
const int CASEH = 49;

///Informations relatives à la grille
const int MARGINLEFT = 18;
const int MARGINTOP = 50;
const int PADDINGRIGHT = 2;
const int PADDINGBOTTOM = 3;

///Informations relatives à notre niveau
const int NB_MONSTRE_MAX_PAR_NIVEAU = 45;
const int NB_OBSTACLE_MAX_PAR_NIVEAU = 45;
const int NB_LIGNE = 9;
const int NB_COLONNE = 5;

const int NBNIVEAU = 6;

#endif

