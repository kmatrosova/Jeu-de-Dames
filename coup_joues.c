#include <stdio.h>
#include <stdlib.h>

#include "coup_joues.h"

coord creer_coord(int ligne, int colonne){
	coord c;
	c.ligne=ligne;
	c.colonne=colonne;
	return c;
}

mouvement* creer_mouvement(coord* positions, int nb_pos){
	mouvment *m=malloc(sizeof(mouvement));
	m->suiv=NULL;
	m->prec=NULL;
	m->positions=positions;
	m->nb_positions=nb_pos;
	return m;
}

liste_mouvement* initialise_liste_mvmt(){
	liste_mouvement* lm=malloc(sizeof(liste_mouvement));
	lm->debut=NULL;
	lm->fin=NULL;
	lm->taille=0;
	return lm;
}
int liste_vide(liste_mouvement *lm)
{
    return(!lm->taille)?1:0;
}

void ajouter_mvmt_fin(liste_mouvement* lm, mouvement* m){
	if(liste_vide(lm))
		lm->debut=lm->fin;
	else
		lm->fin->suivant=m;

	m->prec=lm->fin;
	lm->fin=m;
	lm->taille++;
}
void supprimer_mvmt_fin(liste_mouvement* lm){
	mouvement* m=lm->fin;
	lm->fin=m->prec;
	free(m->positions);
	free(m);
	lm->taille--;
}









