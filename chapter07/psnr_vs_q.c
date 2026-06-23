/*
 * psnr_vs_q.c  --  Chapter 7: Quantization
 *
 * Sweep the quantizer step size and watch quality (PSNR) fall.
 * Because quantization noise power is Delta^2 / 12, PSNR drops by a
 * roughly fixed number of dB each time Delta doubles -- the steady
 * "quality slider" behaviour of every codec.
 *
 * Build: gcc -O2 -o psnr_vs_q psnr_vs_q.c -lm
 */

#include <stdio.h>
#include <math.h>

int main(void) {
    /* A small test signal (8-bit sample values). */
    double x[] = {52, 55, 61, 66, 70, 61, 64, 73,
                  63, 59, 55, 90, 109, 85, 69, 72};
    int n = sizeof(x) / sizeof(x[0]);

    printf("%8s %12s %10s\n", "Delta", "MSE", "PSNR(dB)");
    for (double delta = 2.0; delta <= 64.0; delta *= 2.0) {
        double se = 0.0;
        for (int i = 0; i < n; i++) {
            int    q    = (int)lround(x[i] / delta);
            double xhat = q * delta;
            double e    = x[i] - xhat;
            se += e * e;
        }
        double mse  = se / n;
        double psnr = (mse > 0.0) ? 10.0 * log10(255.0*255.0 / mse) : INFINITY;
        printf("%8.1f %12.4f %10.2f\n", delta, mse, psnr);
    }
    return 0;
}
