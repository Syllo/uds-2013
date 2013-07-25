#include <math.h>
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


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
    static
void kernel_floyd_warshall(int n,
        DATA_TYPE POLYBENCH_2D(path,N,N,n,n))
{
    int i, j, k;

#ifdef ceild
# undef ceild
#endif
#ifdef floord
# undef floord
#endif
#ifdef max
# undef max
#endif
#ifdef min
# undef min
#endif
#define ceild(n,d)  ceil(((double)(n))/((double)(d)))
#define floord(n,d) floor(((double)(n))/((double)(d)))
#define max(x,y)    ((x) > (y)? (x) : (y))
#define min(x,y)    ((x) < (y)? (x) : (y))
  register int lbv, ubv, lb, ub, lb1, ub1, lb2, ub2;
  register int c0, c1, c2;
#pragma scop
if ((_PB_N >= 1)) {
    for (c0 = 0; c0 <= (_PB_N + -1); c0++) {
        for (c1 = 0; c1 <= (_PB_N + -1); c1++) {
            for (c2 = 0; c2 <= (_PB_N + -1); c2++) {
        path[c1][c2]=path[c1][c2]<path[c1][c0]+path[c0][c2]?path[c1][c2]:path[c1][c0]+path[c0][c2];
      }
    }
  }
}
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
