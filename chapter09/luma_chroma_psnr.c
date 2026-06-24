/*
 * luma_chroma_psnr.c -- Chapter 9, Exercise 6
 *
 * Measure the PSNR of the luminance and chrominance planes
 * separately after chroma subsampling and reconstruction. The
 * chroma plane typically shows a much lower PSNR than luma, yet the
 * image still looks fine -- direct evidence that the eye tolerates
 * far more error in color than in brightness.
 */

#include <stdio.h>
#include <math.h>

#define N 8

static double psnr(const int *orig, const int *recon, int n)
{
    double mse = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        double d = (double)(orig[i] - recon[i]);
        mse += d * d;
    }
    mse /= n;
    if (mse == 0.0) return INFINITY;
    return 10.0 * log10((255.0 * 255.0) / mse);
}

int main(void)
{
    /* Luma: nearly preserved (kept at full resolution). */
    int luma_orig[N]  = {60, 62, 200, 205, 90, 92, 130, 132};
    int luma_recon[N] = {60, 62, 199, 205, 90, 91, 130, 132};

    /* Chroma: heavily degraded by 4:2:0 subsampling + upsampling. */
    int chroma_orig[N]  = {100, 104, 120, 124, 80, 84, 140, 144};
    int chroma_recon[N] = {102, 102, 122, 122, 82, 82, 142, 142};

    printf("luma   PSNR = %.2f dB\n", psnr(luma_orig,   luma_recon,   N));
    printf("chroma PSNR = %.2f dB\n", psnr(chroma_orig, chroma_recon, N));
    printf("chroma carries more error, yet the image looks unchanged.\n");
    return 0;
}
