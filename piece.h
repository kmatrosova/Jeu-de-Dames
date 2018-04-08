#ifndef PIECE_H
#define PIECE_H

#define J0 0
#define J1 1

typedef struct piece_s{
    int promu;
    int joueur;
}piece;

piece* piece_creer(int statut, int joueur);//crée une pièce
int piece_joueur(piece* p); //prend en argument une piece et renvoie son joueur
piece* piece_identifier(char c);//prend en argument un caractere et renvoie la piece correspondante
char piece_caractere(piece* p);//prend en argument une piece et renvoie le caractere qui lui est associé
void piece_afficher(piece* p);//prend en argument une piece et affiche le caractere qui lui est associé




#endif // PIECE
