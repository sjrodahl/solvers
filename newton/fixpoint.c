#include <stdio.h>
#include <math.h>

double fix_point(double (*g)(double), double start, double epsilon, int N){
    double x;
    double x_next;
    double epsilon_next;
    int i;

    x = start;
    for (i =0; i< N; i++){
        x_next = g(x);
        if (fabs(x_next-x) < epsilon){
            printf("Solution found after %d iterations: %2.4f\n", i, x_next);
            return x_next;
        }
        x = x_next;
    }
    printf("No solution found %d iterations starting at %2.3f\n with epsilon = %1.3f", N, start, epsilon);
}

double g(double x){
    return (1/(1+x*x));
}

int main(){
    printf("%2.5f\n", fix_point(g, 0.5, 0.0001, 1000));
}
