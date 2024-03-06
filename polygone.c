#include <stdio.h>
#include <stdlib.h>
#include "polygone.h"
#include "svg.h"

// Sommet d’un polygone
struct sSommet
{
  int x, y; // Coordonnées entières du sommet
  struct sSommet *pSuivant; // Adresse du sommet suivant
};

// Descripteur du polygone pointant vers une liste simplement chaînée de sommets
struct sPolygone
{
  int NbSommets ; // Nombre de sommets
  struct sSommet *PremierSommet; // Adresse du premier sommet
};

/* -------------------------------- PolygoneCreer ------------------------------
 * Crée un polygone vide
 * Sortie : tPolygone (struct sPolygone), polygone qui vient d'être alloué
 */
tPolygone PolygoneCreer(void) {

    // Allocation de la mémoire sPolygone
    tPolygone Poly = malloc(sizeof(struct sPolygone));

    // Vérification que l'allocation a fonctionné
    if (Poly == NULL) {
        perror("Erreur de création du polygone");
        return NULL;
    }

    // Initialisation du nombre de sommets et de l'adresse du premier sommet
    Poly->NbSommets = 0;
    Poly->PremierSommet = NULL;

    return Poly;
}

/* ----------------------------- PolygoneNbSommets -----------------------------
 * Retourne le nombre de sommets de Poly
 * Entrées :
 *  - Poly : tPolygone, polygone à qui on retourne le nombre de sommets
 * Sortie : int, nombre de sommets de Poly
 */
int PolygoneNbSommets(tPolygone Poly) {
  return Poly->NbSommets;
}

/* ------------------------------- AllouerSommet -------------------------------
 * Alloue un sommet
 * Sortie : struct sSommet, sommet qui vient d'être alloué
 */
static struct sSommet* AllouerSommet() {
  // Allocation de mémoire pour le nouveau sommet
  struct sSommet *pNouv = malloc(sizeof(struct sSommet));

  // Vérification de l'allocation
  if (pNouv == NULL) {
      perror("Erreur de création du sommet");
      return NULL;
  }
  return pNouv;
}

/* ------------------------- PolygoneAjouterSommetEnFin ------------------------
 * Ajoute un sommet de coordonnées (x,y) à la fin de Poly
 * Entrées :
 *  - x : int, coordonées x du sommet à ajouter
 *  - y : int, coordonées y du sommet à ajouter
 *  - Poly : tPolygone , polygone à qui on ajoute le sommet
 */
void PolygoneAjouterSommetEnFin(int x, int y, tPolygone Poly) {
  // Allocation de mémoire pour le nouveau sommet
  struct sSommet *pNouv = AllouerSommet();

  // Initialisation du sommet
  pNouv->x = x;
  pNouv->y = y;
  pNouv->pSuivant = NULL;

  // Si Poly est vide, le nouveau sommet devient le premier sommet
  if (Poly->PremierSommet == NULL)
    Poly->PremierSommet = pNouv;
  // Sinon, on cherche le dernier sommet
  else {
    struct sSommet* pDer = Poly->PremierSommet;
    // Tant qu'on arrive pas au dernier sommet
    while (pDer->pSuivant != NULL) {
      pDer = pDer->pSuivant;
    }
    pDer->pSuivant = pNouv;
  }
  // Incrémente le nombre de sommet
  Poly->NbSommets++;
}

/* ------------------------ PolygoneAjouterSommetEnDebut -----------------------
 * Ajoute un sommet de coordonnées (x,y) au début de Poly
 * Entrées :
 *  - x : int, coordonées x du sommet à ajouter
 *  - y : int, coordonées y du sommet à ajouter
 *  - Poly : tPolygone , polygone à qui on ajoute le sommet
 */
void PolygoneAjouterSommetEnDebut(int x, int y, tPolygone Poly) {
  // Allocation de mémoire pour le nouveau sommet
  struct sSommet *pNouv = AllouerSommet();

  // Initialisation du sommet
  pNouv->x = x;
  pNouv->y = y;
  pNouv->pSuivant = Poly->PremierSommet;
  // Le nouveau sommet devient le premier sommet
  Poly->PremierSommet = pNouv;
  Poly->NbSommets++;
}

/* ------------------------ PolygoneAjouterSommetEnIeme ------------------------
 * Ajoute un sommet de coordonnées (x,y) à la ieme position des sommets de Poly
 * Entrées :
 *  - x : int, coordonées x du sommet à ajouter
 *  - y : int, coordonées y du sommet à ajouter
 *  - Poly : tPolygone , polygone à qui on ajoute le sommet
 */
void PolygoneAjouterSommetEnIeme(int x, int y, int i, tPolygone Poly) {
  // Vérification de la compatibilité de i
  if (i < 0 || i > Poly->NbSommets) {
    perror("L'indice est hors des données actuelles");
    return;
  }

  // Si le sommet est en début ou fin
  if (i == 0) {
    PolygoneAjouterSommetEnDebut(x, y, Poly);
    return;
  }
  if (i == Poly->NbSommets) {
    PolygoneAjouterSommetEnFin(x, y, Poly);
    return;
  }
  // Sinon, cas général :

  // Allocation de mémoire pour le nouveau sommet
  struct sSommet *pNouv = AllouerSommet();

  // Initialisation du sommet
  pNouv->x = x;
  pNouv->y = y;

  // On cherche le sommet en i-1ème position (précédant i)
  struct sSommet *pPrec = Poly->PremierSommet;
  int Indice = 0;
  while (Indice < i-1) {
    pPrec = pPrec->pSuivant;
    Indice++;
  }
  pNouv->pSuivant = pPrec->pSuivant;
  pPrec->pSuivant = pNouv;
  Poly->NbSommets++;
}

/* ----------------------------- PolygoneAfficher ------------------------------
 * Affiche à l’écran les coordonnées des sommets du polygone à n sommets Poly
 * Entrées :
 *  - Poly : tPolygone , polygone qu'on affiche
 */
void PolygoneAfficher(tPolygone Poly) {
  // Affichage du nombre de sommets
  printf("%d\n", Poly->NbSommets);

  // Parcours des sommets et affichage des coordonnées
  struct sSommet *pSommet = Poly->PremierSommet;
  while (pSommet != NULL) {
    printf("%d %d\n", pSommet->x, pSommet->y);
    pSommet = pSommet->pSuivant;
  }
}

/* --------------------------- PolygoneSommetIeme ------------------------------
 * Délivre en sortie les coordonnées du sommet qui se trouve à la ie position
 * Entrées :
 *  - Poly : tPolygone , polygone à qui on ajoute le sommet
 *  - i : int , indice de la position du sommet
 *  - px : int * , coordonnée x du sommet
 *  - py : int * , coordonnée y du sommet
 */
void PolygoneSommetIeme(tPolygone Poly, int i, int *px, int *py) {
  // Vérification de la validité de i
  if (i < 0 || i > Poly->NbSommets-1) {
    perror("Indice de sommet invalide");
    return;
  }

  // On cherche le sommet en ième position
  struct sSommet *pIeme = Poly->PremierSommet;
  int Indice = 0;
  while (Indice < i) {
    pIeme = pIeme->pSuivant;
    Indice++;
  }
  // Affectation au pointeurs des valeurs des coordonées du sommet
  *px = pIeme->x;
  *py = pIeme->y;
}

/* ------------------------ PolygoneSommetSupprimerIeme ------------------------
 * Supprime le sommet qui se trouve à la ie position de Poly
 * Entrées :
 *  - i : int , indice du sommet à supprimer
 *  - Poly : tPolygone, polygone à qui on doit supprmer le sommet
 */
void PolygoneSommetSupprimerIeme(int i, tPolygone Poly) {
  // Vérification de la validité de i
  if (i < 0 || i >= Poly->NbSommets-1) {
        perror("Indice de sommet invalide");
        return;
  }

  // On cherche le sommet en ième position
  struct sSommet *pIeme = Poly->PremierSommet;
  struct sSommet *pPrec;
  int Indice = 0;
  while (Indice < i) {
    pPrec = pIeme;
    pIeme = pIeme->pSuivant;
    Indice++;
  }

  // Si c'est le premier sommet à supprimer
  if (i == 0)
    Poly->PremierSommet = pIeme->pSuivant;
  // Si c'est le dernier sommet à supprimer
  else if (i == Poly->NbSommets - 1)
    pPrec->pSuivant = NULL;
  else
    pPrec->pSuivant = pIeme->pSuivant;

  // Libérer la mémoire du sommet supprimé
  free(pIeme);

  Poly->NbSommets--;
}

/* ------------------------------ PolygoneLiberer ------------------------------
 * Libère la mémoire occupée par le polygone Poly
 * Entrées :
 *  - Poly : tPolygone, polygone dont on libère la mémoire alloué
 */
void PolygoneLiberer(tPolygone Poly) {
  // Initialisation d'un sommet au premier sommet du polygone, ainsi qu'un
  // sommet intermédiaire
  struct sSommet *pIeme = Poly->PremierSommet;
  struct sSommet *pSuiv;
  // On libère la mémoire occupé par chaque sommet en commençant par le premier
  while (pIeme != NULL) {
    pSuiv = pIeme->pSuivant;
    free(pIeme);
    pIeme = pSuiv;
  }
  // On finit par libérer le polygone
  free(Poly);
}

/* ------------------------------- PolygoneLiref -------------------------------
 * Lit dans le fichier de texte d’identificateur f les coordonnées des sommets
 * d’un polygone et retourne le polygone
 * Entrées :
 *  - f : FILE *, identificateur du fichier à lire
 * Sortie : tPolygone, polygone lu dans le fichier
 */
tPolygone PolygoneLiref(FILE *f) {

  int NbSommets, x, y;
  tPolygone Poly;

  // Lecture du nombre de sommets
  if (fscanf(f, "%d", &NbSommets) < 0) {
    perror("Erreur de lecture du nombre de sommets");
    return NULL;
  }

  // Création du polygone
  Poly = PolygoneCreer();

  // Lecture des sommets
  for (int i = 0; i < NbSommets; i++) {
    fscanf(f, "%d %d", &x, &y);
    PolygoneAjouterSommetEnFin(x, y, Poly);
  }
  return Poly;
}


/* ------------------------------ PolygoneEcriref ------------------------------
 * Ecrit dans le fichier de texte d’identificateur f les coordonnées des sommets
 * du polygone Poly sous le même format que celui de la fonction PolygoneAfficher
 * Entrées :
 *  - Poly : tPolygone, polygone à écrire
 *  - f : FILE *, identificateur du fichier à lire
 */
void PolygoneEcriref(tPolygone Poly, FILE *f) {

  int NbSommets = Poly->NbSommets;
  int x, y;

  // Ecriture du nombre de sommets
  fprintf(f, "%d\n", NbSommets);

  // Ecriture des sommets
  for (int i = 0; i < NbSommets; i++) {
    PolygoneSommetIeme(Poly, i, &x, &y);
    fprintf(f, "%d %d\n", x, y);
  }
}

/* ---------------------------------- TabX -------------------------------------
 * Créer un tableau contenant les coordonnées x du polygone Poly
 * Entrées :
 *  - Poly : tPolygone, polygone
 *  - NbSommets : int, nombre de sommets dans Poly
 * Sortie : float*, tableau des coordonnées x
 */
static float* TabX(tPolygone Poly, int NbSommets) {
  // Allocation du tableau
  float* x = malloc(NbSommets * sizeof(float));
  struct sSommet *pIeme = Poly->PremierSommet;
  int Indice = 0;

  // Initialisation des éléments du tableau
  while (Indice < NbSommets) {
    x[Indice] = pIeme->x;
    pIeme = pIeme->pSuivant;
    Indice++;
  }
  return x;
}

/* ---------------------------------- TabY -------------------------------------
 * Créer un tableau contenant les coordonnées y du polygone Poly
 * Entrées :
 *  - Poly : tPolygone, polygone
 *  - NbSommets : int, nombre de sommets dans Poly
 * Sortie : float*, tableau des coordonnées y
 */
static float* TabY(tPolygone Poly, int NbSommets) {
  // Allocation du tableau
  float* y = malloc(NbSommets * sizeof(float));
  struct sSommet *pIeme = Poly->PremierSommet;
  int Indice = 0;

  // Initialisation des éléments du tableau
  while (Indice < NbSommets) {
    y[Indice] = pIeme->y;
    pIeme = pIeme->pSuivant;
    Indice++;
  }
  return y;
}

/* ---------------------------- PolygoneEcrireSvg ------------------------------
 * Ecrit le polygone Poly dans le fichier au format SVG d’identificateur
 * IdFichSVG avec le style d’adresse pStyle
 * Entrées :
 *  - Poly : tPolygone, polygone
 *  - pStyle : tStyle *, style de POLYGONE_H
 *  - IdFichSVG : FILE *, identificateur du fichier SVG
 */
void PolygoneEcrireSvg(tPolygone Poly, tStyle *pStyle, FILE *IdFichSVG) {

  int NbSommets = Poly->NbSommets;
  float *x = TabX(Poly, NbSommets);
  float *y = TabY(Poly, NbSommets);

  // Ecriture du polygone dans le fichier SVG
  SvgEcrirePolygone(IdFichSVG, x, y, NbSommets, pStyle);
  // Libération des tableaux de coordonnées
  free(x);
  free(y);
}
