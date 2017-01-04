#include <immintrin.h>

void __attribute__ ((noinline)) transpose(double *b, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double t = b[i * n + j];
            b[i * n + j] = b[j * n + i];
            b[j * n + i] = t;
        }
    }
}

void matrix_multiply(double *a, double *b, double *c, int n) {
    transpose(b, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            __m256d t0 = _mm256_set_pd(0, 0, 0, 0);
            __m256d t1 = _mm256_set_pd(0, 0, 0, 0);
            __m256d t2 = _mm256_set_pd(0, 0, 0, 0);
            __m256d t3 = _mm256_set_pd(0, 0, 0, 0);
            for (int k = 0; k < n; k += 16) {
                __m256d a0 = _mm256_load_pd(&a[i * n + k + 0]);
                __m256d a1 = _mm256_load_pd(&a[i * n + k + 4]);
                __m256d a2 = _mm256_load_pd(&a[i * n + k + 8]);
                __m256d a3 = _mm256_load_pd(&a[i * n + k + 12]);

                __m256d b0 = _mm256_load_pd(&b[j * n + k + 0]);
                __m256d b1 = _mm256_load_pd(&b[j * n + k + 4]);
                __m256d b2 = _mm256_load_pd(&b[j * n + k + 8]);
                __m256d b3 = _mm256_load_pd(&b[j * n + k + 12]);

                t0 = _mm256_fmadd_pd(a0, b0, t0);
                t1 = _mm256_fmadd_pd(a1, b1, t1);
                t2 = _mm256_fmadd_pd(a2, b2, t2);
                t3 = _mm256_fmadd_pd(a3, b3, t3);
            }
            c[i * n + j + 0] =
                    ((double *) &t0)[0] + ((double *) &t0)[1] + ((double *) &t0)[2] + ((double *) &t0)[3] +
                    ((double *) &t1)[0] + ((double *) &t1)[1] + ((double *) &t1)[2] + ((double *) &t1)[3] +
                    ((double *) &t2)[0] + ((double *) &t2)[1] + ((double *) &t2)[2] + ((double *) &t2)[3] +
                    ((double *) &t3)[0] + ((double *) &t3)[1] + ((double *) &t3)[2] + ((double *) &t3)[3];
        }
    }
}
