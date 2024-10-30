#include "robot.h"
#include <stdio.h>

#define TAILLE_TERRAIN 10

/* Affiche une orientation sur la sortie standard */
void afficher_orientation(Orientation o) {
  switch (o) {
  case Nord:
    printf("Nord\n");
    break;
  case Est:
    printf("Est\n");
    break;
  case Sud:
    printf("Sud\n");
    break;
  case Ouest:
    printf("Ouest\n");
    break;
  }
}

void afficher_infos_robot(Robot *r) {
  int x, y;
  int x1, y1;

  // Récupérer la position du robot
  position(r, &x, &y);
  // Récupérer la case devant le robot
  position_devant(r, &x1, &y1);
  // Afficher la position
  printf("Position : (%d, %d) - Orientation : ", x, y);
  afficher_orientation(orient(r));
  printf("\n");
}

int main(int argc, char **argv) {
  //initialisation
  Robot r;
  char c;


  init_robot(&r, 0, 0, Est);

  afficher_infos_robot(&r);

  printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in : ");
  scanf(" %c", &c);
  while (c != 'f') {

    /* À compléter */
    //pour chaque valeur de c, on associe une action du fichier robot.c
    switch(c){
      case 'a':
        printf("On avance\n");
        avancer(&r);
        break;
      case 'g':
        printf("On tourne a gauche\n");
        tourner_a_gauche(&r);
        break;
      case 'd':
        printf("On tourne a droite\n");
        tourner_a_droite(&r);
        break;
      default:
        printf("Action non valide\n");
        break;
    }




    afficher_infos_robot(&r);
    //on affiche les donnees du robot, puis on redemande une action a l'utilisateur
    printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in : ");
    scanf(" %c", &c);
  }
}
