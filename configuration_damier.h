#ifndef CONF_DAM_H
#define CONF_DAM_H

#define DIM 10

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


configuration* creer_conf(char damier[DIM][DIM]);
liste_configuration* creer_liste_conf();
int liste_conf_vide(liste_configuration *lc);

void ajouter_conf(liste_configuration* lc, configuration* c);
void supprimer_conf(liste_configuration* lc);


#endif
