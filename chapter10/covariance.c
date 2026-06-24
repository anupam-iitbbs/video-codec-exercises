/* covariance.c -- Chapter 10: covariance between two pixel sets.
 *
 * Cov(X,Y) = E[(X - meanX)(Y - meanY)]
 *
 * A positive covariance means X and Y rise and fall together; a value
 * near zero means they are unrelated. Neighboring pixels in a natural
 * image have a strongly positive covariance.
 *
 * Build:  cc -O2 -o covariance covariance.c
 */
#include <stdio.h>

int main(void) {
    double X[] = {2, 4, 6};
    double Y[] = {3, 5, 7};
    int n = sizeof(X) / sizeof(X[0]);

    double mx = 0, my = 0;
    for (int i = 0; i < n; ++i) { mx += X[i]; my += Y[i]; }
    mx /= n; my /= n;

    double cov = 0;
    for (int i = 0; i < n; ++i)
        cov += (X[i] - mx) * (Y[i] - my);
    cov /= n;

    printf("meanX = %.3f  meanY = %.3f\n", mx, my);
    printf("Cov(X,Y) = %.4f", cov);
    if (cov > 0)      printf("  (positive: they move together)\n");
    else if (cov < 0) printf("  (negative: they move oppositely)\n");
    else              printf("  (zero: unrelated)\n");
    return 0;
}
