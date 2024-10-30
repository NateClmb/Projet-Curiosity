#ifndef _OBSERVATEUR_H_
#define _OBSERVATEUR_H_
#include <stdio.h>

typedef enum {A,G,D,M} Alphabet;

typedef enum {Init,Mes,E} Etats;

//permet de switcher entre les etats de l'automate vu en TD
Etats transition(Etats q,Alphabet command);

//permet de switcher entre les etats de notre automate
Etats transition2(Etats q,Alphabet command);

//Initialise l'automate
Etats initialise_automate();

//Regarde si l'automate est dans un état final
int etat_final(Etats q);

#endif