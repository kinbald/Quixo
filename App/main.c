/*!
* \file main.c
* \brief Fichier main du jeu
* \author desrumaux
* \date 31/01/17
*/

/*!
 * \include Fontions du moteur du jeu
 */
#include "modules/moteur.h"
/*!
 * \include Fonctions d'affichage du jeu
 */
#include "modules/affichage.h"

/*!
 * \brief Pointeur vers le plateau de jeu
 */
extern PLATEAU *plateau_jeu;

/*!
 * \brief Fonction principale du jeu
 * @return int
 */
int main(int argc, char **argv)
{
	initPlateau();
	initialiseGfx(argc, argv);

	prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);

	lanceBoucleEvenements();
	return 0;
}
