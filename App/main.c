/*!
* \file main.c
* \brief Fichier main du jeu
* \author desrumaux
* \date 31/01/17
*/
#include "modules/moteur.h"
#include "modules/affichage.h"
#include <string.h>

extern PLATEAU *plateau_jeu;

/*!
 * \brief Fonction principale du jeu
 * @return int
 */
int main(void)
{
	initPlateau();

	return 0;
}
