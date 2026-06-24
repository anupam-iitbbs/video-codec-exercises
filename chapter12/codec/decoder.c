/* chapter12/codec/decoder.c
 * Ties the inverse path together: dequantize -> inverse DCT -> undo prediction.
 * Chapter 12 minimal codec. Demonstrates the full decode of one block.
 */
#include <stdio.h>
#include <math.h>

#define N 4

static double C(int k){return k==0?sqrt(1.0/N):sqrt(2.0/N);}

static void idct2(const double in[N][N], double out[N][N]){
    for(int x=0;x<N;x++)for(int y=0;y<N;y++){
        double s=0.0;
        for(int u=0;u<N;u++)for(int v=0;v<N;v++)
            s+=C(u)*C(v)*in[u][v]
               *cos((2*x+1)*u*M_PI/(2*N))
               *cos((2*y+1)*v*M_PI/(2*N));
        out[x][y]=s;
    }
}

int main(void){
    /* Quantized levels from the encoder, with step Q. */
    int q[N][N]={{52,-1,0,0},{-1,0,0,0},{0,0,0,0},{0,0,0,0}};
    int Q=8;
    double X[N][N];
    /* 1. dequantize */
    for(int u=0;u<N;u++)for(int v=0;v<N;v++) X[u][v]=(double)q[u][v]*Q;
    /* 2. inverse transform back to the residual domain */
    double res[N][N];
    idct2(X,res);
    /* 3. undo left-prediction per row (cumulative sum) */
    int out[N][N];
    for(int r=0;r<N;r++){
        out[r][0]=(int)round(res[r][0]);
        for(int c=1;c<N;c++) out[r][c]=out[r][c-1]+(int)round(res[r][c]);
    }
    printf("Reconstructed block:\n");
    for(int r=0;r<N;r++){for(int c=0;c<N;c++)printf("%4d",out[r][c]);printf("\n");}
    return 0;
}
