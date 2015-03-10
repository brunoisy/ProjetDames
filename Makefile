all: jeu test

jeu: programme.c
	gcc -o programme programme.c dames.c

test:test.c
	gcc -I$(HOME)/local/include test.c dames.c -L$(HOME)/local/lib -lcunit -o test
