#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 4

#include "linalg_iterations.h"

int main(){
    int i;    
    float *x0;
    float *res;
    float *b;
    int N;
    float epsilon;
    float A[M*M] = {1, -0.25, -0.25, 0,
        -0.25, 1, 0, -0.25,
        -0.25, 0, 1, -0.25,
        0, -0.25, -0.25, 1};
    x0 = malloc(M*sizeof(float));
    res =  malloc(M*sizeof(float));
    b = malloc(M*sizeof(float));
    for (i=0; i<M; i++){
        x0[i] = 100.0;
        b[i] = 50.0;
    }
    b[2] = 25.0;
    b[3] = 25.0;
    memcpy(res, x0, M*sizeof(float));
    N = 6000;
    epsilon = 0.0001;
    //gauss_seidel(A, b, x0, res, M, epsilon, N);
    jacobi(A, b, x0, res, M, epsilon, N);
    for (i=0; i<M; i++){
        printf("x_%d = %2.4f\n", i, res[i]);
    }
    free(x0);
    free(res);
    free(b);
}
