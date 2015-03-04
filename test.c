/*
 * Ce fichier contient l'ensemble des fonctions nécessaires à la vérification des fonctions implémentées dans le fichier dames.c
 */

#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "dames.h"

int init_suite1(void);
int clean_suite1(void);
void verifdep(struct game *);
void test_new_game(void); //VERIFIER SI C'EST VRAIMENT NECESSAIRE
void test_load_game(void);
void test_apply_moves(void);
void test_is_move_seq_valid(void);
void test_undo_moves(void);

	
struct game *game1;


/*
 *
 */
int main()
{
	
	CU_pSuite pSuite = NULL;

	/* Initialise le catalogue de tests */
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* Ajoute la suite au catalogue */
	pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Ajoute les tests à la suite */
	if ((NULL == CU_add_test(pSuite, "test new_game()", test_new_game)) ||
		 (NULL == CU_add_test(pSuite, "test load_game()", test_load_game)) ||
		 (NULL == CU_add_test(pSuite, "test apply_moves()", test_apply_moves)) ||
		 (NULL == CU_add_test(pSuite, "test is_move_seq_valid()", test_is_move_seq_valid)) ||
		 (NULL == CU_add_test(pSuite, "test undo_moves()", test_undo_moves)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	/* Exécute les tests et affiche les erreurs */
	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());

	/* Libère les ressources utilisées par le catalogue */
	CU_cleanup_registry();

}

/*
 * Initialise les données nécessaires à l'exécution des tests
 */
int init_suite1(void)
{

	
}

/*
 * Libère les données utilisées dans l'exécution des tests
 */
int clean_suite1(void)
{
	
	//LIBERER MEMOIRE MOVES
	
}

/*
 * Cette fonction crée une partie et vérifie que le plateau a les bonnes dimensions, que le joueur qui commence à jouer 
 * est bien le joueur blanc, que la liste des mouvements effectués est bien vide et que les pions sont bien positionnés.
 */
void test_new_game(void)
{
	
	game1 = new_game(10,10); //Initialise la partie 
	
	CU_ASSERT_EQUAL((*game1).xsize, 10); //Vérifie que le plateau a les bonnes dimensions
	CU_ASSERT_EQUAL((*game1).ysize, 10);
	
	CU_ASSERT_EQUAL((*game1).cur_player, 1); //Vérifie que le joueur blanc commence bien la partie
	
	CU_ASSERT_EQUAL((game1 -> moves), NULL); //Vérifie que la liste des mouvements exécutés est bien vide
	
	verifdep(game1);
	
}

/*
 * Cette fonction charge une partie à partir, de la taille du plateau, de la position des pions et du joueur qui doit 
 * jouer sont tour. Elle vérifie ensuite que la partie a correctement été chargée en comparant les données une par une.
 */
void test_load_game(void)
{
	
	/* Crée un plateau de jeu probable */
	int gameboard[10][10] = {{0,1,0,1,0,0,0,0,0,0},{1,0,1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1,0,1},{1,0,1,0,0,0,1,0,1,0},{0,0,0,0,0,0,0,0,0,0},{0,0,5,0,5,0,5,0,0,0},{0,5,0,5,0,5,0,0,0,5},{0,0,0,0,5,0,5,0,5,0},{0,0,0,0,0,0,0,5,0,5},{5,0,5,0,5,0,5,0,5,0}}; 
	
	struct game *game2;
	game2 = load_game(10, 10, gameboard, 0);//Charge une partie
	
	CU_ASSERT_EQUAL((*game2).xsize, 10); //Vérifie que le plateau a les bonnes dimensions
	CU_ASSERT_EQUAL((*game2).ysize, 10);
	
	CU_ASSERT_EQUAL((*game1).cur_player, 0); //Vérifie que c'est bien au tour du joueur noir de jouer
	
	CU_ASSERT_PTR_EQUAL((*game1).board, &gameboard);//Vérifie que le jeu se joue bien sur le plateau chargé
	
}

/*
 * Cette fonction applique une suite de mouvements à un jeu et vérifie que l'état final est bien celui attendu
 */
void test_apply_moves(void)
{
	
	/* Crée une suite de mouvements valides */
	struct move_seq *ptrseq1 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if(ptrseq1 == NULL) 
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq2 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if(ptrseq2 == NULL) 
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq3 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if(ptrseq3 == NULL) 
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq4 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if(ptrseq4 == NULL) 
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq5 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if(ptrseq5 == NULL) 
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq6 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if(ptrseq6 == NULL) 
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq7 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if(ptrseq7 == NULL) 
		exit(EXIT_FAILURE);
	
	struct move *ptrmove1 = (struct move *) malloc(sizeof(struct move));
	if(ptrmove1 == NULL) 
		exit(EXIT_FAILURE);
	struct move *ptrmove2 = (struct move *) malloc(sizeof(struct move));
	if(ptrmove2 == NULL) 
		exit(EXIT_FAILURE);
	struct move *ptrmove3 = (struct move *) malloc(sizeof(struct move));
	if(ptrmove3 == NULL) 
		exit(EXIT_FAILURE);
	struct move *ptrmove4 = (struct move *) malloc(sizeof(struct move));
	if(ptrmove4 == NULL) 
		exit(EXIT_FAILURE);
	struct move *ptrmove5 = (struct move *) malloc(sizeof(struct move));
	if(ptrmove5 == NULL) 
		exit(EXIT_FAILURE);
	struct move *ptrmove6 = (struct move *) malloc(sizeof(struct move));
	if(ptrmove6 == NULL) 
		exit(EXIT_FAILURE);
	
	struct coord coord1 = {4,3};
	struct coord coord2 = {3,4};
	struct coord coord3 = {5,6};
	struct coord coord4 = {4,5};
	struct coord coord5 = {4,7};
	struct coord coord6 = {6,5};
	struct coord coord7 = {1,6};
	struct coord coord8 = {0,5};
	struct coord coord9 = {6,3};
	struct coord coord10 = {5,4};
	
	(*ptrseq1).c_old = coord1;
	(*ptrseq1).c_new = coord2;
	ptrseq1 -> next = NULL;
	(*ptrseq2).c_old = coord3;
	(*ptrseq2).c_new = coord4;
	ptrseq2 -> next = NULL;
	(*ptrseq3).c_old = coord2;
	(*ptrseq3).c_new = coord3;
	ptrseq3 -> next = NULL;
	(*ptrseq4).c_old = coord7;
	(*ptrseq4).c_new = coord8;
	ptrseq4 -> next = NULL;
	(*ptrseq5).c_old = coord9;
	(*ptrseq5).c_new = coord10;
	ptrseq5 -> next = NULL;
	(*ptrseq6).c_old = coord5;
	(*ptrseq6).c_new = coord6;
	ptrseq6 -> next = ptrseq7;
	(*ptrseq7).c_old = coord6;
	(*ptrseq7).c_new = coord1;
	ptrseq7 -> next = NULL;
	
	ptrmove1 -> next = ptrmove2;
	ptrmove1 -> seq = ptrseq1;
	ptrmove2 -> next = ptrmove3;
	ptrmove2 -> seq = ptrseq2;
	ptrmove3 -> next = ptrmove4;
	ptrmove3 -> seq = ptrseq3;
	ptrmove4 -> next = ptrmove5;
	ptrmove4 -> seq = ptrseq4;
	ptrmove5 -> next = ptrmove6;
	ptrmove5 -> seq = ptrseq5;
	ptrmove6 -> next = NULL;
	ptrmove6 -> seq = ptrseq6;
	
	/* Vérifie une séquence de plusieurs mouvements qui se suivent */
	apply_moves(game1, ptrmove1);
	
	int pos_fin[10][10] = {{0,1,0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1,0,1},{1,0,1,0,5,0,0,0,1,0},{0,0,0,0,0,0,0,0,0,0},{5,0,0,0,0,0,0,0,0,0},{0,0,0,5,0,0,0,5,0,5},{5,0,5,0,0,0,5,0,5,0},{0,5,0,5,0,5,0,5,0,5},{5,0,5,0,5,0,5,0,5,0}}; //Etat final du plateau attendu
	
	int i;
	int j;
	for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			
			CU_ASSERT_EQUAL((*game1).board[i][j], pos_fin[i][j]);
				
		}
	}
	
	free(ptrseq7);
	ptrseq6 -> next = NULL;
	free(ptrseq6);
	ptrmove6 -> seq = NULL;
	free(ptrseq5);
	ptrmove5 -> seq = NULL; 
	free(ptrseq4);
	ptrmove4 -> seq = NULL;
	free(ptrseq3);
	ptrmove3 -> seq = NULL;
	free(ptrseq2);
	ptrmove2 -> seq = NULL;
	free(ptrseq1);
	ptrmove1 -> seq = NULL;
	free(ptrmove6);
	ptrmove5 -> next = NULL;
	free(ptrmove5);
	ptrmove4 -> next = NULL;
	free(ptrmove4);
	ptrmove3 -> next = NULL;
	free(ptrmove3);
	ptrmove2 -> next = NULL;
	free(ptrmove2);
	ptrmove1 -> next = NULL;
	free(ptrmove1);
	
	
	/* Vérifie qu'un pion est bien transformé en dame lorsqu'il arrive sur la dernière ligne du côté adverse (pb1 et pn1) mais pas de son côté (pb2 et pn2) et qu'il ne se passe rien quand une dame arrive du côté adverse (db et dn) 

	  0_1_2_3_4_5_6_7_8_9		  0_1_2_3_4_5_6_7_8_9
	0|0 0 0 0 0 0 0 0 0 0		0|0 7 0 7 0 0 0 1 0 0
	1|5 0 7 0 0 0 0 0 5 0		1|0 0 0 0 0 0 0 0 5 0
	2|0 0 0 0 0 0 0 0 0 1		2|0 0 0 0 0 0 0 0 0 0
	3|0 0 0 0 0 0 0 0 0 0		3|0 0 0 0 0 0 0 0 0 0
	4|0 0 0 0 0 0 0 0 0 0  =>	4|0 0 0 0 0 0 0 0 0 0	
	5|0 0 0 0 0 0 0 0 0 0		5|0 0 0 0 0 0 0 0 0 0	
	6|0 0 0 0 0 0 0 0 0 0		6|0 0 0 0 0 0 0 0 0 0	1 = pion noir
	7|0 0 0 0 0 0 0 0 5 0		7|0 0 0 0 0 0 0 0 0 0	3 = dame noir
	8|0 1 0 3 0 0 0 1 0 0		8|0 0 0 0 0 0 0 1 0 0	5 = pion blanc
	9|0 0 0 0 0 0 0 0 0 0		9|3 0 3 0 0 0 5 0 0 0	7 = dame blanche

	*/
	int gameboard1[10][10] = {{0,0,0,0,0,0,0,0,0,0},{5,0,7,0,0,0,0,0,5,0},{0,0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,5,0},{0,1,0,3,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,0,0}};
	
	struct game *game3;	
	game3 = load_game(10, 10, gameboard1, 1);
	
	struct move_seq *ptrseq_pb1 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if(ptrseq_pb1 == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq_pn1 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if(ptrseq_pn1 == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq_db = (struct move_seq *) malloc(sizeof(struct move_seq));
	if (ptrseq_db == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq_dn = (struct move_seq *) malloc(sizeof(struct move_seq));
	if (ptrseq_dn == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq_pb2 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if (ptrseq_pb2 == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *ptrseq_pn2 = (struct move_seq *) malloc(sizeof(struct move_seq));
	if (ptrseq_pn2 == NULL)
		exit(EXIT_FAILURE);
	
	struct move *ptrmove_pb1 = (struct move *) malloc(sizeof(struct move));
	if (ptrmove_pb1 == NULL)
		exit(EXIT_FAILURE);
	struct move *ptrmove_pn1 = (struct move *) malloc(sizeof(struct move));
	if (ptrmove_pn1 == NULL)
		exit(EXIT_FAILURE);
	struct move *ptrmove_db = (struct move *) malloc(sizeof(struct move));
	if (ptrmove_db == NULL)
		exit(EXIT_FAILURE);
	struct move *ptrmove_dn = (struct move *) malloc(sizeof(struct move));
	if (ptrmove_dn == NULL)
		exit(EXIT_FAILURE);
	struct move *ptrmove_pb2 = (struct move *) malloc(sizeof(struct move));
	if (ptrmove_pb2 == NULL)
		exit(EXIT_FAILURE);
	struct move *ptrmove_pn2 = (struct move *) malloc(sizeof(struct move));
	if (ptrmove_pn2 == NULL)
		exit(EXIT_FAILURE);
	
	struct coord coord_pb1_init = {0,1}; //Coordonnées initiales du pion blanc qui doit être transformé en dame
	struct coord coord_pb1_fin = {1,0}; //Coordonnées finales du pion blanc qui doit être transformé en dame
	struct coord coord_pn1_init = {1,8}; //Coordonnées initiales du pion noir qui doit être transformé en dame
	struct coord coord_pn1_fin = {0,9}; //Coordonnées finales du pion noir qui doit être transformé en dame
	struct coord coord_db_init = {2,1}; //Coordonnées initiales de la dame blanche qui ne doit pas être transformée
	struct coord coord_db_fin = {3,0}; //Coordonnées finales de la dame blanche qui ne doit pas être transformée
	struct coord coord_dn_init = {3,8}; //Coordonnées initiales de la dame noire qui ne doit pas être transformée
	struct coord coord_dn_fin = {2,9}; //Coordonnées finales de la dame noire qui ne doit pas être transformée
	struct coord coord_pb2_init = {8,7}; //Coordonnées initiales du pion blanc qui ne doit pas être transformé
	struct coord coord_pb2_fin = {6,9}; //Coordonnées finales du pion blanc qui ne doit pas être transformé
	struct coord coord_pn2_init = {9,2}; //Coordonnées initiales du pion noir qui ne doit pas être transformé
	struct coord coord_pn2_fin = {7,0}; //Coordonnées finales du pion noir qui ne doit pas être transformé
	
	
	(*ptrseq_pb1).c_old = coord_pb1_init;
	(*ptrseq_pb1).c_new = coord_pb1_fin;
	ptrseq_pb1 -> next = NULL;
	(*ptrseq_pn1).c_old = coord_pn1_init;
	(*ptrseq_pn1).c_new = coord_pn1_fin;
	ptrseq_pn1 -> next = NULL;
	(*ptrseq_db).c_old = coord_db_init;
	(*ptrseq_db).c_new = coord_db_fin;
	ptrseq_db -> next = NULL;
	(*ptrseq_dn).c_old = coord_dn_init;
	(*ptrseq_dn).c_new = coord_dn_fin;
	ptrseq_dn -> next = NULL;
	(*ptrseq_pb2).c_old = coord_pb2_init;
	(*ptrseq_pb2).c_new = coord_pb2_fin;
	ptrseq_pb2 -> next = NULL;
	(*ptrseq_pn2).c_old = coord_pn2_init;
	(*ptrseq_pn2).c_new = coord_pn2_fin;
	ptrseq_pn2 -> next = NULL;
	
	ptrmove_pb1 -> seq = ptrseq_pb1;
	ptrmove_pb1 -> next = ptrmove_pn1;
	ptrmove_pn1 -> seq = ptrseq_pn1;
	ptrmove_pn1 -> next = ptrmove_db;
	ptrmove_db -> seq = ptrseq_db;
	ptrmove_db -> next = ptrmove_dn;
	ptrmove_dn -> seq = ptrseq_dn;
	ptrmove_dn -> next = ptrmove_pb2;
	ptrmove_pb2 -> seq = ptrseq_pb2;
	ptrmove_pb2 -> next = ptrmove_pn2;
	ptrmove_pn2 -> seq = ptrseq_pn2;
	ptrmove_pn2 -> next = NULL;
	
	apply_moves(game3, ptrmove_pb1);
	
	int gameboard1_final[10][10] = {{0,7,0,7,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,5,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,1,0,0},{3,0,3,0,0,0,5,0,0,0}};
	
	int i2;
	int j2;
	for(i2 = 0; i2 < 10; i2++){
		for(j2 = 0; j2 < 10; j2++){
			
			CU_ASSERT_EQUAL((*game3).board[i2][j2], gameboard1_final[i2][j2]);
			
		}	
	}
	
	free(ptrseq_pn2);
	ptrmove_pn2 -> seq = NULL;
	free(ptrmove_pn2);
	ptrmove_pb2 -> next = NULL;
	free(ptrseq_pb2);
	ptrmove_pb2 -> seq = NULL;
	free(ptrmove_pb2);
	ptrmove_dn -> next = NULL;
	free(ptrseq_dn);
	ptrmove_dn -> seq = NULL;
	free(ptrmove_dn);
	ptrmove_db -> next = NULL;
	free(ptrseq_db);
	ptrmove_db -> seq = NULL;
	free(ptrmove_db);
	ptrmove_pn1 -> next = NULL;
	free(ptrseq_pn1);
	ptrmove_pn1 -> seq = NULL;
	free(ptrmove_pn1);
	ptrmove_pb1 -> next = NULL;
	free(ptrseq_pb1);
	ptrmove_pb1 -> seq = NULL;
	free(ptrmove_pb1);
	
	/* Vérifie qu'un mouvement non-valide est signalé */
	
	int gameboard2[10][10] = {{1,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
	
	struct game *game4;
	game4 = load_game(10, 10, &(&gameboard2), 0);
	
	struct move_seq *ptrseq_err = (struct move_seq *) malloc(sizeof(struct move_seq));
	if (ptrseq_err == NULL)
		exit(EXIT_FAILURE);
	
	struct move *ptrmove_err = (struct move *) malloc(sizeof(struct move));
	if (ptrmove_err == NULL)
		exit(EXIT_FAILURE);
	
	struct coord coord_err1 = {0,0};
	struct coord coord_err2 = {3,8};
	
	(*ptrseq_err).c_old = coord_err1;
	(*ptrseq_err).c_new = coord_err2;
	ptrseq_err -> next = NULL;
	
	ptrmove_err -> seq = ptrseq_err;
	ptrmove_err -> next = NULL;
	
	int resultat_err = apply_moves(game4, ptrmove_err);
	
	CU_ASSERT_EQUAL(resultat_err, -1); //Un mouvement non-valide doit être signalé par '-1'
	
	free(ptrseq_err);
	ptrmove_err -> seq = NULL;
	free(ptrmove_err);
	
	/* Vérifie qu'un jeu terminé est bien signalé 
	
	  0_1_2_3_4_5_6_7_8_9		  0_1_2_3_4_5_6_7_8_9
	0|1 0 0 0 0 0 0 0 0 0		0|0 0 0 0 0 0 0 0 0 0
	1|0 5 0 0 0 0 0 0 0 0		1|0 0 0 0 0 0 0 0 0 0
	2|0 0 0 0 0 0 0 0 0 0		2|0 0 1 0 0 0 0 0 0 0
	3|0 0 0 0 0 0 0 0 0 0		3|0 0 0 0 0 0 0 0 0 0
	4|0 0 0 0 0 0 0 0 0 0  =>	4|0 0 0 0 0 0 0 0 0 0
	5|0 0 0 0 0 0 0 0 0 0		5|0 0 0 0 0 0 0 0 0 0	
	6|0 0 0 0 0 0 0 0 0 0		6|0 0 0 0 0 0 0 0 0 0	1 = pion noir
	7|0 0 0 0 0 0 0 0 0 0		7|0 0 0 0 0 0 0 0 0 0	3 = dame noir
	8|0 0 0 O 0 0 0 0 0 0		8|0 0 0 0 0 0 0 0 0 0	5 = pion blanc
	9|0 0 0 0 0 0 0 0 0 0		9|0 0 0 0 0 0 0 0 0 0	7 = dame blanche
	
	*/
	
	int gameboard3[10][10] = {{1,0,0,0,0,0,0,0,0,0},{0,5,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
	
	struct game *game5;
	game5 = load_game(10, 10, &(&gameboard3), 0);
	
	struct move_seq *ptrseq_end = (struct move_seq *) malloc(sizeof(struct move_seq));
	if (ptrseq_err == NULL)
		exit(EXIT_FAILURE);
	
	struct move *ptrmove_end = (struct move *) malloc(sizeof(struct move));
	if (ptrmove_err == NULL)
		exit(EXIT_FAILURE);
	
	struct coord coord_end1 = {0,0};
	struct coord coord_end2 = {2,2};
	
	(*ptrseq_end).c_old = coord_end1;
	(*ptrseq_end).c_new = coord_end2;
	ptrseq_end -> next = NULL;
	
	ptrmove_end -> seq = ptrseq_end;
	ptrmove_end -> next = NULL;
	
	int resultat_end = apply_moves(game5, ptrmove_end);
	
	CU_ASSERT_EQUAL(resultat_end,1); //Vérifie que la partie est finie
	
	free(ptrseq_end);
	ptrmove_end -> seq = NULL;
	free(ptrmove_end);
	
}

/*
 * Vérifie que les différents mouvements non-valides sont bien repérés par la fonction is_move_seq_valid
 */
void test_is_move_seq_valid(void)
{
	
	int gameboardvalid[10][10] = {{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,0,5,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,7,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
	
	struct game *gameval;
	gameval = load_game(10, 10, &(&gameboardvalid), 1);
	
	struct move_seq *seq_casedevant = (struct move_seq *) malloc(sizeof(struct move_seq)); //Un pion doit se déplacer en diagonale
	if (seq_casedevant == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *seq_casederriere = (struct move_seq *) malloc(sizeof(struct move_seq)); //Un pion ne peut pas aller en arrière
	if (seq_casederriere == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *seq_casevide = (struct move_seq *) malloc(sizeof(struct move_seq)); //Pas de pion à déplacer
	if (seq_casevide == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *seq_sautecasevide = (struct move_seq *) malloc(sizeof(struct move_seq)); //Un pion saute une case vide (comme pour prendre un pion adverse)
	if (seq_sautecasevide == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *seq_mauvaisjoueur = (struct move_seq *) malloc(sizeof(struct move_seq)); //C'est à l'autre joueur de jouer
	if (seq_mauvaisjoueur == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *seq_dame = (struct move_seq *) malloc(sizeof(struct move_seq)); //Doit etre valide, mouvement de la dame sur la diagonale
	if (seq_dame == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *seq_caseoccupee = (struct move_seq *) malloc(sizeof(struct move_seq)); //Pion sur la case d'arrivée
	if (seq_caseoccupee == NULL)
		exit(EXIT_FAILURE);
	struct move_seq *seq_plusieurspions = (struct move_seq *) malloc(sizeof(struct move_seq)); //Un move contient plusieurs séquences avec des pions différents qui bougent
	if (seq_plusieurspions == NULL)
		exit(EXIT_FAILURE);
		
	struct coord coord_pn = {3,2};
	struct coord coord_pb = {2,3};
	struct coord coord_db = {7,6};
	struct coord casedevant = {2,2}; 
	struct coord casederriere = {2,4}; 
	struct coord casevide = {1,3}; 
	struct coord sautecasevide = {0,2};  
	struct coord mauvaisjoueur = {1,4};
	struct coord dame = {2,1}; 
	struct coord valid = {4,1};
	
	(*seq_casedevant).c_old = coord_pb;
	(*seq_casedevant).c_new = casedevant;
	seq_casedevant -> next = NULL;
	(*seq_casederriere).c_old = coord_pb;
	(*seq_casederriere).c_new = casederriere;
	seq_casederriere -> next = NULL;
	(*seq_casevide).c_old = casevide;
	(*seq_casevide).c_new = casedevant;
	seq_casevide -> next = NULL;
	(*seq_sautecasevide).c_old = coord_pb;
	(*seq_sautecasevide).c_new = sautecasevide;
	seq_sautecasevide -> next = NULL;
	(*seq_mauvaisjoueur).c_old = coord_pn;
	(*seq_mauvaisjoueur).c_new = mauvaisjoueur;
	seq_mauvaisjoueur -> next = NULL;
	(*seq_dame).c_old = coord_db;
	(*seq_dame).c_new = dame;
	seq_dame -> next = NULL;
	(*seq_caseoccupee).c_old = coord_pb;
	(*seq_caseoccupee).c_new = coord_pn;
	seq_caseoccupee -> next = NULL;
	(*seq_plusieurspions).c_old = coord_pb;
	(*seq_plusieurspions).c_new = valid;
	seq_plusieurspions -> next = NULL;
	
	struct coord *coordcapture;
	int nonvalid1 = is_move_seq_valid(gameval, seq_casedevant, NULL, coordcapture);
	int nonvalid2 = is_move_seq_valid(gameval, seq_casederriere, NULL, coordcapture);
	int nonvalid3 = is_move_seq_valid(gameval, seq_casevide, NULL, coordcapture);
	int nonvalid4 = is_move_seq_valid(gameval, seq_sautecasevide, NULL, coordcapture);
	int nonvalid5 = is_move_seq_valid(gameval, seq_mauvaisjoueur, NULL, coordcapture);
	int valid1 = is_move_seq_valid(gameval, seq_dame, NULL, coordcapture);
	int nonvalid6 = is_move_seq_valid(gameval, seq_caseoccupee, NULL, coordcapture);
	int nonvalid7 = is_move_seq_valid(gameval, seq_plusieurspions, seq_dame, coordcapture);
	
	CU_ASSERT_EQUAL(nonvalid1, 0);
	CU_ASSERT_EQUAL(nonvalid2, 0);
	CU_ASSERT_EQUAL(nonvalid3, 0);
	CU_ASSERT_EQUAL(nonvalid4, 0);
	CU_ASSERT_EQUAL(nonvalid5, 0);
	CU_ASSERT_EQUAL(valid1, 2);
	CU_ASSERT_EQUAL(nonvalid6, 0);
	CU_ASSERT_EQUAL(nonvalid7, 0);
	
	free(seq_casedevant);
	free(seq_casederriere);
	free(seq_casevide);
	free(seq_sautecasevide);
	free(seq_mauvaisjoueur);
	free(seq_dame);
	free(seq_caseoccupee);
	free(seq_plusieurspions);
	
}

/*
 * Cette fonction reprend la partie game1 telle qu'à la fin de la fonction test_apply_moves et annule tous les mouvements + 1. Le mouvement de plus devrait être ignoré et le plateau final devrait être celui de départ.
 */
void test_undo_moves(void)
{
	
	undo_moves(game1, 7);
	
	verifdep(game1);
	
}

/*
 * Cette fonction vérifie que la disposition des pièces dans le jeu placé en argument correspond bien au plateau tel qu'il devrait être au début d'une partie
 */
void verifdep(struct game *gamev)
{

	int i;
	int j;
	for(i = 0; i < 10; i++) {
		for(j = 0; j < 10; j++) {
		
			if(j < 4 && ((i+j)&1) ) //Les pions se situent sur les cases dont la somme des coordonnées est impaire
			{
				CU_ASSERT_EQUAL((*gamev).board[i][j], 1); //Vérifie l'emplacement des pions noirs
			}
			else if(j > 5 && ((i+j)&1) ) //Les pions se situent sur les cases dont la somme des coordonnées est impaire
			{
				CU_ASSERT_EQUAL((*gamev).board[i][j], 5); //Vérifie l'emplacement des pions blancs
			}
			else
			{
				CU_ASSERT_NOT_EQUAL((*gamev).board[i][j], 1); //Vérifie que les autres cases sont bien vides
				CU_ASSERT_NOT_EQUAL((*gamev).board[i][j], 5); 
			}
			
		}
	} 

}
