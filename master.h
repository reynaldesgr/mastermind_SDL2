#ifndef master_h
#define master_h

/* DECLARATION DES CONSTANTES SYMBOLIQUES */

#define NB_COLONNES 4
#define NB_LIGNES   10
#define NB_COULEURS 6

#define true  1
#define false 0


/* COULEURS */
#define couleur(param) printf("\033[%sm", param)

int solution[4];

/* DECLARATION DES TYPES PERSONNELS */
// et de leur typedef si besoin

typedef struct{
    int bienp;
    int malp;
} combinaison; 

/* DECLARATIONS DES METHODES */
void afficher_plateau           (int (* plateau)[NB_COLONNES + 2]);

void affichage_jeu              (int (* plateau)[NB_COLONNES + 2]);
void afficher_solution          (void);
void prendre_proposition        (int (*p)[NB_COLONNES + 2], int prp[NB_COLONNES], int essai);

void initialiser_solution       (int * tab, int * germe);
void initialiser_plateau        (int (* plateau)[NB_COLONNES + 2]);

/* METHODES UTILITAIRES */
int contenir                    (int * solution, int c);

combinaison compiler_proposition(int * proposition, int * solution); // le prototype est a adapter
// mettre ici les autres declarations

#endif