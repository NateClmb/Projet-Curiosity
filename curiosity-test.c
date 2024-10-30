#include "environnement.h"
#include "interprete.h"
#include "programme.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  //initialisation des variables
  Environnement envt;
  Programme prog;
  erreur_terrain errt;
  erreur_programme errp;
  etat_inter etat;
  resultat_inter res;
  FILE *f;
  char Etat_OK=0;
  char ligne[256];
  int max_rep=0;
  char result;
  int rx,ry;
  char orientation;


  //test si il y a assez d'arguments
  if (argc < 2) {
    printf("Usage: %s <nom_fichier_test>\n", argv[0]);
    return 1;
  }

  //Ouverture du fichier en mode lecture
  f = fopen(argv[1], "r");
  if (f == NULL) {
    gestion_erreur_terrain(ERREUR_FICHIER);
    return 1;
  }

  //Récupération de la première ligne
  fscanf(f,"%s\n",ligne);
  
  printf("Ligne Terrain:%s\n",ligne);
  
  /* Initialisation de l'environnement : lecture du terrain,
     initialisation de la position du robot */
  errt = initialise_environnement(&envt, ligne);
  gestion_erreur_terrain(errt);


  //Récupération de la seconde ligne
  fscanf(f,"%s\n",ligne);
  printf("SECONDE LIGNE:%s\n",ligne);
  /* Lecture du programme */
  errp = lire_programme(&prog, ligne);
  gestion_erreur_programme(errp);

  // Initialisation du nombre max de répétition
  fscanf(f,"%d\n",&max_rep);
  printf("MAX_REP:%d\n", max_rep);

  //
  fscanf(f,"%c\n",&result);
  printf("result:%c\n", result);
  
  
  /* Initialisation de l'état */
  init_etat(&etat);
  do {
    res = exec_pas(&prog, &envt, &etat);
    /* Affichage du terrain et du robot */
    // afficher_envt(&envt);
    max_rep--;
  } while (res == OK_ROBOT && max_rep>0);

  /* Affichage du résultat */
  /*ici et jusqu'a la fin du prog, pour resumer ces lignes testent le comportement d'un programme, on est ok
  a partir du moment ou: -L'utilisateur "voit" ou le robot est censé finir avec quelle orientation, et si le programme correspond à cette
  pensée de l'utilisateur ALORS LA on est ok*/
  switch (res) {
  case OK_ROBOT:
    if ( result=='F'){
      fscanf(f,"%d %d\n",&rx, &ry);
      fscanf(f,"%c\n",&result);
      
      if (rx==envt.r.x && ry==envt.r.y){
        switch (envt.r.o){
        case Nord:
          orientation='N';
          break;
        case Sud:
          orientation='S';
          break;
        case Est:
          orientation='E';
          break;
        case Ouest:
          orientation='O';
          break;
        default:
          printf("Erreur : Orientation pas valide\n");
          Etat_OK= 1;
        }

        if (orientation==result){
          printf("Ok\n");
        }

        else{
          printf("Erreur : Orientation pas correspondante\n");
          Etat_OK =1;
        }
      }
      else{

      printf("Erreur : Coordonné non correspondante\n");
      Etat_OK =1;
      }
    }

    else {
      printf("Erreur : État final non correspondant\n");
      Etat_OK =1;
    }
    break;
  case SORTIE_ROBOT:
    if (result=='S' ){
      printf("Ok\n");
      Etat_OK = 0;
    }
    else {
      printf("Erreur : État final non correspondant\n");
      Etat_OK = 1;
    }
    break;

  case ARRET_ROBOT:
    if (result=='N'){
      fscanf(f,"%d %d\n",&rx, &ry);
      fscanf(f,"%c\n",&result);
      if (rx==envt.r.x && ry==envt.r.y){
        switch (envt.r.o){
        case Nord:
          orientation='N';
          break;
        case Sud:
          orientation='S';
          break;
        case Est:
          orientation='E';
          break;
        case Ouest:
          orientation='O';
          break;
        default:
          printf("Erreur : Orientation pas valide\n");
          return 1;
        }
        if (orientation==result){
          printf("Ok\n");
          return 0;
        }
        else{
          printf("Erreur : Orientation pas correspondante\n");
          return 1;
        }
      }
      printf("Erreur : Coordonné non correspondante\n");
      return 1;
    }

    else {
      printf("Erreur : État final non correspondant\n");
      return 1;
    }
    break;
  case PLOUF_ROBOT:
    if (result=='P' ){
      printf("Ok\n");
    }
    else {
      printf("Erreur : État final non correspondant\n");
      Etat_OK = 1;
    }
    break;
  case CRASH_ROBOT:
    if (result=='O'){
      printf("Ok\n");
    }
    else {
      printf("Erreur : État final non correspondant\n");
      Etat_OK = 1;
    };
    break;
  case ERREUR_PILE_VIDE:
    printf("ERREUR : pile vide\n");
    Etat_OK = 1;
    break;
  case ERREUR_ADRESSAGE:
    printf("ERREUR : erreur d'adressage\n");
    Etat_OK = 1;
    break;
  case ERREUR_DIVISION_PAR_ZERO:
    printf("ERREUR : division par 0\n");
    Etat_OK = 1;
    break;
  }

  if (Etat_OK ==0){
    printf("Ok\n");
  }
  fclose(f);
  return 0;
}