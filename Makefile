test: main.c closure.c closure.h player.c player.h
	cc -g main.c closure.c player.c -o test -Wall -Wextra
