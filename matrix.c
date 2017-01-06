#include <immintrin.h>

void __attribute__ ((noinline)) transpose(double *m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double t = m[i * n + j];
            m[i * n + j] = m[j * n + i];
            m[j * n + i] = t;
        }
    }
}

void matrix_multiply(double *a, double *b, double *c, int n) {
    transpose(b, n);
    int si = 20, sj = 16;
    for (int ti = 0; ti < n / si; ti++) {
        for (int tj = 0; tj < n / sj; tj++) {
            for (int pi = 0; pi < si; pi++) {
                for (int pj = 0; pj < sj; pj += 4) {
                    int i = ti * si + pi;
                    int j = tj * sj + pj;
                    double t0 = 0, t1 = 0, t2 = 0, t3 = 0;
                    double t4 = 0, t5 = 0, t6 = 0, t7 = 0;
                    for (int k = 0; k < n; k += 2) {
                        t0 += a[i * n + k + 0] * b[(j + 0) * n + k + 0];
                        t1 += a[i * n + k + 0] * b[(j + 1) * n + k + 0];
                        t2 += a[i * n + k + 0] * b[(j + 2) * n + k + 0];
                        t3 += a[i * n + k + 0] * b[(j + 3) * n + k + 0];
                        t4 += a[i * n + k + 1] * b[(j + 0) * n + k + 1];
                        t5 += a[i * n + k + 1] * b[(j + 1) * n + k + 1];
                        t6 += a[i * n + k + 1] * b[(j + 2) * n + k + 1];
                        t7 += a[i * n + k + 1] * b[(j + 3) * n + k + 1];
                    }
                    c[i * n + j + 0] = t0 + t4;
                    c[i * n + j + 1] = t1 + t5;
                    c[i * n + j + 2] = t2 + t6;
                    c[i * n + j + 3] = t3 + t7;
                }
            }
        }
    }
}
