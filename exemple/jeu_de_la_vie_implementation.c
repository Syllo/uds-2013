#include <stdio.h>
#include <stdlib.h>
#include <jeu_de_la_vie_implementation.h>

#define N 10
typedef enum {Mort,Vie} Vivant;

int t[N][N];
int temp[N-2][N-2];

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
    temp[i-1][j-1]=game_of_life(t[i],[j],t[i-1][j],t[i-1][j-1],t[i-1][j+1],[i][j-1],[i][j+1],[i+1][j-1],[i+1][j],[i+1][j+1]);
}

void c opie(int i, int j){
    t[i][j]=temp[i-1][j-1];
}

int max(int i, int j){

   i>j ? return i : return j;
}

void 
ame_of_life_multifor{
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
