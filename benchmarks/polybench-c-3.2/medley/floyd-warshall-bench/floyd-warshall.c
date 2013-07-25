/**
 * floyd-warshall.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "floyd-warshall.h"


/* Array initialization. */
    static
void init_array (int n,
        DATA_TYPE POLYBENCH_2D(path,N,N,n,n))
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            path[i][j] = ((DATA_TYPE) (i+1)*(j+1)) / n;
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
    static
void print_array(int n,
        DATA_TYPE POLYBENCH_2D(path,N,N,n,n))

{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            fprintf (stderr, DATA_PRINTF_MODIFIER, path[i][j]);
            if ((i * n + j) % 20 == 0) fprintf (stderr, "\n");
        }
    fprintf (stderr, "\n");
}

static inline void mult1(int i, DATA_TYPE POLYBENCH_2D(path,N,N,n,n), int k){
    for(int j=i; j<k; j++){
        if(j!=i)
            path[i][j] = path[i][j] < path[i][k] + path[k][j] ? path[i][j] : path[i][k] + path[k][j];
        path[j][i] = path[j][i] < path[k][i] + path[j][k] ? path[j][i] : path[k][i] + path[j][k];
    }
}
static inline void mult2(int i, DATA_TYPE POLYBENCH_2D(path,N,N,n,n), int n, int k){
    for(int j=k+1; j< n; j++){
        path[i][j] = path[i][j] < path[i][k] + path[k][j] ? path[i][j] : path[i][k] + path[k][j];
    }
}
static inline void mult3(int j, DATA_TYPE POLYBENCH_2D(path,N,N,n,n), int n, int k){
    for(int i=k+1; i< n; i++){
        path[i][j] = path[i][j] < path[i][k] + path[k][j] ? path[i][j] : path[i][k] + path[k][j];
    }
}
static inline int max(int a , int b){
    return a>b ? a : b;
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */
    static
void kernel_floyd_warshall(int n,
        DATA_TYPE POLYBENCH_2D(path,N,N,n,n))
{
    int i1, i2, j3;

#pragma scop

    for(int k=0; k< _PB_N; k++){
        multifor(i1=0,i2=0,j3=0; i1<k+1, i2<k+1, j3<k+1; i1++,i2++,j3++; 1,1,1; 0,1,1){
0:{
      mult1(i1, path, k);
  }
1:{
      mult2(i2,path, n, k);
  }
2:{
      mult3(j3,path,n,k);
  }
        }
    for(int i=k+1; i<n;i++){
        for(int j=k+1;j<n;j++){
            path[i][j] = path[i][j] < path[i][k] + path[k][j] ? path[i][j] : path[i][k] + path[k][j];
        }
    }
    }
    //source code  for (k = 0; k < _PB_N; k++)
    //source code  {
    //source code      for(i = 0; i < _PB_N; i++)
    //source code          for (j = 0; j < _PB_N; j++)
    //source code              path[i][j] = path[i][j] < path[i][k] + path[k][j] ?
    //source code                  path[i][j] : path[i][k] + path[k][j];
    //source code  }
#pragma endscop

}


int main(int argc, char** argv)
{
    /* Retrieve problem size. */
    int n = N;

    /* Variable declaration/allocation. */
    POLYBENCH_2D_ARRAY_DECL(path, DATA_TYPE, N, N, n, n);


    /* Initialize array(s). */
    init_array (n, POLYBENCH_ARRAY(path));

    /* Start timer. */
    polybench_start_instruments;

    /* Run kernel. */
    kernel_floyd_warshall (n, POLYBENCH_ARRAY(path));

    /* Stop and print timer. */
    polybench_stop_instruments;
    polybench_print_instruments;
#ifdef __PRINT
    print_array(n,POLYBENCH_ARRAY(path));
#endif
    /* Prevent dead-code elimination. All live-out data must be printed
       by the function call in argument. */
    polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(path)));

    /* Be clean. */
    POLYBENCH_FREE_ARRAY(path);

    return 0;
}
