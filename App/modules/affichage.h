/*!
* \file affichage.h
* \brief Fichier contenant les prototypes des fonctions du module affichage
* \author desrumaux
* \date 24/01/17
*/
#ifndef G_AFFICHAGE

#define G_AFFICHAGE

#include "outils.h"
#include "../lib/GfxLib.h"

/*!
 * \brief Fonction de gestion des événements
 *
 * Appelée automatiquement par le système dès qu'un événement survient
 *
 * @param EvenementGfx
 */
void gestionEvenement(EvenementGfx evenement);

/*!
 * \brief Fonction qui permet d'afficher le plateau suivant les coordonnées envoyées
 *
 * @param coordonneesPlateau Pointeur vers un tableau contenant les coorodonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 */
void affichePlateau(int *coordonneesPlateau);

/*!
 * \brief Fonction qui permet de calculer le pas dans la grille d'un plateau
 *
 * Calcul depuis les coordonnées le pas de chaque case.
 *
 * @param coordonneesPlateau Pointeur vers un tableau contenant les coorodonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 *
 * @return Pas de chaque case
 */
float calculePas(int *coordonneesPlateau);

/*!
 * \brief Fonction qui permet d'afficher la grile de jeu.
 *
 * @param coordonneesPlateau Pointeur vers un tableau contenant les coorodonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 */
void afficheGrille(int *coordonneesPlateau);

/*!
 * \brief Fonction qui permet d'afficher le symbole correspondant à la case parcourue dans le plateau de jeu
 *
 * @param pas Pas de la grille
 * @param case_jeu Case à traiter
 * @param joueur Joueur courant
 */
void afficheSymbole(float pas, CASE case_jeu, int joueur);

#endif
