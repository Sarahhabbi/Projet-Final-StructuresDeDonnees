#include "Graphe.h"


Graphe* creerGraphe(Reseau* r){
    if (r == NULL){
        printf("Reseau non alloué");
        return NULL;
    }
    Graphe* graphe = (Graphe*)malloc(sizeof(Graphe));
    if (graphe == NULL){
        printf("Problème d'allocation");
        return NULL; 
    }
    graphe->gamma = r->gamma;
    graphe->nbsom = r->nbNoeuds;
    graphe->nbcommod =  nbCommodites(r); // fonction définie dans Reseau.c

    // on remplit les sommets
    graphe->T_som = (Sommet **)malloc(sizeof(Sommet *)*(graphe->nbsom)); 
    CellNoeud* noeuds = r->noeuds;
    while (noeuds){
        Sommet* sommet =  (Sommet*)malloc(sizeof(Sommet));
        sommet->num = noeuds->nd->num;
        sommet->x =  noeuds->nd->x;
        sommet->x =  noeuds->nd->y;
        graphe->T_som[sommet->num] = sommet;
        // créer la Liste chainee des voisins
        CellNoeud * voisins = noeuds->nd->voisins;
        while(voisins){
            Arete *arete = (Arete *)malloc(sizeof(Arete));
            arete->u = noeuds->nd->num;
            arete->v = voisins->nd->num;
            // mettre l'arete dans sa cellule
            Cellule_arete * cellule_arete = (Cellule_arete *)malloc(sizeof(Cellule_arete));
            cellule_arete->a = arete;
            // ajouter la cellule crée à la liste  des voinsins
            cellule_arete->suiv = sommet->L_voisin;
            sommet->L_voisin = cellule_arete->suiv;
            // passer au prochain voisin
            voisins = voisins->suiv;
        }
        noeuds = noeuds->suiv;
        
    }

    // on remplit les commoditées
    graphe->T_commod =  (Commod *)malloc(sizeof(Commod)*graphe->nbcommod);
    int i = 0;
    CellCommodite *commodites = r->commodites;
    while (commodites){
        Commod commodite;
        commodite.e1 = commodites->extrA->num;
        commodite.e2 = commodites->extrB->num;
        graphe->T_commod[i] = commodite;
        i++;

    }
    


    return graphe;

}