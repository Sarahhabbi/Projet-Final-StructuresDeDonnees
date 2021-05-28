#include<stdio.h>
#include<stdlib.h>
#include "Reseau.h"
#include "Chaine.h"

//fonction de création d'une commodité [non demandée]
Noeud* creerNoeud(double x, double y, int num){
    Noeud * nd = (Noeud*)(malloc(sizeof(Noeud)));
    nd->x = x;
    nd->y = y;
    nd->num = num;
    return nd;
}
CellCommodite* creerCommodite(Noeud* a, Noeud* b){
    CellCommodite * cellCom = (CellCommodite*)(malloc(sizeof(CellCommodite)));
    cellCom->extrA = a;
    cellCom->extrB = b;
    cellCom->suiv = NULL;
    return cellCom;
}

CellNoeud *creerCellNoeud(Noeud *noeud){
	CellNoeud *new = (CellNoeud *)malloc(sizeof(CellNoeud));
    new->nd = noeud;
    new->suiv = NULL;
	return new;
}


//2.1
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    if(R==NULL){
        printf("Réseau non alloué");
        return NULL;
    }
    CellNoeud* tmp = R->noeuds; //premier pointeur sur la liste chainée de noeuds

    while(tmp){
        Noeud* n = tmp->nd;     //récupération du noeud dans la cellule
        if(n->x == x && n->y == y){
            return n;
        }
        tmp = tmp->suiv;
    }
    // il n'y a pas de noeud aux coordonnées x et y
    // alors création d'un nouveau noeud
    Noeud* new = creerNoeud(x,y, R->nbNoeuds+1);
    R->nbNoeuds+=1; //on incrémente le nb de noeuds

    //création de la cellule du noeud
    CellNoeud* newCell = creerCellNoeud(new);
    newCell->suiv = R->noeuds;  //insération en tête de la liste des noeuds du réseau
    newCell->nd->voisins = NULL;    //voisins du noeud 
    R->noeuds = newCell;
    return new;
}


void insertNoeud(Noeud* nd, Noeud* new){
    //gérer le cas ou le noeud new est déjà dans la liste de voisins de nd
    CellNoeud* tmp = nd->voisins;
    while(tmp){
        if(tmp->nd == new){
            return;
        }
        tmp = tmp->suiv;
    }
    CellNoeud* newCell = creerCellNoeud(new); //création d'une CellNoeud pour le noeud voisin
    newCell->suiv = nd->voisins;  
    nd->voisins = newCell; //mise en tête du nouveau voisin dans la liste des voisins de nd
}

void afficher_voisins(CellNoeud* noeuds){
    CellNoeud* tmp1 = noeuds;
    while(tmp1){
        CellNoeud* tmp2 = tmp1->nd->voisins;
        printf("Noeud:%d -->",tmp1->nd->num);
        while(tmp2){
            printf("num:%d | ", tmp2->nd->num);
            tmp2 = tmp2->suiv;
        }
        printf("\n");
        tmp1 = tmp1->suiv;
    }   
}

//2.2 
Reseau* reconstitueReseauListe(Chaines *C){
    Reseau *R=(Reseau*) malloc(sizeof(Reseau));
    //initialisation du Réseau
        R->noeuds = NULL;
        R->commodites = NULL;
        R->nbNoeuds = 0;
        R->gamma = C->gamma;

    //Parcours de chaque chaines
    CellChaine* tmp=C->chaines;
    while (tmp){//parcours de toutes les chaines
    
        CellPoint* p=tmp->points; //récupération des points de la chaine
        Noeud* ndprec = rechercheCreeNoeudListe(R,p->x,p->y);   //ajout du noeud avec les coordonnées du point dans le Reseau
        Noeud* e1 = ndprec;//récupérer l'extrA  pour créer une commodité
        p = p->suiv;
        while (p!=NULL){
            Noeud* nd = rechercheCreeNoeudListe(R,p->x,p->y);   //ajout du noeud avec les coordonnées du point dans le Reseau
            insertNoeud(ndprec, nd);
            insertNoeud(nd, ndprec); 
            ndprec=nd;
            p = p->suiv;
        }
        Noeud* e2 = ndprec;//récupérer  extrB pour créer une commodité

        //ajout de la commodité après avoir enregistré une chaîne
        CellCommodite * cellCom = creerCommodite(e1,e2);
        cellCom->suiv = R->commodites;
        R->commodites = cellCom;

        tmp = tmp->suiv; //passage à la chaine suivante
   }
   return R;
}

int nbCommodites(Reseau *R){
    if (R==NULL){
        return 0;
    }
    int nb = 0;
    CellCommodite * com = R->commodites;
    while (com){
        nb++;
        com = com->suiv;        
    }
    return nb;
}

int nbLiaisons(Reseau *R){   
    if (R==NULL){
        return 0;
    }
    CellNoeud* noeuds = R->noeuds;
    int cp = 0;
    while(noeuds){ //on parcours tous les noeuds du Reseau
        Noeud* tmp = noeuds->nd; //n
        CellNoeud* voisin = tmp->voisins;
        while(voisin){
            if(tmp->num > voisin->nd->num){
                cp++;
            }
            voisin = voisin->suiv;
        }
        noeuds = noeuds->suiv;
    }
    return cp;
}


void ecrireReseauTxt(Reseau *R, FILE *f){

	fprintf(f, "NbNoeuds: %d\n", R->nbNoeuds); 
	fprintf(f, "NbLiaisons: %d\n", nbLiaisons(R));  //fonction pas encore codée 
	fprintf(f, "NbCommodites: %d\n", nbCommodites(R));
	fprintf(f, "Gamma: %d\n", R->gamma);
	fprintf(f, "\n");

    //affichage des noeuds du Réseau
    CellNoeud *noeuds = R->noeuds;
	Noeud *noeud;
	while (noeuds){
		noeud = noeuds->nd;
		fprintf(f, "v %d %.2f %.2f\n", noeud->num, noeud->x, noeud->y);
		noeuds = noeuds -> suiv;
	}
	fprintf(f,"\n");

    // affichage des liaisons
    noeuds = R->noeuds;
	while (noeuds){
		noeud = noeuds->nd;
        CellNoeud* voisins= noeud->voisins;
        while(voisins){
            if(voisins->nd->num < noeud->num){
                fprintf(f, "l %d %d \n", voisins->nd->num, noeud->num);
            }
            voisins = voisins->suiv;
        }
		noeuds = noeuds -> suiv;
	}

	fprintf(f,"\n");

    //affichage des commodités
    CellCommodite* com = R->commodites;
    while (com){
		fprintf(f, "k %d %d\n",com->extrA->num, com->extrB->num);
		com = com->suiv;
	}
}

void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}

