/*
 * rle.c -- run-length encoding of a zig-zag coefficient sequence.
 *
 * Companion code for Chapter 12, "Building a Transform Codec."
 *
 * After quantization most coefficients are zero, and after the zig-zag scan
 * those zeros cluster into a long trailing run. Run-length coding describes
 * the sequence as (value, run_of_zeros_before_it) pairs and stops at the last
 * nonzero, replacing the tail with a single end-of-block marker. This is the
 * idea behind the entropy stage; see entropy.c for the symbol coder itself.
 */

#include "rle.h"

/*
 * Encode seq[n] into pairs[]. Each emitted pair is (run, value): 'run' counts
 * the zeros preceding a nonzero 'value'. A trailing (0, 0) pair marks
 * end-of-block. Returns the number of pairs written (including the marker).
 */
int rle_encode(const int *seq, int n, RLEPair *pairs)
{
    int count = 0;   /* pairs written            */
    int run   = 0;   /* zeros seen since last nz */

    for (int i = 0; i < n; i++) {
        if (seq[i] == 0) {
            run++;
        } else {
            pairs[count].run   = run;
            pairs[count].value = seq[i];
            count++;
            run = 0;
        }
    }

    /* end-of-block: everything from here on is zero */
    pairs[count].run   = 0;
    pairs[count].value = 0;
    count++;
    return count;
}

/*
 * Decode 'count' pairs back into seq[n], zero-filling the trailing block.
 * The (0, 0) end-of-block marker stops expansion early.
 */
void rle_decode(const RLEPair *pairs, int count, int *seq, int n)
{
    int pos = 0;

    for (int p = 0; p < count; p++) {
        if (pairs[p].run == 0 && pairs[p].value == 0)
            break;  /* end-of-block */

        for (int z = 0; z < pairs[p].run && pos < n; z++)
            seq[pos++] = 0;
        if (pos < n)
            seq[pos++] = pairs[p].value;
    }

    while (pos < n)
        seq[pos++] = 0;
}
