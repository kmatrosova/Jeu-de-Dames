#ifndef PARTIE_JOUER_H
#define PARTIE_JOUER_H

#include "deplacement.h"


int partie_jouer(partie *p, int IA);

void aff_mvmt(mouvement*m);
void aff_pc(pieces_capture*pc);
void aff(partie *p);

coord pieceCap(partie* p, coord dep, coord arr);
int deplacement(partie* p, coord dep, coord arr, int n);
void annuler_deplacement(partie *p, int n);
void IA_jouer_intermediaire(partie *p, coord *d, int profondeur, coord *maxd, coord *maxf, int n);
void IA_jouer(partie *p, coord *c, int profondeur);
int eval(partie *p);
int Min(partie *p,int profondeur);
int Max(partie *p,int profondeur);

#endif
