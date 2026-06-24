/* histogram.c -- Chapter 10: intensity histogram of an 8-bit image.
 *
 * Counts how many pixels take each value 0..255 and prints the
 * histogram. A distribution concentrated on few values signals
 * redundancy that compression can exploit.
 *
 * Build:  cc -O2 -o histogram histogram.c
 * Usage:  ./histogram            (uses a small built-in demo image)
 */
#include <stdio.h>

#define W 8
#define H 8

int main(void) {
    /* Tiny smooth demo image (values clustered, not spread out). */
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

    long hist[256] = {0};
    for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x)
            hist[img[y][x]]++;

    printf("value  count  bar\n");
    for (int v = 0; v < 256; ++v) {
        if (hist[v] == 0) continue;
        printf("%5d  %5ld  ", v, hist[v]);
        for (long b = 0; b < hist[v]; ++b) putchar('#');
        putchar('\n');
    }
    return 0;
}
