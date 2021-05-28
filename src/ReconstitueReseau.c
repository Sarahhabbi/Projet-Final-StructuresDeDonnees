#include<stdio.h>
#include<stdlib.h>
#include "Reseau.h"
#include "Chaine.h"

int main(int argc, char* argv[]){
    if(argc<2){
        printf("1 arguments attendu");
        exit(1);
    }
    char* fic= argv[1];
    // int choix = atoi(argv[2]);

    //ouverture du fichier en lecture
    FILE* f = fopen(fic,"r");
    //lecture de la chaine
    Chaines* C = lectureChaines(f);
    // constitution du réseau
    Reseau * reseau  = reconstitueReseauListe(C);
    // écriture du réseau
    FILE* f2 = fopen("00014_burma_test.res","w");
    ecrireReseauTxt(reseau, f2);
    afficher_voisins(reseau->noeuds);
    fclose(f);
    fclose(f2);

    // question 1.3
    afficheReseauSVG(reseau, "svg_test_reseau");
    

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
