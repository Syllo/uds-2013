/* Voici un exemple d'utilisation d'une structure multifor dans le cas du calcul du Jeu de la Vie qui est implémenté sous forme de matrice NxN, N>2. (Note : les bords ne sont pas mis a jour dans cet exemple)
 * Le problème se résout sous la forme de deux opérations succesive présenté ci-dessous
 * 1:   On calcule les états des cellules de la grille et on les sauvegarde dans une grille temporaire
 * 2:   Mettre à jour la grille principale avec les valeurs calculé précédement
 */

/*  Voici un exemple d'implementation en C de cet algorithme
 */

int t[N][N];
int temp[N-2][N-2];

void calc (){
    for(i=1;i<N-1;i++)
        for(j=1;j<N-1;j++){
            temp[i-1][j-1]=game_of_life(t[i-1][j],t[i-1][j-1],t[i-1][j+1],[i][j-1],[i][j+1],[i+1][j-1],[i+1][j],[i+1][j+1]);
        }
    for(i=1;i<N-1;i++)
        for(j=1;j<N-1;j++){
            t[i][j]=temp[i-1][j-1];
        }
}

/* Ici on lit (N-2)²*8 valeurs et sauvegarde (N-2)² valeurs pour la première boucle puis lit et ecrit (N-2)² valeurs pour la seconde boucle. Tout est executé sequentiellement
 Le prochain programme utilise la structure multifor pour effectué le même travail
 */

void calc_multifor (){
    multifor(i=1, i2=1; i<N-1, i2<N-1; i++, i2++; 1, 1; 0, 3){
        multifor(j=1, j2=1; j<N-1, j2<N-1; j++, j2++; 1, 1; 0, 3){
            0:  temp[i-1][j-1]=game_of_life(t[i-1][j],t[i-1][j-1],t[i-1][j+1],[i][j-1],[i][j+1],[i+1][j-1],[i+1][j],[i+1][j+1]);
            1:  t[i2][j2]=temp[i2-1][j2-1];
        }
    }
}

/* Dans ce cas on effectue les premiers calculs avant de recopier les valeurs, car si on a déjà calculé les deux premières lignes et colonnes les valeurs dans la première ligne ne sont plus utile pour la suite du calcule de la grille ce qui permet aux deux boucles de fonctionner en parallèle. Avec cet implémentation il n'est pas non plus necesaire d'avoir une grille de même taille pour la temporaire mais une grille contenant (N-2)*6-9 suffit pour sauvegardé les données réelement utile ce qui fait qu'on gagne en place mémoire.
