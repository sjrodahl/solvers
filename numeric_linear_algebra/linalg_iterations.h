#ifndef LINALG_ITERATIONS_H
#define LINALG_ITERATIONS_H


#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float f_arr_max(float *array, int size);

void f_vec_diff(float *arr1, float *arr2, float*diff, int size);

int gauss_seidel(
        float *A,       /* INPUT:  m*m matrix */
        float *b,       /* INPUT: Vector with m elements */
        float *x_start, /* INPUT: Initial guess. Vector with m elements */
        float *x_result,/* OUTPUT: Result of the iteration */
        int m,          /* INPUT: A is an m*m matrix. x and b is of size m */
        float epsilon,  /* INPUT: error tolerance > 0 */
        int N           /* INPUT: Maximum number of iterations */
        );


int jacobi(
        float *A,       /* INPUT */
        float *b,       /* INPUT */ 
        float *x_start, /* INPUT */
        float *x_result,/* OUTPUT */ 
        int m,          /* INPUT */
        float epsilon,  /* INPUT */
        int N           /* INPUT */
        );

#endif
