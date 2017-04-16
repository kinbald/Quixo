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
 * Scores du jeu
 */
SCORE scores[2];

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
	static int coordonneesGrille[4]; // Coordonnées de la grille de jeu dans menuPartie
	static int LargeurFenetreCourante = LargeurFenetre;
	static int HauteurFenetreCourante = HauteurFenetre;
	static DonneesImageRGB *imageRegles = NULL; // Image pour règles de jeu
	static CLIC clic; // Clic lorsqu'un évènement de boutonSouris est detecté
	static CASE retourClic, savePioche; // Cases permettant la gestion des clics
	static int joueurCourant;
	static int MODE;
	static int menuCourant, ancienMenu;

	switch (evenement) {
	case Initialisation:
		initPlateau();
		if (imageRegles == NULL) {
			imageRegles = lisBMPRGB("deuxjoueurs.bmp");
		}
		demandeAnimation_ips(25);	// Configure le système pour un mode 25 images par seconde
		assigneTaillePlateau(coordonneesGrille); // Préparation position grille
		activeGestionDeplacementPassifSouris(); // Activation du mode souris passif
		menuCourant = menuPrincipal; // Menu de démarrage
		ancienMenu = menuPrincipal;
		MODE = -1;
		break;
	case Affichage:
		redimensionnementForce(menuCourant);
		// On part d'un fond d'ecran
		effaceFenetre(239, 240, 244);
		gestionAffichage(menuCourant, coordonneesGrille,
				 LargeurFenetreCourante,
				 HauteurFenetreCourante, imageRegles,
				 joueurCourant);
		rafraichisFenetre();
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
          // Cas particulier des boutons de retour (menuRegles), on garde l'ancien état
			if (menuCourant == redirectSurbrillance
			    || menuCourant == menuPartie
			    || menuCourant == menuPrincipal) {
				ancienMenu = menuCourant;
			}
          // Récupération de l'action correspondant au clic envoyé
			menuCourant =
			    recupereClicAffichage(&retourClic, &clic,
						  coordonneesGrille,
						  LargeurFenetreCourante,
						  HauteurFenetreCourante);
          // Gestion de l'action à effectuer
			switch (menuCourant) {
              // Redirection menu principal
			case redirectMenuPrincipal:
              // Cas particulier accès menuRegles depuis partie en cours, on souhaite revenir au jeu et non au menu
				if ((ancienMenu == menuPartie
				     || ancienMenu == redirectSurbrillance)
				    && clic.menu == menuRegles) {
					menuCourant = ancienMenu;
				} else {
					menuCourant = menuPrincipal;
					if (ancienMenu == menuPartie
					    || ancienMenu ==
					    redirectSurbrillance) {
						initPlateau();
					}
				}
				break;
                // Redirection vers menu de choix des symboles pour le jeu
			case redirectMenuChoixSymboleS:
				menuCourant = menuChoixSymboles;
                // Ajout du mode de jeu choisi pour les symboles
				MODE = clic.mode;
				break;
			case redirectMenuRegles:
				menuCourant = menuRegles;
				break;
			case redirectMenuPartie:
				joueurCourant = clic.joueurCourant;
				menuCourant = menuPartie;
				break;
			case redirectMenuVictoire:
				menuCourant = menuVictoire;
				break;
			case menuPartie:
			case redirectSurbrillance:
			case redirectPioche:
			case redirectRePioche:
			case redirectContinue:
              // Cas particulier clicExterieur au plateau
				if (clic.menu == menuPartie
				    && menuCourant == redirectRePioche) {
					menuCourant = menuPartie;
					break;
				}
                // Action à effectuer sur le plateau quand un clic dans le plateau est détecté
				menuCourant =
				    calculeTour(&joueurCourant, menuCourant,
						&retourClic, &savePioche);
				// S'il n'y a pas de gagnant on change de joueur
				if (menuCourant == redirectAdversaire) {
					joueurCourant =
					    changeJoueur(joueurCourant);
                  // Si c'est le mode contre l'ordinateur alors on fait le fait jouer
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
                // Réinitialisation du plateau
				initPlateau();
				if (MODE != VIA) {
					joueurCourant =
					    changeJoueur(joueurCourant);
				}
				//TODO score
				break;
                // Redirecion après une défaite contre l'ordinateur
			case redirectRecommencerDef:
				menuCourant = menuPartie;
				joueurCourant = changeJoueur(joueurCourant);
				initPlateau();
				break;
                // Clic dans le menuPartie mais extérieur au plateau
			case redirectExterieur:
				if (ancienMenu == redirectSurbrillance) {
					menuCourant = redirectSurbrillance;
				} else {
					menuCourant = menuPartie;
				}
				break;
			}
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
		redimensionnementForce(menuCourant);
		LargeurFenetreCourante = largeurFenetre();
		HauteurFenetreCourante = hauteurFenetre();
		assigneTaillePlateau(coordonneesGrille);
		break;
	}
}
