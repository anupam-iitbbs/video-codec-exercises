/* chapter12/codec/quant.c
 * Scalar quantization and dequantization for DCT coefficients.
 * Chapter 12 minimal codec. The step Q is derived from a QP.
 */
#include <stdio.h>
#include <math.h>

#define N 4

int quant(double coeff, int Q) {
    return (int)round(coeff / (double)Q);
}

double dequant(int level, int Q) {
    return (double)level * (double)Q;
}

int main(void) {
    /* Example transformed block (smooth: large DC, tiny AC). */
    double X[N][N] = {
        {416,-6, 0, 0},
        {-5, 1, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0}
    };
    int Q = 8;
    int nonzero = 0;
    printf("Quantized levels (Q=%d):\n", Q);
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            int q = quant(X[u][v], Q);
            if (q != 0) nonzero++;
            printf("%4d", q);
        }
        printf("\n");
    }
    printf("Surviving nonzero coefficients: %d of %d\n", nonzero, N*N);
    return 0;
}
