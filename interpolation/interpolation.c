#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void newton_divided_difference(
        double *x,           /* INPUT: x-coordinates */
        double *y,           /* INPUT: y(x_i) for x_i in x */
        double *div_diff,    /* OUTPUT: list of the divided differences*/
        int n               /* INPUT number of elements in x, y, and div_dif */
        )
{
    int i, j, m; // Iterators
    double *div_diff_matrix; 

    // Helper function to transfer from matrix indexing to flat indexing
    int index(int x, int y){ return x+y*n; }
    
    div_diff_matrix = calloc(n*n,sizeof(double));

    // Copy f to the diagonal of the div-diff matrix
    for (i=0; i<n; i++){
        div_diff_matrix[index(i,i)] = y[i];
    }
    // Calculate the coefficients iteratively
    for(m=1; m<n; m++){
        for (j=0; j<n-m; j++){
            div_diff_matrix[index(j+m, j)] = (div_diff_matrix[index(j+m, j+1)]-div_diff_matrix[index(j+m-1, j)])/(x[j+m]-x[j]);
        }
    }
    // Print the coefficients:
    // Print the div_diff matrix (the coefficients a_k is the top row; k=0,1,...n-1) 
    for (i =0; i< n*n; i++){
      printf("(%d)%2.3f ",i, div_diff_matrix[i]);
      if (( i+1) % n == 0){ printf("\n");}
      }

    // Copy the first row, containing all a_k, to the output variable
    memcpy(div_diff, div_diff_matrix, n*sizeof(double));

    free(div_diff_matrix);
}

/*
 * Calculates the coefficients obtained by Newtons divided differences.
 * The coeffisients a_k, k = 0,1,...,n ,
 *
 */
double newton_divided_difference_evaluate(
        double *f,      // list of function values at coordinates in x
        double *x,      // list of x coordinates
        double x_star,  // Return value is p(x_star);
        int n           // number of elements in x and f
        )
{ 
    int i;
    int m;
    int j;
    double *div_diff;
    double *p;

    int index(int x, int y){ return x+y*n; }

    double factor(int n){
        double f = 1.0;
        if (n==0){return f;}
        for(int i = 0; i<n; i++){
            f *= x_star-x[i];
        }
        return f;
    }

    div_diff = malloc(n*sizeof(double));

    // Calculating Newtons divided differences (result stored in div_diff
    newton_divided_difference(x, f, div_diff, n);
    
    double res;
    res = 0;
    for (i = 0; i<n; i++){
        res += div_diff[i]*factor(i);
    }
    return res;
        

    free(div_diff);
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
    printf("%2.4f\n", newton_divided_difference_evaluate(f, x, 2.5, 4));

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
    double *div_diff;
    div_diff = malloc(num_elem*sizeof(double));
    newton_divided_difference(x, f, div_diff, num_elem);
    for (i=0; i<num_elem; i++){
        printf("dd_%d = %2.5f\n", i, div_diff[i]);
    }
    //printf("%2.5f\n", newton_divided_difference_evaluate(f, x, x_star, num_elem));

}
