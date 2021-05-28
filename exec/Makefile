all: ChaineMain MainReseauLC MainReseauHachage MainReseauArbre Main

Chaine.o : Chaine.c Chaine.h
	gcc -c Chaine.c

Reseau.o : Reseau.c Reseau.h
	gcc -c Reseau.c

Hachage.o : Hachage.c Hachage.h
	gcc -c Hachage.c

ArbreQuat.o : ArbreQuat.c ArbreQuat.h
	gcc -c ArbreQuat.c

SVGwriter.o : SVGwriter.c SVGwriter.h
	gcc -c SVGwriter.c

ChaineMain: ChaineMain.o Chaine.o SVGwriter.o
	gcc -o ChaineMain ChaineMain.o Chaine.o SVGwriter.o


ChaineMain.o : ChaineMain.c Chaine.h
	gcc -c ChaineMain.c

MainReseauLC: ReconstitueReseau.o Chaine.o Reseau.o SVGwriter.o
	gcc -o MainReseauLC ReconstitueReseau.o Chaine.o Reseau.o SVGwriter.o

ReconstitueReseau.o : ReconstitueReseau.c Chaine.h Reseau.h
	gcc -c ReconstitueReseau.c


MainReseauHachage: ReconstitueReseauHachage.o Chaine.o Reseau.o Hachage.o SVGwriter.o
	gcc -o MainReseauHachage ReconstitueReseauHachage.o Chaine.o Reseau.o Hachage.o SVGwriter.o

	
ReconstitueReseauHachage.o : ReconstitueReseauHachage.c Chaine.h Reseau.h Hachage.h
	gcc -c ReconstitueReseauHachage.c


MainReseauArbre : ReconstitueReseauArbre.o Chaine.o Reseau.o ArbreQuat.o SVGwriter.o
	gcc -o MainReseauArbre ReconstitueReseauArbre.o Chaine.o Reseau.o ArbreQuat.o SVGwriter.o

ReconstitueReseauArbre.o : ReconstitueReseauArbre.c Chaine.h Reseau.h Hachage.h
	gcc -c ReconstitueReseauArbre.c

main.o : main.c 
	gcc -c main.c

Main : main.o Chaine.o Reseau.o ArbreQuat.o Hachage.o SVGwriter.o
	gcc -o Main main.o Chaine.o Reseau.o ArbreQuat.o Hachage.o SVGwriter.o

clean :
	rm -f *.o ChaineMain MainReseauLC MainReseauHahcage



