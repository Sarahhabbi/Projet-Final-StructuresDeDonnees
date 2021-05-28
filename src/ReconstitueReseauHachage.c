#include<stdio.h>
#include<stdlib.h>
#include "Chaine.h"
#include "Hachage.h"

#define M  30

int main(int argc, char* argv[]){
    if(argc<2){
        printf("2 arguments attendu");
        exit(1);
    }
    char* fic= argv[1];
    // int choix = atoi(argv[2]);

    //ouverture du fichier en lecture
    FILE* f = fopen(fic,"r");
    //lecture de la chaine
    Chaines* C = lectureChaines(f);
    // constitution du réseau
    Reseau * reseau  = reconstitueReseauHachage(C, M);
    // écriture du réseau
    FILE* f2 = fopen("00014_burma_test.resH","w");
    ecrireReseauTxt(reseau, f2);
    //afficher_voisins(reseau->noeuds);
    fclose(f);
    fclose(f2);

    // question 1.3
    afficheReseauSVG(reseau, "svg_test_reseauH");
    

    //pour la 2.3 
    // switch (choix)
    // {
    // case 1:
        
    //     break;

    // case 2:
       
    //     break;

    // case 3:
       
    //     break;

    // default:
    //     break;
    // }
    return 0;
}