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
        for (int j = 0; j < n; j += 4) {
            double t0 = 0;
            double t1 = 0;
            double t2 = 0;
            double t3 = 0;
            for (int k = 0; k < n; k++) {
                t0 += a[i * n + k] * b[(j + 0) * n + k];
                t1 += a[i * n + k] * b[(j + 1) * n + k];
                t2 += a[i * n + k] * b[(j + 2) * n + k];
                t3 += a[i * n + k] * b[(j + 3) * n + k];
            }
            c[i * n + j + 0] = t0;
            c[i * n + j + 1] = t1;
            c[i * n + j + 2] = t2;
            c[i * n + j + 3] = t3;
        }
    }
}
