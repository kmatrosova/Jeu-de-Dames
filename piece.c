#include <stdlib.h>
#include <stdio.h>

#include "piece.h"

piece* piece_creer(int statut, int joueur)
{
	piece* p = malloc(sizeof(piece));

	p->promu = statut;
	p->joueur = joueur;

	return p;
}

int piece_joueur(piece* p)
{
	return p->joueur;
}

piece* piece_identifier(char c)
{
	if (c == 'p')
        return piece_creer(0,J0);
	if (c == 'P')
        return piece_creer(0,J1);
	if (c == 'd')
        return piece_creer(1,J0);
	if (c == 'D')
        return piece_creer(1,J1);
}

char piece_caractere(piece* p)
{
	if (p->promu == 0 && p->joueur == J0)
		return 'p';
	else if (p->promu == 0 && p->joueur == J1)
		return 'P';
	else if (p->promu == 1 && p->joueur == J0)
		return 'd';
	else return 'D';
}

void piece_afficher(piece* p)
{
	printf("%c", piece_caractere(p));
}

