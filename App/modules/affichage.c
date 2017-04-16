/*!
* \file affichage.c
* \brief Fichier contenant les fonctions d'affichage
* \author desrumaux
* \date 24/01/17
*/
#include "affichage.h"

/*!
 * Plateau de jeu
 */
extern PLATEAU plateau_jeu;

/*!
 * Scores du jeu
 */
extern SCORE scores[2];

/*!
 * \brief Fonction qui permet d'afficher le plateau suivant les coordonnées envoyées
 *
 * @param coordonneesPlateau Pointeur vers un tableau contenant les coordonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 * @param LARGEURFenetre largeur de la fênetre
 * @param HAUTEURFenetre Hauteur de la fenêtre
 */
void affichePlateau(int *coordonneesPlateau, int LARGEURFenetre,
		    int HAUTEURFenetre)
{
	// Affichage de la grille de jeu
	afficheGrille(coordonneesPlateau);
	// Affichage des boutons
	afficheBouton(LARGEURFenetre, HAUTEURFenetre);

	// Index pour le parcours du tableau (départ du coin gauche supérieur)
	int index_ligne = 0;
	// Index pour le parcours du tableau (départ du coté gauche de l'affichage)
	int index_colonne = 0;

	// Pas des cases
	float pas = calculePas(coordonneesPlateau);

	CASE casePion;
	CASE caseLecture;
	caseLecture.ligne = index_ligne;

	// Coordonnée en pixels (ligne) du assigneTaillePlateau de la première case
	casePion.ligne = (int)(coordonneesPlateau[1] - (pas / 2));
	// Coordonnée en pixels (colonne) du assigneTaillePlateau de la première case
	casePion.colonne = (int)(coordonneesPlateau[0] + (pas / 2));

	while (index_ligne < TAILLE_PLATEAU) {
		while (index_colonne < TAILLE_PLATEAU) {
			caseLecture.colonne = index_colonne;
			// Traitement de l'affichage de la case (coordonées du assigneTaillePlateau : (coordX, coordY)
			afficheSymbole(pas, &casePion,
				       getCase(&plateau_jeu, &caseLecture),
				       &caseLecture);
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
 * \brief Fonction qui permet d'afficher la grille de jeu.
 *
 * @param coordonneesPlateau Pointeur vers un tableau contenant les coorodonnées en X et en Y des points Haut-Gauche et Bas-Droit du plateau
 */
void afficheGrille(int *coordonneesPlateau)
{

	float pas = calculePas(coordonneesPlateau);

	// Fond
	couleurCourante(35, 59, 110);
	rectangle(coordonneesPlateau[0] + pas, coordonneesPlateau[1] - pas,
		  coordonneesPlateau[2] - pas, coordonneesPlateau[3] + pas);
	// Cases centrales
	couleurCourante(80, 80, 80);
	rectangle(coordonneesPlateau[0] + (2 * pas),
		  coordonneesPlateau[1] - (2 * pas),
		  coordonneesPlateau[2] - (2 * pas),
		  coordonneesPlateau[3] + (2 * pas));
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
 * @param lectureCase Case (plateau) où la flèche doit être placée
 */
void afficheSymbole(float pas, CASE * case_jeu, int joueur, CASE * lectureCase)
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
		afficheSurbrillance(case_jeu, pas, lectureCase);
		break;
	case pioche:
		couleurCourante(210, 210, 210);
		rectangle(case_jeu->colonne - 10, case_jeu->ligne + 10,
			  case_jeu->colonne + 10, case_jeu->ligne - 10);
		break;
	case vide:
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
	epaisseurDeTrait(4.0);
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
	epaisseurDeTrait(4.0);
	ligne((float)(case_jeu->colonne - (pas / 3)),
	      (float)(case_jeu->ligne - (pas / 3)),
	      (float)(case_jeu->colonne + (pas / 3)),
	      (float)(case_jeu->ligne + pas / 3));
	ligne((float)(case_jeu->colonne - (pas / 3)),
	      (float)(case_jeu->ligne + (pas / 3)),
	      (float)(case_jeu->colonne + (pas / 3)),
	      (float)(case_jeu->ligne - pas / 3));

	epaisseurDeTrait(5.0);
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
	pas = (float)((2 * M_PI) / 360.0 * precision);

	xCoin1 = case_jouee->colonne;
	yCoin1 = case_jouee->ligne;
	teta = 0;
	xCoin2 = case_jouee->colonne + (float)(rayon * cos(teta));
	yCoin2 = case_jouee->ligne + (float)(rayon * sin(teta));
	teta = pas;
	xCoin3 = case_jouee->colonne + (float)(rayon * cos(teta));
	yCoin3 = case_jouee->ligne + (float)(rayon * sin(teta));
	triangle(xCoin1, yCoin1, xCoin2, yCoin2, xCoin3, yCoin3);
	for (teta = pas; teta <= 2 * M_PI; teta = teta + pas) {
		xCoin2 = xCoin3;
		yCoin2 = yCoin3;
		xCoin3 = case_jouee->colonne + (float)(rayon * cos(teta));
		yCoin3 = case_jouee->ligne + (float)(rayon * sin(teta));
		triangle(xCoin1, yCoin1, xCoin2, yCoin2, xCoin3, yCoin3);
	}
}

/*!
 * \brief Fonction qui permet d'afficher un cercle de rayon donné.
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
		epaisseurDeTrait(3.0);
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
		epaisseurDeTrait(3.0);
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
	epaisseurDeTrait(5.0);
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
 * @param LARGEURFenetre
 * @param HAUTEURFenetre
 * @return Action à effectuer
 */
int recupereClicAffichage(CASE * retourClic, CLIC * clicSouris,
			  int *coordonneesPlateau, int LARGEURFenetre,
			  int HAUTEURFenetre)
{

	switch (clicSouris->menu) {
	case menuPartie:
	case redirectPioche:
	case redirectRePioche:
	case redirectSurbrillance:
		if (clicSouris->coordX >= coordonneesPlateau[0]
		    && clicSouris->coordY <= coordonneesPlateau[1]
		    && clicSouris->coordX <= coordonneesPlateau[2]
		    && clicSouris->coordY >= coordonneesPlateau[3]) {
			clicPlateau(retourClic, clicSouris, coordonneesPlateau);

			return gereEtatsClic(retourClic, clicSouris->menu);
		}		//Bouton en bas du menu partie
		else if (((clicSouris->coordX >= 0.1 * LARGEURFenetre)
			  && (clicSouris->coordY <= 0.15 * HAUTEURFenetre)
			  && (clicSouris->coordX <= 0.4 * LARGEURFenetre)
			  && (clicSouris->coordY >= 0.05 * HAUTEURFenetre))
			 || ((clicSouris->coordX >= 0.6 * LARGEURFenetre)
			     && (clicSouris->coordY <= 0.15 * HAUTEURFenetre)
			     && (clicSouris->coordX <= 0.9 * LARGEURFenetre)
			     && (clicSouris->coordY >= 0.05 * HAUTEURFenetre))) {
			return clicMenu(clicSouris, LARGEURFenetre,
					HAUTEURFenetre);
		} else {
			if (clicSouris->menu == redirectPioche) {
				return redirectCentral;
			}
			return redirectExterieur;
		}
	case menuPrincipal:
	case menuRegles:
		return clicMenu(clicSouris, LARGEURFenetre, HAUTEURFenetre);
	case menuChoixSymboles:
		return clicMenu(clicSouris, LARGEURFenetre, HAUTEURFenetre);
	case menuVictoire:
	case redirectMenuDefaite:
		return clicMenu(clicSouris, LARGEURFenetre, HAUTEURFenetre);
	default:
		return redirectMenuPrincipal;
	}
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
	return 0;
}

/*!
 * \brief Fonction qui permet de renvoyer l'action à effectuer après un clic dans le plateau de jeu
 *
 * @param clic
 * @param etatMenu
 * @return
 */
int gereEtatsClic(CASE * clic, int etatMenu)
{
	int cLigne = clic->ligne;
	int cCol = clic->colonne;
	switch (etatMenu) {
	case menuPartie:
		if ((cCol == 1) || (cCol == TAILLE_PLATEAU - 2)
		    || (cLigne == TAILLE_PLATEAU - 2) || (cLigne == 1)) {
			return redirectPioche;

		}
		break;
	case redirectSurbrillance:
		if (cLigne == 0 || cLigne == TAILLE_PLATEAU - 1 || cCol == 0
		    || cCol == TAILLE_PLATEAU - 1) {
			return redirectContinue;
		} else {
			return redirectRePioche;
		}
	default:
		break;

	}
	return redirectCentral;
}

/*!
 * \brief Fonction qui permet d'afficher une flèche sur les cases où le joueur peut jouer après une pioche.
 * @param case_jouee Case en pixels où la flèche doit être placée
 * @param pas Pas de la case
 * @param lectureCase Case (plateau) où la flèche doit être placée
 */
void afficheSurbrillance(CASE * case_jouee, float pas, CASE * lectureCase)
{
	couleurCourante(240, 0, 0);
	float xRectangle, yRectangle;
	float xRectangle2, yRectangle2;
	float xTriangle1, yTriangle1, xTriangle2, yTriangle2, xTriangle3,
	    yTriangle3;

	if (lectureCase->ligne == 0) {
		xRectangle = case_jouee->colonne - 10;
		yRectangle = case_jouee->ligne + (pas / 2 - 5);
		xRectangle2 = case_jouee->colonne + 10;
		yRectangle2 = case_jouee->ligne;
		xTriangle1 = case_jouee->colonne - 30;
		yTriangle1 = yRectangle2;
		xTriangle2 = case_jouee->colonne + 30;
		yTriangle2 = yRectangle2;
		xTriangle3 = case_jouee->colonne;
		yTriangle3 = case_jouee->ligne - (pas / 4);
	} else if (lectureCase->ligne == 6) {
		xRectangle = case_jouee->colonne - 10;
		yRectangle = case_jouee->ligne - (pas / 2 - 5);
		xRectangle2 = case_jouee->colonne + 10;
		yRectangle2 = case_jouee->ligne;
		xTriangle1 = case_jouee->colonne - 30;
		yTriangle1 = yRectangle2;
		xTriangle2 = case_jouee->colonne + 30;
		yTriangle2 = yRectangle2;
		xTriangle3 = case_jouee->colonne;
		yTriangle3 = case_jouee->ligne + (pas / 4);
	} else if (lectureCase->colonne == 0) {
		xRectangle = case_jouee->colonne - (pas / 2 - 5);
		yRectangle = case_jouee->ligne + 10;
		xRectangle2 = case_jouee->colonne;
		yRectangle2 = case_jouee->ligne - 10;
		xTriangle1 = xRectangle2;
		yTriangle1 = case_jouee->ligne - 30;
		xTriangle2 = xRectangle2;
		yTriangle2 = case_jouee->ligne + 30;
		xTriangle3 = case_jouee->colonne + (pas / 4);
		yTriangle3 = case_jouee->ligne;
	} else if (lectureCase->colonne == 6) {
		xRectangle = case_jouee->colonne + (pas / 2 - 5);
		yRectangle = case_jouee->ligne + 10;
		xRectangle2 = case_jouee->colonne;
		yRectangle2 = case_jouee->ligne - 10;
		xTriangle1 = xRectangle2;
		yTriangle1 = case_jouee->ligne - 30;
		xTriangle2 = xRectangle2;
		yTriangle2 = case_jouee->ligne + 30;
		xTriangle3 = case_jouee->colonne - (pas / 4);
		yTriangle3 = case_jouee->ligne;
	} else {
		return;
	}
	rectangle(xRectangle, yRectangle, xRectangle2, yRectangle2);
	triangle(xTriangle1, yTriangle1, xTriangle2, yTriangle2, xTriangle3,
		 yTriangle3);
}

/*!
 * \brief Fonction qui redimensionne automatiquement pour garder un ratio minimal
 */
void redimensionnementForce(int menu)
{
	int largeur;
	int hauteur;
	largeur = 500;
	hauteur = 580;
	if (menu == menuRegles) {
		largeur = 725;
		hauteur = 650;
	}
	if ((largeurFenetre() < largeur) || (hauteurFenetre() < hauteur)) {
		redimensionneFenetre(largeur, hauteur);
	}
}

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
int gestionAffichage(int menu, int *coordonneesGrille,
		     int LargeurFenetreCourante, int HauteurFenetreCourante,
		     DonneesImageRGB * imageRegles, int joueurCourant)
{
	switch (menu) {
	case menuPrincipal:
		afficheMenuPrincipal(LargeurFenetreCourante,
				     HauteurFenetreCourante);
		break;
	case redirectMenuChoixSymboleS:
		afficheMenuSelection(LargeurFenetreCourante,
				     HauteurFenetreCourante);
		break;
	case redirectMenuRegles:
		afficheRegles(imageRegles, LargeurFenetreCourante,
			      HauteurFenetreCourante);
		break;
	case menuPartie:
	case redirectSurbrillance:
	case redirectRePioche:
	case redirectPioche:
	case redirectExterieur:
		affichePlateau(coordonneesGrille,
			       LargeurFenetreCourante, HauteurFenetreCourante);
		//Affichage du joueur courant
		afficheJoueurCourant(joueurCourant, LargeurFenetreCourante,
				     HauteurFenetreCourante);
		break;
	case redirectMenuVictoire:
		afficheVictoire(LargeurFenetreCourante, HauteurFenetreCourante,
				joueurCourant);
		break;
	case redirectMenuDefaite:
		afficheDefaite(LargeurFenetreCourante, HauteurFenetreCourante);
		break;
	case redirectQuitter:
		libereDonneesImageRGB(&imageRegles);
		exit(EXIT_SUCCESS);
	}
	return 0;
}

/*!
 * \brief Fonction qui affiche le menu où le joueur choisit son mode de jeu
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @return 0 pour ok, -1 pour ko
 */
int afficheMenuPrincipal(int LARGEURFenetre, int HAUTEURFenetre)
{
	static int time = 0;
	//bleu
	static float rouge = 239;
	static float vert = 240;
	static float bleu = 244;
	int anim = 125;
	if (time <= anim) {
		rouge = rouge - (239 - 65) / (float)anim;
		vert = vert - (240 - 95) / (float)anim;
		bleu = bleu - (244 - 157) / (float)anim;
		couleurCourante((int)rouge, (int)vert, (int)bleu);
		time += 1;
	} else {
		couleurCourante(65, 95, 157);
	}
	float largeurTexteTitre = 0.1 * LARGEURFenetre;
	float largeurBoutons = 0.05 * LARGEURFenetre;
	float largeurTexteBoutonsMode = tailleChaine("1 VS 1", largeurBoutons);
	float largeurTexteBoutonsQ = tailleChaine("Quitter", largeurBoutons);
	float largeurTexteBoutonsR = tailleChaine("Regles", largeurBoutons);
	epaisseurDeTrait(3.5);
	afficheChaine("Quixo", largeurTexteTitre,
		      0.4 * LARGEURFenetre - (largeurTexteTitre / 2),
		      0.8 * HAUTEURFenetre);

	epaisseurDeTrait(3);
	if ((abscisseSouris() >= 0.15 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.7 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.45 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.55 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	//1VS1
	rectangle(0.15 * LARGEURFenetre, 0.7 * HAUTEURFenetre,
		  0.45 * LARGEURFenetre, 0.55 * HAUTEURFenetre);
	//Gris
	couleurCourante(239, 240, 255);
	afficheChaine("1 VS 1", largeurBoutons,
		      (0.30 * LARGEURFenetre) - (largeurTexteBoutonsMode / 2),
		      0.60 * HAUTEURFenetre);

	//1 VS IA
	if ((abscisseSouris() >= 0.55 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.7 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.85 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.55 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	rectangle(0.55 * LARGEURFenetre, 0.7 * HAUTEURFenetre,
		  0.85 * LARGEURFenetre, 0.55 * HAUTEURFenetre);
	couleurCourante(239, 240, 255);
	afficheChaine("1 VS IA", largeurBoutons,
		      0.7 * LARGEURFenetre - (largeurTexteBoutonsMode / 2),
		      0.60 * HAUTEURFenetre);

	//Règles
	if ((abscisseSouris() >= 0.15 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.45 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.45 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.3 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	rectangle(0.15 * LARGEURFenetre, 0.45 * HAUTEURFenetre,
		  0.45 * LARGEURFenetre, 0.3 * HAUTEURFenetre);
	couleurCourante(239, 240, 255);
	afficheChaine("Regles", largeurBoutons,
		      0.3 * LARGEURFenetre - (largeurTexteBoutonsR / 2),
		      0.35 * HAUTEURFenetre);

	//Quitter
	if ((abscisseSouris() >= 0.55 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.45 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.85 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.3 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	rectangle(0.55 * LARGEURFenetre, 0.45 * HAUTEURFenetre,
		  0.85 * LARGEURFenetre, 0.3 * HAUTEURFenetre);
	couleurCourante(239, 240, 255);
	afficheChaine("Quitter", largeurBoutons,
		      0.7 * LARGEURFenetre - (largeurTexteBoutonsQ / 2),
		      0.35 * HAUTEURFenetre);

	couleurCourante(65, 95, 157);
	afficheChaine
	    ("Cree par G. Desrumaux, M. Bouteille, P. Parrat, C. Bostyn",
	     0.03 * LARGEURFenetre,
	     LARGEURFenetre / 2 -
	     (tailleChaine
	      ("Cree par G. Desrumaux, M. Bouteille, P. Parrat, C. Bostyn",
	       0.03 * LARGEURFenetre) / 2), 10);

	return 0;
}

/*!
 * \brief Fonction qui affiche le menu où les joueurs choisissent leurs symboles
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @return 0
 */
int afficheMenuSelection(int LARGEURFenetre, int HAUTEURFenetre)
{
	float largeurTexteTitre = 0.1 * LARGEURFenetre;
	float largeurBoutons = 0.05 * LARGEURFenetre;
	float largeurTexteBoutonsMode = tailleChaine("Retour", largeurBoutons);
	float largeurTexteBoutonsC = tailleChaine("Croix", largeurBoutons);
	float largeurTexteBoutonsR = tailleChaine("Cercle", largeurBoutons);
	float largeurTexteSymbole =
	    tailleChaine("Choisissez un symbole :", largeurBoutons);

	//Bleu
	couleurCourante(65, 95, 157);
	epaisseurDeTrait(3.5);
	afficheChaine("Quixo", largeurTexteTitre,
		      0.4 * LARGEURFenetre - (largeurTexteTitre / 2),
		      0.8 * HAUTEURFenetre);
	afficheChaine("Choisissez un symbole :", largeurBoutons,
		      (LARGEURFenetre / 2) - (largeurTexteSymbole / 2),
		      0.70 * HAUTEURFenetre);

	if ((abscisseSouris() >= 0.15 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.6 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.45 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.45 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	//gauche
	rectangle(0.15 * LARGEURFenetre, 0.60 * HAUTEURFenetre,
		  0.45 * LARGEURFenetre, 0.45 * HAUTEURFenetre);
	//gris
	couleurCourante(239, 240, 255);
	afficheChaine("Croix", largeurBoutons,
		      0.3 * LARGEURFenetre - (largeurTexteBoutonsC / 2),
		      0.5 * HAUTEURFenetre);
	//droite
	if ((abscisseSouris() >= 0.55 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.6 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.85 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.45 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	rectangle(0.55 * LARGEURFenetre, 0.60 * HAUTEURFenetre,
		  0.85 * LARGEURFenetre, 0.45 * HAUTEURFenetre);
	couleurCourante(239, 240, 255);
	afficheChaine("Cercle", largeurBoutons,
		      0.7 * LARGEURFenetre - (largeurTexteBoutonsR / 2),
		      0.5 * HAUTEURFenetre);

	if ((abscisseSouris() >= 0.35 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.3 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.65 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.15 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	rectangle(0.5 * LARGEURFenetre - (largeurTexteBoutonsMode / 0.9),
		  0.3 * HAUTEURFenetre,
		  0.5 * LARGEURFenetre + (largeurTexteBoutonsMode / 0.9),
		  0.15 * HAUTEURFenetre);
	couleurCourante(239, 240, 255);
	afficheChaine("Retour", largeurBoutons,
		      0.5 * LARGEURFenetre - (largeurTexteBoutonsMode / 2),
		      0.20 * HAUTEURFenetre);

	return 0;

}

/*!
 * \brief Fonction qui affiche les règles du jeu
 * @param image Image bmp à afficher
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @return 0
 */
int afficheRegles(DonneesImageRGB * image, int LARGEURFenetre,
		  int HAUTEURFenetre)
{
	float largeurTexteTitre = 0.1 * LARGEURFenetre;
	float largeurBoutons = 0.05 * LARGEURFenetre;
	float largeurTexteBoutonsMode = tailleChaine("Retour", largeurBoutons);

	//Bleu
	couleurCourante(65, 95, 157);
	epaisseurDeTrait(3.5);
	afficheChaine("Quixo", largeurTexteTitre,
		      0.4 * LARGEURFenetre - (largeurTexteTitre / 2),
		      0.8 * HAUTEURFenetre);
	if ((abscisseSouris() >= 0.35 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.3 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.65 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.15 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	rectangle(0.5 * LARGEURFenetre - (largeurTexteBoutonsMode / 0.9),
		  0.3 * HAUTEURFenetre,
		  0.5 * LARGEURFenetre + (largeurTexteBoutonsMode / 0.9),
		  0.15 * HAUTEURFenetre);
	//Gris
	couleurCourante(239, 240, 255);
	afficheChaine("Retour", largeurBoutons,
		      0.50 * LARGEURFenetre - (largeurTexteBoutonsMode / 2),
		      0.20 * HAUTEURFenetre);
	if (image != NULL) {
		ecrisImage((largeurFenetre() - image->largeurImage) / 2,
			   (hauteurFenetre() - image->hauteurImage) / 1.5,
			   image->largeurImage, image->hauteurImage,
			   image->donneesRGB);
	}
	return 0;
}

/*!
 * \brief Fonction qui gère le clic dans les menus à l'aide des boutons
 * @param clicSouris Clic du joueur sur l'affichage graphique (coordonnées en X et Y) et menu courant
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @return Action à effectuer
 */
int clicMenu(CLIC * clicSouris, int LARGEURFenetre, int HAUTEURFenetre)
{
	// Le menu courant est le menu Principal
	if (clicSouris->menu == menuPrincipal) {
		//1 VS 1
		if ((clicSouris->coordX >= 0.15 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.7 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.45 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.55 * HAUTEURFenetre)) {
			clicSouris->menu = redirectMenuChoixSymboleS;
			clicSouris->mode = V1;
		}
		//1 VS IA
		if ((clicSouris->coordX >= 0.55 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.7 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.85 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.55 * HAUTEURFenetre)) {
			clicSouris->menu = redirectMenuChoixSymboleS;
			clicSouris->mode = VIA;
		}
		//Règles
		if ((clicSouris->coordX >= 0.15 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.45 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.45 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.3 * HAUTEURFenetre)) {
			clicSouris->menu = redirectMenuRegles;
		}
		//Quitter
		if ((clicSouris->coordX >= 0.55 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.45 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.85 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.3 * HAUTEURFenetre)) {
			clicSouris->menu = redirectQuitter;
		}
		// on renvoie le menuCourant
		return (clicSouris->menu);
		// Le menu courant est le menu des règles
	} else if (clicSouris->menu == menuRegles) {
		if ((clicSouris->coordX >= 0.35 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.3 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.65 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.15 * HAUTEURFenetre)) {
			return redirectMenuPrincipal;
		}

		return (clicSouris->menu);
		// Le menu courant est le menu choix symbole
	} else if (clicSouris->menu == menuChoixSymboles) {
		//Retour
		if ((clicSouris->coordX >= 0.35 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.3 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.65 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.15 * HAUTEURFenetre)) {
			clicSouris->menu = redirectMenuPrincipal;
		}
		// Croix vers menuPartie
		if ((clicSouris->coordX >= 0.15 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.60 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.45 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.45 * HAUTEURFenetre)) {
			clicSouris->joueurCourant = croix_gauche;
			clicSouris->menu = redirectMenuPartie;
		}
		// Rond vers menu Partie
		if ((clicSouris->coordX >= 0.55 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.60 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.85 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.45 * HAUTEURFenetre)) {
			clicSouris->joueurCourant = rond_gauche;
			clicSouris->menu = redirectMenuPartie;
		}
		return (clicSouris->menu);
		// Le menu courant est le menu partie
	} else if (clicSouris->menu == menuPartie
		   || clicSouris->menu == redirectSurbrillance) {
		//Règles
		if ((clicSouris->coordX >= 0.1 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.2 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.4 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.05 * HAUTEURFenetre)) {
			clicSouris->menu = redirectMenuRegles;
		}
		//Menu Principal
		if ((clicSouris->coordX >= 0.6 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.2 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.9 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.05 * HAUTEURFenetre)) {
			clicSouris->menu = redirectMenuPrincipal;
		}
		return (clicSouris->menu);

		// Le menu courant est le menu victoire
	} else if (clicSouris->menu == menuVictoire) {
		//Menu Principal
		if ((clicSouris->coordX >= 0.1 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.25 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.4 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.1 * HAUTEURFenetre)) {
			clicSouris->menu = redirectRecommencer;
		}
		//Quitter
		if ((clicSouris->coordX >= 0.6 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.25 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.9 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.1 * HAUTEURFenetre)) {
			clicSouris->menu = redirectQuitter;
		}
		return (clicSouris->menu);
	} else if (clicSouris->menu == redirectMenuDefaite) {
		//Menu Principal
		if ((clicSouris->coordX >= 0.1 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.25 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.4 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.1 * HAUTEURFenetre)) {
			clicSouris->menu = redirectRecommencerDef;
		}
		//Quitter
		if ((clicSouris->coordX >= 0.6 * LARGEURFenetre)
		    && (clicSouris->coordY <= 0.25 * HAUTEURFenetre)
		    && (clicSouris->coordX <= 0.9 * LARGEURFenetre)
		    && (clicSouris->coordY >= 0.1 * HAUTEURFenetre)) {
			clicSouris->menu = redirectQuitter;
		}
		return (clicSouris->menu);
	} else {
		return redirectMenuPrincipal;
	}
}

/*!
 * \brief Fonction qui affiche les boutons dans le menu partie
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @return 0
 */
int afficheBouton(int LARGEURFenetre, int HAUTEURFenetre)
{
	float largeurBoutons = 0.05 * LARGEURFenetre;
	float largeurTexteBoutonsQ = tailleChaine("Menu", largeurBoutons);
	float largeurTexteBoutonsR = tailleChaine("Regles", largeurBoutons);
//Bleu
	if ((abscisseSouris() >= 0.1 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.2 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.4 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.05 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	//Rectangle gauche
	rectangle(0.10 * LARGEURFenetre, 0.2 * HAUTEURFenetre,
		  0.40 * LARGEURFenetre, 0.05 * HAUTEURFenetre);
	//Rectangle droite
	if ((abscisseSouris() >= 0.6 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.2 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.9 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.05 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	rectangle(0.60 * LARGEURFenetre, 0.2 * HAUTEURFenetre,
		  0.90 * LARGEURFenetre, 0.05 * HAUTEURFenetre);
	//Gris
	couleurCourante(239, 240, 255);
	epaisseurDeTrait(2);
	afficheChaine("Regles", largeurBoutons,
		      0.25 * LARGEURFenetre - (largeurTexteBoutonsR / 2),
		      0.1 * HAUTEURFenetre);
	afficheChaine("Menu", largeurBoutons,
		      0.75 * LARGEURFenetre - (largeurTexteBoutonsQ / 2),
		      0.1 * HAUTEURFenetre);

	return 0;
}

/*!
 * \brief Fonction qui affiche le joueur courant dans le menu partie
 * @param LARGEURFenetre Largeur de la fenêtre
 * @param HAUTEURFenetre Hauteur de la fenêtre
 * @param joueurCourant Joueur qui doit jouer
 * @return 0
 */
int afficheJoueurCourant(int joueurCourant, int LARGEURFenetre,
			 int HAUTEURFenetre)
{
	int largeurTitre = tailleChaine("Quixo", 0.025 * LARGEURFenetre);
	//bleu
	couleurCourante(65, 95, 157);
	rectangle(0, HAUTEURFenetre, LARGEURFenetre, HAUTEURFenetre - 50);
	epaisseurDeTrait(1.5);
	couleurCourante(239, 240, 255);
	afficheChaine("Quixo", 0.025 * LARGEURFenetre,
		      0.5 * LARGEURFenetre - (largeurTitre / 2),
		      HAUTEURFenetre - 45);

	CASE caseADessinerCroix, caseADessinerRond;
	caseADessinerCroix.colonne = 25;
	caseADessinerCroix.ligne = HAUTEURFenetre - 60 - 25;

	caseADessinerRond.colonne = LARGEURFenetre - 25;
	caseADessinerRond.ligne = HAUTEURFenetre - 60 - 25;

	if (joueurCourant == 3) {
		couleurCourante(65, 95, 157);
	} else {
		couleurCourante(150, 150, 150);
	}
	rectangle(0, HAUTEURFenetre - 60, 50, HAUTEURFenetre - 60 - 50);
	couleurCourante(239, 240, 255);
	afficheCroixPoint(&caseADessinerCroix, 45, 2);

	if (joueurCourant == 4) {
		couleurCourante(65, 95, 157);
	} else {
		couleurCourante(150, 150, 150);
	}
	//Coin haut gauche
	rectangle(LARGEURFenetre - 50, HAUTEURFenetre - 60, LARGEURFenetre,
		  HAUTEURFenetre - 60 - 50);
	couleurCourante(239, 240, 255);
	afficheRondPoint(&caseADessinerRond, 15, 2);
	return 0;
}

/*!
 * \brief Fonction qui affiche le score
 * @param LARGEURFenetre largeur de la fenêtre
 * @param HAUTEURFenetre hauteur de la fenêtre
 * @param joueurCourant Joueur ayant gagné la partie
 * @return 0
 */
int afficheVictoire(int LARGEURFenetre, int HAUTEURFenetre, int joueurCourant)
{
	float largeurTexteTitre = 0.1 * LARGEURFenetre;
	float largeurTexte = 0.08 * LARGEURFenetre;
	float largeurBoutons = 0.05 * LARGEURFenetre;
	float largeurTexteBoutonsMode = tailleChaine("Rejouer", largeurBoutons);
	float largeurTexteBoutonsQ = tailleChaine("Quitter", largeurBoutons);

	//Bleu
	couleurCourante(65, 95, 157);
	rectangle(0, HAUTEURFenetre, LARGEURFenetre, HAUTEURFenetre - 180);
	epaisseurDeTrait(3.5);
	couleurCourante(239, 240, 255);
	afficheChaine("Quixo", largeurTexteTitre,
		      0.4 * LARGEURFenetre - (largeurTexteTitre / 2),
		      0.8 * HAUTEURFenetre);
	couleurCourante(65, 95, 157);
	afficheChaine("Bravo",
		      largeurTexte,
		      0.5 * LARGEURFenetre -
		      (tailleChaine("Bravo", largeurTexte) / 2) -
		      (LARGEURFenetre / 10), 0.6 * HAUTEURFenetre);
	CASE dessin;
	dessin.colonne =
	    (int)(0.5 * LARGEURFenetre +
		  (tailleChaine("Bravo", largeurTexte) / 2));
	dessin.ligne = (int)(0.6 * HAUTEURFenetre + largeurTexte / 2.5);
	if (joueurCourant == 3) {
		afficheCroixPoint(&dessin, largeurTexteTitre, 2);
	} else if (joueurCourant == 4) {
		afficheRondPoint(&dessin, largeurTexteTitre / 3, 2);
	}
	afficheChaine("!", largeurTexte,
		      0.5 * LARGEURFenetre +
		      (tailleChaine("Bravo", largeurTexte) / 2) +
		      (LARGEURFenetre / 10), 0.6 * HAUTEURFenetre);
	afficheChaine("Tu as gagne !", largeurTexte,
		      0.5 * LARGEURFenetre -
		      (tailleChaine("Tu as gagne !", largeurTexte) / 2),
		      0.45 * HAUTEURFenetre);

	if ((abscisseSouris() >= 0.1 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.25 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.4 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.1 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	//Rectangle gauche
	rectangle(0.10 * LARGEURFenetre, 0.25 * HAUTEURFenetre,
		  0.40 * LARGEURFenetre, 0.1 * HAUTEURFenetre);
	if ((abscisseSouris() >= 0.6 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.25 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.9 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.1 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	//Rectangle droite
	rectangle(0.60 * LARGEURFenetre, 0.25 * HAUTEURFenetre,
		  0.90 * LARGEURFenetre, 0.1 * HAUTEURFenetre);
	//Gris
	couleurCourante(239, 240, 255);
	epaisseurDeTrait(2);
	afficheChaine("Rejouer", largeurBoutons,
		      0.25 * LARGEURFenetre - (largeurTexteBoutonsMode / 2),
		      0.15 * HAUTEURFenetre);
	afficheChaine("Quitter", largeurBoutons,
		      0.75 * LARGEURFenetre - (largeurTexteBoutonsQ / 2),
		      0.15 * HAUTEURFenetre);
	return 0;
}

/*!
 * \brief Fonction qui permet de gérer la taille d'affichage du plateau de jeu
 * @param coordonneesPlateau Tableau de gestion des coordonnées du plateau
 * @return
 */
void assigneTaillePlateau(int *coordonneesPlateau)
{
	int hauteurMilieu = hauteurFenetre() / 2;
	int largeurMilieu = largeurFenetre() / 2;
	int tailleX = TAILLE_PLATEAU * (0.1 * largeurMilieu);
	int tailleY = TAILLE_PLATEAU * (0.1 * hauteurMilieu);
	if (hauteurMilieu >= largeurMilieu) {
		coordonneesPlateau[0] = largeurMilieu - tailleX;
		coordonneesPlateau[1] = hauteurMilieu + tailleX + 40;
		coordonneesPlateau[2] = largeurMilieu + tailleX;
		coordonneesPlateau[3] = hauteurMilieu - tailleX + 40;
	} else {
		coordonneesPlateau[0] = largeurMilieu - tailleY;
		coordonneesPlateau[1] = hauteurMilieu + tailleY + 40;
		coordonneesPlateau[2] = largeurMilieu + tailleY;
		coordonneesPlateau[3] = hauteurMilieu - tailleY + 40;
	}
}

/*!
 * \brief Fonction qui permet d'afficher le menu de défaite lorsque le joueur perd contre l'ordinateur
 *
 * @param LARGEURFenetre Largeur de la fenêtre en pixels
 * @param HAUTEURFenetre Hauteur de la fenêtre en pixels
 */
void afficheDefaite(int LARGEURFenetre, int HAUTEURFenetre)
{
	float largeurTexte = 0.05 * LARGEURFenetre;
	couleurCourante(65, 95, 157);
	afficheChaine("Desole tu as",
		      largeurTexte,
		      0.5 * LARGEURFenetre -
		      (tailleChaine("Desole tu as", largeurTexte) / 2),
		      0.6 * HAUTEURFenetre);
	afficheChaine("perdu contre l'ordinateur", largeurTexte,
		      0.5 * LARGEURFenetre -
		      (tailleChaine("perdu contre l'ordinateur", largeurTexte) /
		       2), 0.5 * HAUTEURFenetre);

	float largeurTexteTitre = 0.1 * LARGEURFenetre;
	float largeurBoutons = 0.05 * LARGEURFenetre;
	float largeurTexteBoutonsMode = tailleChaine("Rejouer", largeurBoutons);
	float largeurTexteBoutonsQ = tailleChaine("Quitter", largeurBoutons);

	//Bleu
	couleurCourante(65, 95, 157);
	rectangle(0, HAUTEURFenetre, LARGEURFenetre, HAUTEURFenetre - 180);
	epaisseurDeTrait(3.5);
	couleurCourante(239, 240, 255);
	afficheChaine("Quixo", largeurTexteTitre,
		      0.4 * LARGEURFenetre - (largeurTexteTitre / 2),
		      0.8 * HAUTEURFenetre);

	if ((abscisseSouris() >= 0.1 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.25 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.4 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.1 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	//Rectangle gauche
	rectangle(0.10 * LARGEURFenetre, 0.25 * HAUTEURFenetre,
		  0.40 * LARGEURFenetre, 0.1 * HAUTEURFenetre);
	if ((abscisseSouris() >= 0.6 * LARGEURFenetre)
	    && (ordonneeSouris() <= 0.25 * HAUTEURFenetre)
	    && (abscisseSouris() <= 0.9 * LARGEURFenetre)
	    && (ordonneeSouris() >= 0.1 * HAUTEURFenetre)) {
		couleurCourante(90, 105, 180);
	} else {
		couleurCourante(65, 95, 157);
	}
	//Rectangle droite
	rectangle(0.60 * LARGEURFenetre, 0.25 * HAUTEURFenetre,
		  0.90 * LARGEURFenetre, 0.1 * HAUTEURFenetre);
	//Gris
	couleurCourante(239, 240, 255);
	epaisseurDeTrait(2);
	afficheChaine("Rejouer", largeurBoutons,
		      0.25 * LARGEURFenetre - (largeurTexteBoutonsMode / 2),
		      0.15 * HAUTEURFenetre);
	afficheChaine("Quitter", largeurBoutons,
		      0.75 * LARGEURFenetre - (largeurTexteBoutonsQ / 2),
		      0.15 * HAUTEURFenetre);
}
