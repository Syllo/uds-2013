#include <math.h>
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
    int i, j, k;
    int T1c1=1,T1c2=1,T1c5=1;

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
    register int c1t1, c2t1, c1, c2, c5t1, c5;
#pragma scop
    if ((_PB_NI >= 1)) {
        if (((_PB_NJ >= 1) && (_PB_NL >= 1))) {
            lb1 = round((-1 + (1 / T1c1)));
            ub1 = round(((_PB_NI * (1 / T1c1)) + ((1 / T1c1) * -1)));
#pragma omp parallel for private(c2t1, c1, c2) firstprivate(lb1, ub1)
            for (c1t1 = lb1; c1t1 <= ub1; ++(c1t1)) {
                for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round((((_PB_NJ * (1 / T1c2)) + (_PB_NL * (1 / T1c2))) + ((1 / T1c2) * -2))); ++(c2t1)) {
                    for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                        for (c2 = max((c2t1 * T1c2), 0); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), min((_PB_NJ + -1), (_PB_NL + -1))); c2++) {
                            D[c1][c2]*=beta;
                            tmp[c1][c2]=0;
                        }
                    }
                }
                for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round((((_PB_NJ * (1 / T1c2)) + (_PB_NL * (1 / T1c2))) + ((1 / T1c2) * -2))); ++(c2t1)) {
                    for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                        for (c2 = max((c2t1 * T1c2), _PB_NL); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NJ + -1)); c2++) {
                            tmp[c1][c2]=0;
                        }
                    }
                }
                for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round((((_PB_NJ * (1 / T1c2)) + (_PB_NL * (1 / T1c2))) + ((1 / T1c2) * -2))); ++(c2t1)) {
                    for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                        for (c2 = max((c2t1 * T1c2), _PB_NJ); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NL + -1)); c2++) {
                            D[c1][c2]*=beta;
                        }
                    }
                }
            }
        }
        if (((_PB_NJ >= 1) && _PB_NL <= 0)) {
            lb1 = round((-1 + (1 / T1c1)));
            ub1 = round(((_PB_NI * (1 / T1c1)) + ((1 / T1c1) * -1)));
#pragma omp parallel for private(c2t1, c1, c2) firstprivate(lb1, ub1)
            for (c1t1 = lb1; c1t1 <= ub1; ++(c1t1)) {
                for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round(((_PB_NJ * (1 / T1c2)) + ((1 / T1c2) * -1))); ++(c2t1)) {
                    for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                        for (c2 = max((c2t1 * T1c2), 0); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NJ + -1)); c2++) {
                            tmp[c1][c2]=0;
                        }
                    }
                }
            }
        }
        if ((_PB_NJ <= 0 && (_PB_NL >= 1))) {
            lb1 = round((-1 + (1 / T1c1)));
            ub1 = round(((_PB_NI * (1 / T1c1)) + ((1 / T1c1) * -1)));
#pragma omp parallel for private(c2t1, c1, c2) firstprivate(lb1, ub1)
            for (c1t1 = lb1; c1t1 <= ub1; ++(c1t1)) {
                for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round(((_PB_NL * (1 / T1c2)) + ((1 / T1c2) * -1))); ++(c2t1)) {
                    for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                        for (c2 = max((c2t1 * T1c2), 0); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NL + -1)); c2++) {
                            D[c1][c2]*=beta;
                        }
                    }
                }
            }
        }
        if ((((_PB_NJ >= 1) && (_PB_NK >= 1)) && (_PB_NL >= 1))) {
            lb1 = round((-1 + (1 / T1c1)));
            ub1 = round(((_PB_NI * (1 / T1c1)) + ((1 / T1c1) * -1)));
#pragma omp parallel for private(c2t1, c5t1, c1, c2, c5) firstprivate(lb1, ub1)
            for (c1t1 = lb1; c1t1 <= ub1; ++(c1t1)) {
                for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round(((_PB_NJ * (1 / T1c2)) + ((1 / T1c2) * -1))); ++(c2t1)) {
                    for (c5t1 = round((-1 + (1 / T1c5))); c5t1 <= round((((_PB_NK * (1 / T1c5)) + (_PB_NL * (1 / T1c5))) + ((1 / T1c5) * -2))); ++(c5t1)) {
                        for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                            for (c2 = max((c2t1 * T1c2), 0); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NJ + -1)); c2++) {
                                for (c5 = max((c5t1 * T1c5), 0); c5 <= min(((c5t1 * T1c5) + (T1c5 + -1)), (_PB_NK + -1)); c5++) {
                                    tmp[c1][c2]+=alpha*A[c1][c5]*B[c5][c2];
                                }
                            }
                        }
                    }
                    for (c5t1 = round((-1 + (1 / T1c5))); c5t1 <= round((((_PB_NK * (1 / T1c5)) + (_PB_NL * (1 / T1c5))) + ((1 / T1c5) * -2))); ++(c5t1)) {
                        for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                            for (c2 = max((c2t1 * T1c2), 0); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NJ + -1)); c2++) {
                                for (c5 = max((c5t1 * T1c5), 0); c5 <= min(((c5t1 * T1c5) + (T1c5 + -1)), (_PB_NL + -1)); c5++) {
                                    D[c1][c5]+=tmp[c1][c2]*C[c2][c5];
                                }
                            }
                        }
                    }
                }
            }
        }
        if ((((_PB_NJ >= 1) && (_PB_NK >= 1)) && _PB_NL <= 0)) {
            lb1 = round((-1 + (1 / T1c1)));
            ub1 = round(((_PB_NI * (1 / T1c1)) + ((1 / T1c1) * -1)));
#pragma omp parallel for private(c2t1, c5t1, c1, c2, c5) firstprivate(lb1, ub1)
            for (c1t1 = lb1; c1t1 <= ub1; ++(c1t1)) {
                for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round(((_PB_NJ * (1 / T1c2)) + ((1 / T1c2) * -1))); ++(c2t1)) {
                    for (c5t1 = round((-1 + (1 / T1c5))); c5t1 <= round(((_PB_NK * (1 / T1c5)) + ((1 / T1c5) * -1))); ++(c5t1)) {
                        for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                            for (c2 = max((c2t1 * T1c2), 0); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NJ + -1)); c2++) {
                                for (c5 = max((c5t1 * T1c5), 0); c5 <= min(((c5t1 * T1c5) + (T1c5 + -1)), (_PB_NK + -1)); c5++) {
                                    tmp[c1][c2]+=alpha*A[c1][c5]*B[c5][c2];
                                }
                            }
                        }
                    }
                }
            }
        }
        if ((((_PB_NJ >= 1) && _PB_NK <= 0) && (_PB_NL >= 1))) {
            lb1 = round((-1 + (1 / T1c1)));
            ub1 = round(((_PB_NI * (1 / T1c1)) + ((1 / T1c1) * -1)));
#pragma omp parallel for private(c2t1, c5t1, c1, c2, c5) firstprivate(lb1, ub1)
            for (c1t1 = lb1; c1t1 <= ub1; ++(c1t1)) {
                for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round(((_PB_NJ * (1 / T1c2)) + ((1 / T1c2) * -1))); ++(c2t1)) {
                    for (c5t1 = round((-1 + (1 / T1c5))); c5t1 <= round(((_PB_NL * (1 / T1c5)) + ((1 / T1c5) * -1))); ++(c5t1)) {
                        for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                            for (c2 = max((c2t1 * T1c2), 0); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NJ + -1)); c2++) {
                                for (c5 = max((c5t1 * T1c5), 0); c5 <= min(((c5t1 * T1c5) + (T1c5 + -1)), (_PB_NL + -1)); c5++) {
                                    D[c1][c5]+=tmp[c1][c2]*C[c2][c5];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
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
    print_array(ni, nl, POLYBENCH_ARRAY(D));
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
