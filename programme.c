#include <stdio.h>
#include <stdlib.h>
#include "dames.h"


int main (int argc, char * argv[]){
	struct game * game=new_game(10,10);
	if(game==NULL)
		return EXIT_FAILURE;
	printf("\n 1: pion noir, 5: pion blanc, 3: dame noire, 7: dame blanche\n\n");
	print_board(game);
	printf("\naux blancs de jouer\n");
	int choice, choice2, xin, yin, xfin, yfin, undo, am;
	struct move * moves;
	struct move_seq * seq;
	choice=1;
	while(choice!=3){
		printf("les commandes sont: \n   1: move \n   2: undo_move \n   3: quit\n");
		printf("choix commande:\n");
		scanf("%i", &choice);
		if(choice==1){
			moves=(struct move *) malloc (sizeof(struct move));
			if(moves==NULL)
				return EXIT_FAILURE;
			seq=(struct move_seq *) malloc (sizeof(struct move_seq));
			if(seq==NULL)
				return EXIT_FAILURE;
			moves->next=NULL;
			moves->seq=seq;
			choice2=1;
			while(choice2==1){
				printf("entrez Xinitial\n");
				scanf("%i", &xin);
				printf("entrez Yinitial\n");
				scanf("%i", &yin);
				printf("entrez Xfinal\n");
				scanf("%i", &xfin);
				printf("entrez Yfinal\n");
				scanf("%i", &yfin);	
				(seq->c_old).x=xin;
				(seq->c_old).y=yin;
				(seq->c_new).x=xfin;
				(seq->c_new).y=yfin;
				printf("les commandes sont: \n   1: ajouter une sequence \n   2: finir le mouvement\n");
				printf("choix commande:\n");
				scanf("%i", &choice2);
				if(choice2==1){
					seq->next=(struct move_seq *) malloc (sizeof(struct move_seq));
					if(seq->next==NULL)
						return EXIT_FAILURE;
					seq=seq->next;
				}
				if(choice2==2)
					seq->next=NULL;
			}	
			am=apply_moves(game, moves);
			free_moves(moves);
			moves=NULL;
			if(am==-1){
				printf("entrez un mouvement autorisé\n");
			}
			if(am==0){
				print_board(game);
				if(game->cur_player==PLAYER_WHITE)
					printf("\naux blancs de jouer\n");
				if(game->cur_player==PLAYER_BLACK)
					printf("\naux noirs de jouer\n");
			}
			if(am==1){
				print_board(game);
				printf("\nfélécitations, vous avez gagné!\n");
			}
		}
		if(choice==2){
			printf("entrez le nombre de mouvements à defaire\n");
			scanf("%i", &undo);
			if(undo_moves(game, undo)==-1)
				printf("erreur dans l'annulation de mouvements, redémarrez la partie\n");
			print_board(game);
			if(game->cur_player==PLAYER_WHITE)
				printf("\naux blancs de jouer\n");
			if(game->cur_player==PLAYER_BLACK)
				printf("\naux noirs de jouer\n");
		}
		printf("______________________________________________________________\n");
	}
	free_game(game);
	game=NULL;

	printf("partie quittée\n");
	printf("______________________________________________________________\n");
}
