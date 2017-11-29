#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double newton_divided_difference(
        double *f,
        double *x,
        double x_star,
        int n)
{ 
    int i;
    int m;
    int j;
    double *div_diff;
    double *p;

    int index(int x, int y){ return x+y*n; }

    div_diff = (double*)calloc(n*n, sizeof(double));
    p = (double*)malloc(n*sizeof(double));

    for (i=0; i<n; i++){
        div_diff[index(i,i)] = f[i];
        //        printf("%d: %2.2f\n", index(i,i), f[i]);
    }
    for(m=1; m<n; m++){
        for (j=0; j<n-m; j++){
            div_diff[index(j+m, j)] = (div_diff[index(j+m, j+1)]-div_diff[index(j+m-1, j)])/(x[j+m]-x[j]);
        }
    }
    /*for (i =0; i< n*n; i++){
      printf(" %2.2f ", div_diff[i]);
      if (( i+1) % n == 0){ printf("\n");}
      }*/

    p[0] = f[0];
    for (i=0; i<n; i++){
        double temp_prod=1;
        for (j=0; j<i; j++){
            temp_prod *= (x_star-x[j]);
        }
        p[i] = p[i-1]+temp_prod*div_diff[index(i, 0)];
    }
    return p[n-1];
    free(div_diff);
    free(p);
}

int default_main(){
    double f[4];
    double x[4];

    f[0] = -1;
    f[1] = 1;
    f[2] = 3;
    f[3] = 11;
    x[0] = -1.0;
    x[1] = 0.0;
    x[2] = 1.0;
    x[3] = 2.0;
    printf("%2.4f\n", newton_divided_difference(f, x, 2.5, 4));

}

int main(int argc, char **argv){
    if (argc != 2){
        default_main();
        return 0;
    }
    int i;
    int num_elem;
    double x_star;
    FILE *input = fopen(argv[1], "r");
    if (input == NULL){
        printf("ERROR. Could not open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d\n", &num_elem);
    printf("%d elems\n", num_elem);
    double x[num_elem];
    double f[num_elem];
    fscanf(input, "%lf\n", &x_star);
    printf("x* = %2.4f\n", x_star);
    for (i = 0; i<num_elem; i++){
        if(fscanf(input,"%lf %lf\n", &x[i], &f[i])==EOF){
            printf("ERROR not enough elements on f and x: i = %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    for(i=0; i<num_elem; i++)
        printf("x[%d] = %2.3lf, f[%d] = %2.3lf\n",i, x[i],i, f[i]);
    printf("%2.5f\n", newton_divided_difference(f, x, x_star, num_elem));
}
