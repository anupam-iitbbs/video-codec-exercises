/*
 * fft_2d_image.c  -  Chapter 5, Exercise 6
 *
 * Apply a 2D DFT to a small synthetic grayscale image and confirm
 * that the energy clusters at the low-frequency corner (DC and its
 * neighbours), with high-frequency coefficients near zero. This is
 * the energy-compaction property that makes transform coding work.
 *
 * For clarity this uses a direct O(M^2 N^2) 2D DFT, not a fast FFT.
 * It is meant to be read, not to be fast.
 *
 * Build: gcc -O2 -o fft_2d_image fft_2d_image.c -lm
 * Run:   ./fft_2d_image
 */

#include <stdio.h>
#include <math.h>

#define M 8                 /* image height */
#define N 8                 /* image width  */
#define TWO_PI 6.283185307179586

int main(void)
{
    double img[M][N];
    double mag[M][N];

    /* A smooth gradient: brightness rises gently across the block. */
    for (int y = 0; y < M; ++y)
        for (int x = 0; x < N; ++x)
            img[y][x] = 100.0 + 5.0 * (x + y);

    /* Direct 2D DFT: magnitude of each (u,v) coefficient. */
    for (int u = 0; u < M; ++u) {
        for (int v = 0; v < N; ++v) {
            double re = 0.0, im = 0.0;
            for (int y = 0; y < M; ++y) {
                for (int x = 0; x < N; ++x) {
                    double a = TWO_PI * ((double)u * y / M + (double)v * x / N);
                    re += img[y][x] * cos(a);
                    im -= img[y][x] * sin(a);
                }
            }
            mag[u][v] = sqrt(re * re + im * im);
        }
    }

    printf("2D DFT magnitudes (note the huge DC term at [0][0]):\\n\\n");
    for (int u = 0; u < M; ++u) {
        for (int v = 0; v < N; ++v)
            printf("%9.1f", mag[u][v]);
        printf("\\n");
    }
    printf("\\nNearly all the energy sits in the low-frequency corner.\\n");
    return 0;
}
