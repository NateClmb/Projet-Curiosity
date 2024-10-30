#include "observateur.h"

//permet de switcher entre les etats de l'automate vu en TD
Etats transition(Etats q, Alphabet command){
    switch(q){
        case Init:
            if (command == M){
                q=Mes;
            }
            else if (command == A){ //modifier A par G, pour avoir l'automate d'Anis
                q=E;
            }
            break;
        case Mes:
            if (command != M){
                q=Init;
            }
            break;
        default:
            break;
    }
    return q;
}

Etats transition2(Etats q, Alphabet command){
    switch(q){
        case Init:
            if (command == M){
                q=Mes;
            }
            else if ((command == G) || (command == D)){
                q=E;
            }
            break;
        case Mes:
            if (command == A){
                q=Init;
            }
            else if ((command == G) || (command == D)){
                q=E;
            }
            break;
        default:
            break;
    }
    return q;
}

//Initialise l'automate
Etats initialise_automate(){
    return Init;
}

//Regarde si l'automate est dans un état final
int etat_final(Etats q){
    if (q == E){
        return 0;
    }
    return 1;
}