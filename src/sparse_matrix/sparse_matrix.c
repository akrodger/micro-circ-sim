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

void mcs_apply_linmap(double* x, double* y);

/*
 * Static Local Variables:
 */

mcs_spmat* lin_map;

/*
 * Function Implementations:
 */

void mcs_spmatvec(char tran, mcs_spmat* A, double* x, double* y){
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

void mcs_apply_lin_map(double* x, double* y){
    mcs_spmatvec('n',lin_map,x,y);
}

void mcs_bicgstab(void (*L)(double*,double*),
                        double* b,
                        double* x,
                        double* work,
                        long N,
                        double tol){
    /********From Xianyi Zeng's lecture notes at UT El Paso*********/
    double a, w, be, rho_old, rho_new, norm2;
    double *r_j, *r_0, *p_j, *v_j, *s_j, *t_j;
    //long N = A->r_len;
    long i=0;
    r_j = work;
    p_j = &(work[N]);
    v_j = &(work[2*N]);
    s_j = &(work[3*N]);
    t_j = &(work[4*N]);
    r_0 = &(work[5*N]);
    L(x,r_0);
    mcs_vector_add(b,r_0,-1.0,r_0,i,N);
    mcs_vector_copy(r_0,r_j,i,N);
    mcs_vector_copy(r_0,p_j,i,N);
    mcs_vector_dot(r_j,r_0,rho_old,i,N);
    do{
        L(p_j,v_j);
        mcs_vector_dot(v_j,r_0,a,i,N);
        a = rho_old / a;
        mcs_vector_add(r_j,v_j,-a,s_j,i,N);
        L(s_j,t_j);
        mcs_vector_dot(t_j,t_j,norm2,i,N);
        mcs_vector_dot(t_j,s_j,w,i,N);
        w = w/norm2;
        mcs_vector_combo2(x,p_j,a,s_j,w,x,i,N);
        mcs_vector_add(s_j,t_j,-w,r_j,i,N);
        mcs_vector_dot(r_j,r_j,norm2,i,N);
        if(sqrt(norm2) < N*tol){break;}
        mcs_vector_dot(r_j,r_0,rho_new,i,N);
        be = (a/w)*(rho_new/rho_old);
        rho_old = rho_new;
        w = -w*be;
        mcs_vector_combo2(r_j,p_j,be,v_j,w,p_j,i,N);
    }while(1);
    /****************END LECTURE NOTES REFERENCE********************/
}

void mcs_spmat_bicgstab(mcs_spmat* A,
                        double* b,
                        double* x,
                        double* work,
                        double tol){
    extern mcs_spmat* lin_map;
    lin_map = A;
    mcs_bicgstab(&mcs_apply_lin_map,b,x,work,A->r_len,tol);
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
