/*************************************************************************
ALGLIB 3.18.0 (source code generated 2021-10-25)
Copyright (c) Sergey Bochkanov (ALGLIB project).

>>> SOURCE LICENSE >>>
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation (www.fsf.org); either version 2 of the 
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

A copy of the GNU General Public License is available at
http://www.fsf.org/licensing/licenses
>>> END OF LICENSE >>>
*************************************************************************/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "alglibinternal.h"

// disable some irrelevant warnings
#if (AE_COMPILER==AE_MSVC) && !defined(AE_ALL_WARNINGS)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#pragma warning(disable:4611)
#pragma warning(disable:4702)
#pragma warning(disable:4996)
#endif

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS IMPLEMENTATION OF C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS IMPLEMENTATION OF COMPUTATIONAL CORE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_TSORT) || !defined(AE_PARTIAL_BUILD)
static void tsort_tagsortfastirec(/* Real    */ ae_vector* a,
     /* Integer */ ae_vector* b,
     /* Real    */ ae_vector* bufa,
     /* Integer */ ae_vector* bufb,
     ae_int_t i1,
     ae_int_t i2,
     ae_state *_state);
static void tsort_tagsortfastrrec(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* bufa,
     /* Real    */ ae_vector* bufb,
     ae_int_t i1,
     ae_int_t i2,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_APSERV) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
The function performs zero-coalescing on real value.

NOTE: no check is performed for B<>0

  -- ALGLIB --
     Copyright 18.05.2015 by Bochkanov Sergey
*************************************************************************/
double coalesce(double a, double b, ae_state *_state)
{
    double result;


    result = a;
    if( ae_fp_eq(a,0.0) )
    {
        result = b;
    }
    return result;
}
/*************************************************************************
This function checks that all values from X[] are distinct. It does more
than just usual floating point comparison:
* first, it calculates max(X) and min(X)
* second, it maps X[] from [min,max] to [1,2]
* only at this stage actual comparison is done

The meaning of such check is to ensure that all values are "distinct enough"
and will not cause interpolation subroutine to fail.

NOTE:
    X[] must be sorted by ascending (subroutine ASSERT's it)

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
ae_bool aredistinct(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state)
{
    double a;
    double b;
    ae_int_t i;
    ae_bool nonsorted;
    ae_bool result;


    ae_assert(n>=1, "APSERVAreDistinct: internal error (N<1)", _state);
    if( n==1 )
    {
        
        /*
         * everything is alright, it is up to caller to decide whether it
         * can interpolate something with just one point
         */
        result = ae_true;
        return result;
    }
    a = x->ptr.p_double[0];
    b = x->ptr.p_double[0];
    nonsorted = ae_false;
    for(i=1; i<=n-1; i++)
    {
        a = ae_minreal(a, x->ptr.p_double[i], _state);
        b = ae_maxreal(b, x->ptr.p_double[i], _state);
        nonsorted = nonsorted||ae_fp_greater_eq(x->ptr.p_double[i-1],x->ptr.p_double[i]);
    }
    ae_assert(!nonsorted, "APSERVAreDistinct: internal error (not sorted)", _state);
    for(i=1; i<=n-1; i++)
    {
        if( ae_fp_eq((x->ptr.p_double[i]-a)/(b-a)+1,(x->ptr.p_double[i-1]-a)/(b-a)+1) )
        {
            result = ae_false;
            return result;
        }
    }
    result = ae_true;
    return result;
}
/*************************************************************************
Resizes X and fills by zeros

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
void setlengthzero(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state)
{
    ae_int_t i;


    ae_assert(n>=0, "SetLengthZero: N<0", _state);
    ae_vector_set_length(x, n, _state);
    for(i=0; i<=n-1; i++)
    {
        x->ptr.p_double[i] = (double)(0);
    }
}
/*************************************************************************
If Length(X)<N, resizes X

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
void ivectorsetlengthatleast(/* Integer */ ae_vector* x,
     ae_int_t n,
     ae_state *_state)
{


    if( x->cnt<n )
    {
        ae_vector_set_length(x, n, _state);
    }
}


/*************************************************************************
If Length(X)<N, resizes X

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
void rvectorsetlengthatleast(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state)
{


    if( x->cnt<n )
    {
        ae_vector_set_length(x, n, _state);
    }
}
/*************************************************************************
This function checks that length(X) is at least N and first N values  from
X[] are finite

  -- ALGLIB --
     Copyright 18.06.2010 by Bochkanov Sergey
*************************************************************************/
ae_bool isfinitevector(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state)
{
    ae_int_t i;
    double v;
    ae_bool result;


    ae_assert(n>=0, "APSERVIsFiniteVector: internal error (N<0)", _state);
    if( n==0 )
    {
        result = ae_true;
        return result;
    }
    if( x->cnt<n )
    {
        result = ae_false;
        return result;
    }
    v = (double)(0);
    for(i=0; i<=n-1; i++)
    {
        v = 0.01*v+x->ptr.p_double[i];
    }
    result = ae_isfinite(v, _state);
    return result;
}
/*************************************************************************
Safe sqrt(x^2+y^2)

  -- ALGLIB --
     Copyright by Bochkanov Sergey
*************************************************************************/
double safepythag2(double x, double y, ae_state *_state)
{
    double w;
    double xabs;
    double yabs;
    double z;
    double result;


    xabs = ae_fabs(x, _state);
    yabs = ae_fabs(y, _state);
    w = ae_maxreal(xabs, yabs, _state);
    z = ae_minreal(xabs, yabs, _state);
    if( ae_fp_eq(z,(double)(0)) )
    {
        result = w;
    }
    else
    {
        result = w*ae_sqrt(1+ae_sqr(z/w, _state), _state);
    }
    return result;
}
/*************************************************************************
This function makes periodic mapping of X to [A,B].

It accepts X, A, B (A>B). It returns T which lies in  [A,B] and integer K,
such that X = T + K*(B-A).

NOTES:
* K is represented as real value, although actually it is integer
* T is guaranteed to be in [A,B]
* T replaces X

  -- ALGLIB --
     Copyright by Bochkanov Sergey
*************************************************************************/
void apperiodicmap(double* x,
     double a,
     double b,
     double* k,
     ae_state *_state)
{

    *k = 0;

    ae_assert(ae_fp_less(a,b), "APPeriodicMap: internal error!", _state);
    *k = (double)(ae_ifloor((*x-a)/(b-a), _state));
    *x = *x-*k*(b-a);
    while(ae_fp_less(*x,a))
    {
        *x = *x+(b-a);
        *k = *k-1;
    }
    while(ae_fp_greater(*x,b))
    {
        *x = *x-(b-a);
        *k = *k+1;
    }
    *x = ae_maxreal(*x, a, _state);
    *x = ae_minreal(*x, b, _state);
}
/*************************************************************************
This function is used to increment value of integer variable
*************************************************************************/
void inc(ae_int_t* v, ae_state *_state)
{


    *v = *v+1;
}
/*************************************************************************
This function returns product of three real numbers. It is convenient when
you have to perform typecast-and-product of two INTEGERS.
*************************************************************************/
double rmul3(double v0, double v1, double v2, ae_state *_state)
{
    double result;


    result = v0*v1*v2;
    return result;
}
/*************************************************************************
This function returns (A div B) rounded up; it expects that A>0, B>0, but
does not check it.
*************************************************************************/
ae_int_t idivup(ae_int_t a, ae_int_t b, ae_state *_state)
{
    ae_int_t result;


    result = a/b;
    if( a%b>0 )
    {
        result = result+1;
    }
    return result;
}
/*************************************************************************
This function returns max(i0,i1)
*************************************************************************/
ae_int_t imax2(ae_int_t i0, ae_int_t i1, ae_state *_state)
{
    ae_int_t result;


    result = i0;
    if( i1>result )
    {
        result = i1;
    }
    return result;
}
/*************************************************************************
This function returns max(i0,i1,i2)
*************************************************************************/
ae_int_t imax3(ae_int_t i0, ae_int_t i1, ae_int_t i2, ae_state *_state)
{
    ae_int_t result;


    result = i0;
    if( i1>result )
    {
        result = i1;
    }
    if( i2>result )
    {
        result = i2;
    }
    return result;
}
/*************************************************************************
'bounds' value: maps X to [B1,B2]

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
double boundval(double x, double b1, double b2, ae_state *_state)
{
    double result;


    if( ae_fp_less_eq(x,b1) )
    {
        result = b1;
        return result;
    }
    if( ae_fp_greater_eq(x,b2) )
    {
        result = b2;
        return result;
    }
    result = x;
    return result;
}
/*************************************************************************
This function is used in parallel functions for recurrent division of large
task into two smaller tasks.

It has following properties:
* it works only for TaskSize>=2 and TaskSize>TileSize (assertion is thrown otherwise)
* Task0+Task1=TaskSize, Task0>0, Task1>0
* Task0 and Task1 are close to each other
* Task0>=Task1
* Task0 is always divisible by TileSize

  -- ALGLIB --
     Copyright 07.04.2013 by Bochkanov Sergey
*************************************************************************/
void tiledsplit(ae_int_t tasksize,
     ae_int_t tilesize,
     ae_int_t* task0,
     ae_int_t* task1,
     ae_state *_state)
{
    ae_int_t cc;

    *task0 = 0;
    *task1 = 0;

    ae_assert(tasksize>=2, "TiledSplit: TaskSize<2", _state);
    ae_assert(tasksize>tilesize, "TiledSplit: TaskSize<=TileSize", _state);
    cc = chunkscount(tasksize, tilesize, _state);
    ae_assert(cc>=2, "TiledSplit: integrity check failed", _state);
    *task0 = idivup(cc, 2, _state)*tilesize;
    *task1 = tasksize-(*task0);
    ae_assert(*task0>=1, "TiledSplit: internal error", _state);
    ae_assert(*task1>=1, "TiledSplit: internal error", _state);
    ae_assert(*task0%tilesize==0, "TiledSplit: internal error", _state);
    ae_assert(*task0>=(*task1), "TiledSplit: internal error", _state);
}
/*************************************************************************
This function is used to calculate number of chunks (including partial,
non-complete chunks) in some set. It expects that ChunkSize>=1, TaskSize>=0.
Assertion is thrown otherwise.

Function result is equivalent to Ceil(TaskSize/ChunkSize), but with guarantees
that rounding errors won't ruin results.

  -- ALGLIB --
     Copyright 21.01.2015 by Bochkanov Sergey
*************************************************************************/
ae_int_t chunkscount(ae_int_t tasksize,
     ae_int_t chunksize,
     ae_state *_state)
{
    ae_int_t result;


    ae_assert(tasksize>=0, "ChunksCount: TaskSize<0", _state);
    ae_assert(chunksize>=1, "ChunksCount: ChunkSize<1", _state);
    result = tasksize/chunksize;
    if( tasksize%chunksize!=0 )
    {
        result = result+1;
    }
    return result;
}
/*************************************************************************
Returns A-tile size for a matrix.

A-tiles are smallest tiles (32x32), suitable for processing by ALGLIB  own
implementation of Level 3 linear algebra.

  -- ALGLIB routine --
     10.01.2019
     Bochkanov Sergey
*************************************************************************/
ae_int_t matrixtilesizea(ae_state *_state)
{
    ae_int_t result;


    result = 32;
    return result;
}


/*************************************************************************
Returns B-tile size for a matrix.

B-tiles are larger  tiles (64x64), suitable for parallel execution or for
processing by vendor's implementation of Level 3 linear algebra.

  -- ALGLIB routine --
     10.01.2019
     Bochkanov Sergey
*************************************************************************/
ae_int_t matrixtilesizeb(ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_MKL
    ae_int_t result;


    result = 64;
    return result;
#else
    return _ialglib_i_matrixtilesizeb();
#endif
}
/*************************************************************************
This function returns minimum cost of task which is feasible for
multithreaded processing. It returns real number in order to avoid overflow
problems.

  -- ALGLIB --
     Copyright 10.01.2018 by Bochkanov Sergey
*************************************************************************/
double smpactivationlevel(ae_state *_state)
{
    double nn;
    double result;


    nn = (double)(2*matrixtilesizeb(_state));
    result = ae_maxreal(0.95*2*nn*nn*nn, 1.0E7, _state);
    return result;
}
#endif
#if defined(AE_COMPILE_ABLASF) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
Sets vector X[] to V, reallocating X[] if too small

INPUT PARAMETERS:
    N       -   vector length
    V       -   value to set
    X       -   possibly preallocated array

OUTPUT PARAMETERS:
    X       -   leading N elements are replaced by V; array is reallocated
                if its length is less than N.

  -- ALGLIB --
     Copyright 20.01.2020 by Bochkanov Sergey
*************************************************************************/
void isetallocv(ae_int_t n,
     ae_int_t v,
     /* Integer */ ae_vector* x,
     ae_state *_state)
{


    if( x->cnt<n )
    {
        ae_vector_set_length(x, n, _state);
    }
    isetv(n, v, x, _state);
}
/*************************************************************************
Fast kernel

  -- ALGLIB routine --
     19.01.2010
     Bochkanov Sergey
*************************************************************************/
ae_bool rmatrixrighttrsmf(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_ABLAS
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_rmatrixrighttrsmf(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2);
#endif
}
/*************************************************************************
Fast kernel

  -- ALGLIB routine --
     19.01.2010
     Bochkanov Sergey
*************************************************************************/
ae_bool rmatrixlefttrsmf(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_ABLAS
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_rmatrixlefttrsmf(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2);
#endif
}
/*************************************************************************
Fast kernel

  -- ALGLIB routine --
     19.01.2010
     Bochkanov Sergey
*************************************************************************/
ae_bool rmatrixsyrkf(ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_ABLAS
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_rmatrixsyrkf(n, k, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper);
#endif
}
/*************************************************************************
RMatrixGEMM kernel, basecase code for RMatrixGEMM.

This subroutine calculates C = alpha*op1(A)*op2(B) +beta*C where:
* C is MxN general matrix
* op1(A) is MxK matrix
* op2(B) is KxN matrix
* "op" may be identity transformation, transposition

Additional info:
* multiplication result replaces C. If Beta=0, C elements are not used in
  calculations (not multiplied by zero - just not referenced)
* if Alpha=0, A is not used (not multiplied by zero - just not referenced)
* if both Beta and Alpha are zero, C is filled by zeros.

IMPORTANT:

This function does NOT preallocate output matrix C, it MUST be preallocated
by caller prior to calling this function. In case C does not have  enough
space to store result, exception will be generated.

INPUT PARAMETERS
    M       -   matrix size, M>0
    N       -   matrix size, N>0
    K       -   matrix size, K>0
    Alpha   -   coefficient
    A       -   matrix
    IA      -   submatrix offset
    JA      -   submatrix offset
    OpTypeA -   transformation type:
                * 0 - no transformation
                * 1 - transposition
    B       -   matrix
    IB      -   submatrix offset
    JB      -   submatrix offset
    OpTypeB -   transformation type:
                * 0 - no transformation
                * 1 - transposition
    Beta    -   coefficient
    C       -   PREALLOCATED output matrix
    IC      -   submatrix offset
    JC      -   submatrix offset

  -- ALGLIB routine --
     27.03.2013
     Bochkanov Sergey
*************************************************************************/
void rmatrixgemmk(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;


    
    /*
     * if matrix size is zero
     */
    if( m==0||n==0 )
    {
        return;
    }
    
    /*
     * Try optimized code
     */
    if( ablasf_rgemm32basecase(m, n, k, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state) )
    {
        return;
    }
    
    /*
     * if K=0 or Alpha=0, then C=Beta*C
     */
    if( k==0||ae_fp_eq(alpha,(double)(0)) )
    {
        if( ae_fp_neq(beta,(double)(1)) )
        {
            if( ae_fp_neq(beta,(double)(0)) )
            {
                for(i=0; i<=m-1; i++)
                {
                    for(j=0; j<=n-1; j++)
                    {
                        c->ptr.pp_double[ic+i][jc+j] = beta*c->ptr.pp_double[ic+i][jc+j];
                    }
                }
            }
            else
            {
                for(i=0; i<=m-1; i++)
                {
                    for(j=0; j<=n-1; j++)
                    {
                        c->ptr.pp_double[ic+i][jc+j] = (double)(0);
                    }
                }
            }
        }
        return;
    }
    
    /*
     * Call specialized code.
     *
     * NOTE: specialized code was moved to separate function because of strange
     *       issues with instructions cache on some systems; Having too long
     *       functions significantly slows down internal loop of the algorithm.
     */
    if( optypea==0&&optypeb==0 )
    {
        rmatrixgemmk44v00(m, n, k, alpha, a, ia, ja, b, ib, jb, beta, c, ic, jc, _state);
    }
    if( optypea==0&&optypeb!=0 )
    {
        rmatrixgemmk44v01(m, n, k, alpha, a, ia, ja, b, ib, jb, beta, c, ic, jc, _state);
    }
    if( optypea!=0&&optypeb==0 )
    {
        rmatrixgemmk44v10(m, n, k, alpha, a, ia, ja, b, ib, jb, beta, c, ic, jc, _state);
    }
    if( optypea!=0&&optypeb!=0 )
    {
        rmatrixgemmk44v11(m, n, k, alpha, a, ia, ja, b, ib, jb, beta, c, ic, jc, _state);
    }
}
/*************************************************************************
RMatrixGEMM kernel, basecase code for RMatrixGEMM, specialized for sitation
with OpTypeA=0 and OpTypeB=0.

Additional info:
* this function requires that Alpha<>0 (assertion is thrown otherwise)

INPUT PARAMETERS
    M       -   matrix size, M>0
    N       -   matrix size, N>0
    K       -   matrix size, K>0
    Alpha   -   coefficient
    A       -   matrix
    IA      -   submatrix offset
    JA      -   submatrix offset
    B       -   matrix
    IB      -   submatrix offset
    JB      -   submatrix offset
    Beta    -   coefficient
    C       -   PREALLOCATED output matrix
    IC      -   submatrix offset
    JC      -   submatrix offset

  -- ALGLIB routine --
     27.03.2013
     Bochkanov Sergey
*************************************************************************/
void rmatrixgemmk44v00(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    double v;
    double v00;
    double v01;
    double v02;
    double v03;
    double v10;
    double v11;
    double v12;
    double v13;
    double v20;
    double v21;
    double v22;
    double v23;
    double v30;
    double v31;
    double v32;
    double v33;
    double a0;
    double a1;
    double a2;
    double a3;
    double b0;
    double b1;
    double b2;
    double b3;
    ae_int_t idxa0;
    ae_int_t idxa1;
    ae_int_t idxa2;
    ae_int_t idxa3;
    ae_int_t idxb0;
    ae_int_t idxb1;
    ae_int_t idxb2;
    ae_int_t idxb3;
    ae_int_t i0;
    ae_int_t i1;
    ae_int_t ik;
    ae_int_t j0;
    ae_int_t j1;
    ae_int_t jk;
    ae_int_t t;
    ae_int_t offsa;
    ae_int_t offsb;


    ae_assert(ae_fp_neq(alpha,(double)(0)), "RMatrixGEMMK44V00: internal error (Alpha=0)", _state);
    
    /*
     * if matrix size is zero
     */
    if( m==0||n==0 )
    {
        return;
    }
    
    /*
     * A*B
     */
    i = 0;
    while(i<m)
    {
        j = 0;
        while(j<n)
        {
            
            /*
             * Choose between specialized 4x4 code and general code
             */
            if( i+4<=m&&j+4<=n )
            {
                
                /*
                 * Specialized 4x4 code for [I..I+3]x[J..J+3] submatrix of C.
                 *
                 * This submatrix is calculated as sum of K rank-1 products,
                 * with operands cached in local variables in order to speed
                 * up operations with arrays.
                 */
                idxa0 = ia+i+0;
                idxa1 = ia+i+1;
                idxa2 = ia+i+2;
                idxa3 = ia+i+3;
                offsa = ja;
                idxb0 = jb+j+0;
                idxb1 = jb+j+1;
                idxb2 = jb+j+2;
                idxb3 = jb+j+3;
                offsb = ib;
                v00 = 0.0;
                v01 = 0.0;
                v02 = 0.0;
                v03 = 0.0;
                v10 = 0.0;
                v11 = 0.0;
                v12 = 0.0;
                v13 = 0.0;
                v20 = 0.0;
                v21 = 0.0;
                v22 = 0.0;
                v23 = 0.0;
                v30 = 0.0;
                v31 = 0.0;
                v32 = 0.0;
                v33 = 0.0;
                
                /*
                 * Different variants of internal loop
                 */
                for(t=0; t<=k-1; t++)
                {
                    a0 = a->ptr.pp_double[idxa0][offsa];
                    a1 = a->ptr.pp_double[idxa1][offsa];
                    b0 = b->ptr.pp_double[offsb][idxb0];
                    b1 = b->ptr.pp_double[offsb][idxb1];
                    v00 = v00+a0*b0;
                    v01 = v01+a0*b1;
                    v10 = v10+a1*b0;
                    v11 = v11+a1*b1;
                    a2 = a->ptr.pp_double[idxa2][offsa];
                    a3 = a->ptr.pp_double[idxa3][offsa];
                    v20 = v20+a2*b0;
                    v21 = v21+a2*b1;
                    v30 = v30+a3*b0;
                    v31 = v31+a3*b1;
                    b2 = b->ptr.pp_double[offsb][idxb2];
                    b3 = b->ptr.pp_double[offsb][idxb3];
                    v22 = v22+a2*b2;
                    v23 = v23+a2*b3;
                    v32 = v32+a3*b2;
                    v33 = v33+a3*b3;
                    v02 = v02+a0*b2;
                    v03 = v03+a0*b3;
                    v12 = v12+a1*b2;
                    v13 = v13+a1*b3;
                    offsa = offsa+1;
                    offsb = offsb+1;
                }
                if( ae_fp_eq(beta,(double)(0)) )
                {
                    c->ptr.pp_double[ic+i+0][jc+j+0] = alpha*v00;
                    c->ptr.pp_double[ic+i+0][jc+j+1] = alpha*v01;
                    c->ptr.pp_double[ic+i+0][jc+j+2] = alpha*v02;
                    c->ptr.pp_double[ic+i+0][jc+j+3] = alpha*v03;
                    c->ptr.pp_double[ic+i+1][jc+j+0] = alpha*v10;
                    c->ptr.pp_double[ic+i+1][jc+j+1] = alpha*v11;
                    c->ptr.pp_double[ic+i+1][jc+j+2] = alpha*v12;
                    c->ptr.pp_double[ic+i+1][jc+j+3] = alpha*v13;
                    c->ptr.pp_double[ic+i+2][jc+j+0] = alpha*v20;
                    c->ptr.pp_double[ic+i+2][jc+j+1] = alpha*v21;
                    c->ptr.pp_double[ic+i+2][jc+j+2] = alpha*v22;
                    c->ptr.pp_double[ic+i+2][jc+j+3] = alpha*v23;
                    c->ptr.pp_double[ic+i+3][jc+j+0] = alpha*v30;
                    c->ptr.pp_double[ic+i+3][jc+j+1] = alpha*v31;
                    c->ptr.pp_double[ic+i+3][jc+j+2] = alpha*v32;
                    c->ptr.pp_double[ic+i+3][jc+j+3] = alpha*v33;
                }
                else
                {
                    c->ptr.pp_double[ic+i+0][jc+j+0] = beta*c->ptr.pp_double[ic+i+0][jc+j+0]+alpha*v00;
                    c->ptr.pp_double[ic+i+0][jc+j+1] = beta*c->ptr.pp_double[ic+i+0][jc+j+1]+alpha*v01;
                    c->ptr.pp_double[ic+i+0][jc+j+2] = beta*c->ptr.pp_double[ic+i+0][jc+j+2]+alpha*v02;
                    c->ptr.pp_double[ic+i+0][jc+j+3] = beta*c->ptr.pp_double[ic+i+0][jc+j+3]+alpha*v03;
                    c->ptr.pp_double[ic+i+1][jc+j+0] = beta*c->ptr.pp_double[ic+i+1][jc+j+0]+alpha*v10;
                    c->ptr.pp_double[ic+i+1][jc+j+1] = beta*c->ptr.pp_double[ic+i+1][jc+j+1]+alpha*v11;
                    c->ptr.pp_double[ic+i+1][jc+j+2] = beta*c->ptr.pp_double[ic+i+1][jc+j+2]+alpha*v12;
                    c->ptr.pp_double[ic+i+1][jc+j+3] = beta*c->ptr.pp_double[ic+i+1][jc+j+3]+alpha*v13;
                    c->ptr.pp_double[ic+i+2][jc+j+0] = beta*c->ptr.pp_double[ic+i+2][jc+j+0]+alpha*v20;
                    c->ptr.pp_double[ic+i+2][jc+j+1] = beta*c->ptr.pp_double[ic+i+2][jc+j+1]+alpha*v21;
                    c->ptr.pp_double[ic+i+2][jc+j+2] = beta*c->ptr.pp_double[ic+i+2][jc+j+2]+alpha*v22;
                    c->ptr.pp_double[ic+i+2][jc+j+3] = beta*c->ptr.pp_double[ic+i+2][jc+j+3]+alpha*v23;
                    c->ptr.pp_double[ic+i+3][jc+j+0] = beta*c->ptr.pp_double[ic+i+3][jc+j+0]+alpha*v30;
                    c->ptr.pp_double[ic+i+3][jc+j+1] = beta*c->ptr.pp_double[ic+i+3][jc+j+1]+alpha*v31;
                    c->ptr.pp_double[ic+i+3][jc+j+2] = beta*c->ptr.pp_double[ic+i+3][jc+j+2]+alpha*v32;
                    c->ptr.pp_double[ic+i+3][jc+j+3] = beta*c->ptr.pp_double[ic+i+3][jc+j+3]+alpha*v33;
                }
            }
            else
            {
                
                /*
                 * Determine submatrix [I0..I1]x[J0..J1] to process
                 */
                i0 = i;
                i1 = ae_minint(i+3, m-1, _state);
                j0 = j;
                j1 = ae_minint(j+3, n-1, _state);
                
                /*
                 * Process submatrix
                 */
                for(ik=i0; ik<=i1; ik++)
                {
                    for(jk=j0; jk<=j1; jk++)
                    {
                        if( k==0||ae_fp_eq(alpha,(double)(0)) )
                        {
                            v = (double)(0);
                        }
                        else
                        {
                            v = ae_v_dotproduct(&a->ptr.pp_double[ia+ik][ja], 1, &b->ptr.pp_double[ib][jb+jk], b->stride, ae_v_len(ja,ja+k-1));
                        }
                        if( ae_fp_eq(beta,(double)(0)) )
                        {
                            c->ptr.pp_double[ic+ik][jc+jk] = alpha*v;
                        }
                        else
                        {
                            c->ptr.pp_double[ic+ik][jc+jk] = beta*c->ptr.pp_double[ic+ik][jc+jk]+alpha*v;
                        }
                    }
                }
            }
            j = j+4;
        }
        i = i+4;
    }
}
/*************************************************************************
RMatrixGEMM kernel, basecase code for RMatrixGEMM, specialized for sitation
with OpTypeA=0 and OpTypeB=1.

Additional info:
* this function requires that Alpha<>0 (assertion is thrown otherwise)

INPUT PARAMETERS
    M       -   matrix size, M>0
    N       -   matrix size, N>0
    K       -   matrix size, K>0
    Alpha   -   coefficient
    A       -   matrix
    IA      -   submatrix offset
    JA      -   submatrix offset
    B       -   matrix
    IB      -   submatrix offset
    JB      -   submatrix offset
    Beta    -   coefficient
    C       -   PREALLOCATED output matrix
    IC      -   submatrix offset
    JC      -   submatrix offset

  -- ALGLIB routine --
     27.03.2013
     Bochkanov Sergey
*************************************************************************/
void rmatrixgemmk44v01(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    double v;
    double v00;
    double v01;
    double v02;
    double v03;
    double v10;
    double v11;
    double v12;
    double v13;
    double v20;
    double v21;
    double v22;
    double v23;
    double v30;
    double v31;
    double v32;
    double v33;
    double a0;
    double a1;
    double a2;
    double a3;
    double b0;
    double b1;
    double b2;
    double b3;
    ae_int_t idxa0;
    ae_int_t idxa1;
    ae_int_t idxa2;
    ae_int_t idxa3;
    ae_int_t idxb0;
    ae_int_t idxb1;
    ae_int_t idxb2;
    ae_int_t idxb3;
    ae_int_t i0;
    ae_int_t i1;
    ae_int_t ik;
    ae_int_t j0;
    ae_int_t j1;
    ae_int_t jk;
    ae_int_t t;
    ae_int_t offsa;
    ae_int_t offsb;


    ae_assert(ae_fp_neq(alpha,(double)(0)), "RMatrixGEMMK44V00: internal error (Alpha=0)", _state);
    
    /*
     * if matrix size is zero
     */
    if( m==0||n==0 )
    {
        return;
    }
    
    /*
     * A*B'
     */
    i = 0;
    while(i<m)
    {
        j = 0;
        while(j<n)
        {
            
            /*
             * Choose between specialized 4x4 code and general code
             */
            if( i+4<=m&&j+4<=n )
            {
                
                /*
                 * Specialized 4x4 code for [I..I+3]x[J..J+3] submatrix of C.
                 *
                 * This submatrix is calculated as sum of K rank-1 products,
                 * with operands cached in local variables in order to speed
                 * up operations with arrays.
                 */
                idxa0 = ia+i+0;
                idxa1 = ia+i+1;
                idxa2 = ia+i+2;
                idxa3 = ia+i+3;
                offsa = ja;
                idxb0 = ib+j+0;
                idxb1 = ib+j+1;
                idxb2 = ib+j+2;
                idxb3 = ib+j+3;
                offsb = jb;
                v00 = 0.0;
                v01 = 0.0;
                v02 = 0.0;
                v03 = 0.0;
                v10 = 0.0;
                v11 = 0.0;
                v12 = 0.0;
                v13 = 0.0;
                v20 = 0.0;
                v21 = 0.0;
                v22 = 0.0;
                v23 = 0.0;
                v30 = 0.0;
                v31 = 0.0;
                v32 = 0.0;
                v33 = 0.0;
                for(t=0; t<=k-1; t++)
                {
                    a0 = a->ptr.pp_double[idxa0][offsa];
                    a1 = a->ptr.pp_double[idxa1][offsa];
                    b0 = b->ptr.pp_double[idxb0][offsb];
                    b1 = b->ptr.pp_double[idxb1][offsb];
                    v00 = v00+a0*b0;
                    v01 = v01+a0*b1;
                    v10 = v10+a1*b0;
                    v11 = v11+a1*b1;
                    a2 = a->ptr.pp_double[idxa2][offsa];
                    a3 = a->ptr.pp_double[idxa3][offsa];
                    v20 = v20+a2*b0;
                    v21 = v21+a2*b1;
                    v30 = v30+a3*b0;
                    v31 = v31+a3*b1;
                    b2 = b->ptr.pp_double[idxb2][offsb];
                    b3 = b->ptr.pp_double[idxb3][offsb];
                    v22 = v22+a2*b2;
                    v23 = v23+a2*b3;
                    v32 = v32+a3*b2;
                    v33 = v33+a3*b3;
                    v02 = v02+a0*b2;
                    v03 = v03+a0*b3;
                    v12 = v12+a1*b2;
                    v13 = v13+a1*b3;
                    offsa = offsa+1;
                    offsb = offsb+1;
                }
                if( ae_fp_eq(beta,(double)(0)) )
                {
                    c->ptr.pp_double[ic+i+0][jc+j+0] = alpha*v00;
                    c->ptr.pp_double[ic+i+0][jc+j+1] = alpha*v01;
                    c->ptr.pp_double[ic+i+0][jc+j+2] = alpha*v02;
                    c->ptr.pp_double[ic+i+0][jc+j+3] = alpha*v03;
                    c->ptr.pp_double[ic+i+1][jc+j+0] = alpha*v10;
                    c->ptr.pp_double[ic+i+1][jc+j+1] = alpha*v11;
                    c->ptr.pp_double[ic+i+1][jc+j+2] = alpha*v12;
                    c->ptr.pp_double[ic+i+1][jc+j+3] = alpha*v13;
                    c->ptr.pp_double[ic+i+2][jc+j+0] = alpha*v20;
                    c->ptr.pp_double[ic+i+2][jc+j+1] = alpha*v21;
                    c->ptr.pp_double[ic+i+2][jc+j+2] = alpha*v22;
                    c->ptr.pp_double[ic+i+2][jc+j+3] = alpha*v23;
                    c->ptr.pp_double[ic+i+3][jc+j+0] = alpha*v30;
                    c->ptr.pp_double[ic+i+3][jc+j+1] = alpha*v31;
                    c->ptr.pp_double[ic+i+3][jc+j+2] = alpha*v32;
                    c->ptr.pp_double[ic+i+3][jc+j+3] = alpha*v33;
                }
                else
                {
                    c->ptr.pp_double[ic+i+0][jc+j+0] = beta*c->ptr.pp_double[ic+i+0][jc+j+0]+alpha*v00;
                    c->ptr.pp_double[ic+i+0][jc+j+1] = beta*c->ptr.pp_double[ic+i+0][jc+j+1]+alpha*v01;
                    c->ptr.pp_double[ic+i+0][jc+j+2] = beta*c->ptr.pp_double[ic+i+0][jc+j+2]+alpha*v02;
                    c->ptr.pp_double[ic+i+0][jc+j+3] = beta*c->ptr.pp_double[ic+i+0][jc+j+3]+alpha*v03;
                    c->ptr.pp_double[ic+i+1][jc+j+0] = beta*c->ptr.pp_double[ic+i+1][jc+j+0]+alpha*v10;
                    c->ptr.pp_double[ic+i+1][jc+j+1] = beta*c->ptr.pp_double[ic+i+1][jc+j+1]+alpha*v11;
                    c->ptr.pp_double[ic+i+1][jc+j+2] = beta*c->ptr.pp_double[ic+i+1][jc+j+2]+alpha*v12;
                    c->ptr.pp_double[ic+i+1][jc+j+3] = beta*c->ptr.pp_double[ic+i+1][jc+j+3]+alpha*v13;
                    c->ptr.pp_double[ic+i+2][jc+j+0] = beta*c->ptr.pp_double[ic+i+2][jc+j+0]+alpha*v20;
                    c->ptr.pp_double[ic+i+2][jc+j+1] = beta*c->ptr.pp_double[ic+i+2][jc+j+1]+alpha*v21;
                    c->ptr.pp_double[ic+i+2][jc+j+2] = beta*c->ptr.pp_double[ic+i+2][jc+j+2]+alpha*v22;
                    c->ptr.pp_double[ic+i+2][jc+j+3] = beta*c->ptr.pp_double[ic+i+2][jc+j+3]+alpha*v23;
                    c->ptr.pp_double[ic+i+3][jc+j+0] = beta*c->ptr.pp_double[ic+i+3][jc+j+0]+alpha*v30;
                    c->ptr.pp_double[ic+i+3][jc+j+1] = beta*c->ptr.pp_double[ic+i+3][jc+j+1]+alpha*v31;
                    c->ptr.pp_double[ic+i+3][jc+j+2] = beta*c->ptr.pp_double[ic+i+3][jc+j+2]+alpha*v32;
                    c->ptr.pp_double[ic+i+3][jc+j+3] = beta*c->ptr.pp_double[ic+i+3][jc+j+3]+alpha*v33;
                }
            }
            else
            {
                
                /*
                 * Determine submatrix [I0..I1]x[J0..J1] to process
                 */
                i0 = i;
                i1 = ae_minint(i+3, m-1, _state);
                j0 = j;
                j1 = ae_minint(j+3, n-1, _state);
                
                /*
                 * Process submatrix
                 */
                for(ik=i0; ik<=i1; ik++)
                {
                    for(jk=j0; jk<=j1; jk++)
                    {
                        if( k==0||ae_fp_eq(alpha,(double)(0)) )
                        {
                            v = (double)(0);
                        }
                        else
                        {
                            v = ae_v_dotproduct(&a->ptr.pp_double[ia+ik][ja], 1, &b->ptr.pp_double[ib+jk][jb], 1, ae_v_len(ja,ja+k-1));
                        }
                        if( ae_fp_eq(beta,(double)(0)) )
                        {
                            c->ptr.pp_double[ic+ik][jc+jk] = alpha*v;
                        }
                        else
                        {
                            c->ptr.pp_double[ic+ik][jc+jk] = beta*c->ptr.pp_double[ic+ik][jc+jk]+alpha*v;
                        }
                    }
                }
            }
            j = j+4;
        }
        i = i+4;
    }
}


/*************************************************************************
RMatrixGEMM kernel, basecase code for RMatrixGEMM, specialized for sitation
with OpTypeA=1 and OpTypeB=0.

Additional info:
* this function requires that Alpha<>0 (assertion is thrown otherwise)

INPUT PARAMETERS
    M       -   matrix size, M>0
    N       -   matrix size, N>0
    K       -   matrix size, K>0
    Alpha   -   coefficient
    A       -   matrix
    IA      -   submatrix offset
    JA      -   submatrix offset
    B       -   matrix
    IB      -   submatrix offset
    JB      -   submatrix offset
    Beta    -   coefficient
    C       -   PREALLOCATED output matrix
    IC      -   submatrix offset
    JC      -   submatrix offset

  -- ALGLIB routine --
     27.03.2013
     Bochkanov Sergey
*************************************************************************/
void rmatrixgemmk44v10(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    double v;
    double v00;
    double v01;
    double v02;
    double v03;
    double v10;
    double v11;
    double v12;
    double v13;
    double v20;
    double v21;
    double v22;
    double v23;
    double v30;
    double v31;
    double v32;
    double v33;
    double a0;
    double a1;
    double a2;
    double a3;
    double b0;
    double b1;
    double b2;
    double b3;
    ae_int_t idxa0;
    ae_int_t idxa1;
    ae_int_t idxa2;
    ae_int_t idxa3;
    ae_int_t idxb0;
    ae_int_t idxb1;
    ae_int_t idxb2;
    ae_int_t idxb3;
    ae_int_t i0;
    ae_int_t i1;
    ae_int_t ik;
    ae_int_t j0;
    ae_int_t j1;
    ae_int_t jk;
    ae_int_t t;
    ae_int_t offsa;
    ae_int_t offsb;


    ae_assert(ae_fp_neq(alpha,(double)(0)), "RMatrixGEMMK44V00: internal error (Alpha=0)", _state);
    
    /*
     * if matrix size is zero
     */
    if( m==0||n==0 )
    {
        return;
    }
    
    /*
     * A'*B
     */
    i = 0;
    while(i<m)
    {
        j = 0;
        while(j<n)
        {
            
            /*
             * Choose between specialized 4x4 code and general code
             */
            if( i+4<=m&&j+4<=n )
            {
                
                /*
                 * Specialized 4x4 code for [I..I+3]x[J..J+3] submatrix of C.
                 *
                 * This submatrix is calculated as sum of K rank-1 products,
                 * with operands cached in local variables in order to speed
                 * up operations with arrays.
                 */
                idxa0 = ja+i+0;
                idxa1 = ja+i+1;
                idxa2 = ja+i+2;
                idxa3 = ja+i+3;
                offsa = ia;
                idxb0 = jb+j+0;
                idxb1 = jb+j+1;
                idxb2 = jb+j+2;
                idxb3 = jb+j+3;
                offsb = ib;
                v00 = 0.0;
                v01 = 0.0;
                v02 = 0.0;
                v03 = 0.0;
                v10 = 0.0;
                v11 = 0.0;
                v12 = 0.0;
                v13 = 0.0;
                v20 = 0.0;
                v21 = 0.0;
                v22 = 0.0;
                v23 = 0.0;
                v30 = 0.0;
                v31 = 0.0;
                v32 = 0.0;
                v33 = 0.0;
                for(t=0; t<=k-1; t++)
                {
                    a0 = a->ptr.pp_double[offsa][idxa0];
                    a1 = a->ptr.pp_double[offsa][idxa1];
                    b0 = b->ptr.pp_double[offsb][idxb0];
                    b1 = b->ptr.pp_double[offsb][idxb1];
                    v00 = v00+a0*b0;
                    v01 = v01+a0*b1;
                    v10 = v10+a1*b0;
                    v11 = v11+a1*b1;
                    a2 = a->ptr.pp_double[offsa][idxa2];
                    a3 = a->ptr.pp_double[offsa][idxa3];
                    v20 = v20+a2*b0;
                    v21 = v21+a2*b1;
                    v30 = v30+a3*b0;
                    v31 = v31+a3*b1;
                    b2 = b->ptr.pp_double[offsb][idxb2];
                    b3 = b->ptr.pp_double[offsb][idxb3];
                    v22 = v22+a2*b2;
                    v23 = v23+a2*b3;
                    v32 = v32+a3*b2;
                    v33 = v33+a3*b3;
                    v02 = v02+a0*b2;
                    v03 = v03+a0*b3;
                    v12 = v12+a1*b2;
                    v13 = v13+a1*b3;
                    offsa = offsa+1;
                    offsb = offsb+1;
                }
                if( ae_fp_eq(beta,(double)(0)) )
                {
                    c->ptr.pp_double[ic+i+0][jc+j+0] = alpha*v00;
                    c->ptr.pp_double[ic+i+0][jc+j+1] = alpha*v01;
                    c->ptr.pp_double[ic+i+0][jc+j+2] = alpha*v02;
                    c->ptr.pp_double[ic+i+0][jc+j+3] = alpha*v03;
                    c->ptr.pp_double[ic+i+1][jc+j+0] = alpha*v10;
                    c->ptr.pp_double[ic+i+1][jc+j+1] = alpha*v11;
                    c->ptr.pp_double[ic+i+1][jc+j+2] = alpha*v12;
                    c->ptr.pp_double[ic+i+1][jc+j+3] = alpha*v13;
                    c->ptr.pp_double[ic+i+2][jc+j+0] = alpha*v20;
                    c->ptr.pp_double[ic+i+2][jc+j+1] = alpha*v21;
                    c->ptr.pp_double[ic+i+2][jc+j+2] = alpha*v22;
                    c->ptr.pp_double[ic+i+2][jc+j+3] = alpha*v23;
                    c->ptr.pp_double[ic+i+3][jc+j+0] = alpha*v30;
                    c->ptr.pp_double[ic+i+3][jc+j+1] = alpha*v31;
                    c->ptr.pp_double[ic+i+3][jc+j+2] = alpha*v32;
                    c->ptr.pp_double[ic+i+3][jc+j+3] = alpha*v33;
                }
                else
                {
                    c->ptr.pp_double[ic+i+0][jc+j+0] = beta*c->ptr.pp_double[ic+i+0][jc+j+0]+alpha*v00;
                    c->ptr.pp_double[ic+i+0][jc+j+1] = beta*c->ptr.pp_double[ic+i+0][jc+j+1]+alpha*v01;
                    c->ptr.pp_double[ic+i+0][jc+j+2] = beta*c->ptr.pp_double[ic+i+0][jc+j+2]+alpha*v02;
                    c->ptr.pp_double[ic+i+0][jc+j+3] = beta*c->ptr.pp_double[ic+i+0][jc+j+3]+alpha*v03;
                    c->ptr.pp_double[ic+i+1][jc+j+0] = beta*c->ptr.pp_double[ic+i+1][jc+j+0]+alpha*v10;
                    c->ptr.pp_double[ic+i+1][jc+j+1] = beta*c->ptr.pp_double[ic+i+1][jc+j+1]+alpha*v11;
                    c->ptr.pp_double[ic+i+1][jc+j+2] = beta*c->ptr.pp_double[ic+i+1][jc+j+2]+alpha*v12;
                    c->ptr.pp_double[ic+i+1][jc+j+3] = beta*c->ptr.pp_double[ic+i+1][jc+j+3]+alpha*v13;
                    c->ptr.pp_double[ic+i+2][jc+j+0] = beta*c->ptr.pp_double[ic+i+2][jc+j+0]+alpha*v20;
                    c->ptr.pp_double[ic+i+2][jc+j+1] = beta*c->ptr.pp_double[ic+i+2][jc+j+1]+alpha*v21;
                    c->ptr.pp_double[ic+i+2][jc+j+2] = beta*c->ptr.pp_double[ic+i+2][jc+j+2]+alpha*v22;
                    c->ptr.pp_double[ic+i+2][jc+j+3] = beta*c->ptr.pp_double[ic+i+2][jc+j+3]+alpha*v23;
                    c->ptr.pp_double[ic+i+3][jc+j+0] = beta*c->ptr.pp_double[ic+i+3][jc+j+0]+alpha*v30;
                    c->ptr.pp_double[ic+i+3][jc+j+1] = beta*c->ptr.pp_double[ic+i+3][jc+j+1]+alpha*v31;
                    c->ptr.pp_double[ic+i+3][jc+j+2] = beta*c->ptr.pp_double[ic+i+3][jc+j+2]+alpha*v32;
                    c->ptr.pp_double[ic+i+3][jc+j+3] = beta*c->ptr.pp_double[ic+i+3][jc+j+3]+alpha*v33;
                }
            }
            else
            {
                
                /*
                 * Determine submatrix [I0..I1]x[J0..J1] to process
                 */
                i0 = i;
                i1 = ae_minint(i+3, m-1, _state);
                j0 = j;
                j1 = ae_minint(j+3, n-1, _state);
                
                /*
                 * Process submatrix
                 */
                for(ik=i0; ik<=i1; ik++)
                {
                    for(jk=j0; jk<=j1; jk++)
                    {
                        if( k==0||ae_fp_eq(alpha,(double)(0)) )
                        {
                            v = (double)(0);
                        }
                        else
                        {
                            v = 0.0;
                            v = ae_v_dotproduct(&a->ptr.pp_double[ia][ja+ik], a->stride, &b->ptr.pp_double[ib][jb+jk], b->stride, ae_v_len(ia,ia+k-1));
                        }
                        if( ae_fp_eq(beta,(double)(0)) )
                        {
                            c->ptr.pp_double[ic+ik][jc+jk] = alpha*v;
                        }
                        else
                        {
                            c->ptr.pp_double[ic+ik][jc+jk] = beta*c->ptr.pp_double[ic+ik][jc+jk]+alpha*v;
                        }
                    }
                }
            }
            j = j+4;
        }
        i = i+4;
    }
}


/*************************************************************************
RMatrixGEMM kernel, basecase code for RMatrixGEMM, specialized for sitation
with OpTypeA=1 and OpTypeB=1.

Additional info:
* this function requires that Alpha<>0 (assertion is thrown otherwise)

INPUT PARAMETERS
    M       -   matrix size, M>0
    N       -   matrix size, N>0
    K       -   matrix size, K>0
    Alpha   -   coefficient
    A       -   matrix
    IA      -   submatrix offset
    JA      -   submatrix offset
    B       -   matrix
    IB      -   submatrix offset
    JB      -   submatrix offset
    Beta    -   coefficient
    C       -   PREALLOCATED output matrix
    IC      -   submatrix offset
    JC      -   submatrix offset

  -- ALGLIB routine --
     27.03.2013
     Bochkanov Sergey
*************************************************************************/
void rmatrixgemmk44v11(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    double v;
    double v00;
    double v01;
    double v02;
    double v03;
    double v10;
    double v11;
    double v12;
    double v13;
    double v20;
    double v21;
    double v22;
    double v23;
    double v30;
    double v31;
    double v32;
    double v33;
    double a0;
    double a1;
    double a2;
    double a3;
    double b0;
    double b1;
    double b2;
    double b3;
    ae_int_t idxa0;
    ae_int_t idxa1;
    ae_int_t idxa2;
    ae_int_t idxa3;
    ae_int_t idxb0;
    ae_int_t idxb1;
    ae_int_t idxb2;
    ae_int_t idxb3;
    ae_int_t i0;
    ae_int_t i1;
    ae_int_t ik;
    ae_int_t j0;
    ae_int_t j1;
    ae_int_t jk;
    ae_int_t t;
    ae_int_t offsa;
    ae_int_t offsb;


    ae_assert(ae_fp_neq(alpha,(double)(0)), "RMatrixGEMMK44V00: internal error (Alpha=0)", _state);
    
    /*
     * if matrix size is zero
     */
    if( m==0||n==0 )
    {
        return;
    }
    
    /*
     * A'*B'
     */
    i = 0;
    while(i<m)
    {
        j = 0;
        while(j<n)
        {
            
            /*
             * Choose between specialized 4x4 code and general code
             */
            if( i+4<=m&&j+4<=n )
            {
                
                /*
                 * Specialized 4x4 code for [I..I+3]x[J..J+3] submatrix of C.
                 *
                 * This submatrix is calculated as sum of K rank-1 products,
                 * with operands cached in local variables in order to speed
                 * up operations with arrays.
                 */
                idxa0 = ja+i+0;
                idxa1 = ja+i+1;
                idxa2 = ja+i+2;
                idxa3 = ja+i+3;
                offsa = ia;
                idxb0 = ib+j+0;
                idxb1 = ib+j+1;
                idxb2 = ib+j+2;
                idxb3 = ib+j+3;
                offsb = jb;
                v00 = 0.0;
                v01 = 0.0;
                v02 = 0.0;
                v03 = 0.0;
                v10 = 0.0;
                v11 = 0.0;
                v12 = 0.0;
                v13 = 0.0;
                v20 = 0.0;
                v21 = 0.0;
                v22 = 0.0;
                v23 = 0.0;
                v30 = 0.0;
                v31 = 0.0;
                v32 = 0.0;
                v33 = 0.0;
                for(t=0; t<=k-1; t++)
                {
                    a0 = a->ptr.pp_double[offsa][idxa0];
                    a1 = a->ptr.pp_double[offsa][idxa1];
                    b0 = b->ptr.pp_double[idxb0][offsb];
                    b1 = b->ptr.pp_double[idxb1][offsb];
                    v00 = v00+a0*b0;
                    v01 = v01+a0*b1;
                    v10 = v10+a1*b0;
                    v11 = v11+a1*b1;
                    a2 = a->ptr.pp_double[offsa][idxa2];
                    a3 = a->ptr.pp_double[offsa][idxa3];
                    v20 = v20+a2*b0;
                    v21 = v21+a2*b1;
                    v30 = v30+a3*b0;
                    v31 = v31+a3*b1;
                    b2 = b->ptr.pp_double[idxb2][offsb];
                    b3 = b->ptr.pp_double[idxb3][offsb];
                    v22 = v22+a2*b2;
                    v23 = v23+a2*b3;
                    v32 = v32+a3*b2;
                    v33 = v33+a3*b3;
                    v02 = v02+a0*b2;
                    v03 = v03+a0*b3;
                    v12 = v12+a1*b2;
                    v13 = v13+a1*b3;
                    offsa = offsa+1;
                    offsb = offsb+1;
                }
                if( ae_fp_eq(beta,(double)(0)) )
                {
                    c->ptr.pp_double[ic+i+0][jc+j+0] = alpha*v00;
                    c->ptr.pp_double[ic+i+0][jc+j+1] = alpha*v01;
                    c->ptr.pp_double[ic+i+0][jc+j+2] = alpha*v02;
                    c->ptr.pp_double[ic+i+0][jc+j+3] = alpha*v03;
                    c->ptr.pp_double[ic+i+1][jc+j+0] = alpha*v10;
                    c->ptr.pp_double[ic+i+1][jc+j+1] = alpha*v11;
                    c->ptr.pp_double[ic+i+1][jc+j+2] = alpha*v12;
                    c->ptr.pp_double[ic+i+1][jc+j+3] = alpha*v13;
                    c->ptr.pp_double[ic+i+2][jc+j+0] = alpha*v20;
                    c->ptr.pp_double[ic+i+2][jc+j+1] = alpha*v21;
                    c->ptr.pp_double[ic+i+2][jc+j+2] = alpha*v22;
                    c->ptr.pp_double[ic+i+2][jc+j+3] = alpha*v23;
                    c->ptr.pp_double[ic+i+3][jc+j+0] = alpha*v30;
                    c->ptr.pp_double[ic+i+3][jc+j+1] = alpha*v31;
                    c->ptr.pp_double[ic+i+3][jc+j+2] = alpha*v32;
                    c->ptr.pp_double[ic+i+3][jc+j+3] = alpha*v33;
                }
                else
                {
                    c->ptr.pp_double[ic+i+0][jc+j+0] = beta*c->ptr.pp_double[ic+i+0][jc+j+0]+alpha*v00;
                    c->ptr.pp_double[ic+i+0][jc+j+1] = beta*c->ptr.pp_double[ic+i+0][jc+j+1]+alpha*v01;
                    c->ptr.pp_double[ic+i+0][jc+j+2] = beta*c->ptr.pp_double[ic+i+0][jc+j+2]+alpha*v02;
                    c->ptr.pp_double[ic+i+0][jc+j+3] = beta*c->ptr.pp_double[ic+i+0][jc+j+3]+alpha*v03;
                    c->ptr.pp_double[ic+i+1][jc+j+0] = beta*c->ptr.pp_double[ic+i+1][jc+j+0]+alpha*v10;
                    c->ptr.pp_double[ic+i+1][jc+j+1] = beta*c->ptr.pp_double[ic+i+1][jc+j+1]+alpha*v11;
                    c->ptr.pp_double[ic+i+1][jc+j+2] = beta*c->ptr.pp_double[ic+i+1][jc+j+2]+alpha*v12;
                    c->ptr.pp_double[ic+i+1][jc+j+3] = beta*c->ptr.pp_double[ic+i+1][jc+j+3]+alpha*v13;
                    c->ptr.pp_double[ic+i+2][jc+j+0] = beta*c->ptr.pp_double[ic+i+2][jc+j+0]+alpha*v20;
                    c->ptr.pp_double[ic+i+2][jc+j+1] = beta*c->ptr.pp_double[ic+i+2][jc+j+1]+alpha*v21;
                    c->ptr.pp_double[ic+i+2][jc+j+2] = beta*c->ptr.pp_double[ic+i+2][jc+j+2]+alpha*v22;
                    c->ptr.pp_double[ic+i+2][jc+j+3] = beta*c->ptr.pp_double[ic+i+2][jc+j+3]+alpha*v23;
                    c->ptr.pp_double[ic+i+3][jc+j+0] = beta*c->ptr.pp_double[ic+i+3][jc+j+0]+alpha*v30;
                    c->ptr.pp_double[ic+i+3][jc+j+1] = beta*c->ptr.pp_double[ic+i+3][jc+j+1]+alpha*v31;
                    c->ptr.pp_double[ic+i+3][jc+j+2] = beta*c->ptr.pp_double[ic+i+3][jc+j+2]+alpha*v32;
                    c->ptr.pp_double[ic+i+3][jc+j+3] = beta*c->ptr.pp_double[ic+i+3][jc+j+3]+alpha*v33;
                }
            }
            else
            {
                
                /*
                 * Determine submatrix [I0..I1]x[J0..J1] to process
                 */
                i0 = i;
                i1 = ae_minint(i+3, m-1, _state);
                j0 = j;
                j1 = ae_minint(j+3, n-1, _state);
                
                /*
                 * Process submatrix
                 */
                for(ik=i0; ik<=i1; ik++)
                {
                    for(jk=j0; jk<=j1; jk++)
                    {
                        if( k==0||ae_fp_eq(alpha,(double)(0)) )
                        {
                            v = (double)(0);
                        }
                        else
                        {
                            v = 0.0;
                            v = ae_v_dotproduct(&a->ptr.pp_double[ia][ja+ik], a->stride, &b->ptr.pp_double[ib+jk][jb], 1, ae_v_len(ia,ia+k-1));
                        }
                        if( ae_fp_eq(beta,(double)(0)) )
                        {
                            c->ptr.pp_double[ic+ik][jc+jk] = alpha*v;
                        }
                        else
                        {
                            c->ptr.pp_double[ic+ik][jc+jk] = beta*c->ptr.pp_double[ic+ik][jc+jk]+alpha*v;
                        }
                    }
                }
            }
            j = j+4;
        }
        i = i+4;
    }
}

#endif
#if defined(AE_COMPILE_ABLASMKL) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
MKL-based kernel

  -- ALGLIB routine --
     12.10.2017
     Bochkanov Sergey
*************************************************************************/
ae_bool rmatrixmvmkl(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t opa,
     /* Real    */ ae_vector* x,
     ae_int_t ix,
     /* Real    */ ae_vector* y,
     ae_int_t iy,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_MKL
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_rmatrixmvmkl(m, n, a, ia, ja, opa, x, ix, y, iy);
#endif
}
/*************************************************************************
MKL-based kernel

  -- ALGLIB routine --
     01.10.2013
     Bochkanov Sergey
*************************************************************************/
ae_bool rmatrixsyrkmkl(ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_MKL
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_rmatrixsyrkmkl(n, k, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper);
#endif
}
/*************************************************************************
MKL-based kernel

  -- ALGLIB routine --
     01.10.2013
     Bochkanov Sergey
*************************************************************************/
ae_bool rmatrixgemmmkl(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_MKL
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_rmatrixgemmmkl(m, n, k, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc);
#endif
}
/*************************************************************************
MKL-based kernel

  -- ALGLIB routine --
     16.10.2014
     Bochkanov Sergey
*************************************************************************/
ae_bool rmatrixlefttrsmmkl(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_MKL
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_rmatrixlefttrsmmkl(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2);
#endif
}
/*************************************************************************
MKL-based kernel

  -- ALGLIB routine --
     16.10.2014
     Bochkanov Sergey
*************************************************************************/
ae_bool rmatrixrighttrsmmkl(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_MKL
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_rmatrixrighttrsmmkl(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2);
#endif
}




/*************************************************************************
MKL-based kernel.

NOTE:

if function returned False, CholResult is NOT modified. Not ever referenced!
if function returned True, CholResult is set to status of Cholesky decomposition
(True on succeess).

  -- ALGLIB routine --
     16.10.2014
     Bochkanov Sergey
*************************************************************************/
ae_bool spdmatrixcholeskymkl(/* Real    */ ae_matrix* a,
     ae_int_t offs,
     ae_int_t n,
     ae_bool isupper,
     ae_bool* cholresult,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_MKL
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_spdmatrixcholeskymkl(a, offs, n, isupper, cholresult);
#endif
}
/*************************************************************************
MKL-based kernel.

Returns True if MKL was present and handled request (MKL  completion  code
is returned as separate output parameter).

D and E are pre-allocated arrays with length N (both of them!). On output,
D constraints eigenvalues, and E is destroyed.

Z is preallocated array[N,N] for ZNeeded<>0; ignored for ZNeeded=0.

EVDResult is modified if and only if MKL is present.

  -- ALGLIB routine --
     20.10.2014
     Bochkanov Sergey
*************************************************************************/
ae_bool sparsegemvcrsmkl(ae_int_t opa,
     ae_int_t arows,
     ae_int_t acols,
     double alpha,
     /* Real    */ ae_vector* vals,
     /* Integer */ ae_vector* cidx,
     /* Integer */ ae_vector* ridx,
     /* Real    */ ae_vector* x,
     ae_int_t ix,
     double beta,
     /* Real    */ ae_vector* y,
     ae_int_t iy,
     ae_state *_state)
{
#ifndef ALGLIB_INTERCEPTS_MKL
    ae_bool result;


    result = ae_false;
    return result;
#else
    return _ialglib_i_sparsegemvcrsmkl(opa, arows, acols, alpha, vals, cidx, ridx, x, ix, beta, y, iy);
#endif
}
#endif
#if defined(AE_COMPILE_TSORT) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
Same as TagSort, but optimized for real keys and integer labels.

A is sorted, and same permutations are applied to B.

NOTES:
1.  this function assumes that A[] is finite; it doesn't checks that
    condition. All other conditions (size of input arrays, etc.) are not
    checked too.
2.  this function uses two buffers, BufA and BufB, each is N elements large.
    They may be preallocated (which will save some time) or not, in which
    case function will automatically allocate memory.

  -- ALGLIB --
     Copyright 11.12.2008 by Bochkanov Sergey
*************************************************************************/
void tagsortfasti(/* Real    */ ae_vector* a,
     /* Integer */ ae_vector* b,
     /* Real    */ ae_vector* bufa,
     /* Integer */ ae_vector* bufb,
     ae_int_t n,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_bool isascending;
    ae_bool isdescending;
    double tmpr;
    ae_int_t tmpi;


    
    /*
     * Special case
     */
    if( n<=1 )
    {
        return;
    }
    
    /*
     * Test for already sorted set
     */
    isascending = ae_true;
    isdescending = ae_true;
    for(i=1; i<=n-1; i++)
    {
        isascending = isascending&&a->ptr.p_double[i]>=a->ptr.p_double[i-1];
        isdescending = isdescending&&a->ptr.p_double[i]<=a->ptr.p_double[i-1];
    }
    if( isascending )
    {
        return;
    }
    if( isdescending )
    {
        for(i=0; i<=n-1; i++)
        {
            j = n-1-i;
            if( j<=i )
            {
                break;
            }
            tmpr = a->ptr.p_double[i];
            a->ptr.p_double[i] = a->ptr.p_double[j];
            a->ptr.p_double[j] = tmpr;
            tmpi = b->ptr.p_int[i];
            b->ptr.p_int[i] = b->ptr.p_int[j];
            b->ptr.p_int[j] = tmpi;
        }
        return;
    }
    
    /*
     * General case
     */
    if( bufa->cnt<n )
    {
        ae_vector_set_length(bufa, n, _state);
    }
    if( bufb->cnt<n )
    {
        ae_vector_set_length(bufb, n, _state);
    }
    tsort_tagsortfastirec(a, b, bufa, bufb, 0, n-1, _state);
}
/*************************************************************************
Same as TagSort, but optimized for real keys and real labels.

A is sorted, and same permutations are applied to B.

NOTES:
1.  this function assumes that A[] is finite; it doesn't checks that
    condition. All other conditions (size of input arrays, etc.) are not
    checked too.
2.  this function uses two buffers, BufA and BufB, each is N elements large.
    They may be preallocated (which will save some time) or not, in which
    case function will automatically allocate memory.

  -- ALGLIB --
     Copyright 11.12.2008 by Bochkanov Sergey
*************************************************************************/
void tagsortfastr(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* bufa,
     /* Real    */ ae_vector* bufb,
     ae_int_t n,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_bool isascending;
    ae_bool isdescending;
    double tmpr;


    
    /*
     * Special case
     */
    if( n<=1 )
    {
        return;
    }
    
    /*
     * Test for already sorted set
     */
    isascending = ae_true;
    isdescending = ae_true;
    for(i=1; i<=n-1; i++)
    {
        isascending = isascending&&a->ptr.p_double[i]>=a->ptr.p_double[i-1];
        isdescending = isdescending&&a->ptr.p_double[i]<=a->ptr.p_double[i-1];
    }
    if( isascending )
    {
        return;
    }
    if( isdescending )
    {
        for(i=0; i<=n-1; i++)
        {
            j = n-1-i;
            if( j<=i )
            {
                break;
            }
            tmpr = a->ptr.p_double[i];
            a->ptr.p_double[i] = a->ptr.p_double[j];
            a->ptr.p_double[j] = tmpr;
            tmpr = b->ptr.p_double[i];
            b->ptr.p_double[i] = b->ptr.p_double[j];
            b->ptr.p_double[j] = tmpr;
        }
        return;
    }
    
    /*
     * General case
     */
    if( bufa->cnt<n )
    {
        ae_vector_set_length(bufa, n, _state);
    }
    if( bufb->cnt<n )
    {
        ae_vector_set_length(bufb, n, _state);
    }
    tsort_tagsortfastrrec(a, b, bufa, bufb, 0, n-1, _state);
}
/*************************************************************************
Sorting function optimized for integer keys and real labels, can be used
to sort middle of the array

A is sorted, and same permutations are applied to B.

NOTES:
    this function assumes that A[] is finite; it doesn't checks that
    condition. All other conditions (size of input arrays, etc.) are not
    checked too.

  -- ALGLIB --
     Copyright 11.12.2008 by Bochkanov Sergey
*************************************************************************/
void tagsortmiddleir(/* Integer */ ae_vector* a,
     /* Real    */ ae_vector* b,
     ae_int_t offset,
     ae_int_t n,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t k;
    ae_int_t t;
    ae_int_t tmp;
    double tmpr;
    ae_int_t p0;
    ae_int_t p1;
    ae_int_t at;
    ae_int_t ak;
    ae_int_t ak1;
    double bt;


    
    /*
     * Special cases
     */
    if( n<=1 )
    {
        return;
    }
    
    /*
     * General case, N>1: sort, update B
     */
    for(i=2; i<=n; i++)
    {
        t = i;
        while(t!=1)
        {
            k = t/2;
            p0 = offset+k-1;
            p1 = offset+t-1;
            ak = a->ptr.p_int[p0];
            at = a->ptr.p_int[p1];
            if( ak>=at )
            {
                break;
            }
            a->ptr.p_int[p0] = at;
            a->ptr.p_int[p1] = ak;
            tmpr = b->ptr.p_double[p0];
            b->ptr.p_double[p0] = b->ptr.p_double[p1];
            b->ptr.p_double[p1] = tmpr;
            t = k;
        }
    }
    for(i=n-1; i>=1; i--)
    {
        p0 = offset+0;
        p1 = offset+i;
        tmp = a->ptr.p_int[p1];
        a->ptr.p_int[p1] = a->ptr.p_int[p0];
        a->ptr.p_int[p0] = tmp;
        at = tmp;
        tmpr = b->ptr.p_double[p1];
        b->ptr.p_double[p1] = b->ptr.p_double[p0];
        b->ptr.p_double[p0] = tmpr;
        bt = tmpr;
        t = 0;
        for(;;)
        {
            k = 2*t+1;
            if( k+1>i )
            {
                break;
            }
            p0 = offset+t;
            p1 = offset+k;
            ak = a->ptr.p_int[p1];
            if( k+1<i )
            {
                ak1 = a->ptr.p_int[p1+1];
                if( ak1>ak )
                {
                    ak = ak1;
                    p1 = p1+1;
                    k = k+1;
                }
            }
            if( at>=ak )
            {
                break;
            }
            a->ptr.p_int[p1] = at;
            a->ptr.p_int[p0] = ak;
            b->ptr.p_double[p0] = b->ptr.p_double[p1];
            b->ptr.p_double[p1] = bt;
            t = k;
        }
    }
}
/*************************************************************************
Internal TagSortFastI: sorts A[I1...I2] (both bounds are included),
applies same permutations to B.

  -- ALGLIB --
     Copyright 06.09.2010 by Bochkanov Sergey
*************************************************************************/
static void tsort_tagsortfastirec(/* Real    */ ae_vector* a,
     /* Integer */ ae_vector* b,
     /* Real    */ ae_vector* bufa,
     /* Integer */ ae_vector* bufb,
     ae_int_t i1,
     ae_int_t i2,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    ae_int_t cntless;
    ae_int_t cnteq;
    ae_int_t cntgreater;
    double tmpr;
    ae_int_t tmpi;
    double v0;
    double v1;
    double v2;
    double vp;


    
    /*
     * Fast exit
     */
    if( i2<=i1 )
    {
        return;
    }
    
    /*
     * Non-recursive sort for small arrays
     */
    if( i2-i1<=16 )
    {
        for(j=i1+1; j<=i2; j++)
        {
            
            /*
             * Search elements [I1..J-1] for place to insert Jth element.
             *
             * This code stops immediately if we can leave A[J] at J-th position
             * (all elements have same value of A[J] larger than any of them)
             */
            tmpr = a->ptr.p_double[j];
            tmpi = j;
            for(k=j-1; k>=i1; k--)
            {
                if( a->ptr.p_double[k]<=tmpr )
                {
                    break;
                }
                tmpi = k;
            }
            k = tmpi;
            
            /*
             * Insert Jth element into Kth position
             */
            if( k!=j )
            {
                tmpr = a->ptr.p_double[j];
                tmpi = b->ptr.p_int[j];
                for(i=j-1; i>=k; i--)
                {
                    a->ptr.p_double[i+1] = a->ptr.p_double[i];
                    b->ptr.p_int[i+1] = b->ptr.p_int[i];
                }
                a->ptr.p_double[k] = tmpr;
                b->ptr.p_int[k] = tmpi;
            }
        }
        return;
    }
    
    /*
     * Quicksort: choose pivot
     * Here we assume that I2-I1>=2
     */
    v0 = a->ptr.p_double[i1];
    v1 = a->ptr.p_double[i1+(i2-i1)/2];
    v2 = a->ptr.p_double[i2];
    if( v0>v1 )
    {
        tmpr = v1;
        v1 = v0;
        v0 = tmpr;
    }
    if( v1>v2 )
    {
        tmpr = v2;
        v2 = v1;
        v1 = tmpr;
    }
    if( v0>v1 )
    {
        tmpr = v1;
        v1 = v0;
        v0 = tmpr;
    }
    vp = v1;
    
    /*
     * now pass through A/B and:
     * * move elements that are LESS than VP to the left of A/B
     * * move elements that are EQUAL to VP to the right of BufA/BufB (in the reverse order)
     * * move elements that are GREATER than VP to the left of BufA/BufB (in the normal order
     * * move elements from the tail of BufA/BufB to the middle of A/B (restoring normal order)
     * * move elements from the left of BufA/BufB to the end of A/B
     */
    cntless = 0;
    cnteq = 0;
    cntgreater = 0;
    for(i=i1; i<=i2; i++)
    {
        v0 = a->ptr.p_double[i];
        if( v0<vp )
        {
            
            /*
             * LESS
             */
            k = i1+cntless;
            if( i!=k )
            {
                a->ptr.p_double[k] = v0;
                b->ptr.p_int[k] = b->ptr.p_int[i];
            }
            cntless = cntless+1;
            continue;
        }
        if( v0==vp )
        {
            
            /*
             * EQUAL
             */
            k = i2-cnteq;
            bufa->ptr.p_double[k] = v0;
            bufb->ptr.p_int[k] = b->ptr.p_int[i];
            cnteq = cnteq+1;
            continue;
        }
        
        /*
         * GREATER
         */
        k = i1+cntgreater;
        bufa->ptr.p_double[k] = v0;
        bufb->ptr.p_int[k] = b->ptr.p_int[i];
        cntgreater = cntgreater+1;
    }
    for(i=0; i<=cnteq-1; i++)
    {
        j = i1+cntless+cnteq-1-i;
        k = i2+i-(cnteq-1);
        a->ptr.p_double[j] = bufa->ptr.p_double[k];
        b->ptr.p_int[j] = bufb->ptr.p_int[k];
    }
    for(i=0; i<=cntgreater-1; i++)
    {
        j = i1+cntless+cnteq+i;
        k = i1+i;
        a->ptr.p_double[j] = bufa->ptr.p_double[k];
        b->ptr.p_int[j] = bufb->ptr.p_int[k];
    }
    
    /*
     * Sort left and right parts of the array (ignoring middle part)
     */
    tsort_tagsortfastirec(a, b, bufa, bufb, i1, i1+cntless-1, _state);
    tsort_tagsortfastirec(a, b, bufa, bufb, i1+cntless+cnteq, i2, _state);
}
/*************************************************************************
Internal TagSortFastR: sorts A[I1...I2] (both bounds are included),
applies same permutations to B.

  -- ALGLIB --
     Copyright 06.09.2010 by Bochkanov Sergey
*************************************************************************/
static void tsort_tagsortfastrrec(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* bufa,
     /* Real    */ ae_vector* bufb,
     ae_int_t i1,
     ae_int_t i2,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    double tmpr;
    double tmpr2;
    ae_int_t tmpi;
    ae_int_t cntless;
    ae_int_t cnteq;
    ae_int_t cntgreater;
    double v0;
    double v1;
    double v2;
    double vp;


    
    /*
     * Fast exit
     */
    if( i2<=i1 )
    {
        return;
    }
    
    /*
     * Non-recursive sort for small arrays
     */
    if( i2-i1<=16 )
    {
        for(j=i1+1; j<=i2; j++)
        {
            
            /*
             * Search elements [I1..J-1] for place to insert Jth element.
             *
             * This code stops immediatly if we can leave A[J] at J-th position
             * (all elements have same value of A[J] larger than any of them)
             */
            tmpr = a->ptr.p_double[j];
            tmpi = j;
            for(k=j-1; k>=i1; k--)
            {
                if( a->ptr.p_double[k]<=tmpr )
                {
                    break;
                }
                tmpi = k;
            }
            k = tmpi;
            
            /*
             * Insert Jth element into Kth position
             */
            if( k!=j )
            {
                tmpr = a->ptr.p_double[j];
                tmpr2 = b->ptr.p_double[j];
                for(i=j-1; i>=k; i--)
                {
                    a->ptr.p_double[i+1] = a->ptr.p_double[i];
                    b->ptr.p_double[i+1] = b->ptr.p_double[i];
                }
                a->ptr.p_double[k] = tmpr;
                b->ptr.p_double[k] = tmpr2;
            }
        }
        return;
    }
    
    /*
     * Quicksort: choose pivot
     * Here we assume that I2-I1>=16
     */
    v0 = a->ptr.p_double[i1];
    v1 = a->ptr.p_double[i1+(i2-i1)/2];
    v2 = a->ptr.p_double[i2];
    if( v0>v1 )
    {
        tmpr = v1;
        v1 = v0;
        v0 = tmpr;
    }
    if( v1>v2 )
    {
        tmpr = v2;
        v2 = v1;
        v1 = tmpr;
    }
    if( v0>v1 )
    {
        tmpr = v1;
        v1 = v0;
        v0 = tmpr;
    }
    vp = v1;
    
    /*
     * now pass through A/B and:
     * * move elements that are LESS than VP to the left of A/B
     * * move elements that are EQUAL to VP to the right of BufA/BufB (in the reverse order)
     * * move elements that are GREATER than VP to the left of BufA/BufB (in the normal order
     * * move elements from the tail of BufA/BufB to the middle of A/B (restoring normal order)
     * * move elements from the left of BufA/BufB to the end of A/B
     */
    cntless = 0;
    cnteq = 0;
    cntgreater = 0;
    for(i=i1; i<=i2; i++)
    {
        v0 = a->ptr.p_double[i];
        if( v0<vp )
        {
            
            /*
             * LESS
             */
            k = i1+cntless;
            if( i!=k )
            {
                a->ptr.p_double[k] = v0;
                b->ptr.p_double[k] = b->ptr.p_double[i];
            }
            cntless = cntless+1;
            continue;
        }
        if( v0==vp )
        {
            
            /*
             * EQUAL
             */
            k = i2-cnteq;
            bufa->ptr.p_double[k] = v0;
            bufb->ptr.p_double[k] = b->ptr.p_double[i];
            cnteq = cnteq+1;
            continue;
        }
        
        /*
         * GREATER
         */
        k = i1+cntgreater;
        bufa->ptr.p_double[k] = v0;
        bufb->ptr.p_double[k] = b->ptr.p_double[i];
        cntgreater = cntgreater+1;
    }
    for(i=0; i<=cnteq-1; i++)
    {
        j = i1+cntless+cnteq-1-i;
        k = i2+i-(cnteq-1);
        a->ptr.p_double[j] = bufa->ptr.p_double[k];
        b->ptr.p_double[j] = bufb->ptr.p_double[k];
    }
    for(i=0; i<=cntgreater-1; i++)
    {
        j = i1+cntless+cnteq+i;
        k = i1+i;
        a->ptr.p_double[j] = bufa->ptr.p_double[k];
        b->ptr.p_double[j] = bufb->ptr.p_double[k];
    }
    
    /*
     * Sort left and right parts of the array (ignoring middle part)
     */
    tsort_tagsortfastrrec(a, b, bufa, bufb, i1, i1+cntless-1, _state);
    tsort_tagsortfastrrec(a, b, bufa, bufb, i1+cntless+cnteq, i2, _state);
}
#endif

}

