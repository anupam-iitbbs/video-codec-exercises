/*
 * sine_gen.c --- Chapter 4, Exercise 1: Generate sinusoids at different frequencies
 *
 * Companion code for "From Signals to Video Codecs", Volume 1
 *
 * Objective: Observe how frequency affects the appearance of a signal.
 * Generate sine waves at different frequencies and print their values.
 *
 * Compile: gcc -O2 -Wall -o sine_gen sine_gen.c -lm
 * Run:     ./sine_gen
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359
#define SAMPLE_RATE 8000.0  // 8 kHz
#define DURATION 1.0        // 1 second

void generateSine(double frequency, const char *label) {
    int numSamples = (int)(DURATION * SAMPLE_RATE);
    double *signal = malloc(numSamples * sizeof(double));
    
    printf("\n=== Frequency: %.1f Hz ===\n", frequency);
    printf("First 20 samples:\n");
    
    for (int i = 0; i < numSamples; i++) {
        double t = i / SAMPLE_RATE;
        signal[i] = sin(2.0 * PI * frequency * t);
        
        if (i < 20) {
            printf("%.6f ", signal[i]);
            if ((i + 1) % 5 == 0) printf("\n");
        }
    }
    
    // Count zero crossings as a proxy for frequency
    int zeroCrossings = 0;
    for (int i = 0; i < numSamples - 1; i++) {
        if ((signal[i] < 0 && signal[i+1] >= 0) || (signal[i] >= 0 && signal[i+1] < 0)) {
            zeroCrossings++;
        }
    }
    
    printf("\nZero crossings in 1 second: %d (implies ~%.1f Hz)\n", 
           zeroCrossings / 2, zeroCrossings / 2.0);
    
    free(signal);
}

int main() {
    printf("Chapter 4, Exercise 1: Sine Wave Generation at Different Frequencies\n");
    printf("========================================================================\n");
    printf("Sample Rate: %.0f Hz\n", SAMPLE_RATE);
    printf("Duration: %.1f seconds\n\n", DURATION);
    
    // Generate sines at different frequencies
    generateSine(1.0,   "Very low frequency");
    generateSine(10.0,  "Low frequency");
    generateSine(100.0, "Medium frequency");
    generateSine(1000.0, "High frequency");
    
    printf("\n\nObservation:\n");
    printf("As frequency increases, the sine wave oscillates more rapidly.\n");
    printf("At 1 Hz, the signal completes 1 full cycle in 1 second.\n");
    printf("At 1000 Hz, the signal completes 1000 cycles in 1 second.\n");
    
    return 0;
}
