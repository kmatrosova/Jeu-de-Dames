#include <stdio.h>
#include <stdlib.h>

#include "partie_jouer.h"



int menu_main();
int menu_charger();

int main(int argc, char *argv[])
{
    char *chargement = NULL;
    int c;
    
    if(argc == 2)
    {
            chargement = argv[1];
	    	partie *p=partie_charger(chargement);
	    	if(p!=NULL)
	    	{
	    		c = menu_charger();
	    		partie_jouer(p, c);
	    	}
                
    }

    int x;
    partie *p;
    while(1)
    {
	x=menu_main();

	if(x==1)
	{
	    p=partie_nouvelle();
	    partie_jouer(p, 0);
	}
	if(x==2)
	{
	    p=partie_nouvelle();
	    aff(p);
	    partie_jouer(p, 1);
	}
	if(x==3)
	{
	    p=option_main_chargement_partie(p);
	    if(p!=NULL)
	    {
    		c = menu_charger();
    		partie_jouer(p, c);
    	    }
	}
	if(x==4)
	{
	    replay();
	}
	if(x==5)
	{
	    break;
	}
    }
    return 0;
}

int menu_main()
{
    int c=0;
    printf("\n\nJEU DE DAMES\n");
    printf("\n1-Joueur VS Joueur\n2-Joueur VS Ordinateur\n3-Charger partie\n4-Rejouer une partie\n5-Quitter partie\nVotre choix ?");
    while(c<1 || c>5)
    	scanf("%d", &c);
    printf("\n");
    return c;
}

int menu_charger()
{
    int c=2;
    printf("\n\nPartie chargée\n");
    printf("\n0-Joueur VS Joueur\n1-Joueur VS Ordinateur\nVotre choix ?");
    while(c<0 || c>1)
    	scanf("%d", &c);
    printf("\n");
    return c;
}

