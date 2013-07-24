/**
 * 2mm.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "2mm.h"


/* Array initialization. */
    static
void init_array(int ni, int nj, int nk, int nl,
        DATA_TYPE *alpha,
        DATA_TYPE *beta,
        DATA_TYPE POLYBENCH_2D(A,NI,NK,ni,nl),
        DATA_TYPE POLYBENCH_2D(B,NK,NJ,nk,nj),
        DATA_TYPE POLYBENCH_2D(C,NL,NJ,nl,nj),
        DATA_TYPE POLYBENCH_2D(D,NI,NL,ni,nl))
{
    int i, j;

    *alpha = 32412;
    *beta = 2123;
    for (i = 0; i < ni; i++)
        for (j = 0; j < nk; j++)
            A[i][j] = ((DATA_TYPE) i*j) / ni;
    for (i = 0; i < nk; i++)
        for (j = 0; j < nj; j++)
            B[i][j] = ((DATA_TYPE) i*(j+1)) / nj;
    for (i = 0; i < nl; i++)
        for (j = 0; j < nj; j++)
            C[i][j] = ((DATA_TYPE) i*(j+3)) / nl;
    for (i = 0; i < ni; i++)
        for (j = 0; j < nl; j++)
            D[i][j] = ((DATA_TYPE) i*(j+2)) / nk;
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
    static
void print_array(int ni, int nl,
        DATA_TYPE POLYBENCH_2D(D,NI,NL,ni,nl))
{
    int i, j;

    for (i = 0; i < ni; i++)
        for (j = 0; j < nl; j++) {
            fprintf (stderr, DATA_PRINTF_MODIFIER, D[i][j]);
            if ((i * ni + j) % 20 == 0) fprintf (stderr, "\n");
        }
    fprintf (stderr, "\n");
}

static inline int min (int a, int b){
    return a<b ? a : b;
}

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
    static
void kernel_2mm(int ni, int nj, int nk, int nl,
        DATA_TYPE alpha,
        DATA_TYPE beta,
        DATA_TYPE POLYBENCH_2D(tmp,NI,NJ,ni,nj),
        DATA_TYPE POLYBENCH_2D(A,NI,NK,ni,nk),
        DATA_TYPE POLYBENCH_2D(B,NK,NJ,nk,nj),
        DATA_TYPE POLYBENCH_2D(C,NL,NJ,nl,nj),
        DATA_TYPE POLYBENCH_2D(D,NI,NL,ni,nl))
{
    int i1, i2, j1, j2, k1, k2;

#pragma scop
    /* D := alpha*A*B*C + beta*D */
    multifor(i1=0, i2=0; i1< _PB_NI, i2< _PB_NI; i1++, i2++; 1, 1; 0, 1){
        multifor(j1=0, j2=0; j1< _PB_NJ, j2< _PB_NL; j1++, j2++; 1, 1; 0, 0){
0:{
      tmp[i1][j1]=0;
  }
1:{
      D[i2][j2]*=beta;
  }
  multifor(k1=0, k2=0; k1< _PB_NK, k2< _PB_NJ; k1++, k2++; 1, 1; 0, 0){
0:{
      tmp[i1][j1]+=alpha* A[i1][k1]* B[k1][j1];
  }
1:{
      D[i2][j2]+= tmp[i2][k2] * C[k2][j2];
  }
  }
        }
    }

    // source code                for (i = 0; i < _PB_NI; i++)
    // source code                for (j = 0; j < _PB_NJ; j++)
    // source code                {
    // source code                tmp[i][j] = 0;
    // source code                for (k = 0; k < _PB_NK; ++k)
    // source code                tmp[i][j] += alpha * A[i][k] * B[k][j];
    // source code                }
    // source code                for (i = 0; i < _PB_NI; i++)
    // source code                for (j = 0; j < _PB_NL; j++)
    // source code                {
    // source code                D[i][j] *= beta;
    // source code                for (k = 0; k < _PB_NJ; ++k)
    // source code                D[i][j] += tmp[i][k] * C[k][j];
    // source code                }
#pragma endscop

}


int main(int argc, char** argv)
{
    /* Retrieve problem size. */
    int ni = NI;
    int nj = NJ;
    int nk = NK;
    int nl = NL;

    /* Variable declaration/allocation. */
    DATA_TYPE alpha;
    DATA_TYPE beta;
    POLYBENCH_2D_ARRAY_DECL(tmp,DATA_TYPE,NI,NJ,ni,nj);
    POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,NI,NK,ni,nk);
    POLYBENCH_2D_ARRAY_DECL(B,DATA_TYPE,NK,NJ,nk,nj);
    POLYBENCH_2D_ARRAY_DECL(C,DATA_TYPE,NL,NJ,nl,nj);
    POLYBENCH_2D_ARRAY_DECL(D,DATA_TYPE,NI,NL,ni,nl);

    /* Initialize array(s). */
    init_array (ni, nj, nk, nl, &alpha, &beta,
            POLYBENCH_ARRAY(A),
            POLYBENCH_ARRAY(B),
            POLYBENCH_ARRAY(C),
            POLYBENCH_ARRAY(D));

    /* Start timer. */
    polybench_start_instruments;

    /* Run kernel. */
    kernel_2mm (ni, nj, nk, nl,
            alpha, beta,
            POLYBENCH_ARRAY(tmp),
            POLYBENCH_ARRAY(A),
            POLYBENCH_ARRAY(B),
            POLYBENCH_ARRAY(C),
            POLYBENCH_ARRAY(D));

    /* Stop and print timer. */
    polybench_stop_instruments;
    polybench_print_instruments;
#ifdef __PRINT
    print_array(ni,nl,POLYBENCH_ARRAY(D));
#endif
    /* Prevent dead-code elimination. All live-out data must be printed
       by the function call in argument. */
    polybench_prevent_dce(print_array(ni, nl,  POLYBENCH_ARRAY(D)));

    /* Be clean. */
    POLYBENCH_FREE_ARRAY(tmp);
    POLYBENCH_FREE_ARRAY(A);
    POLYBENCH_FREE_ARRAY(B);
    POLYBENCH_FREE_ARRAY(C);
    POLYBENCH_FREE_ARRAY(D);

    return 0;
}
