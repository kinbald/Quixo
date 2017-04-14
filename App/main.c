/*!
* \file main.c
* \brief Fichier main du jeu
* \author desrumaux
* \date 31/01/17
*/
#include "modules/moteur.h"
#include "modules/affichage.h"

/*!
 * Plateau de jeu
 */
PLATEAU plateau_jeu;

/*!
 * Nombre de coups évalués
 */
int nombreCoups;

/*!
 * \brief Fonction principale du jeu
 * @return int
 */
int main(int argc, char **argv)
{
	// Initialisation seed
	srand((unsigned int)time(NULL));
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
 * @param evenement EvenementGfx
 */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false;	// Pour savoir si on est en mode plein écran ou pas
	static int coordonneesGrille[4];
	static int LargeurFenetreCourante = LargeurFenetre;
	static int HauteurFenetreCourante = HauteurFenetre;
	static DonneesImageRGB *imageRegles = NULL;
	static CLIC clic;
	static CASE retourClic, savePioche;
	static int joueurCourant;
	static int MODE;
	char nombre[20];

	static int menuCourant;

	switch (evenement) {
	case Initialisation:
		initPlateau();
		// Variable affichage nombre appels IA
		nombreCoups = 0;

		if (imageRegles == NULL) {
			imageRegles = lisBMPRGB("deuxjoueurs.bmp");
		}
		demandeAnimation_ips(25);	// Configure le système pour un mode 24 images par seconde
		assigneTaillePlateau(coordonneesGrille);
		menuCourant = menuPrincipal;
		MODE = -1;
		break;
	case Affichage:
		// On part d'un fond d'ecran blanc
		effaceFenetre(239, 240, 244);
		//afficheTitre(150, 600);
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
			afficheRegles(imageRegles, LargeurFenetreCourante,
				      HauteurFenetreCourante);
			break;
		case menuPartie:
		case redirectSurbrillance:
		case redirectRePioche:
		case redirectPioche:
			affichePlateau(coordonneesGrille);
			// <-> Affichage du nombre d'appels à l'IA
			sprintf(nombre, "%d", nombreCoups);
			couleurCourante(255, 0, 0);
			epaisseurDeTrait(1.5);
			afficheChaine(nombre, 10, 40, 600);
			// <->
			break;

		case menuVictoire:
			afficheChaine("Victoire de ", 40, 100, 100);
			sprintf(nombre, "%d", joueurCourant);
			couleurCourante(255, 0, 0);
			epaisseurDeTrait(1.5);
			afficheChaine(nombre, 40, 380, 100);
			break;

		case redirectQuitter:
			libereDonneesImageRGB(&imageRegles);
			exit(EXIT_SUCCESS);
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
			libereDonneesImageRGB(&imageRegles);
			exit(EXIT_SUCCESS);
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
			rafraichisFenetre();	// Force un rafraîchissement
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
			printf("Clic affichage : %d\nJoueur : %d\n",
			       menuCourant, joueurCourant);
			switch (menuCourant) {
			case redirectMenuPrincipal:
				menuCourant = menuPrincipal;
				break;
			case redirectMenuChoixSymboleS:
				menuCourant = menuChoixSymboles;
				MODE = clic.mode;
				break;
			case redirectMenuRegles:
				menuCourant = menuRegles;
				break;
			case redirectMenuPartie:
				joueurCourant = clic.joueurCourant;
				menuCourant = menuPartie;
				break;
			case redirectRePioche:
			case menuPartie:
			case redirectSurbrillance:
			case redirectPioche:
			case redirectContinue:
				if (clic.menu == menuPartie
				    && menuCourant == redirectRePioche) {
					menuCourant = menuPartie;
					break;
				}
				menuCourant =
				    calculeTour(&joueurCourant, menuCourant,
						&retourClic, &savePioche);
				// On fait jouer l'IA lors du changement de joueur
				if (menuCourant == redirectAdversaire) {
					if (MODE == VIA) {
						menuCourant =
						    calculeTour(&joueurCourant,
								jeuIA,
								&retourClic,
								&savePioche);
					} else {
						menuCourant = menuPartie;
					}
				}
				break;
			case redirectCentral:
				menuCourant = menuPartie;
				break;
			case redirectRecommencer:
				menuCourant = menuPartie;
				initPlateau();
				joueurCourant = changeJoueur(joueurCourant);
				//TODO score
				break;

			}

			printf("Menu %d\n", menuCourant);
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
		//redimensionnementForce();
		LargeurFenetreCourante = largeurFenetre();
		HauteurFenetreCourante = hauteurFenetre();
		assigneTaillePlateau(coordonneesGrille);
		break;
	}
}
