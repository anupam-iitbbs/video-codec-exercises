/* chapter12/rd_curve.c
 * Exercise 9: sweep QP and print (rate, PSNR) pairs to plot the
 * rate-distortion curve of the minimal codec. Rate is approximated by the
 * number of surviving coefficients; distortion by quantization SSE -> PSNR.
 */
#include <stdio.h>
#include <math.h>

#define N 4

int main(void){
    double X[N*N]={416,-6,-5,1,2,0,-1,0,0,0,0,0,0,0,0,0};
    printf("# rate(nonzero)  PSNR(dB)\n");
    for(int Q=2; Q<=64; Q*=2){
        int nz=0; double sse=0;
        for(int i=0;i<N*N;i++){
            int q=(int)round(X[i]/Q);
            double back=(double)q*Q;
            if(q)nz++;
            double e=X[i]-back; sse+=e*e;
        }
        double mse = sse/(N*N);
        double psnr = (mse==0)? 99.0 : 10.0*log10((255.0*255.0)/mse);
        printf("  %3d           %7.2f\n", nz, psnr);
    }
    return 0;
}
