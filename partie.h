#ifndef PARTIE_H
#define PARTIE_H

#include "coup_joues.h"
#include "configuration_damier.h"


#define J1 1
#define J0 0


typedef struct partie_s{
    char damier[DIM][DIM];
    int joueur;
    liste_mouvement * LM;
    liste_configuration * LC;
}partie;


void afficher_plateau(char damier[DIM][DIM]);
int case_vide(partie *p, coord c); //teste si une case du plateau est vide
void changer_joueur(partie *p);//changer le joueur qui a le trait

void modifier_case(partie *P, piece *p, coord c);//modifie une case du damier de la partie p
void modif_damier(partie *p, mouvement *m);//modifie le damier, supprime piece captures; ajoute coup a la liste

void annuler_mouvement(partie *p);
coord saisie_case();
int partie_options(partie *p);
partie* partie_creer();//alloure mémoire partie et initialise les coups joués
void partie_detruire(partie *p);//libère l'espace mémoire qu'occupe une partie
partie* partie_nouvelle();//renvoie pointeur sur une partie initialisée
//int partie_jouer(partie *p);

void partie_sauvegarder(partie *p, char *chemin);
partie* partie_charger(char *chemin);

void replay_jouer(partie *p);// prend une partie et la rejoue
void ajouter_nouvelle_position(coord *position, coord c, int size);
int piece_adversaire(partie* p, coord c);
int fin_du_jeu(partie *p);
pieces_capture* capturer(partie* p, coord dep, coord arr);
int verifier_fichier(char* chemin);
partie* option_main_chargement_partie(partie *p);
void option_sauvegarder_partie(partie *p);
void enregistrer_config(partie* p, char* chemin);
void replay();

#endif
