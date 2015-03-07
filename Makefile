all: programme test

programme: programme.c
	gcc -o programme programme.c dames.c

test:test.c
	gcc -o test test.c dames.c -I$HOME/local/include
