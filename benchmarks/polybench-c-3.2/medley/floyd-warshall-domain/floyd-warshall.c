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

#pragma scop
    printf("digraph G{\n rankdir=\"LR\";\nedge[style=\"\",dir=\"forward\"];\n");
    k=_PB_N/2;
#ifdef _K1
    k=0;
#endif
#ifdef _K2
    k=_PB_N/4;
#endif
#ifdef _K3
    k=_PB_N/2;
#endif
#ifdef _K4
    k=3*_PB_N/4;
#endif
#ifdef _K5
    k=_PB_N-1;
#endif
    printf("subgraph cluster_1 {\n  style=filled;\n  fillcolor=lightgrey;\n  label = \"Floyd-Warshall loop %d\";\n",k);
    for(i=0; i<_PB_N;i++){
        for(j=0; j<_PB_N; j++){
            if(i<k && j<k){
                printf("node [pos=\"%d,%d!\" shape=point color=green height=0.2] a%da%d;\n",i,j,i,j);
            }
            else{
                if(i>k && j>k){
                    printf("node [pos=\"%d,%d!\" shape=point color=magenta height=0.2] a%da%d;\n",i,j,i,j);
                }
                else{
                    if(i>k && j<k){
                        printf("node [pos=\"%d,%d!\" shape=point color=cyan height=0.2] a%da%d;\n",i,j,i,j);
                    }
                    else{
                        if(i<k && j>k){
                            printf("node [pos=\"%d,%d!\" shape=point color=red height=0.2] a%da%d;\n",i,j,i,j);
                        }
                        else{
                            if(j==k && i>k){
                                printf("node [pos=\"%d,%d!\" shape=point color=blue height=0.2] a%da%d;\n",i,j,i,j);
                            }
                            else{
                                if(i==k && j<k){
                                    printf("node [pos=\"%d,%d!\" shape=point color=chartreuse height=0.2] a%da%d;\n",i,j,i,j);
                                }
                                else{
                                    if(i==k && j>k){
                                        printf("node [pos=\"%d,%d!\" shape=point color=pink height=0.2] a%da%d;\n",i,j,i,j);
                                    }
                                    else{
                                        if(i==k && j==k){
                                            printf("node [pos=\"%d,%d!\" shape=point color=black height=0.2] a%da%d;\n",i,j,i,j);
                                        }
                                        else{
                                            printf("node [pos=\"%d,%d!\" shape=point color=yellow height=0.2] a%da%d;\n",i,j,i,j);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("}\n");
    printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=magenta ];\n9\n",8,-1,8,-1);
    printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=green ];\n1\n",0,-1,0,-1);
    printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=yellow ];\n2\n",1,-1,1,-1);
    printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=red ];\n3\n",2,-1,2,-1);
    printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=chartreuse ];\n4\n",3,-1,3,-1);
    printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=black ];\n5\n",4,-1,4,-1);
    printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=pink ];\n6\n",5,-1,5,-1);
    printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=cyan ];\n7\n",6,-1,6,-1);
    printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=blue ];\n8\n",7,-1,7,-1);
    printf("}\n");
    //source code   for (k = 0; k < _PB_N; k++)
    //source code   {
    //source code       for(i = 0; i < _PB_N; i++)
    //source code           for (j = 0; j < _PB_N; j++)
    //source code               path[i][j] = path[i][j] < path[i][k] + path[k][j] ?
    //source code                   path[i][j] : path[i][k] + path[k][j];
    //source code   }
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

    /* Prevent dead-code elimination. All live-out data must be printed
       by the function call in argument. */
    polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(path)));

    /* Be clean. */
    POLYBENCH_FREE_ARRAY(path);

    return 0;
}
