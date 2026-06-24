/*
 * rgb2ycbcr.c -- Chapter 9, Exercise 1
 *
 * Convert RGB pixels to the YCbCr color space (BT.601, 8-bit, with
 * the standard 128 offset on the chroma channels). Separating
 * luminance from chrominance is the first step that lets a codec
 * treat brightness and color differently.
 */

#include <stdio.h>

typedef struct { unsigned char r, g, b; } RGB;
typedef struct { unsigned char y, cb, cr; } YCbCr;

static unsigned char clamp8(double v)
{
    if (v < 0.0)   return 0;
    if (v > 255.0) return 255;
    return (unsigned char)(v + 0.5);
}

YCbCr rgb_to_ycbcr(RGB p)
{
    double Y  =  0.299 * p.r + 0.587 * p.g + 0.114 * p.b;
    double Cb = -0.169 * p.r - 0.331 * p.g + 0.500 * p.b + 128.0;
    double Cr =  0.500 * p.r - 0.419 * p.g - 0.081 * p.b + 128.0;
    YCbCr o = { clamp8(Y), clamp8(Cb), clamp8(Cr) };
    return o;
}

int main(void)
{
    RGB samples[] = {
        {200, 150, 100},   /* warm tone   */
        {  0,   0,   0},   /* black       */
        {255, 255, 255},   /* white       */
        {  0, 255,   0},   /* pure green  */
    };
    int n = (int)(sizeof(samples) / sizeof(samples[0]));
    int i;

    printf("   R   G   B  ->   Y  Cb  Cr\n");
    for (i = 0; i < n; i++) {
        RGB p = samples[i];
        YCbCr o = rgb_to_ycbcr(p);
        printf("%4d%4d%4d  ->  %3d %3d %3d\n",
               p.r, p.g, p.b, o.y, o.cb, o.cr);
    }
    return 0;
}
