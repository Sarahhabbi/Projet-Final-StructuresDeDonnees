#include<stdio.h>
#include<stdlib.h>
#include "Chaine.h"

// quetion 1.1
Chaines* lectureChaines(FILE *f){
    Chaines* chaines = (Chaines*)malloc(sizeof(Chaines));
    if (chaines == NULL){
        printf("problème d'allocatin mémoire");
        return NULL;
    }
    char buffer[256];
    int nbChaines; int gamma; char tmp[256];
    // lecture de nombres de chaines
    if(fgets(buffer, 256, f)==NULL){
        printf("problème de lecture de fichiers");
        return NULL;
    }
    
    if (sscanf(buffer, "%s %d", tmp, &nbChaines)!=2){
        printf("problème de lecture de formattage de fichier");
        return NULL;
    }
    // lecture de gamma
    if(fgets(buffer, 256, f)==NULL){
        printf("problème de lecture de fichiers");
        return NULL;
    }
    if (sscanf(buffer, "%s %d", tmp, &gamma)!=2){
        printf("problème de formattage de fichier");
        return NULL;
    }
    chaines->nbChaines = nbChaines; 
    chaines->gamma= gamma;
    chaines->chaines = NULL;
    // lecture des lignes de chaines
    while (nbChaines>0){
        CellChaine* cellChaine = (CellChaine*)malloc(sizeof(CellChaine));
        int num; int nbPoints;
        if (fscanf(f, " %d %d", &num, &nbPoints)!=2){
            printf("problème de formattage de fichier");
            return NULL;
        }
        cellChaine->numero = num;
        cellChaine->points=NULL;
        cellChaine->suiv = chaines->chaines;
        chaines->chaines =  cellChaine->suiv;
        // lecture de points
        
        while (nbPoints>0){
            CellPoint* cellPoint = (CellPoint*)malloc(sizeof(CellPoint));
            double x, y;
            if (fscanf(f, " %lf %lf", &x, &y)!=2){
                printf("problème de de formattage de fichier");
                return NULL;
            }
            
            cellPoint->x = x;
            cellPoint->y = y;
            cellPoint->suiv = cellChaine->points;
            cellChaine->points =cellPoint;

            nbPoints--;
        }
        cellChaine->suiv = chaines->chaines;
        chaines->chaines = cellChaine;
        
        nbChaines--;
   
    }
    return chaines;
}
// quetion 1.2
void ecrireChaines(Chaines *C, FILE *f){
    if(C== NULL){
        printf("Ecriture échoué !");
        return;
    }
    fprintf(f, "NbChain: %d\n", C->nbChaines);
    fprintf(f, "Gamma: %d\n", C->gamma);
    CellChaine * chaines = C->chaines;
    while (chaines)
    {
        fprintf(f, "%d ", chaines->numero);
        CellPoint *points = chaines->points;
        while(points){
           fprintf(f, "%.2lf %.2lf ", points->x, points->y); 
           points=points->suiv;
        }
        fprintf(f, "\n"); 
        chaines = chaines->suiv;
    }
    
}

void afficheChainesSVG(Chaines *C, char* nomInstance){
    int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}


double longueurChaine(CellChaine *c){
    double longeur = 0;
    CellPoint * precdent =NULL;
    CellPoint * point = c->points;
    while (point->suiv){
        precdent = point;
        point= point->suiv;
        longeur += sqrt( (precdent->x - point->x)*(precdent->x - point->x) + (precdent->y - point->y)*(precdent->y - point->y) );

    }
    return longeur;
       
}

double longueurTotale(Chaines *C){
    
    if (C==NULL){
        return 0;
    }
    double longeur = 0;
    CellChaine * chaines = C->chaines;
    while (chaines){
        longeur+= longueurChaine(chaines);
        chaines=chaines->suiv;        
    }
    return longeur;
}

int comptePointsTotal(Chaines *C){
    
     if (C==NULL){
        return 0;
    }
    int nbPointsTotal = 0;
    CellChaine* chaines = C->chaines;
    while (chaines){
        CellPoint *points = chaines->points;
        while (points){
        
            nbPointsTotal +=1;
            points = points->suiv;
        }
        
        chaines = chaines->suiv;
    }

    
    return nbPointsTotal;
}

void liberer_CellPoint(CellPoint* c){
    CellPoint* tmp;
    //parcours de la liste des points
    while(c){
        tmp = c->suiv;
        free(c);
        c = tmp;
    }
}

void liberer_CellChaine(CellChaine* c){
    CellChaine* tmp;
    //parcours de la liste de chaines
    while(c){
        tmp = c->suiv;
        liberer_CellPoint(c->points);
        free(c);
        c = tmp;
    }
}

void liberer_Chaine(Chaines* c){
    liberer_CellChaine(c->chaines);
    free(c);
}