#include "linalg_iterations.h"

float f_arr_max(float *array, int size){
    int i;
    float max;
    max = -INFINITY;
    for (i=0; i<size; i++){
        if (array[i] > max){
            max = array[i];
        }
    }
    return max;
}

void f_vec_diff(float *arr1, float *arr2, float*diff, int size){
    int i;
    for(i= 0; i< size; i++){
        diff[i] = fabs(arr1[i]-arr2[i]);
    }
}

int gauss_seidel(
        float *A,       // m*m matrix
        float *b,       // Vector with m elements
        float *x_start,      // Initial guess. Vector with m elements
        float *x_result,  //Output: Result of the iteration
        int m,         // A is an m*m matrix. x and b is of size m 
        float epsilon,  // error tolerance > 0
        int N           // Maximum number of iterations
        )          
{
    int i, j, k;    //Iterators
    float temp_val;
    float *x_old;
    float *x_diff;

    int index(int x ,int y){
        return x+y*m;
    }

    x_diff = malloc(m*sizeof(float));
    x_old = malloc(m*sizeof(float));
    memcpy(x_result, x_start, m*sizeof(float));
    memcpy(x_old, x_start, m*sizeof(float));

    for (i=0; i<N; i++){
        for (j=0; j<m; j++){
            temp_val = b[j];
            for (k=0; k<m; k++){  
                if (j!=k){
                    temp_val -= A[index(j,k)]*x_result[k];
                }
            }
            x_result[j] = temp_val * 1.0/A[index(j,j)];
        }
        f_vec_diff(x_old, x_result, x_diff, m);
        if (f_arr_max(x_diff, m) < epsilon){
            printf("Found a solution after %d iterations\n", i);
            free(x_old);
            free(x_diff);
            return 0;
        }
        memcpy(x_old, x_result, m*sizeof(float));
    }
    printf("No solution found after %d iterations\n", N);
    free(x_old);
    free(x_diff);
    return -1;   //Exit failure
}

/*
 * ---  JACOBI ITERATIONS ---
 *  Jacobi iterations solve equations on the form Ax = b, where A is an m*m matrix, and x and b are vectors of size m.
 *  Ax = b, A = D + R => x_next = D⁻¹(b - R x_prev), where D is the diagonal component of A, and R is the remainder (https://en.wikipedia.org/wiki/Jacobi_method)
 *
 *  For element j, we need to subtract from b_j the sum  SUM_(i=!=j) a_ij*x_j and multiple with 1/a_jj (from D⁻¹)
 *  x_j_next = 1/a_jj(b_j - SUM_(i=!=j) a_ij*x_j_prev)
 *
 *
 */
int jacobi(
        float *A,       /* INPUT */
        float *b,       /* INPUT */ 
        float *x_start, /* INPUT */
        float*x_result, /* OUTPUT */ 
        int m,          /* INPUT */
        float epsilon,  /* INPUT */
        int N           /* INPUT */
        )
{
    int i, j, k, l; // Iterators
    float *x;       // Data from the last iteration
    float sum;      // SUM_(k=!=j) a_ij*x_j
    int break_flag; 
    //Allocate space for the results of the iterations
    x = (float *)malloc(m*sizeof(float));
    memcpy(x, x_start, m*sizeof(float));
    
    for(i=0; i<N; i++){    
        break_flag = 1;
        //#pragma omp parallel for num_threads(m) private(sum)
        for(j=0; j<m; j++){
            sum = 0.0;
            for (k=0 ; k<m ; k++){
                if (k!=j){
                    sum += A[k+j*m]*x[j];
                }
            }
            x_result[j] = (1/A[j+j*m])*( b[j] -sum);

            if (fabs(x_result[j]-x[j]) > epsilon){
                break_flag = 0;
            }
        }
        // Break if the difference after a step is less than epsilon in each element
        if (break_flag){
            printf("Found solution after %d iterations.\n", i);
            return 0;
        }
        memcpy(x, x_result, m*sizeof(float));
    }
    printf("No solution found after %d iterations\n", N);
    return -1;
}

