/*
 * ycbcr2rgb.c -- Chapter 9, Exercise 2
 *
 * Convert YCbCr pixels back to RGB (the inverse of rgb2ycbcr.c) and
 * verify that a round trip recovers the original values to within
 * rounding. The transform is reversible, so YCbCr by itself loses
 * nothing; the loss in a codec comes later, from subsampling and
 * quantization.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct { unsigned char r, g, b; } RGB;
typedef struct { unsigned char y, cb, cr; } YCbCr;

static unsigned char clamp8(double v)
{
    if (v < 0.0)   return 0;
    if (v > 255.0) return 255;
    return (unsigned char)(v + 0.5);
}

static YCbCr rgb_to_ycbcr(RGB p)
{
    double Y  =  0.299 * p.r + 0.587 * p.g + 0.114 * p.b;
    double Cb = -0.169 * p.r - 0.331 * p.g + 0.500 * p.b + 128.0;
    double Cr =  0.500 * p.r - 0.419 * p.g - 0.081 * p.b + 128.0;
    YCbCr o = { clamp8(Y), clamp8(Cb), clamp8(Cr) };
    return o;
}

RGB ycbcr_to_rgb(YCbCr p)
{
    double Y  = (double)p.y;
    double Cb = (double)p.cb - 128.0;
    double Cr = (double)p.cr - 128.0;
    double R = Y + 1.402   * Cr;
    double G = Y - 0.344   * Cb - 0.714 * Cr;
    double B = Y + 1.772   * Cb;
    RGB o = { clamp8(R), clamp8(G), clamp8(B) };
    return o;
}

int main(void)
{
    RGB samples[] = {
        {200, 150, 100}, {10, 20, 30}, {255, 255, 255}, {0, 128, 64},
    };
    int n = (int)(sizeof(samples) / sizeof(samples[0]));
    int i, max_err = 0;

    printf("original ->  recovered   (per-channel error)\n");
    for (i = 0; i < n; i++) {
        RGB p = samples[i];
        RGB q = ycbcr_to_rgb(rgb_to_ycbcr(p));
        int er = abs(p.r - q.r), eg = abs(p.g - q.g), eb = abs(p.b - q.b);
        if (er > max_err) max_err = er;
        if (eg > max_err) max_err = eg;
        if (eb > max_err) max_err = eb;
        printf("%3d %3d %3d  ->  %3d %3d %3d   (%d %d %d)\n",
               p.r, p.g, p.b, q.r, q.g, q.b, er, eg, eb);
    }
    printf("maximum round-trip error: %d (rounding only)\n", max_err);
    return 0;
}
