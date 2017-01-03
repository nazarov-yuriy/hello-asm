void matrix_multiply(double *a, double *b, double *c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double t = 0;
            for (int k = 0; k < n; k++) {
                t += a[i * n + k] * b[k * n + j];
            }
            c[i * n + j] = t;
        }
    }
}
