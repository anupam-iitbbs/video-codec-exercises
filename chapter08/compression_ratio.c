/*
 * compression_ratio.c -- Chapter 8, Exercise 5
 *
 * Measure the original and compressed sizes of a quantized block and
 * report the compression ratio CR = original_bits / compressed_bits.
 *
 * Original size assumes a naive fixed-length code (8 bits per symbol).
 * Compressed size uses a simple model: run-length over zeros plus a
 * variable-length cost for nonzero values, terminated by EOB.
 */

#include <stdio.h>

/* Bits to store a signed value with a crude magnitude code. */
static int value_bits(int v)
{
    int mag = v < 0 ? -v : v;
    int bits = 1;            /* sign bit */
    do { bits++; mag >>= 1; } while (mag > 0);
    return bits;
}

int main(void)
{
    /* Zig-zag-ordered quantized block: nonzeros first, then zeros. */
    int block[] = {37, 2, 1, 0, 0, 0, 0, 0};
    int n = (int)(sizeof(block) / sizeof(block[0]));

    int fixed_bits = n * 8;

    int comp_bits = 0;
    int i, last_nonzero = -1;
    for (i = 0; i < n; i++)
        if (block[i] != 0) last_nonzero = i;

    for (i = 0; i <= last_nonzero; i++) {
        if (block[i] == 0)
            comp_bits += 3;          /* run-length token for a zero */
        else
            comp_bits += value_bits(block[i]);
    }
    comp_bits += 2;                  /* end-of-block marker */

    double cr = (double)fixed_bits / (double)comp_bits;
    printf("original (fixed-length): %d bits\n", fixed_bits);
    printf("compressed (modelled):   %d bits\n", comp_bits);
    printf("compression ratio:       %.2f : 1\n", cr);
    return 0;
}
