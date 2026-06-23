/*
 * uniform_quant.c  --  Chapter 7: Quantization
 *
 * The simplest lossy operation in all of media coding:
 *   quantize:   q     = round(x / Delta)
 *   reconstruct: xhat = q * Delta
 *   error:       e    = x - xhat        (|e| <= Delta/2)
 *
 * Build:  gcc -O2 -o uniform_quant uniform_quant.c -lm
 * Run:    ./uniform_quant
 */

#include <stdio.h>
#include <math.h>

int quantize(double x, double delta) {
    return (int)lround(x / delta);
}

double reconstruct(int q, double delta) {
    return q * delta;
}

int main(void) {
    double x[]    = {21, 24, 26, 28};   /* Worked Example 7.1 */
    double delta  = 5.0;
    int    n      = sizeof(x) / sizeof(x[0]);

    printf("Delta = %.1f\n", delta);
    printf("%8s %6s %8s %8s\n", "x", "q", "xhat", "error");
    for (int i = 0; i < n; i++) {
        int    q    = quantize(x[i], delta);
        double xhat = reconstruct(q, delta);
        double e    = x[i] - xhat;
        printf("%8.1f %6d %8.1f %8.1f\n", x[i], q, xhat, e);
    }
    return 0;
}
