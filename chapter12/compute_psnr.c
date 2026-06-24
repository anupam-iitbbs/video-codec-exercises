/* chapter12/compute_psnr.c
 * Exercise 6: compute MSE and PSNR between an original and a reconstruction.
 */
#include <stdio.h>
#include <math.h>

int main(void){
    int orig[16]={101,102,103,103,102,103,104,104,102,103,104,105,103,104,105,105};
    int recon[16]={101,102,103,104,102,103,104,104,102,103,104,104,103,104,105,105};
    double mse=0;
    for(int i=0;i<16;i++){double e=orig[i]-recon[i]; mse+=e*e;}
    mse/=16.0;
    double psnr = (mse==0)? 99.0 : 10.0*log10((255.0*255.0)/mse);
    printf("MSE  = %.4f\n", mse);
    printf("PSNR = %.2f dB\n", psnr);
    return 0;
}
