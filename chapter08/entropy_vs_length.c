/*
 * entropy_vs_length.c -- Chapter 8, Exercise 6
 *
 * Build a Huffman code, compute its average codeword length L, and
 * compare it against the entropy H of the source. Because Huffman
 * must spend a whole number of bits per symbol, L is always at least
 * H; the gap is the rounding waste that arithmetic coding recovers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    double freq;
    int    sym;
    struct Node *left, *right;
} Node;

static Node *mk(double f, int s, Node *l, Node *r)
{
    Node *n = malloc(sizeof(Node));
    n->freq = f; n->sym = s; n->left = l; n->right = r;
    return n;
}

static int pop_min(Node **pool, int count)
{
    int i, best = 0;
    for (i = 1; i < count; i++)
        if (pool[i]->freq < pool[best]->freq) best = i;
    return best;
}

static void rm(Node **pool, int *count, int idx)
{
    int i;
    for (i = idx; i < *count - 1; i++) pool[i] = pool[i + 1];
    (*count)--;
}

static void emit(Node *n, int depth, int *len, int sym_index_max)
{
    if (!n) return;
    if (n->sym >= 0) { len[n->sym] = depth ? depth : 1; return; }
    emit(n->left,  depth + 1, len, sym_index_max);
    emit(n->right, depth + 1, len, sym_index_max);
}

int main(void)
{
    /* Probabilities of the skewed quantized source. */
    double p[] = {0.70, 0.15, 0.10, 0.05};
    int    n = (int)(sizeof(p) / sizeof(p[0]));

    /* Entropy. */
    double H = 0.0;
    int i;
    for (i = 0; i < n; i++)
        if (p[i] > 0.0) H -= p[i] * log2(p[i]);

    /* Build Huffman tree over the symbol indices 0..n-1. */
    Node *pool[64];
    int count = 0;
    for (i = 0; i < n; i++) pool[count++] = mk(p[i], i, NULL, NULL);
    while (count > 1) {
        int a = pop_min(pool, count); Node *na = pool[a]; rm(pool, &count, a);
        int b = pop_min(pool, count); Node *nb = pool[b]; rm(pool, &count, b);
        pool[count++] = mk(na->freq + nb->freq, -1, na, nb);
    }

    int len[64] = {0};
    emit(pool[0], 0, len, n);

    double L = 0.0;
    for (i = 0; i < n; i++) L += p[i] * len[i];

    printf("entropy        H = %.4f bits/symbol\n", H);
    printf("Huffman length L = %.4f bits/symbol\n", L);
    printf("overhead   L - H = %.4f bits/symbol\n", L - H);
    return 0;
}
