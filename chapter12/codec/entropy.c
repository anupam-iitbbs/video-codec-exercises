/* chapter12/codec/entropy.c
 * Zig-zag scan and run-length encoding of a quantized 4x4 block.
 * Chapter 12 minimal codec. Lossless repackaging of quantizer output.
 */
#include <stdio.h>

#define N 4

/* Row/col order of a 4x4 zig-zag scan, DC first. */
static const int zz[N*N][2] = {
    {0,0},{0,1},{1,0},{2,0},{1,1},{0,2},{0,3},{1,2},
    {2,1},{3,0},{3,1},{2,2},{1,3},{2,3},{3,2},{3,3}
};

void zigzag(const int blk[N][N], int seq[N*N]) {
    for (int i = 0; i < N*N; i++)
        seq[i] = blk[zz[i][0]][zz[i][1]];
}

/* Print a simple (value)(value)(run=k) run-length description. */
void run_length(const int seq[N*N]) {
    int i = 0;
    while (i < N*N) {
        if (seq[i] != 0) {
            printf("(%d)", seq[i]);
            i++;
        } else {
            int run = 0;
            while (i < N*N && seq[i] == 0) { run++; i++; }
            printf("(run=%d)", run);
        }
    }
    printf("\n");
}

int main(void) {
    int q[N][N] = {
        {52,-1, 0, 0},
        {-1, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0}
    };
    int seq[N*N];
    zigzag(q, seq);
    printf("Run-length tokens: ");
    run_length(seq);
    return 0;
}
