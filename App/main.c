/*!
* \file main.c
* \brief Fichier main du jeu
* \author desrumaux
* \date 31/01/17
*/
#include "modules/moteur.h"
#include "modules/affichage.h"

extern PLATEAU plateau_jeu;

/*!
 * \brief Fonction principale du jeu
 * @return int
 */
int main(int argc, char **argv)
{
	initPlateau();
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("Quixo", LargeurFenetre, HauteurFenetre);

	lanceBoucleEvenements();

	return 0;
}
