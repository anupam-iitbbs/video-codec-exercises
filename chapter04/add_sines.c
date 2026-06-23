/*
 * add_sines.c --- Chapter 4, Exercise 2: Add sine waves and observe superposition
 *
 * Companion code for "From Signals to Video Codecs", Volume 1
 *
 * Objective: Verify that sinusoids add together and that the result is a more
 * complex signal. Observe superposition in action.
 *
 * Compile: gcc -O2 -Wall -o add_sines add_sines.c -lm
 * Run:     ./add_sines
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359
#define SAMPLE_RATE 8000.0
#define DURATION 0.5  // 0.5 seconds for clarity

void addSines(double f1, double f2, double f3, 
              double a1, double a2, double a3,
              const char *label) {
    int numSamples = (int)(DURATION * SAMPLE_RATE);
    
    printf("\n=== %s ===\n", label);
    printf("Frequencies: %.1f Hz (amp %.2f), %.1f Hz (amp %.2f), %.1f Hz (amp %.2f)\n",
           f1, a1, f2, a2, f3, a3);
    printf("First 25 samples of the sum:\n");
    
    for (int i = 0; i < numSamples; i++) {
        double t = i / SAMPLE_RATE;
        double sig = a1 * sin(2.0 * PI * f1 * t) +
                     a2 * sin(2.0 * PI * f2 * t) +
                     a3 * sin(2.0 * PI * f3 * t);
        
        if (i < 25) {
            printf("%.5f ", sig);
            if ((i + 1) % 5 == 0) printf("\n");
        }
    }
    
    printf("\nNotice: The combined signal oscillates at multiple time scales.\n");
    printf("This is the Fourier principle: complex shapes are sums of sinusoids.\n");
}

int main() {
    printf("Chapter 4, Exercise 2: Superposition of Sine Waves\n");
    printf("===================================================\n\n");
    
    // Example 1: Three frequencies with different amplitudes
    addSines(10.0, 50.0, 200.0, 
             0.5, 0.3, 0.2,
             "Three sinusoids: 10 Hz (dominant), 50 Hz (medium), 200 Hz (weak)");
    
    // Example 2: Two close frequencies (beating effect)
    addSines(100.0, 105.0, 0.0,
             1.0, 1.0, 0.0,
             "Two close frequencies (100 Hz and 105 Hz) - observe beating pattern");
    
    // Example 3: Harmonic series (musical example)
    addSines(440.0, 880.0, 1320.0,
             1.0, 0.5, 0.25,
             "Harmonic series: 440 Hz (A note), 880 Hz (octave), 1320 Hz (twelfth)");
    
    printf("\n\nKey Observation:\n");
    printf("The sum of sinusoids at different frequencies is a complex waveform\n");
    printf("that oscillates in multiple time scales. This is the essence of\n");
    printf("Fourier analysis: every complex signal can be decomposed into and\n");
    printf("reconstructed from sinusoids at different frequencies.\n");
    
    return 0;
}
