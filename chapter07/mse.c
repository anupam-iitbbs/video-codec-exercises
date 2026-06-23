/*
 * mse.c  --  Chapter 7: Quantization
 *
 * Mean Squared Error and PSNR between an original signal and its
 * quantized reconstruction. MSE is the raw material of every quality
 * metric in video coding.
 *
 *   MSE  = (1/N) * sum( (x - xhat)^2 )
 *   PSNR = 10 * log10( MAX^2 / MSE )      (MAX = 255 for 8-bit)
 *
 * Build: gcc -O2 -o mse mse.c -lm
 */

#include <stdio.h>
#include <math.h>

double mse(const double *x, const double *xhat, int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++) {
        double e = x[i] - xhat[i];
        s += e * e;
    }
    return s / n;
}

double psnr(double mse_val, double max_val) {
    if (mse_val <= 0.0) return INFINITY;
    return 10.0 * log10((max_val * max_val) / mse_val);
}

int main(void) {
    /* Worked Example 7.2: errors were 1, -1, 1, -2  =>  MSE = 1.75 */
    double x[]    = {21, 24, 26, 28};
    double xhat[] = {20, 25, 25, 30};
    int    n      = sizeof(x) / sizeof(x[0]);

    double m = mse(x, xhat, n);
    printf("MSE  = %.4f\n", m);
    printf("PSNR = %.2f dB (vs 8-bit max 255)\n", psnr(m, 255.0));
    return 0;
}
