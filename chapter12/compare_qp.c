/* chapter12/compare_qp.c
 * Exercise 8: encode the same block at several QP values and tabulate
 * surviving coefficients (a proxy for size) against quantization error.
 */
#include <stdio.h>
#include <math.h>

#define N 4

int main(void){
    /* A transformed block: large DC, a few small AC terms. */
    double X[N*N]={416,-6,-5,1,2,0,-1,0,0,0,0,0,0,0,0,0};
    int Qs[]={4,8,16,32};
    printf("  QP-step | nonzero | quant-error(SSE)\n");
    for(int k=0;k<4;k++){
        int Q=Qs[k], nz=0; double sse=0;
        for(int i=0;i<N*N;i++){
            int q=(int)round(X[i]/Q);
            double back=(double)q*Q;
            if(q)nz++;
            double e=X[i]-back; sse+=e*e;
        }
        printf("  %6d | %7d | %12.2f\n", Q, nz, sse);
    }
    return 0;
}
