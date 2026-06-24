/* chapter12/codec/predict.c
 * Left/top prediction and its inverse for a grayscale block.
 * Part of the minimal transform codec from Chapter 12.
 */
#include <stdio.h>

#define N 4

/* Forward: replace each pixel (except column 0) by its left-neighbor residual. */
void predict_forward(const int in[N][N], int res[N][N]) {
    for (int r = 0; r < N; r++) {
        res[r][0] = in[r][0];                 /* first column kept verbatim */
        for (int c = 1; c < N; c++)
            res[r][c] = in[r][c] - in[r][c-1];
    }
}

/* Inverse: rebuild pixels from residuals by running cumulative sums per row. */
void predict_inverse(const int res[N][N], int out[N][N]) {
    for (int r = 0; r < N; r++) {
        out[r][0] = res[r][0];
        for (int c = 1; c < N; c++)
            out[r][c] = out[r][c-1] + res[r][c];
    }
}

int main(void) {
    int x[N][N] = {
        {101,102,103,103},
        {102,103,104,104},
        {102,103,104,105},
        {103,104,105,105}
    };
    int res[N][N], rec[N][N];

    predict_forward(x, res);
    predict_inverse(res, rec);

    printf("Residual block:\n");
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) printf("%4d", res[r][c]);
        printf("\n");
    }
    return 0;
}
