#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "partie_jouer.h"

int partie_jouer(partie *p, int IA)
{
	coord c1, c2;
	int d, i, autre_coup=1;
	mouvement* m = NULL;
	coord* positions = NULL;
	pieces_capture *pc=NULL;

	int nb_pos=0;/*
	if(IA && P->joueur==J0){
		IA_jouer(p)
	}*/
	do
	{
	    printf("JOUEUR %d \n",p->joueur);
	    afficher_plateau(p->damier);
            positions = malloc(sizeof(coord)*2);

        printf("DEPART\n");
        if(p->joueur == J0 && IA)
        {

        	    IA_jouer(p, NULL, 5);
		    changer_joueur(p);
        }
	else
	{
	        do
		{
		    printf("DEPART (MENU OPTIONS: 10)\n");
		    c1=saisie_case();
		    if(c1.ligne==10)
		        if(!partie_options(p)){
		            partie_detruire(p);
		            return 1;
		        }
		}while(c1.ligne==10||c1.colonne==10);

			printf("ARRIVEE\n");
		do
		{
		    c2=saisie_case();
		}while(c2.ligne==10);
		d = deplacement_valide(p, c1, c2, 0);
		nb_pos = 2;

		if(d == 0){
			printf("DEPLACEMENT INVALIDE\n");
			free(positions);
		}
		else
		{
			positions[0] = c1;
			positions[1] = c2;
			m = creer_mouvement(positions, nb_pos);

			if(d == 2)
			{
				do
		        	{
					pc=capturer(p, c1, c2);
					ajouter_piece(m, pc);
					modifier_case(p, piece_identifier(p->damier[c1.ligne][c1.colonne]), c2); //modifie case d'arrivee
		            		p->damier[pc->c.ligne][pc->c.colonne]='.';                               //modifie case piece capturee
					p->damier[c1.ligne][c1.colonne]='.';                                     //modifie case de depart

					if(verifier_piece_peut_manger(p, c2))
					{
		                		c1=c2;
						do
						{
						    afficher_plateau(p->damier);
						    printf("CASE INTERMEDIAIRE\n");
						    c2=saisie_case();
						}while(c2.ligne==10||deplacement_valide(p,c1,c2,0)!=2);

						nb_pos++;
						ajouter_nouvelle_position(m->positions,c2,nb_pos);
					}
					else{
						autre_coup=0;
						m->nb_positions=nb_pos;
						p->damier[m->positions[0].ligne][m->positions[0].colonne]=p->damier[c2.ligne][c2.colonne];
						for(i=1;i<nb_pos;i++)
							p->damier[m->positions[i].ligne][m->positions[i].colonne]='.';
					}

				}while(autre_coup);
				autre_coup=1;

			}

		    modif_damier(p, m);

		    changer_joueur(p);

		    enregistrer_config(p, "replay");

		    aff(p);

		    positions = NULL;
		    m = NULL;

			}
	    }
	    
	    if(fin_du_jeu(p)){
	    	afficher_plateau(p->damier);

            partie_detruire(p);


	    	return 1;
	    }
	}while(1);
}

void aff(partie *p){
    aff_mvmt(p->LM->debut);
    printf("taille conf:%d\n",p->LC->taille);

}

void aff_pc(pieces_capture*pc){
    while(pc!=NULL){
        printf("PC l:%d c:%d\n",pc->c.ligne,pc->c.colonne);
        pc=pc->suivant;
    }

}
void aff_mvmt(mouvement*m){
    int i;
    while(m!=NULL){
        for(i=0;i<m->nb_positions;i++)
            printf("MVMT l:%d c:%d\n",m->positions[i].ligne,m->positions[i].colonne);
        aff_pc(m->PC);
        m=m->suiv;
        printf("\n\n\n");
    }

}


coord pieceCap(partie* p, coord dep, coord arr)
{
	int i,j;
	coord pc;

	if(arr.ligne>dep.ligne && arr.colonne>dep.colonne){

		for(i=dep.ligne+1, j=dep.colonne+1; i<arr.ligne && j<arr.colonne; i++, j++)
		{
			if(!case_vide(p,creer_coord(i,j)))
				pc = creer_coord(i,j);
		}
	}
	if(arr.ligne<dep.ligne && arr.colonne<dep.colonne){
		for(i=dep.ligne-1, j=dep.colonne-1; i>arr.ligne && j>arr.colonne; i--, j--)
		{
			if(!case_vide(p,creer_coord(i,j)))
				pc = creer_coord(i,j);
		}
	}
	if(arr.ligne<dep.ligne && arr.colonne>dep.colonne){
		for(i=dep.ligne-1, j=dep.colonne+1; i>arr.ligne && j<arr.colonne; i--, j++)
		{
			if(!case_vide(p,creer_coord(i,j)))
				pc = creer_coord(i,j);
		}
	}
	if(arr.ligne>dep.ligne && arr.colonne<dep.colonne){
		for(i=dep.ligne+1, j=dep.colonne-1; i<arr.ligne && j>arr.colonne; i++, j--)
		{
			if(!case_vide(p,creer_coord(i,j)))
				pc = creer_coord(i,j);
		}
	}
	return pc;

}

int deplacement(partie* p, coord dep, coord arr, int n)
{
	int i, j;
	
	
	if(deplacement_valide(p, dep, arr, 1) == 2)
	{
		coord pc = pieceCap(p, dep, arr);
		p->damier[arr.ligne][arr.colonne] = p->damier[dep.ligne][dep.colonne];
		p->damier[dep.ligne][dep.colonne] = '.';
		p->damier[pc.ligne][pc.colonne] = '.';
		
		for(i=0; i<DIM; i++)
		{
			for(j=0; j<DIM; j++)
			{
				if(deplacement_valide(p,arr,creer_coord(i,j), 1) == 2)
					return deplacement(p, arr, creer_coord(i,j), n++);
			}
		}
		ajouter_conf(p->LC, creer_conf(p->damier));
	}
	else if(deplacement_valide(p, dep, arr, 1) == 1)
	{
		p->damier[arr.ligne][arr.colonne] = p->damier[dep.ligne][dep.colonne];
		p->damier[dep.ligne][dep.colonne] = '.';
		ajouter_conf(p->LC, creer_conf(p->damier));
	}
	return n++;	
}

void annuler_deplacement(partie *p, int n)
{
	int i, j;
	if(n>1)
		changer_joueur(p);
	for(i=0; i<n; i++)
		supprimer_conf(p->LC);
	for(i=0; i<DIM; i++)
	{
		for(j=0; j<DIM; j++)
			p->damier[i][j] = p->LC->fin->damier[i][j];	
	}
}

void IA_jouer(partie *p, coord *c, int profondeur)
{
     int i1,j1,i2,j2,tmp;
     coord d, f, maxd, maxf;
     int max=-10000;
     int n=1, m=1;

      if(c == NULL)
      {
	      for(i1=0;i1<DIM;i1++)
	      {
		  d.ligne=i1;
		  for(j1=0;j1<DIM;j1++)
		  {

		     d.colonne=j1;
		     if(case_vide(p, creer_coord(i1,j1))==0 && p->damier[i1][j1] !=' ' && piece_joueur(piece_identifier(p->damier[i1][j1]))==J0)
		     {
		       for(i2=0;i2<DIM;i2++)
		       {
		          f.ligne=i2;
		          for(j2=0;j2<DIM;j2++)
		          {

		              f.colonne=j2;
		              if(deplacement_valide(p,d,f,1) != 0)
		              {
		                  n = deplacement(p,d,f,1);
		                  if(n>=m)
		                  {
		                  	  m=n;
				          changer_joueur(p);
				          tmp = Min(p,profondeur-1);
				          changer_joueur(p);
		                  }
				  annuler_deplacement(p, n);
				  
		                 
				if(tmp>max)
				{
					max=tmp;
					maxd=d;
					maxf=f;	
				}
			     }
		          }

		      }

		    }
		 }
	    }
    }
    else
    {
    	for(i2=0;i2<DIM;i2++)
        {
          f.ligne=i2;
          for(j2=0;j2<DIM;j2++)
          {

              f.colonne=j2;
              if(deplacement_valide(p,*c,f,1) == 2)
              {
                  n = deplacement(p,*c,f,1);
                   if(n>=m)
		   {
		   	m=n;
			changer_joueur(p);
			tmp = Min(p,profondeur-1);
			changer_joueur(p);
		   }
		  annuler_deplacement(p, n);
                 
		if(tmp>max)
		{
			max=tmp;
			maxd=*c;
			maxf=f;	
		}
	     }
          }

      }
		      
    }
    if(deplacement_valide(p, maxd, maxf, 1) == 2)
    {
    	n = deplacement(p,maxd,maxf, 1);
    	annuler_deplacement(p, n-1);
    	if(verifier_piece_peut_manger(p, maxf))
	{
	    printf("je suis al\n");
	    IA_jouer(p, &maxf, profondeur);	
	}
    }
    else
    {
    	n = deplacement(p,maxd,maxf, 1);
    	annuler_deplacement(p, n-1);
    }
    printf("maxd : %d %d\n maxf: %d %d\n", maxd.ligne, maxd.colonne, maxf.ligne, maxf.colonne);	
    
}
/*
void IA_jouer_intermediaire(partie *p, coord *d, int profondeur, coord *maxd, coord *maxf, int n)
{
	int i,j,tmp;
	coord f;
	int max=-10000;
	
	for(i=0;i<DIM;i++)
	{
		f.ligne=i;
		for(j=0;j<DIM;j++)
		{

			f.colonne=j;
			if(deplacement_valide(p,d,f) != 0)
			{		              	  
				n = deplacement(p,d,f,1);
				changer_joueur(p);
				tmp = Min(p,profondeur-1);
				changer_joueur(p);
				annuler_deplacement(p, n);
			 
			if(tmp>max)
			{
				max=tmp;
				maxd=d;
				maxf=f;	
			}
			}
		}

	}
}

*/

int eval(partie *p){
	int score=0;
	int i, j;
	int joueur=p->joueur;
	//printf("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc\n");
	
	p->joueur=J0;
	if(fin_du_jeu(p))
	{
		p->joueur=joueur;
		return 10000;
	}
	
	p->joueur=J1;
	if(fin_du_jeu(p))
	{
		p->joueur=joueur;
		return -10000;
	}
	p->joueur=joueur;
	for(i=0;i<DIM;i++)
	{
		for(j=0;j<DIM;j++)
		{
			if(case_vide(p, creer_coord(i,j))==0 && p->damier[i][j] !=' ')
			{
				if(piece_joueur(piece_identifier(p->damier[i][j]))==J0)
				{
					if(piece_identifier(p->damier[i][j])->promu == 0)
						score++;
					else score+=10;
				}
				else
				{
					if(piece_identifier(p->damier[i][j])->promu == 0)
						score--;
					else score-=10;
				}
			}
		}
	}
	return score;
}

int Min(partie *p, int profondeur)
{
     if(profondeur == 0){
     	//printf("profondeur = 0 dans Min\n");
     	return eval(p);
     }

     //printf("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc\n");	  
     int i1,j1,i2,j2, tmp, min=10000;
     coord d, f;
     int n=1, m=1;

     for(i1=0;i1<DIM;i1++)
     {
          d.ligne=i1;
          for(j1=0;j1<DIM;j1++)
          {
             d.colonne=j1;
             if(case_vide(p, creer_coord(i1,j1))==0 && p->damier[i1][j1] !=' ' && piece_joueur(piece_identifier(p->damier[i1][j1]))==J1)
             {
               for(i2=0;i2<DIM;i2++)
               {
                  f.ligne=i2;
                  for(j2=0;j2<DIM;j2++)
                  {
                      f.colonne=j2;
                      if(deplacement_valide(p,d,f,1) != 0)
                      {
                      	  
                          n = deplacement(p,d,f,1);
                          if(n>=m)
			   {
			   	m=n;
				changer_joueur(p);
				tmp = Min(p,profondeur-1);
				changer_joueur(p);
			   }
			  annuler_deplacement(p, n);
                                           
			  if(tmp < min)
			  	min = tmp;
                      }

                  }
               }
             }
          }
     }
     return min;
}
/*---------------------------------------------------------------*/

int Max(partie *p, int profondeur)
{
     if(profondeur == 0){
     	//printf("profondeur = 0 dans Max\n");
     	return eval(p);
     }

     
     //printf("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc\n");	  
     int i1,j1,i2,j2, tmp, max=-10000;
     coord d, f;
     int n=1, m=1;

     for(i1=0;i1<DIM;i1++)
     {
          d.ligne=i1;
          for(j1=0;j1<DIM;j1++)
          {
             d.colonne=j1;
             if(case_vide(p, creer_coord(i1,j1))==0 && p->damier[i1][j1] !=' ' && piece_joueur(piece_identifier(p->damier[i1][j1]))==J0)
             {
               for(i2=0;i2<DIM;i2++)
               {
                  f.ligne=i2;
                  for(j2=0;j2<DIM;j2++)
                  {
                      f.colonne=j2;
                      if(deplacement_valide(p,d,f,0) != 0)
                      {
                          n = deplacement(p,d,f,1);
                          if(n>=m)
			   {
			   	m=n;
				changer_joueur(p);
				tmp = Min(p,profondeur-1);
				changer_joueur(p);
			   }
			  annuler_deplacement(p, n);
                         
                          if(tmp > max)
		                    max = tmp;
                      }
                  }

               }
            }
         }
      }
     return max;
}
