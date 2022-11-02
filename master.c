#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "master.h"

int couleurs[6] = {1, 2, 3, 4, 5, 6};

// Initialisation de la solution
void initialiser_solution(int * tab, int * germe)
{
    srand(*germe);
    int i, j;
    int c;
    int b = false;
    
    for (i = 0; i < 4; i++)
    {
        while(!b){
            b = true;
            c = couleurs[ rand() % 6 ];
            for (j = 0; j < i; j++){
                if(tab[j] ==  c){
                    b = false;
                    break;
                }
            }
        }
        tab[i] = c;
        b      = !b;

    }
}

// Affichage du plateau
void afficher_plateau(int (* plateau)[NB_COLONNES + 2])
{
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 6; j++)
        {
            printf(" %3d ", plateau[i][j]);
        }
        printf("\n");
    }
}


// Initialisation du plateau
void initialiser_plateau(int (* plateau)[NB_COLONNES + 2])
{
   for (int i = 0; i < 10; i++)
   {
      for(int j = 0; j < 6; j++)
      {
         plateau[i][j] = 0;
      }
   }
}

// Affichage de la solution
void afficher_solution()
{
    for (int i = 0; i < 4; i++)
    {
        printf(" %2d ", solution[i]);
    }
    printf("\n");
}


// Affichage par défaut du plateau - esthétique
void affichage_jeu(int (* plateau)[NB_COLONNES + 2]){

    int i, j;
    printf(" ======================b=m== \n");
    for (i = 0; i < NB_LIGNES; i++)
    {
        printf(" | ");
        for (j = 0; j < NB_COLONNES; j++)
        {
           if(plateau[i][j] != 0){
              couleur("33");
              printf(" %2d ", plateau[i][j]);
              couleur("0");
           }else{
             printf(" %2d ", plateau[i][j]);
           }
        }
        printf(" || ");
        couleur("32");
        printf("%d", plateau[i][NB_COLONNES]);
        couleur("0");
        couleur("31");
        printf(" %d", plateau[i][NB_COLONNES + 1]);
        couleur("0");
        printf("| \n");
    }

    printf(" =========================== \n");
}


// Prends la proposition du joueur
void prendre_proposition(int (*p)[NB_COLONNES + 2], int prp[NB_COLONNES], int essai)
{
    for (int i = 0; i < NB_COLONNES; i++)
    {
        prp[i] = p[essai][i];
    }
}


int contenir(int * solution, int c)
{
   int i;
   for (i = 0; i < NB_COLONNES; i++)
   {
      if (solution[i] == c)
      {
         return true;
      }
   }
   return false;
}

void ens_solutions(int * solution, int * t)
{
    int i;

    for (i = 0; i < NB_COLONNES + 3; i++)
    {
        t[i] = 0; 
    }

    for (i = 0; i < NB_COLONNES; i++)
    {
        t[solution[i]]++;
    }

}


/** VERSION : pointeurs **/
/*
void compiler_proposition(int * proposition, int * solution, int * bienp, int * malp) 
{
   int i;
   int ens  [NB_COLONNES + 3];
   int ens_s[NB_COLONNES + 3];

   *bienp = 0;
   *malp  = 0;

   ens_solutions(proposition, ens);
   ens_solutions(solution, ens_s);

   for (i = 0; i < NB_COLONNES; i++)
   {
      if (solution[i] == proposition[i])
      {
        *bienp = *bienp + 1;
      }else if (ens_s[solution[i]] <= ens[solution[i]] && ens_s[solution[i]] != 0){
        *malp  = *malp + 1;
      }
    }
} */


/** VERSION : structure (combinaison) **/

combinaison compiler_proposition(int * proposition, int * solution) 
{
   int i;
   int ens  [NB_COLONNES + 3];
   int ens_s[NB_COLONNES + 3];

   combinaison c;
   c.bienp = 0;
   c.malp  = 0;


   ens_solutions(proposition, ens);
   ens_solutions(solution, ens_s);

   for (i = 0; i < NB_COLONNES; i++)
    {
        if (solution[i] == proposition[i])
        {
            c.bienp++;
        }else if (ens_s[solution[i]] <= ens[solution[i]] && ens_s[solution[i]] != 0){
            c.malp++;
        } 
    }
   return c;
}