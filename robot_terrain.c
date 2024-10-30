#include "robot.h"
#include "terrain.h"
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

/*affiche les informations du robot*/
void afficher_infos_robot(Robot *r) {
  int x, y;
  int x1, y1;

  // Récupérer la position du robot
  position(r, &x, &y);
  // Récupérer la case devant le robot
  position_devant(r, &x1, &y1);
  // Afficher la position
  printf("Position : (%d, %d) -Position devant: (%d,%d) - Orientation : ", x, y, x1, y1);
  afficher_orientation(orient(r));
  printf("\n");
}

/*affiche le robot dans le terrain*/
void afficher_terrain_et_robot(Terrain *t, Robot *r) {
  //initialisation
  int i, j;
  char c;

  //pour tout les elements du terrain
  for (j = 0; j < hauteur(t); j++) {
    for (i = 0; i < largeur(t); i++) {
      if ((i == abscisse(r)) && (j == ordonnee(r))) {
        // Afficher le robot selon son orientation
        switch (orient(r)) {
        case Nord:
          c = '^';
          break;
        case Est:
          c = '>';
          break;
        case Sud:
          c = 'v';
          break;
        case Ouest:
          c = '<';
          break;
        }
      } else {
        // Afficher la case
        switch (t->tab[i][j]) {
        case LIBRE:
          c = '.';
          break;
        case ROCHER:
          c = '#';
          break;
        case EAU:
          c = '~';
          break;
        }
      }
      printf("%c", c);
    }
    printf("\n");
  }
}

/* Renvoie vrai si le robot r, de sa position et orientation courante,
   peut avancer dans le terrain t */
int robot_peut_avancer(Terrain *t, Robot *r) {
  /* À compléter */
  //initialisation
  int x=0;
  int y=0;
  int resultat=0;
  Case c;
  position_devant(r,&x,&y);
  //ce if gere les cas ou le robot tente de sortir hors du terrain, si il essaye de sortir du terrain, on en l'empeche
  if ((x<0)||(y<0)||(x>=largeur(t))||(y>=hauteur(t))){
    return resultat;
  }


  //pour chaque cas de la case devant le robot
  c=t->tab[x][y];
  switch(c){
    //si la case est libre, resultat est vrai
    case LIBRE:
      printf("terre en vue mon capitaine\n");
      resultat=1;
      break;
    //dans tout les autres cas, resultat est faux
    case ROCHER:
      printf("Rocher droit devant mon capitaine\n");
      break;
    case EAU:
      printf("Riviere droit devant mon capitaine\n");
      break;
    default:
      printf("On peut vraiment en arriver ici ?\n");
      break;
  }
  //si resultat vrai, alors on peut avancer, sinon on ne peut pas
  return resultat;
}

int main(int argc, char **argv) {
  //initialisation
  Terrain t;
  FILE *f;
  erreur_terrain e;
  int x, y;
  Robot r;
  char c;

  // Lecture du terrain : nom du fichier en ligne de commande
  if (argc < 2) {
    printf("Usage: %s <fichier terrain>\n", argv[0]);
    return 1;
  }

  // Lecture du terrain
  f = fopen(argv[1], "r");
  e = lire_terrain(f, &t, &x, &y);
  fclose(f);

  if (e != OK) {
    printf("Erreur lors de la lecture du terrain\n");
    return 2;
  }

  // Initialisation du robot
  init_robot(&r, x, y, Est);

  afficher_infos_robot(&r);
  afficher_terrain_et_robot(&t, &r);

  printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in : ");
  scanf(" %c", &c);
  //teste les commandes pour avancer, droite et gauche
  while (c != 'f') {
    int x, y; // Position devant
    switch (c) {
    case 'G':
    case 'g':
      tourner_a_gauche(&r);
      break;
    case 'D':
    case 'd':
      tourner_a_droite(&r);
      break;
    case 'A':
    case 'a':
      position_devant(&r, &x, &y);
      if (robot_peut_avancer(&t, &r)) {
        avancer(&r);
      } else {
        printf(" !! Le robot ne peut pas avancer !!\n");
      }
    }

    afficher_infos_robot(&r);
    afficher_terrain_et_robot(&t, &r);

    printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in : ");
    scanf(" %c", &c);
  }
}
