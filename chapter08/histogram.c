/*
 * histogram.c -- Chapter 8, Exercise 1
 *
 * Build a symbol histogram (empirical probability distribution)
 * from a sequence of quantized symbols.
 *
 * The output of quantization is a stream of small integers dominated
 * by zeros. Before we can entropy-code it, we need to know how often
 * each symbol occurs. This program counts symbol frequencies and
 * reports the empirical probability of each value.
 */

#include <stdio.h>

#define MIN_SYM (-8)
#define MAX_SYM ( 8)
#define NSYM    (MAX_SYM - MIN_SYM + 1)

int main(void)
{
    /* A short example stream of quantized coefficients. */
    int stream[] = {0,0,0,1,0,0,-1,0,0,0,2,0,0,0,0,1,0,0,-1,0};
    int n = (int)(sizeof(stream) / sizeof(stream[0]));

    long count[NSYM] = {0};
    int i;

    for (i = 0; i < n; i++) {
        int s = stream[i];
        if (s < MIN_SYM || s > MAX_SYM) {
            fprintf(stderr, "symbol %d out of range\n", s);
            continue;
        }
        count[s - MIN_SYM]++;
    }

    printf("symbol  count  probability\n");
    for (i = 0; i < NSYM; i++) {
        if (count[i] == 0)
            continue;
        int sym = i + MIN_SYM;
        double p = (double)count[i] / (double)n;
        printf("%6d  %5ld  %.3f\n", sym, count[i], p);
    }

    printf("total symbols: %d\n", n);
    return 0;
}
