/* mse.c -- Chapter 11: mean squared error between two images.
 *
 * MSE = (1/MN) sum (f - fhat)^2
 *
 * The squaring punishes large errors far more than small ones.
 *
 * Build:  cc -O2 -o mse mse.c
 */
#include <stdio.h>

#define N 8

int main(void) {
    /* Original and reconstructed 1-D signals (stand-in for an image). */
    int f[N]    = {10, 20, 30, 40, 50, 60, 70, 80};
    int fhat[N] = {12, 18, 33, 38, 52, 59, 68, 83};

    long sq = 0;
    for (int i = 0; i < N; ++i) {
        int e = f[i] - fhat[i];
        sq += (long)e * e;
    }
    double mse = (double)sq / N;

    printf("MSE = %.4f\n", mse);
    return 0;
}
