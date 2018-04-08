FICHIER=main.o partie.o deplacement.o coup_joues.o piece.o configuration_damier.o partie_jouer.o
CC=gcc
#CFLAGS=-g -Wall -ansi -pedantic -O3
CFLAGS=-Wall
all:$(FICHIER)
	$(CC) $(CFLAGS) $(FICHIER) -o dames

main.o : main.c
	$(CC) $(CFLAGS) -c main.c
partie.o : partie.c
	$(CC) $(CFLAGS)  -c partie.c
deplacement.o : deplacement.c
	$(CC) $(CFLAGS) -c deplacement.c
piece.o : piece.c
	$(CC) $(CFLAGS) -c piece.c
coup_joues.o : coup_joues.c
	$(CC) $(CFLAGS) -c coup_joues.c
configuration_damier.o : configuration_damier.c
	$(CC) $(CFLAGS) -c configuration_damier.c
partie_jouer.o : partie_jouer.c
	$(CC) $(CFLAGS) -c partie_jouer.c


clean :
	rm -rf *.o
	rm -rf *~
	rm -rf dames
execute :
	dames

