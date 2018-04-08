#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "partie.h"


int deplacement_valide(partie* p, coord dep, coord arr, int IA);
int deplacement_valide_pion(partie* p, coord dep, coord arr);
int deplacement_valide_dame(partie* p, coord dep, coord arr);
int deplacement_pion_2cases(partie* p, coord dep, coord arr);
int verifier_pion_peut_manger(partie* p, coord c);
int verifier_dame_peut_manger(partie* p, coord c);
int verifier_piece_peut_manger(partie* p, coord c);
int verifier_peut_manger(partie* p);

#endif
