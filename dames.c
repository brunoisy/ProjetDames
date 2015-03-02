#include <stdio.h>
#include <stdlib.h>
#include "dames.h"

const int cvide   =0;
const int pnoir   =1;
const int pblanc  =5;
const int dnoir   =3;
const int dblanc  =7;


int main (int argc, char * argv[]){
	struct game * ng=new_game(10,10);
	printf("xsize=%i\n", ng->xsize);
	printf("ysize=%i\n",ng->ysize);
	printf("cur_player=%i\n",ng->cur_player);
	int ** board=ng->board;
	printf("case 0 0=%i\n",board[0][0]);
	printf("case 0 1=%i\n",board[0][1]);
	printf("case 1 0=%i\n",board[1][0]);
	printf("case 0 9=%i\n",board[0][9]);
	printf("case 9 0=%i\n",board[9][0]);
}


extern struct game *new_game(int xsize, int ysize){ //pq xsize, ysize, pas tjrs 10x10?
	struct game * newG=(struct game *) malloc(sizeof(struct game));

	int ** board = (int **) malloc((size_t)xsize*sizeof(int *));
	if (board==NULL)
		{return NULL;}
	int x;
	for(x=0;x<xsize;x++){
		board[x]=(int *) malloc((size_t)ysize*sizeof(int));
		if (board[x]==NULL)
			{return NULL;}
	}
		
	//remplir le damier 
	int i;
	int j;
	for(i=0; i<4; i++){
		for(j=0; j<10; j++){
			if ((i+j)%2==0){
				board[i][j]=cvide;
			}
			else{
				board[i][j]=pnoir;
			}
		}
	}
	
	for(i=4; i<6; i++){
		for(j=0; j<10; j++){			
			board[i][j]=cvide;			
		}
	}

	for(i=6; i<10; i++){
		for(j=0; j<10; j++){
			if ((i+j)%2==0){
				board[i][j]=cvide;
			}
			else{
				board[i][j]=pblanc;
			}
		}
	}

	newG->board=board;
	newG->xsize=xsize;
	newG->ysize=ysize;
	newG->moves=NULL; //pe un premier move vide? 
	newG->cur_player=PLAYER_WHITE;

	return newG;
}



extern struct game *load_game(int xsize, int ysize, const int **board, int cur_player){// utilisation 'extern' demandee ici?
	struct game * newG=(struct game *) malloc(sizeof(struct game));	;
	newG->board=(int **) board;
	newG->xsize=xsize;
	newG->ysize=ysize;
	newG->moves=NULL; //idem newGame
	newG->cur_player=cur_player;
	return newG;
}
