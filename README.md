# Projet-Final-StructuresDeDonnees

<h1> Lecture, stockage et affichage des données</h1>
<h3>Exercice 1 – Manipulation d’une instance de “Liste de Chaˆınes” </h3>
- Construction d'une bibliothèque de manipulations d’instances : lecture et  écriture de fichier, affichage graphique de réseaux, calcul de la longueur totale des chaînées, et calcul du nombre de points.
<h2> Structure de liste chainée utilisée</h2>
![Capture d’écran 2021-05-28 à 11 44 21](https://user-images.githubusercontent.com/72084057/119964980-0c801c00-bfaa-11eb-95ee-f1ba1be7507f.png)
- Chaine.h

<h1> Reconstitution du réseau </h1>
<h3>Exercice 2 - Première méthode : stockage par liste chaînée</h3> 
- Algorithme de reconstitution de réseau en codant l’ensemble des nœuds du réseau par une liste chaînée. Pour cela, nous avons besoin de définir une structure pour manipuler un réseau: ensemble de nœuds, de câbles et de commodités.
<h2> Structure de réseau utilisée</h2>
 
 ![Capture d’écran 2021-05-28 à 11 47 37](https://user-images.githubusercontent.com/72084057/119965390-81535600-bfaa-11eb-984e-7c0ced2f590f.png)
 - Reseau.h
 
 <h3>Exercice 3 - Manipulation d'un réseau</h3> 
- Implémentation de méthodes pour manipuler et afficher un struct Reseau. Pour cela, on va stocker sur disque un Reseau en utilisant le format illustrée par l’instance 00014 burma qui est donnée par le fichier suivant 00014 burma.res (obtenu par l’exercice précédent).

<h3>Exercice 4 -Deuxième méthode : stockage par table de hachage </h3> 
-  Table de hachage avec gestion des collisions par chaînage. La table de hachage va donc contenir un tableau de pointeurs vers une liste de nœuds. Lors du parcours de la liste des points constituant une chaîne, la table de hachage va nous permettre de déterminer rapidement si un nœud a déjà été stocké dans le réseau. 
-  Hachage.h

 <h3> Exercice 5- Manipulation d'un réseau</h3> 
- Pour cet exercice, un arbre quaternaire sera utilisé pour la reconstitution du réseau. Comme pour la table de hachage, l’arbre quaternaire va nous permettre de d ́eterminer rapidement si un nœud a déjà été stocké dans le réseau.
- 
<h2> Structure de réseau utilisée</h2>
![Capture d’écran 2021-05-28 à 11 53 19](https://user-images.githubusercontent.com/72084057/119966148-4ef62880-bfab-11eb-9ddf-a619d189ab22.png)




