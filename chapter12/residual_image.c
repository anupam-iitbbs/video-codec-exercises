/* chapter12/residual_image.c
 * Exercise 2: compute the residual of a full grayscale image and compare
 * its variance to the original. Demonstrates how prediction collapses variance.
 */
#include <stdio.h>

static double variance(const int *a, int n){
    double m=0; for(int i=0;i<n;i++) m+=a[i]; m/=n;
    double v=0; for(int i=0;i<n;i++){double d=a[i]-m; v+=d*d;} return v/n;
}

int main(void){
    /* A small smooth row stands in for image data. */
    int img[8]={101,102,103,103,104,104,105,106};
    int res[8];
    res[0]=img[0];
    for(int i=1;i<8;i++) res[i]=img[i]-img[i-1];
    printf("Original variance:  %.3f\n", variance(img,8));
    printf("Residual variance:  %.3f\n", variance(res+1,7));
    return 0;
}
