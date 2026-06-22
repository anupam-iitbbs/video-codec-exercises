/*
 * aliasing.c  --- Chapter 3, Exercise 3: Create aliasing
 *
 * Companion code for "From Signals to Video Codecs", Volume 1.
 *
 * Take a sine wave x(t) = sin(2*pi*f*t) and sample it too slowly.
 * Below the Nyquist rate (fs > 2f) the samples of a FAST sine become
 * indistinguishable from those of a SLOWER sine: the alias frequency
 *
 *     f_alias = | f - fs * round(f / fs) |
 *
 * The program samples a fast tone at a deliberately low rate, prints
 * the samples, and reports the alias frequency a reconstruction would
 * mistakenly recover. Aliasing is not noise --- it is false
 * information created by insufficient sampling (Section 3.6).
 *
 * Build:  gcc -O2 -Wall -o aliasing aliasing.c -lm
 * Run:    ./aliasing
 */

#include <stdio.h>
#include <math.h>

#define N 20

int main(void)
{
    double f  = 9.0;    /* true signal frequency, Hz            */
    double fs = 10.0;   /* sampling rate, Hz  (fs < 2f: too low!)*/

    printf("True frequency f  = %.1f Hz\n", f);
    printf("Sampling rate  fs = %.1f Hz  (Nyquist needs fs > %.1f)\n",
           fs, 2.0 * f);

    printf("\n  n        t        x = sin(2*pi*f*t)\n");
    for (int n = 0; n < N; n++) {
        double t = n / fs;
        double x = sin(2.0 * M_PI * f * t);
        printf("%3d   %6.3f   % .3f\n", n, t, x);
    }

    /* Alias frequency that a naive reconstruction would 'see'. */
    double f_alias = fabs(f - fs * round(f / fs));
    printf("\nThese samples look exactly like a %.1f Hz tone.\n", f_alias);
    printf("The %.1f Hz signal has been disguised as %.1f Hz: aliasing.\n",
           f, f_alias);
    printf("\nRaise fs above %.1f Hz and the alias disappears.\n", 2.0 * f);
    return 0;
}
