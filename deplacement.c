#include <stdio.h>
#include <stdlib.h>

#include "deplacement.h"

int deplacement_valide(partie* p, coord dep, coord arr, int IA){
	if(case_vide(p, creer_coord(arr.ligne,arr.colonne))==0)
	{
		if(p->joueur == J1 && !IA) printf("CASE D'ARRIVEE NON VALIDE\n");
		return 0;
	}
	if(case_vide(p, creer_coord(dep.ligne,dep.colonne)) || p->damier[dep.ligne][dep.colonne]==' ')
	{
		if(p->joueur == J1 && !IA)  printf("CASE DE DEPART NON VALIDE\n");
		return 0;
	}
	if(piece_identifier(p->damier[dep.ligne][dep.colonne])->joueur!=p->joueur)
	{
		if(p->joueur == J1 && !IA) printf("PIECE DU JOUEUR ADVERSE\n");
		return 0;
	}
	if(piece_identifier(p->damier[dep.ligne][dep.colonne])->promu)
	{
		if (deplacement_valide_dame(p,dep,arr)==2) return 2;
		else if (deplacement_valide_dame(p,dep,arr)==1){
			if(verifier_peut_manger(p))
			{
				if(p->joueur == J1 && !IA) printf("Vous avez l'obligation de manger !\n");
				return 0;
			}
			else
				return 1;
		}
		else return 0;
	}
	else
	{
		if (deplacement_valide_pion(p,dep,arr)==2) return 2;
		else if (deplacement_valide_pion(p,dep,arr)==1){
            	if(verifier_peut_manger(p))
            	{
			if(p->joueur == J1 && !IA)  printf("Vous avez l'obligation de manger !\n");
			return 0;
		}
			else
				return 1;
		}
		else
		{
			if(p->joueur == J1 && !IA) printf("DEPLACEMENT PION PAS POSSIBLE\n");
			return 0;
		}
	}
}


int deplacement_pion_2cases(partie* p, coord dep, coord arr)
{
	if(arr.ligne==dep.ligne+2){
		if(arr.colonne==dep.colonne-2){
			if(piece_adversaire(p,creer_coord(dep.ligne+1,dep.colonne-1)) == 1)
				return 2;
		}
		else if(arr.colonne==dep.colonne+2){
			if(piece_adversaire(p,creer_coord(dep.ligne+1,dep.colonne+1)) == 1)
				return 2;
		}
	}
	else if(arr.ligne==dep.ligne-2){
		if(arr.colonne==dep.colonne-2){
			if(piece_adversaire(p,creer_coord(dep.ligne-1,dep.colonne-1)) == 1)
				return 2;
		}
		else if(arr.colonne==dep.colonne+2){
			if(piece_adversaire(p,creer_coord(dep.ligne-1,dep.colonne+1)) == 1)
				return 2;
		}
	}
	return 0;
}

int deplacement_valide_pion(partie* p, coord dep, coord arr)
{
	if(p->joueur==J0){
		if(arr.ligne==dep.ligne+1){
			if(arr.colonne==dep.colonne-1 ||arr.colonne==dep.colonne+1){
				return 1;
			}
		}
	}
	if(p->joueur==J1){
		if(arr.ligne==dep.ligne-1){
			if(arr.colonne==dep.colonne-1 ||arr.colonne==dep.colonne+1){
				return 1;
			}
		}
	}
	return deplacement_pion_2cases(p,dep,arr);
}
int deplacement_valide_dame(partie* p, coord dep, coord arr){
	int i, j;

	int x=arr.ligne-dep.ligne;
	int y=arr.colonne-dep.colonne;
	if(x<0) x=-x;
	if(y<0) y=-y;
	if(x!=y) return 0;
	int p_adv=0;
	
	if(arr.ligne>dep.ligne && arr.colonne>dep.colonne){

		for(i=dep.ligne+1, j=dep.colonne+1; i<arr.ligne && j<arr.colonne; i++, j++)
		{
			if(piece_adversaire(p,creer_coord(i,j)) == 1)
				p_adv++;
			else if (piece_adversaire(p,creer_coord(i,j)) == 0)
				return 0;
		}
	}
	if(arr.ligne<dep.ligne && arr.colonne<dep.colonne){
		for(i=dep.ligne-1, j=dep.colonne-1; i>arr.ligne && j>arr.colonne; i--, j--)
		{
			if(piece_adversaire(p,creer_coord(i,j)) == 1)
				p_adv++;
			else if (piece_adversaire(p,creer_coord(i,j)) == 0)
				return 0;
		}
	}
	if(arr.ligne<dep.ligne && arr.colonne>dep.colonne){
		for(i=dep.ligne-1, j=dep.colonne+1; i>arr.ligne && j<arr.colonne; i--, j++)
		{
			if(piece_adversaire(p,creer_coord(i,j)) == 1)
				p_adv++;
			else if (piece_adversaire(p,creer_coord(i,j)) == 0)
				return 0;
		}
	}
	if(arr.ligne>dep.ligne && arr.colonne<dep.colonne){
		for(i=dep.ligne+1, j=dep.colonne-1; i<arr.ligne && j>arr.colonne; i++, j--)
		{
			if(piece_adversaire(p,creer_coord(i,j)) == 1)
				p_adv++;
			else if (piece_adversaire(p,creer_coord(i,j)) == 0)
				return 0;
		}
	}
	if(p_adv>1) return 0;
	if(p_adv==0) return 1;
	else return 2;
}


int verifier_pion_peut_manger(partie* p, coord c)
{
	if((piece_adversaire(p, creer_coord(c.ligne+1,c.colonne+1)) == 1)&&case_vide(p, creer_coord(c.ligne+2,c.colonne+2))==1)
		return 1;
	if((piece_adversaire(p, creer_coord(c.ligne+1,c.colonne-1)) == 1)&&case_vide(p, creer_coord(c.ligne+2,c.colonne-2))==1)
		return 1;
	if((piece_adversaire(p, creer_coord(c.ligne-1,c.colonne+1)) == 1)&&case_vide(p, creer_coord(c.ligne-2,c.colonne+2))==1)
		return 1;
	if((piece_adversaire(p, creer_coord(c.ligne-1,c.colonne-1)) == 1)&&case_vide(p, creer_coord(c.ligne-2,c.colonne-2))==1)
		return 1;
	else return 0;
}

int verifier_dame_peut_manger(partie* p, coord c)
{
	int i, j;

	for(i=c.ligne+1, j=c.colonne+1; i<DIM && j<DIM; i++, j++)
	{
		if(piece_adversaire(p, creer_coord(i,j)) == 0)
			break;
		else if((piece_adversaire(p, creer_coord(i,j)) == 1) && (case_vide(p, creer_coord(i+1,j+1))==1))
			return 1;

	}
	for(i=c.ligne+1, j=c.colonne-1; i<DIM && j>0; i++, j--)
	{
		if(piece_adversaire(p, creer_coord(i,j)) == 0)
			break;
		else if(piece_adversaire(p, creer_coord(i,j)) == 1 && case_vide(p, creer_coord(i+1,j-1))==1)
			return 1;

	}
	for(i=c.ligne-1, j=c.colonne+1; i>0 && j<DIM; i--, j++)
	{
		if(piece_adversaire(p, creer_coord(i,j)) == 0)
			break;
		else if(piece_adversaire(p, creer_coord(i,j)) == 1 && case_vide(p, creer_coord(i-1,j+1))==1)
			return 1;
		
	}
	for(i=c.ligne-1, j=c.colonne-1; i>0 && j>0; i--, j--)
	{
		if(piece_adversaire(p, creer_coord(i,j)) == 0)
			break;
		else if(piece_adversaire(p, creer_coord(i,j)) == 1 && case_vide(p, creer_coord(i-1,j-1))==1)
			return 1;
	}
	return 0;
}

int verifier_piece_peut_manger(partie* p, coord c)
{
	if(p->damier[c.ligne][c.colonne]!=' ' && p->damier[c.ligne][c.colonne]!='.' && piece_joueur(piece_identifier(p->damier[c.ligne][c.colonne]))== p->joueur)
	{
		if(piece_identifier(p->damier[c.ligne][c.colonne])->promu)	
			return verifier_dame_peut_manger(p, c);
		else return verifier_pion_peut_manger(p, c);
	}
	return 0;
}

int verifier_peut_manger(partie* p)
{
	int i, j;

	for(i=0; i<DIM; i++)
	{
		for(j=0; j<DIM; j++)
		{
			if(verifier_piece_peut_manger(p, creer_coord(i,j))) return 1;
		}
	}
	return 0;
}


