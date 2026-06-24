/* psnr.c -- Chapter 11: peak signal-to-noise ratio from MSE.
 *
 * PSNR = 10 * log10( PEAK^2 / MSE )   in decibels, with PEAK = 255.
 *
 * Higher PSNR = lower error. Rough guide: ~30 dB noticeable loss,
 * ~40 dB visually clean, >50 dB essentially invisible.
 *
 * Build:  cc -O2 -o psnr psnr.c
 */
#include <stdio.h>
#include <math.h>

#define PEAK 255.0

static double psnr_from_mse(double mse) {
    if (mse <= 0.0) return INFINITY;   /* identical images */
    return 10.0 * log10((PEAK * PEAK) / mse);
}

int main(void) {
    double mse_list[] = {5.25, 25.0, 100.0, 400.0};
    int n = sizeof(mse_list) / sizeof(mse_list[0]);

    printf("   MSE      PSNR (dB)\n");
    for (int i = 0; i < n; ++i)
        printf("%7.2f   %8.2f\n", mse_list[i], psnr_from_mse(mse_list[i]));
    return 0;
}
