/*!
* \file main.c
* \brief Fichier main du jeu
* \author desrumaux
* \date 31/01/17
*/
#include "modules/moteur.h"
#include "modules/affichage.h"

PLATEAU plateau_jeu;

/*!
 * \brief Fonction principale du jeu
 * @return int
 */
int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("Quixo", LargeurFenetre, HauteurFenetre);

	lanceBoucleEvenements();

	return 0;
}

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
	static int coordonneesGrille[4];
	static int LARGEURFenetre;
	static int HAUTEURFenetre;
	static CLIC clic;
	static CASE retourClic, savePioche;
	static int joueurCourant;
	static int menuCourant;

	static int donnees = 0;
	/*static int i = 0;
	   int j = 0; */

	switch (evenement) {
	case Initialisation:
		initPlateau();

		demandeAnimation_ips(24);	// Configure le système pour un mode 50 images par seconde

		coordonneesGrille[0] = 100;
		coordonneesGrille[1] = 700;
		coordonneesGrille[2] = 700;
		coordonneesGrille[3] = 100;

		joueurCourant = rond_gauche;

		menuCourant = menuPartie;
		break;

	case Affichage:

		// On part d'un fond d'ecran blanc
		effaceFenetre(239, 240, 244);
		if (donnees == 0) {
			afficheMenuPrincipal(LARGEURFenetre, HAUTEURFenetre);
		}

		if (donnees == redirectMenuChoixSymboleS) {
			afficheMenuSelection(LARGEURFenetre, HAUTEURFenetre);

		}

		if (donnees == redirectMenuRegles) {
			afficheRegles(LARGEURFenetre, HAUTEURFenetre);
		}

		if (donnees == redirectMenuPrincipal) {
			afficheMenuPrincipal(LARGEURFenetre, HAUTEURFenetre);
		}

		if (donnees == redirectMenuPartie) {

			affichePlateau(coordonneesGrille);
		}

		if (donnees == redirectQuitter) {
			exit(0);
		}
		rafraichisFenetre();

		//affichePlateau(coordonneesGrille);
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
		if (etatBoutonSouris() == GaucheAppuye) {
			// Préparation du clic à envoyer à la fonction
			clic.coordX = abscisseSouris();
			clic.coordY = ordonneeSouris();
			clic.joueurCourant = joueurCourant;
			clic.menu = menuCourant;
			menuCourant = recupereClicAffichage(&retourClic, &clic,
							    coordonneesGrille);
			menuCourant =
			    calculeTour(&joueurCourant, menuCourant,
					&retourClic, &savePioche);
			donnees = recupereClicAffichage(&retourClic, &clic,
							coordonneesGrille,
							LARGEURFenetre,
							HAUTEURFenetre);
			printf("donne = %d\n", donnees);

			if (donnees == 0) {
				clic.menu = menuPrincipal;
			}

			if (donnees == redirectMenuChoixSymboleS) {
				clic.menu = menuChoixSymboles;

			}

			if (donnees == redirectMenuRegles) {
				clic.menu = menuRegles;
			}

			/*      if (clic.menu == redirectSurbrillance) {
			   calculeSurbrillance(&retourClic);
			   } */
		}
		break;
	case Souris:		// Si la souris est deplacee
		break;
	case Inactivite:	// Quand aucun message n'est disponible
		break;
	case Redimensionnement:	// La taille de la fenetre a ete modifie ou on est passe en plein ecran
		// Donc le systeme nous en informe
		printf("Largeur : %d\t", largeurFenetre());
		printf("Hauteur : %d\n", hauteurFenetre());
		// Force une taille de fenêtre minimale
		redimensionnementForce();
		LARGEURFenetre = largeurFenetre();
		HAUTEURFenetre = hauteurFenetre();
		break;
	}
}
