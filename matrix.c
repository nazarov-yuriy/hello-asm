void matrix_multiply(double *a, double *b, double *c, int n) {
    //Transpose b
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double t = b[i * n + j];
            b[i * n + j] = b[j * n + i];
            b[j * n + i] = t;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double t = 0;
            for (int k = 0; k < n; k++) {
                t += a[i * n + k] * b[j * n + k];
            }
            c[i * n + j] = t;
        }
    }
}
