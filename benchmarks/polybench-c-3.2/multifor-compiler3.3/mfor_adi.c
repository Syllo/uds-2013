/**
 * adi.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

/* Include polybench common header. */
#include "polybench.h"

#include "minmax.h"

/* Include benchmark-specific header. */
/* Default data type is double, default size is 10x1024x1024. */
#include "adi.h"


struct timeval start, end;

/* Array initialization. */
static
void init_array (int n,
		 DATA_TYPE POLYBENCH_2D(X,N,N,n,n),
		 DATA_TYPE POLYBENCH_2D(A,N,N,n,n),
		 DATA_TYPE POLYBENCH_2D(B,N,N,n,n))
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      {
	X[i][j] = ((DATA_TYPE) i*(j+1) + 1) / n;
	A[i][j] = ((DATA_TYPE) i*(j+2) + 2) / n;
	B[i][j] = ((DATA_TYPE) i*(j+3) + 3) / n;
      }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int n,
		 DATA_TYPE POLYBENCH_2D(X,N,N,n,n))

{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      fprintf(stderr, DATA_PRINTF_MODIFIER, X[i][j]);
      if ((i * N + j) % 20 == 0) fprintf(stderr, "\n");
    }
  fprintf(stderr, "\n");
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */

void kernel_adi(int tsteps,
		int n,
		DATA_TYPE POLYBENCH_2D(X,N,N,n,n),
		DATA_TYPE POLYBENCH_2D(A,N,N,n,n),
		DATA_TYPE POLYBENCH_2D(B,N,N,n,n))
{
  int t, i1, i2;

#pragma scop
/*  for (t = 0; t < _PB_TSTEPS; t++)
    { */
 gettimeofday(&start, NULL);
  
 /*     for (i1 = 0; i1 < _PB_N; i1++)
	for (i2 = 1; i2 < _PB_N; i2++)
	  {
	    X[i1][i2] = X[i1][i2] - X[i1][i2-1] * A[i1][i2] / B[i1][i2-1];
	    B[i1][i2] = B[i1][i2] - A[i1][i2] * A[i1][i2] / B[i1][i2-1];
	  }


      for (i1 = 0; i1 < _PB_N; i1++)
	X[i1][_PB_N-1] = X[i1][_PB_N-1] / B[i1][_PB_N-1];


      for (i1 = 0; i1 < _PB_N; i1++)
	for (i2 = 0; i2 < _PB_N-2; i2++)
	  X[i1][_PB_N-i2-2] = (X[i1][_PB_N-2-i2] - X[i1][_PB_N-2-i2-1] * A[i1][_PB_N-i2-3]) / B[i1][_PB_N-3-i2];


      for (i1 = 1; i1 < _PB_N; i1++)
	for (i2 = 0; i2 < _PB_N; i2++) {
	  X[i1][i2] = X[i1][i2] - X[i1-1][i2] * A[i1][i2] / B[i1-1][i2];
	  B[i1][i2] = B[i1][i2] - A[i1][i2] * A[i1][i2] / B[i1-1][i2];
	}


      for (i2 = 0; i2 < _PB_N; i2++)
	X[_PB_N-1][i2] = X[_PB_N-1][i2] / B[_PB_N-1][i2];


      for (i1 = 0; i1 < _PB_N-2; i1++)
	for (i2 = 0; i2 < _PB_N; i2++)
	  X[_PB_N-2-i1][i2] = (X[_PB_N-2-i1][i2] - X[_PB_N-i1-3][i2] * A[_PB_N-3-i1][i2]) / B[_PB_N-2-i1][i2]; */

int i11,i21,i31,i41,i51,i61,j21, j22, j32, j42, j52, j62;

multifor(i11 = 0, i21 = 0, i31 = 0, i41 = 1, i51 = 0, i61 = 0; i11 < _PB_N, i21 < _PB_N, i31 < _PB_N, i41 < _PB_N, i51 < 1, i61 < _PB_N-2 ; i11++,i21++,i31++,i41++,i51++,i61++; 1,1,1,1,1,1; 0,0,0,1,_PB_N-1,_PB_N-1)
  multifor(j21 = 0, j22 = 0, j32 = 0, j42 = 0, j52 = 0, j62 = 0; j21 < _PB_N, j22 < 0, j32 < _PB_N-2, j42 < _PB_N, j52 < _PB_N, j62 < _PB_N ; j21++,j22++,j32++,j42++,j52++,j62++; 1,1,1,1,1,1; 0,_PB_N-1,_PB_N-3,2*_PB_N-6,2*_PB_N-6,2*_PB_N-6)
  {
    0 : {
          X[i11][j21] = X[i11][j21] - X[i11][j21-1] * A[i11][j21] / B[i11][j21-1];
          B[i11][j21] = B[i11][j21] - A[i11][j21] * A[i11][j21] / B[i11][j21-1];
        }
    1 : X[i21][_PB_N-1] = X[i21][_PB_N-1] / B[i21][_PB_N-1];
    2 : X[i31][_PB_N-j32-2] = (X[i31][_PB_N-2-j32] - X[i31][_PB_N-2-j32-1] * A[i31][_PB_N-j32-3]) / B[i31][_PB_N-3-j32];
    3 : {
          X[i41][j42] = X[i41][j42] - X[i41-1][j42] * A[i41][j42] / B[i41-1][j42];
	  B[i41][j42] = B[i41][j42] - A[i41][j42] * A[i41][j42] / B[i41-1][j42];
        }
    4 : X[_PB_N-1][j52] = X[_PB_N-1][j52] / B[_PB_N-1][j52];
    5 : X[_PB_N-2-i61][j62] = (X[_PB_N-2-i61][j62] - X[_PB_N-i61-3][j62] * A[_PB_N-3-i61][j62]) / B[_PB_N-2-i61][j62];
  }

gettimeofday(&end, NULL);
printf("the end \n");
printf("%ld TIME \n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));
 //   }
#pragma endscop

}


int main(int argc, char** argv) 
{
  /* Retrieve problem size. */
  int n = N;
  int tsteps = TSTEPS;

  /* Variable declaration/allocation. */
  POLYBENCH_2D_ARRAY_DECL(X, DATA_TYPE, N, N, n, n);
  POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
  POLYBENCH_2D_ARRAY_DECL(B, DATA_TYPE, N, N, n, n);


  /* Initialize array(s). */
  init_array (n, POLYBENCH_ARRAY(X), POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_adi (tsteps, n, POLYBENCH_ARRAY(X),
	      POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(B));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(X)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(X);
  POLYBENCH_FREE_ARRAY(A);
  POLYBENCH_FREE_ARRAY(B);

  return 0;
}
