#ifndef CONF_DAM_H
#define CONF_DAM_H
#define DIM 10

typedef struct coordonnee_s{
	int ligne;
	int colonne;
}coord;

typedef struct configuration_s{
	char damier[DIM][DIM];
	struct configuration_s * suiv;
	struct configuration_s * prec;
}configuration;

typedef struct liste_configuration_s{
	int taille;
	configuration * debut;
	configuration * fin;
}liste_configuration;

configuration* conf_init();
configuration* creer_conf();

liste_configuration* creer_liste_conf();
void ajouter_conf();
void supprimer_conf();

#endif
