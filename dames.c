#include <stdio.h>
#include <stdlib.h>
#include "dames.h"

void free_board(int ** board, int xsize);
void free_moves(struct move * moves);
void free_move_seq(struct move_seq *seq);
int color(int piece);
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
	for(i=0; i<4; i++){ // ne respecte pas xsize
		for(j=0; j<ysize; j++){
			if ((i+j)%2==0){
				board[i][j]=cvide;
			}
			else{
				board[i][j]=pnoir;
			}
		}
	}
	for(i=4; i<6; i++){
		for(j=0; j<ysize; j++){			
			board[i][j]=cvide;			
		}
	}
	for(i=6; i<10; i++){
		for(j=0; j<ysize; j++){
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



extern struct game *load_game(int xsize, int ysize, const int **board, int cur_player){
	struct game * newG=(struct game *) malloc(sizeof(struct game));	;
	newG->board=(int **) board;
	newG->xsize=xsize;
	newG->ysize=ysize;
	newG->moves=NULL; //idem newGame
	newG->cur_player=cur_player;
	return newG;
}



extern void free_game(struct game *game){
	free_board(game->board, game->xsize);
	free_moves(game->moves);
	free(game);
	game=NULL;	
}



extern int is_move_seq_valid(const struct game *game, const struct move_seq *seq, const struct move_seq *prev, struct coord *taken){
	int ** board=game->board;
	struct coord c_old=seq->c_old;
	struct coord c_new=seq->c_new;
	struct coord prev_c_new=prev->c_new;	
	int xold=c_old.x;
	int yold=c_old.y;
	int xnew=c_new.x;
	int ynew=c_new.y;	
	if(xold<0 || xold>game->xsize-1 || yold<0 || yold>game->ysize-1){ // si la case de depart est hors jeu
		return 0;
	}
	if(xnew<0 || xnew>game->xsize-1 || ynew<0 || ynew>game->ysize-1){ // si la case d'arrivee est hors-jeu
		return 0;
	}
	int piecedep=board[xold][yold]; // valeur de la piece a deplacer
	int piecearr=board[xnew][ynew]; // valeur de la piece d'arrivee
	if(piecedep==cvide){// s'il faut deplacer une case vide
		return 0; 
	}
	if(color(piecedep)!=game->cur_player){ // si la piece a deplacer n'est pas de la couleur du joueur actuel
		return 0;
	}
	if(piecearr!=cvide){// si on arrive sur une case occupee
		return 0;
	}
	if(prev!=NULL){ // si la sequence n'est pas la premiere d'un mouvement
		if(prev_c_new.x != xold||prev_c_new.y != yold){ // si la sequence ne fait pas partie d'une rafle
			return 0;
		}
		//***
	}
	int updir=-2*color(piecedep)+1; // direction du haut en fonction de la couleur de la piece deplacee : -1 si blanc, 1 si noir.
	int pvalue=31>>(30<<piecedep); // valeur de la piece : 1 si dame, 0 si pion
	int deltax=xnew-xold;
	int deltay=ynew-yold;
	if(pvalue==0){// si nous bougons un pion
		if(abs(deltax)==1&&deltay==updir){ // si deplacement d'une case (sans prise):
			return 1;
		}
		if(abs(deltax)==2&&abs(deltay)==2){ // si deplacement de 2 cases (avec prise)
			if(board[xold+deltax/2][yold+deltay/2]==cvide){ // si la case intermediare est vide
				return 0;
			}
			if(color(board[xold+deltax/2][yold+deltay/2])==color(piecedep)){ // si la piece intermediare est de meme couleur que la piece bougee
				return 0;
			}
			if(color(board[xold+deltax/2][yold+deltay/2])==-2*color(piecedep)+1){ // si la piece intermediaire est de la couleur adverse 
				taken->x=xold+deltax/2;
				taken->y=yold+deltay/2;
				return 2;		
			}
			else{ 
				printf("FAIL1");
				return EXIT_FAILURE;			
			}
		}
	}
	if(pvalue==1){// si nous bougons un reine
		if(abs(deltax)!=abs(deltay)){ // si la reine ne se déplace pas en diagonale
			return 0;
		}
		int takex; // abscisse de la piece prise par la reine
		int takey; // ordonnee de la piece prise par la reine
		int a=0; // nombre de pions pris par la reine en une sequence. si >1, sequence invalide
		int cval; // valeur de la case survolee par la diagonale
		int i;
		for(i=1; i<abs(deltax); i++){ // pour tous les elements situes sur la diagonale parcoure par la reine
			cval=board[xold+i*deltax/abs(deltax)][yold+i*deltay/abs(deltax)];
			if(cval==cvide){// si c'est une case vide
				// ne rien faire, legal ou skip?
			}
			else{
				if(color(cval)==color(piecedep)){ // si cet element est de la meme couleur que la reine
					return 0;
				}
				if(color(cval)==-2*color(piecedep)+1){ // si cet element est de couleur opposee
					takex=xold+i*deltax/abs(deltax);
					takey=yold+i*deltay/abs(deltax);
					a++;
				}
				else{
					printf("FAIL2");
					return EXIT_FAILURE;
				}
			}
		}
		if (a==0){ // si la reine n'a fait que se deplacer
			return 1;
		}
		if(a==1){ // si la reine a pris un pion ennemi
			taken->x=takex;
			taken->y=takey;
			return 2;
		}
		else{ // si la reine a pris plus d'un pion ennemi
			return 0;
		}
	}
	else{
		printf("FAIL3");
		return EXIT_FAILURE;
	}
}

/*
 * color
 * renvoie la couleur de la piece passe en argument
 *
 * @piece: valeur de la piece dont la couleur est a evaluer
 */
int color(int piece){
	return 2>>piece;
}

/*
 * free_board
 * Libérer les ressources allouées à plateau de jeu
 *
 * @bord: pointeur vers la structure du plateau de jeu
 * @xsize: taille des abscisses du plateau
 */
void free_board(int ** board, int xsize){
	int x;
	for(x=0;x<xsize;x++){
		free(board[x]);
		board[x]=NULL;
	}
	free(board);
	board=NULL; //return; ?
}


/*
 * free_moves
 * Libérer les ressources allouées à une suite de mouvements
 *
 * @moves: pointeur vers la liste chainee de moves
 */
void free_moves(struct move *moves){
	while(moves!=NULL){
		free_move_seq(moves->seq);
		struct move * nextmoves=moves->next;
		free(moves);
		moves=nextmoves;
	}
}


/*
 * free_move_seq
 * Libérer les ressources allouées à une suite de séquences d'un mouvement
 *
 * @moves: pointeur vers la liste chainee de move_seq
 */
void free_move_seq(struct move_seq *seq){
	while(seq!=NULL){
		struct move_seq *nextseq=seq->next;
		free(seq);
		seq=nextseq;
	}
}
