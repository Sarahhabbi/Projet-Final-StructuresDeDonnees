#include<stdio.h>
#include<stdlib.h>
#include "ArbreQuat.h"


void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
    if(C){
        CellChaine* tmp = C->chaines;
        //on initilise des variables qui serviront à trouver les min et max parmi les points de la chaine 
        CellPoint* p = tmp->points; // c'est le premier point de la chaine, on aurait pu les affecter tous à 0 mais c'est mieux d'utiliser un point du reseau
        double x_min = p->x;  
        double x_max = p->x;
        double y_min = p->y;
        double y_max = p->y;

        while(tmp){ // parcours de toutes les chaînes 
            CellPoint* point = tmp->points; // parcours de tous les points
            while(point){
                //test des coordonnées du point courant avec les coordonnée max et min
                if(point->x > x_max){   
                    x_max = point->x;
                }
                if(point->y > y_max){
                    y_max = point->y;
                }
                if(point->x < x_min){
                    x_min = point->x;
                }
                if(point->y < y_min){
                    y_min = point->y;
                }
                point = point->suiv;
            }
            tmp = tmp->suiv;
        }
        //on affecte aux paramètres les valeurs qu'on a trouvées
        *xmin = x_min;
        *ymin = y_min;
        *xmax = x_max;
        *ymax = y_max;
    }
}

void afficherArbre(ArbreQuat** a){
	if((*a) == NULL || a==NULL) {
		return;
	}
	if((*a)->noeud) {
		printf("Num:%d    X = %f   Y = %f \n", (*a)->noeud->num, (*a)->noeud->x, (*a)->noeud->y);
	}
    // printf("coucou\n");
	afficherArbre(&(*a)->no);
	afficherArbre(&(*a)->so);
	afficherArbre(&(*a)->ne);
	afficherArbre(&(*a)->se);
}

ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY){
    ArbreQuat* abr = (ArbreQuat*)(malloc(sizeof(ArbreQuat)));
    abr->xc = xc;
    abr->yc = yc;
    abr->coteX = coteX;
    abr->coteY = coteY;
    abr->noeud = NULL;
    abr->se = NULL;
    abr->so = NULL;
    abr->ne = NULL;
    abr->no = NULL;
    return abr;
}

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
    ArbreQuat* abr = (*a); 

    // cas arbre vide
    if (abr == NULL){
        // printf("insertion arbre vide\n");
        //coordonnées du milieu de la cellule parent
        double xc = parent->xc; 
        double yc = parent->yc;
        double CoteX = parent->coteX; 
        double CoteY = parent->coteY;
        double newXC;
        double newYC;

        // if(n->x < xc){
        //     newXC = xc - (xc/4.0); // quart ouest du rectangle
        // }else{
        //     newXC = xc + (xc/4.0); // quart est du rectangle
        // }
        // if(n->x < yc){
        //     newYC = yc - (yc/4.0); // quart nord du rectangle
        // }else{ 
        //     newYC = yc + (yc/4.0); // quart sud du rectangle
        // }
        //on détermine le nouveau centre de la cellule de l'arbre 
        if(n->x < xc){  //Correction
            newXC = xc - (CoteX/4.0); // quart ouest du rectangle
        }else{
            newXC = xc + (CoteX/4.0); // quart est du rectangle
        }
        if(n->x < yc){
            newYC = yc - (CoteY/4.0); // quart nord du rectangle
        }else{ 
            newYC =yc + (CoteY/4.0); // quart sud du rectangle
        }

        abr = creerArbreQuat(newXC,newYC, parent->coteX/2.0, parent->coteY/2.0); 
        abr->noeud = n;  //on ajoute le noeud dans la nouvelle cellule créée
    }

    //cas Feuille
    else if(abr->noeud != NULL){
        // printf("insertion feuilles\n");
        Noeud* nd = abr->noeud;
        abr->noeud = NULL;
        if(nd->x < abr->xc){
            if(nd->y < abr->yc){
                insererNoeudArbre(nd,&(abr->so),abr);
            }
            else{
                insererNoeudArbre(nd,&(abr->no),abr);
            }
        }else{
            if(nd->y < abr->yc){
                insererNoeudArbre(nd,&(abr->se),abr);
            }
            else{
                insererNoeudArbre(nd,&(abr->ne),abr);
            }
        }
        if(n->x < abr->xc){
            if(n->y < abr->yc){
                insererNoeudArbre(n,&(abr->so),abr);
            }
            else{
                insererNoeudArbre(n,&(abr->no),abr);
            }
        }else{
            if(n->y < abr->yc){
                insererNoeudArbre(n,&(abr->se),abr);
            }
            else{
                insererNoeudArbre(n,&(abr->ne),abr);
            }
        }
    }

    //Cas cellule interne
    else if( (*a != NULL) && ((*a)->noeud == NULL) ) {
        // printf("insertion cellule interne\n");
        if(n->x < abr->xc){
            if(n->y < abr->yc){
                insererNoeudArbre(n,&(abr->so),abr);
            }
            else{
                insererNoeudArbre(n,&(abr->no),abr);
            }
        }else{
            if(n->y < abr->yc){
                insererNoeudArbre(n,&(abr->se),abr);
            }
            else{
                insererNoeudArbre(n,&(abr->ne),abr);
            }
        }
    }
    return;
}


Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){
    if(R == NULL){
        printf("Réseau non alloué");
        return NULL;
    }
    //CAS arbre vide
    if (*a == NULL){ 
        // printf("V\n");//test
        // il n'y a pas de noeud aux coordonnées x et y dans l'arbre
        Noeud* new = creerNoeud(x,y, R->nbNoeuds+1);

        //création de la cellule du noeud
        CellNoeud* newCell = creerCellNoeud(new);
        //insertion en tête de la liste des noeuds du réseau
        newCell->suiv = R->noeuds; 
        R->noeuds = newCell;
        newCell->nd->voisins = NULL;    //voisins du noeud 
        R->nbNoeuds+=1; //on incrémente le nb de noeuds

        insererNoeudArbre(new,a,parent); // on insere le nouveau noeud dans l'arbre

        return new;
    }

    //cas feuille   
    if((*a)->noeud != NULL){  
        // printf("F\n");//test
       Noeud* tmp = (*a)->noeud; 
        if(tmp->x == x && tmp->y == y){ //le noeud est dans l'arbre
            return tmp;
        }
        // il n'y a pas de noeud aux coordonnées x et y dans l'arbre
        Noeud* new = creerNoeud(x,y, R->nbNoeuds+1);

        //création de la cellule du noeud
        CellNoeud* newCell = creerCellNoeud(new);
        //insertion en tête de la liste des noeuds du réseau
        newCell->suiv = R->noeuds; 
        R->noeuds = newCell;
        newCell->nd->voisins = NULL;    //voisins du noeud 
        R->nbNoeuds+=1; //on incrémente le nb de noeuds

        insererNoeudArbre(new,a,parent); // on insere le nouveau noeud dans l'arbre
        return new;
    }
    
    //Cas cellule interne
    if(*a!=NULL && (*a)->noeud == NULL){  
        // printf("CI\n"); //test
        if(x < (*a)->xc){
            if(y < (*a)->yc){
                return rechercheCreeNoeudArbre(R,&(*a)->so,*a,x,y);
            }
            else{
                return rechercheCreeNoeudArbre(R,&(*a)->no,*a,x,y);
            }
        }else{
            if(y < (*a)->yc){
                return rechercheCreeNoeudArbre(R,&(*a)->se,*a,x,y);
            }
            else{
                return rechercheCreeNoeudArbre(R,&(*a)->ne,*a,x,y);
            }
        }
    }
    return NULL;
}


void libereArbreQuat(ArbreQuat* a) {
    if (a == NULL) return;
    
    if (a -> noeud != NULL) {
        free(a);
        return;
    }
    libereArbreQuat(a -> so);
    libereArbreQuat(a -> no);
    libereArbreQuat(a -> ne);
    libereArbreQuat(a -> se);
    free(a);
}
Reseau* reconstitueReseauArbre(Chaines* C){
    // création et initialisation de l'arbre parent
    double xmin, xmax, ymin, ymax;
    chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
    double coteX = xmax-xmin;
    double coteY = ymax-ymin;
    ArbreQuat* parent = creerArbreQuat(coteX/2.0, coteY/2.0, coteX, coteY);
    // printf("%p\n", parent); //test 

    //initialisation du Réseau
    Reseau* R=(Reseau*)(malloc(sizeof(Reseau)));
    R->noeuds = NULL;
    R->commodites = NULL;
    R->nbNoeuds = 0;
    R->gamma = C->gamma;

    //Parcours de chaque chaines
    CellChaine* tmp = C->chaines;
    while (tmp){ //parcours de toutes les chaines

        CellPoint* p = tmp->points; //récupération des points de la chaine
        Noeud* ndprec = rechercheCreeNoeudArbre(R,&parent,parent,p->x,p->y);   //ajout du noeud avec les coordonnées du point dans le Reseau
        Noeud* e1 = ndprec;     //récupérer l'extrA  pour créer une commodité
        p = p->suiv;
        Noeud* nd = NULL;
        while (p != NULL){
            if(p->x < parent->xc){ 
                if(p->y < parent->yc){
                    nd = rechercheCreeNoeudArbre(R,&(parent->so),parent,p->x,p->y); 
                }
                else{
                    nd = rechercheCreeNoeudArbre(R,&(parent->no),parent,p->x,p->y); 
                }
            }else{
                if(p->y < parent->yc){
                    nd = rechercheCreeNoeudArbre(R,&(parent->se),parent,p->x,p->y); 
                }
                else{
                    nd = rechercheCreeNoeudArbre(R,&(parent->ne),parent,p->x,p->y); 
                }
            }
            // printf("num: %d,  x: %.2f,  y: %.2f\n", nd->num, nd->x, nd->y); //Test 
            insertNoeud(ndprec, nd);
            insertNoeud(nd, ndprec); 
            ndprec = nd;
            p = p->suiv;
        }
        Noeud* e2 = ndprec;//récupérer  extrB pour créer une commodité

        //ajout de la commodité après avoir enregistré une chaîne
        CellCommodite * cellCom = creerCommodite(e1,e2);
        cellCom->suiv = R->commodites;
        R->commodites = cellCom;

        tmp = tmp->suiv; //passage à la chaine suivante
    }
    afficherArbre(&parent);
    return R;
}