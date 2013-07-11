#define S1(i,j) tmp[i][j]=0;
#define S2(i,j,k) tmp[i][j]+=alpha*A[i][k]*B[k][j];
#define S3(i,j) D[i][j]*=beta;
#define S4(i,j,k) D[i][j]+=tmp[i][k]*C[k][j];
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
            S3(c1, c2);
            S1(c1, c2);
          }
        }
      }
            for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round((((_PB_NJ * (1 / T1c2)) + (_PB_NL * (1 / T1c2))) + ((1 / T1c2) * -2))); ++(c2t1)) {
                for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                    for (c2 = max((c2t1 * T1c2), _PB_NL); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NJ + -1)); c2++) {
            S1(c1, c2);
          }
        }
      }
            for (c2t1 = round((-1 + (1 / T1c2))); c2t1 <= round((((_PB_NJ * (1 / T1c2)) + (_PB_NL * (1 / T1c2))) + ((1 / T1c2) * -2))); ++(c2t1)) {
                for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                    for (c2 = max((c2t1 * T1c2), _PB_NJ); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NL + -1)); c2++) {
            S3(c1, c2);
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
            S1(c1, c2);
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
            S3(c1, c2);
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
                S2(c1, c2, c5);
              }
            }
          }
        }
                for (c5t1 = round((-1 + (1 / T1c5))); c5t1 <= round((((_PB_NK * (1 / T1c5)) + (_PB_NL * (1 / T1c5))) + ((1 / T1c5) * -2))); ++(c5t1)) {
                    for (c1 = max((c1t1 * T1c1), 0); c1 <= min(((c1t1 * T1c1) + (T1c1 + -1)), (_PB_NI + -1)); c1++) {
                        for (c2 = max((c2t1 * T1c2), 0); c2 <= min(((c2t1 * T1c2) + (T1c2 + -1)), (_PB_NJ + -1)); c2++) {
                            for (c5 = max((c5t1 * T1c5), 0); c5 <= min(((c5t1 * T1c5) + (T1c5 + -1)), (_PB_NL + -1)); c5++) {
                S4(c1, c5, c2);
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
                S2(c1, c2, c5);
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
                S4(c1, c5, c2);
              }
            }
          }
        }
      }
    }
  }
}
#pragma endscop
