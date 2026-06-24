/*
 * zigzag.c -- zig-zag scan for a 4x4 transform block.
 *
 * Companion code for Chapter 12, "Building a Transform Codec."
 *
 * After the DCT and quantization, most of the nonzero coefficients sit in
 * the top-left corner of the block (low frequencies). Reading the block in
 * a zig-zag order groups those nonzeros together and pushes the long run of
 * trailing zeros to the end, which is exactly what the run-length coder in
 * rle.c wants to see.
 */

#include "zigzag.h"

/* The standard 4x4 zig-zag order, listed as flat (row*4 + col) indices. */
static const int ZZ[16] = {
     0,  1,  4,  8,
     5,  2,  3,  6,
     9, 12, 13, 10,
     7, 11, 14, 15
};

/* Forward scan: block[16] in row-major order -> seq[16] in zig-zag order. */
void zigzag_scan(const int *block, int *seq)
{
    for (int i = 0; i < 16; i++)
        seq[i] = block[ZZ[i]];
}

/* Inverse scan: undo zigzag_scan, restoring row-major order. */
void zigzag_unscan(const int *seq, int *block)
{
    for (int i = 0; i < 16; i++)
        block[ZZ[i]] = seq[i];
}
