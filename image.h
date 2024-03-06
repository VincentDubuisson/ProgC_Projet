#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#ifndef IMAGE_H
#define IMAGE_H

typedef struct sImage *tImage;

/* --------------------------------- ImAllouer ---------------------------------
 * Alloue et initialise l’espace mémoire nécessaire pour stocker une image
 * contenant une matrice de NbLignes lignes et NbColonnes colonnes niveaux de gris
 * Entrées :
 *  - NbLignes : int, nombre de lignes
 *  - NbColonnes : int, nombre de colonnes
 * Sortie : tImage (struct sImage), image qui vient d'être alloué
 */
extern tImage ImAllouer(int NbLignes, int NbColonnes);

/* --------------------------------- ImLiberer ---------------------------------
 * Libère tout l’espace mémoire occupé par l’image d’adresse pIm
 * Entrées :
 *  - pIm : tImage, image à libérer
 */
extern void ImLiberer(tImage *pIm);

/* ---------------------------------- ImNbLig ----------------------------------
 * Retourne le nombre de lignes de l’image Im
 * Entrées :
 *  - Im : tImage, image
 * Sortie : int, nombre de ligne de l'image Im
 */
extern int ImNbLig(tImage Im);

/* ---------------------------------- ImNbCol ----------------------------------
 * Retourne le nombre de colonnes de l’image Im
 * Entrées :
 *  - Im : tImage, image
 * Sortie : int, nombre de colonnes de l'image Im
 */
extern int ImNbCol(tImage Im);

/* --------------------------------- ImNivGris ---------------------------------
 * Retourne la matrice des niveaux de gris de l’image Im.
 * Entrées :
 *  - Im : tImage, image
 * Sortie : tMatrice, matrice de niveau de gris de l'image
 */
extern tMatrice ImNivGris(tImage Im);

/* ---------------------------------- ImLire -----------------------------------
 * Lit l’image contenue dans le fichier de nom NomFichier au format PGM-ASCII
 * et retourne cette image ou NULL en cas de problème
 * Entrées :
 *  - NomFichier[] : char, nom du fichier à lire
 * Sortie : tImage , image des éléments du fichier NomFichier
 */
extern tImage ImLire(char NomFichier[]);

/* --------------------------------- ImEcrire ----------------------------------
 * Ecrit l’image Im dans le fichier de nom NomFichier au format PGM-ASCII
 * Entrées :
 *  - Im : tImage, image à écrire dans le fichier NomFichier
 *  - NomFichier[] : char, nom du fichier à écrire
 */
extern void ImEcrire(tImage Im, char NomFichier[]);

#endif /* IMAGE_H */
