/*
 * difference_image.c -- visualize the difference between two frames.
 *
 * Companion code for Volume 2, Chapter 1, "Prediction: The Missing Piece."
 *
 * Temporal prediction in its simplest form uses the previous frame as the
 * prediction for the current one. The residual is then just the pixel-by-pixel
 * difference between the two frames. Displayed with mid-gray (128) standing for
 * zero, the result is nearly empty except where the scene actually changed --
 * the clearest single picture of temporal redundancy.
 */

#include "difference_image.h"

/* Clamp an integer to the displayable range [0, 255]. */
static unsigned char clamp8(int v)
{
    if (v < 0)   return 0;
    if (v > 255) return 255;
    return (unsigned char)v;
}

/*
 * Build a viewable difference image: out[i] = 128 + (cur[i] - prev[i]).
 * Pixels that did not change map to mid-gray; motion appears as light/dark.
 */
void difference_image(const unsigned char *cur,
                      const unsigned char *prev,
                      unsigned char *out, int n)
{
    for (int i = 0; i < n; i++) {
        int diff = (int)cur[i] - (int)prev[i];
        out[i] = clamp8(128 + diff);
    }
}
