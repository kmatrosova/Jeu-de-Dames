#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "partie.h"


void decalage(){
	printf("		");
}
void decalage_num(int j){
	printf("	       %d", j);
}
void afficher_plateau(char damier[DIM][DIM]){
	int i,j;
	decalage();
	for(j=0;j<DIM;j++)
        printf("  %d ", j);
    printf("\n");
	for(j=0;j<DIM;j++){
		decalage();
		for(i=0;i<DIM;i++){
			if(i!=9)
				printf("+---");
			else
				printf("+---+");
		}

		printf("\n");
		decalage_num(j);
		for(i=0;i<DIM;i++){
			if(i!=9)
				printf("| %c ", damier[j][i]);

			else
				printf("| %c |", damier[j][i]);
		}
		if(j==1){
			decalage();
			printf("JOUEUR 0");
		}
		if(j==8){
			decalage();
			printf("JOUEUR 1");
		}
		printf("\n");
	}
	decalage();
	for(i=0;i<DIM;i++){
        if(i!=9)
            printf("+---");
        else
            printf("+---+");
    }
    printf("\n");
}
//alloure mémoire partie et initialise les coups joués
partie* partie_creer()
{
	partie* p = malloc(sizeof(partie));
	p->joueur=J0;
	p->LM=initialise_liste_mvmt();
	p->LC=creer_liste_conf();
	return p;
}


//teste si une case du plateau est vide
int case_vide(partie *p, coord c)
{
	if(c.ligne>=DIM || c.ligne<0 || c.colonne>=DIM || c.colonne<0) return -1;
	char e = p->damier[c.ligne][c.colonne];
	if(e =='.')
		return 1;

	return 0;
}

//changer le joueur qui a le trait
void changer_joueur(partie *p)
{
	if(p->joueur==J0)
		p->joueur=J1;
	else
		p->joueur=J0;
}

//modifie une case du damier de la partie p
void modifier_case(partie *P, piece *p, coord c)
{
	char e = piece_caractere(p);
	P->damier[c.ligne][c.colonne]=e;
}

//modifie le damier, supprime piece captures; ajoute coup a la liste
void modif_damier(partie *p, mouvement *m)
{
	configuration* conf=NULL;

	coord case_dep=creer_coord(m->positions[0].ligne,m->positions[0].colonne);
	coord case_arr=creer_coord(m->positions[m->nb_positions-1].ligne,m->positions[m->nb_positions-1].colonne);
	piece *pce = piece_identifier(p->damier[case_dep.ligne][case_dep.colonne]);

	pieces_capture *pc=m->PC;
	while(pc!=NULL){
		p->damier[pc->c.ligne][pc->c.colonne]='.';
		pc=pc->suivant;
	}
	modifier_case(p,pce,case_arr);


	p->damier[case_dep.ligne][case_dep.colonne]='.';
	if(p->joueur==J0 && case_arr.ligne==9){
		p->damier[case_arr.ligne][case_arr.colonne]='d';
		m->promotion=1;
	}

	if(p->joueur==J1 && case_arr.ligne==0){
		p->damier[case_arr.ligne][case_arr.colonne]='D';
		m->promotion=1;
	}

	ajouter_mvmt(p->LM,m);


	conf=creer_conf(p->damier);
	ajouter_conf(p->LC, conf);
}

void partie_sauvegarder(partie *p, char *chemin)
{
	FILE* f = fopen(chemin, "w+");
	int i,j;

	fprintf(f, "PL\n");
	for(i = 0; i < DIM ; i++)
	{
		for(j = 0; j < DIM; j++)
			fprintf(f, "%c", p->damier[i][j]);
		fprintf(f,"\n");
	}

	fclose(f);
}

partie* partie_nouvelle()
{
	partie *p = partie_charger("damier");

	return p;
}



int piece_adversaire(partie* p, coord c)
{
	if(c.ligne>=DIM || c.ligne<0 || c.colonne>=DIM || c.colonne<0) return -1;
	if(case_vide(p,c)==1){
		return -1;
	}
	if(p->joueur == J0)
	{
		if(piece_joueur(piece_identifier(p->damier[c.ligne][c.colonne])) == J1)
			return 1;
		else return 0;
	}
	else
	{
		if(piece_joueur(piece_identifier(p->damier[c.ligne][c.colonne])) == J0)
			return 1;
		else return 0;
	}
}

coord saisie_case(){
	char ligne[10],colonne[10];
	int i=0,j=0,l,c;
	do
	{
		printf("Saisie de la case : ");
		scanf("%s %s", ligne, colonne);
		for(i=0;ligne[i]!='\n'&&ligne[i]!='\0';i++)
			if(((int)ligne[i]<48||(int)ligne[i]>57)&&ligne[i]!=' '){
				printf("Saisie non correcte\n");
				j=-1;
				break;
			}
		for(i=0;colonne[i]!='\n'&&colonne[i]!='\0';i++)
			if(((int)colonne[i]<48||(int)colonne[i]>57)&&colonne[i]!=' '){
				printf("Saisie non correcte\n");
				j=-1;
				break;
			}
		if(j!=-1){
			l=atoi(ligne);
			c=atoi(colonne);
			if(!(c>10||l>10||c<0||l<0)){
                if(c==10||l==10)
                    return creer_coord(10,10);

                return creer_coord(l,c);
			}
		}
		j=0;
	}while(1);
}

void annuler_mouvement(partie *p)
{
	int i, j;

	changer_joueur(p);

	supprimer_mvmt(p->LM);
	supprimer_conf(p->LC);



	for(i=0; i<DIM; i++)
	{
		for(j=0; j<DIM; j++)
		{

			p->damier[i][j] = p->LC->fin->damier[i][j];
		}

	}
	afficher_plateau(p->damier);
}


int partie_options(partie *p){
    char choix[3], on;
    char chemin[50];
    int c;
    printf("1-Sauvegarder\n2-Annuler mouvement\n3-Quitter\n4-Revenir\n");
    do
    {
        scanf("%s",choix);
        c=atoi(choix);
    }while(c<0||c>4);
    if(c==1){
        printf("Chemin du fichier: ");
        scanf("%s",chemin);
        partie_sauvegarder(p,chemin);
    }
    else if(c==2){
        if(liste_mvmt_vide(p->LM))
            printf("Aucun mouvement effectue\n");
        else
            annuler_mouvement(p);
    }
    else if(c==3){
        printf("Voulez vous sauvegarder la partie ? (o/n) ");
        do{
            scanf("%c",&on);
        }while(on!='o'&&on!='n');
        if(on=='o'){
            printf("Chemin du fichier: ");
            scanf("%s",chemin);
            partie_sauvegarder(p,chemin);
        }
        return 0;
    }
    return 1;

}


pieces_capture* capturer(partie* p, coord dep, coord arr)
{
	int i,j;
	pieces_capture* pc = NULL;

	if(arr.ligne>dep.ligne && arr.colonne>dep.colonne){

		for(i=dep.ligne+1, j=dep.colonne+1; i<arr.ligne && j<arr.colonne; i++, j++)
		{
			if(!case_vide(p,creer_coord(i,j)))
				pc = creer_PC(piece_identifier(p->damier[i][j]), creer_coord(i,j));
		}
	}
	if(arr.ligne<dep.ligne && arr.colonne<dep.colonne){
		for(i=dep.ligne-1, j=dep.colonne-1; i>arr.ligne && j>arr.colonne; i--, j--)
		{
			if(!case_vide(p,creer_coord(i,j)))
				pc = creer_PC(piece_identifier(p->damier[i][j]), creer_coord(i,j));
		}
	}
	if(arr.ligne<dep.ligne && arr.colonne>dep.colonne){
		for(i=dep.ligne-1, j=dep.colonne+1; i>arr.ligne && j<arr.colonne; i--, j++)
		{
			if(!case_vide(p,creer_coord(i,j)))
				pc = creer_PC(piece_identifier(p->damier[i][j]), creer_coord(i,j));
		}
	}
	if(arr.ligne>dep.ligne && arr.colonne<dep.colonne){
		for(i=dep.ligne+1, j=dep.colonne-1; i<arr.ligne && j>arr.colonne; i++, j--)
		{
			if(!case_vide(p,creer_coord(i,j)))
				pc = creer_PC(piece_identifier(p->damier[i][j]), creer_coord(i,j));
		}
	}
	return pc;

}
void ajouter_nouvelle_position(coord *position, coord c, int size){
	realloc(position, sizeof(coord));
	position[size-1]=c;
}
int fin_du_jeu(partie *p){
    int i,j,JR0=0,JR1=0;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(p->damier[i][j]!=' ' && p->damier[i][j]!='.'){
                if(piece_joueur(piece_identifier(p->damier[i][j]))==J0)
                    JR0++;
                else
                    JR1++;
            if(JR0>0&&JR1>0)
                return 0;
            }
        }
    }

    if(JR0==0)
        printf("****LE JOUEUR 1 A GAGNE !****\n");
    else
        printf("****LE JOUEUR 0 A GAGNE !****\n");
    return 1;
}
void option_sauvegarder_partie(partie *p)
{
     char sauv[51];

     printf("\nNom du fichier de sauvegarde (50 caracteres max): ");
     scanf("%s", sauv);
     partie_sauvegarder(p, sauv);
}

partie* partie_charger(char *chemin)
{
    FILE* f = fopen(chemin, "r");
    if(f==NULL){
        printf("Fichier introuvable!\n");
        return NULL;
    }
    char ligne[15];
	int i=0,j=0;

	fgets(ligne, sizeof(ligne), f);
	if(strcmp(ligne,"PL\n")!=0){
        printf("Format fichier invalide!\n");
        return NULL;
	}

	partie* p = partie_creer();

	while (fgets(ligne, sizeof(ligne), f)){
		for(i = 0; ligne[i]!='\0'&&ligne[i]!='\n' ; i++)
		{
			p->damier[j][i]=ligne[i];
		}
		j++;
	}
	fclose(f);

	ajouter_conf(p->LC, creer_conf(p->damier));


	return p;
}

partie* option_main_chargement_partie(partie *p)
{
    char chargement[51];

    printf("\nNom du fichier de chargement:\n");
    scanf("%s", chargement);

    p=partie_charger(chargement);

    return p;
}

void enregistrer_config(partie* p, char* chemin)
{
	FILE* f = fopen(chemin, "a");
	int i,j;

	int size;
	if (NULL != f) {
    		fseek (f, 0, SEEK_END);
    		size = ftell(f);

	    	if (0 == size) {
			fprintf(f,"PR\n");
		    }
	}

	for(i = 0; i < DIM ; i++)
	{
		for(j = 0; j < DIM; j++)
			fprintf(f, "%c", p->LC->fin->damier[i][j]);
		fprintf(f,"\n");
	}

	fclose(f);
}

void replay()
{
	char damier[DIM][DIM];
	FILE* f = fopen("replay", "r");
	char ligne[15];
	char PR[3]="PR";
	int i=0,j=0;

	fgets(ligne, sizeof(ligne), f);
	while(ligne[i]!='\0' && ligne[i]!='\n') i++;
	ligne[i]='\0';
	if(!strcmp(ligne, PR))
	{
		while (fgets(ligne, sizeof(ligne), f)){
			for(i = 0; ligne[i]!='\0'&&ligne[i]!='\n' ; i++)
			{
				damier[j][i]=ligne[i];
			}
			j++;
			if(j%10==0)
			{
				afficher_plateau(damier);
				j=0;
				//sleep(1);
			}
		}
		fclose(f);

	}
	else printf("\nFormat fichier inconnu: chargement impossible\n");
}
void partie_detruire(partie *p){
	while(p->LM->debut!=NULL)
		supprimer_mvmt(p->LM);

	while(p->LC->debut!=NULL)
		supprimer_conf(p->LC);

	free(p);
}
