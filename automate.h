#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Alphabet Alphabet;
struct Alphabet 
{
    char listeAlphabet[100];
    int tailleAlphabet;
        
};

typedef struct States States;
struct States
{
    char liste[100];
    int taille;
        
};

typedef struct Relation Relation;
struct Relation
{
    char from;
    char to;
    char alphabet;
};

typedef struct ListeRelations ListeRelations;
struct ListeRelations
{
    int taille;
    Relation* liste;
};

typedef struct Automate Automate;
struct Automate
{
    Alphabet alphabet;
    States Initial_States;
    States Final_States;
    ListeRelations liste_Relations;
};


Alphabet getAlphabet(){
    Alphabet alphabet;                                           //Liste qui contiendra notre alphabet. /!\ Alphabet de 20 caractères max
    alphabet.tailleAlphabet = 0;
    FILE* fichier = NULL; 
    fichier=fopen("automate.txt", "r");
    if(fichier != NULL){                                         //Permet de vérifier que le fichier a bien été ouvert  
        fseek(fichier,3, SEEK_SET);                              // On déplace le curseur 3 fois sur la ligne pour qu'il pointe sur la première valeur de l'alphabet
        int i = 0;                                             
        for(int a=0; a<=30; a++){
            if(i%2 == 0){                                       //Cette condition permet d'alterner et de prendre un caractère sur 2
                alphabet.listeAlphabet[alphabet.tailleAlphabet] = fgetc(fichier);
                i++;
                alphabet.tailleAlphabet++;
            }
            else{
                if( fgetc(fichier) != '}')                      //Cette condition permet de repérer la fin de l'alphabet
                i++;
                else
                break;
            }
        }
        fclose(fichier);
    }
    else{
        printf("Importation du fichier échoué \n");
    }
    return alphabet;
}

States getInitialStates(){
    States initialStates;
    initialStates.taille=0;
    char ligneInitialStates[100];                                //On crée cette variable car on aura besoin d'une liste de char qui contiendra la chaine de caractères correspondant à la ligne des états initiaux quand on utilisera fgets (ligne 63) 
    FILE* fichier = NULL; 
    fichier=fopen("automate.txt", "r");
    if(fichier != NULL){                                         //Permet de vérifier que le fichier a bien été ouvert  
        fgets(ligneInitialStates, 100, fichier);                 //Permet de déplacer le curseur à la ligne 2
        for(int a=0; a<3; a++) fgetc(fichier);                   // On déplace le curseur 3 fois sur la ligne 2 pour qu'il pointe sur la première valeur des états initiaux
        int i = 0;                                             
        for(int b=0; b<=30; b++){
            if(i%2 == 0){                                       //Cette condition permet d'alterner et de prendre un caractère sur 2
                initialStates.liste[initialStates.taille] = fgetc(fichier);
                i++;
                initialStates.taille++;
            }
            else{
                if( fgetc(fichier) != '}')                      //Cette condition permet de repérer la fin des états initiaux
                i++;
                else
                break;
            }
        }
        fclose(fichier);
    }
    else{
        printf("Importation du fichier échoué \n");
    }
    return initialStates;
}

States getFinalStates(){
    States finalStates;
    finalStates.taille=0;
    char ligneFinalStates[100];                                                 //On crée cette variable car on aura besoin d'une liste de char qui contiendra la chaine de caractères correspondant à la ligne des états finaux quand on utilisera fgets (ligne 63) 
    FILE* fichier = NULL; 
    fichier=fopen("automate.txt", "r");
    if(fichier != NULL){                                                       //Permet de vérifier que le fichier a bien été ouvert  
        for (int a=0; a<= 1; a++) fgets(ligneFinalStates, 100, fichier);       //Permet de déplacer le curseur à la ligne 3              
        for (int b=0; b<3; b++)  fgetc(fichier);                               // On déplace le curseur 3 fois sur la ligne  3 pour qu'il pointe sur la première valeur des états finaux
        int i = 0;                                             
        for(int c=0; c<=30; c++){
            if(i%2 == 0){                                                     //Cette condition permet d'alterner et de prendre un caractère sur 2
                finalStates.liste[finalStates.taille] = fgetc(fichier);
                i++;
                finalStates.taille++;
            }
            else{
                if( fgetc(fichier) != '}')                                    //Cette condition permet de repérer la fin des états finaux
                i++;
                else
                break;
            }
        }
        
        fclose(fichier);
    }
    else printf("Importation du fichier échoué \n");
    return finalStates;
}

ListeRelations getListeRelations(){
    ListeRelations liste_Relations;
    Relation relation;
    int nombreRelations = 0;
    int valeurCurseurFin = 0;                                                //Récuperera la valeur du curseur pointant sur le dernier caractere du fichier
    char ligneRelation[100];                                                 //On crée cette variable car on aura besoin d'une liste de char (string) qui contiendra la chaine de caractères correspondant à la ligne des relations quand on utilisera fgets 
    FILE* fichier = NULL; 
    fichier=fopen("automate.txt", "r");

        fseek(fichier, 0, SEEK_END);
        valeurCurseurFin = ftell(fichier);                                   //Permet de récupérer la valeur du curseur pointant sur le dernier caractère du fichier
        fseek(fichier, 0, SEEK_SET);                                         //On replace le curseur au début 
        for(int a=0; a<3; a++) fgets(ligneRelation, 100, fichier);           //Permet de placer le curseur à la 4e ligne  
        while(ftell(fichier) < valeurCurseurFin){
            fgets(ligneRelation, 100, fichier);
            nombreRelations++;
        }
        Relation* listeRelations = NULL;
        listeRelations = malloc(nombreRelations*3*sizeof(char));             //Permet d'allouer la mémoire pour notre tableau de relations
        fseek(fichier, 0, SEEK_SET);                                         //On replace le curseur au début
        for(int b=0; b<3; b++) fgets(ligneRelation, 100, fichier);           //Permet de placer le curseur à la 4e ligne 
        for(int c=0; c<nombreRelations;c++){
            relation.from=fgetc(fichier);
            fseek(fichier, 1, SEEK_CUR);                                     //On déplace le curseur d'un caractèer pour que celui-ci pointe sur le 3e caractère de la ligne
            relation.to=fgetc(fichier);
            fseek(fichier, 1, SEEK_CUR);
            relation.alphabet=fgetc(fichier);
            (*(listeRelations+c))= relation;
            fgets(ligneRelation,100, fichier);
        } 
        liste_Relations.taille=nombreRelations;
        liste_Relations.liste=listeRelations;    
    return liste_Relations;
}

Automate getAutomate(){
    Automate automate;
    automate.alphabet=getAlphabet();
    automate.Initial_States=getInitialStates();
    automate.Final_States=getFinalStates();
    automate.liste_Relations=getListeRelations();
    return automate;
}

void printAutomaton(Automate automate){
    
    /*  ALPHABET  */
    printf("\n\n------------ AUTOMATE ------------ \n\n");
    printf("Alphabet : ");
    for(int i=0; i<(automate.alphabet.tailleAlphabet - 1); i++) printf(" %c - ",automate.alphabet.listeAlphabet[i]);
    printf("%c \n\n", automate.alphabet.listeAlphabet[automate.alphabet.tailleAlphabet-1]); 
    
    /*  Etats Initiaux  */
    printf("Etats initiaux : ");
    for(int j=0; j<(automate.Initial_States.taille-1); j++) printf("%c - ", automate.Initial_States.liste[j]);
    printf("%c \n\n", automate.Initial_States.liste[automate.Initial_States.taille-1]);

    /*  Etats Finaux  */
    printf("Etats finaux : ");
    for(int j=0; j<(automate.Final_States.taille-1); j++) printf("%c - ", automate.Final_States.liste[j]);
    printf("%c \n\n", automate.Final_States.liste[automate.Final_States.taille-1]);

    /*  Relations  */
    printf("Relations : \n");
    for(int k=0; k<automate.liste_Relations.taille; k++) printf("%c --> %c  =  %c \n", (*(automate.liste_Relations.liste+k)).from, (*(automate.liste_Relations.liste+k)).to, (*(automate.liste_Relations.liste+k)).alphabet);
    printf("\n\n");

}

