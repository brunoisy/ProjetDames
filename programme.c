#include <stdio.h>
#include <stdlib.h>
#include "dames.h"


int main (int argc, char * argv[]){
	printf("\nles commandes sont: \n 1:move \n 2:undo_move \n 3:quit\n" );
	struct game * game=new_game(10,10);
	if(game==NULL)
		return EXIT_FAILURE;
	print_board(game);
	printf("aux blancs de jouer\n");

	int * choice=(int *)malloc(sizeof(int));
	int * choice2=(int *)malloc(sizeof(int));
	int * xin=(int *)malloc(sizeof(int));
	int * yin=(int *)malloc(sizeof(int));
	int * xfin=(int *)malloc(sizeof(int));
	int * yfin=(int *)malloc(sizeof(int));
	int * undo=(int *)malloc(sizeof(int));
	printf("choix commande:\n");
	scanf("%i", choice);
	while(*choice!=3){
		if(*choice==1){
			struct move * moves=(struct move *) malloc (sizeof(struct move));
			if(moves==NULL)
				return EXIT_FAILURE;
			struct move_seq * seq=(struct move_seq *) malloc (sizeof(struct move_seq));
			if(seq==NULL)
				return EXIT_FAILURE;
			moves->seq=seq;
			*choice2=1;
			while(*choice2==1){
				printf("entrez Xinitial Yinitial Xfinal Yfinal\n");
				scanf("%i %i %i %i", xin, yin, xfin, yfin);
				(seq->c_old).x=*xin;
				(seq->c_old).y=*yin;
				(seq->c_new).x=*xfin;
				(seq->c_new).y=*yfin;
				seq=seq->next;
				printf("les commandes sont: \n 1:ajouter une sequence \n 2:finir le mouvement\n");
				printf("choix commande:\n");
				scanf("%i", choice2);
				if(*choice==1){
					seq=(struct move_seq *) malloc (sizeof(struct move_seq));
					if(seq==NULL)
						return EXIT_FAILURE;
				}
				if(*choice==2)
					seq=NULL;
			}		
			int j=apply_moves(game, moves);
			free_moves(moves);
			moves=NULL;
			if(j==-1){
				printf("entrez un mouvement autorisé\n");
			}
			if(j==0){
				print_board(game);
				if(game->cur_player==PLAYER_WHITE)
					printf("aux blancs de jouer\n");
				if(game->cur_player==PLAYER_BLACK)
					printf("aux noirs de jouer\n");
			}
			if(j==1){
				print_board(game);
				printf("félécitations, vous avez gagné!\n");
			}
		}
		if(*choice==2){
			printf("entrez le nombre de mouvements à defaire");
			scanf("%i", undo);
			undo_moves(game, *undo);
		}
		printf("choix commande:\n");
		scanf("%i", choice);
	}
	free_game(game);
	game=NULL;
	free(choice);
	choice=NULL;
	free(choice2);
	choice2=NULL;
	free(xin);
	xin=NULL;
	free(yin);
	yin=NULL;
	free(xfin);
	xfin=NULL;
	free(yfin);
	yfin=NULL;
	free(undo);
	undo=NULL;
	printf("partie quittée\n");
}
