/*!
* \file moteur.c
* \brief Fichier contenant les fonctions du module moteur
* \author desrumaux
* \date 24/01/17
*/
#include "moteur.h"

extern PLATEAU plateau_jeu;
extern int nombreCoups;

/*!
 * \brief décalage des pions
 * @param plateau Plateau du jeu à accéder
 * @param colonnePiochee et lignePiochee de la case prise et colonneJouee et ligneJouee de la case de surbrillance choisie
 * @return ::0 si le décalage a bien été effectuer et -1 si y a eu un problème
*/
int decalage(PLATEAU * plateau, int colonnePiochee, int lignePiochee,
	     int colonneJouee, int ligneJouee)
{
	int differenceColonne = 0;
	int differenceLigne = 0;
	unsigned int decalage = 0;
	int i = 0;
	unsigned int verif_increment = 0;
	int memmoire2 = 1;
	int memmoire3 = 1;
	int ok = -1;
	CASE SET;
	CASE GET;

	// calcul du nombre de case  a déplacer :
	differenceColonne = colonnePiochee - colonneJouee;
	differenceLigne = lignePiochee - ligneJouee;

	//printf("differenceColonne %d \n", differenceColonne);
	//printf("differenceLigne %d \n", differenceLigne);

	if (differenceLigne == 0) {
		decalage = abs(differenceColonne);	// valeur absolue de la difference pour savoir combien de déclage on doit faire

		//printf(" valeur de décalage%d \n" , decalage ) ;
		GET.ligne = ligneJouee;
		GET.colonne = colonneJouee;

		SET.ligne = lignePiochee;
		SET.colonne = colonnePiochee;

		setCase(plateau, &SET, getCase(plateau, &GET));	// valeur de la case jouee

		//si cette condition est vérifier on effectura un déplacement bas vers le haut
		if (differenceColonne > 0) {
			i = colonneJouee;

			while (verif_increment <= decalage) {

				if (i % 2 == 0) {
					GET.ligne = ligneJouee;
					GET.colonne = i;
					memmoire2 = getCase(plateau, &GET);

					SET.ligne = ligneJouee;
					SET.colonne = i;
					setCase(plateau, &SET, memmoire3);
				} else {
					GET.ligne = ligneJouee;
					GET.colonne = i;
					memmoire3 = getCase(plateau, &GET);

					SET.ligne = ligneJouee;
					SET.colonne = i;
					setCase(plateau, &SET, memmoire2);

				}
				i = i + 1;
				verif_increment = verif_increment + 1;
			}
			ok = 0;
			//si cette condition est vérifier on effectura un déplacement Haut vers le bas
		} else if (differenceColonne < 0) {
			i = colonneJouee;
			while (verif_increment <= decalage) {
				if (i % 2 == 0) {
					GET.ligne = ligneJouee;
					GET.colonne = i;
					memmoire2 = getCase(plateau, &GET);

					SET.ligne = ligneJouee;
					SET.colonne = i;
					setCase(plateau, &SET, memmoire3);
				} else {
					GET.ligne = ligneJouee;
					GET.colonne = i;
					memmoire3 = getCase(plateau, &GET);

					SET.ligne = ligneJouee;
					SET.colonne = i;
					setCase(plateau, &SET, memmoire2);
				}
				i = i - 1;
				verif_increment = verif_increment + 1;
			}
			ok = 0;
		}
	} else if (differenceColonne == 0) {
		decalage = abs(differenceLigne);
		//printf(" valeur de décalage%d \n" , decalage ) ;

		GET.ligne = ligneJouee;
		GET.colonne = colonneJouee;

		SET.ligne = lignePiochee;
		SET.colonne = colonnePiochee;

		setCase(plateau, &SET, getCase(plateau, &GET));	// valeur de la case jouee

		//si cette condition est vérifier on effectura un déplacement droite  vers la gauche
		if (differenceLigne > 0) {
			i = ligneJouee;

			while (verif_increment <= decalage) {

				if (i % 2 == 0) {
					GET.ligne = i;
					GET.colonne = colonneJouee;
					memmoire2 = getCase(plateau, &GET);

					SET.ligne = i;
					SET.colonne = colonneJouee;
					setCase(plateau, &SET, memmoire3);
				} else {
					GET.ligne = i;
					GET.colonne = colonneJouee;
					memmoire3 = getCase(plateau, &GET);

					SET.ligne = i;
					SET.colonne = colonneJouee;
					setCase(plateau, &SET, memmoire2);
				}
				i = i + 1;
				verif_increment = verif_increment + 1;
			}
			ok = 0;
			//si cette condition est vérifier on effectura un déplacement gauche vers la droite
		} else if (differenceLigne < 0) {
			i = ligneJouee;
			//printf("val de i : %d \n" ,  i);
			while (verif_increment <= decalage) {
				//printf("on deplace  4! %d \n" , i);
				if (i % 2 == 0) {
					GET.ligne = i;
					GET.colonne = colonneJouee;
					memmoire2 = getCase(plateau, &GET);

					SET.ligne = i;
					SET.colonne = colonneJouee;
					setCase(plateau, &SET, memmoire3);
				} else {
					GET.ligne = i;
					GET.colonne = colonneJouee;
					memmoire3 = getCase(plateau, &GET);

					SET.ligne = i;
					SET.colonne = colonneJouee;
					setCase(plateau, &SET, memmoire2);
				}
				i = i - 1;
				verif_increment = verif_increment + 1;
			}
			ok = 0;
		}
	}
	return (ok);
}

/*!
 * \brief verification de la victoire d'un joueur par les lignes'
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireLigne1V1(int joueurCourant)
{
	int colonne = 0, ligne = 0, gagnant = -1, increment =
	    0, nbrcasetableau = 5;

	CASE GET;

	for (ligne = 1; ligne < TAILLE_PLATEAU - 1; ligne++) {
		for (colonne = 1; colonne < TAILLE_PLATEAU - 1; colonne++) {
			GET.ligne = ligne;
			GET.colonne = colonne;
			if (getCase(&plateau_jeu, &GET) == joueurCourant) {
				increment++;
				//printf("increment  = %d\n" , increment);
			}
		}
		if ((increment == nbrcasetableau)) {
			return (gagnant = joueurCourant);
		}
		increment = 0;
	}
	return (gagnant);
}

/*!
 * \brief verification de la victoire d'un joueur par les colonnes
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireColonne1V1(int joueurCourant)
{
	int colonne = 0, ligne = 0, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;

	for (colonne = 1; colonne < TAILLE_PLATEAU - 1; colonne++) {
		for (ligne = 1; ligne < TAILLE_PLATEAU - 1; ligne++) {
			GET.ligne = ligne;
			GET.colonne = colonne;
			if (getCase(&plateau_jeu, &GET) == joueurCourant) {
				increment++;
			}
		}
		if ((increment == nbrcasetableau)) {
			return (gagnant = joueurCourant);
		}
		increment = 0;
	}
	return (gagnant);
}

/*!
 * \brief verification de la victoire d'un joueur par la diagonale de gauche haut vers droite bas
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleG1V1(int joueurCourant)
{
	int diagonale = 0, gagnant = -1, increment = 0, nbrcasetableau = 5;
	CASE GET;
	for (diagonale = 1; diagonale < TAILLE_PLATEAU - 1; diagonale++) {
		GET.ligne = diagonale;
		GET.colonne = diagonale;
		if (getCase(&plateau_jeu, &GET) == joueurCourant) {
			increment++;
		}
		if ((increment == nbrcasetableau)) {
			return (gagnant = joueurCourant);
		}
	}
	return (gagnant);
}

/*!
 * \brief verification de la victoire d'un joueur par la diagonale de gauche bas vers droite haut
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleD1V1(int joueurCourant)
{
	int ligne = 0, colonne = 1, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;
	for (ligne = TAILLE_PLATEAU - 2; ligne > 0; ligne = ligne - 1) {
		GET.ligne = ligne;
		GET.colonne = colonne;
		if (getCase(&plateau_jeu, &GET) == joueurCourant) {
			increment++;
		}
		colonne = colonne + 1;
		if ((increment == nbrcasetableau)) {
			return (gagnant = joueurCourant);
		}
	}
	return (gagnant);
}

/*!
 * \brief verification de la victoire en 2V2 d'un joueur par les ligne
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireLigne2V2(int joueurCourant, int joueurAllier)
{
	int colonne = 0, ligne = 0, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;
	for (ligne = 1; ligne < TAILLE_PLATEAU - 1; ligne++) {
		for (colonne = 1; colonne < TAILLE_PLATEAU - 1; colonne++) {
			GET.ligne = ligne;
			GET.colonne = colonne;
			//printf("valeur case = %d\n" , TEST[ligne][colonne]) ;
			if ((getCase(&plateau_jeu, &GET) == joueurCourant)
			    || (getCase(&plateau_jeu, &GET) == joueurAllier)) {
				increment++;
				//printf("increment  = %d\n" , increment);
			}
		}
		if ((increment == nbrcasetableau)) {
			return (gagnant = joueurCourant);
		}
		increment = 0;
	}
	return (gagnant);
}

/*!
 * \brief verification de la victoire en 2V2 d'un joueur par les colonnes
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireColonne2V2(int joueurCourant, int joueurAllier)
{
	int colonne = 0, ligne = 0, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;
	for (colonne = 1; colonne < TAILLE_PLATEAU - 1; colonne++) {
		for (ligne = 1; ligne < TAILLE_PLATEAU - 1; ligne++) {
			GET.ligne = ligne;
			GET.colonne = colonne;
			if ((getCase(&plateau_jeu, &GET) == joueurCourant)
			    || (getCase(&plateau_jeu, &GET) == joueurAllier)) {
				increment++;
			}
		}
		if ((increment == nbrcasetableau)) {
			return (gagnant = joueurCourant);
		}
		increment = 0;
	}
	return (gagnant);
}

/*!
 * \brief verification de la victoire en 2V2 d'un joueur par la  diagonale de gauche haut vers droite bas
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleG2V2(int joueurCourant, int joueurAllier)
{
	int diagonale = 0, gagnant = -1, increment = 0, nbrcasetableau = 5;
	CASE GET;

	for (diagonale = 1; diagonale < TAILLE_PLATEAU - 1; diagonale++) {
		GET.ligne = diagonale;
		GET.colonne = diagonale;
		if ((getCase(&plateau_jeu, &GET) == joueurCourant)
		    || (getCase(&plateau_jeu, &GET) == joueurAllier)) {
			increment++;
		}
		if ((increment == nbrcasetableau)) {
			return (gagnant = joueurCourant);
		}
	}
	return (gagnant);
}

/*!
 * \brief verification de la victoire d'un joueur en 2V2 par la diagonale de gauche bas vers droite haut
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleD2V2(int joueurCourant, int joueurAllier)
{
	int ligne = 0, colonne = 1, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;
	for (ligne = TAILLE_PLATEAU - 2; ligne > 0; ligne = ligne - 1) {
		GET.ligne = ligne;
		GET.colonne = colonne;
		if ((getCase(&plateau_jeu, &GET) == joueurCourant)
		    || (getCase(&plateau_jeu, &GET) == joueurAllier)) {
			increment++;
		}
		colonne = colonne + 1;
		if ((increment == nbrcasetableau)) {
			return (gagnant = joueurCourant);
		}
	}
	return (gagnant);
}

/*!
 * \brief appel des fonctions de test de victiore pour le mode 2v2 et 1V1
 * \brief /!\ si on est en mode 1V1 alors  joueurAllier = 0
 * @param plateau Plateau du jeu à accéder
 * @param joueurCuourant et joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoire(int joueurCourant, int joueurAllier)
{
	int ligne = 0, colonne = 0, diagonaleG = 0, diagonaleD = 0, aucun = -1;

	if (joueurAllier == 0) {
		ligne = testeVictoireLigne1V1(joueurCourant);
		if (ligne == joueurCourant) {
			printf("victoire en ligne !! \n");
			return (ligne);
		}

		colonne = testeVictoireColonne1V1(joueurCourant);
		if (colonne == joueurCourant) {
			printf("victoire en colonne !! \n");
			return (colonne);
		}

		diagonaleG = testeVictoireDiagonaleG1V1(joueurCourant);
		if (diagonaleG == joueurCourant) {
			printf("victoire en diagonale gauche !! \n");
			return (diagonaleG);
		}

		diagonaleD = testeVictoireDiagonaleD1V1(joueurCourant);
		if (diagonaleD == joueurCourant) {
			printf("victoire en diagonale droite !! \n");
			return (diagonaleD);
		}
	} else {
		ligne = testeVictoireLigne2V2(joueurCourant, joueurAllier);
		if (ligne == joueurCourant) {
			printf("victoire en ligne !! \n");
			return (ligne);
		}

		colonne = testeVictoireColonne2V2(joueurCourant, joueurAllier);
		if (colonne == joueurCourant) {
			printf("victoire en colonne !! \n");
			return (colonne);
		}

		diagonaleG =
		    testeVictoireDiagonaleG2V2(joueurCourant, joueurAllier);
		if (diagonaleG == joueurCourant) {
			printf("victoire en diagonale gauche !! \n");
			return (diagonaleG);
		}

		diagonaleD =
		    testeVictoireDiagonaleD2V2(joueurCourant, joueurAllier);
		if (diagonaleD == joueurCourant) {
			printf("victoire en diagonale droite !! \n");
			return (diagonaleD);
		}

	}
	return (aucun);
}

/*!
 * \brief Fonction qui vérifie que le cube voulant être pioché est disponible
 *
 * @param clicJoueur Clic du jouer sur l'affichage graphique (coordonnées en X et Y)
 * @return 0 si coup possible, -1 sinon
 */
int verifieSymbole(CASE * clicJoueur, int joueurCourant)
{
	int joueur = getCase(&plateau_jeu, clicJoueur);

	if (joueur == joueurCourant || joueur == vide) {
		return 0;
	} else {
		return -1;
	}
}

/*!
 * \brief Fonction qui déterminer les cases où le joueur peut déposer le cube qu'il a pioché
 * @param casePiochee Coordonnées de la case que le joueur a pioché
 * @return 0
 */
int calculeSurbrillance(CASE * casePiochee)
{

	CASE surbrillanceCase;
	short index_move;
	short nb_mouvements;
	// Cases à mettre en surbrillance
	int move[3][2];

	int x = casePiochee->colonne;
	int y = casePiochee->ligne;

	// Vérification du cas des quatre coins
	if ((x == 1 || x == 5) && (y == 1 || y == 5)) {
		// Seulement deux mouvements possibles
		nb_mouvements = 2;

		// Premier mouvement possible
		move[0][0] = ((x + 5) % 10);
		move[0][1] = y;

		// Deuxieme mouvement possible
		move[1][0] = x;
		move[1][1] = ((y + 5) % 10);
	} else {
		// Trois mouvements possibles
		nb_mouvements = 3;

		if (x == 1 || x == 5) {
			// Premier mouvement possible
			move[0][0] = ((x + 5) % 10);
			move[0][1] = y;

			// Deuxième mouvement possible
			move[1][0] = x;
			move[1][1] = 0;

			// Troisième mouvement possible
			move[2][0] = x;
			move[2][1] = 6;
		} else {
			// Premier mouvement possible
			move[0][0] = x;
			move[0][1] = ((y + 5) % 10);

			// Deuxième mouvement possible
			move[1][0] = 0;
			move[1][1] = y;

			// Troisième mouvement possible
			move[2][0] = 6;
			move[2][1] = y;
		}
	}
	// Modification des cases du plateau à partir du tableau des surbrillances
	for (index_move = 0; index_move < nb_mouvements; index_move++) {
		surbrillanceCase.colonne = move[index_move][0];
		surbrillanceCase.ligne = move[index_move][1];
		setCase(&plateau_jeu, &surbrillanceCase, surbrillance);
	}
	setCase(&plateau_jeu, casePiochee, pioche);
	return 0;
}

/*!
 * \brief Fonction qui permet de nettoyer le plateau après la surbrillance
 * @param plateau
 */
void nettoieSurbrillance(PLATEAU * plateau)
{
	int index_li, index_col;
	CASE emplacement;
	for (index_li = 0; index_li < TAILLE_PLATEAU; index_li++) {
		for (index_col = 0; index_col < TAILLE_PLATEAU; index_col++) {
			emplacement.colonne = index_col;
			emplacement.ligne = index_li;
			if (getCase(plateau, &emplacement) == surbrillance) {
				setCase(plateau, &emplacement, tampon);
			}
		}
	}
}

/*!
 * \brief Fonction permet de gérer l'avancement du jeu
 *
 * @param joueurCourant
 * @param etatClic Permet de connaîre l'étape dans le jeu
 * @param caseJouee
 * @param casePiochee
 * @return
 */
int calculeTour(int *joueurCourant, int etatClic, CASE * caseJouee,
		CASE * casePiochee)
{
	int victoire;
	switch (etatClic) {
	case menuPartie:
		return menuPartie;
	case redirectPioche:
		if (verifieSymbole(caseJouee, *joueurCourant)
		    == 0 || verifieSymbole(caseJouee, vide) == 0) {
			casePiochee->ligne = caseJouee->ligne;
			casePiochee->colonne = caseJouee->colonne;
			calculeSurbrillance(caseJouee);
			return redirectSurbrillance;
		} else {
			return menuPartie;
		}
	case redirectContinue:
		if (verifieSymbole(caseJouee, surbrillance) == 0) {
			setCase(&plateau_jeu, caseJouee, *joueurCourant);
			decalage(&plateau_jeu, casePiochee->colonne,
				 casePiochee->ligne, caseJouee->colonne,
				 caseJouee->ligne);
			nettoieSurbrillance(&plateau_jeu);
			if (*joueurCourant == rond_gauche) {
				victoire = testeVictoire(croix_gauche, 0);
			} else {
				victoire = testeVictoire(rond_gauche, 0);
			}
			if (victoire != -1) {
				printf("%d\n", victoire);
				if (*joueurCourant == rond_gauche) {
					*joueurCourant = croix_gauche;
				} else {
					*joueurCourant = rond_gauche;
				}
				return redirectMenuVictoire;
			}
			victoire = testeVictoire(*joueurCourant, 0);
			if (victoire != -1) {
				printf("%d\n", victoire);
				if (*joueurCourant == rond_gauche) {
					*joueurCourant = croix_gauche;
				} else {
					*joueurCourant = rond_gauche;
				}
				return redirectMenuVictoire;
			} else {
				if (*joueurCourant == rond_gauche) {
					*joueurCourant = croix_gauche;
				} else {
					*joueurCourant = rond_gauche;
				}
			}
			return menuPartie;
		} else {
			return redirectSurbrillance;
		}
	case redirectRePioche:
		return redirectSurbrillance;
	case redirectCentral:
		return menuPartie;
	}
	return 0;
}

/*!
 * \brief Fontion qui permet d'appliquer un coup sur un plateau
 * 
 * @param plateau Plateau de jeu
 * @param casePioche Case de pioche
 * @param jouee Case de dépôt
 * @param joueur Joueur
 */
void joueCoup(PLATEAU * plateau, CASE casePioche, CASE jouee, int joueur)
{
	setCase(plateau, &jouee, joueur);
	decalage(plateau, casePioche.colonne, casePioche.ligne, jouee.colonne,
		 jouee.ligne);
	setCase(plateau, &jouee, tampon);
}

/*!
 * \brief Fonction qui permet de déjouer un coup sur le plateau
 * @param plateau Plateau de jeu
 * @param casePioche Case où le joueur avait pioché
 * @param jouee Case où le joueur avait joué
 * @param ancienEtat Dernier état de la case 
 */
void dejoueCoup(PLATEAU * plateau, CASE casePioche, CASE jouee, int ancienEtat)
{
	decalage(plateau, casePioche.colonne, casePioche.ligne, jouee.colonne,
		 jouee.ligne);
	setCase(plateau, &jouee, ancienEtat);
	setCase(plateau, &casePioche, tampon);
}

/*!
 * \brief Fonction qui permet de changer de joueur
 * @param joueur Joueur courant
 * @return 
 */
int changeJoueur(int joueur)
{
	return joueur == rond_gauche ? croix_gauche : rond_gauche;
}

/*!
 * \brief Fonction qui implémente l'algorithme min max de recherche de mouvement favorable
 * @param plateau Plateau de jeu
 * @param joueur Joueur courant
 * @param depth Profondeur de l'évaluation
 * @return 
 */
int MinMax(PLATEAU * plateau, int joueur, int depth)
{
	// Index des boucles
	int index_ligne, index_colonne, index_move;
	// Cases permettant d'accéder au plateau
	CASE caseCourante, caseCouranteJouee;
	int retour = 0;
	int score = -2;
	int hasMove = -1;
	// Tableau des mouvements autorisés
	int possibleMove[3][2];
	// Nombre de mouvements autorisés
	int number_movement;
	int newDepth;

	nombreCoups++;

	if (depth > 5) {
		return -1;
	} else if (testeVictoire(joueur, 0) != -1) {
		return joueur;
	} else {
		for (index_ligne = 1; index_ligne < TAILLE_PLATEAU - 1;
		     index_ligne++) {
			for (index_colonne = 1;
			     index_colonne < TAILLE_PLATEAU - 1;
			     index_colonne++) {
				caseCourante.colonne = index_colonne;
				caseCourante.ligne = index_ligne;
				// Si la case est sur l'extrémité du plateau
				if (index_colonne == 1
				    || index_colonne == 5
				    || index_ligne == 1 || index_ligne == 5) {
					int valCase =
					    getCase(plateau, &caseCourante);
					// La case est jouable (vide ou le joueur peut repiocher son pion)
					if (valCase == vide
					    || valCase == joueur) {
						if ((index_colonne == 1
						     || index_colonne == 5)
						    && (index_ligne == 1
							|| index_ligne == 5)) {
							// Seulement deux mouvements possibles
							number_movement = 2;
							// Premier mouvement possible
							possibleMove[0][0] =
							    ((index_colonne +
							      5) % 10);
							possibleMove[0][1] =
							    index_ligne;
							// Deuxieme mouvement possible
							possibleMove[1][0] =
							    index_colonne;
							possibleMove[1][1] =
							    ((index_ligne +
							      5) % 10);
						} else {
							// Trois mouvements possibles
							number_movement = 3;
							if (index_colonne == 1
							    || index_colonne ==
							    5) {
								// Premier mouvement possible
								possibleMove[0]
								    [0] =
								    ((index_colonne + 5) % 10);
								possibleMove[0]
								    [1] =
								    index_ligne;
								// Deuxième mouvement possible
								possibleMove[1]
								    [0] =
								    index_colonne;
								possibleMove[1]
								    [1] = 0;
								// Troisième mouvement possible
								possibleMove[2]
								    [0] =
								    index_colonne;
								possibleMove[2]
								    [1] = 6;
							} else {
								// Premier mouvement possible
								possibleMove[0]
								    [0] =
								    index_colonne;
								possibleMove[0]
								    [1] =
								    ((index_ligne + 5) % 10);
								// Deuxième mouvement possible
								possibleMove[1]
								    [0] = 0;
								possibleMove[1]
								    [1] =
								    index_ligne;
								// Troisième mouvement possible
								possibleMove[2]
								    [0] = 6;
								possibleMove[2]
								    [1] =
								    index_ligne;
							}
						}
						// Pour toutes les cases jouables, on calcule la profondeur suivante
						for (index_move = 0;
						     index_move <
						     number_movement;
						     index_move++) {
							caseCouranteJouee.
							    colonne =
							    possibleMove
							    [index_move][0];
							caseCouranteJouee.
							    ligne =
							    possibleMove
							    [index_move][1];
							joueCoup(plateau,
								 caseCourante,
								 caseCouranteJouee,
								 joueur);
							// Afin d'éviter un overflow possible
							if (depth < INT_MAX - 3) {
								newDepth =
								    depth;
							}
							retour =
							    -MinMax(plateau,
								    changeJoueur
								    (joueur),
								    newDepth +
								    2);
							dejoueCoup(plateau,
								   caseCouranteJouee,
								   caseCourante,
								   valCase);
							// Si c'est un parcours favorable
							if (retour > score) {
								score = retour;
								hasMove = 1;
							}
						}
					}
				}
			}
		}
	}
	// Si le parcours n'a pas trouvé de mouvement favorable
	if (hasMove == -1)
		return 0;
	// Valeur du mouvement
	return score;
}

/*!
 * \brief Fonction qui effectue un mouvement de l'IA sur le plateau
 * @param plateau
 */
void mouvementIA(PLATEAU * plateau)
{
	// Coup qui sera joué par l'IA
	COUP move;
	// Tableau qui contiendra les mouvements possibles
	int possibleMove[3][2];

	int score = -2;
	// Index des boucles
	int index_ligne, index_colonne, index_move;
	int number_movement = 0;
	CASE caseCourante, caseCouranteJouee;
	caseCourante.colonne = 0;
	caseCourante.ligne = 0;
	caseCouranteJouee.ligne = 0;
	caseCouranteJouee.colonne = 0;
	move.caseJouee = caseCouranteJouee;
	move.casePiochee = caseCourante;

	// Pour toutes les cases du plateau
	for (index_ligne = 1; index_ligne < TAILLE_PLATEAU - 1; index_ligne++) {
		for (index_colonne = 1; index_colonne < TAILLE_PLATEAU - 1;
		     index_colonne++) {
			caseCourante.colonne = index_colonne;
			caseCourante.ligne = index_ligne;
			// Si la case est sur l'extrémité du plateau
			if (index_colonne == 1
			    || index_colonne == 5
			    || index_ligne == 1 || index_ligne == 5) {
				int valCase = getCase(plateau, &caseCourante);
				// La case est jouable (vide ou le joueur peut repiocher son pion)
				if (valCase == vide || valCase == croix_gauche) {
					caseCourante.colonne = index_colonne;
					caseCourante.ligne = index_ligne;

					if ((index_colonne == 1
					     || index_colonne == 5)
					    && (index_ligne == 1
						|| index_ligne == 5)) {
						// Seulement deux mouvements possibles
						number_movement = 2;
						// Premier mouvement possible
						possibleMove[0][0] =
						    ((index_colonne + 5) % 10);
						possibleMove[0][1] =
						    index_ligne;
						// Deuxieme mouvement possible
						possibleMove[1][0] =
						    index_colonne;
						possibleMove[1][1] =
						    ((index_ligne + 5) % 10);
					} else {
						// Trois mouvements possibles
						number_movement = 3;
						if (index_colonne == 1
						    || index_colonne == 5) {
							// Premier mouvement possible
							possibleMove[0][0] =
							    ((index_colonne +
							      5) % 10);
							possibleMove[0][1] =
							    index_ligne;
							// Deuxième mouvement possible
							possibleMove[1][0] =
							    index_colonne;
							possibleMove[1][1] = 0;
							// Troisième mouvement possible
							possibleMove[2][0] =
							    index_colonne;
							possibleMove[2][1] = 6;
						} else {
							// Premier mouvement possible
							possibleMove[0][0] =
							    index_colonne;
							possibleMove[0][1] =
							    ((index_ligne +
							      5) % 10);
							// Deuxième mouvement possible
							possibleMove[1][0] = 0;
							possibleMove[1][1] =
							    index_ligne;
							// Troisième mouvement possible
							possibleMove[2][0] = 6;
							possibleMove[2][1] =
							    index_ligne;
						}
					}
					// Modification des cases du plateau à partir du tableau des surbrillances
					for (index_move = 0;
					     index_move < number_movement;
					     index_move++) {
						caseCouranteJouee.colonne =
						    possibleMove[index_move][0];
						caseCouranteJouee.ligne =
						    possibleMove[index_move][1];
						joueCoup(plateau, caseCourante,
							 caseCouranteJouee,
							 croix_gauche);
						int tempScore =
						    -MinMax(plateau,
							    changeJoueur
							    (croix_gauche), 0);
						dejoueCoup(plateau,
							   caseCouranteJouee,
							   caseCourante,
							   valCase);
						if (tempScore > score) {
							score = tempScore;
							move.caseJouee =
							    caseCouranteJouee;
							move.casePiochee =
							    caseCourante;
						}
					}
				}
			}
		}
	}
	// On joue le coup généré
	joueCoup(plateau, move.casePiochee, move.caseJouee, croix_gauche);
}
