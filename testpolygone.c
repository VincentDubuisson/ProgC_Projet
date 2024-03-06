#include <stdio.h>
#include <stdlib.h>
#include "polygone.h"
#include "svg.h"


int main(void) {

  tPolygone Poly;

  // Création du polygone Poly
  Poly = PolygoneCreer();

  // Ajout de sommet à Poly
  PolygoneAjouterSommetEnFin(2, 5, Poly);
  PolygoneAjouterSommetEnFin(4, 7, Poly);
  PolygoneAjouterSommetEnIeme(1, 2, 1, Poly);
  PolygoneAjouterSommetEnDebut(5, 7, Poly);
  PolygoneAfficher(Poly);

  // Suppression d'un sommet de Poly
  PolygoneSommetSupprimerIeme(2, Poly);
  PolygoneAfficher(Poly);

  // Ecriture de Poly dans le fichier testpolygone.txt
  FILE *fichier = fopen("testpolygone.txt", "wt");
  PolygoneEcriref(Poly, fichier);
  fclose(fichier);
  PolygoneLiberer(Poly);

  // Lecture de Poly dans le fichier testpolygone.txt
  fichier = fopen("testpolygone.txt", "rt");
  Poly = PolygoneLiref(fichier);
  PolygoneAfficher(Poly);
  fclose(fichier);

  // Création du fichier SVG testpolygone.svg, écriture (dessin) de Poly
  FILE *IdFichSVG = SvgCreer("testpolygone.svg", 10, 10);
  tStyle Style={"blue",0.125,1,"none",0,"red",0.125};
  PolygoneEcrireSvg(Poly, &Style, IdFichSVG);
  SvgFermer(IdFichSVG);
  PolygoneLiberer(Poly);

  return 0;
}
