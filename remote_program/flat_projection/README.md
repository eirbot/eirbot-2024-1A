## Module python indispensable :
1. opencv 
2. skimage
3. numpy 
4. matplotlib

## Démarche d'utilisation des scripts:
### **detect_aruco_tag.py**
#### Principe :
- utilise la caméra pour détecter des tags aruco sur flux continu

#### Possibilité offerte : 
- obtenir les coordonnées de chacun des coins du tag aruco, possibilité de
  tracer une flèche *(utilisable pour orientation des panneaux solaires )*

### **homo_transformation.py**
#### Principe : 
- prend en paramètre une image source et un tableau de coordonnée et opère la
  transformation homographique :
  https://docs.opencv.org/4.x/d9/dab/tutorial_homography.html

Note : la manière de trouver le tableau de coordonnées n'est pas indiquer Une
première méthode : plot l'image, noter les coordonées des coins du livre dans
mon exemple à la main et obtenir une image transformée qui va nous servir de
modèle pour la suite

#### Possibilité offerte : 
- si l'on connait les coordonnées des coins d'un objet, on peut obtenir une
  transformation homographique de cette image

### **get_corner_of_object.py**
#### Principe :
- prend en paramètre une image **modèle** obtenue à partir de
  *homo_transformation.py* et une image à pointer et renvoie les coordonnées
  des coins de l'objet

#### Possibilité offerte : 
- dès qu'on a une image modèle on peut transformer n'importe quelle photo d'un
  même objet

Note : n'est pas très satisfaisant pour des inclinaisons trop élevées *(essayer
avec book_bog_angle.jpg)*

## Nouvelles fonctions facilement implémentables
Pour implémenter video : définir une cadence de prise de photos : 2/sec =>
appliquer *get_corner_of_object.py* *homo_transformation.py* *(qui marche
seulement sur des images)*

Possibilité d'associer les id des tag aruco à des objets spécifiques *(panneaux
solaires, robots, plantes)*
