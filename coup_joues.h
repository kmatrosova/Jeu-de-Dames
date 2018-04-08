#ifndef COUPS_JOUES_H
#define COUPS_JOUES_H
#include "piece.h"

#define DIM 10

typedef struct coordonnee_s{
	int ligne;
	int colonne;
}coord;
typedef struct pieces_capture_s{
	piece p;
	coord c;
	struct pieces_capture_s *suivant;
}pieces_capture;

typedef struct mouvement_s{
	int promotion;
	pieces_capture* PC;
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
pieces_capture* creer_PC(piece *p, coord c);
void ajouter_piece(mouvement* m, pieces_capture *PC);

mouvement* creer_mouvement(coord* positions, int nb_pos);
liste_mouvement* initialise_liste_mvmt();
int liste_mvmt_vide(liste_mouvement *lm);

void ajouter_mvmt(liste_mouvement* lm, mouvement* m);
void supprimer_mvmt(liste_mouvement* lm);



#endif
