/*!
* \file moteur.c
* \brief Fichier contenant les fonctions du module moteur
* \author desrumaux
* \date 24/01/17
*/
#include "moteur.h"

/*!
 * \brief Fonction qui vérifie que le cube voulant être pioché est disponible
 *
 * @param clicJoueur Clic du jouer sur l'affichage graphique (coordonnées en X et Y)
 * @return 0 si coup possible, -1 sinon
 */
int verifieSymbole(CLIC * clicJoueur)
{
	CASE case_jouee;
	case_jouee.colonne = clicJoueur->coordX;
	case_jouee.ligne = clicJoueur->coordY;
	int joueur = getCase(&plateau_jeu, &case_jouee);

	if (joueur == clicJoueur->joueurCourant || joueur == vide) {
		return 0;
	} else {
		return -1;
	}
}

/*!
 * \brief Fonction qui déterminer les cases où le joueur peut déposer le cube qu'il a pioché
 * @param casePiochee Coordonnées de la case que le joueur a pioché
 * @return 0
 */
int calculeSurbrillance(CASE * casePiochee)
{

	CASE surbrillanceCase;
	short index_move;
	short nb_mouvements;
	// Cases à mettre en surbrillance
	int move[3][2];

	int x = casePiochee->colonne;
	int y = casePiochee->ligne;

	// Vérification du cas des quatre coins
	if ((x == 1 || x == 5) && (y == 1 || y == 5)) {
		// Seulement deux mouvements possibles
		nb_mouvements = 2;

		// Premier mouvement possible
		move[0][0] = ((x + 5) % 10);
		move[0][1] = y;

		// Deuxieme mouvement possible
		move[1][0] = x;
		move[1][1] = ((y + 5) % 10);
	} else {
		// Trois mouvements possibles
		nb_mouvements = 3;

		if (x == 1 || x == 5) {
			// Premier mouvement possible
			move[0][0] = ((x + 5) % 10);
			move[0][1] = y;

			// Deuxième mouvement possible
			move[1][0] = x;
			move[1][1] = 0;

			// Troisième mouvement possible
			move[2][0] = x;
			move[2][1] = 6;
		} else {
			// Premier mouvement possible
			move[0][0] = x;
			move[0][1] = ((y + 5) % 10);

			// Deuxième mouvement possible
			move[1][0] = 0;
			move[1][1] = y;

			// Troisième mouvement possible
			move[2][0] = 6;
			move[2][1] = y;
		}
	}
	// Modification des cases du plateau à partir du tableau des surbrillances
	for (index_move = 0; index_move < nb_mouvements; index_move++) {
		surbrillanceCase.colonne = move[index_move][0];
		surbrillanceCase.ligne = move[index_move][1];
		setCase(&plateau_jeu, &surbrillanceCase, surbrillance);
	}
	return 0;
}
