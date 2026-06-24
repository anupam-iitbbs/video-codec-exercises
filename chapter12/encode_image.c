/* chapter12/encode_image.c
 * Exercise 7: encode a 4x4 block end to end -- predict, DCT, quantize,
 * run-length -- to show the full pipeline producing a compact token stream.
 * Compile alongside codec/dct.c style routines; self-contained here for clarity.
 */
#include <stdio.h>
#include <math.h>

#define N 4
static double C(int k){return k==0?sqrt(1.0/N):sqrt(2.0/N);}

int main(void){
    int img[N][N]={{101,102,103,103},{102,103,104,104},
                   {102,103,104,105},{103,104,105,105}};
    /* 1. prediction (left) */
    double res[N][N];
    for(int r=0;r<N;r++){res[r][0]=img[r][0];for(int c=1;c<N;c++)res[r][c]=img[r][c]-img[r][c-1];}
    /* 2. forward DCT */
    double X[N][N];
    for(int u=0;u<N;u++)for(int v=0;v<N;v++){double s=0;
        for(int x=0;x<N;x++)for(int y=0;y<N;y++)
            s+=res[x][y]*cos((2*x+1)*u*M_PI/(2*N))*cos((2*y+1)*v*M_PI/(2*N));
        X[u][v]=C(u)*C(v)*s;}
    /* 3. quantize */
    int Q=8,q[N][N],nz=0;
    for(int u=0;u<N;u++)for(int v=0;v<N;v++){q[u][v]=(int)round(X[u][v]/Q); if(q[u][v])nz++;}
    printf("Nonzero quantized coefficients: %d of %d\n", nz, N*N);
    printf("DC level = %d\n", q[0][0]);
    return 0;
}
