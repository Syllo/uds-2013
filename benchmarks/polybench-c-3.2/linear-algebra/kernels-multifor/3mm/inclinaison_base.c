#include <stdio.h>
#include <stdlib.h>

const int I = 4;

void baseTo1_4 (){
    /* Passage des valeurs de la base normale à la base incliné */

    printf("ij->i'j'\n");
    for(int i=0; i<I; i++){
        printf("\n");
        for(int j=0; j<I; j++){
            printf("[%d][%d]->[%d][%d]\n",i,j,i+j,j-i);
        }
    }
}

void B_4ToBase(){
    /* Passage des valeurs de la base incliné vers la base normal avec le parcours dans le même ordre */
    printf("\ni'j'->ij\n");
    for(int i=0,k=i; i<I; i=k+++1){
        printf("\n");
        for(int j=-i, m=j; j<m+I; j+=1, i+=1){
            printf("[%d][%d]->[%d][%d]\n",i,j,(i-j)/2,(i+j)/2);
        }
    }
}

void decoupeUpper(){
    for(int i=0; i<I; i++){
        printf("\n");
        for(int ibis=i, j=-ibis; j<-i+I; j+=1, ibis+=1){
            if(j<=0)
                printf("[%d][%d]->[%d][%d]\n",ibis,j,(ibis-j)/2,(ibis+j)/2);
        }
    }
}

void decoupeDown(){

}

int main(){
    //B_4ToBase();
    //baseTo1_4();
    decoupeUpper();
    return 0;
}
