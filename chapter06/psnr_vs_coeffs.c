/*
 * psnr_vs_coeffs.c  -  Chapter 6, Exercise 5
 *
 * Sweep K (number of DCT coefficients kept) and report the
 * reconstruction quality as PSNR. Demonstrates that quality
 * saturates after only a few coefficients for a smooth signal,
 * the practical face of energy compaction.
 *
 * Build: gcc -O2 -o psnr_vs_coeffs psnr_vs_coeffs.c -lm
 * Run:   ./psnr_vs_coeffs
 */

#include <stdio.h>
#include <math.h>

#define N 8
#define PI 3.14159265358979323846
#define PEAK 255.0

static double alpha(int k){ return (k==0)?sqrt(1.0/N):sqrt(2.0/N); }

static void fdct(const double *x, double *X){
    for (int k=0;k<N;++k){ double s=0; for(int n=0;n<N;++n) s+=x[n]*cos(PI*(2*n+1)*k/(2.0*N)); X[k]=alpha(k)*s; }
}
static void idct(const double *X, double *x){
    for (int n=0;n<N;++n){ double s=0; for(int k=0;k<N;++k) s+=alpha(k)*X[k]*cos(PI*(2*n+1)*k/(2.0*N)); x[n]=s; }
}

/* keep the first K coefficients (low-frequency truncation) */
static double psnr_for_K(const double *x, const double *X, int K){
    double Xk[N], r[N];
    for(int i=0;i<N;++i) Xk[i]=(i<K)?X[i]:0.0;
    idct(Xk,r);
    double mse=0; for(int i=0;i<N;++i) mse+=(r[i]-x[i])*(r[i]-x[i]);
    mse/=N;
    if (mse<=0) return INFINITY;
    return 10.0*log10(PEAK*PEAK/mse);
}

int main(void){
    double x[N]={120,124,128,132,136,140,144,148};
    double X[N];
    fdct(x,X);
    printf(" K   PSNR (dB)\n");
    for (int K=1;K<=N;++K){
        double p=psnr_for_K(x,X,K);
        if (isinf(p)) printf("%2d   perfect\n", K);
        else          printf("%2d   %7.2f\n", K, p);
    }
    printf("\nPSNR climbs fast and then saturates: a few coeffs suffice.\n");
    return 0;
}
