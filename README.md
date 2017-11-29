# Solvers
Implementation of some numerical solvers

## Newton's Method for Solving Equations _f(x) = 0_

Assuming f has a continous derivative, we can solve the equation _f(x) = 0_ using Newton's method.
The idea is that we approximate the graph by following the tangent in a point until we cross the x-axis.
We continue iterating from this value until a converging to a solution with a satisfactory error rate.

## Interpolation

### Newton's Divided Differences

Newton's Divided Differences Interpolation is an interpolation demanding less arithmatic operations than the Lagrange interpolation.
The idea is as follows: For each point (x_0, f_0), ..., (x_n, f_n), we find a p_i of degree _i_, such that p_n(x) = p_{n-1}(x) + g_n(x), where g_n(x) is a polynomial of degree n. 

First calculate p_0(x):
    
    p_0(x_0) = f_0 => p_0(x) = f_0

    p_1(x) = p_0(x) + f\[x0,x1\](x-x0)
    
    p_n(x) = p_n-1(x) + f\[x0,x1, xn\](x-x0)...(x-xn-1)

f\[xi, xj\] is called the divided difference between i and j. It is defined as:

    f\[x_p, x_{p+1}, ..., x_{p+v}\] = f\[x_{p+1}, ..., x_{p+v}\]/x_{p+v}-x_p

and

    f\[x_j] = f_j

In this implementation of Newton's divided differences interpolation, f\[...] is implemented as a matrix where f\[x_j,...,x_m] is stored in position (m, j), and calculated incrementally. The f\[]-terms that are being used in p, are in the first row of the matrix.

