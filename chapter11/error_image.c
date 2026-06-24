/* error_image.c -- Chapter 11: build the difference (error) image.
 *
 * For each pixel, e = f - fhat. To make small errors visible, the
 * error is shifted by 128 (mid-grey = zero error) and clamped to
 * 0..255. The result is written as a PGM image you can open and view.
 *
 * Build:  cc -O2 -o error_image error_image.c
 * Usage:  ./error_image  > diff.pgm
 */
#include <stdio.h>

#define W 8
#define H 8

static int clamp(int v) { return v < 0 ? 0 : (v > 255 ? 255 : v); }

int main(void) {
    unsigned char f[H][W], fhat[H][W];

    /* Synthesize an original (smooth ramp) and a reconstruction
       that differs mostly along one diagonal "edge". */
    for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x) {
            f[y][x]    = (unsigned char)(40 + 12 * x);
            fhat[y][x] = f[y][x];
            if (x == y) fhat[y][x] = (unsigned char)clamp(f[y][x] + 30);
        }

    /* Emit the error image as PGM (mid-grey = zero error). */
    printf("P2\n%d %d\n255\n", W, H);
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            int e = (int)f[y][x] - (int)fhat[y][x];
            printf("%d ", clamp(e + 128));
        }
        printf("\n");
    }
    return 0;
}
