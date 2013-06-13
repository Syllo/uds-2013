#include <stdio.h>
#include <stdlib.h>
#include <jeu_de_la_vie_implementation.h>

#define N 10
#define SEED 12

Vivant t[N][N];
Vivant temp[N-2][N-2];

Vivant game_of_life (Vivant mm,Vivant bm, Vivant bg, Vivant bd, Vivant mg, Vivant md, Vivant hg, Vivant hm, Vivant hd){
    int nombreEnVie;
    nombreEnVie=bm+bg+bd+mg+md+hg+hd+hm;
    if(nombreEnVie==3 || nombreEnVie==2){
        if(nombreEnVie==3){
            return Vie;
        }
        else{
            return mm;
        }
    }
    return Mort;
}

void compute(int i,int j){
    temp[i-1][j-1]=game_of_life(t[i][j],t[i-1][j],t[i-1][j-1],t[i-1][j+1],t[i][j-1],t[i][j+1],t[i+1][j-1],t[i+1][j],t[i+1][j+1]);
}

void copie(int i, int j){
    t[i][j]=temp[i-1][j-1];
}

int max(int i, int j){
   return i>j ? i : j;
}

void game_of_life_multifor(){
    for(int i=1; i<N-1; i++){
        for(int j=1; j<N-1; j++){
            compute(i,j);
            if(i>=4){
                copie(i-3,j);
            }
        }
    }
    for(int i=max(4,N-1); i<=N+1; i++){
        for(int j=1; j<N-1; j++){
            copie(i-3,j);
        }
    }
    return;
}

void game_of_life_normal(){
    for(int i=1; i<N-1; i++){
        for(int j=1; j<N-1; j++){
            compute(i,j);
        }
    }
    for(int i=1; i<N-1; i++){
        for(int j=1; j<N-1; j++){
            copie(i,j);
        }
    }
    return;
}

void initialise_alea(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            t[i][j]=(Vivant) rand()%2;
        }
    }
}

int main (){
    FILE * jdv_normal_data=fopen("jdv_normal.data","w");
    FILE * jdv_multifor_data=fopen("jdv_multifor.data","w");
    if(jdv_multifor_data==NULL || jdv_normal_data==NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    srand(SEED);
    initialise_alea();
    game_of_life_normal();
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            fprintf(jdv_normal_data, "%d %d %d\n", i, j, t[i][j]);
        }
    }
    srand(SEED); //réinitialise le rand pour obtenir les mêmes valeurs
    initialise_alea();
    game_of_life_multifor();
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            fprintf(jdv_multifor_data, "%d %d %d\n", i, j, t[i][j]);
        }
    }
    if(fclose(jdv_multifor_data)==EOF || fclose(jdv_normal_data)==EOF){
        perror("fclose");
    }
    return EXIT_SUCCESS;
}
