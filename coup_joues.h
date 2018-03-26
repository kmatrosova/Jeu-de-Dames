#ifndef COUPS_JOUES_H
#define COUPS_JOUES_H

#define DIM 10

typedef struct coordonnee_s{
	int ligne;
	int colonne;
}coord;

typedef struct mouvement_s{
	int promotion;
	int capture;
	struct mouvement_s * suiv;
	struct mouvement_s * prec;
	coord * positions;
	int nb_positions;
}mouvement;

typedef struct liste_mouvement_s{
	int taille;
	mouvement * debut;
	mouvement * fin;
}liste_mouvement;

coord creer_coord(int ligne, int colonne);


mouvement* creer_mouvement(coord* positions, int nb_pos);
liste_mouvement* initialise_liste_mvmt();
int liste_vide(liste_mouvement *lm);

void ajouter_mvmt_fin(liste_mouvement* lm, mouvement* m);
void supprimer_mvmt_fin(liste_mouvement* lm);



#endif
