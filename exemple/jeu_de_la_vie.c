/* Voici un exemple d'utilisation d'une structure multifor dans le cas du calcul du Jeu de la Vie qui est implémenté sous forme de matrice NxN, N>2. (Note : les bords ne sont pas mis a jour dans cet exemple)
 * Le problème se résout sous la forme de deux opérations successives présenté ci-dessous
 * 1:   On calcule les états des cellules de la grille et on les sauvegarde dans une grille temporaire
 * 2:   Mettre à jour la grille principale avec les valeurs calculé précédemment
 */

/*  Voici un exemple d'implémentation en C de cet algorithme (on suppose les grilles initialisées)
 */

int t[N][N];
int temp[N-2][N-2];

void calc (){
    for(i=1;i<N-1;i++)
        for(j=1;j<N-1;j++){
            temp[i-1][j-1]=game_of_life(t[i][j],t[i-1][j],t[i-1][j-1],t[i-1][j+1],[i][j-1],[i][j+1],[i+1][j-1],[i+1][j],[i+1][j+1]);
        }
    for(i=1;i<N-1;i++)
        for(j=1;j<N-1;j++){
            t[i][j]=temp[i-1][j-1];
        }
}

/* Ici on lit (N-2)²*8 valeurs et sauvegarde (N-2)² valeurs pour la première boucle puis lit et écrit (N-2)² valeurs pour la seconde boucle. Tout est exécuté séquentiellement lient
 Le prochain programme utilise la structure multifor pour effectué le même travail
 */

void calc_multifor (){
    multifor(i=1, i2=1; i<N-1, i2<N-1; i++, i2++; 1, 1; 0, 3){
        multifor(j=1, j2=1; j<N-1, j2<N-1; j++, j2++; 1, 1; 0, 0){
            0:  temp[i-1][j-1]=game_of_life(t[i][j],t[i-1][j],t[i-1][j-1],t[i-1][j+1],[i][j-1],[i][j+1],[i+1][j-1],[i+1][j],[i+1][j+1]);
            1:  t[i2][j2]=temp[i2-1][j2-1];
        }
    }
}

/* Dans ce cas on effectue les premiers calculs avant de recopier les valeurs, car si on a déjà calculé les deux premières lignes et colonnes les valeurs dans la première ligne ne sont plus utile pour la suite du calcule de la grille ce qui permet aux deux boucles de fonctionner en parallèle. Avec cet implémentation il n'est pas non plus nécessaire d'avoir une grille de même taille pour la temporaire mais une grille contenant (N-2)*3 suffit pour sauvegardé les données réellement utile ce qui fait qu'on gagne en espace mémoire.
 * */

/* Déc mposition pour compilation du multifor 
 * 1) Domaines d'itération
 * 
 * D1:=[N] -> { [i,j] : 1<=i<N-1 and 0<=j<N-1
 * D2:=[N] -> { [i2,j2] : 1<=i2<N-1 and 0<=j2<N-1
 *
 * 2)Domaine de référence
 *
 * map1(i,j)= (1,1)(i,j)+(0,0) = (i,j)
 * map2(i2,j2)= (1,1)(i2,j2)+(3,0)= (i2+3,j2)
 *
 * 3)Expression dans le domaine de référence
 *
 * P1 := [N] -> { [i,j,0,i,j] : 1<=i<N-1 and 1<=j<N-1};
 * P2 := [N] -> { [i2_,j2,1,i2,j2] : i2_=i2+3 and 1<=i2<N-1 and 1<=j2<N-1};
 *
 * codgen(P1+P2);
 * 
 * 4) Code obtenu
 *
 * {
 *     for (int c0 = 1; c0 < N - 1; c0 += 1)
 *         for (int c1 = 1; c1 < N - 1; c1 += 1) {
 *             (c0, c1, 0, c0, c1);
 *             if (c0 >= 4)
 *                 (c0, c1, 1, c0 - 3, c1);
 *         }
 *     for (int c0 = max(4, N - 1); c0 <= N + 1; c0 += 1)
 *         for (int c1 = 1; c1 < N - 1; c1 += 1)
 *             (c0, c1, 1, c0 - 3, c1);
 * }
 *
 * 5) Traduction en C
 */

void compute(int i,int j){
    temp[i-1][j-1]=game_of_life(t[i][j],t[i-1][j],t[i-1][j-1],t[i-1][j+1],[i][j-1],[i][j+1],[i+1][j-1],[i+1][j],[i+1][j+1]);
}

void c opie(int i, int j){
    t[i][j]=temp[i-1][j-1];
}

int max(int i, int j){
    i>j ? return i : return j;
}

{
     for(int i=1; i<N-1; i++){
        for(int j=1; j<N-1; j++){
            compute(i,j);
            if(i>=4){
                copie(i-3,j);
            }
        }
    }
      for(i=max(4,N-1); i<=N+1; i++){
        for(j=1; j<N-1; j++){
            copie(i-3,j);
        }
    }
}

