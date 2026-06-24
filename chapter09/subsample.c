/*
 * subsample.c -- Chapter 9, Exercise 3
 *
 * Produce 4:2:2 and 4:2:0 chrominance planes from a full-resolution
 * (4:4:4) chrominance plane by averaging. 4:2:2 averages horizontal
 * pairs; 4:2:0 averages each 2x2 block. Luminance is never touched.
 */

#include <stdio.h>

#define W 4
#define H 4

/* 4:2:2 -- average each horizontal pair; width halves, height same. */
static void to_422(const int in[H][W], int out[H][W/2])
{
    int y, x;
    for (y = 0; y < H; y++)
        for (x = 0; x < W/2; x++)
            out[y][x] = (in[y][2*x] + in[y][2*x+1] + 1) / 2;
}

/* 4:2:0 -- average each 2x2 block; width and height both halve. */
static void to_420(const int in[H][W], int out[H/2][W/2])
{
    int y, x;
    for (y = 0; y < H/2; y++)
        for (x = 0; x < W/2; x++)
            out[y][x] = (in[2*y][2*x]   + in[2*y][2*x+1]
                       + in[2*y+1][2*x] + in[2*y+1][2*x+1] + 2) / 4;
}

int main(void)
{
    int chroma[H][W] = {
        {100, 104, 120, 124},
        {102, 106, 122, 126},
        { 80,  84, 140, 144},
        { 82,  86, 142, 146},
    };
    int c422[H][W/2];
    int c420[H/2][W/2];
    int y, x;

    to_422(chroma, c422);
    to_420(chroma, c420);

    printf("4:4:4 chroma -> %d samples\n", W * H);
    printf("4:2:2 chroma -> %d samples\n", (W/2) * H);
    for (y = 0; y < H; y++) {
        for (x = 0; x < W/2; x++) printf("%4d", c422[y][x]);
        printf("\n");
    }
    printf("4:2:0 chroma -> %d samples\n", (W/2) * (H/2));
    for (y = 0; y < H/2; y++) {
        for (x = 0; x < W/2; x++) printf("%4d", c420[y][x]);
        printf("\n");
    }
    return 0;
}
