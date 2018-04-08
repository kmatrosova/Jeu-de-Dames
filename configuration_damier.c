#include <stdio.h>
#include <stdlib.h>
#include "configuration_damier.h"



configuration* creer_conf(char damier[DIM][DIM]){
	int i,j;
	configuration* newc = malloc(sizeof(configuration));
	newc->suiv=NULL;
	newc->prec=NULL;
	for(i=0;i<DIM;i++){
		for(j=0;j<DIM;j++){
			newc->damier[i][j]=damier[i][j];
		}
	}

	return newc;
}

int liste_conf_vide(liste_configuration *lc){
    return(!lc->taille)?1:0;
}

liste_configuration* creer_liste_conf(){
	liste_configuration* lc = malloc(sizeof(liste_configuration));
	lc->debut=NULL;
	lc->fin=NULL;
	lc->taille = 0;
	return lc;
}
void ajouter_conf(liste_configuration* lc, configuration* c){
	if(liste_conf_vide(lc))
		lc->debut=c;
	else
		lc->fin->suiv=c;

	c->prec=lc->fin;
	lc->fin=c;
	lc->taille++;
}
void supprimer_conf(liste_configuration* lc){
	if(liste_conf_vide(lc))
		return;
	configuration* c=lc->fin;
	lc->fin=c->prec;
	free(c);
	lc->taille--;
	if(lc->taille==0){
		lc->debut=NULL;
		lc->fin=NULL;
	}
}


