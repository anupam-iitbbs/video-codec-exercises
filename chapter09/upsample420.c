/*
 * upsample420.c -- Chapter 9, Exercise 4
 *
 * Reconstruct a 4:2:0 image: upsample the quarter-resolution
 * chrominance back to full resolution and recombine it with the
 * full-resolution luminance. Here we use simple nearest-neighbor
 * (pixel replication) upsampling; real codecs use smoother filters.
 */

#include <stdio.h>

#define W 4
#define H 4

/* Replicate each 4:2:0 chroma sample over its 2x2 luma block. */
static void upsample_420(const int in[H/2][W/2], int out[H][W])
{
    int y, x;
    for (y = 0; y < H; y++)
        for (x = 0; x < W; x++)
            out[y][x] = in[y/2][x/2];
}

int main(void)
{
    /* Full-resolution luminance (kept intact). */
    int luma[H][W] = {
        { 60,  62, 200, 205},
        { 64,  66, 210, 215},
        { 90,  92, 130, 132},
        { 94,  96, 134, 136},
    };
    /* Quarter-resolution chroma (one sample per 2x2 luma block). */
    int chroma420[H/2][W/2] = {
        {103, 123},
        { 83, 143},
    };
    int chroma_full[H][W];
    int y, x;

    upsample_420(chroma420, chroma_full);

    printf("reconstructed chroma plane (full resolution):\n");
    for (y = 0; y < H; y++) {
        for (x = 0; x < W; x++) printf("%4d", chroma_full[y][x]);
        printf("\n");
    }
    printf("luma is untouched at full resolution (%d samples)\n", W * H);
    return 0;
}
