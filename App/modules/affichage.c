/*!
* \file affichage.c
* \brief Fichier contenant les fonctions d'affichage
* \author desrumaux
* \date 24/01/17
*/
#include "affichage.h"

extern PLATEAU plateau_jeu;

/*!
 * \brief Fonction de gestion des événements
 *
 * Appelée automatiquement par le système dès qu'un événement survient
 *
 * @param EvenementGfx
 */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false;	// Pour savoir si on est en mode plein écran ou pas
	static int coordonnees[4];

	switch (evenement) {
	case Initialisation:
		initPlateau();
		demandeAnimation_ips(1);	// Configure le système pour un mode 50 images par seconde

		break;

	case Affichage:
		// On part d'un fond d'ecran blanc
		effaceFenetre(0, 0, 0);

		affichePlateau(coordonnees);

		epaisseurDeTrait(10.0);
		couleurCourante(255, 0, 0);
		break;

	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(),
		       caractereClavier());

		switch (caractereClavier()) {
		case 'Q':	// Quitter le programme
		case 'q':
			exit(0);

		case 'F':
		case 'f':
			pleinEcran = !pleinEcran;	// Changement de mode plein ecran
			if (pleinEcran)
				modePleinEcran();
			else
				redimensionneFenetre(LargeurFenetre,
						     HauteurFenetre);
			break;

		case 'R':
		case 'r':
			rafraichisFenetre();	// Force un rafraîchissment
			break;
		}
		break;

	case ClavierSpecial:
		printf("ASCII %d\n", toucheClavier());
		break;

	case BoutonSouris:

		break;

	case Souris:		// Si la souris est deplacee
		break;

	case Inactivite:	// Quand aucun message n'est disponible
		break;

	case Redimensionnement:	// La taille de la fenetre a ete modifie ou on est passe en plein ecran
		// Donc le systeme nous en informe
		printf("Largeur : %d\t", largeurFenetre());
		printf("Hauteur : %d\n", hauteurFenetre());
		break;
	}
}

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
	int index_ligne = TAILLE_PLATEAU;
	// Index pour le parcours du tableau (départ du coté gauche de l'affichage)
	int index_colonne = 0;

	// Pas des cases
	float pas = calculePas(coordonneesPlateau);

	CASE casePion;

	// Coordonnée en pixels (ligne) du milieu de la première case
	casePion.ligne = (int)(coordonneesPlateau[1] - (pas / 2));
	// Coordonnée en pixels (colonne) du milieu de la première case
	casePion.colonne = (int)(coordonneesPlateau[0] + (pas / 2));

	while (index_ligne > 0) {
		while (index_colonne < TAILLE_PLATEAU) {
			// Traitement de l'affichage de la case (coordonées du milieu : (coordX, coordY)
			afficheSymbole(pas, casePion,
				       plateau_jeu[index_ligne][index_colonne]);

			// On incrémente la position en pixels ( colonne + 1)
			casePion.colonne = (int)(casePion.colonne + pas);
			index_colonne += 1;
		}
		// On repart de la première case sur la gauche du plateau
		casePion.colonne = (int)(coordonneesPlateau[0] + (pas / 2));
		index_colonne = 0;

		// On decrémente la position en pixels (ligne -1)
		casePion.ligne = (int)(casePion.ligne - pas);
		index_ligne -= 1;
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
	couleurCourante(0, 0, 20);
	rectangle(coordonneesPlateau[0], coordonneesPlateau[1],
		  coordonneesPlateau[2], coordonneesPlateau[3]);
	// Couleur et trait colonnes et lignes
	couleurCourante(255, 255, 255);
	epaisseurDeTrait(1.0);

	ligne(coordonneesPlateau[0], coordonneesPlateau[3],
	      coordonneesPlateau[0], coordonneesPlateau[1]);
	ligne(coordonneesPlateau[0], coordonneesPlateau[3],
	      coordonneesPlateau[2], coordonneesPlateau[3]);

	int index_colonne = 0;
	int index_ligne = 0;

	int valeurX = coordonneesPlateau[0];
	int valeurY = coordonneesPlateau[3];

	while (index_colonne < TAILLE_PLATEAU) {
		valeurX += pas;
		ligne(valeurX, coordonneesPlateau[1], valeurX,
		      coordonneesPlateau[3]);
		index_colonne += 1;
	}
	while (index_ligne < TAILLE_PLATEAU) {
		valeurY += pas;
		ligne(coordonneesPlateau[0], valeurY, coordonneesPlateau[2],
		      valeurY);
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
void afficheSymbole(float pas, CASE case_jeu, int joueur)
{
	switch (joueur) {
	case croix_bas:
	case rond_bas:
	case croix_haut:
	case croix_droit:
	case croix_gauche:
	case rond_haut:
	case rond_droit:
	case rond_gauche:
	case vide:
	case surbrillance:
	case tampon:
		break;
	}
}
