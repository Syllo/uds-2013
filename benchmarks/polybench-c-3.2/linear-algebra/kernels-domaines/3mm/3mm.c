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
    struct table *ddv_table;
    int indices[DIMENSION];
    int memref[DIMENSION];

    ddv_table=NULL;

    printf("digraph G {\n  rankdir=\"LR\";\n  edge[style=\"\",dir=\"forward\"];\n");

    SUB_CLUST(1)
        for (i = 0; i < _PB_NI; i++)
            for (j = 0; j < _PB_NJ; j++)
            {
#ifdef dom_a
                printf("node [pos=\"%d,%d!\" shape=point color=green height=0.2] a%da%d;\n",i,j,i,j);
                printf("edge[style=\"invisible\" dir=\"none\"];\n");
                printf("edge[style=\"\" dir=\"forward\"];\n");
                printf("edge[color=green];\n");
                DDV_FUSE(i,j,i,j,'a','e',1)
#endif
                    E[i][j] = 0;
                for (k = 0; k < _PB_NK; ++k)
                    E[i][j] += A[i][k] * B[k][j];
            }
    printf("}\n");
    /* F := C*D */
    SUB_CLUST(2)
        for (i = 0; i < _PB_NJ; i++)
            for (j = 0; j < _PB_NL; j++)
            {
                F[i][j] = 0;
#ifdef dom_b
                printf("node [pos=\"%d,%d!\" shape=point color=blue height=0.2] b%db%d;\n",i+_PB_NI,j+_PB_NJ+2,i,j);
                printf("edge[style=\"invisible\" dir=\"none\"];\n");
                printf("edge[style=\"\" dir=\"forward\"];\n");
                printf("edge[color=blue];\n");
                DDV_FUSE(i,j,i,j,'b','f',1)
#endif
                    for (k = 0; k < _PB_NM; ++k)
                        F[i][j] += C[i][k] * D[k][j];
            }
    printf("}\n");
    /* G := E*F */
    SUB_CLUST(3)
        for (i = 0; i < _PB_NI; i++)
            for (j = 0; j < _PB_NL; j++)
            {
                G[i][j] = 0;
                for (k = 0; k < _PB_NJ; ++k){
#ifdef dom_c
                    printf("node [pos=\"%d,%d!\" shape=point color=yellow height=0.2] c%dc%d;\n",i+_PB_NI+2,j+_PB_NJ-2,i,j);
                    printf("edge[style=\"invisible\" dir=\"none\"];\n");
                    printf("edge[style=\"\" dir=\"forward\"];\n");
                    printf("edge[color=red];\n");
                    DDV_FUSE(i,j,k,j,'c','e',0)
                        DDV_FUSE(i,j,i,k,'c','f',0)
#endif
                    G[i][j] += E[i][k] * F[k][j];
                }
            }
    printf("}\n");
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
