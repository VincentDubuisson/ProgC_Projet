#include <stdio.h>
#include <stdlib.h>
#include "svg.h"

#ifndef POLYGONE_H
#define POLYGONE_H

typedef struct sSommet *tSommet;
typedef struct sPolygone *tPolygone;

/* -------------------------------- PolygoneCreer ------------------------------
 * Crée un polygone vide
 * Sortie : tPolygone (struct sPolygone), polygone qui vient d'être alloué
 */
extern tPolygone PolygoneCreer(void);

/* ----------------------------- PolygoneNbSommets -----------------------------
 * Retourne le nombre de sommets de Poly
 * Entrée :
 *  - tPolygone : polygone
 * Sortie : int, nombre de sommets de Poly
 */
extern int PolygoneNbSommets(tPolygone Poly);

/* ------------------------- PolygoneAjouterSommetEnFin ------------------------
 * Ajoute un sommet de coordonnées (x,y) à la fin de Poly
 * Entrées :
 *  - x : int, coordonées x du sommet à ajouter
 *  - y : int, coordonées y du sommet à ajouter
 *  - Poly : tPolygone , polygone à qui on ajoute le sommet
 */
extern void PolygoneAjouterSommetEnFin(int x, int y, tPolygone Poly);

/* ------------------------ PolygoneAjouterSommetEnDebut -----------------------
 * Ajoute un sommet de coordonnées (x,y) au début de Poly
 * Entrées :
 *  - x : int, coordonées x du sommet à ajouter
 *  - y : int, coordonées y du sommet à ajouter
 *  - Poly : tPolygone , polygone à qui on ajoute le sommet
 */
extern void PolygoneAjouterSommetEnDebut(int x, int y, tPolygone Poly);

/* ------------------------ PolygoneAjouterSommetEnIeme ------------------------
 * Ajoute un sommet de coordonnées (x,y) à la ieme position des sommets de Poly
 * Entrées :
 *  - x : int, coordonées x du sommet à ajouter
 *  - y : int, coordonées y du sommet à ajouter
 *  - Poly : tPolygone , polygone à qui on ajoute le sommet
 */
extern void PolygoneAjouterSommetEnIeme(int x, int y, int i, tPolygone Poly);

/* ----------------------------- PolygoneAfficher ------------------------------
 * Affiche à l’écran les coordonnées des sommets du polygone à n sommets Poly
 * Entrée :
 *  - Poly : tPolygone , polygone qu'on affiche
 */
extern void PolygoneAfficher(tPolygone Poly);

/* --------------------------- PolygoneSommetIeme ------------------------------
 * Délivre en sortie les coordonnées du sommet qui se trouve à la ie position
 * Entrées :
 *  - Poly : tPolygone , polygone à qui on ajoute le sommet
 *  - i : int , indice de la position du sommet
 *  - px : int * , coordonnée x du sommet
 *  - py : int * , coordonnée y du sommet
 */
extern void PolygoneSommetIeme(tPolygone Poly, int i, int *px, int *py);

/* ------------------------ PolygoneSommetSupprimerIeme ------------------------
 * Supprime le sommet qui se trouve à la ie position de Poly
 * Entrées :
 *  - i : int , indice du sommet à supprimer
 *  - Poly : tPolygone, polygone à qui on retourne le nombre de sommets
 */
extern void PolygoneSommetSupprimerIeme(int i, tPolygone Poly);

/* ------------------------------ PolygoneLiberer ------------------------------
 * Libère la mémoire occupée par le polygone Poly
 * Entrées :
 *  - Poly : tPolygone, polygone dont on libère la mémoire alloué
 */
extern void PolygoneLiberer(tPolygone Poly);

/* ------------------------------- PolygoneLiref -------------------------------
 * Lit dans le fichier de texte d’identificateur f les coordonnées des sommets
 * d’un polygone et retourne le polygone
 * Entrée :
 *  - f : FILE *, identificateur du fichier à lire
 * Sortie : tPolygone, polygone lu dans le fichier
 */
extern tPolygone PolygoneLiref(FILE *f);

/* ------------------------------ PolygoneEcriref ------------------------------
 * Ecrit dans le fichier de texte d’identificateur f les coordonnées des sommets
 * du polygone Poly sous le même format que celui de la fonction PolygoneAfficher
 * Entrées :
 *  - Poly, tPolygone, polygone à écrire
 *  - f : FILE *, identificateur du fichier à lire
 */
extern void PolygoneEcriref(tPolygone Poly, FILE *f);

/* ---------------------------- PolygoneEcrireSvg ------------------------------
 * Ecrit le polygone Poly dans le fichier au format SVG d’identificateur
 * IdFichSVG avec le style d’adresse pStyle
 * Entrées :
 *  - Poly : tPolygone, polygone
 *  - pStyle : tStyle *, style de POLYGONE_H
 *  - IdFichSVG : FILE *, identificateur du fichier SVG
 */
extern void PolygoneEcrireSvg(tPolygone Poly, tStyle *pStyle, FILE *IdFichSVG);

#endif /* POLYGONE_H */
