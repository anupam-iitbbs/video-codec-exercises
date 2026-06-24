/* bitrate_quality.c -- Chapter 11: bitrate versus quality (PSNR).
 *
 * Prints a small table and ASCII plot of PSNR against bitrate,
 * illustrating diminishing returns: each doubling of bitrate buys
 * fewer decibels than the last.
 *
 * Build:  cc -O2 -o bitrate_quality bitrate_quality.c
 */
#include <stdio.h>

int main(void) {
    double mbps[] = {1, 2, 4, 8};
    double psnr[] = {35, 40, 42, 43};
    int n = sizeof(mbps) / sizeof(mbps[0]);

    printf("Mbps   PSNR(dB)   gain over previous\n");
    for (int i = 0; i < n; ++i) {
        printf("%4.0f   %6.1f", mbps[i], psnr[i]);
        if (i > 0) printf("     +%.1f dB", psnr[i] - psnr[i - 1]);
        printf("\n");
    }
    printf("(each doubling of bitrate buys fewer dB -> diminishing returns)\n");
    return 0;
}
