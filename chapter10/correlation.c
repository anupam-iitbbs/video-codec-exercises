/* correlation.c -- Chapter 10: correlation of horizontally adjacent pixels.
 *
 * rho = Cov(X,Y) / (sigmaX * sigmaY),  always in [-1, +1].
 *
 * Here X is each pixel and Y is its right-hand neighbor. For natural
 * images rho is typically about 0.95, the statistical reason spatial
 * prediction works so well.
 *
 * Build:  cc -O2 -o correlation correlation.c
 */
#include <stdio.h>
#include <math.h>

#define W 8
#define H 8

int main(void) {
    /* Smooth demo image: adjacent pixels are very close in value. */
    unsigned char img[H][W] = {
        {100,101,101,102,102,103,103,104},
        {101,101,102,102,103,103,104,104},
        {101,102,102,103,103,104,104,105},
        {102,102,103,103,104,104,105,105},
        {102,103,103,104,104,105,105,106},
        {103,103,104,104,105,105,106,106},
        {103,104,104,105,105,106,106,107},
        {104,104,105,105,106,106,107,107}
    };

    double sx = 0, sy = 0, sxx = 0, syy = 0, sxy = 0;
    long n = 0;
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W - 1; ++x) {
            double a = img[y][x], b = img[y][x + 1];
            sx += a; sy += b;
            sxx += a * a; syy += b * b; sxy += a * b;
            ++n;
        }
    }
    double cov = sxy / n - (sx / n) * (sy / n);
    double vx  = sxx / n - (sx / n) * (sx / n);
    double vy  = syy / n - (sy / n) * (sy / n);
    double rho = cov / sqrt(vx * vy);

    printf("pairs = %ld\n", n);
    printf("horizontal correlation rho = %.4f\n", rho);
    return 0;
}
