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
	piece* p = malloc(sizeof(piece));

	if (c == 'p')
	{
		p->promu = 0;
		p->joueur = 0;
	}
	if (c == 'P')
	{
		p->promu = 0;
		p->joueur = 1;
	}
	if (c == 'd')
	{
		p->promu = 1;
		p->joueur = 0;
	}
	if (c == 'D')
	{
		p->promu = 1;
		p->joueur = 1;
	}
	
	return p;
}

char piece_caractere(piece* p)
{
	if (p->promu == 0 && p->joueur == 0)
		return 'p';
	else if (p->promu == 0 && p->joueur == 1)
		return 'P';
	else if (p->promu == 1 && p->joueur == 0)
		return 'd';
	else return 'D';
}

void piece_afficher(piece* p)
{
	printf("%c", piece_caractere(p));
}

