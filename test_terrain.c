#include "terrain.h"
#include <stdio.h>

int main(int argc, char **argv) {
  //initialisation
  FILE *f;
  Terrain t;
  int x, y;
  char nomfichier[DIM_MAX];
  int stop=0;
  erreur_terrain er;

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  //on ouvre le fichier et er contient le resultat du test de lire_terrain
  f = fopen(argv[1], "r");
  er=lire_terrain(f, &t, &x, &y);
  //tant qu'on a un test non valide
  while((er!=OK)){
    switch(er){
      //en cas d'erreur fichier, on redemande a l'utilisateur un nom de fichier pour reessayer
      case ERREUR_FICHIER:
        printf("Erreur lors de l'ouverture du fichier, réessayer avec un autre nom de fichier:\n-> ");
        printf("\n");
        scanf("%s",nomfichier);
        f = fopen(nomfichier, "r");
        er=lire_terrain(f, &t, &x, &y);
        break;
      //les autres erreurs doivent etre corrigees manuellement dans les fichiers, donc on dit que le test est "ok" (pour sortir de la boucle), mais on n'affiche que le message d'erreur, pas le terrain
      case ERREUR_LECTURE_LARGEUR:
        printf("Erreur au niveau de la largeur, veuillez la corriger\n");
        er=OK;
        stop=1;
        break;
      case ERREUR_LECTURE_HAUTEUR:
        printf("Erreur au niveau de la hauteur, veuillez la corriger\n");
        er=OK;
        stop=1;
        break;
      case   ERREUR_CARACTERE_INCORRECT:
        printf("Un symbole inconnu est glissé dans le terrain, veuillez le remplacer par un caractere parmi: # ou . ou ~\n");
        er = OK;
        stop=1;
        break;
      case ERREUR_POSITION_ROBOT_MANQUANTE:
        printf("Il n'y a aucun robot, veuillez en ajouter 1\n");
        er=OK;
        stop=1;
        break;

      default:
        er = OK;
        stop=1;
        printf("Erreur non prévue par la correction du TP6");
        break;
    }
  }




  fclose(f);
  if (stop == 0){
    //affichage terrain si le test est reellement ok (donc un ok qui n'est pas la juste pour sortir de la boucle)
    afficher_terrain(&t);
    printf("Position initiale du robot : (%d, %d)\n", x, y);
  }
}
