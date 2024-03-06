#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image.h"
#include "matrice.h"
#include "svg.h"
#include "polygone.h"
#include "contour.h"

int main(int argc, char *argv[]) {

  // Vérification du nombre d'arguments
  if (argc != 5) {
    perror("Nombre de paramètre incorrect!");
    return 1;
  }

  tStyle Style = {"blue", 0.125, 1, "none", 0, "red", 0.125};
  // Lecture de l'image PGM
  tImage Im = ImLire(argv[1]);
  // Création du tableau de coordonnées
  unsigned char *Etiquettes = malloc(ImNbCol(Im) * sizeof(unsigned char));
  int NbRegions = ContourEtiquettes(argv[1], Etiquettes);

  // Ecriture des polygones dans le fichier texte
  ContourExtraire(argv[1], Etiquettes, NbRegions, argv[3]);

  // Ecriture (dessin) des polygone de contour de régions dans le fichier SVG
  ContourEcrireSurImageSvg(argv[3], argv[2], ImNbCol(Im), ImNbLig(Im), &Style, argv[4]);

  free(Etiquettes);
  ImLiberer(&Im);
  return 0;
}
