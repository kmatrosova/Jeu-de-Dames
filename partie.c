#include <stdio.h>
#include <stdlib.h>

#include "partie.h"


//teste si une case du plateau est vide
int case_vide(partie *p, coord c){
	char c = p->damier[c.ligne][c.colonne];
	if(c=="." || c==" ")
		return 1;
	
	return 0;
}

//changer le joueur qui a le trait
void changer_joueur(partie *p){
	if(p->joueur==J0)
		p->joueur=J1;
	else
		p->joueur=J0;
}

//modifie une case du damier de la partie p
void modifier_case(partie *P, piece *p, coord c){
	c=piece_caractere(p);
	P->damier[c.ligne][c.colonne]=c;
}

//modifie le damier, supprime piece captures; ajoute coup a la liste
void modif_damier(partie *p, mouvement m){


}
