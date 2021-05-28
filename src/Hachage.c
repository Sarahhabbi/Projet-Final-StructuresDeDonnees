#include<math.h>
#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#define  A ((sqrt(5)-1)/2)

// donne des clees à partir des coordonnées
int fonctionClef(int x, int y){
    return y + (x + y)*(x + y + 1)/2;
}
// donne des indices à partir d'une clée et la taille du tableau de hachage
int fonctionHachage(int cle, int M){
    return (int)(M*(cle*A - (int)(cle*A))); // A définie avec un #define
}

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){
    if(R==NULL || H== NULL){
        return NULL;
    }
    int clee = fonctionClef( (int)x, (int)y);
    int indice =fonctionHachage(clee, H->M);
    CellNoeud * cellNoeud = H->T[indice];
    while(cellNoeud !=NULL){
        if(cellNoeud->nd->x == x && cellNoeud->nd->y == y ){
            return cellNoeud->nd;
        }
        cellNoeud = cellNoeud->suiv;
    }
   

    // il n'y a pas de noeud aux coordonnées x et y
    // alors création d'un nouveau noeud
    Noeud* new = (Noeud*)(malloc(sizeof(Noeud)));
    new->x = x;
    new->y = y;
    new->voisins = NULL;
    new->num = R->nbNoeuds+1;
    R->nbNoeuds+=1; //on incrémente le nb de noeuds

    // ajout dans le reseau
    //création de la cellule du noeud
    CellNoeud* newCell = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    newCell->nd = new;  
    newCell->suiv = R->noeuds;  //insération en tête de la liste des noeuds du réseau 
    R->noeuds = newCell;

    // ajout dans ta table de hachage
    //création d'une deuxième cellule du noeud
    CellNoeud* newCell2 = (CellNoeud*)(malloc(sizeof(CellNoeud)));
    newCell2->nd = new;  
    newCell2->suiv = H->T[indice];
    H->T[indice] = newCell2;

    return new;
}


Reseau* reconstitueReseauHachage(Chaines *C, int M){
    // création et initialisation de la table de hachage
    TableHachage* H = (TableHachage*)malloc(sizeof(TableHachage));
    H->T = (CellNoeud**)malloc(sizeof(CellNoeud* )*M);
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
        Noeud* ndprec = rechercheCreeNoeudHachage(R, H, p->x,p->y);   //ajout du noeud avec les coordonnées du point dans le Reseau
        Noeud* e1 = ndprec;//récupérer l'extrA  pour créer une commodité
        p = p->suiv;
        while (p!=NULL){
            Noeud* nd = rechercheCreeNoeudHachage(R, H, p->x,p->y);   //ajout du noeud avec les coordonnées du point dans le Reseau
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