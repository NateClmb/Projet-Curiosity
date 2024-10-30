#include "generation_terrains.h"
#include "terrain.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nb_cases_occupees(Terrain *T) {
  int occupee = 0;
  int x, y;
  for (x = 0; x < largeur(T); x++) {
    for (y = 0; y < hauteur(T); y++) {
      if (T->tab[x][y] != LIBRE)
        occupee++;
    }
  }
  return occupee;
}

// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_max de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char **argv) {
  int N, l, h;
  float dObst;
  FILE *resFile;
  Terrain T;

  if (argc < 6) {
    printf(
        "Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n",
        argv[0]);
    return 1;
  }

  N = strtol(argv[1], NULL, 10);
  l = strtol(argv[2], NULL, 10);
  h = strtol(argv[3], NULL, 10);
  dObst = strtof(argv[4], NULL);

  // test de l et h
  if (l > DIM_MAX || l % 2 == 0) {
    printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if (h > DIM_MAX || h % 2 == 0) {
    printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if ((dObst > 1) || (dObst < 0)) {
    printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
    return 1;
  }

  // Ouverture du fichier résultat
  resFile = fopen(argv[5], "w");
  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);

  // Initialisation de la fonction random
  // A compléter
  float density;
  float ttl_density=0;
  int terrain_valide;
  float vald=0.0;
  srand(time(NULL));


  // A compléter
  // Génération aléatoire des terrains
  for (int i=0; i<N; i++){
    generation_aleatoire(&T,l,h,dObst);
    T.largeur=l;
    T.hauteur=h;
    terrain_valide=existe_chemin_vers_sortie(&T);
    //printf("Terrain valide: %d",terrain_valide);
    if (terrain_valide > 0){
      vald+=1.0;
    }
    density=0;

    // Écriture des terrains générés dans le fichier resFile
    for (int k=0; k<h; k++){
      for (int j=0; j<l; j++){
        if ((k == h/2) && (j == l/2)) {
          T.tab[k][j]='C';
          fprintf(resFile,"%c",T.tab[k][j]);
        }
        else {
          switch (T.tab[k][j]) {
            case 0:
              T.tab[k][j] = '.';
              break;
            case 1:
              T.tab[k][j] = '#';
              density+=1;
              break;
            case 2:
              T.tab[k][j] = '~';
              density+=1;
              break;
            }
        fprintf(resFile,"%c",T.tab[k][j]);
        }
      }
      fprintf(resFile,"\n");
    }

    density = (density/(l*h));
    ttl_density += density;
    // Écriture/Affichage des statistiques
    printf("\nLongeur: %d, hauteur %d, densite theorique %f, densite reelle %f\n",l,h,dObst,density);
    fprintf(resFile,"\n");
    fprintf(resFile,"\n");
    fprintf(resFile,"\n");
  }
  // fermeture des fichiers
  fprintf(resFile,"Densite moyenne: %f\n",ttl_density/N);
  fprintf(resFile,"Pourcentage terrain valide : %f\n",(vald/N)*100);
  fclose(resFile);
  return 0;
}
