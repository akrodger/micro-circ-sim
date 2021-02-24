#ifndef MCS_VECTOR_MATH_H
#define MCS_VECTOR_MATH_H

/*
 * An extremely simple macro-based linear algebra library by Bram Rodgers.
 * Original Draft Dated: 23, Feb 2021
 */

/*
 * Header File Body:
 */

/*
 * Macros and Includes go here.
 */

/*
 * z, x, and y are two arrays with n entries.
 * a is a scalar. i is an iteration index.
 * Compute z[i] = x[i]+a*y[i]
 * for each i.
 */
#define mcs_vector_add(x,y,a,z,i,n) \
    do{\
        for((i)=0;(i)<(n);(i)++){\
            (z)[(i)] = ((x)[(i)]) + (a)*((y)[(i)]);\
        }\
    }while(0)

/*
 * x and y are two arrays with n entries.
 * i is an iteration index.
 * Compute prod = sum_{i=0}^{n-1} x[i]*y[i]
 */
#define mcs_vector_dot(x,y,prod,i,n) \
    do{\
        (prod)=0;\
        for((i)=0;(i)<(n);(i)++){\
            (prod) += ((x)[(i)]) * ((y)[(i)]);\
        }\
    }while(0)

/*
 * x and y are two arrays with n entries.
 * i is an iteration index.
 * Copy y[i] = x[i]
 * for each i.
 */
#define mcs_vector_copy(x,y,i,n) \
    do{\
        for((i)=0;(i)<(n);(i)++){\
            (y)[(i)] = ((x)[(i)]);\
        }\
    }while(0)


/*
 * z, x, y, and v are two arrays with n entries.
 * a is a scalar. i is an iteration index.
 * Compute z[i] = x[i]+a*y[i]+b*v[i]
 * for each i.
 */
#define mcs_vector_combo2(x,y,a,v,b,z,i,n) \
    do{\
        for((i)=0;(i)<(n);(i)++){\
            (z)[(i)] = ((x)[(i)]) + (a)*((y)[(i)]) + (b)*((v)[(i)]);\
        }\
    }while(0)


#endif
