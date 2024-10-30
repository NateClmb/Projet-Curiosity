#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "generation_terrains.h"

#include <stdio.h>
#include <stdlib.h>

//

void gestion_erreur_terrain(erreur_terrain e) {
  /*cette fonction gère les erreurs de terrain, et affiche dans la console si il y a une erreur */
  /*pas de commentaire sur chaque cas, le nom des variables est assez exaustif*/
  switch (e) {
  case OK:
    break;
  case ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case ERREUR_LECTURE_LARGEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
    exit(1);
  case ERREUR_LECTURE_HAUTEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
    exit(1);
  case ERREUR_LARGEUR_INCORRECTE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case ERREUR_CARACTERE_INCORRECT:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case ERREUR_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case ERREUR_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case ERREUR_POSITION_ROBOT_MANQUANTE:
    printf(
        "Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}

void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for (i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}

void gestion_erreur_programme(erreur_programme e) {
  /*cette fonction gère les erreurs de programme, et affiche dans la console si il y a une erreur */
  /*pas de commentaire sur chaque cas, le nom des variables est assez exaustif*/
  switch (e.type_err) {
  case OK_PROGRAMME:
    break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}

int main(int argc, char **argv) {
    //initialisation des variables que l'on utilisera
    int N, l, h;
    int seed, nb_pas;
    float dObst;
    FILE *resFile;
    Terrain T;
    int etat_rob;
    int compteur_pas;
    int etat_final=-1;

  //check si on a assez d'arguments
    if (argc < 9) {
        printf(
            "Usage: %s <fichier_programme> <N> <largeur> <hauteur> <densite_obstacle> <graine> <nb_pas> <fichier_res> \n",
            argv[0]);
        return 1;
    }

    //associe chaque element de l'entree standard a sa variable associée
    programme = fopen(argv[1],"r");
    N = strtol(argv[2], NULL, 10);
    l = strtol(argv[3], NULL, 10);
    h = strtol(argv[4], NULL, 10);
    dObst = strtof(argv[5], NULL);
    seed = strtol(argv[6], NULL, 10);
    nb_pas = strtol(argv[7], NULL, 10);

    printf("dObst: %f\n",dObst);

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
    resFile = fopen(argv[8], "w");
    // Écriture du nombre de terrains
    fprintf(resFile, "Nombre de terrains teste: %d\n", N);

    // Initialisation de la fonction random
    // A compléter
    //initialisation variables pour les statistiques
    //float density;
    //float ttl_density=0;
    int terrain_valide;
    float vald=0.0;
    float nombr_pas=0.0;
    int nb_terrain_sortie=0;
    int nb_terrain_obstacle=0;
    int nb_terrain_bloque=0;
    srand(time(NULL)%seed);


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
        //density=0;

        // Écriture des terrains générés dans le fichier resFile
        /*
        for (int i=0; i<h; i++){
            for (int j=0; j<l; j++){
                if ((i == h/2) && (j == l/2)) {
                    T.tab[i][j]='C';
                    //fprintf(resFile,"%c",T.tab[i][j]);
                    }
                else {
                    switch (T.tab[i][j]) {
                        case 0:
                        T.tab[i][j] = '.';
                        break;
                        case 1:
                        T.tab[i][j] = '#';
                        density+=1;
                        break;
                        case 2:
                        T.tab[i][j] = '~';
                        density+=1;
                        break;
                        }
                    //fprintf(resFile,"%c",T.tab[i][j]);
                }
        }
        //fprintf(resFile,"\n");
        }*/


        //teste le robot dans le terrain
        Environnement envt;
        Programme prog;
        // erreur_programme errp;
        etat_inter etat;
        resultat_inter res;
        Robot r;


        envt.t = T;
        init_robot(&r,(l/2),(h/2),Est);
        envt.r = r;
        /* Lecture du programme */
        // errp = lire_programme(&prog, argv[1]);

        /* Initialisation de l'état  et execution du programme en fonction du nombre de pas donne*/
        init_etat(&etat);
        etat_final=-1;
        etat_rob=0;
        compteur_pas=0;
        while (compteur_pas<nb_pas){
          res = exec_pas(&prog, &envt, &etat);
          etat_rob++;
          compteur_pas++;
          if (res == SORTIE_ROBOT){
              etat_final = etat_rob;
              nombr_pas+=etat_final;
              nb_terrain_sortie++;
              break;
          }
          else if (res == PLOUF_ROBOT){
              etat_final=-2;
              nb_terrain_obstacle++;
              break;
          }
          else if (res == CRASH_ROBOT){
              etat_final=-3;
              nb_terrain_obstacle++;
              break;
          }
        }
        if (compteur_pas==nb_pas){
          nb_terrain_bloque++;
        }
        




        //density = (density/(l*h));
        //ttl_density += density;
        // Écriture/Affichage des statistiques
        //printf("\nTerrain N°%d \n Longeur: %d, hauteur %d, densite theorique %f, densite reelle %f\n",i+1,l,h,dObst,density);
        fprintf(resFile,"%d\n",etat_final);
    }
    // fermeture des fichiers et affichage
    //printf("Densite moyenne: %f\n",ttl_density/N);
    printf("Pourcentage terrain valide: %f\n",(vald/N)*100);
    printf("Nb pas moyen par terrain valide: %f\n",nombr_pas/nb_terrain_sortie);
    printf("Nombre terrain ou robot prend obstacle: %d\n",nb_terrain_obstacle);
    printf("Nombre terrains bloque: %d\n",nb_terrain_bloque);
    fclose(resFile);
    return 0;
}