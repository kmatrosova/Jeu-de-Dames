#include <stdio.h>
#include <stdlib.h>

#include "coup_joues.h"

coord creer_coord(int ligne, int colonne){
	coord c;
	c.ligne=ligne;
	c.colonne=colonne;
	return c;
}

pieces_capture* creer_PC(piece *p, coord c)
{
	pieces_capture* PC = malloc(sizeof(pieces_capture));
	PC->p.promu = p->promu;
	PC->p.joueur = piece_joueur(p);
	PC->c.ligne = c.ligne;
	PC->c.colonne = c.colonne;
	PC->suivant = NULL;

	return PC;
}

void ajouter_piece(mouvement* m, pieces_capture *PC)
{
	pieces_capture *newpc=m->PC;
	if(newpc==NULL){
		m->PC=PC;
		return;
	}
	else{
		while(newpc->suivant!=NULL)
			newpc=newpc->suivant;
		newpc->suivant=PC;
	}
}

mouvement* creer_mouvement(coord* positions, int nb_pos){
	mouvement *m=malloc(sizeof(mouvement));
	m->PC=NULL;
	m->suiv=NULL;
	m->prec=NULL;
	m->positions=positions;
	m->nb_positions=nb_pos;
	m->promotion=0;
	return m;
}
liste_mouvement* initialise_liste_mvmt(){
	liste_mouvement* lm=malloc(sizeof(liste_mouvement));
	lm->debut=NULL;
	lm->fin=NULL;
	lm->taille=0;
	return lm;
}
int liste_mvmt_vide(liste_mouvement *lm)
{
    return(!lm->taille)?1:0;
}

void ajouter_mvmt(liste_mouvement* lm, mouvement* m){
	if(liste_mvmt_vide(lm))
		lm->debut=m;
	else{

        m->prec=lm->fin;
		lm->fin->suiv=m;
	}
	lm->fin=m;

	lm->taille++;
}
void supprimer_mvmt(liste_mouvement* lm){
	if(liste_mvmt_vide(lm))
		return;
	mouvement* m=lm->fin;
	lm->fin=m->prec;
	free(m->positions);
	free(m);
	lm->taille--;
	if(lm->taille==0){
		lm->debut=NULL;
		lm->fin=NULL;
	}
}









