#include <stdio.h>
#include <stdlib.h>
#include "configuration_damier.h"


int main()
{
	creer_liste_conf();

	return EXIT_SUCCESS;
}


configuration* conf_init()
{
	int i, j;
	configuration* c = malloc(sizeof(configuration));
	c->suiv = malloc(sizeof(configuration));
	c->suiv = malloc(sizeof(configuration));
	
	for(i = 0; i<4; i++)
	{
		if(i == 0 || i == 2)
		{
			for(j = 1; j<DIM; j=j+2)
				c->damier[i][j] = 'p';
		}
		else
		{
			for(j = 0; j<DIM; j=j+2)
				c->damier[i][j] = 'p';
		}		
	}
	
	for(i = 6; i<DIM; i++)
	{
		if(i == 6 || i == 8)
		{
			for(j = 1; j<DIM; j=j+2)
				c->damier[i][j] = 'P';
		}
		else
		{
			for(j = 0; j<DIM; j=j+2)
				c->damier[i][j] = 'P';
		}	
		
		
	}
	
	for(i=0; i<DIM; i++)
	{
		for(j=0; j<DIM; j++)
		{
			if(c->damier[i][j] != 'p' && c->damier[i][j] != 'P')
				c->damier[i][j] = '.';
		}
	}	
	
	for(i=0; i<DIM; i++)
	{
		for(j=0; j<DIM; j++)
			printf("%c", c->damier[i][j]);
		printf("\n");
	}	
	return c;	
}
/*
configuration* creer_conf(configuration* c, coord* dep, coord* arr)
{
	c->damier[][] = c->damier[dep->ligne][dep->colonne]
	
	
}
*/


liste_configuration* creer_liste_conf()
{
	liste_configuration* l = malloc(sizeof(liste_configuration));
	
	l->debut = malloc(sizeof(liste_configuration));
	l->fin = malloc(sizeof(liste_configuration));
	l->taille = 0;
	l->debut = conf_init();
	
	return l;
}
void ajouter_conf(liste_configuration* l, configuration* c)
{
	
}
void supprimer_conf();

