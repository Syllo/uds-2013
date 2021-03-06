/**
 * 3mm.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
/* Default data type is double, default size is 4000. */
#include "3mm.h"


/* Array initialization. */
    static
void init_array(int ni, int nj, int nk, int nl, int nm,
        DATA_TYPE POLYBENCH_2D(A,NI,NK,ni,nk),
        DATA_TYPE POLYBENCH_2D(B,NK,NJ,nk,nj),
        DATA_TYPE POLYBENCH_2D(C,NJ,NM,nj,nm),
        DATA_TYPE POLYBENCH_2D(D,NM,NL,nm,nl))
{
    int i, j;

    for (i = 0; i < ni; i++)
        for (j = 0; j < nk; j++)
            A[i][j] = ((DATA_TYPE) i*j) / ni;
    for (i = 0; i < nk; i++)
        for (j = 0; j < nj; j++)
            B[i][j] = ((DATA_TYPE) i*(j+1)) / nj;
    for (i = 0; i < nj; i++)
        for (j = 0; j < nm; j++)
            C[i][j] = ((DATA_TYPE) i*(j+3)) / nl;
    for (i = 0; i < nm; i++)
        for (j = 0; j < nl; j++)
            D[i][j] = ((DATA_TYPE) i*(j+2)) / nk;
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
    static
void print_array(int ni, int nl,
        DATA_TYPE POLYBENCH_2D(G,NI,NL,ni,nl))
{
    int i, j;

    for (i = 0; i < ni; i++)
        for (j = 0; j < nl; j++) {
            fprintf (stderr, DATA_PRINTF_MODIFIER, G[i][j]);
            if ((i * ni + j) % 20 == 0) fprintf (stderr, "\n");
        }
    fprintf (stderr, "\n");
}
//static inline int min(int a, int b){
//    return a<b ? a: b;
//}
//static inline int max(int a, int b){
//    return a>b ? a : b;
//}

/**
 * Sert au calcul de la matrice G qui est coupé en deux selon la diagonale, faisant deux matrices triangulaire.
 * Si boulien est égale à 0 calcul de la partie supérieure (qui doit être plié avec un grain de -1 ou calculé après que E et F soient entièrement calculé) et sinon la partie inférieure.
 * */

static inline void calculatation(int i, int _PB_NI, 
        DATA_TYPE POLYBENCH_2D(G,NI,NL,ni,nl),
        DATA_TYPE POLYBENCH_2D(E,NI,NJ,ni,nj),
        DATA_TYPE POLYBENCH_2D(F,NJ,NL,nj,nl),
        int boulien){
    for(int ibis=i, jbis=-i; jbis<-i+_PB_NI; ibis++, jbis++){
        int ibase=(ibis-jbis)/2, jbase=(ibis+jbis)/2;
        if( boulien!=0 ? jbis<=0 : jbis>0){
            G[ibase][jbase]=0;
            for(int k=0; k<_PB_NI; k++){
                G[ibase][jbase]+=E[ibase][k]* F[k][jbase];
            }
        }
    }
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */
    static
void kernel_3mm(int ni, int nj, int nk, int nl, int nm,
        DATA_TYPE POLYBENCH_2D(E,NI,NJ,ni,nj),
        DATA_TYPE POLYBENCH_2D(A,NI,NK,ni,nk),
        DATA_TYPE POLYBENCH_2D(B,NK,NJ,nk,nj),
        DATA_TYPE POLYBENCH_2D(F,NJ,NL,nj,nl),
        DATA_TYPE POLYBENCH_2D(C,NJ,NM,nj,nm),
        DATA_TYPE POLYBENCH_2D(D,NM,NL,nm,nl),
        DATA_TYPE POLYBENCH_2D(G,NI,NL,ni,nl))
{
    int i1, i2, ini, i3, j1, j2, k1, k2;

#pragma scop
    multifor(i1=0, i2=0, i3=0, ini=0; i1<ni, i2<ni, i3<ni, ini<ni; i1++, i2++, i3++, ini++; 1, 1, 1, 1; 0, 0, ni, 1){
2:{
      calculatation(i3,_PB_NI,G,E,F,0); //calcul de la matrice supérieure avec un grain de -1 pour plier le domaine
  }
3:{
      calculatation(ini,_PB_NI,G,E,F,1); //calcul de la matrice inférieure
  }
  multifor(j1=0, j2=0; j1 < ni, j2<ni; j1++, j2++;1, 1; 0, 0){
0:{
      E[i1][j1]=0;
  }
1:{
      F[j2][i2]=0;
  }
  multifor(k1=0, k2=0; k1 < ni, k2<ni; k1++, k2++; 1, 1; 0, 0){
0:{
      E[i1][j1]+=A[i1][k1]*B[k1][j1];
  }
1:{
      F[j2][i2]+=C[j2][k2]*D[k2][i2];
  }
  }
  }
    }
    //  multifor(i1=0, j2=0, nb_row_G=0; i1< _PB_NI, j2< _PB_NL, nb_row_G < _PB_NI; i1++, j2++, nb_row_G++; 1, 1,1; 0, 0, 1){
    //      multifor(j1=0, i2=0, i3=0; j1< _PB_NJ, i2< _PB_NJ, i3< i1; j1++, i2++, i3++; 1, 1, 1; 0, 0, 0){
    //          0:{
    //                E[i1][j1]=0;
    //            }
    //          1:{
    //                F[i2][j2]=0;
    //            }
    //            multifor(k1=0, k2=0, j3=0; k1< _PB_NK, k2< _PB_NM, j3 < j2; k1++, k2++, j3++; 1, 1, 1; 0, 0, 0){
    //                  0:{
    //                        E[i1][j1]+= A[i1][k1] * B[k1][j1];
    //                    }
    //                  1:{
    //                        F[i2][j2]+= C[i2][k2] * D[k2][j2];
    //                    }
    //                  2:{
    //                        if(i3 < i1-1){
    //                            j3=j2-1;
    //                        }
    //                        G[i3][j3]=0;
    //                        for(k3=0; k3 < _PB_NJ; k3++){

    //                              G[i3][j3]+=E[i3][k3]*F[k3][j3];
    //                              if(j3==3)
    //                            printf("nb_row:%d i1:%d j2:%d i3:%d j3:%d k3:%d valG %f valE %f valF %f\n",nb_row_G,i1,j2,i3,j3,k3,G[i3][j3],E[i3][k3], F[k3][j3]);
    //                        }
    //                    }
    //            }
    //      }
    //  }

    //source code        /* E := A*B */
    //source code        for (i = 0; i < _PB_NI; i++)
    //source code            for (j = 0; j < _PB_NJ; j++)
    //source code            {
    //source code                E[i][j] = 0;
    //source code                for (k = 0; k < _PB_NK; ++k)
    //source code                    E[i][j] += A[i][k] * B[k][j];
    //source code            }
    //source code        /* F := C*D */
    //source code        for (i = 0; i < _PB_NJ; i++)
    //source code            for (j = 0; j < _PB_NL; j++)
    //source code            {
    //source code                F[i][j] = 0;
    //source code                for (k = 0; k < _PB_NM; ++k)
    //source code                    F[i][j] += C[i][k] * D[k][j];
    //source code            }
    //source code        /* G := E*F */
    //source code        for (i = 0; i < _PB_NI; i++)
    //source code            for (j = 0; j < _PB_NL; j++)
    //source code            {
    //source code                G[i][j] = 0;
    //source code                for (k = 0; k < _PB_NJ; ++k)
    //source code                    G[i][j] += E[i][k] * F[k][j];
    //source code            }
#pragma endscop

}


int main(int argc, char** argv)
{
    /* Retrieve problem size. */
    int ni = NI;
    int nj = NJ;
    int nk = NK;
    int nl = NL;
    int nm = NM;

    /* Variable declaration/allocation. */
    POLYBENCH_2D_ARRAY_DECL(E, DATA_TYPE, NI, NJ, ni, nj);
    POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, NI, NK, ni, nk);
    POLYBENCH_2D_ARRAY_DECL(B, DATA_TYPE, NK, NJ, nk, nj);
    POLYBENCH_2D_ARRAY_DECL(F, DATA_TYPE, NJ, NL, nj, nl);
    POLYBENCH_2D_ARRAY_DECL(C, DATA_TYPE, NJ, NM, nj, nm);
    POLYBENCH_2D_ARRAY_DECL(D, DATA_TYPE, NM, NL, nm, nl);
    POLYBENCH_2D_ARRAY_DECL(G, DATA_TYPE, NI, NL, ni, nl);

    /* Initialize array(s). */
    init_array (ni, nj, nk, nl, nm,
            POLYBENCH_ARRAY(A),
            POLYBENCH_ARRAY(B),
            POLYBENCH_ARRAY(C),
            POLYBENCH_ARRAY(D));

    /* Start timer. */
    polybench_start_instruments;

    /* Run kernel. */
    kernel_3mm (ni, nj, nk, nl, nm,
            POLYBENCH_ARRAY(E),
            POLYBENCH_ARRAY(A),
            POLYBENCH_ARRAY(B),
            POLYBENCH_ARRAY(F),
            POLYBENCH_ARRAY(C),
            POLYBENCH_ARRAY(D),
            POLYBENCH_ARRAY(G));

    /* Stop and print timer. */
    polybench_stop_instruments;
    polybench_print_instruments;
#ifdef __PRINT
    print_array(ni,nl,POLYBENCH_ARRAY(G));
#endif
    /* Prevent dead-code elimination. All live-out data must be printed
       by the function call in argument. */
    polybench_prevent_dce(print_array(ni, nl,  POLYBENCH_ARRAY(G)));

    /* Be clean. */
    POLYBENCH_FREE_ARRAY(E);
    POLYBENCH_FREE_ARRAY(A);
    POLYBENCH_FREE_ARRAY(B);
    POLYBENCH_FREE_ARRAY(F);
    POLYBENCH_FREE_ARRAY(C);
    POLYBENCH_FREE_ARRAY(D);
    POLYBENCH_FREE_ARRAY(G);

    return 0;
}
