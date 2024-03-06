#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image.h"
#include "matrice.h"
#include "svg.h"
#include "polygone.h"

#ifndef CONTOUR_H
#define CONTOUR_H

/* --------------------------- ContourEtiquettes -------------------------------
 * Extrait les étiquettes des régions d’une image d’étiquettes stockée dans un
 * fichier au format PGM de nom NomFichEtiquettes, les stocke dans le tableau
 * Etiquettes et retourne le nombre d’étiquettes trouvées
 * Entrées :
 *  - NomFichEtiquettes[] : char, nom du fichier au format PGM
 *  - Etiquettes[] : unsigned char, tableau des étiquettes des régions
 * Sortie : int, nombre d'étiquettes (nb de régions)
 */
extern int ContourEtiquettes(char NomFichEtiquettes[], unsigned char Etiquettes[]);

/* ----------------------------- ContourSuivi ----------------------------------
 * Effectue, dans l’image d’étiquettes Im, le suivi du contour d’une région
 * d’étiquette Etiquette et retourne les pixels du contour de la région sous
 * la forme d’un polygone
 * Entrées :
 *  - Im : tImage, image d'étiquettes
 *  - Etiquette : unsigned char, étiquette dont on doit faire le contour
 * Sortie : tPolygone, polygone des pixles du contour de la region Etiquette
 */
extern tPolygone ContourSuivi(tImage Im, unsigned char Etiquette);

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
extern void ContourExtraire(char NomFichEtiquettes[], unsigned char Etiquettes[], int NbRegions, char NomFichContours[]);

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
extern void ContourEcrireSurImageSvg(char NomFichContours[], char NomFichImage[], int NbCol, int NbLig, tStyle *pStyle, char NomFichSVG[]);

#endif /* CONTOUR_H */
