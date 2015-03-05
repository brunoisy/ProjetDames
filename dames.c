#include <stdio.h>
#include <stdlib.h>
#include "dames.h"

int change_player(int cur_player);
int ** make_empty_board(int xsize, int ysize);
int ** copy_board(int xsize, const int ** board);
void free_board(int ** board, int xsize);
void free_moves(struct move * moves);
void free_move_seq(struct move_seq *seq);
struct move* copy_moves(const struct move* moves);
struct move_seq* copy_move_seq(const struct move_seq* seq);
int color(int piece);
void add_move_to_game(struct game * game, const struct move * addmove);
int apply_move_seq(struct game * game, struct move_seq * appseq, struct move_seq * prev);
int undo_move_seq(struct game *game);


const int cvide   =0;
const int pnoir   =1;
const int pblanc  =5;
const int dnoir   =3;
const int dblanc  =7;


int main (int argc, char * argv[]){ 
	//printf("test new_game&&print_board\n");
	struct game * ng=new_game(10,10);
/*	printf("xsize=%i\n", ng->xsize);
	printf("ysize=%i\n",ng->ysize);
	printf("cur_player=%i\n",ng->cur_player);
	print_board(ng);
*/
	//printf("\ntest is_move_seq_valid\n");
	struct move * moves=(struct move *)malloc(sizeof(struct move));
	struct move_seq * seq=(struct move_seq *)malloc(sizeof(struct move_seq));
	struct coord * taken=(struct coord *)malloc(sizeof(struct coord));

	moves->next=NULL;
	moves->seq=seq;
	seq->next=NULL;
	struct coord c_old;
	struct coord c_new;
	c_old.x=1;
	c_old.y=6;
	c_new.x=0;
	c_new.y=5;
	seq->c_old=c_old;
	seq->c_new=c_new;
	//struct move * moves2=copy_moves(moves);
	//printf("moves %p moves2 %p", moves, moves2);
	//printf("moves->seq %p moves2->seq %p", moves->seq, moves2->seq);
	//printf("%i\n",is_move_seq_valid(ng, seq, NULL, taken));
	printf("\ntest apply_moves\n");
	apply_moves(ng, moves);
	print_board(ng);
	printf("\ntest undo_moves\n");
	undo_moves(ng,1);
	print_board(ng);
	free(taken);
	//free_moves(moves); //Il semblerait que la fonction apply_moves libere deja moves, pe du a une mauvaise copie
	free_game(ng);
}



extern struct game *new_game(int xsize, int ysize){
	struct game * newG=(struct game *) malloc(sizeof(struct game));
	if(newG==NULL)
		return NULL;
	int ** board = make_empty_board(xsize, ysize); // creer le damier
	if(board==NULL)
		return NULL;
		
	//remplir le damier 
	int i;
	int j;
	for(i=0; i<10;i++){ // pr chaque abscisse
		for(j=0; j<4;j++){// pr les ordonnees allant de 0 a 3
			if ((i+j)%2==0)
				board[i][j]=cvide;
			else
				board[i][j]=pnoir;
		}
		for(j=4;j<6;j++){// pr les ordonnees allant de 4 a 5
			board[i][j]=cvide;
		}
		for(j=6;j<10;j++){// pr les ordonnees allant de 6 a 9
			if ((i+j)%2==0)
				board[i][j]=cvide;
			else
				board[i][j]=pblanc;
		}
	}

	newG->board=board;
	newG->xsize=xsize;
	newG->ysize=ysize;
	newG->moves=NULL;
	newG->cur_player=PLAYER_WHITE;
	return newG;
}




extern struct game *load_game(int xsize, int ysize, const int **board, int cur_player){
	struct game * newG=(struct game *) malloc(sizeof(struct game));
	if (newG==NULL)
		return NULL;
	newG->board=copy_board(xsize, board); // car il est necessaire d'allouer un nouvel espace memoire a la variable newG->board
	newG->xsize=xsize;
	newG->ysize=ysize;
	newG->moves=NULL;
	newG->cur_player=cur_player;
	return newG;
}




extern void free_game(struct game *game){
	free_board(game->board, game->xsize);
	free_moves(game->moves);
	free(game);
	game=NULL;	
}




extern int apply_moves(struct game *game, const struct move *moves){
	struct move * movestoapply=copy_moves(moves);
	struct move * tobefreed=movestoapply;
	while(movestoapply!=NULL){ // tant que les mouvements ne sont pas termines
		if (apply_move_seq(game, movestoapply->seq, NULL)==-1) // appliquer la sequence, et s'il y a un mouvement invalide
			return -1;
		game->cur_player=change_player(game->cur_player); // on change de joueur
		add_move_to_game(game, movestoapply); // on rajoute le mouvement effectue a la liste de moves dans game
		movestoapply=movestoapply->next; 	
	}
	free_moves(tobefreed);
	return 0;
}



extern int is_move_seq_valid(const struct game *game, const struct move_seq *seq, const struct move_seq *prev, struct coord *taken){
	int ** board=game->board; // ne sera pas modifié
	const int xold=(seq->c_old).x;
	const int yold=(seq->c_old).y;
	const int xnew=(seq->c_new).x;
	const int ynew=(seq->c_new).y;
	int rafle=0;// vaudra 0 si prev==NULL et 1 si non

	if(xold<0 || xold>game->xsize-1 || yold<0 || yold>game->ysize-1) // si la case de depart est hors jeu
		return 0;
	if(xnew<0 || xnew>game->xsize-1 || ynew<0 || ynew>game->ysize-1) // si la case d'arrivee est hors-jeu
		return 0;
	int piecedep=board[xold][yold]; // valeur de la piece a deplacer
	int piecearr=board[xnew][ynew]; // valeur de la piece d'arrivee

	if(piecedep==cvide) // s'il faut deplacer une case vide
		return 0;
	if(color(piecedep)!=game->cur_player) // si la piece a deplacer n'est pas de la couleur du joueur actuel
		return 0;
	if(piecearr!=cvide)// si on arrive sur une case occupee
		return 0;

	if(prev!=NULL){ // si la sequence n'est pas la premiere d'un mouvement
		const struct coord prev_c_new=prev->c_new;
		const struct coord prev_c_old=prev->c_old;
		if(prev_c_new.x != xold||prev_c_new.y != yold) // si la sequence ne fait pas partie d'une rafle
			return 0;

		rafle=1;
	}
	int updir=-2*color(piecedep)+1; // direction du haut en fonction de la couleur de la piece deplacee : -1 si blanc, 1 si noir.
	int pvalue=(piecedep<<30)>>31; // valeur de la piece deplacee : 1 si dame, 0 si pion
	int deltax=xnew-xold;
	int deltay=ynew-yold;
	if(pvalue==0){// si nous bougons un pion
		if(abs(deltax)==1&&deltay==updir){ // si deplacement d'une case (sans prise):
			if(rafle==0) // si premier deplacement du mouvement
				return 1;
			else // si non (car le pion doit prendre une piece)
				return 0;
		}
		if(abs(deltax)==2&&abs(deltay)==2){ // si deplacement de 2 cases (avec prise)
			int mval=board[xold+deltax/2][yold+deltay/2]; // valeur de la case situee sur la diagonale de passage du pion
			if(mval==cvide) // si la case intermediare est vide
				return 0;
			if(color(mval)==color(piecedep)) // si la piece intermediare est de meme couleur que la piece bougee
				return 0;
			if(color(mval)==-2*color(piecedep)+1){ // si la piece intermediaire est de la couleur adverse 
				taken->x=xold+deltax/2;
				taken->y=yold+deltay/2;
				return 2;		
			}
			else{ 
				printf("FAIL1\n");
				return EXIT_FAILURE;			
			}
		}
		else // si deplacement illegal
			return 0;
	}
	if(pvalue==1){ // si nous bougons un reine
		if(abs(deltax)!=abs(deltay)) // si la reine ne se déplace pas en diagonale
			return 0;
		int takex; // abscisse de la piece prise par la reine
		int takey; // ordonnee de la piece prise par la reine
		int pionspris=0; // nombre de pions pris par la reine en une sequence. si >1, sequence invalide
		int cval; // valeur de la case survolee par la diagonale
		int i;
		for(i=1; i<abs(deltax); i++){ // pour tous les elements situes sur la diagonale parcoure par la reine
			cval=board[xold+i*deltax/abs(deltax)][yold+i*deltay/abs(deltax)];
			if(cval!=cvide){ // si ce n'est pas une case vide
				if(color(cval)==color(piecedep)) // si cet element est de la meme couleur que la reine
					return 0;
				if(color(cval)==-2*color(piecedep)+1){ // si cet element est de couleur opposee
					takex=xold+i*deltax/abs(deltax);
					takey=yold+i*deltay/abs(deltax);
					pionspris++;
				}
				else{
					printf("FAIL2\n");
					return EXIT_FAILURE;
				}
			}
		}
		if (pionspris==0){ // si la reine n'a fait que se deplacer
			if(rafle==0) // si premier déplacement du mouvement
				return 1;
			else // si non (car la reine doit prendre une piece ennemie)
				return 0;
		}
		if(pionspris==1){ // si la reine a pris une piece ennemie
			taken->x=takex;
			taken->y=takey;
			return 2;
		}
		else // si la reine a pris plus d'une piece ennemie
			return 0;
	}
	else{
		printf("FAIL3\n");
		return EXIT_FAILURE;
	}
}




extern int undo_moves(struct game *game, int n){
	int i;
	for(i=0;i<n||game->moves==NULL;i++){
		if(undo_move_seq(game)==-1) // defaire le dernier mouvement, et si erreur
			return -1;
	}
	return 0;
}





extern void print_board(const struct game *game){
	int ** board=game->board;
	int i;
	int j;
	for(j=0;j<10;j++){ // pr chaque ligne
		for(i=0;i<10;i++){
			printf(" %i",board[i][j]);// imprimer chaque element
		}
		printf("\n");
	}
}








//____________________________________________________________________________________________________________________________________________









/*
 * change_player
 * renvoie le joueur suivant (0 si 1, 1 si 0)
 *
 * @cur_player: joueur actuel
 */
int change_player(int cur_player){
	return 1-cur_player;
}


/*
 * copy_moves
 * cree une liste chainee de mouvements identique a celle passee en argument, mais pointée par un autre pointeur
 *
 * @moves: pointeur vers la structure moves a copier
 */
struct move* copy_moves(const struct move* moves){
	if (moves==NULL)
		return NULL;
	struct move * newmoves=(struct move *)malloc(sizeof(struct move));
	if(newmoves==NULL)
		return NULL;
	struct move * nthmove;
	struct move * nextmove;
	*newmoves=*moves;
	nthmove=newmoves;
	while(nthmove->next!=NULL){
		nthmove->seq=copy_move_seq(nthmove->seq);
		nextmove=(struct move *)malloc(sizeof(struct move));
		if(nextmove==NULL)
			return NULL;
		*nextmove=*(nthmove->next);
		nthmove->next=nextmove;
		nthmove=nextmove;
	}
	return newmoves;
}


/*
 * copy_move_seq
 * cree une liste chainee de sequences identique a celle passee en argument, mais pointée par un autre pointeur
 *
 * @seq: pointeur vers la structure sequence a copier
 */
struct move_seq* copy_move_seq(const struct move_seq* seq){
	if (seq==NULL)
		return NULL;
	struct move_seq * newseq=(struct move_seq *)malloc(sizeof(struct move_seq));
	struct move_seq * nthseq;
	struct move_seq * nextseq;
	*newseq=*seq;
	nthseq=newseq;
	while(nthseq->next!=NULL){
		nextseq=(struct move_seq *)malloc(sizeof(struct move_seq));
		*nextseq=*(nthseq->next);
		nthseq->next=nextseq;
		nthseq=nextseq;
	}
	return newseq;
}


/*
 * add_move_to_game
 * rajoute le premier mouvement de addmove (le dernier mouvement joue) a (!!!) l'avant (!!!) de la chaine de moves de la partie
 *
 * @game: pointeur vers la structure game
 * @addmove: pointeur vers la structure move dont on veut rajouter le premier element a game->moves
 */
void add_move_to_game(struct game * game, const struct move * addmove){
	struct move * newmove=(struct move *)malloc(sizeof(struct move));
	newmove->seq=copy_move_seq(addmove->seq);
	newmove->next=game->moves;
	game->moves=newmove;
}


/*
 * make_empty_board
 * crée un damier vide (sans pions)
 *
 * @xsize: taille des abscisses du plateau
 * @ysize: taille des ordonnees du plateau
 */
int ** make_empty_board(int xsize, int ysize){
	int ** board = (int **) malloc((size_t)xsize*sizeof(int *));
	if (board==NULL)
		return NULL;
	int x;
	for(x=0;x<xsize;x++){
		board[x]=(int *) malloc((size_t)ysize*sizeof(int));
		if (board[x]==NULL)
			return NULL;
	}
	return board;
}


/*
 * copy_board
 * cree un damier identique a celui passe en argument, mais pointé par un autre pointeur
 *
 * @board: tableau a copier
 */
int ** copy_board(int xsize, const int **board){
	int ** newboard=make_empty_board(xsize,10);
	if(newboard==NULL)
		return NULL;
	int i;
	int j;
	for(i=0;i<xsize;i++){
		for(j=0;j<10;j++){
			newboard[i][j]=board[i][j];
		}
	}
	return newboard;
}


/*
 * apply_move_seq
 * applique une sequence de mouvements (un mouvement simple) a une partie
 *
 * @game: pointeur vers la structure de la partie
 * @appseq: pointeur vers la structure du mouvement a appliquer
 * @prev: pointeur vers la séquence précédent immédiatement la séquence à vérifier, NULL s'il @seq est la première séquence du mouvement
 */
int apply_move_seq(struct game * game, struct move_seq * appseq, struct move_seq * prev){
	struct move_seq * seq=appseq; // car appseq doit rester pointer sur le debut de la sequence
	int ** board=game->board;
	struct coord * taken=(struct coord *)malloc(sizeof(struct coord*));
	struct coord c_old;
	struct coord c_new;
	while(seq!=NULL){ // tant que la sequence n'est pas terminee
		if(is_move_seq_valid(game, seq, prev, taken)==0){ // si la sequence n'est pas valide
			free(taken);
			taken=NULL;
			return -1;
		}
		c_old=seq->c_old;
		c_new=seq->c_new;
		seq->old_orig=board[c_old.x][c_old.y]; //old_orig contient la valeur entière de la pièce se situant en @c_old avant l'exécution du mouvement
		if(c_new.y==0&&game->cur_player==PLAYER_WHITE) // si une piece blanche est arrivee a l'autre bout du damier
			board[c_new.x][c_new.y]=dblanc;
		else{	
			if(c_new.y==10&&game->cur_player==PLAYER_BLACK) // si une piece noire est arrivee a l'autre bout du damier
				board[c_new.x][c_new.y]=dnoir;
			else // si non
				board[c_new.x][c_new.y]=board[c_old.x][c_old.y]; // la nouvelle case contient la piece deplacee
		}
		board[c_old.x][c_old.y]=cvide; // l'ancienne case est maintenant vide
		if(taken!=NULL){// si une piece a ete prise
			seq->piece_value=board[taken->x][taken->y];
			seq->piece_taken=*taken;
			board[taken->x][taken->y]=cvide; // la case de la piece prise est vide
		}
		else
			seq->piece_value=0;
		prev=seq;
		seq=seq->next;
	}
	free(taken);
	taken=NULL;
	return 0;
}


/*
 * color
 * renvoie la couleur de la piece passe en argument
 *
 * @piece: valeur de la piece dont la couleur est a evaluer
 */
int color(int piece){
	return piece>>2;
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
	board=NULL;
}


/*
 * free_moves
 * Libérer les ressources allouées à une suite de mouvements
 *
 * @moves: pointeur vers la liste chainee de moves
 */
void free_moves(struct move *moves){
	struct move * nextmoves;
	while(moves!=NULL){
		free_move_seq(moves->seq);
		nextmoves=moves->next;
		free(moves);
		moves=NULL;
		moves=nextmoves;
	}
printf("infreemoves\n");
}


/*
 * free_move_seq
 * Libérer les ressources allouées à une suite de séquences d'un mouvement
 *
 * @moves: pointeur vers la liste chainee de move_seq
 */
void free_move_seq(struct move_seq *seq){
	struct move_seq *nextseq;
	while(seq!=NULL){
		nextseq=seq->next;
		free(seq);
		seq=NULL;
		seq=nextseq;
	}
}


/*
 * undo_move_seq
 * defait le dernier mouvement d'une partie
 *
 * @game: pointeur vers la partie a modifier
 * @return: 0 si OK, -1 si erreur
 */
int undo_move_seq(struct game *game){
	struct move_seq * seq=(game->moves)->seq;
	struct coord c_old;
	struct coord c_new;
	struct coord piece_taken;
	int ** board=game->board;
	while(seq!=NULL){
		c_old=seq->c_old;
		c_new=seq->c_new;
		piece_taken=seq->piece_taken;
		board[c_old.x][c_old.y]=seq->old_orig; // la piece ayant bouge retrouve sa place
		board[c_new.x][c_new.y]=cvide; // l'endroit ou elle etait arrivee redevient une case vide
		if(seq->piece_value!=0)
			board[piece_taken.x][piece_taken.y]=seq->piece_value; // la piece prise reapparait
		seq=seq->next;
	}
	game->cur_player=change_player(game->cur_player); // on change de joueur
	return 0;
}
