#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "observateur.h"

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
    //FILE *terrain;
    //FILE *programme;
    //initialisation des variables
    Environnement envt;
    Programme prog;
    resultat_inter res;
    etat_inter etat;

    //test si il y a assez d'arguments
    if (argc < 3) {
        printf(
            "Usage: %s <fichier_terrain> <fichier_programme> \n",
            argv[0]);
        return 1;
    }

    //terrain = fopen(argv[1],"r");
    //programme = fopen(argv[2],"r");
    //On initialise l'environnement, le programme, et l'état
    initialise_environnement(&envt,argv[1]);
    lire_programme(&prog,argv[2]);
    init_etat(&etat);

    //execution du programme
    do{
        res=exec_pas(&prog,&envt,&etat);
    } while (res == OK);

    //on regarde l'état de l'automate à la fin de l'éxécution du programme
    switch(envt.observateur){
        case E:
            //etat puits
            printf("Le programme n'est pas valide\n");
            break;
        default:
            //autres états qui eux sont finaux
            printf("Le programme est valide\n");
            break;
    }

    return 0;
}