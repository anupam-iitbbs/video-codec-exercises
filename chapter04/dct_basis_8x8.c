/*
 * dct_basis_8x8.c --- Chapter 4, Exercise 4: Construct 2D cosine basis for 8x8 blocks
 *
 * Companion code for "From Signals to Video Codecs", Volume 1
 *
 * Objective: Generate and understand the 64 cosine basis functions used in the
 * Discrete Cosine Transform. Visualize what low-frequency and high-frequency
 * basis functions look like.
 *
 * Compile: gcc -O2 -Wall -o dct_basis_8x8 dct_basis_8x8.c -lm
 * Run:     ./dct_basis_8x8
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BLOCKSIZE 8
#define PI 3.14159265359

/*
 * Compute a single 2D DCT basis function.
 * basis[u][v][i][j] = cos(pi * (2*i + 1) * u / (2*blockSize)) *
 *                      cos(pi * (2*j + 1) * v / (2*blockSize))
 */
double dctBasis(int u, int v, int i, int j) {
    double cu = cos(PI * (2.0 * i + 1.0) * u / (2.0 * BLOCKSIZE));
    double cv = cos(PI * (2.0 * j + 1.0) * v / (2.0 * BLOCKSIZE));
    return cu * cv;
}

void printBasis(int u, int v) {
    printf("\nBasis function [u=%d, v=%d]:\n", u, v);
    printf("Spatial frequencies: u (horizontal)=%d, v (vertical)=%d\n", u, v);
    printf("8x8 grid (rounded to 3 decimals):\n");
    
    for (int i = 0; i < BLOCKSIZE; i++) {
        for (int j = 0; j < BLOCKSIZE; j++) {
            printf("%7.3f ", dctBasis(u, v, i, j));
        }
        printf("\n");
    }
}

int main() {
    printf("Chapter 4, Exercise 4: DCT Basis Functions for 8x8 Blocks\n");
    printf("=========================================================\n\n");
    
    printf("The DCT decomposes an 8x8 block of pixels into 64 coefficients,\n");
    printf("one for each basis function. Each basis is a 2D cosine pattern:\n\n");
    
    printf("basis[u][v][i][j] = cos(pi*(2i+1)*u/16) * cos(pi*(2j+1)*v/16)\n\n");
    
    printf("- u,v in [0,7] index the 64 basis functions\n");
    printf("- i,j in [0,7] are spatial coordinates in the block\n");
    printf("- u=0, v=0 is the DC (zero-frequency) component: all values ~0.5\n");
    printf("- Higher u,v have more oscillations (higher spatial frequencies)\n\n");
    
    // Show the DC component (u=0, v=0)
    printBasis(0, 0);
    
    // Show a horizontal-only basis (u=7, v=0)
    printBasis(7, 0);
    
    // Show a vertical-only basis (u=0, v=7)
    printBasis(0, 7);
    
    // Show the highest-frequency basis (u=7, v=7)
    printBasis(7, 7);
    
    printf("\n\nKey Observations:\n");
    printf("- basis[0][0] is nearly constant (~0.5 everywhere): the average brightness\n");
    printf("- basis[7][0] oscillates horizontally: detects vertical edges\n");
    printf("- basis[0][7] oscillates vertically: detects horizontal edges\n");
    printf("- basis[7][7] oscillates both ways: detects diagonal texture\n");
    printf("\nWhen you apply the DCT to an image block, the coefficient values\n");
    printf("tell you how much of each basis function is present in the block.\n");
    printf("Natural images concentrate energy in low-frequency bases;\n");
    printf("high-frequency coefficients are usually small or zero.\n");
    
    return 0;
}
