/*!
* \file outils.c
* \brief Fichier contenant les fonctions du module outils
* \author desrumaux
* \date 24/01/17
*/
#include "outils.h"

/*!
 * \brief Accesseur pour un plateau de jeu de type PLATEAU
 * @param plateau Plateau du jeu à accéder
 * @param case_jeu Case du jeu à lire
 * @return ::SYMBOLE du joueur dans la case demandée
 */
int getCase(PLATEAU plateau, CASE case_jeu)
{
	int valeurRetour;	///< Valeur de retour de la case du plateau demandée

	if ((case_jeu.ligne >= 0) && (case_jeu.ligne < TAILLE_PLATEAU)
	    && (case_jeu.colonne >= 0) && (case_jeu.colonne < TAILLE_PLATEAU)) {
		valeurRetour = plateau[case_jeu.ligne][case_jeu.colonne];
		return (valeurRetour);
	} else {
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
int setCase(PLATEAU plateau, CASE case_jeu, SYMBOLE symbole)
{
	if ((case_jeu.ligne >= 0)
	    && (case_jeu.ligne < TAILLE_PLATEAU)
	    && (case_jeu.colonne >= 0)
	    && (case_jeu.colonne < TAILLE_PLATEAU)
	    && (symbole >= croix_bas)
	    && (symbole <= tampon)) {
		plateau[case_jeu.ligne][case_jeu.colonne] = symbole;	/// Lecture dans le plateau envoyé
		return (0);
	} else {
		return (-1);
	}
}
