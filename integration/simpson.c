#include <stdio.h>
#include <math.h>

/*
 * Calculate the integral from a to b of f(x) from given values in f
 * using equidistance x0 = a, x1 = a+h, ...x_{2m} = x0 + 2mh = b
 * h = (b-a)/2m
 * NOTICE: f has 2m+1 elements to ensure an even number.
 */
double simpson(double *f, double a, double b, int m){
    int i;
    int isOdd = 1;
    double sum0;    // Ending samples f_0, f_2m (we add these once)
    double sum1;    // Odd samples. f_1, f_3,..., f_{2m-1} (Add these 4 times) 
    double sum2;    // Even samples. f_2,...f_{2m-2} (add these twice)
    double h;
    h = (b-a)/(2*m);
    sum0 = f[0]+f[2*m];
    sum1 = 0;
    sum2 = 0;

    for(i = 1; i<2*m; i++){
        if (isOdd){
            sum1 += f[i];
        }
        else{
            sum2 += f[i];
        }
        isOdd = !isOdd;
    }
    return (h/3)*(sum0+4*sum1 + 2*sum2);
}

int main(){
    int i;
    double a=0.0;
    double b=1.0;
    int m= 5;
    double f[2*m+1];
    for (i=0; i<2*m+1; i++){
        f[i] = exp(-((0.1*i)*(0.1*i)));
    }
    double J;
    J = simpson(f, a, b, m);
    printf("%2.6f\n", J);
}
