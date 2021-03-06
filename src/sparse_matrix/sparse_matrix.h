#ifndef MCS_SPARSE_MATRIX_H
#define MCS_SPARSE_MATRIX_H

/*
 * Lightweight Sparse Matrix in COO format by Bram Rodgers.
 * Features include matrix multiplication and matrix inversion.
 * Original Draft Dated: 23, Feb 2021
 */

/*
 * Header File Body:
 */

/*
 * Macros and Includes go here.
 */
#include<stdlib.h>
#include"math.h"

/*
 * A struct for Coordinate array format sparse matrix:
 */

typedef struct _mcs_spmat{
    double* dat;
    long* r;
    long* c;
    long nnz;
    long r_len;
    long c_len;
} mcs_spmat;

/*
 * Function Declarations:
 */

/*
 * Do matrix-vector multiplication of the form
 * y = A * x
 * or
 * y = A^(T) * x
 * Where A is sparse. Output stored in y.
 *
 * If tran = 't' or 'T' then y = A^(T) * x is computed. Otherwise y = A * x
 * is computed.
 */
void mcs_spmatvec(char tran, mcs_spmat* A, double* x, double* y);



/*
 * For a linear map T, solve the system of equations T(x) = b for a
 * given b using the stabilized biconjugate gradient method.
 *
 * T(x) is defined with the function pointer L. Given an input v, the output
 * is the second argument of L. So if T(v)[i] = w[i],
 * this is computed by L(v,w).
 *
 * BICGSTAB halts when approximated residual is less than tol.
 *
 * Expected: (# entries of x) = (# entries of b) = N.
 * workspace vector called work expected to have 6*(# entries of x)
 * memory allocated.
 *
 * x is expected to contain an intial guess for the solution to the system.
 * Therefore, it is required to set the entries of x before calling.
 */
void mcs_bicgstab(void (*L)(double*,double*),
                        double* b,
                        double* x,
                        double* work,
                        long N,
                        double tol);

/*
 * For the sparse matrix A, solve the system of equations A*x = b for a given b
 * using the stabilized biconjugate gradient method.
 *
 * Function halts when approximated residual is less than tol.
 *
 * Expected: (# entries of x) = (# entries of b) = A->r_len = A->c_len.
 * workspace vector called work expected to have 6*(# entries of x)
 * memory allocated.
 *
 * x is expected to contain an intial guess for the solution to the system.
 * Therefore, it is required to set the entries of x before calling.
 */
void mcs_spmat_bicgstab(mcs_spmat* A,
                        double* b,
                        double* x,
                        double* work,
                        double tol);

/*
 * Allocate a sparse matrix struct without initializing the entries
 * of the row or column arrays. Calls 4 mallocs.
 */
void mcs_alloc_spmat(mcs_spmat** A,
                     long nnz,
                     long numRow,
                     long numCol);

/*
 * Free a sparse matrix struct. Calls 4 frees.
 */
void mcs_free_spmat(mcs_spmat** A);

#endif
