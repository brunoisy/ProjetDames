#include <stdio.h>
#include <stdlib.h>
#include "dames.h"

int pnoir   =1;
int pblanc  =5;
int dnoir   =3;
int dblanc  =7;
int cvide   =0;

int main (int argc, char * argv[]){
	
}


extern struct game *new_game(int xsize, int ysize){ //pq xsize, ysize, pas tjrs 9x9?
	struct game * newG;
	newG->xsize=xsize;
	newG->ysize=ysize;
	int ** board = malloc(xsize*ysize*sizeof(int)); //louche
	if (board==NULL)
		{return NULL;}
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
		j=0;
	}
	for(i=4; i<6; i++){
		for(j=0; j<10; j++){			
			board[i][j]=cvide;			
		}
		j=0;
	}
	for(i=6; i<10; i++){
		for(j=0; j<10; j++){
			if ((i+j)%2==0){
				board[i][j]=pblanc;
			}
			else{
				board[i][j]=cvide;
			}
		}
		j=0;
	}
	newG->board=board;
	return newG;
}



extern struct game *load_game(int xsize, int ysize, const int **board, int cur_player){// utilisation 'extern' demandee ici?
	struct game * newG;
	newG->board=board;
	newG->xsize=xsize;
	newG->ysize=ysize;
	newG->cur_player=cur_player; //quid de struct move *moves dans la struct game? : pas nécessaire à l'initialisation
	return newG;
}
