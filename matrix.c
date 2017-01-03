#include <immintrin.h>

void __attribute__ ((noinline)) transpose4(double *m, int n) {
    for (int i = 0; i < n; i += 4) {
        for (int j = i + 4; j < n; j += 4) {
            __m256d a = _mm256_load_pd(&m[(i + 0) * n + j]);
            __m256d b = _mm256_load_pd(&m[(i + 1) * n + j]);
            __m256d c = _mm256_load_pd(&m[(i + 2) * n + j]);
            __m256d d = _mm256_load_pd(&m[(i + 3) * n + j]);

            _mm256_store_pd(&m[(j + 0) * n + i], a);
            _mm256_store_pd(&m[(j + 1) * n + i], b);
            _mm256_store_pd(&m[(j + 2) * n + i], c);
            _mm256_store_pd(&m[(j + 3) * n + i], d);
        }
    }
}

void matrix_multiply(double *a, double *b, double *c, int n) {
    transpose4(b, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j += 4) {
            __m256d t4 = _mm256_set_pd(0, 0, 0, 0);
            for (int k = 0; k < n; k++) {
                __m256d a4 = _mm256_set_pd(a[i * n + k], a[i * n + k], a[i * n + k], a[i * n + k]);
                __m256d b4 = _mm256_load_pd(&b[j * n + k]);
                t4 = _mm256_fmadd_pd(a4, b4, t4);
            }
            _mm256_store_pd(&c[i * n + j], t4);
        }
    }
}
