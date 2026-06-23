/*
 * keep_k_coeffs.c  -  Chapter 6, Exercise 4
 *
 * Transform a 1D signal with the DCT-II, keep only the K
 * largest-magnitude coefficients (zero the rest), invert, and
 * compare the reconstruction to the original. Shows how few
 * coefficients a smooth signal really needs.
 *
 * Build: gcc -O2 -o keep_k_coeffs keep_k_coeffs.c -lm
 * Run:   ./keep_k_coeffs
 */

#include <stdio.h>
#include <math.h>

#define N 8
#define PI 3.14159265358979323846

static double alpha(int k){ return (k==0)?sqrt(1.0/N):sqrt(2.0/N); }

static void fdct(const double *x, double *X){
    for (int k=0;k<N;++k){ double s=0; for(int n=0;n<N;++n) s+=x[n]*cos(PI*(2*n+1)*k/(2.0*N)); X[k]=alpha(k)*s; }
}
static void idct(const double *X, double *x){
    for (int n=0;n<N;++n){ double s=0; for(int k=0;k<N;++k) s+=alpha(k)*X[k]*cos(PI*(2*n+1)*k/(2.0*N)); x[n]=s; }
}

int main(void){
    double x[N]={10,12,14,16,18,20,22,24};
    double X[N], r[N];
    fdct(x,X);

    for (int K=1;K<=N;++K){
        double Xk[N];
        for(int i=0;i<N;++i) Xk[i]=X[i];
        /* zero all but the K largest-magnitude coefficients */
        for(int drop=0;drop<N-K;++drop){
            int idx=-1; double best=1e30;
            for(int i=0;i<N;++i) if(Xk[i]!=0.0 && fabs(Xk[i])<best){best=fabs(Xk[i]);idx=i;}
            if(idx>=0) Xk[idx]=0.0;
        }
        idct(Xk,r);
        double err=0; for(int i=0;i<N;++i) err+=(r[i]-x[i])*(r[i]-x[i]);
        printf("K=%d  reconstruction error (SSE) = %.4f\n", K, err);
    }
    printf("\nA smooth signal is nearly perfect with just K=2.\n");
    return 0;
}
