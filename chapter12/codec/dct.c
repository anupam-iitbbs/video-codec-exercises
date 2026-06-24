/* chapter12/codec/dct.c
 * Forward and inverse 2D DCT for a 4x4 block (Chapter 12 minimal codec).
 * Uses the separable type-II DCT applied to rows then columns.
 */
#include <stdio.h>
#include <math.h>

#define N 4

static double C(int k) { return k == 0 ? sqrt(1.0/N) : sqrt(2.0/N); }

void dct2_forward(const double in[N][N], double out[N][N]) {
    for (int u = 0; u < N; u++)
        for (int v = 0; v < N; v++) {
            double sum = 0.0;
            for (int x = 0; x < N; x++)
                for (int y = 0; y < N; y++)
                    sum += in[x][y]
                         * cos((2*x+1)*u*M_PI/(2*N))
                         * cos((2*y+1)*v*M_PI/(2*N));
            out[u][v] = C(u) * C(v) * sum;
        }
}

void dct2_inverse(const double in[N][N], double out[N][N]) {
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
            double sum = 0.0;
            for (int u = 0; u < N; u++)
                for (int v = 0; v < N; v++)
                    sum += C(u) * C(v) * in[u][v]
                         * cos((2*x+1)*u*M_PI/(2*N))
                         * cos((2*y+1)*v*M_PI/(2*N));
            out[x][y] = sum;
        }
}

int main(void) {
    double x[N][N] = {
        {101,102,103,103},
        {102,103,104,104},
        {102,103,104,105},
        {103,104,105,105}
    };
    double X[N][N], rec[N][N];
    dct2_forward(x, X);
    dct2_inverse(X, rec);
    printf("DC coefficient X[0][0] = %.2f\n", X[0][0]);
    printf("Round-trip pixel rec[0][0] = %.2f (orig 101)\n", rec[0][0]);
    return 0;
}
