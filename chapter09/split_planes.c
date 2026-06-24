/*
 * split_planes.c -- Chapter 9, Exercise 5
 *
 * Split an interleaved YCbCr image into three separate planes and
 * write each as a standalone 8-bit grayscale PGM image, so the Y,
 * Cb, and Cr planes can be inspected individually. Viewing the Y
 * plane alone reveals that all the sharp detail lives in luminance.
 */

#include <stdio.h>

#define W 4
#define H 4

/* Write one plane as a binary PGM (P5) grayscale image. */
static int write_pgm(const char *name, const unsigned char *plane,
                     int w, int h)
{
    FILE *f = fopen(name, "wb");
    if (!f) { perror(name); return -1; }
    fprintf(f, "P5\n%d %d\n255\n", w, h);
    fwrite(plane, 1, (size_t)(w * h), f);
    fclose(f);
    return 0;
}

int main(void)
{
    /* Interleaved Y, Cb, Cr triples for a 4x4 image. */
    unsigned char img[H * W * 3];
    unsigned char y_plane[H * W];
    unsigned char cb_plane[H * W];
    unsigned char cr_plane[H * W];
    int i;

    /* Fill with a simple gradient for demonstration. */
    for (i = 0; i < H * W; i++) {
        img[3*i + 0] = (unsigned char)(i * 16);   /* Y  */
        img[3*i + 1] = 128;                        /* Cb */
        img[3*i + 2] = 128;                        /* Cr */
    }

    for (i = 0; i < H * W; i++) {
        y_plane[i]  = img[3*i + 0];
        cb_plane[i] = img[3*i + 1];
        cr_plane[i] = img[3*i + 2];
    }

    write_pgm("plane_y.pgm",  y_plane,  W, H);
    write_pgm("plane_cb.pgm", cb_plane, W, H);
    write_pgm("plane_cr.pgm", cr_plane, W, H);
    printf("wrote plane_y.pgm, plane_cb.pgm, plane_cr.pgm\n");
    return 0;
}
