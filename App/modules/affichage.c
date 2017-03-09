/*!
* \file affichage.c
* \brief Fichier contenant les fonctions d'affichage
* \author desrumaux
* \date 24/01/17
*/
#include "affichage.h"

/*!
 * \brief Fonction de gestion des événements
 * Appelée automatiquement par le système dès qu'un événement survient
 * @param evenement
 */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false;	///< Pour savoir si on est en mode plein écran ou pas

	switch (evenement) {
	case Initialisation:

		demandeAnimation_ips(120);	///< Configure le système pour un mode 50 images par seconde
		break;

	case Affichage:
		// On part d'un fond d'ecran blanc
		effaceFenetre(255, 255, 255);

		break;

	case Clavier:
		printf("%c : ASCII %d\n", caractereClavier(),
		       caractereClavier());

		switch (caractereClavier()) {
		case 'Q':	///< Quitter le programme
		case 'q':
			exit(0);

		case 'F':
		case 'f':
			pleinEcran = !pleinEcran;	///< Changement de mode plein ecran
			if (pleinEcran)
				modePleinEcran();
			else
				redimensionneFenetre(LargeurFenetre,
						     HauteurFenetre);
			break;

		case 'R':
		case 'r':
			rafraichisFenetre();	///< Force un rafraîchissment
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
