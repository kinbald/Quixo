/*!
* \file moteur.h
* \brief Fichier contenant les prototypes des fonctions du module moteur
* \author desrumaux
* \date 24/01/17
*/
#ifndef G_MOTEUR

#define G_MOTEUR

#include "outils.h"
#include <limits.h>

/*!
 * \brief décalage des pions
 * @param plateau Plateau du jeu à accéder
 * @param colonnePiochee et lignePiochee de la case prise et colonneJouee et ligneJouee de la case de surbrillance choisie
 * @return ::0 si le décalage a bien été effectuer et -1 si y a eu un problème
*/
int decalage(PLATEAU * plateau, int colonnePiochee, int lignePiochee,
	     int colonneJouee, int ligneJouee);

/*!
 * \brief verification de la victoire d'un joueur par les lignes'
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireLigne1V1(int joueurCourant);

/*!
 * \brief verification de la victoire d'un joueur par les colonnes
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireColonne1V1(int joueurCourant);

/*!
 * \brief verification de la victoire d'un joueur par la diagonale de gauche haut vers droite bas
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleG1V1(int joueurCourant);

/*!
 * \brief verification de la victoire d'un joueur par la diagonale de gauche bas vers droite haut
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleD1V1(int joueurCourant);

/*!
 * \brief verification de la victoire en 2V2 d'un joueur par les ligne
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireLigne2V2(int joueurCourant, int joueurAllier);

/*!
 * \brief verification de la victoire en 2V2 d'un joueur par les colonnes
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireColonne2V2(int joueurCourant, int joueurAllier);

/*!
 * \brief verification de la victoire en 2V2 d'un joueur par la  diagonale de gauche haut vers droite bas
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleG2V2(int joueurCourant, int joueurAllier);

/*!
 * \brief verification de la victoire d'un joueur en 2V2 par la diagonale de gauche bas vers droite haut
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleD2V2(int joueurCourant, int joueurAllier);

/*!
 * \brief appel des fonctions de test de victiore pour le mode 2v2 et 1V1
 * \brief /!\ si on est en mode 1V1 alors  joueurAllier = 0
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoire(int joueurCourant, int joueurAllier);

/*!
 * \brief Fonction qui vérifie que le cube voulant être pioché est disponible
 *
 * @param clicJoueur Clic du jouer sur l'affichage graphique (coordonnées en X et Y)
 * @return 0 si coup possible, -1 sinon
 */
int verifieSymbole(CASE * clicJoueur, int joueurCourant);

/*!
 * \brief Fonction qui déterminer les cases où le joueur peut déposer le cube qu'il a pioché
 * @param casePiochee Coordonnées de la case que le joueur a pioché
 * @return 0
 */
int calculeSurbrillance(CASE * casePiochee);

/*!
 * \brief Fonction qui permet de nettoyer le plateau après la surbrillance
 * @param plateau
 */
void nettoieSurbrillance(PLATEAU * plateau);
/*!
 * \brief Fonction permet de gérer l'avancement du jeu
 *
 * @param joueurCourant
 * @param etatClic Permet de connaîre l'étape dans le jeu
 * @param caseJouee
 * @param casePiochee
 * @return
 */
int calculeTour(int *joueurCourant, int etatClic, CASE * caseJouee,
		CASE * casePiochee);

/*!
 * \brief Fontion qui permet d'appliquer un coup sur un plateau
 *
 * @param plateau Plateau de jeu
 * @param casePioche Case de pioche
 * @param jouee Case de dépôt
 * @param joueur Joueur
 */
void joueCoup(PLATEAU * plateau, CASE casePioche, CASE jouee, int joueur);

/*!
 * \brief Fonction qui permet de déjouer un coup sur le plateau
 * @param plateau Plateau de jeu
 * @param casePioche Case où le joueur avait pioché
 * @param jouee Case où le joueur avait joué
 * @param ancienEtat Dernier état de la case
 */
void dejoueCoup(PLATEAU * plateau, CASE casePioche, CASE jouee, int ancienEtat);

/*!
 * \brief Fonction qui permet de changer de joueur
 * @param joueur Joueur courant
 * @return
 */
int changeJoueur(int joueur);

/*!
 * \brief Fonction qui implémente l'algorithme min max de recherche de mouvement favorable
 * @param plateau Plateau de jeu
 * @param joueur Joueur courant
 * @param depth Profondeur de l'évaluation
 * @return
 */
int MinMax(PLATEAU * plateau, int joueur, int depth);

/*!
 * \brief Fonction qui effectue un mouvement de l'IA sur le plateau
 * @param plateau
 */
void mouvementIA(PLATEAU * plateau);
#endif
