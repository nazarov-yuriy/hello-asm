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
    int si = 100;
    for (int ti = 0; ti < n / si; ti++) {
        for (int j = 0; j < n; j += 8) {
            for (int pi = 0; pi < si; pi++) {
                int i = ti * si + pi;
                double t0 = 0, t1 = 0, t2 = 0, t3 = 0;
                double t4 = 0, t5 = 0, t6 = 0, t7 = 0;
                for (int k = 0; k < n; k++) {
                    t0 += a[i * n + k + 0] * b[(j + 0) * n + k + 0];
                    t1 += a[i * n + k + 0] * b[(j + 1) * n + k + 0];
                    t2 += a[i * n + k + 0] * b[(j + 2) * n + k + 0];
                    t3 += a[i * n + k + 0] * b[(j + 3) * n + k + 0];
                    t4 += a[i * n + k + 0] * b[(j + 4) * n + k + 0];
                    t5 += a[i * n + k + 0] * b[(j + 5) * n + k + 0];
                    t6 += a[i * n + k + 0] * b[(j + 6) * n + k + 0];
                    t7 += a[i * n + k + 0] * b[(j + 7) * n + k + 0];
                }
                c[i * n + j + 0] = t0;
                c[i * n + j + 1] = t1;
                c[i * n + j + 2] = t2;
                c[i * n + j + 3] = t3;
                c[i * n + j + 4] = t4;
                c[i * n + j + 5] = t5;
                c[i * n + j + 6] = t6;
                c[i * n + j + 7] = t7;
            }
        }
    }
}

