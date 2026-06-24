/*
 * encoder.c -- drives the forward path of the minimal transform codec.
 *
 * Companion code for Chapter 12, "Building a Transform Codec."
 *
 * This file contains no new ideas. It simply wires together the stages built
 * in the other files, in the order the chapter describes:
 *
 *     predict -> transform -> quantize -> zig-zag -> run-length
 *
 * The structure of the code is the structure of the theory: each call below
 * corresponds to one box in the encoder block diagram. The decoder (decoder.c)
 * runs exactly these steps in reverse.
 */

#include "predict.h"
#include "dct.h"
#include "quant.h"
#include "zigzag.h"
#include "rle.h"
#include "encoder.h"

/*
 * Encode one 4x4 block of pixels at the given quantization parameter qp.
 * Produces a run-length pair list in 'pairs'; returns the number of pairs.
 */
int encode_block(const int *pixels, int qp, RLEPair *pairs)
{
    int residual[16];
    int coeff[16];
    int quant[16];
    int seq[16];

    /* 1. Prediction: remove spatial correlation.        */
    predict_forward(pixels, residual);

    /* 2. Transform: compact the residual's energy.      */
    dct_forward(residual, coeff);

    /* 3. Quantization: discard imperceptible precision. */
    quant_forward(coeff, qp, quant);

    /* 4. Zig-zag: gather the zeros into one long run.   */
    zigzag_scan(quant, seq);

    /* 5. Run-length: describe that run compactly.       */
    return rle_encode(seq, 16, pairs);
}
