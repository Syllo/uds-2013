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
#include "DDV_API.h"

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
    int i, j, k;

#pragma scop
    /* E := A*B */
    printf("digraph G {\n  rankdir=\"LR\";\n  edge[style=\"\",dir=\"forward\"];\n");
    printf("subgraph cluster_1 {\n  style=filled;\n  fillcolor=seagreen1;\n  label = \"E=A*B\";\n");
    for (i = 0; i < _PB_NI; i++)
        for (j = 0; j < _PB_NJ; j++)
        {
            printf("node [pos=\"%d,%d!\" shape=point color=green height=0.2] a%da%d;\n",i,j,i,j);
        }
    printf("}\n");
    /* F := C*D */
    printf("subgraph cluster_2 {\n  style=filled;\n  fillcolor=royalblue1;\n  label = \"F=C*D\";\n");
    for (i = 0; i < _PB_NJ; i++)
        for (j = 0; j < _PB_NL; j++)
        {
            if(i<_PB_NI && j<_PB_NJ){
                printf("node [pos=\"%d,%d!\" shape=point color=cyan height=0.2] b%db%d;\n",i,j,i,j);
            }
            else{
                printf("node [pos=\"%d,%d!\" shape=point color=blue height=0.2] b%db%d;\n",i,j,i,j);
            }
        }
    printf("}\n");
    /* G := E*F */
    printf("subgraph cluster_3 {\n  style=filled;\n  fillcolor=lightpink2;\n  label = \"G=E*F\";\n");
    for (i = 0; i < _PB_NI; i++)
        for (j = 0; j < _PB_NL; j++)
        {
            if(i+1<_PB_NJ && i+1<_PB_NI && j+1<_PB_NJ && j+1 < _PB_NL){
                printf("node [pos=\"%d,%d!\" shape=point color=white height=0.2] c%dc%d;\n",i+1,j+1,i,j);
            }
            else{
                if(i+1>=_PB_NJ && i+1<_PB_NI && j+1<_PB_NJ || j+1>=_PB_NL && j+1<_PB_NJ && i+1<_PB_NI){
                    printf("node [pos=\"%d,%d!\" shape=point color=yellow height=0.2] c%dc%d;\n",i+1,j+1,i,j);
                }
                else{
                    if(i+1<_PB_NJ && i+1>=_PB_NI && j+1<_PB_NL || j+1>=_PB_NJ && j+1<_PB_NL && i+1<_PB_NJ){
                    printf("node [pos=\"%d,%d!\" shape=point color=purple height=0.2] c%dc%d;\n",i+1,j+1,i,j);
                    }
                    else{
                    printf("node [pos=\"%d,%d!\" shape=point color=red height=0.2] c%dc%d;\n",i+1,j+1,i,j);
                    }
                }

            }
       }
    printf("}\n");
      printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=red ];\nG\n",0,-1,0,-1);
      printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=green ];\nE\n",1,-1,1,-1);
      printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=blue ];\nF\n",2,-1,2,-1);
printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=purple ];\n\"G+F\"\n",3,-1,3,-1);
printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=yellow ];\n\"G+E\"\n",4,-1,4,-1);
printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=white ];\n\"G+E+F\"\n",5,-1,5,-1);
printf("node [shape=box,style=filled,pos=\"%d,%d!\", color=cyan ];\n\"E+F\"\n",6,-1,6,-1);
    printf("}\n");
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
