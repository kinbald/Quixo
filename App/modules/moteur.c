/*!
* \file moteur.c
* \brief Fichier contenant les fonctions du module moteur
* \author desrumaux
* \date 24/01/17
*/
#include "moteur.h"
/*!
 * Plateau de jeu
 */
extern PLATEAU plateau_jeu;

/*!
 * Nombre de coups évalués
 */
extern int nombreCoups;

/*!
 * \brief décalage des pions
 * @param plateau Plateau du jeu à accéder
 * @param colonnePiochee Colonne de la case piochée
 * @param lignePiochee Ligne de la case piochée
 * @param colonneJouee Colonne de la case de surbrillance choisie
 * @param ligneJouee Ligne de la case de surbrillance choisie
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

	if (differenceLigne == 0) {
		decalage = abs(differenceColonne);	// valeur absolue de la difference pour savoir combien de déclage on doit faire

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
 * @param joueurCourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireLigne1V1(PLATEAU * plateau, int joueurCourant)
{
	int colonne = 0, ligne = 0, gagnant = -1, increment =
	    0, nbrcasetableau = 5;

	CASE GET;

	for (ligne = 1; ligne < TAILLE_PLATEAU - 1; ligne++) {
		for (colonne = 1; colonne < TAILLE_PLATEAU - 1; colonne++) {
			GET.ligne = ligne;
			GET.colonne = colonne;
			if (getCase(plateau, &GET) == joueurCourant) {
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
 * \brief verification de la victoire d'un joueur par les colonnes
 * @param plateau Plateau du jeu à accéder
 * @param joueurCourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireColonne1V1(PLATEAU * plateau, int joueurCourant)
{
	int colonne = 0, ligne = 0, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;

	for (colonne = 1; colonne < TAILLE_PLATEAU - 1; colonne++) {
		for (ligne = 1; ligne < TAILLE_PLATEAU - 1; ligne++) {
			GET.ligne = ligne;
			GET.colonne = colonne;
			if (getCase(plateau, &GET) == joueurCourant) {
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
 * @param joueurCourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleG1V1(PLATEAU * plateau, int joueurCourant)
{
	int diagonale = 0, gagnant = -1, increment = 0, nbrcasetableau = 5;
	CASE GET;
	for (diagonale = 1; diagonale < TAILLE_PLATEAU - 1; diagonale++) {
		GET.ligne = diagonale;
		GET.colonne = diagonale;
		if (getCase(plateau, &GET) == joueurCourant) {
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
 * @param joueurCourant
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleD1V1(PLATEAU * plateau, int joueurCourant)
{
	int ligne = 0, colonne = 1, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;
	for (ligne = TAILLE_PLATEAU - 2; ligne > 0; ligne = ligne - 1) {
		GET.ligne = ligne;
		GET.colonne = colonne;
		if (getCase(plateau, &GET) == joueurCourant) {
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
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireLigne2V2(PLATEAU * plateau, int joueurCourant,
			  int joueurAllier)
{
	int colonne = 0, ligne = 0, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;
	for (ligne = 1; ligne < TAILLE_PLATEAU - 1; ligne++) {
		for (colonne = 1; colonne < TAILLE_PLATEAU - 1; colonne++) {
			GET.ligne = ligne;
			GET.colonne = colonne;
			//printf("valeur case = %d\n" , TEST[ligne][colonne]) ;
			if ((getCase(plateau, &GET) == joueurCourant)
			    || (getCase(plateau, &GET) == joueurAllier)) {
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
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireColonne2V2(PLATEAU * plateau, int joueurCourant,
			    int joueurAllier)
{
	int colonne = 0, ligne = 0, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;
	for (colonne = 1; colonne < TAILLE_PLATEAU - 1; colonne++) {
		for (ligne = 1; ligne < TAILLE_PLATEAU - 1; ligne++) {
			GET.ligne = ligne;
			GET.colonne = colonne;
			if ((getCase(plateau, &GET) == joueurCourant)
			    || (getCase(plateau, &GET) == joueurAllier)) {
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
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleG2V2(PLATEAU * plateau, int joueurCourant,
			       int joueurAllier)
{
	int diagonale = 0, gagnant = -1, increment = 0, nbrcasetableau = 5;
	CASE GET;

	for (diagonale = 1; diagonale < TAILLE_PLATEAU - 1; diagonale++) {
		GET.ligne = diagonale;
		GET.colonne = diagonale;
		if ((getCase(plateau, &GET) == joueurCourant)
		    || (getCase(plateau, &GET) == joueurAllier)) {
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
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoireDiagonaleD2V2(PLATEAU * plateau, int joueurCourant,
			       int joueurAllier)
{
	int ligne = 0, colonne = 1, gagnant = -1, increment =
	    0, nbrcasetableau = 5;
	CASE GET;
	for (ligne = TAILLE_PLATEAU - 2; ligne > 0; ligne = ligne - 1) {
		GET.ligne = ligne;
		GET.colonne = colonne;
		if ((getCase(plateau, &GET) == joueurCourant)
		    || (getCase(plateau, &GET) == joueurAllier)) {
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
 * @param joueurCourant
 * @param joueurAllier
 * @return :: joueurCourant si il a gagné sinon -1
 */
int testeVictoire(PLATEAU * plateau, int joueurCourant, int joueurAllier)
{
	int ligne = 0, colonne = 0, diagonaleG = 0, diagonaleD = 0, aucun = -1;

	if (joueurAllier == 0) {
		ligne = testeVictoireLigne1V1(plateau, joueurCourant);
		if (ligne == joueurCourant) {
			//printf("victoire en ligne !! \n");
			return (ligne);
		}

		colonne = testeVictoireColonne1V1(plateau, joueurCourant);
		if (colonne == joueurCourant) {
			//printf("victoire en colonne !! \n");
			return (colonne);
		}

		diagonaleG = testeVictoireDiagonaleG1V1(plateau, joueurCourant);
		if (diagonaleG == joueurCourant) {
			//printf("victoire en diagonale gauche !! \n");
			return (diagonaleG);
		}

		diagonaleD = testeVictoireDiagonaleD1V1(plateau, joueurCourant);
		if (diagonaleD == joueurCourant) {
			//printf("victoire en diagonale droite !! \n");
			return (diagonaleD);
		}
	} else {
		ligne =
		    testeVictoireLigne2V2(plateau, joueurCourant, joueurAllier);
		if (ligne == joueurCourant) {
			//printf("victoire en ligne !! \n");
			return (ligne);
		}

		colonne =
		    testeVictoireColonne2V2(plateau, joueurCourant,
					    joueurAllier);
		if (colonne == joueurCourant) {
			//printf("victoire en colonne !! \n");
			return (colonne);
		}

		diagonaleG =
		    testeVictoireDiagonaleG2V2(plateau, joueurCourant,
					       joueurAllier);
		if (diagonaleG == joueurCourant) {
			//printf("victoire en diagonale gauche !! \n");
			return (diagonaleG);
		}

		diagonaleD =
		    testeVictoireDiagonaleD2V2(plateau, joueurCourant,
					       joueurAllier);
		if (diagonaleD == joueurCourant) {
			//printf("victoire en diagonale droite !! \n");
			return (diagonaleD);
		}

	}
	return (aucun);
}

/*!
 * \brief Fonction qui vérifie la victoire en mode 1v1 ou 1vIA et qui prend en compte la cas particulier de la victoire adverse
 * @param plateau Plateau de jeu
 * @param joueurCourant Joueur courant
 * @param joueurAllier Joueur allier (facultatif : 0)
 * @return
 */
int testeVictoireCasParticulier(PLATEAU * plateau, int *joueurCourant,
				int joueurAllier)
{
	int victoire;
	victoire = testeVictoire(plateau, changeJoueur(*joueurCourant),
				 joueurAllier);
	if (victoire != -1) {
		*joueurCourant = changeJoueur(*joueurCourant);
		return 1;
	}
	victoire = testeVictoire(plateau, *joueurCourant, joueurAllier);
	if (victoire != -1) {
		return 1;
	} else {
		*joueurCourant = changeJoueur(*joueurCourant);
	}
	return 0;
}

/*!
 * \brief Fonction qui vérifie que le cube voulant être pioché est disponible
 *
 * @param plateau Plateau de jeu
 * @param clicJoueur Clic du jouer sur l'affichage graphique (coordonnées en X et Y)
 * @param joueurCourant
 * @return 0 si coup possible, -1 sinon
 */
int verifieSymbole(PLATEAU * plateau, CASE * clicJoueur, int joueurCourant)
{
	int joueur = getCase(plateau, clicJoueur);

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
		if (verifieSymbole(&plateau_jeu, caseJouee, *joueurCourant) == 0
		    || verifieSymbole(&plateau_jeu, caseJouee, vide) == 0) {
			casePiochee->ligne = caseJouee->ligne;
			casePiochee->colonne = caseJouee->colonne;
			calculeSurbrillance(caseJouee);
			return redirectSurbrillance;
		} else {
			return menuPartie;
		}
	case redirectContinue:
		if (verifieSymbole(&plateau_jeu, caseJouee, surbrillance) == 0) {
			setCase(&plateau_jeu, caseJouee, *joueurCourant);
			decalage(&plateau_jeu, casePiochee->colonne,
				 casePiochee->ligne, caseJouee->colonne,
				 caseJouee->ligne);
			nettoieSurbrillance(&plateau_jeu);

			victoire =
			    testeVictoireCasParticulier(&plateau_jeu,
							joueurCourant, 0);
			if (victoire == 1) {
				return redirectMenuVictoire;
			}
			return redirectAdversaire;
		} else {
			return redirectSurbrillance;
		}
	case redirectRePioche:
		return redirectSurbrillance;
	case redirectCentral:
		return menuPartie;
	case jeuIA:
		nombreCoups = 0;
		mouvementIA(&plateau_jeu, *joueurCourant);
		*joueurCourant = changeJoueur(*joueurCourant);
		victoire =
		    testeVictoireCasParticulier(&plateau_jeu, joueurCourant, 0);
		if (victoire == 1) {
			return redirectMenuVictoire;
		}
		return menuPartie;
		break;
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
 * \brief Fonction qui implémente l'algorithme min-max de recherche de mouvement favorable
 * @param plateau Plateau de jeu
 * @param joueur Joueur qui doit placer son coup
 * @param joueurLancement Lanceur du coup principal
 * @param depth Profondeur courante de recherche
 * @param isMax Le coup est-il maximal ou minimal
 * @param alpha Elagage alpha
 * @param beta Elagage beta
 * @return
 */
int MinMax(PLATEAU * plateau, int joueur, int joueurLancement, int depth,
	   int isMax, int alpha, int beta)
{
	// Index des boucles
	int index_ligne, index_colonne, index_move;
	int index_colonneRandA = 0, index_ligneRandA = 0;
	// Cases permettant d'accéder au plateau
	CASE caseCourante, caseCouranteJouee;
	// Tableau des mouvements autorisés
	int mouvementsPossibles[3][2];
	// Nombre de mouvements autorisés
	int nombre_mouvements;
	// Future profondeur
	int nouvelleProfondeur;

	// Valeur aléatoire de parcours du plateau généré à chaque appel de la fonction
	int valeurAleaCol = rand() % (TAILLE_PLATEAU - 2);
	int valeurAleaLi = rand() % (TAILLE_PLATEAU - 2);
	// Evaluation du coup
	int evaluation = 0;

	// Incrément du nombre de coups calculés
	nombreCoups++;

	// Si on dépasse la profondeure maximale ou s'il y a un gagnant
	if (depth >= PROFONDEUR_LIMITE
	    || testeVictoire(plateau, joueur, 0) != -1) {
		// On évalue le plateau
		evaluation = evaluePlateau(plateau, joueur);
		// Si le coup est pour l'adversaire, on maximise l'importance
		if (joueur != joueurLancement) {
			evaluation *= -1;
		} else if (evaluation == joueur) {
			evaluation *= -1;
		}
	} else {
		int prochaineEvaluation = 0;
		for (index_ligne = 1; index_ligne < TAILLE_PLATEAU - 1;
		     index_ligne++) {
			for (index_colonne = 1;
			     index_colonne < TAILLE_PLATEAU - 1;
			     index_colonne++) {
				// On parcourt la plateau de façon aléatoire
				index_colonneRandA =
				    ((index_colonne +
				      valeurAleaCol) % (TAILLE_PLATEAU - 2)) +
				    1;
				index_ligneRandA =
				    ((index_ligne +
				      valeurAleaLi) % (TAILLE_PLATEAU - 2)) + 1;
				caseCourante.colonne = index_colonneRandA;
				caseCourante.ligne = index_ligneRandA;
				// Si la case est sur l'extrémité du plateau
				if (index_colonneRandA == 5
				    || index_colonneRandA == 1
				    || index_ligneRandA == 5
				    || index_ligneRandA == 1) {
					int valCase =
					    getCase(plateau, &caseCourante);
					// La case est jouable (vide ou le joueur peut repiocher son pion)
					if (valCase == vide
					    || valCase == joueur) {
						if ((index_colonneRandA == 1
						     || index_colonneRandA == 5)
						    && (index_ligneRandA == 1
							|| index_ligneRandA ==
							5)) {
							// Seulement deux mouvements possibles
							nombre_mouvements = 2;
							// Premier mouvement possible
							mouvementsPossibles[0]
							    [0] =
							    ((index_colonneRandA
							      + 5) % 10);
							mouvementsPossibles[0]
							    [1] =
							    index_ligneRandA;
							// Deuxieme mouvement possible
							mouvementsPossibles[1]
							    [0] =
							    index_colonneRandA;
							mouvementsPossibles[1]
							    [1] =
							    ((index_ligneRandA +
							      5) % 10);
						} else {
							// Trois mouvements possibles
							nombre_mouvements = 3;
							if (index_colonneRandA
							    == 1
							    ||
							    index_colonneRandA
							    == 5) {
								// Premier mouvement possible
								mouvementsPossibles
								    [0][0] =
								    ((index_colonneRandA + 5) % 10);
								mouvementsPossibles
								    [0][1] =
								    index_ligneRandA;
								// Deuxième mouvement possible
								mouvementsPossibles
								    [1][0] =
								    index_colonneRandA;
								mouvementsPossibles
								    [1][1] = 0;
								// Troisième mouvement possible
								mouvementsPossibles
								    [2][0] =
								    index_colonneRandA;
								mouvementsPossibles
								    [2][1] = 6;
							} else {
								// Premier mouvement possible
								mouvementsPossibles
								    [0][0] =
								    index_colonneRandA;
								mouvementsPossibles
								    [0][1] =
								    ((index_ligneRandA + 5) % 10);
								// Deuxième mouvement possible
								mouvementsPossibles
								    [1][0] = 0;
								mouvementsPossibles
								    [1][1] =
								    index_ligneRandA;
								// Troisième mouvement possible
								mouvementsPossibles
								    [2][0] = 6;
								mouvementsPossibles
								    [2][1] =
								    index_ligneRandA;
							}
						}
						// Pour toutes les cases jouables, on calcule la profondeur suivante
						for (index_move = 0;
						     index_move <
						     nombre_mouvements;
						     index_move++) {
							caseCouranteJouee.
							    colonne =
							    mouvementsPossibles
							    [index_move][0];
							caseCouranteJouee.
							    ligne =
							    mouvementsPossibles
							    [index_move][1];
							joueCoup(plateau,
								 caseCourante,
								 caseCouranteJouee,
								 joueur);
							// Afin d'éviter un overflow possible
							if (depth < INT_MAX - 3) {
								nouvelleProfondeur
								    = depth;
							}
							// On change le type de recherche
							if (isMax == 0) {
								isMax = 1;
							} else {
								isMax = 0;
							}
							// On effectue l'évaluation du prochain coup adverse
							prochaineEvaluation =
							    MinMax(plateau,
								   changeJoueur
								   (joueur),
								   joueurLancement,
								   nouvelleProfondeur
								   + 1, isMax,
								   alpha, beta);
							dejoueCoup(plateau,
								   caseCouranteJouee,
								   caseCourante,
								   valCase);
							// Le minimum de recherche est supérieur au maximum
							if (alpha > beta) {
								break;
							} else if (isMax == 0
								   &&
								   ((prochaineEvaluation < beta)
								    /*|| ((prochaineEvaluation == beta) && (rand() % 2 == 0)) */
								   )) {
								// Réduction écart recherche coup minimal
								beta =
								    prochaineEvaluation;
							} else if (isMax == 1
								   &&
								   ((prochaineEvaluation > alpha)
								    /*|| ((prochaineEvaluation == alpha) && (rand() % 2 == 0)) */
								   )) {
								// Réduction écart recherche coup maximal
								alpha =
								    prochaineEvaluation;
							}
						}
						if (alpha > beta) {
							break;
						}
					}
				}
			}
		}
		if (isMax == 1) {
			evaluation = alpha;
		} else {
			evaluation = beta;
		}
	}
	return evaluation;
}

/*!
 * \brief Fonction qui effectue un mouvement de l'IA sur le plateau
 * @param plateau
 */
void mouvementIA(PLATEAU * plateau, int symbole)
{
	// Coup qui sera joué par l'IA
	COUP move;
	// Tableau qui contiendra les mouvements possibles
	int mouvementsPossibles[3][2];

	// Score minimal pour l'ordinateur
	int score = INT_MIN;
	// Index des boucles
	int index_ligne, index_colonne, index_move;
	int nombre_mouvements = 0;
	// Cases des traitements
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
			if (index_colonne == 1 || index_colonne == 5
			    || index_ligne == 1 || index_ligne == 5) {
				// On récupère la case
				int valCase = getCase(plateau, &caseCourante);
				// La case est jouable (vide ou pion qui appartient au joueur)
				if (valCase == vide || valCase == symbole) {
					caseCourante.colonne = index_colonne;
					caseCourante.ligne = index_ligne;
					// Calcul des mouvements possibles
					if ((index_colonne == 1
					     || index_colonne == 5)
					    && (index_ligne == 1
						|| index_ligne == 5)) {
						// Seulement deux mouvements possibles
						nombre_mouvements = 2;
						// Premier mouvement possible
						mouvementsPossibles[0][0] =
						    ((index_colonne + 5) % 10);
						mouvementsPossibles[0][1] =
						    index_ligne;
						// Deuxieme mouvement possible
						mouvementsPossibles[1][0] =
						    index_colonne;
						mouvementsPossibles[1][1] =
						    ((index_ligne + 5) % 10);
					} else {
						// Trois mouvements possibles
						nombre_mouvements = 3;
						if (index_colonne == 1
						    || index_colonne == 5) {
							// Premier mouvement possible
							mouvementsPossibles[0]
							    [0] =
							    ((index_colonne +
							      5) % 10);
							mouvementsPossibles[0]
							    [1] = index_ligne;
							// Deuxième mouvement possible
							mouvementsPossibles[1]
							    [0] = index_colonne;
							mouvementsPossibles[1]
							    [1] = 0;
							// Troisième mouvement possible
							mouvementsPossibles[2]
							    [0] = index_colonne;
							mouvementsPossibles[2]
							    [1] = 6;
						} else {
							// Premier mouvement possible
							mouvementsPossibles[0]
							    [0] = index_colonne;
							mouvementsPossibles[0]
							    [1] =
							    ((index_ligne +
							      5) % 10);
							// Deuxième mouvement possible
							mouvementsPossibles[1]
							    [0] = 0;
							mouvementsPossibles[1]
							    [1] = index_ligne;
							// Troisième mouvement possible
							mouvementsPossibles[2]
							    [0] = 6;
							mouvementsPossibles[2]
							    [1] = index_ligne;
						}
					}
					// Modification des cases du plateau à partir du tableau des surbrillances possibles
					for (index_move = 0;
					     index_move < nombre_mouvements;
					     index_move++) {
						caseCouranteJouee.colonne =
						    mouvementsPossibles
						    [index_move][0];
						caseCouranteJouee.ligne =
						    mouvementsPossibles
						    [index_move][1];
						// On joue le premier coup
						joueCoup(plateau, caseCourante,
							 caseCouranteJouee,
							 symbole);
						// On demande les évaluations des cas possibles à partir de ce coup en envoyant l'adversaire, la profondeur de 1 et le coup minimal
						int tempScore = MinMax(plateau,
								       changeJoueur
								       (symbole),
								       symbole,
								       1, 0,
								       INT_MIN,
								       INT_MAX);
						// On déjoue le coup
						dejoueCoup(plateau,
							   caseCouranteJouee,
							   caseCourante,
							   valCase);
						// Si l'évaluation est meilleure que le score minimal, on choisira ce coup
						if (tempScore > score
						    || ((tempScore == score)
							&& (rand() % 2 == 0))) {
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
	joueCoup(plateau, move.casePiochee, move.caseJouee, symbole);
}

/*!
 * \brief Fonction qui permet d'évaluer un plateau donné pour un joueur suivant les lignes, les colonnes et les diagonales
 *
 * @param plateau
 * @param joueurCourant
 * @return
 */
int evaluePlateau(PLATEAU * plateau, int joueurCourant)
{
	int evaluation = 0;
	int gagnant = testeVictoire(plateau, joueurCourant, 0);
	int coupPerdant = INT_MIN;
	int coupGagnant = INT_MAX;

	// S'il y a déjà un gagnant
	if (gagnant != -1) {
		// Si c'est le joueur alors évaluation maximale sinon évaluation minimale
		if (gagnant == joueurCourant) {
			evaluation = INT_MAX;
		} else {
			evaluation = INT_MIN;
		}
	} else {		// S'il n'y a pas de gagnant
		// Évaluation des lignes
		evaluation = evalueLignes(plateau, evaluation, joueurCourant);

		// Si le joueur n'est ni gagnant ni perdant alors on évalue les colonnes
		if (evaluation != coupPerdant && evaluation != coupGagnant) {
			evaluation =
			    evalueColonnes(plateau, evaluation, joueurCourant);
		}
		// Si le joueur n'est ni gagnant ni perdant alors on évalue les diagonales
		if (evaluation != coupPerdant && evaluation != coupGagnant) {
			evaluation =
			    evalueDiagonales(plateau, evaluation,
					     joueurCourant);
		}
	}
	return evaluation;
}

/*!
 * \brief Fonction qui permet d'évaluer les lignes du plateau envoyé
 *
 * Plus le retour est grand plus le joueurCourant est favorisé et inversement si le retour est faible
 *
 * @param plateau Plateau de jeu
 * @param evaluation Evaluation de base du joueurCourant (par exemple après une étude des diagonales)
 * @param joueurCourant
 * @return
 */
int evalueLignes(PLATEAU * plateau, int evaluation, int joueurCourant)
{
	int evaluationLignes = evaluation;
	int ligneGagnante = 0, lignePerdante = 0;
	CASE caseCourante;
	int index_ligne, index_colonne;

	for (index_ligne = 1; index_ligne < TAILLE_PLATEAU - 1; index_ligne++) {
		caseCourante.colonne = 1;
		caseCourante.ligne = index_ligne;
		int etatLigne = getCase(plateau, &caseCourante);

		if (etatLigne == joueurCourant) {
			evaluationLignes++;
		} else if (etatLigne != vide) {
			evaluationLignes--;
		}

		int facteurPreponderance = 1;

		for (index_colonne = 2; index_colonne < TAILLE_PLATEAU - 1;
		     index_colonne++) {
			caseCourante.colonne = index_colonne;
			caseCourante.ligne = index_ligne;
			int pionCourant = getCase(plateau, &caseCourante);

			if (pionCourant == joueurCourant) {
				evaluationLignes++;
			} else if (pionCourant != vide) {
				evaluationLignes--;
			}
			caseCourante.colonne = index_colonne - 1;
			caseCourante.ligne = index_ligne;
			if (pionCourant == getCase(plateau, &caseCourante)) {
				facteurPreponderance =
				    (facteurPreponderance *
				     facteurPreponderance) * 100;

				if (pionCourant == joueurCourant) {
					evaluationLignes +=
					    facteurPreponderance;
				} else if (pionCourant != vide) {
					evaluationLignes -=
					    facteurPreponderance;
				}
			} else {
				etatLigne = vide;
				facteurPreponderance = 1;
			}
		}

		if (etatLigne == joueurCourant) {
			ligneGagnante = 1;
			break;
		} else if (etatLigne != vide) {
			lignePerdante = 1;
			break;
		}
	}

	if (ligneGagnante == 1 && lignePerdante == 0) {
		evaluationLignes = INT_MAX;
	} else if (lignePerdante == 1) {
		evaluationLignes = INT_MIN;
	}
	return evaluationLignes;
}

/*!
 * \brief Fonction qui permet d'évaluer les colonnes du plateau envoyé
 *
 * Plus le retour est grand plus le joueurCourant est favorisé et inversement si le retour est faible
 *
 * @param plateau Plateau de jeu
 * @param evaluation Evaluation de base du joueurCourant (par exemple après une étude des lignes)
 * @param joueurCourant
 * @return
 */
int evalueColonnes(PLATEAU * plateau, int evaluation, int joueurCourant)
{
	int evaluationColonnes = evaluation;
	int colonneGagnante = 0, colonnePerdante = 0;
	int index_ligne, index_colonne;
	CASE caseCourante;

	// Parcours du plateau en partant de (1,1)
	for (index_colonne = 1; index_colonne < TAILLE_PLATEAU - 1;
	     index_colonne++) {
		caseCourante.ligne = 1;
		caseCourante.colonne = index_colonne;
		int etatColonne = getCase(plateau, &caseCourante);

		if (etatColonne == joueurCourant) {
			evaluationColonnes++;
		} else if (etatColonne != vide) {
			evaluationColonnes--;
		}

		int facteurPreponderance = 1;

		// Parcours des lignes
		for (index_ligne = 2; index_ligne < TAILLE_PLATEAU - 1;
		     index_ligne++) {
			caseCourante.colonne = index_colonne;
			caseCourante.ligne = index_ligne;
			int pionCourant = getCase(plateau, &caseCourante);

			if (pionCourant == joueurCourant) {
				evaluationColonnes++;
			} else if (pionCourant != vide) {
				evaluationColonnes--;
			}
			// Pion précédent pour vérifier si on possède une suite
			caseCourante.colonne = index_colonne;
			caseCourante.ligne = index_ligne - 1;
			if (pionCourant == getCase(plateau, &caseCourante)) {
				facteurPreponderance =
				    (facteurPreponderance *
				     facteurPreponderance) * 100;

				if (pionCourant == joueurCourant) {
					evaluationColonnes +=
					    facteurPreponderance;
				} else if (pionCourant != vide) {
					evaluationColonnes -=
					    facteurPreponderance;
				}
			} else {
				etatColonne = vide;
				facteurPreponderance = 1;
			}
		}		// Fin du parcours des lignes

		// Cas des colonnes gagnantes, on arrête la boucle pour retourner l'évaluation
		if (etatColonne == joueurCourant) {
			colonneGagnante = 1;
			break;
		} else if (etatColonne != vide) {
			colonnePerdante = 1;
			break;
		}
	}

	// S'il a une colonne gagnante c'est la maximum de pionts pour le joueur sinon c'est le minimum
	if (colonneGagnante == 1 && colonnePerdante == 0) {
		evaluationColonnes = INT_MAX;
	} else if (colonnePerdante == 1) {
		evaluationColonnes = INT_MIN;
	}
	return evaluationColonnes;
}

/*!
 * \brief Fonction qui permet d'évaluer les diagonales du plateau envoyé
 *
 * Plus le retour est grand plus le joueurCourant est favorisé et inversement si le retour est faible
 *
 * @param plateau Plateau de jeu
 * @param evaluation Evaluation de base du joueurCourant (par exemple après une étude des lignes)
 * @param joueurCourant
 * @return
 */
int evalueDiagonales(PLATEAU * plateau, int evaluation, int joueurCourant)
{
	int evaluationDiagonale = evaluation;
	// Index des parcours
	int index_ligne, index_colonne;
	CASE caseCourante;
	// Premieère case du parcours
	caseCourante.ligne = 1;
	caseCourante.colonne = 1;
	// Contenu première case
	int etatLigne = getCase(plateau, &caseCourante);

	// Si la case est détenue par le joueurCourant alors on augmente l'evaluation sinon on la décremente
	if (etatLigne == joueurCourant) {
		evaluationDiagonale++;
	} else if (etatLigne != vide) {
		evaluationDiagonale--;
	}
	// Facteur d'importance du joueur sur le plateau
	int facteurPreponderance = 1;

	// On parcourt toute la diagonale
	for (index_colonne = 2; index_colonne < TAILLE_PLATEAU - 1;
	     index_colonne++) {
		caseCourante.colonne = index_colonne;
		caseCourante.ligne = index_colonne;
		int pionCourant = getCase(plateau, &caseCourante);

		if (pionCourant == joueurCourant) {
			evaluationDiagonale++;
		} else if (pionCourant != vide) {
			evaluationDiagonale--;
		}
		// Case précédente
		caseCourante.colonne = index_colonne - 1;
		caseCourante.ligne = index_colonne - 1;
		// Si la case précédente est la même que celle étudiée avec caseCourante
		if (pionCourant == getCase(plateau, &caseCourante)) {
			// On incrémente le facteur de prépondérance
			facteurPreponderance =
			    (facteurPreponderance * facteurPreponderance) * 100;
			// Si la case précédente nous appartenait on augmente l'évaluation
			if (pionCourant == joueurCourant) {
				evaluationDiagonale += facteurPreponderance;
			} else if (pionCourant != vide) {	// Si elle appartenait à un autre joueur, on décrémente l'évaluation
				evaluationDiagonale -= facteurPreponderance;
			}
		} else {	// Si la la case précédente est différente, on considère un emplacement vide
			etatLigne = vide;
			facteurPreponderance = 1;
		}
	}			// Fin du calcul de la diagonale

	// Si la premiere diagonale n'est pas vide mais qu'elle n'appartient pas au joueur courant, on évalue en minimal
	if (etatLigne != vide && etatLigne != joueurCourant) {
		evaluationDiagonale = INT_MIN;
	} else {
		// Si elle nous appartenait, on évalue au maximum
		if (etatLigne == joueurCourant) {
			evaluationDiagonale = INT_MAX;
		} else {
			//S'il y avait des cases vides on s'occupe de la deuxième diagonale
			caseCourante.colonne = 1;
			caseCourante.ligne = TAILLE_PLATEAU - 2;
			// On évalue en partant du coin inférieur droit
			etatLigne = getCase(plateau, &caseCourante);

			if (etatLigne == joueurCourant) {
				evaluationDiagonale++;
			} else if (etatLigne != vide) {
				evaluationDiagonale--;
			}
			// Boucle d'évaluation de la deuxième diagonale
			for (index_ligne = 2; index_ligne < TAILLE_PLATEAU - 1;
			     index_ligne++) {
				caseCourante.ligne =
				    TAILLE_PLATEAU - 1 - index_ligne;
				caseCourante.colonne = index_ligne;
				int pionCourant =
				    getCase(plateau, &caseCourante);

				if (pionCourant == joueurCourant) {
					evaluationDiagonale++;
				} else if (pionCourant != vide) {
					evaluationDiagonale--;
				}

				caseCourante.ligne =
				    TAILLE_PLATEAU - index_ligne;
				caseCourante.colonne = index_ligne - 1;
				if (pionCourant ==
				    getCase(plateau, &caseCourante)) {
					facteurPreponderance =
					    (facteurPreponderance *
					     facteurPreponderance) * 100;

					if (pionCourant == joueurCourant) {
						evaluationDiagonale +=
						    facteurPreponderance;
					} else if (pionCourant != vide) {
						evaluationDiagonale -=
						    facteurPreponderance;
					}
				} else {
					etatLigne = vide;
					facteurPreponderance = 1;
				}
			}

			if (etatLigne == joueurCourant) {
				evaluationDiagonale = INT_MAX;
			} else if (etatLigne != vide) {
				evaluationDiagonale = INT_MIN;
			}
		}
	}
	return evaluationDiagonale;
}
