/*!
* \file outils.c
* \brief Fichier contenant les fonctions du module outils
* \author desrumaux
* \date 24/01/17
*/
#include "outils.h"

extern PLATEAU plateau_jeu;

/*!
 * \brief Accesseur pour un plateau de jeu de type PLATEAU
 * @param plateau Plateau du jeu à accéder
 * @param case_jeu Case du jeu à lire
 * @return ::SYMBOLE du joueur dans la case demandée
 */
int getCase(PLATEAU * plateau, CASE * case_jeu)
{
	int valeurRetour;	// Valeur de retour de la case du plateau demandée

	if ((case_jeu->ligne >= 0) && (case_jeu->ligne < TAILLE_PLATEAU) && (case_jeu->colonne >= 0) && (case_jeu->colonne < TAILLE_PLATEAU))
	{
		valeurRetour = (*plateau)[case_jeu->ligne][case_jeu->colonne];
		return (valeurRetour);
	} else
	{
		return (-1);
	}
}

/*!
 * \brief Mutateur pour un plateau de jeu de type PLATEAU
 * @param plateau Plateau de jeu à modifier
 * @param case_jeu Case du jeu à modifier
 * @param symbole Symbole à modifier dans le plateau
 * @return int
 */
int setCase(PLATEAU * plateau, CASE * case_jeu, int symbole)
{
	if ((case_jeu->ligne >= 0) && (case_jeu->ligne < TAILLE_PLATEAU) && (case_jeu->colonne >= 0) && (case_jeu->colonne < TAILLE_PLATEAU))
	{
		(*plateau)[case_jeu->ligne][case_jeu->colonne] = symbole;	// Lecture dans le plateau envoyé
		return (0);
	} else
	{
		return (-1);
	}
}

/*!
 * \brief Fonction permettant d'initialiser le plateau de jeu
 * @return 0
 */
int initPlateau(void)
{
	int index_ligne;
	int index_colonne;

	CASE initVide;
	for (index_ligne = 0; index_ligne < TAILLE_PLATEAU; index_ligne = index_ligne + 1)
	{
		initVide.ligne = index_ligne;
		for (index_colonne = 0; index_colonne < TAILLE_PLATEAU; index_colonne = index_colonne + 1)
		{
			initVide.colonne = index_colonne;
			if (index_colonne == 0 || index_colonne == (TAILLE_PLATEAU - 1) || index_ligne == 0 || index_ligne == (TAILLE_PLATEAU - 1))
			{
				setCase(&plateau_jeu, &initVide, tampon);	// Si on est sur le bord du plateau on place le ::SYMBOLE tampon
			} else
			{
				setCase(&plateau_jeu, &initVide, vide);	// Sinon on place le ::SYMBOLE vide
			}
		}
	}
	return 0;
}

/*!
 * \brief Fonction qui permet d'initialiser un tableau de SCORE.
 * @param scoreJoueur Tableau des scores
 * @param nombreJoueurs Nombre de joueurs sur la partie
 * @param joueurs Listes des symboles des joueurs
 */
void initScore(SCORE * scoreJoueur, int nombreJoueurs, int *joueurs)
{
	int i;
	if (scoreJoueur != NULL)
	{
		for (i = 0; i < nombreJoueurs; i++)
		{
			scoreJoueur[i].joueur = joueurs[i];
			scoreJoueur[i].score = 0;
		}
	}
}

/*!
 * \brief Fonction permettant de modifier le score d'un joueur dans le tableau des scores.
 * @param scoresJoueurs Tableau de structures SCORE
 * @param nombreJoueurs Nombre de joueurs listés dans le tableau
 * @param joueur Joueur courant à modifier
 * @param nouveauScore Score à modifier
 */
void setScore(SCORE * scoresJoueurs, int nombreJoueurs, int joueur, int nouveauScore)
{
	int i;
	if (scoresJoueurs != NULL)
	{
		// Parcours des scores pour trouver celui du joueur correspondant
		for (i = 0; i < nombreJoueurs; i++)
		{
			if (scoresJoueurs[i].joueur == joueur)
			{
				scoresJoueurs[i].score = nouveauScore;
			}
		}
	}
}

/*!
 * \brief Fonction qui permet de récupérer un score à partir du tableau des scores et d'un joueur.
 * @param scoresJoueurs Tableau de structures SCORE
 * @param nombreJoueurs Nombre de joueurs listés dans le tableau
 * @param joueur Joueur courant à récupérer
 * @return Score du joueur
 */
int getScore(SCORE * scoresJoueurs, int nombreJoueurs, int joueur)
{
	int i;
	if (scoresJoueurs != NULL)
	{
		for (i = 0; i < nombreJoueurs; i++)
		{
			if (scoresJoueurs[i].joueur == joueur)
			{
				return scoresJoueurs[i].score;
			}
		}
	}
	return -1;
}
