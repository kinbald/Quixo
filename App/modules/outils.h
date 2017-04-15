/*!
* \file outils.h
* \brief Fichier contenant les prototypes des fonctions du module outils et les déclarations de variables globales
* \author desrumaux
* \date 24/01/17
*/

#ifndef G_OUTILS

#define G_OUTILS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/ESLib.h"
#include <limits.h>
#include <time.h>

#ifndef M_PI
/*!
 * \brief Définition de la valeur de pi
 */
#define M_PI 3.14159265358979323846264338327
#endif

/*!
 * \brief Taille du plateau de jeu
 */
#define TAILLE_PLATEAU 7

/*!
 * \brief Mode de jeu 1 personne contre l'ordinateur
 */
#define VIA 1

/*!
 * \brief Mode de jeu 1 personne contre une autre
 */
#define V1 2

/*!
 * \brief Profondeur maximale de recherche IA
 */
#define PROFONDEUR_LIMITE 6

/*!
 * \brief Largeur de la fenêtre graphique
 */
#define LargeurFenetre 800

/*!
 * \brief Hauteur de la fenêtre graphique
 */
#define HauteurFenetre 800

/*!
 * \brief Plateau de jeu : tableau de TAILLE_PLATEAU*TAILLE_PLATEAU entiers
 */
typedef int PLATEAU[TAILLE_PLATEAU][TAILLE_PLATEAU];

/*!
 * \brief États possibles des cases du plateau de jeu
 */
typedef enum {
	croix_bas = 1,
	rond_bas = 2,
	croix_gauche = 3,
	rond_gauche = 4,
	croix_haut = 5,
	rond_haut = 6,
	croix_droit = 7,
	rond_droit = 8,
	vide = 9,
	surbrillance = 10,
	tampon = 11,
	pioche = 12
} SYMBOLE;

/*!
 * \brief États possibles de la gestion des menus du jeu
 */
typedef enum {
	menuPrincipal = 0,
	menuRegles = 1,
	menuChoixSymboles = 2,
	menuPartie = 3,
	menuVictoire = 4,
	menuChoixSymboleM = 5
} MENUS;

/*!
 * \brief États possibles de la gestion du retour au menu avec clics
 */
typedef enum {
	redirectMenuPrincipal = 0,
	redirectMenuRegles = 1,
	redirectMenuChoixSymboleS = 2,
	redirectMenuPartie = 31,
	redirectMenuVictoire = 4,
	redirectMenuChoixSymboleM = 5,
	redirectContinue = 6,
	redirectRecommencer = 7,
	redirectSurbrillance = 8,
	redirectCentral = 9,
	redirectPioche = 10,
	redirectRePioche = 11,
	redirectQuitter = 12,
	redirectAdversaire = 13,
	jeuIA = 14,
	redirectExterieur = 15
} ETATS;

/*!
 * \brief Structure de données de score d'un joueur
 */
typedef struct score {
	int joueur;		///< SYMBOLE du joueur
	int score;		///< Score du joueur
} SCORE;

/*!
 * \brief Structure de données d'une case du tableau
 */
typedef struct case_jeu {
	int colonne;		///< Colonne de la case
	int ligne;		///< Ligne de la case
} CASE;

/*!
 * \brief Structure de données d'un clic de joueur
 */
typedef struct clic {
	int coordX;		///< Coordonnée suivant X du clic
	int coordY;		///< Coordonnée suivant Y du clic
	int joueurCourant;	///< SYMBOLE du joueur courant
	int menu;		///< MENUS en cours
	int mode;		///< S'il est défini, mode de jeu en cours
} CLIC;

/*!
 * \brief Structure permettant de gérer un coup avec la case piochée et la case jouée
 */
typedef struct coup {
	CASE caseJouee;		///< Case de surbrillance choisie
	CASE casePiochee;	///< Case de jeu choisie pour jouer
} COUP;

/*!
 * Plateau de jeu
 */
extern PLATEAU plateau_jeu;

/*!
 * \brief Accesseur pour un plateau de jeu de type PLATEAU
 * @param plateau Plateau du jeu à accéder
 * @param case_jeu Case du jeu à lire
 * @return ::SYMBOLE du joueur dans la case demandée
 */
int getCase(PLATEAU * plateau, CASE * case_jeu);

/*!
 * \brief Mutateur pour un plateau de jeu de type PLATEAU
 * @param plateau Plateau de jeu à modifier
 * @param case_jeu Case du jeu à modifier
 * @param symbole Symbole à modifier dans le plateau
 * @return int
 */
int setCase(PLATEAU * plateau, CASE * case_jeu, int symbole);

/*!
 * \brief Fonction permettant d'initialiser le plateau de jeu
 * @return 0
 */
int initPlateau(void);

#endif
