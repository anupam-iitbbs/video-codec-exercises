/*
 * jpeg_quant.c  --  Chapter 7: Quantization
 *
 * Quantize an 8x8 block of DCT coefficients with the standard JPEG
 * luminance quantization table:
 *   Q[u][v]  = round( C[u][v] / TABLE[u][v] )   (encode)
 *   Chat     = Q * TABLE                         (decode)
 *
 * The table quantizes low frequencies (top-left) finely and high
 * frequencies (bottom-right) coarsely, matching human vision.
 *
 * Build: gcc -O2 -o jpeg_quant jpeg_quant.c -lm
 */

#include <stdio.h>
#include <math.h>

static const int JPEG_LUMA[8][8] = {
    {16, 11, 10, 16,  24,  40,  51,  61},
    {12, 12, 14, 19,  26,  58,  60,  55},
    {14, 13, 16, 24,  40,  57,  69,  56},
    {14, 17, 22, 29,  51,  87,  80,  62},
    {18, 22, 37, 56,  68, 109, 103,  77},
    {24, 35, 55, 64,  81, 104, 113,  92},
    {49, 64, 78, 87, 103, 121, 120, 101},
    {72, 92, 95, 98, 112, 100, 103,  99}
};

int main(void) {
    /* Example DCT coefficient block (already transformed). */
    double C[8][8] = {{0}};
    C[0][0] = 240; C[0][1] = -30; C[0][2] = 12;
    C[1][0] = -24; C[1][1] = 8;   C[2][0] = 6; C[0][3] = 5;

    int    Q[8][8];
    int    zeros = 0;
    double se = 0.0;

    for (int u = 0; u < 8; u++)
        for (int v = 0; v < 8; v++) {
            Q[u][v]      = (int)lround(C[u][v] / JPEG_LUMA[u][v]);
            double chat  = Q[u][v] * (double)JPEG_LUMA[u][v];
            double e     = C[u][v] - chat;
            se += e * e;
            if (Q[u][v] == 0) zeros++;
        }

    printf("Quantized indices (top-left corner):\n");
    for (int u = 0; u < 4; u++) {
        for (int v = 0; v < 4; v++) printf("%5d", Q[u][v]);
        printf("\n");
    }
    printf("\nZeros: %d of 64    Block MSE: %.4f\n", zeros, se / 64.0);
    return 0;
}
