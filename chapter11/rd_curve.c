/* rd_curve.c -- Chapter 11: print a rate-distortion curve as ASCII.
 *
 * Reads a set of (rate, distortion) operating points and draws a
 * simple text plot of distortion versus rate, showing the
 * characteristic steep-then-flat shape.
 *
 * Build:  cc -O2 -o rd_curve rd_curve.c
 */
#include <stdio.h>

int main(void) {
    /* Operating points: rate (arbitrary units) and distortion. */
    double rate[] = {1, 2, 3, 4, 5, 6};
    double dist[] = {200, 90, 45, 25, 16, 12};
    int n = sizeof(rate) / sizeof(rate[0]);

    /* Find max distortion for scaling the bar plot. */
    double dmax = 0;
    for (int i = 0; i < n; ++i) if (dist[i] > dmax) dmax = dist[i];

    printf("rate  distortion\n");
    for (int i = 0; i < n; ++i) {
        printf("%3.0f   %6.1f  ", rate[i], dist[i]);
        int bars = (int)(dist[i] / dmax * 40.0 + 0.5);
        for (int b = 0; b < bars; ++b) putchar('*');
        putchar('\n');
    }
    printf("(steep first, flat later -> diminishing returns)\n");
    return 0;
}
