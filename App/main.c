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
	static int LargeurFenetreCourante = LargeurFenetre;
	static int HauteurFenetreCourante = HauteurFenetre;
	static CLIC clic;
	static CASE retourClic, savePioche;
	static int joueurCourant;

	static int menuCourant;

	switch (evenement) {
	case Initialisation:
		initPlateau();

		demandeAnimation_ips(24);	// Configure le système pour un mode 50 images par seconde

		coordonneesGrille[0] = 100;
		coordonneesGrille[1] = 700;
		coordonneesGrille[2] = 700;
		coordonneesGrille[3] = 100;

		menuCourant = menuPrincipal;
		break;

	case Affichage:

		// On part d'un fond d'ecran blanc
		effaceFenetre(239, 240, 244);
		switch (menuCourant) {
		case menuPrincipal:
			afficheMenuPrincipal(LargeurFenetreCourante,
					     HauteurFenetreCourante);
			break;
		case redirectMenuChoixSymboleS:
			afficheMenuSelection(LargeurFenetreCourante,
					     HauteurFenetreCourante);
			break;
		case redirectMenuRegles:
			afficheRegles(LargeurFenetreCourante,
				      HauteurFenetreCourante);
			break;
		case menuPartie:
		case redirectSurbrillance:
		case redirectRePioche:
		case redirectPioche:
			affichePlateau(coordonneesGrille);
			break;
		case redirectQuitter:
			exit(0);
		}
		rafraichisFenetre();
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
			menuCourant =
			    recupereClicAffichage(&retourClic, &clic,
						  coordonneesGrille,
						  LargeurFenetreCourante,
						  HauteurFenetreCourante);
			printf("donne = %d\n", menuCourant);

			switch (menuCourant) {
			case redirectMenuPrincipal:
				menuCourant = menuPrincipal;
				break;
			case redirectMenuChoixSymboleS:
				menuCourant = menuChoixSymboles;
				break;
			case redirectMenuRegles:
				menuCourant = menuRegles;
				break;
			case redirectMenuPartie:
				joueurCourant = clic.joueurCourant;
				menuCourant = menuPartie;
				break;
			case menuPartie:
			case redirectSurbrillance:
			case redirectPioche:
			case redirectRePioche:
			case redirectContinue:

				menuCourant =
				    calculeTour(&joueurCourant, menuCourant,
						&retourClic, &savePioche);
				break;
			}
			printf("Redonne = %d\n", menuCourant);
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
		LargeurFenetreCourante = largeurFenetre();
		HauteurFenetreCourante = hauteurFenetre();
		break;
	}
}
