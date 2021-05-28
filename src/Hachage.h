#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Chaine.h"
#include "Reseau.h"

typedef struct _Hachage{
    int M; // taille de la table de hachage
    CellNoeud** T; // la table de hachage
} TableHachage;

int fonctionClef(int x, int y); // donne les cles
int fonctionHachage(int cle, int M); // donne les indices hachées
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
Reseau* reconstitueReseauHachage(Chaines *C, int M);
#endif