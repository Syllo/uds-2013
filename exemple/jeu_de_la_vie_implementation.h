#ifndef __JEU_DE_VIE_IMPLEMENTATION_H
#define __JEU_DE_VIE_IMPLEMENTATION_H

typedef enum {Mort,Vie} Vivant;

/**
 * \brief Calcule l'état suivant de la cellule par rapport aux cellules environnantes
 * \param mm Cellule du centre (celle qui évolue)
 * \param bm Cellule bas milieu
 * \param bg Cellule bas gauche
 * \param bd Cellule bas droite
 * \param mg Cellule milieu gauche
 * \param md Cellule milieu droite
 * \param hg Cellule haut gauche
 * \param hm Cellule haut milieu
 * \param hd Cellule haut droite
 * \return L'état de la cellule dans 1 pas de temps
 */

Vivant game_of_life (Vivant mm,Vivant bm, Vivant bg, Vivant bd, Vivant mg, Vivant md, Vivant hg, Vivant hm, Vivant hd);

/**
 * \brief Remplit la grille temp avec les valeurs du temps+1
 * \param i la ligne a calculer
 * \param j la colonne a calculer
 * \pre 1<=i<N
 * \pre 1<=j<N
 */

void compute(int i,int j);

/*
 * \brief Copie de la grille temporaire vers la grille principale
 * \param i La ligne de la grille principal a remplir
 * \paral j La colonne de la grille principal a remplir
 */

void copie(int i, int j);

/**
 * \brief Renvoie le max entre i et j
 * \param i un entier signé
 * \param j un entier signé
 * \return Le plus grand de i et j
 */

int max(int i, int j);

/**
 * Version multifor du jeu de la vie(voit jeu_de_la_vie.c
 */

void game_of_life_multifor();

/**
 * Version itérative normal du jeu de la vie (voir jeu_de_la_vie.c)
 */

void game_of_life_normal();

/**
 * \brief Initialise la grille avec des valeurs aléatoires
 */

void initialise_alea();

/**
 * Lance le jeu de la vie avec et sans multifor et sauvegarde les résultats dans le dossier courant sous la forme "ligne colonne valeur"
 */

int main();

#endif // __JEU_DE_VIE_IMPLEMENTATION_H
