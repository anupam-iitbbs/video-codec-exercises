/* predict_pixels.c -- Chapter 10: predict each pixel from its neighbor.
 *
 * Predictor:  xhat[n] = x[n-1]
 * Error:      e[n] = x[n] - xhat[n]
 *
 * Reports the prediction error for each pixel and the mean absolute
 * error. Small errors mean the pixels are highly correlated -- the
 * statistical basis of intra prediction.
 *
 * Build:  cc -O2 -o predict_pixels predict_pixels.c
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int x[] = {50, 52, 53, 55, 56, 55, 57, 58};
    int n = sizeof(x) / sizeof(x[0]);

    long abs_sum = 0;
    printf("n   x[n]  pred  error\n");
    for (int i = 0; i < n; ++i) {
        int pred  = (i == 0) ? x[0] : x[i - 1];
        int err   = x[i] - pred;
        abs_sum  += abs(err);
        printf("%d   %4d  %4d  %4d\n", i, x[i], pred, err);
    }
    printf("mean absolute error = %.3f\n", (double)abs_sum / n);
    printf("(small error => strong correlation => good prediction)\n");
    return 0;
}
