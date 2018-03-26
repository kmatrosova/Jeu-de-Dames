#ifndef PARTIE_H
#define PARTIE_H

#include "piece.h"

#define J1 1
#define J0 0


typedef struct partie_s{
    char damier[DIM][DIM];
    int joueur;
    liste_mouvement * LM;
    liste_configuration * LC;
}partie;

int case_vide(partie *p, coord c); //teste si une case du plateau est vide
void changer_joueur(partie *p)//changer le joueur qui a le trait

void modifier_case(partie *P, piece *p, coord c);//modifie une case du damier de la partie p
void modif_damier(partie *p, mouvement m);//modifie le damier, supprime piece captures; ajoute coup a la liste

void annuler_mouvement(partie *p);
coord saisie_case();

partie* partie_creer();//alloure mémoire partie et initialise les coups joués
void partie_detruire(partie *p);//libère l'espace mémoire qu'occupe une partie
partie* partie_nouvelle();//renvoie pointeur sur une partie initialisée
void partie_jouer(partie *p);

void partie_sauvegarder(partie *p, char *chemin);
partie* partie_charger(char *chemin);

void replay_jouer(partie *p)// prend une partie et la rejoue


#endif
