all: jeu test

jeu: programme.c
	gcc -o programme programme.c dames.c

test:test.c
	gcc test.c dames.c -lcunit -o test
