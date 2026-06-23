/*
 * huffman.c -- Chapter 8, Exercise 3
 *
 * Build a Huffman code from symbol counts and print the codeword
 * assigned to each symbol. The algorithm repeatedly merges the two
 * least frequent nodes until a single tree remains; the two rarest
 * symbols end up deepest in the tree and so carry the longest codes.
 *
 * Worked example from the book: A:40 B:30 C:20 D:10
 *   -> A=0  B=10  C=110  D=111   (average length 1.9 bits/symbol)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSYM 256

typedef struct Node {
    long freq;
    int  sym;        /* -1 for internal nodes */
    struct Node *left, *right;
} Node;

static Node *make_node(long freq, int sym, Node *l, Node *r)
{
    Node *n = malloc(sizeof(Node));
    n->freq = freq; n->sym = sym; n->left = l; n->right = r;
    return n;
}

/* Pop the node of smallest frequency from a simple array pool. */
static int pop_min(Node **pool, int *count)
{
    int i, best = 0;
    for (i = 1; i < *count; i++)
        if (pool[i]->freq < pool[best]->freq)
            best = i;
    int idx = best;
    /* caller reads pool[idx]; we remove it by shifting */
    return idx;
}

static void remove_at(Node **pool, int *count, int idx)
{
    int i;
    for (i = idx; i < *count - 1; i++)
        pool[i] = pool[i + 1];
    (*count)--;
}

/* Walk the tree, emitting 0 for left and 1 for right. */
static void emit(Node *n, char *code, int depth, char codes[][64])
{
    if (!n) return;
    if (n->sym >= 0) {
        code[depth] = '\0';
        strcpy(codes[n->sym], depth ? code : "0");
        return;
    }
    code[depth] = '0'; emit(n->left,  code, depth + 1, codes);
    code[depth] = '1'; emit(n->right, code, depth + 1, codes);
}

int main(void)
{
    int    syms[]  = {'A', 'B', 'C', 'D'};
    long   freqs[] = { 40,  30,  20,  10 };
    int    n = (int)(sizeof(syms) / sizeof(syms[0]));

    Node  *pool[MAXSYM];
    int    count = 0;
    int    i;

    for (i = 0; i < n; i++)
        pool[count++] = make_node(freqs[i], syms[i], NULL, NULL);

    long total = 0;
    for (i = 0; i < n; i++) total += freqs[i];

    /* Repeatedly merge the two smallest. */
    while (count > 1) {
        int a = pop_min(pool, &count); Node *na = pool[a]; remove_at(pool, &count, a);
        int b = pop_min(pool, &count); Node *nb = pool[b]; remove_at(pool, &count, b);
        pool[count++] = make_node(na->freq + nb->freq, -1, na, nb);
    }

    char codes[MAXSYM][64];
    char buf[64];
    emit(pool[0], buf, 0, codes);

    double avg = 0.0;
    printf("symbol  freq  code\n");
    for (i = 0; i < n; i++) {
        int s = syms[i];
        printf("%6c  %4ld  %s\n", s, freqs[i], codes[s]);
        avg += (double)freqs[i] / total * (double)strlen(codes[s]);
    }
    printf("average length L = %.3f bits/symbol\n", avg);
    return 0;
}
