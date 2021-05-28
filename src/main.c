#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"

#define NB_POINTS_CHAINE 100
#define X_MAX 500
#define Y_MAX 500

Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax) {
    srand(time(NULL));

    //Création d'une chaine
    Chaines* chaine = (Chaines*)(malloc(sizeof(Chaines)));
    chaine->nbChaines = nbChaines;
    chaine->gamma = nbPointsChaine;

    CellChaine* listeChaine = NULL; //pour créer une liste chainée de chaine
    for (int i = 0; i < nbChaines; i++) { //pour générer un certain nombre de chaines
        //création d'une chaine de points
        CellChaine* chaineCell = (CellChaine*)(malloc(sizeof(CellChaine)));
        chaineCell->numero = i;

        //génération des points
        CellPoint* listePoint = NULL;
        for (int j = 0; j < nbPointsChaine; j++) {
            CellPoint* point = (CellPoint*)(malloc(sizeof(CellPoint)));
            point->x = rand()%xmax;
            point->y = rand()%ymax;
            point->suiv = listePoint;
            listePoint = point;
        }

        chaineCell->points = listePoint;
        chaineCell->suiv = listeChaine;
        listeChaine = chaineCell;
    }
    chaine->chaines = listeChaine;
    return chaine;
}

int main() {
    FILE* f1 = fopen("vitesse_liste.txt", "w");
    FILE* f2 = fopen("vitesse_hach.txt", "w");
    clock_t temps_initial, temps_final;
    double temps_cpu;
    Chaines* c;
    Reseau* R1 = NULL;
    Reseau* R2 = NULL;
    Reseau* R3 = NULL;

    for (int i = 500; i <=5000 ; i += 500) { 
        c = generationAleatoire(i, NB_POINTS_CHAINE, X_MAX, Y_MAX);

        // temps_initial = clock();
        // R1 = reconstitueReseauListe(c);
        // temps_final = clock();
        // temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        // fprintf(f1, "%d %f\n", i, temps_cpu);


        temps_initial = clock();
        R2 = reconstitueReseauHachage(c, i);
        temps_final = clock();
        temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        fprintf(f2, "%d %f\n",i , temps_cpu);

        // temps_initial = clock();
        // R3 = reconstitueReseauArbre(c);
        // temps_final = clock();
        // temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        // fprintf(f2, "%d %f\n",i , temps_cpu);
    }
    fclose(f1);
    fclose(f2);
    return 0;
}