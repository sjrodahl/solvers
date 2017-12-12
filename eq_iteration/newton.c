#include <stdio.h>
#include <math.h>

double newton(
        double (*f)(double),
        double (*df)(double),
        double x0,
        double epsilon,
        int N)
{
    int i;
    double out;
    double deriv;
    double x;
    double x_next;
    x = x0;
    for (i=0; i<N; i++){
        deriv = df(x);
        if (deriv == 0.0){
            printf("Newton failed: f'(%2.6f) = 0\n", x);
            return 0.0;
        }
        x_next = x- f(x)/df(x);
        if (fabs(x_next-x) < epsilon*x_next){
            printf("Newton succeeded after %d iterations: f(%2.6f) = 0\n", i, x_next);
            return x_next;
        }
        x = x_next;
    }
    printf("Newton failed after %d iterations\n", N);
    return 0.0;
}

double f(double x){
    return x*x -2;
}
double df(double x){
    return 2*x;
}
int main(){
    // Solve x² = 2
    double res;
    res = newton(f, df, 1.2, 0.00001, 1000);
    printf("sqrt(2) ~= %2.4f \n", res);
}
