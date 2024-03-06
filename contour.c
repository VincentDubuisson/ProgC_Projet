#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image.h"
#include "matrice.h"
#include "svg.h"
#include "polygone.h"


/* --------------------------- EstDansEtiquettes -------------------------------
 * Vérifie si Pixel est dans le tableau Etiquettes
 * Entrées :
 *  - Etiquettes[] : unsigned char, tableau des étiquettes des régions
 *  - Pixel : int, étiquette à vérifier
 *  - NbEtiquettes : int, nombre d'étiquettes dans Etiquettes
 * Sortie : bool
 */
static bool EstDansEtiquettes(unsigned char Etiquettes[], int Pixel, int NbEtiquettes) {

  int i = 0;
  // Parcours du tableau Etiquettes
  while (i < NbEtiquettes) {
    if (Pixel == Etiquettes[i])
      return true;
    i++;
  }
  return false;
}

/* --------------------------- ContourEtiquettes -------------------------------
 * Extrait les étiquettes des régions d’une image d’étiquettes stockée dans un
 * fichier au format PGM de nom NomFichEtiquettes, les stocke dans le tableau
 * Etiquettes et retourne le nombre d’étiquettes trouvées
 * Entrées :
 *  - NomFichEtiquettes[] : char, nom du fichier au format PGM
 *  - Etiquettes[] : unsigned char, tableau des étiquettes des régions
 * Sortie : int, nombre d'étiquettes (nb de régions)
 */
int ContourEtiquettes(char NomFichEtiquettes[], unsigned char Etiquettes[]) {

  tImage Im = ImLire(NomFichEtiquettes); // Lecture du fichier NomFichEtiquettes
  tMatrice Mat = ImNivGris(Im); // Récupération de la matrice de l'image
  int NbEtiquettes = 0; // Nombre d'étiquettes différentes (nb de régions)

  // Parcours de l'image Im
  for (int i = 0; i < ImNbLig(Im); i++) {
    for (int j = 0; j < ImNbCol(Im); j++) {
      int Pixel = Mat[i][j];
      // Si le Pixel est une étiquettes non référencié, on incrémente le compteur
      if (Pixel != 0 && !(EstDansEtiquettes(Etiquettes, Pixel, NbEtiquettes))) {
        Etiquettes[NbEtiquettes] = Pixel;
        NbEtiquettes++;
      }
    }
  }
  ImLiberer(&Im);

  return NbEtiquettes;
}

/* -------------------------------- TabXY --------------------------------------
 * Ajoute au tableau Tab de coordonées du contour de la région d'étiquettes, les
 * coordonnées x et y
 * Entrées :
 *  - Tab : int **, tableau de coordonnées
 *  - NbElts : int *, nombre d'éléments du tableau Tab
 *  - x : int, coordonnées x
 *  - y : int, coordonnées y
 */
static void TabXY(int** Tab, int* NbElts, int x, int y) {

  (*Tab)[*NbElts] = x;
  (*Tab)[*NbElts+1] = y;
  *NbElts += 2;
}

/* ----------------------------- ContourSuivi ----------------------------------
 * Effectue, dans l’image d’étiquettes Im, le suivi du contour d’une région
 * d’étiquette Etiquette et retourne les pixels du contour de la région sous
 * la forme d’un polygone
 * Entrées :
 *  - Im : tImage, image d'étiquettes
 *  - Etiquette : unsigned char, étiquette dont on doit faire le contour
 * Sortie : tPolygone, polygone des pixles du contour de la region Etiquette
 */
tPolygone ContourSuivi(tImage Im, unsigned char Etiquette) {

  int xDep = 0, yDep = 0; // Coordonnées du pixel de départ | x = colonne, y = ligne
  int xTortue, yTortue; // Coordonnées de la position de la tortue
  bool Fin = false; // Boolean indiquant si l'algorithme de la tortue est fini
  bool PremierPixel = false; //Boolean indiquant si on a trouvé le premier pixel
  tMatrice Mat = ImNivGris(Im); // Récupération de la matrice de l'image
  tPolygone Poly = PolygoneCreer(); // Création du polygone qui fait le contour
  int Direction = 3; // Direction du déplacement | 0 = horizontal
  int NbElts = 0; // Nombre d'éléments du tableau de coordonnées

  // Allocation du tableau de coordonnées du contour
  // Le tableau est de la forme suivante: [x1, y1, x2, y2, ...]
  int *TabCoord = malloc(ImNbLig(Im) * ImNbCol(Im) * sizeof(int));
  if (TabCoord == NULL) {
    perror("Erreur d'allocation du tableau TabCoord\n");
    return NULL;
  }

  // ALGORITHME DE LA TORTUE
  // Détection du premier pixel de l'étiquette
  for (int i = 0; i < ImNbLig(Im) && !PremierPixel; i++) {
    for (int j = 0; j < ImNbCol(Im) && !PremierPixel; j++) {
      if (Mat[i][j] == Etiquette) {
        yDep = i;
        xDep = j;
        PremierPixel = true;
      }
    }
  }
  // On ajoute le premier Pixel au tableau de coordonées du contour
  TabXY(&TabCoord, &NbElts, xDep, yDep);
  xTortue = xDep;
  yTortue = yDep - 1;


  // Déplacement de la tortue
  while (!Fin) {

    switch (Direction) {
      case 0:
        // S’arrêter si le pixel courant est celui du départ
        if (xTortue == xDep && yTortue == yDep) {
          Fin = true;
        // Si le pixel courant est dans la région
        } else if (Mat[yTortue][xTortue] == Etiquette) {
          TabXY(&TabCoord, &NbElts, xTortue, yTortue);
          yTortue--;
          Direction = 3;
        // Sinon (le pixel courant est à l’extérieur de la région)
        } else {
          yTortue++;
          Direction = 1;
        }
        break;

      case 1:
        if (xTortue == xDep && yTortue == yDep) {
          Fin = true;
        } else if (Mat[yTortue][xTortue] == Etiquette) {
          TabXY(&TabCoord, &NbElts, xTortue, yTortue);
          xTortue++;
          Direction = 0;
        } else {
          xTortue--;
          Direction = 2;
        }
        break;

      case 2:
        if (xTortue == xDep && yTortue == yDep) {
          Fin = true;
        } else if (Mat[yTortue][xTortue] == Etiquette) {
          TabXY(&TabCoord, &NbElts, xTortue, yTortue);
          yTortue++;
          Direction = 1;
        } else {
          yTortue--;
          Direction = 3;
        }
        break;

      case 3:
        if (xTortue == xDep && yTortue == yDep) {
          Fin = true;
        } else if (Mat[yTortue][xTortue] == Etiquette) {
          TabXY(&TabCoord, &NbElts, xTortue, yTortue);
          xTortue--;
          Direction = 2;
        } else {
          xTortue++;
          Direction = 0;
        }
        break;
    }
  }

  // Recherche de doublons
  for (int i = 0; i < NbElts; i += 2) {
    for (int j = i + 2; j < NbElts; j += 2) {
      if (TabCoord[i] == TabCoord[j] && TabCoord[i+1] == TabCoord[j+1]) {
        // Le couple (j, j+1) est un doublon
        for (int k = j; k < NbElts-2; k += 2) {
          TabCoord[k] = TabCoord[k+2];
          TabCoord[k+1] = TabCoord[k+3];
        }
        NbElts -= 2;
        j -= 2;
      }
    }
    PolygoneAjouterSommetEnFin(TabCoord[i], TabCoord[i+1], Poly);
  }
  free(TabCoord);
  //FIN ALGO TORTUE

  return Poly;
}

/* ---------------------------- ContourExtraire --------------------------------
 * Localise les contours des régions, dont les NbRegions étiquettes sont
 * stockées dans le tableau Etiquette, dans l’image d’étiquettes stockée dans
 * le fichier au format PGM NomFichEtiquettes et écrit leurs coordonnées dans
 * le fichier de texte NomFichContours
 * Entrées :
 *  - NomFichEtiquettes[] : char, nom du fichier PGM où récupérer les coordonées
 *  - Etiquettes[] : unsigned char, tableau des coordonées du contour
 *  - NbRegions : int, nombre de régions
 *  - NomFichContours[] : char, nom du fichier texte où écrire les coordonées
 */
void ContourExtraire(char NomFichEtiquettes[], unsigned char Etiquettes[], int NbRegions, char NomFichContours[]) {

  // Lecture du fichier PGM
  tImage Im = ImLire(NomFichEtiquettes);
  tPolygone Poly;

  // Ouverture du fichier texte en écriture
  FILE *f = fopen(NomFichContours, "wt");

  fprintf(f, "%d\n", NbRegions);

  // Ecriture des polygones de contour
  for (int i = 0; i < NbRegions; i++) {
    Poly = ContourSuivi(Im, Etiquettes[i]);
    PolygoneEcriref(Poly, f);
    PolygoneLiberer(Poly);
  }

  ImLiberer(&Im);
  fclose(f);
}

/* ------------------------ ContourEcrireSurImageSvg ---------------------------
 * Ecrit un ensemble de contours stocké dans le fichier NomFichContours sur une
 * image stockée au format PNG dans le fichier NomFichImage, de largeur NbCol
 * et de hauteur NbLig, avec le style d’adresse pStyle, dans le fichier au
 * format SVG NomFichSVG.
 * Entrées :
 *  - NomFichContours[] : char, nom du fichier texte où écrire les coordonées
 *  - NomFichImage[] : char, nom du fichier PNG
 *  - NbCol : int, largeur du fichier SVG
 *  - NbLig : int, hauteur du fichier SVG
 *  - pStyle : tStyle *, style du polygone
 *  - NomFichSVG[] : char, nom du fichier SVG où dessiner les polygones
 */
void ContourEcrireSurImageSvg(char NomFichContours[], char NomFichImage[], int NbCol, int NbLig, tStyle *pStyle, char NomFichSVG[]) {
  // Création du tableau de coordonnées
  unsigned char *Etiquettes = malloc(NbCol * sizeof(unsigned char));
  tPolygone Poly;
  int NbRegions;

  // Création du fichier SVG
  FILE *f = SvgCreer(NomFichSVG, NbCol, NbLig);

  // Ecriture de l'image NomFichImage dans le fichier SVG d'identificateur f
  SvgEcrireImage(f, NomFichImage, NbCol, NbLig);

  // Ouverture du fichier texte en lecture et lecture du nombre de régions
  FILE *f1 = fopen(NomFichContours, "rt");
  fscanf(f1, "%d", &NbRegions);

  // Ecriture des polygones de contours
  for (int i = 0; i < NbRegions; i++) {
    Poly = PolygoneLiref(f1);
    PolygoneEcrireSvg(Poly, pStyle, f);
    PolygoneLiberer(Poly);
  }

  // Libération des espaces mémoires alloués et fermuture du fichier SVG
  free(Etiquettes);
  SvgFermer(f);

}
