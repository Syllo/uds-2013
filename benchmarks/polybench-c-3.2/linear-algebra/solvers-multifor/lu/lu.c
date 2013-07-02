/**
 * lu.c: This file is part of the PolyBench/C 3.2 test suite.
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
/* Default data type is double, default size is 1024. */
#include "lu.h"


/* Array initialization. */
    static
void init_array (int n,
        DATA_TYPE POLYBENCH_2D(A,N,N,n,n))
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A[i][j] = ((DATA_TYPE) (i+1)*(j+1)) / n;
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
    static
void print_array(int n,
        DATA_TYPE POLYBENCH_2D(A,N,N,n,n))

{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            fprintf (stderr, DATA_PRINTF_MODIFIER, A[i][j]);
            if ((i * n + j) % 20 == 0) fprintf (stderr, "\n");
        }
    fprintf (stderr, "\n");
}


static inline void decompoLu(int nbr, int k, int i, DATA_TYPE POLYBENCH_2D(A,N,N,n,n)){
    A[i][k]=A[i][k]/A[k][k];
    int j;
    for(j=0; j<nbr; j++){
        A[i][j]=A[i][j]-A[i][j]*A[k][j];
    }
}
static inline int min(int a, int b){
    return a<b ? a : b;
}
static inline int max(int a, int b){
    return a>b ? a : b;
}

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
    static
void kernel_lu(int n,
        DATA_TYPE POLYBENCH_2D(A,N,N,n,n))
{
    int i0, i1, i2, k;
#pragma scop

    for(k=0; k<_PB_N; k++){
       
        //multifor(i0=0, i1=_PB_N/3, i2=2*_PB_N/3; i0<_PB_N/3 && k<_PB_N/3, i1<2*_PB_N/3 && k<2*_PB_N/3, i2<_PB_N; i0++, i1++, i2++; 1 ,1 ,1; 0,0,0){
       
       
       multifor(i0=0, i1=42, i2=84; i0<42 /*&& k<42*/, i1<84/* && k<84*/, i2<128; i0++, i1++, i2++; 1 ,1 ,1; 0,0,0){
0:{ //intervalle 0 .._NB_N /3 -1
      if(i0>k){ // le pivot
          decompoLu(_PB_N, k, i0, A);
      }
  }
1:{ //intervalle _NB_N/3 .. _2*NB_N/3-1
      if(i1>k){ // le pivot
          decompoLu(_PB_N , k, i1, A);
      }
  }
2:{ // intervalle 2*_PB_N/3 .. _PB_N-1
      if(i2>k){  // le pivot
          decompoLu(_PB_N, k, i2, A);
      }
  }
        }
    }

    //source code   for (k = 0; k < _PB_N; k++)
    //source code   {
    //source code       for (j = k + 1; j < _PB_N; j++)
    //source code           A[k][j] = A[k][j] / A[k][k];
    //source code       for(i = k + 1; i < _PB_N; i++)
    //source code           for (j = k + 1; j < _PB_N; j++)
    //source code               A[i][j] = A[i][j] - A[i][k] * A[k][j];
    //source code   }
#pragma endscop
}

int main(int argc, char** argv)
{
    /* Retrieve problem size. */
    int n = N;

    /* Variable declaration/allocation. */
    POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);


    /* Initialize array(s). */
    init_array (n, POLYBENCH_ARRAY(A));

    /* Start timer. */
    polybench_start_instruments;

    /* Run kernel. */
    kernel_lu (n, POLYBENCH_ARRAY(A));

    /* Stop and print timer. */
    polybench_stop_instruments;
    polybench_print_instruments;

    /* Prevent dead-code elimination. All live-out data must be printed
       by the function call in argument. */
    polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(A)));

    /* Be clean. */
    POLYBENCH_FREE_ARRAY(A);

    return 0;
}
