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
 * \brief Fonction qui vérifie que le cube voulant être pioché est disponible
 *
 * @param clicJoueur Clic du jouer sur l'affichage graphique (coordonnées en X et Y)
 * @return 0 si coup possible, -1 sinon
 */
int verifieSymbole(CLIC * clicJoueur);

/*!
 * \brief Fonction qui déterminer les cases où le joueur peut déposer le cube qu'il a pioché
 * @param casePiochee Coordonnées de la case que le joueur a pioché
 * @return 0
 */
int calculeSurbrillance(CASE * casePiochee);

#endif
