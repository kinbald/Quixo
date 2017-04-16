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
 * @param colonnePiochee Colonne de la case piochée
 * @param lignePiochee Ligne de la case piochée
 * @param colonneJouee Colonne de la case de surbrillance choisie
 * @param ligneJouee Ligne de la case de surbrillance choisie
 * @return ::0 si le décalage a bien été effectuer et -1 si y a eu un problème
*/
int decalage(PLATEAU * plateau, int colonnePiochee, int lignePiochee,
	     int colonneJouee, int ligneJouee);

/*!
 * \brief verification de la victoire d'un joueur par les lignes'
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireLigne1V1(PLATEAU * plateau, int joueurCourant);

/*!
 * \brief verification de la victoire d'un joueur par les colonnes
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireColonne1V1(PLATEAU * plateau, int joueurCourant);

/*!
 * \brief verification de la victoire d'un joueur par la diagonale de gauche haut vers droite bas
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleG1V1(PLATEAU * plateau, int joueurCourant);

/*!
 * \brief verification de la victoire d'un joueur par la diagonale de gauche bas vers droite haut
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleD1V1(PLATEAU * plateau, int joueurCourant);

/*!
 * \brief verification de la victoire en 2V2 d'un joueur par les ligne
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireLigne2V2(PLATEAU * plateau, int joueurCourant,
			  int joueurAllier);

/*!
 * \brief verification de la victoire en 2V2 d'un joueur par les colonnes
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireColonne2V2(PLATEAU * plateau, int joueurCourant,
			    int joueurAllier);

/*!
 * \brief verification de la victoire en 2V2 d'un joueur par la  diagonale de gauche haut vers droite bas
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleG2V2(PLATEAU * plateau, int joueurCourant,
			       int joueurAllier);

/*!
 * \brief verification de la victoire d'un joueur en 2V2 par la diagonale de gauche bas vers droite haut
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleD2V2(PLATEAU * plateau, int joueurCourant,
			       int joueurAllier);
/*!
 * \brief appel des fonctions de test de victiore pour le mode 2v2 et 1V1
 * \brief /!\ si on est en mode 1V1 alors  joueurAllier = 0
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoire(PLATEAU * plateau, int joueurCourant, int joueurAllier);

/*!
 * \brief Fonction qui vérifie la victoire en mode 1v1 ou 1vIA et qui prend en compte la cas particulier de la victoire adverse
 * @param plateau Plateau de jeu
 * @param joueurCourant Joueur courant
 * @param joueurAllier Joueur allier (facultatif : 0)
 * @return
 */
int testeVictoireCasParticulier(PLATEAU * plateau, int *joueurCourant,
				int joueurAllier);

/*!
 * \brief appel des fonctions de test de victiore pour le mode 2v2 et 1V1
 * \brief /!\ si on est en mode 1V1 alors  joueurAllier = 0
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoire(PLATEAU * plateau, int joueurCourant, int joueurAllier);

/*!
 * \brief Fonction qui vérifie que le cube voulant être pioché est disponible
 *
 * @param plateau Plateau de jeu
 * @param clicJoueur Clic du jouer sur l'affichage graphique (coordonnées en X et Y)
 * @param joueurCourant
 * @return 0 si coup possible, -1 sinon
 */
int verifieSymbole(PLATEAU * plateau, CASE * clicJoueur, int joueurCourant);

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
 * \brief Fonction qui implémente l'algorithme min-max de recherche de mouvement favorable
 * @param plateau Plateau de jeu
 * @param joueur Joueur qui doit placer son coup
 * @param joueurLancement Lanceur du coup principal
 * @param depth Profondeur courante de recherche
 * @param isMax Le coup est-il maximal ou minimal
 * @param alpha Elagage alpha
 * @param beta Elagage beta
 * @return
 */
int MinMax(PLATEAU * plateau, int joueur, int joueurLancement, int depth,
	   int isMax, int alpha, int beta);

/*!
 * \brief Fonction qui effectue un mouvement de l'IA sur le plateau en utilisant l'algorithme de recherche min-max
 * @param plateau Plateau de jeu en cours
 * @param symbole Symbole correspondant à l'ordinateur sur le plateau
 */
void mouvementIA(PLATEAU * plateau, int symbole);

/*!
 * \brief Fonction qui permet d'évaluer un plateau donné pour un joueur suivant les lignes, les colonnes et les diagonales
 *
 * @param plateau
 * @param joueurCourant
 * @return
 */
int evaluePlateau(PLATEAU * plateau, int joueurCourant);

/*!
 * \brief Fonction qui permet d'évaluer les lignes du plateau envoyé
 *
 * Plus le retour est grand plus le joueurCourant est favorisé et inversement si le retour est faible
 *
 * @param plateau Plateau de jeu
 * @param evaluation Evaluation de base du joueurCourant (par exemple après une étude des diagonales)
 * @param joueurCourant
 * @return
 */
int evalueLignes(PLATEAU * plateau, int evaluation, int joueurCourant);

/*!
 * \brief Fonction qui permet d'évaluer les colonnes du plateau envoyé
 *
 * Plus le retour est grand plus le joueurCourant est favorisé et inversement si le retour est faible
 *
 * @param plateau Plateau de jeu
 * @param evaluation Evaluation de base du joueurCourant (par exemple après une étude des lignes)
 * @param joueurCourant
 * @return
 */
int evalueColonnes(PLATEAU * plateau, int evaluation, int joueurCourant);

/*!
 * \brief Fonction qui permet d'évaluer les diagonales du plateau envoyé
 *
 * Plus le retour est grand plus le joueurCourant est favorisé et inversement si le retour est faible
 *
 * @param plateau Plateau de jeu
 * @param evaluation Evaluation de base du joueurCourant (par exemple après une étude des lignes)
 * @param joueurCourant
 * @return
 */
int evalueDiagonales(PLATEAU * plateau, int evaluation, int joueurCourant);

/*!
 * \brief Fonction qui affiche la variable plateau_jeu en console
 */
void affichePlateauConsole(void);

#endif
