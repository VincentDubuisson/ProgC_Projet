#include <stdio.h>
#include <stdlib.h>
#ifndef MATRICE_H
#define MATRICE_H

typedef unsigned char **tMatrice;

/* -------------------------------- MatAllouer ---------------------------------
 * Alloue et initialise l’espace mémoire nécessaire pour stocker une matrice
 * de NbLig lignes et NbCol colonnes
 * Entrées :
 *  - NbLig : int, nombre de lignes
 *  - NbCol : int, nombre de colonnes
 * Sortie : unsigned char **, matrice
 */
extern tMatrice MatAllouer(int NbLig, int NbCol);

/* --------------------------------- MatLire -----------------------------------
 * Ecris la matrice de NbLig lignes et NbCol colonnes ainsi que tout ses éléments
 * entrés par l'utilisateur
 * Entrées :
 *  - pNbLig : int *, nombre de lignes
 *  - pNbCol : int *, nombre de colonnes
 * Sortie : unsigned char **, matrice | Initialisation de pNbLig et pNbCol
 */
extern tMatrice MatLire(int *pNbLig, int *pNbCol);

/* -------------------------------- MatAfficher --------------------------------
 * Affiche à l’écran le contenu de la matrice passée en paramètre
 * Entrées :
 *  - Mat : unsigned char **, matrice à afficher
 *  - NbLig : int, nombre de lignes
 *  - NbCol : int, nombre de colonnes
 * Sortie : printf (affichage)
 */
extern void MatAfficher(tMatrice Mat, int NbLig, int NbCol);

/* --------------------------------- MatCopier ---------------------------------
 * Réalise une copie de la matrice Mat de taille NbLig×NbCol
 * Entrées :
 *  - Mat : unsigned char **, matrice à copier
 *  - NbLig : int, nombre de lignes
 *  - NbCol : int, nombre de colonnes
 * Sortie : unsigned char **, copie de la matrice Mat
 */
extern tMatrice MatCopier(tMatrice Mat, int NbLig, int NbCol);

/* --------------------------------- MatLiberer --------------------------------
 * Libère tout l’espace mémoire occupé par la matrice d’adresse pMat
 * Entrées :
 *  - pMat : tMatrice, pointeur vers la matrce à libérer
 */
extern void MatLiberer(tMatrice *pMat);




#endif /* MATRICE_H */
