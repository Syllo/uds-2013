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
#include "DDV_API.h"

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


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
    static
void kernel_lu(int n,
        DATA_TYPE POLYBENCH_2D(A,N,N,n,n))
{
    int i, j, k;

#pragma scop
    struct table *ddv_table;
    int indices[DIMENSION];
    int memref[DIMENSION];

    ddv_table=NULL;

    printf("digraph G {\n  rankdir=\"LR\";\n  edge[style=\"\",dir=\"forward\"];\n");

    SUB_CLUST(1)
        for (k = 0; k < _PB_N; k++)
        {
            for (j = 0; j < _PB_N; j++){
#ifdef dom_a
                if(j<k+1){
                    printf("node [pos=\"%d,%d!\" shape=point color=black height=0.2] a%da%d;\n",k,j,k,j);
    //                printf("edge[style=\"invisible\" dir=\"none\"];\n");
    //                printf("edge[style=\"\" dir=\"forward\"];\n");
    //                printf("edge[color=white];\n");
    //                DDV_FUSE(k,j,k,j,'a','a',1)
                }
                else{
                    printf("node [pos=\"%d,%d!\" shape=point color=green height=0.2] a%da%d;\n",k,j,k,j);
                    printf("edge[style=\"invisible\" dir=\"none\"];\n");
                    printf("edge[style=\"\" dir=\"forward\"];\n");
                    printf("edge[color=green];\n");
                    DDV_FUSE(k,j,k,j,'a','a',1)
                }
#endif
                if(j>=k+1)
                    A[k][j] = A[k][j] / A[k][k];
            }
            for(i = 0; i < _PB_N; i++)
                for (j = 0; j < _PB_N; j++){
#ifdef dom_b
                    if(i<k+1 || j<k+1){
                    printf("node [pos=\"%d,%d!\" shape=point color=black height=0.2] b%db%d;\n",i+_PB_N+1,j+_PB_N-3,i,j);
                    }
                    else{
                    printf("node [pos=\"%d,%d!\" shape=point color=pink height=0.2] b%db%d;\n",i+_PB_N+1,j+_PB_N-3,i,j);
                    printf("edge[style=\"invisible\" dir=\"none\"];\n");
                    printf("edge[style=\"\" dir=\"forward\"];\n");
                    printf("edge[color=yellow];\n");
                    DDV_FUSE(i,j,i,j,'b','a',0)
                        DDV_FUSE(i,j,i,k,'b','a',0)
                        DDV_FUSE(i,j,k,j,'b','a',0)
                    }
#endif
                    if(i>=k+1 && j>=k+1){
                        A[i][j] = A[i][j] - A[i][k] * A[k][j];
                    }
                }
        }
    printf("}\n}\n");
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
