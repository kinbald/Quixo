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
#include "../lib/BmpLib.h"

/*!
 * \brief Fonction qui permet d'afficher le plateau suivant les coordonnées envoyées
 *
 * @param coordonneesPlateau Pointeur vers un tableau contenant les coorodonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 * @param LARGEURFenetre Largeur de la fenêtre
 * @param HAUTEURFenetre Hauteur de la fenêtre
 *
 */
void affichePlateau(int *coordonneesPlateau, int LARGEURFenetre, int HAUTEURFenetre);

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
 * \brief Fonction qui permet d'afficher la grille de jeu.
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
 * @param lectureCase Case (plateau) où la flèche doit être placée
 */
void afficheSymbole(float pas, CASE * case_jeu, int joueur, CASE * lectureCase);

/*!
 * \brief Fontion qui permet d'afficher une croix de taille pas/3 aux coordonnées de *case_jeu
 *
 * @param case_jeu Case du jeu ciblée pour la croix (coordonnées en X et Y)
 * @param pas Pas des cases
 */
void afficheCroix(CASE * case_jeu, int pas);

/*!
 * \brief Fontion qui permet d'afficher une croix de taille pas/3 aux coordonnées de *case_jeu avec un point
 *
 * @param case_jeu Case du jeu ciblée pour la croix (coordonnées en X et Y)
 * @param pas Pas des cases
 * @param direction Direcion choisie pour le point (0: Droit, 1: Bas, 2: Gauche, 3: Haut)
 */
void afficheCroixPoint(CASE * case_jeu, int pas, int direction);

/*!
 * \brief Fonction qui permet de dessiner un disque sur l'affichage
 * @param case_jouee Case du plateau (en pixels)
 * @param rayon Rayon du disque (en pixels)
 */
void afficheDisque(CASE * case_jouee, float rayon);

/*!
 * \brief Fonction qui permet d'afficher un cercle de rayon donné.
 *
 * @param case_jouee Coordonnées de la case pour placer le cercle
 * @param rayon Rayon du cercle
 */
void afficheRond(CASE * case_jouee, float rayon);

/*!
 * \brief Fonction qui permet d'afficher un cercle de rayon donné avec un point suivant une direction
 *
 * @param case_jouee Coordonnées de la case pour placer le cercle
 * @param rayon Rayon du cercle
 * @param direction Direcion choisie pour le point (0: Droit, 1: Bas, 2: Gauche, 3: Haut)
 */
void afficheRondPoint(CASE * case_jouee, float rayon, int direction);

/*!
 * \brief Fonction qui permet de gérer les clics sur l'affichage graphique en fonction du menu
 *
 * @param retourClic Case utilisée lors d'un clic sur plateau
 * @param clicSouris Clic du joueur sur l'affichage graphique (coordonnées en X et Y) et menu courant
 * @param coordonneesPlateau Coordonnées du plateau de jeu lors d'un clic dans la partie
 * @param LARGEURFenetre
 * @param HAUTEURFenetre
 * @return Action à effectuer
 */
int recupereClicAffichage(CASE * retourClic, CLIC * clicSouris, int *coordonneesPlateau, int LARGEURFenetre, int HAUTEURFenetre);

/*!
 * \brief Fonction qui permet de gérer un clic sur le menuPartie
 * @param retourClic Case qui sera modifiée si le joueur clique sur le plateau
 * @param clicSouris Clic du joueur sur l'affichage graphique (coordonnées en X et Y) et menu courant
 * @param coordonneesPlateau Coordonnées du plateau de jeu lors d'un clic dans la partie
 * @return Action à effectuer
 */
int clicPlateau(CASE * retourClic, CLIC * clicSouris, int *coordonneesPlateau);

/*!
 * \brief Fonction qui permet de renvoyer l'action à effectuer après un clic dans le plateau de jeu
 *
 * @param clic
 * @param etatMenu
 * @return
 */
int gereEtatsClic(CASE * clic, int etatMenu);

/*!
 * \brief Fonction qui permet d'afficher une flèche sur les cases où le joueur peut jouer après une pioche.
 * @param case_jouee Case en pixels où la flèche doit être placée
 * @param pas Pas de la case
 * @param lectureCase Case (plateau) où la flèche doit être placée
 */
void afficheSurbrillance(CASE * case_jouee, float pas, CASE * lectureCase);

/*!
 * \brief Fonction qui redimensionne automatiquement pour garder un ratio minimal
 */
void redimensionnementForce(int menu);

/*!
 * \brief Fonction qui affiche le menu où le joueur choisit son mode de jeu
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @return 0 pour ok, -1 pour ko
 */
int afficheMenuPrincipal(int LARGEURFenetre, int HAUTEURFenetre);

/*!
 * \brief Fonction qui affiche le menu où le joueur choisit son symbole
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @return 0 pour ok, -1 pour ko
 */

int afficheMenuSelection(int LARGEURFenetre, int HAUTEURFenetre);

/*!
 * \brief Fonction qui affiche les règles du jeu
 * @param image Image bmp à afficher
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @return 0 pour ok, -1 pour ko
 */
int afficheRegles(DonneesImageRGB * image, int LARGEURFenetre, int HAUTEURFenetre);

 /*!
  * \brief Fonction qui gère le clic dans les menus à l'aide des boutons
  * @param clicSouris Clic du joueur sur l'affichage graphique (coordonnées en X et Y) et menu courant
  * @param LARGEURFenetre largeur de la fenêtre
  * @param HAUTEURFenetre hauteur de la fenêtre
  * @return Action à effectuer
  */
int clicMenu(CLIC * clicSouris, int LARGEURFenetre, int HAUTEURFenetre);

/*!
 * \brief Fonction qui redirige vers la bonne fonction d'affichage en fonction du menu envoyé.
 *
 * @param menu Menu qui doit être affiché
 * @param LargeurFenetreCourante Largeur de la fenêtre
 * @param HauteurFenetreCourante Hauteur de la fenêtre
 * @param coordonneesGrille Pointeur vers un tableau contenant les coorodonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 * @param imageRegles Pointeur vers l'image qui s'affiche dans le menu des règles de jeu
 * @param joueurCourant Joueur courant de la partie
 * @return 0
 */
int gestionAffichage(int menu, int *coordonneesPlateau, int LARGEURFenetre, int HAUTEURFenetre, DonneesImageRGB * imageRegles, int joueurCourant);

/*!
 * \brief Fonction qui affiche les boutons dans le menu partie
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @return 0
 */
int afficheBouton(int LARGEURFenetre, int HAUTEURFenetre);

/*!
 * \brief Fonction qui affiche le joueur courant dans le menu partie
 * @param LARGEURFenetre Largeur de la fenêtre
 * @param HAUTEURFenetre Hauteur de la fenêtre
 * @param joueurCourant Joueur qui doit jouer
 * @return 0
 */
int afficheJoueurCourant(int joueurCourant, int LARGEURFenetre, int HAUTEURFenetre);

/*!
 * \brief Fonction qui affiche le score
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @param joueurCourant Joueur ayant gagné la partie
 * @return 0
 */
int afficheVictoire(int LARGEURFenetre, int HAUTEURFenetre, int joueurCourant);

/*!
 * \brief Fonction qui permet de gérer la taille d'affichage du plateau de jeu
 * @param coordonneesPlateau Tableau de gestion des coordonnées du plateau
 * @return
 */
void assigneTaillePlateau(int *coordonneesPlateau);

/*!
 * \brief Fonction qui permet d'afficher le menu de défaite lorsque le joueur perd contre l'ordinateur
 *
 * @param LARGEURFenetre Largeur de la fenêtre en pixels
 * @param HAUTEURFenetre Hauteur de la fenêtre en pixels
 */
void afficheDefaite(int LARGEURFenetre, int HAUTEURFenetre);

#endif
