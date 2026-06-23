/*
 * rd_curve.c  --  Chapter 7: Quantization
 *
 * Trace a rate-distortion curve. For each step size we measure:
 *   distortion  = MSE between original and reconstructed coefficients
 *   rate (proxy) = number of nonzero quantized coefficients
 * As the step size grows, rate falls and distortion rises -- the
 * fundamental trade every encoder navigates.
 *
 * Build: gcc -O2 -o rd_curve rd_curve.c -lm
 */

#include <stdio.h>
#include <math.h>

int main(void) {
    /* A block of DCT coefficients: one big DC and a decaying tail. */
    double C[] = {240, -38, 22, -15, 9, -6, 4, -2,
                  18, -12, 7, -4, 3, -1, 1, 0};
    int n = sizeof(C) / sizeof(C[0]);

    printf("%8s %10s %14s\n", "Delta", "rate(nz)", "distortion(MSE)");
    for (double delta = 2.0; delta <= 64.0; delta *= 2.0) {
        int    nz = 0;
        double se = 0.0;
        for (int i = 0; i < n; i++) {
            int    q    = (int)lround(C[i] / delta);
            double chat = q * delta;
            double e    = C[i] - chat;
            se += e * e;
            if (q != 0) nz++;
        }
        printf("%8.1f %10d %14.4f\n", delta, nz, se / n);
    }
    printf("\nFewer nonzeros => fewer bits => more distortion. That is the curve.\n");
    return 0;
}
