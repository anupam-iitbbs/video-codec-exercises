/*
 * sine_gen.c --- Chapter 5, Exercise 1: Generate sinusoids at different frequencies
 *
 * Companion code for "From Signals to Video Codecs", Volume 1, Chapter 5: The Discrete Fourier Transform
 *
 * Objective: Understand sinusoid parameters by generating and observing sine waves
 * with different amplitudes, frequencies, and phases.
 *
 * Compile: gcc -O2 -Wall -o sine_gen sine_gen.c -lm
 * Run:     ./sine_gen
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359
#define SAMPLE_RATE 8000.0  // 8 kHz sampling
#define DURATION 1.0        // 1 second

/*
 * Generate a sinusoid: amplitude * sin(2*pi*frequency*t + phase)
 */
void generateSine(double amplitude, double frequency, double phase, const char *label) {
    int numSamples = (int)(DURATION * SAMPLE_RATE);
    
    printf("\n=== %s ===\n", label);
    printf("Amplitude: %.2f, Frequency: %.1f Hz, Phase: %.4f rad\n", amplitude, frequency, phase);
    printf("First 20 samples:\n");
    
    for (int i = 0; i < numSamples; i++) {
        double t = i / SAMPLE_RATE;
        double sample = amplitude * sin(2.0 * PI * frequency * t + phase);
        
        if (i < 20) {
            printf("%.6f ", sample);
            if ((i + 1) % 5 == 0) printf("\n");
        }
    }
    printf("\n");
}

int main() {
    printf("Chapter 5, Exercise 1: Sinusoid Generation at Different Parameters\n");
    printf("==================================================================\n\n");
    
    printf("A sinusoid is defined as: A * sin(2*pi*f*t + phi)\n");
    printf("where A = amplitude, f = frequency (Hz), phi = phase (radians)\n");
    printf("Sample rate: %.0f Hz, Duration: %.1f second\n\n", SAMPLE_RATE, DURATION);
    
    // Test 1: Vary amplitude with fixed frequency and phase
    generateSine(1.0, 10.0, 0.0, "Test 1: Amplitude 1.0 (base)");
    generateSine(0.5, 10.0, 0.0, "Test 2: Amplitude 0.5 (half strength)");
    generateSine(2.0, 10.0, 0.0, "Test 3: Amplitude 2.0 (double strength)");
    
    // Test 2: Vary frequency with fixed amplitude and phase
    generateSine(1.0,  1.0, 0.0, "Test 4: Frequency 1 Hz (very slow)");
    generateSine(1.0, 10.0, 0.0, "Test 5: Frequency 10 Hz (slow)");
    generateSine(1.0, 100.0, 0.0, "Test 6: Frequency 100 Hz (fast)");
    
    // Test 3: Vary phase with fixed amplitude and frequency
    generateSine(1.0, 10.0, 0.0,         "Test 7: Phase 0 rad (baseline)");
    generateSine(1.0, 10.0, PI/4.0,      "Test 8: Phase π/4 (shifted right)");
    generateSine(1.0, 10.0, PI/2.0,      "Test 9: Phase π/2 (cosine)");
    generateSine(1.0, 10.0, PI,          "Test 10: Phase π (inverted)");
    
    printf("\nKey Observations:\n");
    printf("- Amplitude controls STRENGTH (peak height)\n");
    printf("- Frequency controls SPEED (how fast it oscillates)\n");
    printf("- Phase controls SHIFT (where in the cycle it starts)\n");
    printf("These three parameters completely define a sinusoid.\n");
    
    return 0;
}
