#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "matrice.h"

typedef struct sImage *tImage;

struct sImage
{
  int NbLig ; // Nombre de lignes de l’image
  int NbCol ; // Nombre de colonnes de l’image
  tMatrice NivGris ; // Matrice des niveaux de gris de l’image
};

/* --------------------------------- ImAllouer ---------------------------------
 * Alloue et initialise l’espace mémoire nécessaire pour stocker une image
 * contenant une matrice de NbLignes lignes et NbColonnes colonnes niveaux de gris
 * Entrées :
 *  - NbLignes : int, nombre de lignes
 *  - NbColonnes : int, nombre de colonnes
 * Sortie : tImage (struct sImage), image qui vient d'être alloué
 */
tImage ImAllouer(int NbLignes, int NbColonnes) {
  // Allocation d'une matrice
  tMatrice Mat = MatAllouer(NbLignes, NbColonnes);

  // Allocation de l'image
  tImage Im = malloc(sizeof(struct sImage));
  if (Im == NULL) {
    MatLiberer(&Mat);
    return NULL;
  }

  // Initialisation de l'image
  Im->NbLig = NbLignes;
  Im->NbCol = NbColonnes;
  Im->NivGris = Mat;
  return Im;
}

/* --------------------------------- ImLiberer ---------------------------------
 * Libère tout l’espace mémoire occupé par l’image d’adresse pIm
 * Entrées :
 *  - pIm : tImage, image à libérer
 */
void ImLiberer(tImage *pIm) {

  if (pIm != NULL) {
    // Libération de la matrice NivGris
    MatLiberer(&(*pIm)->NivGris);
    // Libération de l'image
    free(*pIm);
    *pIm = NULL;
  }
}

/* ---------------------------------- ImNbLig ----------------------------------
 * Retourne le nombre de lignes de l’image Im
 * Entrées :
 *  - Im : tImage, image
 * Sortie : int, nombre de lignes de l'image Im
 */
int ImNbLig(tImage Im) {
  return Im->NbLig;
}

/* ---------------------------------- ImNbCol ----------------------------------
 * Retourne le nombre de colonnes de l’image Im
 * Entrées :
 *  - Im : tImage, image
 * Sortie : int, nombre de colonnes de l'image Im
 */
int ImNbCol(tImage Im) {
  return Im->NbCol;
}

/* --------------------------------- ImNivGris ---------------------------------
 * Retourne la matrice des niveaux de gris de l’image Im.
 * Entrées :
 *  - Im : tImage, image
 * Sortie : tMatrice, matrice de niveau de gris de l'image
 */
tMatrice ImNivGris(tImage Im) {
  return Im->NivGris;
}

/* ---------------------------------- ImLire -----------------------------------
 * Lit l’image contenue dans le fichier de nom NomFichier au format PGM-ASCII
 * et retourne cette image ou NULL en cas de problème
 * Entrées :
 *  - NomFichier[] : char, nom du fichier à lire
 * Sortie : tImage , image des éléments du fichier NomFichier
 */
tImage ImLire(char NomFichier[]) {

  FILE *fichier;
  char ch[3];
  int NbLigne;
  int NbColonne;

  // Ouverture du fichier en mode lecture de fichier texte
  fichier = fopen(NomFichier, "rt");
  if (fichier == NULL) {
      printf("Impossible d'ouvrir le fichier %s\n", NomFichier);
      return NULL;
  }

  // Lecture de la signature
  fscanf(fichier, "%3s", ch);
  if (ch[0] != 'P' && ch[1] != '2') {
    return NULL;
  }

  // Lecture du nombre de colonnes et de lignes
  fscanf(fichier, "%d", &NbColonne);
  fscanf(fichier, "%d", &NbLigne);

  int NivMax = 0;
  // Lecture du niveau de gris maximal
  fscanf(fichier, "%d", &NivMax);

  // Aloocation de l'image à retourner
  tImage Im = ImAllouer(NbLigne, NbColonne);
  tMatrice NivGris = Im->NivGris;

  // Lecture des niveaux de gris
  for (int i = 0; i < NbLigne; i++) {
    for (int j = 0; j < NbColonne; j ++) {
      int pixel;
      fscanf(fichier, "%d", &pixel);
      NivGris[i][j] = pixel;
    }
  }
  fclose(fichier);

  // Initialisation des éléments de l'image
  Im->NbLig = NbLigne;
  Im->NbCol = NbColonne;
  Im->NivGris = NivGris;

  return Im;
}

/* --------------------------------- ImEcrire ----------------------------------
 * Ecrit l’image Im dans le fichier de nom NomFichier au format PGM-ASCII
 * Entrées :
 *  - Im : tImage, image à écrire dans le fichier NomFichier
 *  - NomFichier[] : char, nom du fichier à écrire
 */
void ImEcrire(tImage Im, char NomFichier[]) {

  FILE *fichier;
  int NbColonne = Im->NbCol;
  int NbLigne = Im->NbLig;
  tMatrice NivGris = Im->NivGris;
  int NivMax = 255;

  // Ouverture du fichier en mode écriture de fichier texte
  fichier = fopen(NomFichier, "wt");
  if (fichier == NULL) {
      printf("Impossible d'ouvrir le fichier %s\n", NomFichier);
      perror NULL;
  }

  // Ecriture de la signature
  fprintf(fichier, "P2\n");

  // Ecriture du nb de colonnes et de lignes
  fprintf(fichier, "%d ", NbColonne);
  fprintf(fichier, "%d\n", NbLigne);

  // Ecriture du niveau de gris maximal
  fprintf(fichier, "%d\n", NivMax);

  // Ecriture des niveaux de gris
  Im = ImAllouer(NbLigne, NbColonne);
  for (int i = 0; i < NbLigne; i++) {
    for (int j = 0; j < NbColonne; j ++) {
      int pixel = NivGris[i][j];
      if (pixel > NivMax) {
        pixel = NivMax;
      }
      fprintf(fichier, "%d ", pixel);
    }
    fprintf(fichier, "\n");
  }

  fclose(fichier);
}
