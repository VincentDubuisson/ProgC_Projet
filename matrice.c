#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

/* -------------------------------- MatAllouer ---------------------------------
 * Alloue et initialise l’espace mémoire nécessaire pour stocker une matrice
 * de NbLig lignes et NbCol colonnes
 * Entrées :
 *  - NbLig : int, nombre de lignes
 *  - NbCol : int, nombre de colonnes
 * Sortie : tMatrice (unsigned char **), matrice qui vient d'être alloué
 */
tMatrice MatAllouer(int NbLig, int NbCol) {
  // Allocation du tableau contenant les éléments
  unsigned char *tabElts;
  tabElts = malloc(NbLig*NbCol*sizeof(unsigned char));
  if (tabElts == NULL) {
      return NULL;
  }

  // Allocation du tableau des pointeurs
  tMatrice Mat;
  Mat = malloc(NbLig*sizeof(unsigned char*));
  if (Mat == NULL) {
    free(tabElts);
    return NULL;
  }

  // Remplissage du tableau des pointeurs avec les adresses de début des lignes
  for (int i = 0, j = 0; i < NbLig; i++, j += NbCol) {
    Mat[i] = &(tabElts[j]);
  }

  return Mat;
}

/* --------------------------------- MatLire -----------------------------------
 * Ecris la matrice de NbLig lignes et NbCol colonnes ainsi que tout ses éléments
 * entrés par l'utilisateur
 * Entrées :
 *  - pNbLig : int *, nombre de lignes
 *  - pNbCol : int *, nombre de colonnes
 * Sortie : tMatrice, matrice | Initialisation de pNbLig et pNbCol
 */
tMatrice MatLire(int *pNbLig, int *pNbCol) {
  // Lecture du nombre de lignes et de colonnes
  int NbLig, NbCol;
  printf("Entrez le nombre de ligne de la matrice: ");
  scanf("%d", &NbLig);
  printf("Entrez le nombre de colonne de la matrice: ");
  scanf("%d", &NbCol);

  // Allocation de la matrice
  tMatrice Mat;
  Mat = MatAllouer(NbLig, NbCol);

  // Initialisation des éléments de la matrice ainsi que de pNbLig et pNbCol
  for (int i = 0; i < NbLig; i++) {
    for (int j = 0; j < NbCol; j++) {
      printf("Entrez l'éléments %d de la ligne %d: ", j+1, i+1);
      scanf("%hhu", &Mat[i][j]);
      *pNbCol += 1;
    }
    *pNbLig += 1;
  }
  *pNbCol /= *pNbLig;

  return Mat;
}

/* -------------------------------- MatAfficher --------------------------------
 * Affiche à l’écran le contenu de la matrice passée en paramètre
 * Entrées :
 *  - Mat : unsigned char **, matrice à afficher
 *  - NbLig : int, nombre de lignes
 *  - NbCol : int, nombre de colonnes
 * Sortie : printf (affichage)
 */
void MatAfficher(tMatrice Mat, int NbLig, int NbCol) {

  printf("Matrice: \n");
  // Parcours des éléments de la matrice
  for (int i = 0; i < NbLig; i++) {
    for (int j = 0; j < NbCol; j++) {
      printf("%d ", Mat[i][j]);
    }
    printf("\n");
  }
}

/* --------------------------------- MatCopier ---------------------------------
 * Réalise une copie de la matrice Mat de taille NbLig×NbCol
 * Entrées :
 *  - Mat : unsigned char **, matrice à copier
 *  - NbLig : int, nombre de lignes
 *  - NbCol : int, nombre de colonnes
 * Sortie : tMatrice, copie de la matrice Mat
 */
tMatrice MatCopier(tMatrice Mat, int NbLig, int NbCol) {
  // Allocation de la copie
  tMatrice MatCopie = MatAllouer(NbLig, NbCol);
  if (MatCopie == NULL) {
      return NULL;
  }

  // Copie des éléments 1 par 1
  for (int i = 0; i < NbLig; i++) {
      for (int j = 0; j < NbCol; j++) {
          MatCopie[i][j] = Mat[i][j];
      }
  }

  return MatCopie;
}

/* --------------------------------- MatLiberer --------------------------------
 * Libère tout l’espace mémoire occupé par la matrice d’adresse pMat
 * Entrées :
 *  - pMat : tMatrice, pointeur vers la matrce à libérer
 */
void MatLiberer(tMatrice *pMat) {

  if (*pMat != NULL) {
    // Libération du tableau des éléments
    free(**pMat);
    // Libération du tableau  de pointeurs
    free(*pMat);
    *pMat = NULL;
  }
}
