#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Chaine.h"

int main(int argc, char** argv){
    // question 1.1 & 1.2
    if(argc<2){
        printf("Erreur, arguments attendus non entrée\n");
        exit(1);
    }
    
    // On récupeère le nom du fichier
    char* nomfic = argv[1]; 
    FILE * f = fopen(nomfic, "r");
    if (f==NULL){
        printf("L'ouverture du fichier %s a échoué", nomfic);
    }
   
    Chaines* chaines = lectureChaines(f);
    FILE *f2 = fopen("00014_burma_test.cha", "w");
    ecrireChaines(chaines, f2);
    
    fclose(f2);
    fclose(f);
    
    // question 1.3
    afficheChainesSVG(chaines, "svg_test");
    // question 1.4
    //printf("%.2lf\n",longueurChaine(chaines->chaines));
    //printf("%.2lf\n",longueurTotale(chaines));
    // question 1.5
    //printf("%d\n",comptePointsTotal(chaines));
   
    
    return 0;
}
