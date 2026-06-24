/* rd_cost.c -- Chapter 11: the heart of every encoder, J = D + lambda*R.
 *
 * Given several candidate coding choices, each with a distortion and a
 * bit cost, the encoder picks the one with the smallest Lagrangian
 * cost J = D + lambda*R. Changing lambda (the price of a bit) can
 * change the winner.
 *
 * Build:  cc -O2 -o rd_cost rd_cost.c
 */
#include <stdio.h>

typedef struct { const char *name; double D; double R; } Candidate;

static int best_choice(const Candidate *c, int n, double lambda) {
    int best = 0;
    double best_j = c[0].D + lambda * c[0].R;
    for (int i = 1; i < n; ++i) {
        double j = c[i].D + lambda * c[i].R;
        if (j < best_j) { best_j = j; best = i; }
    }
    return best;
}

int main(void) {
    Candidate cand[] = {
        { "Mode A", 20.0, 100.0 },
        { "Mode B", 28.0,  70.0 }
    };
    int n = sizeof(cand) / sizeof(cand[0]);

    double lambdas[] = {0.2, 0.4};
    for (int k = 0; k < 2; ++k) {
        double lam = lambdas[k];
        printf("lambda = %.2f\n", lam);
        for (int i = 0; i < n; ++i)
            printf("  %-7s J = %.1f + %.2f*%.0f = %.1f\n",
                   cand[i].name, cand[i].D, lam, cand[i].R,
                   cand[i].D + lam * cand[i].R);
        printf("  -> winner: %s\n\n", cand[best_choice(cand, n, lam)].name);
    }
    return 0;
}
