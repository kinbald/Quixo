/*!
* \file affichage.c
* \brief Fichier contenant les fonctions d'affichage
* \author desrumaux
* \date 24/01/17
*/
#include "affichage.h"

extern PLATEAU plateau_jeu;

/*!
 * \brief Fonction qui permet d'afficher le plateau suivant les coordonnées envoyées
 *
 * @param coordonneesPlateau Pointeur vers un tableau contenant les coorodonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 */
void affichePlateau(int *coordonneesPlateau)
{
	// Affichage de la grille de jeu
	afficheGrille(coordonneesPlateau);

	// Index pour le parcours du tableau (départ du coin gauche supérieur)
	int index_ligne = 0;
	// Index pour le parcours du tableau (départ du coté gauche de l'affichage)
	int index_colonne = 0;

	// Pas des cases
	float pas = calculePas(coordonneesPlateau);

	CASE casePion;
	CASE caseLecture;
	caseLecture.ligne = index_ligne;

	// Coordonnée en pixels (ligne) du milieu de la première case
	casePion.ligne = (int)(coordonneesPlateau[1] - (pas / 2));
	// Coordonnée en pixels (colonne) du milieu de la première case
	casePion.colonne = (int)(coordonneesPlateau[0] + (pas / 2));

	while (index_ligne < TAILLE_PLATEAU) {
		while (index_colonne < TAILLE_PLATEAU) {
			caseLecture.colonne = index_colonne;
			// Traitement de l'affichage de la case (coordonées du milieu : (coordX, coordY)
			afficheSymbole(pas, &casePion,
				       getCase(&plateau_jeu, &caseLecture));
			// On incrémente la position en pixels ( colonne + 1)
			casePion.colonne = (int)(casePion.colonne + pas);
			index_colonne += 1;
		}
		// On repart de la première case sur la gauche du plateau
		casePion.colonne = (int)(coordonneesPlateau[0] + (pas / 2));
		index_colonne = 0;
		caseLecture.colonne = index_colonne;

		// On decrémente la position en pixels (ligne -1)
		casePion.ligne = (int)(casePion.ligne - pas);
		index_ligne += 1;
		caseLecture.ligne = index_ligne;
	}
}

/*!
 * \brief Fonction qui permet de calculer le pas dans la grille d'un plateau
 *
 * Calcul depuis les coordonnées le pas de chaque case.
 *
 * @param coordonneesPlateau Pointeur vers un tableau contenant les coorodonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 *
 * @return Pas de chaque case
 */
float calculePas(int *coordonneesPlateau)
{
	// Largeur donnée par les coordonnées en entrée
	float largeur = (float)(coordonneesPlateau[2] - coordonneesPlateau[0]);
	// Si la largeur calculée n'est divisble par la taille du plateau (donc perte de pixels à l'affichage)
	if (fmodf(largeur, TAILLE_PLATEAU) != 0.0) {
		int indexZero = 0;
		int indexTwo = 0;
		float coordonnee;

		// Calcul du nombre divisble par la taille du plateau par excès
		while (fmodf(largeur, TAILLE_PLATEAU) != 0.0
		       && indexTwo < TAILLE_PLATEAU) {
			indexTwo = indexTwo + 1;
			coordonnee = coordonneesPlateau[2] + indexTwo;
			largeur = coordonnee - coordonneesPlateau[0];
		}
		// Réinitialisation
		largeur = (coordonneesPlateau[2] - coordonneesPlateau[0]);
		// Calcul du nombre divisble par la taille du plateau par défaut
		while (fmodf(largeur, TAILLE_PLATEAU) != 0
		       && indexZero < TAILLE_PLATEAU) {
			indexZero = indexZero + 1;
			coordonnee = coordonneesPlateau[2] - indexZero;
			largeur = coordonnee - coordonneesPlateau[0];
		}
		// Redéfinition des coordonnées du plateau
		if (indexTwo <= indexZero) {
			coordonneesPlateau[2] =
			    coordonneesPlateau[2] + indexTwo;
			coordonneesPlateau[1] =
			    coordonneesPlateau[1] + indexTwo;
		} else {
			coordonneesPlateau[2] =
			    coordonneesPlateau[2] - indexZero;
			coordonneesPlateau[1] =
			    coordonneesPlateau[1] - indexZero;
		}
	}
	largeur = (coordonneesPlateau[2] - coordonneesPlateau[0]);
	return largeur / TAILLE_PLATEAU;
}

/*!
 * \brief Fonction qui permet d'afficher la grile de jeu.
 *
 * @param coordonneesPlateau Pointeur vers un tableau contenant les coorodonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 */
void afficheGrille(int *coordonneesPlateau)
{

	float pas = calculePas(coordonneesPlateau);

	// Fond
	/*couleurCourante(35, 59, 110);
	   rectangle(coordonneesPlateau[0], coordonneesPlateau[1],
	   coordonneesPlateau[2], coordonneesPlateau[3]); */
	couleurCourante(35, 59, 110);
	rectangle(coordonneesPlateau[0] + pas, coordonneesPlateau[1] - pas,
		  coordonneesPlateau[2] - pas, coordonneesPlateau[3] + pas);
	// Couleur et trait colonnes et lignes
	couleurCourante(239, 240, 244);
	epaisseurDeTrait(4.5);

	int index_colonne = 1;
	int index_ligne = 1;

	int valeurX = coordonneesPlateau[0] + pas;
	int valeurY = coordonneesPlateau[3] + pas;

	while (index_colonne < TAILLE_PLATEAU - 2) {
		valeurX += pas;
		ligne(valeurX, coordonneesPlateau[1] - pas, valeurX,
		      coordonneesPlateau[3] + pas);
		index_colonne += 1;
	}
	while (index_ligne < TAILLE_PLATEAU - 2) {
		valeurY += pas;
		ligne(coordonneesPlateau[0] + pas, valeurY,
		      coordonneesPlateau[2] - pas, valeurY);
		index_ligne += 1;
	}
}

/*!
 * \brief Fonction qui permet d'afficher le symbole correspondant à la case parcourue dans le plateau de jeu
 *
 * @param pas Pas de la grille
 * @param case_jeu Case à traiter
 * @param joueur Joueur courant
 */
void afficheSymbole(float pas, CASE * case_jeu, int joueur)
{
	couleurCourante(239, 240, 244);
	switch (joueur) {
	case croix_droit:
		afficheCroixPoint(case_jeu, pas, 0);
		break;
	case croix_bas:
		afficheCroixPoint(case_jeu, pas, 1);
		break;
	case croix_gauche:
		afficheCroixPoint(case_jeu, pas, 2);
		break;
	case croix_haut:
		afficheCroixPoint(case_jeu, pas, 3);
		break;
	case rond_droit:
		afficheRondPoint(case_jeu, pas / 3, 0);
		break;
	case rond_bas:
		afficheRondPoint(case_jeu, pas / 3, 1);
		break;
	case rond_gauche:
		afficheRondPoint(case_jeu, pas / 3, 2);
		break;
	case rond_haut:
		afficheRondPoint(case_jeu, pas / 3, 3);
		break;
	case surbrillance:
		break;
	case vide:
		afficheCroix(case_jeu, pas);
		break;
	}
}

/*!
 * \brief Fontion qui permet d'afficher une croix de taille pas/3 aux coordonnées de *case_jeu
 *
 * @param case_jeu Case du jeu ciblée pour la croix (coordonnées en X et Y)
 * @param pas Pas des cases
 */
void afficheCroix(CASE * case_jeu, int pas)
{
	epaisseurDeTrait(3);
	ligne((float)(case_jeu->colonne - (pas / 3)),
	      (float)(case_jeu->ligne - (pas / 3)),
	      (float)(case_jeu->colonne + (pas / 3)),
	      (float)(case_jeu->ligne + pas / 3));
	ligne((float)(case_jeu->colonne - (pas / 3)),
	      (float)(case_jeu->ligne + (pas / 3)),
	      (float)(case_jeu->colonne + (pas / 3)),
	      (float)(case_jeu->ligne - pas / 3));
}

/*!
 * \brief Fontion qui permet d'afficher une croix de taille pas/3 aux coordonnées de *case_jeu avec un point
 *
 * @param case_jeu Case du jeu ciblée pour la croix (coordonnées en X et Y)
 * @param pas Pas des cases
 * @param direction Direction choisie pour le point (0: Droit, 1: Bas, 2: Gauche, 3: Haut)
 */
void afficheCroixPoint(CASE * case_jeu, int pas, int direction)
{
	epaisseurDeTrait(3);
	ligne((float)(case_jeu->colonne - (pas / 3)),
	      (float)(case_jeu->ligne - (pas / 3)),
	      (float)(case_jeu->colonne + (pas / 3)),
	      (float)(case_jeu->ligne + pas / 3));
	ligne((float)(case_jeu->colonne - (pas / 3)),
	      (float)(case_jeu->ligne + (pas / 3)),
	      (float)(case_jeu->colonne + (pas / 3)),
	      (float)(case_jeu->ligne - pas / 3));

	if (direction == 0) {
		point(case_jeu->colonne + (pas / 4), case_jeu->ligne);
	} else if (direction == 1) {
		point(case_jeu->colonne, case_jeu->ligne - (pas / 4));
	} else if (direction == 2) {
		point(case_jeu->colonne - (pas / 4), case_jeu->ligne);
	} else if (direction == 3) {
		point(case_jeu->colonne, case_jeu->ligne + (pas / 4));
	}
}

/*!
 * \brief Fonction qui permet de dessiner un disque sur l'affichage
 * @param case_jouee Case du plateau (en pixels)
 * @param rayon Rayon du disque (en pixels)
 */
void afficheDisque(CASE * case_jouee, float rayon)
{
	float xCoin1, yCoin1, xCoin2, yCoin2, xCoin3, yCoin3;
	float teta, pas;
	float precision = 5.0;
	pas = (float)((2 * 3.14) / 360.0 * precision);

	xCoin1 = case_jouee->colonne;
	yCoin1 = case_jouee->ligne;
	teta = 0;
	xCoin2 = case_jouee->colonne + (float)(rayon * cos(teta));
	yCoin2 = case_jouee->ligne + (float)(rayon * sin(teta));
	teta = pas;
	xCoin3 = case_jouee->colonne + (float)(rayon * cos(teta));
	yCoin3 = case_jouee->ligne + (float)(rayon * sin(teta));
	triangle(xCoin1, yCoin1, xCoin2, yCoin2, xCoin3, yCoin3);
	for (teta = pas; teta <= 2 * 3.14; teta = teta + pas) {
		xCoin2 = xCoin3;
		yCoin2 = yCoin3;
		xCoin3 = case_jouee->colonne + (float)(rayon * cos(teta));
		yCoin3 = case_jouee->ligne + (float)(rayon * sin(teta));
		triangle(xCoin1, yCoin1, xCoin2, yCoin2, xCoin3, yCoin3);
	}
}

/*!
 * \brief Fonction qui permet d'afficher un cercle de rayon donné
 *
 * @param case_jouee Coordonnées de la case pour placer le cercle
 * @param rayon Rayon du cercle
 */
void afficheRond(CASE * case_jouee, float rayon)
{
	int centreX = case_jouee->colonne;
	int centreY = case_jouee->ligne;
	int d, x;
	d = 3 - (2 * rayon);
	x = 0;
	float y = rayon;
	while (y >= x) {
		epaisseurDeTrait(2);
		point(centreX + x, centreY + y);
		point(centreX + y, centreY + x);
		point(centreX - x, centreY + y);
		point(centreX - y, centreY + x);
		point(centreX + x, centreY - y);
		point(centreX + y, centreY - x);
		point(centreX - x, centreY - y);
		point(centreX - y, centreY - x);
		if (d < 0) {
			d = d + (4 * x) + 6;
		} else {
			d = d + 4 * (x - y) + 10;
			y += (-1);
		}
		x += 1;
	}
}

/*!
 * \brief Fonction qui permet d'afficher un cercle de rayon donné avec un point suivant une direction
 *
 * @param case_jouee Coordonnées de la case pour placer le cercle
 * @param rayon Rayon du cercle
 * @param direction Direction choisie pour le point (0: Droit, 1: Bas, 2: Gauche, 3: Haut)
 */
void afficheRondPoint(CASE * case_jouee, float rayon, int direction)
{
	int centreX = case_jouee->colonne;
	int centreY = case_jouee->ligne;
	int d, x;
	d = 3 - (2 * rayon);
	x = 0;
	float y = rayon;
	while (y >= x) {
		epaisseurDeTrait(2);
		point(centreX + x, centreY + y);
		point(centreX + y, centreY + x);
		point(centreX - x, centreY + y);
		point(centreX - y, centreY + x);
		point(centreX + x, centreY - y);
		point(centreX + y, centreY - x);
		point(centreX - x, centreY - y);
		point(centreX - y, centreY - x);
		if (d < 0) {
			d = d + (4 * x) + 6;
		} else {
			d = d + 4 * (x - y) + 10;
			y += (-1);
		}
		x += 1;
	}
	if (direction == 0) {
		point(case_jouee->colonne + (rayon / 2), case_jouee->ligne);
	} else if (direction == 1) {
		point(case_jouee->colonne, case_jouee->ligne - (rayon / 2));
	} else if (direction == 2) {
		point(case_jouee->colonne - (rayon / 2), case_jouee->ligne);
	} else if (direction == 3) {
		point(case_jouee->colonne, case_jouee->ligne + (rayon / 2));
	}
}

/*!
 * \brief Fonction qui permet de gérer les clics sur l'affichage graphique en fonction du menu
 *
 * @param retourClic Case utilisée lors d'un clic sur plateau
 * @param clicSouris Clic du joueur sur l'affichage graphique (coordonnées en X et Y) et menu courant
 * @param coordonneesPlateau Coordonnées du plateau de jeu lors d'un clic dans la partie
 * @return Action à effectuer
 */
int recupereClicAffichage(CASE * retourClic, CLIC * clicSouris,
			  int *coordonneesPlateau)
{
	if (clicSouris->menu == menuPartie) {
		if (clicSouris->coordX >= coordonneesPlateau[0]
		    && clicSouris->coordY <= coordonneesPlateau[1]
		    && clicSouris->coordX <= coordonneesPlateau[2]
		    && clicSouris->coordY >= coordonneesPlateau[3]) {
			return clicPlateau(retourClic, clicSouris,
					   coordonneesPlateau);
		}
	}
	return (0);
}

/*!
 * \brief Fonction qui permet de gérer un clic sur le menuPartie
 * @param retourClic Case qui sera modifiée si le joueur clique sur le plateau
 * @param clicSouris Clic du joueur sur l'affichage graphique (coordonnées en X et Y) et menu courant
 * @param coordonneesPlateau Coordonnées du plateau de jeu lors d'un clic dans la partie
 * @return Action à effectuer
 */
int clicPlateau(CASE * retourClic, CLIC * clicSouris, int *coordonneesPlateau)
{
	int taille = coordonneesPlateau[2] - coordonneesPlateau[0];

	retourClic->ligne =
	    (TAILLE_PLATEAU - 1) -
	    ((clicSouris->coordY -
	      coordonneesPlateau[3]) * TAILLE_PLATEAU) / (taille);
	retourClic->colonne =
	    ((clicSouris->coordX -
	      coordonneesPlateau[0]) * TAILLE_PLATEAU) / (taille);
	if (retourClic->ligne > 1 && retourClic->ligne < TAILLE_PLATEAU - 2
	    && retourClic->colonne > 1
	    && retourClic->colonne < TAILLE_PLATEAU - 2) {
		clicSouris->menu = redirectCentral;
	} else if (retourClic->ligne > 0
		   && retourClic->ligne < TAILLE_PLATEAU - 1
		   && retourClic->colonne > 0
		   && retourClic->colonne < TAILLE_PLATEAU - 1) {
		clicSouris->menu = redirectSurbrillance;
	}
	return 0;
}
