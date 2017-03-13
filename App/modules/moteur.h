/*!
* \file moteur.h
* \brief Fichier contenant les prototypes des fonctions du module moteur
* \author desrumaux
* \date 24/01/17
*/
#ifndef G_MOTEUR

#define G_MOTEUR

#include "outils.h"

/*!
 * \brief décalage des pions
 * @param plateau Plateau du jeu à accéder
 * @param colonnePiochee et lignePiochee de la case prise et colonneJouee et ligneJouee de la case de surbrillance choisie
 * @return ::0 si le décalage a bien été effectuer et -1 si y a eu un problème
 */
int decalage( int colonnePiochee, int lignePiochee, int colonneJouee, int ligneJouee ) ;

/*!
 * \brief appel des fonctions de test de victiore pour le mode 2v2 et 1V1
 * \brief /!\ si on est en mode 1V1 alors  joueurAllier = 0
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoire(int joueurCourant , int joueurAllier) ;



#endif

