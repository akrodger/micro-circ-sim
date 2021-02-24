/*
 * Implementation for:
 * Lightweight Sparse Matrix in COO format by Bram Rodgers.
 * Features include matrix multiplication and matrix inversion.
 * Original Draft Dated: 23, Feb 2021
 */

/*
 * Macros and Includes go here: (Some common ones included)
 */
#include "sparse_matrix.h"
#include "vector_math.h"
/*
 * Locally used helper functions:
 */

/*
 * Static Local Variables:
 */

/*
 * Function Implementations:
 */

void mcs_spmatvec(char tran, mcs_spmat* A, double* x, double*y){
    long* r_arr;
    long* c_arr;
    long i, nr;//, nc;
    if(tran == 't' || tran == 'T'){
        r_arr = A->c;
        c_arr = A->r;
        nr = A->c_len;
        //nc = A->r_len;
    }else{
        r_arr = A->r;
        c_arr = A->c;
        nr = A->r_len;
        //nc = A->c_len;
    }
    for(i=0;i<nr;i++){
        y[i] = 0.0;
    }
    for(i=0;i<A->nnz;i++){
        y[r_arr[i]] += A->dat[i]*x[c_arr[i]];
    }
}
#include"stdio.h"
void mcs_spmat_bicgstab(mcs_spmat* A,
                        double* b,
                        double* x,
                        double* work,
                        double tol){
    double a, w, be, res_dot_old, res_dot_new, norm2;
    double *r_j, *r_0, *p_j, *Ap_j, *s_j, *As_j;
    long N = A->r_len, i=0;
    
/*    printf("\n");*/
/*    for(int j=0;j<N;j++){*/
/*        printf("%+2.3lf\n",b[j]);*/
/*        getchar();*/
/*    }*/
    r_0  = b;
    r_j  = work;
    p_j  = &(work[N]);
    Ap_j = &(work[2*N]);
    s_j  = &(work[3*N]);
    As_j = &(work[4*N]);
    for(i=0;i<N;i++){x[i] = 0.0;}
    mcs_vector_copy(r_0,r_j,i,N);
    mcs_vector_copy(r_0,p_j,i,N);
    mcs_vector_dot(r_j,r_0,res_dot_old,i,N);
    do{
        mcs_spmatvec('n',A,p_j,Ap_j);
        mcs_vector_dot(Ap_j,r_0,a,i,N);
        a = res_dot_old / a;
        mcs_vector_add(r_j,Ap_j,-a,s_j,i,N);
        mcs_spmatvec('n',A,s_j,As_j);
        mcs_vector_dot(As_j,As_j,norm2,i,N);
        mcs_vector_dot(As_j,s_j,w,i,N);
        w = w/norm2;
        mcs_vector_combo2(x,p_j,a,s_j,w,x,i,N);
        mcs_vector_add(s_j,As_j,-w,r_j,i,N);
        mcs_vector_dot(r_j,r_j,norm2,i,N);
        if(sqrt(norm2) < N*tol){break;}
        mcs_vector_dot(r_j,r_0,res_dot_new,i,N);
        be = (a/w)*(res_dot_new/res_dot_old);
        res_dot_old = res_dot_new;
        w = -w*be;
        mcs_vector_combo2(r_j,p_j,be,Ap_j,w,p_j,i,N);
    }while(1);
}


void mcs_alloc_spmat(mcs_spmat** A,
                     long nnz,
                     long numRow,
                     long numCol){
    *A = (mcs_spmat*) malloc(sizeof(mcs_spmat));
    (*A)->dat = (double*) malloc(sizeof(double)*nnz);
    (*A)->r = (long*) malloc(sizeof(long)*nnz);
    (*A)->c = (long*) malloc(sizeof(long)*nnz);
    (*A)->nnz = nnz;
    (*A)->r_len = numRow;
    (*A)->c_len = numCol;
}


void mcs_free_spmat(mcs_spmat** A){
    free((*A)->c);
    free((*A)->r);
    free((*A)->dat);
    free(*A);
}
