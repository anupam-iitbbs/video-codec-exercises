/*
 * rle.c -- Chapter 8, Exercise 4
 *
 * Run-length encode a sequence into (run, value) pairs and decode it
 * back, verifying that the round trip is lossless. Run-length coding
 * is a perfect match for quantized blocks, which contain long runs
 * of zeros.
 */

#include <stdio.h>

#define MAXLEN 256

/* Encode src[0..n) into pairs[]; returns number of pairs. */
static int rle_encode(const int *src, int n, int *pairs)
{
    int i = 0, p = 0;
    while (i < n) {
        int v = src[i];
        int run = 1;
        while (i + run < n && src[i + run] == v)
            run++;
        pairs[p++] = run;
        pairs[p++] = v;
        i += run;
    }
    return p / 2;
}

/* Decode npairs (run, value) pairs back into dst[]; returns length. */
static int rle_decode(const int *pairs, int npairs, int *dst)
{
    int i, j, k = 0;
    for (i = 0; i < npairs; i++) {
        int run = pairs[2 * i];
        int v   = pairs[2 * i + 1];
        for (j = 0; j < run; j++)
            dst[k++] = v;
    }
    return k;
}

int main(void)
{
    int src[] = {0,0,0,0,0,0,0, 6, -2, 0,0,0,0, 1, 0,0};
    int n = (int)(sizeof(src) / sizeof(src[0]));

    int pairs[MAXLEN];
    int npairs = rle_encode(src, n, pairs);

    printf("encoded into %d (run,value) pairs:\n", npairs);
    int i;
    for (i = 0; i < npairs; i++)
        printf("  (%d, %d)\n", pairs[2*i], pairs[2*i+1]);

    int dst[MAXLEN];
    int m = rle_decode(pairs, npairs, dst);

    int ok = (m == n);
    for (i = 0; ok && i < n; i++)
        if (dst[i] != src[i]) ok = 0;

    printf("round trip %s (%d symbols -> %d pairs -> %d symbols)\n",
           ok ? "lossless" : "FAILED", n, npairs, m);
    return ok ? 0 : 1;
}
