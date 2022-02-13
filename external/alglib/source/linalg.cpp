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
#include "linalg.h"

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
#if defined(AE_COMPILE_ABLAS) || !defined(AE_PARTIAL_BUILD)
static ae_int_t ablas_blas2minvendorkernelsize = 8;
static void ablas_rmatrixrighttrsm2(ae_int_t m,
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
     ae_state *_state);
static void ablas_rmatrixlefttrsm2(ae_int_t m,
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
     ae_state *_state);
static void ablas_rmatrixsyrk2(ae_int_t n,
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
     ae_state *_state);
static void ablas_rmatrixgemmrec(ae_int_t m,
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
     ae_state *_state);
#endif
#if defined(AE_COMPILE_SPARSE) || !defined(AE_PARTIAL_BUILD)
static double sparse_desiredloadfactor = 0.66;
static double sparse_maxloadfactor = 0.75;
static double sparse_growfactor = 2.00;
static ae_int_t sparse_additional = 10;
static ae_int_t sparse_hash(ae_int_t i,
     ae_int_t j,
     ae_int_t tabsize,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_TRFAC) || !defined(AE_PARTIAL_BUILD)
static ae_bool trfac_spdmatrixcholesky2(/* Real    */ ae_matrix* aaa,
     ae_int_t offs,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* tmp,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_ABLAS) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
IMPORTANT: this function is deprecated since ALGLIB 3.13. Use RMatrixGEMV()
           which is more generic version of this function.
           
Matrix-vector product: y := op(A)*x

INPUT PARAMETERS:
    M   -   number of rows of op(A)
    N   -   number of columns of op(A)
    A   -   target matrix
    IA  -   submatrix offset (row index)
    JA  -   submatrix offset (column index)
    OpA -   operation type:
            * OpA=0     =>  op(A) = A
            * OpA=1     =>  op(A) = A^T
    X   -   input vector
    IX  -   subvector offset
    IY  -   subvector offset
    Y   -   preallocated matrix, must be large enough to store result

OUTPUT PARAMETERS:
    Y   -   vector which stores result

if M=0, then subroutine does nothing.
if N=0, Y is filled by zeros.


  -- ALGLIB routine --

     28.01.2010
     Bochkanov Sergey
*************************************************************************/
void rmatrixmv(ae_int_t m,
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
    ae_int_t i;
    double v;


    
    /*
     * Quick exit
     */
    if( m==0 )
    {
        return;
    }
    if( n==0 )
    {
        for(i=0; i<=m-1; i++)
        {
            y->ptr.p_double[iy+i] = (double)(0);
        }
        return;
    }
    
    /*
     * Try fast kernels
     */
    if( m>ablas_blas2minvendorkernelsize&&n>ablas_blas2minvendorkernelsize )
    {
        
        /*
         * Try MKL kernel
         */
        if( rmatrixmvmkl(m, n, a, ia, ja, opa, x, ix, y, iy, _state) )
        {
            return;
        }
    }
    
    /*
     * Generic code
     */
    if( opa==0 )
    {
        
        /*
         * y = A*x
         */
        for(i=0; i<=m-1; i++)
        {
            v = ae_v_dotproduct(&a->ptr.pp_double[ia+i][ja], 1, &x->ptr.p_double[ix], 1, ae_v_len(ja,ja+n-1));
            y->ptr.p_double[iy+i] = v;
        }
        return;
    }
    if( opa==1 )
    {
        
        /*
         * y = A^T*x
         */
        for(i=0; i<=m-1; i++)
        {
            y->ptr.p_double[iy+i] = (double)(0);
        }
        for(i=0; i<=n-1; i++)
        {
            v = x->ptr.p_double[ix+i];
            ae_v_addd(&y->ptr.p_double[iy], 1, &a->ptr.pp_double[ia+i][ja], 1, ae_v_len(iy,iy+m-1), v);
        }
        return;
    }
}
/*************************************************************************
This subroutine calculates X*op(A^-1) where:
* X is MxN general matrix
* A is NxN upper/lower triangular/unitriangular matrix
* "op" may be identity transformation, transposition
Multiplication result replaces X.

INPUT PARAMETERS
    N   -   matrix size, N>=0
    M   -   matrix size, N>=0
    A       -   matrix, actial matrix is stored in A[I1:I1+N-1,J1:J1+N-1]
    I1      -   submatrix offset
    J1      -   submatrix offset
    IsUpper -   whether matrix is upper triangular
    IsUnit  -   whether matrix is unitriangular
    OpType  -   transformation type:
                * 0 - no transformation
                * 1 - transposition
    X   -   matrix, actial matrix is stored in X[I2:I2+M-1,J2:J2+N-1]
    I2  -   submatrix offset
    J2  -   submatrix offset

  ! FREE EDITION OF ALGLIB:
  ! 
  ! Free Edition of ALGLIB supports following important features for  this
  ! function:
  ! * C++ version: x64 SIMD support using C++ intrinsics
  ! * C#  version: x64 SIMD support using NET5/NetCore hardware intrinsics
  !
  ! We  recommend  you  to  read  'Compiling ALGLIB' section of the ALGLIB
  ! Reference Manual in order  to  find  out  how to activate SIMD support
  ! in ALGLIB.

  ! COMMERCIAL EDITION OF ALGLIB:
  ! 
  ! Commercial Edition of ALGLIB includes following important improvements
  ! of this function:
  ! * high-performance native backend with same C# interface (C# version)
  ! * multithreading support (C++ and C# versions)
  ! * hardware vendor (Intel) implementations of linear algebra primitives
  !   (C++ and C# versions, x86/x64 platform)
  ! 
  ! We recommend you to read 'Working with commercial version' section  of
  ! ALGLIB Reference Manual in order to find out how to  use  performance-
  ! related features provided by commercial edition of ALGLIB.

  -- ALGLIB routine --
     15.12.2009-22.01.2018
     Bochkanov Sergey
*************************************************************************/
void rmatrixrighttrsm(ae_int_t m,
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
    ae_int_t s1;
    ae_int_t s2;
    ae_int_t tsa;
    ae_int_t tsb;
    ae_int_t tscur;


    tsa = matrixtilesizea(_state);
    tsb = matrixtilesizeb(_state);
    tscur = tsb;
    if( imax2(m, n, _state)<=tsb )
    {
        tscur = tsa;
    }
    ae_assert(tscur>=1, "RMatrixRightTRSM: integrity check failed", _state);
    
    /*
     * Upper level parallelization:
     * * decide whether it is feasible to activate multithreading
     * * perform optionally parallelized splits on M
     */
    if( m>=2*tsb&&ae_fp_greater_eq(rmul3((double)(m), (double)(n), (double)(n), _state),smpactivationlevel(_state)) )
    {
        if( _trypexec_rmatrixrighttrsm(m,n,a,i1,j1,isupper,isunit,optype,x,i2,j2, _state) )
        {
            return;
        }
    }
    if( m>=2*tsb )
    {
        
        /*
         * Split X: X*A = (X1 X2)^T*A
         */
        tiledsplit(m, tsb, &s1, &s2, _state);
        rmatrixrighttrsm(s1, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        rmatrixrighttrsm(s2, n, a, i1, j1, isupper, isunit, optype, x, i2+s1, j2, _state);
        return;
    }
    
    /*
     * Basecase: MKL or ALGLIB code
     */
    if( imax2(m, n, _state)<=tsb )
    {
        if( rmatrixrighttrsmmkl(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state) )
        {
            return;
        }
    }
    if( imax2(m, n, _state)<=tsa )
    {
        ablas_rmatrixrighttrsm2(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        return;
    }
    
    /*
     * Recursive subdivision
     */
    if( m>=n )
    {
        
        /*
         * Split X: X*A = (X1 X2)^T*A
         */
        tiledsplit(m, tscur, &s1, &s2, _state);
        rmatrixrighttrsm(s1, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        rmatrixrighttrsm(s2, n, a, i1, j1, isupper, isunit, optype, x, i2+s1, j2, _state);
    }
    else
    {
        
        /*
         * Split A:
         *               (A1  A12)
         * X*op(A) = X*op(       )
         *               (     A2)
         *
         * Different variants depending on
         * IsUpper/OpType combinations
         */
        tiledsplit(n, tscur, &s1, &s2, _state);
        if( isupper&&optype==0 )
        {
            
            /*
             *                  (A1  A12)-1
             * X*A^-1 = (X1 X2)*(       )
             *                  (     A2)
             */
            rmatrixrighttrsm(m, s1, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
            rmatrixgemm(m, s2, s1, -1.0, x, i2, j2, 0, a, i1, j1+s1, 0, 1.0, x, i2, j2+s1, _state);
            rmatrixrighttrsm(m, s2, a, i1+s1, j1+s1, isupper, isunit, optype, x, i2, j2+s1, _state);
        }
        if( isupper&&optype!=0 )
        {
            
            /*
             *                  (A1'     )-1
             * X*A^-1 = (X1 X2)*(        )
             *                  (A12' A2')
             */
            rmatrixrighttrsm(m, s2, a, i1+s1, j1+s1, isupper, isunit, optype, x, i2, j2+s1, _state);
            rmatrixgemm(m, s1, s2, -1.0, x, i2, j2+s1, 0, a, i1, j1+s1, optype, 1.0, x, i2, j2, _state);
            rmatrixrighttrsm(m, s1, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        }
        if( !isupper&&optype==0 )
        {
            
            /*
             *                  (A1     )-1
             * X*A^-1 = (X1 X2)*(       )
             *                  (A21  A2)
             */
            rmatrixrighttrsm(m, s2, a, i1+s1, j1+s1, isupper, isunit, optype, x, i2, j2+s1, _state);
            rmatrixgemm(m, s1, s2, -1.0, x, i2, j2+s1, 0, a, i1+s1, j1, 0, 1.0, x, i2, j2, _state);
            rmatrixrighttrsm(m, s1, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        }
        if( !isupper&&optype!=0 )
        {
            
            /*
             *                  (A1' A21')-1
             * X*A^-1 = (X1 X2)*(        )
             *                  (     A2')
             */
            rmatrixrighttrsm(m, s1, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
            rmatrixgemm(m, s2, s1, -1.0, x, i2, j2, 0, a, i1+s1, j1, optype, 1.0, x, i2, j2+s1, _state);
            rmatrixrighttrsm(m, s2, a, i1+s1, j1+s1, isupper, isunit, optype, x, i2, j2+s1, _state);
        }
    }
}
/*************************************************************************
Serial stub for GPL edition.
*************************************************************************/
ae_bool _trypexec_rmatrixrighttrsm(ae_int_t m,
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
    return ae_false;
}
/*************************************************************************
This subroutine calculates op(A^-1)*X where:
* X is MxN general matrix
* A is MxM upper/lower triangular/unitriangular matrix
* "op" may be identity transformation, transposition
Multiplication result replaces X.

INPUT PARAMETERS
    N   -   matrix size, N>=0
    M   -   matrix size, N>=0
    A       -   matrix, actial matrix is stored in A[I1:I1+M-1,J1:J1+M-1]
    I1      -   submatrix offset
    J1      -   submatrix offset
    IsUpper -   whether matrix is upper triangular
    IsUnit  -   whether matrix is unitriangular
    OpType  -   transformation type:
                * 0 - no transformation
                * 1 - transposition
    X   -   matrix, actial matrix is stored in X[I2:I2+M-1,J2:J2+N-1]
    I2  -   submatrix offset
    J2  -   submatrix offset

  ! FREE EDITION OF ALGLIB:
  ! 
  ! Free Edition of ALGLIB supports following important features for  this
  ! function:
  ! * C++ version: x64 SIMD support using C++ intrinsics
  ! * C#  version: x64 SIMD support using NET5/NetCore hardware intrinsics
  !
  ! We  recommend  you  to  read  'Compiling ALGLIB' section of the ALGLIB
  ! Reference Manual in order  to  find  out  how to activate SIMD support
  ! in ALGLIB.

  ! COMMERCIAL EDITION OF ALGLIB:
  ! 
  ! Commercial Edition of ALGLIB includes following important improvements
  ! of this function:
  ! * high-performance native backend with same C# interface (C# version)
  ! * multithreading support (C++ and C# versions)
  ! * hardware vendor (Intel) implementations of linear algebra primitives
  !   (C++ and C# versions, x86/x64 platform)
  ! 
  ! We recommend you to read 'Working with commercial version' section  of
  ! ALGLIB Reference Manual in order to find out how to  use  performance-
  ! related features provided by commercial edition of ALGLIB.

  -- ALGLIB routine --
     15.12.2009-22.01.2018
     Bochkanov Sergey
*************************************************************************/
void rmatrixlefttrsm(ae_int_t m,
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
    ae_int_t s1;
    ae_int_t s2;
    ae_int_t tsa;
    ae_int_t tsb;
    ae_int_t tscur;


    tsa = matrixtilesizea(_state);
    tsb = matrixtilesizeb(_state);
    tscur = tsb;
    if( imax2(m, n, _state)<=tsb )
    {
        tscur = tsa;
    }
    ae_assert(tscur>=1, "RMatrixLeftTRSMRec: integrity check failed", _state);
    
    /*
     * Upper level parallelization:
     * * decide whether it is feasible to activate multithreading
     * * perform optionally parallelized splits on N
     */
    if( n>=2*tsb&&ae_fp_greater_eq(rmul3((double)(n), (double)(m), (double)(m), _state),smpactivationlevel(_state)) )
    {
        if( _trypexec_rmatrixlefttrsm(m,n,a,i1,j1,isupper,isunit,optype,x,i2,j2, _state) )
        {
            return;
        }
    }
    if( n>=2*tsb )
    {
        tiledsplit(n, tscur, &s1, &s2, _state);
        rmatrixlefttrsm(m, s2, a, i1, j1, isupper, isunit, optype, x, i2, j2+s1, _state);
        rmatrixlefttrsm(m, s1, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        return;
    }
    
    /*
     * Basecase: MKL or ALGLIB code
     */
    if( imax2(m, n, _state)<=tsb )
    {
        if( rmatrixlefttrsmmkl(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state) )
        {
            return;
        }
    }
    if( imax2(m, n, _state)<=tsa )
    {
        ablas_rmatrixlefttrsm2(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        return;
    }
    
    /*
     * Recursive subdivision
     */
    if( n>=m )
    {
        
        /*
         * Split X: op(A)^-1*X = op(A)^-1*(X1 X2)
         */
        tiledsplit(n, tscur, &s1, &s2, _state);
        rmatrixlefttrsm(m, s1, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        rmatrixlefttrsm(m, s2, a, i1, j1, isupper, isunit, optype, x, i2, j2+s1, _state);
    }
    else
    {
        
        /*
         * Split A
         */
        tiledsplit(m, tscur, &s1, &s2, _state);
        if( isupper&&optype==0 )
        {
            
            /*
             *           (A1  A12)-1  ( X1 )
             * A^-1*X* = (       )   *(    )
             *           (     A2)    ( X2 )
             */
            rmatrixlefttrsm(s2, n, a, i1+s1, j1+s1, isupper, isunit, optype, x, i2+s1, j2, _state);
            rmatrixgemm(s1, n, s2, -1.0, a, i1, j1+s1, 0, x, i2+s1, j2, 0, 1.0, x, i2, j2, _state);
            rmatrixlefttrsm(s1, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        }
        if( isupper&&optype!=0 )
        {
            
            /*
             *          (A1'     )-1 ( X1 )
             * A^-1*X = (        )  *(    )
             *          (A12' A2')   ( X2 )
             */
            rmatrixlefttrsm(s1, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
            rmatrixgemm(s2, n, s1, -1.0, a, i1, j1+s1, optype, x, i2, j2, 0, 1.0, x, i2+s1, j2, _state);
            rmatrixlefttrsm(s2, n, a, i1+s1, j1+s1, isupper, isunit, optype, x, i2+s1, j2, _state);
        }
        if( !isupper&&optype==0 )
        {
            
            /*
             *          (A1     )-1 ( X1 )
             * A^-1*X = (       )  *(    )
             *          (A21  A2)   ( X2 )
             */
            rmatrixlefttrsm(s1, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
            rmatrixgemm(s2, n, s1, -1.0, a, i1+s1, j1, 0, x, i2, j2, 0, 1.0, x, i2+s1, j2, _state);
            rmatrixlefttrsm(s2, n, a, i1+s1, j1+s1, isupper, isunit, optype, x, i2+s1, j2, _state);
        }
        if( !isupper&&optype!=0 )
        {
            
            /*
             *          (A1' A21')-1 ( X1 )
             * A^-1*X = (        )  *(    )
             *          (     A2')   ( X2 )
             */
            rmatrixlefttrsm(s2, n, a, i1+s1, j1+s1, isupper, isunit, optype, x, i2+s1, j2, _state);
            rmatrixgemm(s1, n, s2, -1.0, a, i1+s1, j1, optype, x, i2+s1, j2, 0, 1.0, x, i2, j2, _state);
            rmatrixlefttrsm(s1, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state);
        }
    }
}
/*************************************************************************
Serial stub for GPL edition.
*************************************************************************/
ae_bool _trypexec_rmatrixlefttrsm(ae_int_t m,
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
    return ae_false;
}
/*************************************************************************
This subroutine calculates  C=alpha*A*A^T+beta*C  or  C=alpha*A^T*A+beta*C
where:
* C is NxN symmetric matrix given by its upper/lower triangle
* A is NxK matrix when A*A^T is calculated, KxN matrix otherwise

Additional info:
* multiplication result replaces C. If Beta=0, C elements are not used in
  calculations (not multiplied by zero - just not referenced)
* if Alpha=0, A is not used (not multiplied by zero - just not referenced)
* if both Beta and Alpha are zero, C is filled by zeros.

INPUT PARAMETERS
    N       -   matrix size, N>=0
    K       -   matrix size, K>=0
    Alpha   -   coefficient
    A       -   matrix
    IA      -   submatrix offset (row index)
    JA      -   submatrix offset (column index)
    OpTypeA -   multiplication type:
                * 0 - A*A^T is calculated
                * 2 - A^T*A is calculated
    Beta    -   coefficient
    C       -   preallocated input/output matrix
    IC      -   submatrix offset (row index)
    JC      -   submatrix offset (column index)
    IsUpper -   whether C is upper triangular or lower triangular

  ! FREE EDITION OF ALGLIB:
  ! 
  ! Free Edition of ALGLIB supports following important features for  this
  ! function:
  ! * C++ version: x64 SIMD support using C++ intrinsics
  ! * C#  version: x64 SIMD support using NET5/NetCore hardware intrinsics
  !
  ! We  recommend  you  to  read  'Compiling ALGLIB' section of the ALGLIB
  ! Reference Manual in order  to  find  out  how to activate SIMD support
  ! in ALGLIB.

  ! COMMERCIAL EDITION OF ALGLIB:
  ! 
  ! Commercial Edition of ALGLIB includes following important improvements
  ! of this function:
  ! * high-performance native backend with same C# interface (C# version)
  ! * multithreading support (C++ and C# versions)
  ! * hardware vendor (Intel) implementations of linear algebra primitives
  !   (C++ and C# versions, x86/x64 platform)
  ! 
  ! We recommend you to read 'Working with commercial version' section  of
  ! ALGLIB Reference Manual in order to find out how to  use  performance-
  ! related features provided by commercial edition of ALGLIB.

  -- ALGLIB routine --
     16.12.2009-22.01.2018
     Bochkanov Sergey
*************************************************************************/
void rmatrixsyrk(ae_int_t n,
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
    ae_int_t s1;
    ae_int_t s2;
    ae_int_t tsa;
    ae_int_t tsb;
    ae_int_t tscur;


    tsa = matrixtilesizea(_state);
    tsb = matrixtilesizeb(_state);
    tscur = tsb;
    if( imax2(n, k, _state)<=tsb )
    {
        tscur = tsa;
    }
    ae_assert(tscur>=1, "RMatrixSYRK: integrity check failed", _state);
    
    /*
     * Decide whether it is feasible to activate multithreading
     */
    if( n>=2*tsb&&ae_fp_greater_eq(2*rmul3((double)(k), (double)(n), (double)(n), _state)/2,smpactivationlevel(_state)) )
    {
        if( _trypexec_rmatrixsyrk(n,k,alpha,a,ia,ja,optypea,beta,c,ic,jc,isupper, _state) )
        {
            return;
        }
    }
    
    /*
     * Use MKL or generic basecase code
     */
    if( imax2(n, k, _state)<=tsb )
    {
        if( rmatrixsyrkmkl(n, k, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper, _state) )
        {
            return;
        }
    }
    if( imax2(n, k, _state)<=tsa )
    {
        ablas_rmatrixsyrk2(n, k, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper, _state);
        return;
    }
    
    /*
     * Recursive subdivision of the problem
     */
    if( k>=n )
    {
        
        /*
         * Split K
         */
        tiledsplit(k, tscur, &s1, &s2, _state);
        if( optypea==0 )
        {
            rmatrixsyrk(n, s1, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper, _state);
            rmatrixsyrk(n, s2, alpha, a, ia, ja+s1, optypea, 1.0, c, ic, jc, isupper, _state);
        }
        else
        {
            rmatrixsyrk(n, s1, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper, _state);
            rmatrixsyrk(n, s2, alpha, a, ia+s1, ja, optypea, 1.0, c, ic, jc, isupper, _state);
        }
    }
    else
    {
        
        /*
         * Split N
         */
        tiledsplit(n, tscur, &s1, &s2, _state);
        if( optypea==0&&isupper )
        {
            rmatrixsyrk(s1, k, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper, _state);
            rmatrixsyrk(s2, k, alpha, a, ia+s1, ja, optypea, beta, c, ic+s1, jc+s1, isupper, _state);
            rmatrixgemm(s1, s2, k, alpha, a, ia, ja, 0, a, ia+s1, ja, 1, beta, c, ic, jc+s1, _state);
        }
        if( optypea==0&&!isupper )
        {
            rmatrixsyrk(s1, k, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper, _state);
            rmatrixsyrk(s2, k, alpha, a, ia+s1, ja, optypea, beta, c, ic+s1, jc+s1, isupper, _state);
            rmatrixgemm(s2, s1, k, alpha, a, ia+s1, ja, 0, a, ia, ja, 1, beta, c, ic+s1, jc, _state);
        }
        if( optypea!=0&&isupper )
        {
            rmatrixsyrk(s1, k, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper, _state);
            rmatrixsyrk(s2, k, alpha, a, ia, ja+s1, optypea, beta, c, ic+s1, jc+s1, isupper, _state);
            rmatrixgemm(s1, s2, k, alpha, a, ia, ja, 1, a, ia, ja+s1, 0, beta, c, ic, jc+s1, _state);
        }
        if( optypea!=0&&!isupper )
        {
            rmatrixsyrk(s1, k, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper, _state);
            rmatrixsyrk(s2, k, alpha, a, ia, ja+s1, optypea, beta, c, ic+s1, jc+s1, isupper, _state);
            rmatrixgemm(s2, s1, k, alpha, a, ia, ja+s1, 1, a, ia, ja, 0, beta, c, ic+s1, jc, _state);
        }
    }
}
/*************************************************************************
Serial stub for GPL edition.
*************************************************************************/
ae_bool _trypexec_rmatrixsyrk(ae_int_t n,
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
    return ae_false;
}
/*************************************************************************
This subroutine calculates C = alpha*op1(A)*op2(B) +beta*C where:
* C is MxN general matrix
* op1(A) is MxK matrix
* op2(B) is KxN matrix
* "op" may be identity transformation, transposition

Additional info:
* cache-oblivious algorithm is used.
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
    C       -   PREALLOCATED output matrix, large enough to store result
    IC      -   submatrix offset
    JC      -   submatrix offset

  ! FREE EDITION OF ALGLIB:
  ! 
  ! Free Edition of ALGLIB supports following important features for  this
  ! function:
  ! * C++ version: x64 SIMD support using C++ intrinsics
  ! * C#  version: x64 SIMD support using NET5/NetCore hardware intrinsics
  !
  ! We  recommend  you  to  read  'Compiling ALGLIB' section of the ALGLIB
  ! Reference Manual in order  to  find  out  how to activate SIMD support
  ! in ALGLIB.

  ! COMMERCIAL EDITION OF ALGLIB:
  ! 
  ! Commercial Edition of ALGLIB includes following important improvements
  ! of this function:
  ! * high-performance native backend with same C# interface (C# version)
  ! * multithreading support (C++ and C# versions)
  ! * hardware vendor (Intel) implementations of linear algebra primitives
  !   (C++ and C# versions, x86/x64 platform)
  ! 
  ! We recommend you to read 'Working with commercial version' section  of
  ! ALGLIB Reference Manual in order to find out how to  use  performance-
  ! related features provided by commercial edition of ALGLIB.

  -- ALGLIB routine --
     2009-2019
     Bochkanov Sergey
*************************************************************************/
void rmatrixgemm(ae_int_t m,
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
    ae_int_t ts;


    ts = matrixtilesizeb(_state);
    
    /*
     * Check input sizes for correctness
     */
    ae_assert(optypea==0||optypea==1, "RMatrixGEMM: incorrect OpTypeA (must be 0 or 1)", _state);
    ae_assert(optypeb==0||optypeb==1, "RMatrixGEMM: incorrect OpTypeB (must be 0 or 1)", _state);
    ae_assert(ic+m<=c->rows, "RMatrixGEMM: incorect size of output matrix C", _state);
    ae_assert(jc+n<=c->cols, "RMatrixGEMM: incorect size of output matrix C", _state);
    
    /*
     * Decide whether it is feasible to activate multithreading
     */
    if( (m>=2*ts||n>=2*ts)&&ae_fp_greater_eq(2*rmul3((double)(m), (double)(n), (double)(k), _state),smpactivationlevel(_state)) )
    {
        if( _trypexec_rmatrixgemm(m,n,k,alpha,a,ia,ja,optypea,b,ib,jb,optypeb,beta,c,ic,jc, _state) )
        {
            return;
        }
    }
    
    /*
     * Start actual work
     */
    ablas_rmatrixgemmrec(m, n, k, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
}
/*************************************************************************
Serial stub for GPL edition.
*************************************************************************/
ae_bool _trypexec_rmatrixgemm(ae_int_t m,
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
    return ae_false;
}
/*************************************************************************
Level 2 subroutine

  -- ALGLIB routine --
     15.12.2009
     Bochkanov Sergey
*************************************************************************/
static void ablas_rmatrixrighttrsm2(ae_int_t m,
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
    ae_int_t i;
    ae_int_t j;
    double vr;
    double vd;


    
    /*
     * Special case
     */
    if( n*m==0 )
    {
        return;
    }
    
    /*
     * Try to use "fast" code
     */
    if( rmatrixrighttrsmf(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state) )
    {
        return;
    }
    
    /*
     * General case
     */
    if( isupper )
    {
        
        /*
         * Upper triangular matrix
         */
        if( optype==0 )
        {
            
            /*
             * X*A^(-1)
             */
            for(i=0; i<=m-1; i++)
            {
                for(j=0; j<=n-1; j++)
                {
                    if( isunit )
                    {
                        vd = (double)(1);
                    }
                    else
                    {
                        vd = a->ptr.pp_double[i1+j][j1+j];
                    }
                    x->ptr.pp_double[i2+i][j2+j] = x->ptr.pp_double[i2+i][j2+j]/vd;
                    if( j<n-1 )
                    {
                        vr = x->ptr.pp_double[i2+i][j2+j];
                        ae_v_subd(&x->ptr.pp_double[i2+i][j2+j+1], 1, &a->ptr.pp_double[i1+j][j1+j+1], 1, ae_v_len(j2+j+1,j2+n-1), vr);
                    }
                }
            }
            return;
        }
        if( optype==1 )
        {
            
            /*
             * X*A^(-T)
             */
            for(i=0; i<=m-1; i++)
            {
                for(j=n-1; j>=0; j--)
                {
                    vr = (double)(0);
                    vd = (double)(1);
                    if( j<n-1 )
                    {
                        vr = ae_v_dotproduct(&x->ptr.pp_double[i2+i][j2+j+1], 1, &a->ptr.pp_double[i1+j][j1+j+1], 1, ae_v_len(j2+j+1,j2+n-1));
                    }
                    if( !isunit )
                    {
                        vd = a->ptr.pp_double[i1+j][j1+j];
                    }
                    x->ptr.pp_double[i2+i][j2+j] = (x->ptr.pp_double[i2+i][j2+j]-vr)/vd;
                }
            }
            return;
        }
    }
    else
    {
        
        /*
         * Lower triangular matrix
         */
        if( optype==0 )
        {
            
            /*
             * X*A^(-1)
             */
            for(i=0; i<=m-1; i++)
            {
                for(j=n-1; j>=0; j--)
                {
                    if( isunit )
                    {
                        vd = (double)(1);
                    }
                    else
                    {
                        vd = a->ptr.pp_double[i1+j][j1+j];
                    }
                    x->ptr.pp_double[i2+i][j2+j] = x->ptr.pp_double[i2+i][j2+j]/vd;
                    if( j>0 )
                    {
                        vr = x->ptr.pp_double[i2+i][j2+j];
                        ae_v_subd(&x->ptr.pp_double[i2+i][j2], 1, &a->ptr.pp_double[i1+j][j1], 1, ae_v_len(j2,j2+j-1), vr);
                    }
                }
            }
            return;
        }
        if( optype==1 )
        {
            
            /*
             * X*A^(-T)
             */
            for(i=0; i<=m-1; i++)
            {
                for(j=0; j<=n-1; j++)
                {
                    vr = (double)(0);
                    vd = (double)(1);
                    if( j>0 )
                    {
                        vr = ae_v_dotproduct(&x->ptr.pp_double[i2+i][j2], 1, &a->ptr.pp_double[i1+j][j1], 1, ae_v_len(j2,j2+j-1));
                    }
                    if( !isunit )
                    {
                        vd = a->ptr.pp_double[i1+j][j1+j];
                    }
                    x->ptr.pp_double[i2+i][j2+j] = (x->ptr.pp_double[i2+i][j2+j]-vr)/vd;
                }
            }
            return;
        }
    }
}
/*************************************************************************
Level 2 subroutine
*************************************************************************/
static void ablas_rmatrixlefttrsm2(ae_int_t m,
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
    ae_int_t i;
    ae_int_t j;
    double vr;
    double vd;


    
    /*
     * Special case
     */
    if( n==0||m==0 )
    {
        return;
    }
    
    /*
     * Try fast code
     */
    if( rmatrixlefttrsmf(m, n, a, i1, j1, isupper, isunit, optype, x, i2, j2, _state) )
    {
        return;
    }
    
    /*
     * General case
     */
    if( isupper )
    {
        
        /*
         * Upper triangular matrix
         */
        if( optype==0 )
        {
            
            /*
             * A^(-1)*X
             */
            for(i=m-1; i>=0; i--)
            {
                for(j=i+1; j<=m-1; j++)
                {
                    vr = a->ptr.pp_double[i1+i][j1+j];
                    ae_v_subd(&x->ptr.pp_double[i2+i][j2], 1, &x->ptr.pp_double[i2+j][j2], 1, ae_v_len(j2,j2+n-1), vr);
                }
                if( !isunit )
                {
                    vd = 1/a->ptr.pp_double[i1+i][j1+i];
                    ae_v_muld(&x->ptr.pp_double[i2+i][j2], 1, ae_v_len(j2,j2+n-1), vd);
                }
            }
            return;
        }
        if( optype==1 )
        {
            
            /*
             * A^(-T)*X
             */
            for(i=0; i<=m-1; i++)
            {
                if( isunit )
                {
                    vd = (double)(1);
                }
                else
                {
                    vd = 1/a->ptr.pp_double[i1+i][j1+i];
                }
                ae_v_muld(&x->ptr.pp_double[i2+i][j2], 1, ae_v_len(j2,j2+n-1), vd);
                for(j=i+1; j<=m-1; j++)
                {
                    vr = a->ptr.pp_double[i1+i][j1+j];
                    ae_v_subd(&x->ptr.pp_double[i2+j][j2], 1, &x->ptr.pp_double[i2+i][j2], 1, ae_v_len(j2,j2+n-1), vr);
                }
            }
            return;
        }
    }
    else
    {
        
        /*
         * Lower triangular matrix
         */
        if( optype==0 )
        {
            
            /*
             * A^(-1)*X
             */
            for(i=0; i<=m-1; i++)
            {
                for(j=0; j<=i-1; j++)
                {
                    vr = a->ptr.pp_double[i1+i][j1+j];
                    ae_v_subd(&x->ptr.pp_double[i2+i][j2], 1, &x->ptr.pp_double[i2+j][j2], 1, ae_v_len(j2,j2+n-1), vr);
                }
                if( isunit )
                {
                    vd = (double)(1);
                }
                else
                {
                    vd = 1/a->ptr.pp_double[i1+j][j1+j];
                }
                ae_v_muld(&x->ptr.pp_double[i2+i][j2], 1, ae_v_len(j2,j2+n-1), vd);
            }
            return;
        }
        if( optype==1 )
        {
            
            /*
             * A^(-T)*X
             */
            for(i=m-1; i>=0; i--)
            {
                if( isunit )
                {
                    vd = (double)(1);
                }
                else
                {
                    vd = 1/a->ptr.pp_double[i1+i][j1+i];
                }
                ae_v_muld(&x->ptr.pp_double[i2+i][j2], 1, ae_v_len(j2,j2+n-1), vd);
                for(j=i-1; j>=0; j--)
                {
                    vr = a->ptr.pp_double[i1+i][j1+j];
                    ae_v_subd(&x->ptr.pp_double[i2+j][j2], 1, &x->ptr.pp_double[i2+i][j2], 1, ae_v_len(j2,j2+n-1), vr);
                }
            }
            return;
        }
    }
}
/*************************************************************************
Level 2 subrotuine
*************************************************************************/
static void ablas_rmatrixsyrk2(ae_int_t n,
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
    ae_int_t i;
    ae_int_t j;
    ae_int_t j1;
    ae_int_t j2;
    double v;


    
    /*
     * Fast exit (nothing to be done)
     */
    if( (ae_fp_eq(alpha,(double)(0))||k==0)&&ae_fp_eq(beta,(double)(1)) )
    {
        return;
    }
    
    /*
     * Try to call fast SYRK
     */
    if( rmatrixsyrkf(n, k, alpha, a, ia, ja, optypea, beta, c, ic, jc, isupper, _state) )
    {
        return;
    }
    
    /*
     * SYRK
     */
    if( optypea==0 )
    {
        
        /*
         * C=alpha*A*A^H+beta*C
         */
        for(i=0; i<=n-1; i++)
        {
            if( isupper )
            {
                j1 = i;
                j2 = n-1;
            }
            else
            {
                j1 = 0;
                j2 = i;
            }
            for(j=j1; j<=j2; j++)
            {
                if( ae_fp_neq(alpha,(double)(0))&&k>0 )
                {
                    v = ae_v_dotproduct(&a->ptr.pp_double[ia+i][ja], 1, &a->ptr.pp_double[ia+j][ja], 1, ae_v_len(ja,ja+k-1));
                }
                else
                {
                    v = (double)(0);
                }
                if( ae_fp_eq(beta,(double)(0)) )
                {
                    c->ptr.pp_double[ic+i][jc+j] = alpha*v;
                }
                else
                {
                    c->ptr.pp_double[ic+i][jc+j] = beta*c->ptr.pp_double[ic+i][jc+j]+alpha*v;
                }
            }
        }
        return;
    }
    else
    {
        
        /*
         * C=alpha*A^H*A+beta*C
         */
        for(i=0; i<=n-1; i++)
        {
            if( isupper )
            {
                j1 = i;
                j2 = n-1;
            }
            else
            {
                j1 = 0;
                j2 = i;
            }
            if( ae_fp_eq(beta,(double)(0)) )
            {
                for(j=j1; j<=j2; j++)
                {
                    c->ptr.pp_double[ic+i][jc+j] = (double)(0);
                }
            }
            else
            {
                ae_v_muld(&c->ptr.pp_double[ic+i][jc+j1], 1, ae_v_len(jc+j1,jc+j2), beta);
            }
        }
        if( ae_fp_neq(alpha,(double)(0))&&k>0 )
        {
            for(i=0; i<=k-1; i++)
            {
                for(j=0; j<=n-1; j++)
                {
                    if( isupper )
                    {
                        j1 = j;
                        j2 = n-1;
                    }
                    else
                    {
                        j1 = 0;
                        j2 = j;
                    }
                    v = alpha*a->ptr.pp_double[ia+i][ja+j];
                    ae_v_addd(&c->ptr.pp_double[ic+j][jc+j1], 1, &a->ptr.pp_double[ia+i][ja+j1], 1, ae_v_len(jc+j1,jc+j2), v);
                }
            }
        }
        return;
    }
}
/*************************************************************************
This subroutine is an actual implementation of RMatrixGEMM.  It  does  not
perform some integrity checks performed in the  driver  function,  and  it
does not activate multithreading  framework  (driver  decides  whether  to
activate workers or not).

  -- ALGLIB routine --
     10.01.2019
     Bochkanov Sergey
*************************************************************************/
static void ablas_rmatrixgemmrec(ae_int_t m,
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
    ae_int_t s1;
    ae_int_t s2;
    ae_int_t tsa;
    ae_int_t tsb;
    ae_int_t tscur;


    tsa = matrixtilesizea(_state);
    tsb = matrixtilesizeb(_state);
    tscur = tsb;
    if( imax3(m, n, k, _state)<=tsb )
    {
        tscur = tsa;
    }
    ae_assert(tscur>=1, "RMatrixGEMMRec: integrity check failed", _state);
    
    /*
     * Use MKL or ALGLIB basecase code
     */
    if( (m<=tsb&&n<=tsb)&&k<=tsb )
    {
        if( rmatrixgemmmkl(m, n, k, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state) )
        {
            return;
        }
    }
    if( (m<=tsa&&n<=tsa)&&k<=tsa )
    {
        rmatrixgemmk(m, n, k, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
        return;
    }
    
    /*
     * Recursive algorithm: split on M or N
     */
    if( m>=n&&m>=k )
    {
        
        /*
         * A*B = (A1 A2)^T*B
         */
        tiledsplit(m, tscur, &s1, &s2, _state);
        if( optypea==0 )
        {
            ablas_rmatrixgemmrec(s2, n, k, alpha, a, ia+s1, ja, optypea, b, ib, jb, optypeb, beta, c, ic+s1, jc, _state);
            ablas_rmatrixgemmrec(s1, n, k, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
        }
        else
        {
            ablas_rmatrixgemmrec(s2, n, k, alpha, a, ia, ja+s1, optypea, b, ib, jb, optypeb, beta, c, ic+s1, jc, _state);
            ablas_rmatrixgemmrec(s1, n, k, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
        }
        return;
    }
    if( n>=m&&n>=k )
    {
        
        /*
         * A*B = A*(B1 B2)
         */
        tiledsplit(n, tscur, &s1, &s2, _state);
        if( optypeb==0 )
        {
            ablas_rmatrixgemmrec(m, s2, k, alpha, a, ia, ja, optypea, b, ib, jb+s1, optypeb, beta, c, ic, jc+s1, _state);
            ablas_rmatrixgemmrec(m, s1, k, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
        }
        else
        {
            ablas_rmatrixgemmrec(m, s2, k, alpha, a, ia, ja, optypea, b, ib+s1, jb, optypeb, beta, c, ic, jc+s1, _state);
            ablas_rmatrixgemmrec(m, s1, k, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
        }
        return;
    }
    
    /*
     * Recursive algorithm: split on K
     */
    
    /*
     * A*B = (A1 A2)*(B1 B2)^T
     */
    tiledsplit(k, tscur, &s1, &s2, _state);
    if( optypea==0&&optypeb==0 )
    {
        ablas_rmatrixgemmrec(m, n, s1, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
        ablas_rmatrixgemmrec(m, n, s2, alpha, a, ia, ja+s1, optypea, b, ib+s1, jb, optypeb, 1.0, c, ic, jc, _state);
    }
    if( optypea==0&&optypeb!=0 )
    {
        ablas_rmatrixgemmrec(m, n, s1, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
        ablas_rmatrixgemmrec(m, n, s2, alpha, a, ia, ja+s1, optypea, b, ib, jb+s1, optypeb, 1.0, c, ic, jc, _state);
    }
    if( optypea!=0&&optypeb==0 )
    {
        ablas_rmatrixgemmrec(m, n, s1, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
        ablas_rmatrixgemmrec(m, n, s2, alpha, a, ia+s1, ja, optypea, b, ib+s1, jb, optypeb, 1.0, c, ic, jc, _state);
    }
    if( optypea!=0&&optypeb!=0 )
    {
        ablas_rmatrixgemmrec(m, n, s1, alpha, a, ia, ja, optypea, b, ib, jb, optypeb, beta, c, ic, jc, _state);
        ablas_rmatrixgemmrec(m, n, s2, alpha, a, ia+s1, ja, optypea, b, ib, jb+s1, optypeb, 1.0, c, ic, jc, _state);
    }
}
#endif
#if defined(AE_COMPILE_SPARSE) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
This function creates sparse matrix in a Hash-Table format.

This function creates Hast-Table matrix, which can be  converted  to  CRS
format after its initialization is over. Typical  usage  scenario  for  a
sparse matrix is:
1. creation in a Hash-Table format
2. insertion of the matrix elements
3. conversion to the CRS representation
4. matrix is passed to some linear algebra algorithm

Some  information  about  different matrix formats can be found below, in
the "NOTES" section.

INPUT PARAMETERS
    M           -   number of rows in a matrix, M>=1
    N           -   number of columns in a matrix, N>=1
    K           -   K>=0, expected number of non-zero elements in a matrix.
                    K can be inexact approximation, can be less than actual
                    number  of  elements  (table will grow when needed) or 
                    even zero).
                    It is important to understand that although hash-table
                    may grow automatically, it is better to  provide  good
                    estimate of data size.

OUTPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table representation.
                    All elements of the matrix are zero.

NOTE 1

Hash-tables use memory inefficiently, and they have to keep  some  amount
of the "spare memory" in order to have good performance. Hash  table  for
matrix with K non-zero elements will  need  C*K*(8+2*sizeof(int))  bytes,
where C is a small constant, about 1.5-2 in magnitude.

CRS storage, from the other side, is  more  memory-efficient,  and  needs
just K*(8+sizeof(int))+M*sizeof(int) bytes, where M is a number  of  rows
in a matrix.

When you convert from the Hash-Table to CRS  representation, all unneeded
memory will be freed.

NOTE 2

Comments of SparseMatrix structure outline  information  about  different
sparse storage formats. We recommend you to read them before starting  to
use ALGLIB sparse matrices.

NOTE 3

This function completely  overwrites S with new sparse matrix. Previously
allocated storage is NOT reused. If you  want  to reuse already allocated
memory, call SparseCreateBuf function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
void sparsecreate(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     sparsematrix* s,
     ae_state *_state)
{

    _sparsematrix_clear(s);

    sparsecreatebuf(m, n, k, s, _state);
}
/*************************************************************************
This version of SparseCreate function creates sparse matrix in Hash-Table
format, reusing previously allocated storage as much  as  possible.  Read
comments for SparseCreate() for more information.

INPUT PARAMETERS
    M           -   number of rows in a matrix, M>=1
    N           -   number of columns in a matrix, N>=1
    K           -   K>=0, expected number of non-zero elements in a matrix.
                    K can be inexact approximation, can be less than actual
                    number  of  elements  (table will grow when needed) or 
                    even zero).
                    It is important to understand that although hash-table
                    may grow automatically, it is better to  provide  good
                    estimate of data size.
    S           -   SparseMatrix structure which MAY contain some  already
                    allocated storage.

OUTPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table representation.
                    All elements of the matrix are zero.
                    Previously allocated storage is reused, if  its  size
                    is compatible with expected number of non-zeros K.

  -- ALGLIB PROJECT --
     Copyright 14.01.2014 by Bochkanov Sergey
*************************************************************************/
void sparsecreatebuf(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     sparsematrix* s,
     ae_state *_state)
{
    ae_int_t i;


    ae_assert(m>0, "SparseCreateBuf: M<=0", _state);
    ae_assert(n>0, "SparseCreateBuf: N<=0", _state);
    ae_assert(k>=0, "SparseCreateBuf: K<0", _state);
    
    /*
     * Hash-table size is max(existing_size,requested_size)
     *
     * NOTE: it is important to use ALL available memory for hash table
     *       because it is impossible to efficiently reallocate table
     *       without temporary storage. So, if we want table with up to
     *       1.000.000 elements, we have to create such table from the
     *       very beginning. Otherwise, the very idea of memory reuse
     *       will be compromised.
     */
    s->tablesize = ae_round(k/sparse_desiredloadfactor+sparse_additional, _state);
    rvectorsetlengthatleast(&s->vals, s->tablesize, _state);
    s->tablesize = s->vals.cnt;
    
    /*
     * Initialize other fields
     */
    s->matrixtype = 0;
    s->m = m;
    s->n = n;
    s->nfree = s->tablesize;
    ivectorsetlengthatleast(&s->idx, 2*s->tablesize, _state);
    for(i=0; i<=s->tablesize-1; i++)
    {
        s->idx.ptr.p_int[2*i] = -1;
    }
}



/*************************************************************************
This function creates sparse matrix in  a  SKS  format  (skyline  storage
format). Unlike more general  sparsecreatesks(),  this  function  creates
sparse matrix with constant bandwidth.

You may want to use this function instead of sparsecreatesks() when  your
matrix has  constant  or  nearly-constant  bandwidth,  and  you  want  to
simplify source code.

INPUT PARAMETERS
    M, N        -   number of rows(M) and columns (N) in a matrix:
                    * M=N (as for now, ALGLIB supports only square SKS)
                    * N>=1
                    * M>=1
    BW          -   matrix bandwidth, BW>=0

OUTPUT PARAMETERS
    S           -   sparse M*N matrix in SKS representation.
                    All elements are filled by zeros.
                    You may use sparseset() to  change  their values.
                    
NOTE: this function completely  overwrites  S  with  new  sparse  matrix.
      Previously allocated storage is NOT reused. If you  want  to  reuse
      already allocated memory, call sparsecreatesksbandbuf function.

  -- ALGLIB PROJECT --
     Copyright 25.12.2017 by Bochkanov Sergey
*************************************************************************/
void sparsecreatesksband(ae_int_t m,
     ae_int_t n,
     ae_int_t bw,
     sparsematrix* s,
     ae_state *_state)
{

    _sparsematrix_clear(s);

    ae_assert(m>0, "SparseCreateSKSBand: M<=0", _state);
    ae_assert(n>0, "SparseCreateSKSBand: N<=0", _state);
    ae_assert(bw>=0, "SparseCreateSKSBand: BW<0", _state);
    ae_assert(m==n, "SparseCreateSKSBand: M!=N", _state);
    sparsecreatesksbandbuf(m, n, bw, s, _state);
}
/*************************************************************************
This is "buffered" version  of  sparsecreatesksband() which reuses memory
previously allocated in S (of course, memory is reallocated if needed).

You may want to use this function instead  of  sparsecreatesksbuf()  when
your matrix has  constant or nearly-constant  bandwidth,  and you want to
simplify source code.

INPUT PARAMETERS
    M, N        -   number of rows(M) and columns (N) in a matrix:
                    * M=N (as for now, ALGLIB supports only square SKS)
                    * N>=1
                    * M>=1
    BW          -   bandwidth, BW>=0

OUTPUT PARAMETERS
    S           -   sparse M*N matrix in SKS representation.
                    All elements are filled by zeros.
                    You may use sparseset() to change their values.

  -- ALGLIB PROJECT --
     Copyright 13.01.2014 by Bochkanov Sergey
*************************************************************************/
void sparsecreatesksbandbuf(ae_int_t m,
     ae_int_t n,
     ae_int_t bw,
     sparsematrix* s,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t minmn;
    ae_int_t nz;
    ae_int_t mxd;
    ae_int_t mxu;
    ae_int_t dui;


    ae_assert(m>0, "SparseCreateSKSBandBuf: M<=0", _state);
    ae_assert(n>0, "SparseCreateSKSBandBuf: N<=0", _state);
    ae_assert(m==n, "SparseCreateSKSBandBuf: M!=N", _state);
    ae_assert(bw>=0, "SparseCreateSKSBandBuf: BW<0", _state);
    minmn = ae_minint(m, n, _state);
    s->matrixtype = 2;
    s->ninitialized = 0;
    s->m = m;
    s->n = n;
    ivectorsetlengthatleast(&s->ridx, minmn+1, _state);
    s->ridx.ptr.p_int[0] = 0;
    nz = 0;
    for(i=0; i<=minmn-1; i++)
    {
        dui = ae_minint(i, bw, _state);
        nz = nz+1+2*dui;
        s->ridx.ptr.p_int[i+1] = s->ridx.ptr.p_int[i]+1+2*dui;
    }
    rvectorsetlengthatleast(&s->vals, nz, _state);
    for(i=0; i<=nz-1; i++)
    {
        s->vals.ptr.p_double[i] = 0.0;
    }
    ivectorsetlengthatleast(&s->didx, m+1, _state);
    mxd = 0;
    for(i=0; i<=m-1; i++)
    {
        dui = ae_minint(i, bw, _state);
        s->didx.ptr.p_int[i] = dui;
        mxd = ae_maxint(mxd, dui, _state);
    }
    s->didx.ptr.p_int[m] = mxd;
    ivectorsetlengthatleast(&s->uidx, n+1, _state);
    mxu = 0;
    for(i=0; i<=n-1; i++)
    {
        dui = ae_minint(i, bw, _state);
        s->uidx.ptr.p_int[i] = dui;
        mxu = ae_maxint(mxu, dui, _state);
    }
    s->uidx.ptr.p_int[n] = mxu;
}
/*************************************************************************
This function modifies S[i,j] - element of the sparse matrix.

For Hash-based storage format:
* this function can be called at any moment - during matrix initialization
  or later
* new value can be zero or non-zero.  In case new value of S[i,j] is zero,
  this element is deleted from the table.
* this  function  has  no  effect when called with zero V for non-existent
  element.

For CRS-bases storage format:
* this function can be called ONLY DURING MATRIX INITIALIZATION
* zero values are stored in the matrix similarly to non-zero ones
* elements must be initialized in correct order -  from top row to bottom,
  within row - from left to right.
  
For SKS storage:
* this function can be called at any moment - during matrix initialization
  or later
* zero values are stored in the matrix similarly to non-zero ones
* this function CAN NOT be called for non-existent (outside  of  the  band
  specified during SKS matrix creation) elements. Say, if you created  SKS
  matrix  with  bandwidth=2  and  tried to call sparseset(s,0,10,VAL),  an
  exception will be generated.

INPUT PARAMETERS
    S           -   sparse M*N matrix in Hash-Table, SKS or CRS format.
    I           -   row index of the element to modify, 0<=I<M
    J           -   column index of the element to modify, 0<=J<N
    V           -   value to set, must be finite number, can be zero

OUTPUT PARAMETERS
    S           -   modified matrix

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
void sparseset(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     double v,
     ae_state *_state)
{
    ae_int_t hashcode;
    ae_int_t tcode;
    ae_int_t k;
    ae_bool b;


    ae_assert((s->matrixtype==0||s->matrixtype==1)||s->matrixtype==2, "SparseSet: unsupported matrix storage format", _state);
    ae_assert(i>=0, "SparseSet: I<0", _state);
    ae_assert(i<s->m, "SparseSet: I>=M", _state);
    ae_assert(j>=0, "SparseSet: J<0", _state);
    ae_assert(j<s->n, "SparseSet: J>=N", _state);
    ae_assert(ae_isfinite(v, _state), "SparseSet: V is not finite number", _state);
    
    /*
     * Hash-table matrix
     */
    if( s->matrixtype==0 )
    {
        tcode = -1;
        k = s->tablesize;
        if( ae_fp_greater_eq((1-sparse_maxloadfactor)*k,(double)(s->nfree)) )
        {
            sparseresizematrix(s, _state);
            k = s->tablesize;
        }
        hashcode = sparse_hash(i, j, k, _state);
        for(;;)
        {
            if( s->idx.ptr.p_int[2*hashcode]==-1 )
            {
                if( ae_fp_neq(v,(double)(0)) )
                {
                    if( tcode!=-1 )
                    {
                        hashcode = tcode;
                    }
                    s->vals.ptr.p_double[hashcode] = v;
                    s->idx.ptr.p_int[2*hashcode] = i;
                    s->idx.ptr.p_int[2*hashcode+1] = j;
                    if( tcode==-1 )
                    {
                        s->nfree = s->nfree-1;
                    }
                }
                return;
            }
            else
            {
                if( s->idx.ptr.p_int[2*hashcode]==i&&s->idx.ptr.p_int[2*hashcode+1]==j )
                {
                    if( ae_fp_eq(v,(double)(0)) )
                    {
                        s->idx.ptr.p_int[2*hashcode] = -2;
                    }
                    else
                    {
                        s->vals.ptr.p_double[hashcode] = v;
                    }
                    return;
                }
                if( tcode==-1&&s->idx.ptr.p_int[2*hashcode]==-2 )
                {
                    tcode = hashcode;
                }
                
                /*
                 * Next step
                 */
                hashcode = (hashcode+1)%k;
            }
        }
    }
    
    /*
     * CRS matrix
     */
    if( s->matrixtype==1 )
    {
        ae_assert(s->ridx.ptr.p_int[i]<=s->ninitialized, "SparseSet: too few initialized elements at some row (you have promised more when called SparceCreateCRS)", _state);
        ae_assert(s->ridx.ptr.p_int[i+1]>s->ninitialized, "SparseSet: too many initialized elements at some row (you have promised less when called SparceCreateCRS)", _state);
        ae_assert(s->ninitialized==s->ridx.ptr.p_int[i]||s->idx.ptr.p_int[s->ninitialized-1]<j, "SparseSet: incorrect column order (you must fill every row from left to right)", _state);
        s->vals.ptr.p_double[s->ninitialized] = v;
        s->idx.ptr.p_int[s->ninitialized] = j;
        s->ninitialized = s->ninitialized+1;
        
        /*
         * If matrix has been created then
         * initiale 'S.UIdx' and 'S.DIdx'
         */
        if( s->ninitialized==s->ridx.ptr.p_int[s->m] )
        {
            sparseinitduidx(s, _state);
        }
        return;
    }
    
    /*
     * SKS matrix
     */
    if( s->matrixtype==2 )
    {
        b = sparserewriteexisting(s, i, j, v, _state);
        ae_assert(b, "SparseSet: an attempt to initialize out-of-band element of the SKS matrix", _state);
        return;
    }
}
/*************************************************************************
This function returns S[i,j] - element of the sparse matrix.  Matrix  can
be in any mode (Hash-Table, CRS, SKS), but this function is less efficient
for CRS matrices. Hash-Table and SKS matrices can find  element  in  O(1)
time, while  CRS  matrices need O(log(RS)) time, where RS is an number of
non-zero elements in a row.

INPUT PARAMETERS
    S           -   sparse M*N matrix
    I           -   row index of the element to modify, 0<=I<M
    J           -   column index of the element to modify, 0<=J<N

RESULT
    value of S[I,J] or zero (in case no element with such index is found)

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
double sparseget(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     ae_state *_state)
{
    ae_int_t hashcode;
    ae_int_t k;
    ae_int_t k0;
    ae_int_t k1;
    double result;


    ae_assert(i>=0, "SparseGet: I<0", _state);
    ae_assert(i<s->m, "SparseGet: I>=M", _state);
    ae_assert(j>=0, "SparseGet: J<0", _state);
    ae_assert(j<s->n, "SparseGet: J>=N", _state);
    result = 0.0;
    if( s->matrixtype==0 )
    {
        
        /*
         * Hash-based storage
         */
        result = (double)(0);
        k = s->tablesize;
        hashcode = sparse_hash(i, j, k, _state);
        for(;;)
        {
            if( s->idx.ptr.p_int[2*hashcode]==-1 )
            {
                return result;
            }
            if( s->idx.ptr.p_int[2*hashcode]==i&&s->idx.ptr.p_int[2*hashcode+1]==j )
            {
                result = s->vals.ptr.p_double[hashcode];
                return result;
            }
            hashcode = (hashcode+1)%k;
        }
    }
    if( s->matrixtype==1 )
    {
        
        /*
         * CRS
         */
        ae_assert(s->ninitialized==s->ridx.ptr.p_int[s->m], "SparseGet: some rows/elements of the CRS matrix were not initialized (you must initialize everything you promised to SparseCreateCRS)", _state);
        k0 = s->ridx.ptr.p_int[i];
        k1 = s->ridx.ptr.p_int[i+1]-1;
        result = (double)(0);
        while(k0<=k1)
        {
            k = (k0+k1)/2;
            if( s->idx.ptr.p_int[k]==j )
            {
                result = s->vals.ptr.p_double[k];
                return result;
            }
            if( s->idx.ptr.p_int[k]<j )
            {
                k0 = k+1;
            }
            else
            {
                k1 = k-1;
            }
        }
        return result;
    }
    if( s->matrixtype==2 )
    {
        
        /*
         * SKS
         */
        ae_assert(s->m==s->n, "SparseGet: non-square SKS matrix not supported", _state);
        result = (double)(0);
        if( i==j )
        {
            
            /*
             * Return diagonal element
             */
            result = s->vals.ptr.p_double[s->ridx.ptr.p_int[i]+s->didx.ptr.p_int[i]];
            return result;
        }
        if( j<i )
        {
            
            /*
             * Return subdiagonal element at I-th "skyline block"
             */
            k = s->didx.ptr.p_int[i];
            if( i-j<=k )
            {
                result = s->vals.ptr.p_double[s->ridx.ptr.p_int[i]+k+j-i];
            }
        }
        else
        {
            
            /*
             * Return superdiagonal element at J-th "skyline block"
             */
            k = s->uidx.ptr.p_int[j];
            if( j-i<=k )
            {
                result = s->vals.ptr.p_double[s->ridx.ptr.p_int[j+1]-(j-i)];
            }
            return result;
        }
        return result;
    }
    ae_assert(ae_false, "SparseGet: unexpected matrix type", _state);
    return result;
}
/*************************************************************************
This function calculates matrix-vector product  S*x.  Matrix  S  must  be
stored in CRS or SKS format (exception will be thrown otherwise).

INPUT PARAMETERS
    S           -   sparse M*N matrix in CRS or SKS format.
    X           -   array[N], input vector. For  performance  reasons  we 
                    make only quick checks - we check that array size  is
                    at least N, but we do not check for NAN's or INF's.
    Y           -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.
    
OUTPUT PARAMETERS
    Y           -   array[M], S*x
    
NOTE: this function throws exception when called for non-CRS/SKS  matrix.
You must convert your matrix with SparseConvertToCRS/SKS()  before  using
this function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
void sparsemv(sparsematrix* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state)
{
    double tval;
    double v;
    double vv;
    ae_int_t i;
    ae_int_t j;
    ae_int_t lt;
    ae_int_t rt;
    ae_int_t lt1;
    ae_int_t rt1;
    ae_int_t n;
    ae_int_t m;
    ae_int_t d;
    ae_int_t u;
    ae_int_t ri;
    ae_int_t ri1;


    ae_assert(x->cnt>=s->n, "SparseMV: length(X)<N", _state);
    ae_assert(s->matrixtype==1||s->matrixtype==2, "SparseMV: incorrect matrix type (convert your matrix to CRS/SKS)", _state);
    rvectorsetlengthatleast(y, s->m, _state);
    n = s->n;
    m = s->m;
    if( s->matrixtype==1 )
    {
        
        /*
         * CRS format.
         * Perform integrity check.
         */
        ae_assert(s->ninitialized==s->ridx.ptr.p_int[s->m], "SparseMV: some rows/elements of the CRS matrix were not initialized (you must initialize everything you promised to SparseCreateCRS)", _state);
        
        /*
         * Try vendor kernels
         */
        if( sparsegemvcrsmkl(0, s->m, s->n, 1.0, &s->vals, &s->idx, &s->ridx, x, 0, 0.0, y, 0, _state) )
        {
            return;
        }
        
        /*
         * Our own implementation
         */
        for(i=0; i<=m-1; i++)
        {
            tval = (double)(0);
            lt = s->ridx.ptr.p_int[i];
            rt = s->ridx.ptr.p_int[i+1]-1;
            for(j=lt; j<=rt; j++)
            {
                tval = tval+x->ptr.p_double[s->idx.ptr.p_int[j]]*s->vals.ptr.p_double[j];
            }
            y->ptr.p_double[i] = tval;
        }
        return;
    }
    if( s->matrixtype==2 )
    {
        
        /*
         * SKS format
         */
        ae_assert(s->m==s->n, "SparseMV: non-square SKS matrices are not supported", _state);
        for(i=0; i<=n-1; i++)
        {
            ri = s->ridx.ptr.p_int[i];
            ri1 = s->ridx.ptr.p_int[i+1];
            d = s->didx.ptr.p_int[i];
            u = s->uidx.ptr.p_int[i];
            v = s->vals.ptr.p_double[ri+d]*x->ptr.p_double[i];
            if( d>0 )
            {
                lt = ri;
                rt = ri+d-1;
                lt1 = i-d;
                rt1 = i-1;
                vv = ae_v_dotproduct(&s->vals.ptr.p_double[lt], 1, &x->ptr.p_double[lt1], 1, ae_v_len(lt,rt));
                v = v+vv;
            }
            y->ptr.p_double[i] = v;
            if( u>0 )
            {
                lt = ri1-u;
                rt = ri1-1;
                lt1 = i-u;
                rt1 = i-1;
                v = x->ptr.p_double[i];
                ae_v_addd(&y->ptr.p_double[lt1], 1, &s->vals.ptr.p_double[lt], 1, ae_v_len(lt1,rt1), v);
            }
        }
        return;
    }
}
/*************************************************************************
This function calculates matrix-vector product  S^T*x. Matrix S  must  be
stored in CRS or SKS format (exception will be thrown otherwise).

INPUT PARAMETERS
    S           -   sparse M*N matrix in CRS or SKS format.
    X           -   array[M], input vector. For  performance  reasons  we 
                    make only quick checks - we check that array size  is
                    at least M, but we do not check for NAN's or INF's.
    Y           -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.
    
OUTPUT PARAMETERS
    Y           -   array[N], S^T*x
    
NOTE: this function throws exception when called for non-CRS/SKS  matrix.
You must convert your matrix with SparseConvertToCRS/SKS()  before  using
this function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
void sparsemtv(sparsematrix* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_int_t lt;
    ae_int_t rt;
    ae_int_t ct;
    ae_int_t lt1;
    ae_int_t rt1;
    double v;
    double vv;
    ae_int_t n;
    ae_int_t m;
    ae_int_t ri;
    ae_int_t ri1;
    ae_int_t d;
    ae_int_t u;


    ae_assert(s->matrixtype==1||s->matrixtype==2, "SparseMTV: incorrect matrix type (convert your matrix to CRS/SKS)", _state);
    ae_assert(x->cnt>=s->m, "SparseMTV: Length(X)<M", _state);
    n = s->n;
    m = s->m;
    rvectorsetlengthatleast(y, n, _state);
    for(i=0; i<=n-1; i++)
    {
        y->ptr.p_double[i] = (double)(0);
    }
    if( s->matrixtype==1 )
    {
        
        /*
         * CRS format
         * Perform integrity check.
         */
        ae_assert(s->ninitialized==s->ridx.ptr.p_int[m], "SparseMTV: some rows/elements of the CRS matrix were not initialized (you must initialize everything you promised to SparseCreateCRS)", _state);
        
        /*
         * Try vendor kernels
         */
        if( sparsegemvcrsmkl(1, s->m, s->n, 1.0, &s->vals, &s->idx, &s->ridx, x, 0, 0.0, y, 0, _state) )
        {
            return;
        }
        
        /*
         * Our own implementation
         */
        for(i=0; i<=m-1; i++)
        {
            lt = s->ridx.ptr.p_int[i];
            rt = s->ridx.ptr.p_int[i+1];
            v = x->ptr.p_double[i];
            for(j=lt; j<=rt-1; j++)
            {
                ct = s->idx.ptr.p_int[j];
                y->ptr.p_double[ct] = y->ptr.p_double[ct]+v*s->vals.ptr.p_double[j];
            }
        }
        return;
    }
    if( s->matrixtype==2 )
    {
        
        /*
         * SKS format
         */
        ae_assert(s->m==s->n, "SparseMV: non-square SKS matrices are not supported", _state);
        for(i=0; i<=n-1; i++)
        {
            ri = s->ridx.ptr.p_int[i];
            ri1 = s->ridx.ptr.p_int[i+1];
            d = s->didx.ptr.p_int[i];
            u = s->uidx.ptr.p_int[i];
            if( d>0 )
            {
                lt = ri;
                rt = ri+d-1;
                lt1 = i-d;
                rt1 = i-1;
                v = x->ptr.p_double[i];
                ae_v_addd(&y->ptr.p_double[lt1], 1, &s->vals.ptr.p_double[lt], 1, ae_v_len(lt1,rt1), v);
            }
            v = s->vals.ptr.p_double[ri+d]*x->ptr.p_double[i];
            if( u>0 )
            {
                lt = ri1-u;
                rt = ri1-1;
                lt1 = i-u;
                rt1 = i-1;
                vv = ae_v_dotproduct(&s->vals.ptr.p_double[lt], 1, &x->ptr.p_double[lt1], 1, ae_v_len(lt,rt));
                v = v+vv;
            }
            y->ptr.p_double[i] = v;
        }
        return;
    }
}



/*************************************************************************
This function simultaneously calculates two matrix-vector products:
    S*x and S^T*x.
S must be square (non-rectangular) matrix stored in  CRS  or  SKS  format
(exception will be thrown otherwise).

INPUT PARAMETERS
    S           -   sparse N*N matrix in CRS or SKS format.
    X           -   array[N], input vector. For  performance  reasons  we 
                    make only quick checks - we check that array size  is
                    at least N, but we do not check for NAN's or INF's.
    Y0          -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.
    Y1          -   output buffer, possibly preallocated. In case  buffer
                    size is too small to store  result,  this  buffer  is
                    automatically resized.
    
OUTPUT PARAMETERS
    Y0          -   array[N], S*x
    Y1          -   array[N], S^T*x
    
NOTE: this function throws exception when called for non-CRS/SKS  matrix.
You must convert your matrix with SparseConvertToCRS/SKS()  before  using
this function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
void sparsemv2(sparsematrix* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y0,
     /* Real    */ ae_vector* y1,
     ae_state *_state)
{
    ae_int_t l;
    double tval;
    ae_int_t i;
    ae_int_t j;
    double vx;
    double vs;
    double v;
    double vv;
    double vd0;
    double vd1;
    ae_int_t vi;
    ae_int_t j0;
    ae_int_t j1;
    ae_int_t n;
    ae_int_t ri;
    ae_int_t ri1;
    ae_int_t d;
    ae_int_t u;
    ae_int_t lt;
    ae_int_t rt;
    ae_int_t lt1;
    ae_int_t rt1;


    ae_assert(s->matrixtype==1||s->matrixtype==2, "SparseMV2: incorrect matrix type (convert your matrix to CRS/SKS)", _state);
    ae_assert(s->m==s->n, "SparseMV2: matrix is non-square", _state);
    l = x->cnt;
    ae_assert(l>=s->n, "SparseMV2: Length(X)<N", _state);
    n = s->n;
    rvectorsetlengthatleast(y0, l, _state);
    rvectorsetlengthatleast(y1, l, _state);
    for(i=0; i<=n-1; i++)
    {
        y0->ptr.p_double[i] = (double)(0);
        y1->ptr.p_double[i] = (double)(0);
    }
    if( s->matrixtype==1 )
    {
        
        /*
         * CRS format
         */
        ae_assert(s->ninitialized==s->ridx.ptr.p_int[s->m], "SparseMV2: some rows/elements of the CRS matrix were not initialized (you must initialize everything you promised to SparseCreateCRS)", _state);
        for(i=0; i<=s->m-1; i++)
        {
            tval = (double)(0);
            vx = x->ptr.p_double[i];
            j0 = s->ridx.ptr.p_int[i];
            j1 = s->ridx.ptr.p_int[i+1]-1;
            for(j=j0; j<=j1; j++)
            {
                vi = s->idx.ptr.p_int[j];
                vs = s->vals.ptr.p_double[j];
                tval = tval+x->ptr.p_double[vi]*vs;
                y1->ptr.p_double[vi] = y1->ptr.p_double[vi]+vx*vs;
            }
            y0->ptr.p_double[i] = tval;
        }
        return;
    }
    if( s->matrixtype==2 )
    {
        
        /*
         * SKS format
         */
        for(i=0; i<=n-1; i++)
        {
            ri = s->ridx.ptr.p_int[i];
            ri1 = s->ridx.ptr.p_int[i+1];
            d = s->didx.ptr.p_int[i];
            u = s->uidx.ptr.p_int[i];
            vd0 = s->vals.ptr.p_double[ri+d]*x->ptr.p_double[i];
            vd1 = vd0;
            if( d>0 )
            {
                lt = ri;
                rt = ri+d-1;
                lt1 = i-d;
                rt1 = i-1;
                v = x->ptr.p_double[i];
                ae_v_addd(&y1->ptr.p_double[lt1], 1, &s->vals.ptr.p_double[lt], 1, ae_v_len(lt1,rt1), v);
                vv = ae_v_dotproduct(&s->vals.ptr.p_double[lt], 1, &x->ptr.p_double[lt1], 1, ae_v_len(lt,rt));
                vd0 = vd0+vv;
            }
            if( u>0 )
            {
                lt = ri1-u;
                rt = ri1-1;
                lt1 = i-u;
                rt1 = i-1;
                v = x->ptr.p_double[i];
                ae_v_addd(&y0->ptr.p_double[lt1], 1, &s->vals.ptr.p_double[lt], 1, ae_v_len(lt1,rt1), v);
                vv = ae_v_dotproduct(&s->vals.ptr.p_double[lt], 1, &x->ptr.p_double[lt1], 1, ae_v_len(lt,rt));
                vd1 = vd1+vv;
            }
            y0->ptr.p_double[i] = vd0;
            y1->ptr.p_double[i] = vd1;
        }
        return;
    }
}

/*************************************************************************
This function solves linear system op(S)*y=x  where  x  is  vector,  S  is
symmetric  triangular  matrix,  op(S)  is  transposition  or no operation.
Matrix S must be stored in CRS or SKS format  (exception  will  be  thrown
otherwise).

INPUT PARAMETERS
    S           -   sparse square matrix in CRS or SKS format.
    IsUpper     -   whether upper or lower triangle of S is used:
                    * if upper triangle is given,  only   S[i,j] for  j>=i
                      are used, and lower triangle is  ignored (it can  be
                      empty - these elements are not referenced at all).
                    * if lower triangle is given,  only   S[i,j] for  j<=i
                      are used, and upper triangle is ignored.
    IsUnit      -   unit or non-unit diagonal:
                    * if True, diagonal elements of triangular matrix  are
                      considered equal to 1.0. Actual elements  stored  in
                      S are not referenced at all.
                    * if False, diagonal stored in S is used. It  is  your
                      responsibility  to  make  sure  that   diagonal   is
                      non-zero.
    OpType      -   operation type:
                    * if 0, S*x is calculated
                    * if 1, (S^T)*x is calculated (transposition)
    X           -   array[N] which stores input  vector.  For  performance
                    reasons we make only quick  checks  -  we  check  that
                    array  size  is  at  least  N, but we do not check for
                    NAN's or INF's.
    
OUTPUT PARAMETERS
    X           -   array[N], inv(op(S))*x
    
NOTE: this function throws exception when called for  non-CRS/SKS  matrix.
      You must convert your matrix  with  SparseConvertToCRS/SKS()  before
      using this function.

NOTE: no assertion or tests are done during algorithm  operation.   It  is
      your responsibility to provide invertible matrix to algorithm.

  -- ALGLIB PROJECT --
     Copyright 20.01.2014 by Bochkanov Sergey
*************************************************************************/
void sparsetrsv(sparsematrix* s,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{
    ae_int_t n;
    ae_int_t fst;
    ae_int_t lst;
    ae_int_t stp;
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    double v;
    double vd;
    double v0;
    ae_int_t j0;
    ae_int_t j1;
    ae_int_t ri;
    ae_int_t ri1;
    ae_int_t d;
    ae_int_t u;
    ae_int_t lt;
    ae_int_t lt1;


    ae_assert(s->matrixtype==1||s->matrixtype==2, "SparseTRSV: incorrect matrix type (convert your matrix to CRS/SKS)", _state);
    ae_assert(optype==0||optype==1, "SparseTRSV: incorrect operation type (must be 0 or 1)", _state);
    ae_assert(x->cnt>=s->n, "SparseTRSV: Length(X)<N", _state);
    ae_assert(s->m==s->n, "SparseTRSV: matrix is non-square", _state);
    n = s->n;
    if( s->matrixtype==1 )
    {
        
        /*
         * CRS format.
         *
         * Several branches for different combinations of IsUpper and OpType
         */
        ae_assert(s->ninitialized==s->ridx.ptr.p_int[s->m], "SparseTRSV: some rows/elements of the CRS matrix were not initialized (you must initialize everything you promised to SparseCreateCRS)", _state);
        if( optype==0 )
        {
            
            /*
             * No transposition.
             *
             * S*x=y with upper or lower triangular S.
             */
            v0 = (double)(0);
            if( isupper )
            {
                fst = n-1;
                lst = 0;
                stp = -1;
            }
            else
            {
                fst = 0;
                lst = n-1;
                stp = 1;
            }
            i = fst;
            while((stp>0&&i<=lst)||(stp<0&&i>=lst))
            {
                
                /*
                 * Select range of indexes to process
                 */
                if( isupper )
                {
                    j0 = s->uidx.ptr.p_int[i];
                    j1 = s->ridx.ptr.p_int[i+1]-1;
                }
                else
                {
                    j0 = s->ridx.ptr.p_int[i];
                    j1 = s->didx.ptr.p_int[i]-1;
                }
                
                /*
                 * Calculate X[I]
                 */
                v = 0.0;
                for(j=j0; j<=j1; j++)
                {
                    v = v+s->vals.ptr.p_double[j]*x->ptr.p_double[s->idx.ptr.p_int[j]];
                }
                if( !isunit )
                {
                    if( s->didx.ptr.p_int[i]==s->uidx.ptr.p_int[i] )
                    {
                        vd = (double)(0);
                    }
                    else
                    {
                        vd = s->vals.ptr.p_double[s->didx.ptr.p_int[i]];
                    }
                }
                else
                {
                    vd = 1.0;
                }
                v = (x->ptr.p_double[i]-v)/vd;
                x->ptr.p_double[i] = v;
                v0 = 0.25*v0+v;
                
                /*
                 * Next I
                 */
                i = i+stp;
            }
            ae_assert(ae_isfinite(v0, _state), "SparseTRSV: overflow or division by exact zero", _state);
            return;
        }
        if( optype==1 )
        {
            
            /*
             * Transposition.
             *
             * (S^T)*x=y with upper or lower triangular S.
             */
            if( isupper )
            {
                fst = 0;
                lst = n-1;
                stp = 1;
            }
            else
            {
                fst = n-1;
                lst = 0;
                stp = -1;
            }
            i = fst;
            v0 = (double)(0);
            while((stp>0&&i<=lst)||(stp<0&&i>=lst))
            {
                v = x->ptr.p_double[i];
                if( v!=0.0 )
                {
                    
                    /*
                     * X[i] already stores A[i,i]*Y[i], the only thing left
                     * is to divide by diagonal element.
                     */
                    if( !isunit )
                    {
                        if( s->didx.ptr.p_int[i]==s->uidx.ptr.p_int[i] )
                        {
                            vd = (double)(0);
                        }
                        else
                        {
                            vd = s->vals.ptr.p_double[s->didx.ptr.p_int[i]];
                        }
                    }
                    else
                    {
                        vd = 1.0;
                    }
                    v = v/vd;
                    x->ptr.p_double[i] = v;
                    v0 = 0.25*v0+v;
                    
                    /*
                     * For upper triangular case:
                     *     subtract X[i]*Ai from X[i+1:N-1]
                     *
                     * For lower triangular case:
                     *     subtract X[i]*Ai from X[0:i-1]
                     *
                     * (here Ai is I-th row of original, untransposed A).
                     */
                    if( isupper )
                    {
                        j0 = s->uidx.ptr.p_int[i];
                        j1 = s->ridx.ptr.p_int[i+1]-1;
                    }
                    else
                    {
                        j0 = s->ridx.ptr.p_int[i];
                        j1 = s->didx.ptr.p_int[i]-1;
                    }
                    for(j=j0; j<=j1; j++)
                    {
                        k = s->idx.ptr.p_int[j];
                        x->ptr.p_double[k] = x->ptr.p_double[k]-s->vals.ptr.p_double[j]*v;
                    }
                }
                
                /*
                 * Next I
                 */
                i = i+stp;
            }
            ae_assert(ae_isfinite(v0, _state), "SparseTRSV: overflow or division by exact zero", _state);
            return;
        }
        ae_assert(ae_false, "SparseTRSV: internal error", _state);
    }
    if( s->matrixtype==2 )
    {
        
        /*
         * SKS format
         */
        ae_assert(s->m==s->n, "SparseTRSV: non-square SKS matrices are not supported", _state);
        if( (optype==0&&!isupper)||(optype==1&&isupper) )
        {
            
            /*
             * Lower triangular op(S) (matrix itself can be upper triangular).
             */
            v0 = (double)(0);
            for(i=0; i<=n-1; i++)
            {
                
                /*
                 * Select range of indexes to process
                 */
                ri = s->ridx.ptr.p_int[i];
                ri1 = s->ridx.ptr.p_int[i+1];
                d = s->didx.ptr.p_int[i];
                u = s->uidx.ptr.p_int[i];
                if( isupper )
                {
                    lt = i-u;
                    lt1 = ri1-u;
                    k = u-1;
                }
                else
                {
                    lt = i-d;
                    lt1 = ri;
                    k = d-1;
                }
                
                /*
                 * Calculate X[I]
                 */
                v = 0.0;
                for(j=0; j<=k; j++)
                {
                    v = v+s->vals.ptr.p_double[lt1+j]*x->ptr.p_double[lt+j];
                }
                if( isunit )
                {
                    vd = (double)(1);
                }
                else
                {
                    vd = s->vals.ptr.p_double[ri+d];
                }
                v = (x->ptr.p_double[i]-v)/vd;
                x->ptr.p_double[i] = v;
                v0 = 0.25*v0+v;
            }
            ae_assert(ae_isfinite(v0, _state), "SparseTRSV: overflow or division by exact zero", _state);
            return;
        }
        if( (optype==1&&!isupper)||(optype==0&&isupper) )
        {
            
            /*
             * Upper triangular op(S) (matrix itself can be lower triangular).
             */
            v0 = (double)(0);
            for(i=n-1; i>=0; i--)
            {
                ri = s->ridx.ptr.p_int[i];
                ri1 = s->ridx.ptr.p_int[i+1];
                d = s->didx.ptr.p_int[i];
                u = s->uidx.ptr.p_int[i];
                
                /*
                 * X[i] already stores A[i,i]*Y[i], the only thing left
                 * is to divide by diagonal element.
                 */
                if( isunit )
                {
                    vd = (double)(1);
                }
                else
                {
                    vd = s->vals.ptr.p_double[ri+d];
                }
                v = x->ptr.p_double[i]/vd;
                x->ptr.p_double[i] = v;
                v0 = 0.25*v0+v;
                
                /*
                 * Subtract product of X[i] and I-th column of "effective" A from
                 * unprocessed variables.
                 */
                v = x->ptr.p_double[i];
                if( isupper )
                {
                    lt = i-u;
                    lt1 = ri1-u;
                    k = u-1;
                }
                else
                {
                    lt = i-d;
                    lt1 = ri;
                    k = d-1;
                }
                for(j=0; j<=k; j++)
                {
                    x->ptr.p_double[lt+j] = x->ptr.p_double[lt+j]-v*s->vals.ptr.p_double[lt1+j];
                }
            }
            ae_assert(ae_isfinite(v0, _state), "SparseTRSV: overflow or division by exact zero", _state);
            return;
        }
        ae_assert(ae_false, "SparseTRSV: internal error", _state);
    }
    ae_assert(ae_false, "SparseTRSV: internal error", _state);
}
/*************************************************************************
This procedure resizes Hash-Table matrix. It can be called when you  have
deleted too many elements from the matrix, and you want to  free unneeded
memory.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
void sparseresizematrix(sparsematrix* s, ae_state *_state)
{
    ae_frame _frame_block;
    ae_int_t k;
    ae_int_t k1;
    ae_int_t i;
    ae_vector tvals;
    ae_vector tidx;

    ae_frame_make(_state, &_frame_block);
    memset(&tvals, 0, sizeof(tvals));
    memset(&tidx, 0, sizeof(tidx));
    ae_vector_init(&tvals, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tidx, 0, DT_INT, _state, ae_true);

    ae_assert(s->matrixtype==0, "SparseResizeMatrix: incorrect matrix type", _state);
    
    /*
     * Initialization for length and number of non-null elementd
     */
    k = s->tablesize;
    k1 = 0;
    
    /*
     * Calculating number of non-null elements
     */
    for(i=0; i<=k-1; i++)
    {
        if( s->idx.ptr.p_int[2*i]>=0 )
        {
            k1 = k1+1;
        }
    }
    
    /*
     * Initialization value for free space
     */
    s->tablesize = ae_round(k1/sparse_desiredloadfactor*sparse_growfactor+sparse_additional, _state);
    s->nfree = s->tablesize-k1;
    ae_vector_set_length(&tvals, s->tablesize, _state);
    ae_vector_set_length(&tidx, 2*s->tablesize, _state);
    ae_swap_vectors(&s->vals, &tvals);
    ae_swap_vectors(&s->idx, &tidx);
    for(i=0; i<=s->tablesize-1; i++)
    {
        s->idx.ptr.p_int[2*i] = -1;
    }
    for(i=0; i<=k-1; i++)
    {
        if( tidx.ptr.p_int[2*i]>=0 )
        {
            sparseset(s, tidx.ptr.p_int[2*i], tidx.ptr.p_int[2*i+1], tvals.ptr.p_double[i], _state);
        }
    }
    ae_frame_leave(_state);
}


/*************************************************************************
Procedure for initialization 'S.DIdx' and 'S.UIdx'


  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
void sparseinitduidx(sparsematrix* s, ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    ae_int_t lt;
    ae_int_t rt;


    ae_assert(s->matrixtype==1, "SparseInitDUIdx: internal error, incorrect matrix type", _state);
    ivectorsetlengthatleast(&s->didx, s->m, _state);
    ivectorsetlengthatleast(&s->uidx, s->m, _state);
    for(i=0; i<=s->m-1; i++)
    {
        s->uidx.ptr.p_int[i] = -1;
        s->didx.ptr.p_int[i] = -1;
        lt = s->ridx.ptr.p_int[i];
        rt = s->ridx.ptr.p_int[i+1];
        for(j=lt; j<=rt-1; j++)
        {
            k = s->idx.ptr.p_int[j];
            if( k==i )
            {
                s->didx.ptr.p_int[i] = j;
            }
            else
            {
                if( k>i&&s->uidx.ptr.p_int[i]==-1 )
                {
                    s->uidx.ptr.p_int[i] = j;
                    break;
                }
            }
        }
        if( s->uidx.ptr.p_int[i]==-1 )
        {
            s->uidx.ptr.p_int[i] = s->ridx.ptr.p_int[i+1];
        }
        if( s->didx.ptr.p_int[i]==-1 )
        {
            s->didx.ptr.p_int[i] = s->uidx.ptr.p_int[i];
        }
    }
}
/*************************************************************************
This function rewrites existing (non-zero) element. It  returns  True   if
element  exists  or  False,  when  it  is  called for non-existing  (zero)
element.

This function works with any kind of the matrix.

The purpose of this function is to provide convenient thread-safe  way  to
modify  sparse  matrix.  Such  modification  (already  existing element is
rewritten) is guaranteed to be thread-safe without any synchronization, as
long as different threads modify different elements.

INPUT PARAMETERS
    S           -   sparse M*N matrix in any kind of representation
                    (Hash, SKS, CRS).
    I           -   row index of non-zero element to modify, 0<=I<M
    J           -   column index of non-zero element to modify, 0<=J<N
    V           -   value to rewrite, must be finite number

OUTPUT PARAMETERS
    S           -   modified matrix
RESULT
    True in case when element exists
    False in case when element doesn't exist or it is zero
    
  -- ALGLIB PROJECT --
     Copyright 14.03.2012 by Bochkanov Sergey
*************************************************************************/
ae_bool sparserewriteexisting(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     double v,
     ae_state *_state)
{
    ae_int_t hashcode;
    ae_int_t k;
    ae_int_t k0;
    ae_int_t k1;
    ae_bool result;


    ae_assert(0<=i&&i<s->m, "SparseRewriteExisting: invalid argument I(either I<0 or I>=S.M)", _state);
    ae_assert(0<=j&&j<s->n, "SparseRewriteExisting: invalid argument J(either J<0 or J>=S.N)", _state);
    ae_assert(ae_isfinite(v, _state), "SparseRewriteExisting: invalid argument V(either V is infinite or V is NaN)", _state);
    result = ae_false;
    
    /*
     * Hash-table matrix
     */
    if( s->matrixtype==0 )
    {
        k = s->tablesize;
        hashcode = sparse_hash(i, j, k, _state);
        for(;;)
        {
            if( s->idx.ptr.p_int[2*hashcode]==-1 )
            {
                return result;
            }
            if( s->idx.ptr.p_int[2*hashcode]==i&&s->idx.ptr.p_int[2*hashcode+1]==j )
            {
                s->vals.ptr.p_double[hashcode] = v;
                result = ae_true;
                return result;
            }
            hashcode = (hashcode+1)%k;
        }
    }
    
    /*
     * CRS matrix
     */
    if( s->matrixtype==1 )
    {
        ae_assert(s->ninitialized==s->ridx.ptr.p_int[s->m], "SparseRewriteExisting: some rows/elements of the CRS matrix were not initialized (you must initialize everything you promised to SparseCreateCRS)", _state);
        k0 = s->ridx.ptr.p_int[i];
        k1 = s->ridx.ptr.p_int[i+1]-1;
        while(k0<=k1)
        {
            k = (k0+k1)/2;
            if( s->idx.ptr.p_int[k]==j )
            {
                s->vals.ptr.p_double[k] = v;
                result = ae_true;
                return result;
            }
            if( s->idx.ptr.p_int[k]<j )
            {
                k0 = k+1;
            }
            else
            {
                k1 = k-1;
            }
        }
    }
    
    /*
     * SKS
     */
    if( s->matrixtype==2 )
    {
        ae_assert(s->m==s->n, "SparseRewriteExisting: non-square SKS matrix not supported", _state);
        if( i==j )
        {
            
            /*
             * Rewrite diagonal element
             */
            result = ae_true;
            s->vals.ptr.p_double[s->ridx.ptr.p_int[i]+s->didx.ptr.p_int[i]] = v;
            return result;
        }
        if( j<i )
        {
            
            /*
             * Return subdiagonal element at I-th "skyline block"
             */
            k = s->didx.ptr.p_int[i];
            if( i-j<=k )
            {
                s->vals.ptr.p_double[s->ridx.ptr.p_int[i]+k+j-i] = v;
                result = ae_true;
            }
        }
        else
        {
            
            /*
             * Return superdiagonal element at J-th "skyline block"
             */
            k = s->uidx.ptr.p_int[j];
            if( j-i<=k )
            {
                s->vals.ptr.p_double[s->ridx.ptr.p_int[j+1]-(j-i)] = v;
                result = ae_true;
            }
        }
        return result;
    }
    return result;
}
/*************************************************************************
This function returns I-th row of the sparse matrix IN COMPRESSED FORMAT -
only non-zero elements are returned (with their indexes). Matrix  must  be
stored in CRS or SKS format.

INPUT PARAMETERS:
    S           -   sparse M*N matrix in CRS format
    I           -   row index, 0<=I<M
    ColIdx      -   output buffer for column indexes, can be preallocated.
                    In case buffer size is too small to store I-th row, it
                    is automatically reallocated.
    Vals        -   output buffer for values, can be preallocated. In case
                    buffer size is too small to  store  I-th  row,  it  is
                    automatically reallocated.
 
OUTPUT PARAMETERS:
    ColIdx      -   column   indexes   of  non-zero  elements,  sorted  by
                    ascending. Symbolically non-zero elements are  counted
                    (i.e. if you allocated place for element, but  it  has
                    zero numerical value - it is counted).
    Vals        -   values. Vals[K] stores value of  matrix  element  with
                    indexes (I,ColIdx[K]). Symbolically non-zero  elements
                    are counted (i.e. if you allocated place for  element,
                    but it has zero numerical value - it is counted).
    NZCnt       -   number of symbolically non-zero elements per row.

NOTE: when  incorrect  I  (outside  of  [0,M-1]) or  matrix (non  CRS/SKS)
      is passed, this function throws exception.
      
NOTE: this function may allocate additional, unnecessary place for  ColIdx
      and Vals arrays. It is dictated by  performance  reasons  -  on  SKS
      matrices it is faster  to  allocate  space  at  the  beginning  with
      some "extra"-space, than performing two passes over matrix  -  first
      time to calculate exact space required for data, second  time  -  to
      store data itself.

  -- ALGLIB PROJECT --
     Copyright 10.12.2014 by Bochkanov Sergey
*************************************************************************/
void sparsegetcompressedrow(sparsematrix* s,
     ae_int_t i,
     /* Integer */ ae_vector* colidx,
     /* Real    */ ae_vector* vals,
     ae_int_t* nzcnt,
     ae_state *_state)
{
    ae_int_t k;
    ae_int_t k0;
    ae_int_t j;
    ae_int_t j0;
    ae_int_t j1;
    ae_int_t i0;
    ae_int_t upperprofile;

    *nzcnt = 0;

    ae_assert(s->matrixtype==1||s->matrixtype==2, "SparseGetRow: S must be CRS/SKS-based matrix", _state);
    ae_assert(i>=0&&i<s->m, "SparseGetRow: I<0 or I>=M", _state);
    
    /*
     * Initialize NZCnt
     */
    *nzcnt = 0;
    
    /*
     * CRS matrix - just copy data
     */
    if( s->matrixtype==1 )
    {
        *nzcnt = s->ridx.ptr.p_int[i+1]-s->ridx.ptr.p_int[i];
        ivectorsetlengthatleast(colidx, *nzcnt, _state);
        rvectorsetlengthatleast(vals, *nzcnt, _state);
        k0 = s->ridx.ptr.p_int[i];
        for(k=0; k<=*nzcnt-1; k++)
        {
            colidx->ptr.p_int[k] = s->idx.ptr.p_int[k0+k];
            vals->ptr.p_double[k] = s->vals.ptr.p_double[k0+k];
        }
        return;
    }
    
    /*
     * SKS matrix - a bit more complex sequence
     */
    if( s->matrixtype==2 )
    {
        ae_assert(s->n==s->m, "SparseGetCompressedRow: non-square SKS matrices are not supported", _state);
        
        /*
         * Allocate enough place for storage
         */
        upperprofile = s->uidx.ptr.p_int[s->n];
        ivectorsetlengthatleast(colidx, s->didx.ptr.p_int[i]+1+upperprofile, _state);
        rvectorsetlengthatleast(vals, s->didx.ptr.p_int[i]+1+upperprofile, _state);
        
        /*
         * Copy subdiagonal and diagonal parts
         */
        j0 = i-s->didx.ptr.p_int[i];
        i0 = -j0+s->ridx.ptr.p_int[i];
        for(j=j0; j<=i; j++)
        {
            colidx->ptr.p_int[*nzcnt] = j;
            vals->ptr.p_double[*nzcnt] = s->vals.ptr.p_double[j+i0];
            *nzcnt = *nzcnt+1;
        }
        
        /*
         * Copy superdiagonal part
         */
        j0 = i+1;
        j1 = ae_minint(s->n-1, i+upperprofile, _state);
        for(j=j0; j<=j1; j++)
        {
            if( j-i<=s->uidx.ptr.p_int[j] )
            {
                colidx->ptr.p_int[*nzcnt] = j;
                vals->ptr.p_double[*nzcnt] = s->vals.ptr.p_double[s->ridx.ptr.p_int[j+1]-(j-i)];
                *nzcnt = *nzcnt+1;
            }
        }
        return;
    }
}
/*************************************************************************
This function performs efficient in-place  transpose  of  SKS  matrix.  No
additional memory is allocated during transposition.

This function supports only skyline storage format (SKS).

INPUT PARAMETERS
    S       -   sparse matrix in SKS format.

OUTPUT PARAMETERS
    S           -   sparse matrix, transposed.

  -- ALGLIB PROJECT --
     Copyright 16.01.2014 by Bochkanov Sergey
*************************************************************************/
void sparsetransposesks(sparsematrix* s, ae_state *_state)
{
    ae_int_t n;
    ae_int_t d;
    ae_int_t u;
    ae_int_t i;
    ae_int_t k;
    ae_int_t t0;
    ae_int_t t1;
    double v;


    ae_assert(s->matrixtype==2, "SparseTransposeSKS: only SKS matrices are supported", _state);
    ae_assert(s->m==s->n, "SparseTransposeSKS: non-square SKS matrices are not supported", _state);
    n = s->n;
    for(i=1; i<=n-1; i++)
    {
        d = s->didx.ptr.p_int[i];
        u = s->uidx.ptr.p_int[i];
        k = s->uidx.ptr.p_int[i];
        s->uidx.ptr.p_int[i] = s->didx.ptr.p_int[i];
        s->didx.ptr.p_int[i] = k;
        if( d==u )
        {
            
            /*
             * Upper skyline height equal to lower skyline height,
             * simple exchange is needed for transposition
             */
            t0 = s->ridx.ptr.p_int[i];
            for(k=0; k<=d-1; k++)
            {
                v = s->vals.ptr.p_double[t0+k];
                s->vals.ptr.p_double[t0+k] = s->vals.ptr.p_double[t0+d+1+k];
                s->vals.ptr.p_double[t0+d+1+k] = v;
            }
        }
        if( d>u )
        {
            
            /*
             * Upper skyline height is less than lower skyline height.
             *
             * Transposition becomes a bit tricky: we have to rearrange
             * "L0 L1 D U" to "U D L0 L1", where |L0|=|U|=u, |L1|=d-u.
             *
             * In order to do this we perform a sequence of swaps and
             * in-place reversals:
             * * swap(L0,U)         =>  "U   L1  D   L0"
             * * reverse("L1 D L0") =>  "U   L0~ D   L1~" (where X~ is a reverse of X)
             * * reverse("L0~ D")   =>  "U   D   L0  L1~"
             * * reverse("L1")      =>  "U   D   L0  L1"
             */
            t0 = s->ridx.ptr.p_int[i];
            t1 = s->ridx.ptr.p_int[i]+d+1;
            for(k=0; k<=u-1; k++)
            {
                v = s->vals.ptr.p_double[t0+k];
                s->vals.ptr.p_double[t0+k] = s->vals.ptr.p_double[t1+k];
                s->vals.ptr.p_double[t1+k] = v;
            }
            t0 = s->ridx.ptr.p_int[i]+u;
            t1 = s->ridx.ptr.p_int[i+1]-1;
            while(t1>t0)
            {
                v = s->vals.ptr.p_double[t0];
                s->vals.ptr.p_double[t0] = s->vals.ptr.p_double[t1];
                s->vals.ptr.p_double[t1] = v;
                t0 = t0+1;
                t1 = t1-1;
            }
            t0 = s->ridx.ptr.p_int[i]+u;
            t1 = s->ridx.ptr.p_int[i]+u+u;
            while(t1>t0)
            {
                v = s->vals.ptr.p_double[t0];
                s->vals.ptr.p_double[t0] = s->vals.ptr.p_double[t1];
                s->vals.ptr.p_double[t1] = v;
                t0 = t0+1;
                t1 = t1-1;
            }
            t0 = s->ridx.ptr.p_int[i+1]-(d-u);
            t1 = s->ridx.ptr.p_int[i+1]-1;
            while(t1>t0)
            {
                v = s->vals.ptr.p_double[t0];
                s->vals.ptr.p_double[t0] = s->vals.ptr.p_double[t1];
                s->vals.ptr.p_double[t1] = v;
                t0 = t0+1;
                t1 = t1-1;
            }
        }
        if( d<u )
        {
            
            /*
             * Upper skyline height is greater than lower skyline height.
             *
             * Transposition becomes a bit tricky: we have to rearrange
             * "L D U0 U1" to "U0 U1 D L", where |U1|=|L|=d, |U0|=u-d.
             *
             * In order to do this we perform a sequence of swaps and
             * in-place reversals:
             * * swap(L,U1)         =>  "U1  D   U0  L"
             * * reverse("U1 D U0") =>  "U0~ D   U1~ L" (where X~ is a reverse of X)
             * * reverse("U0~")     =>  "U0  D   U1~ L"
             * * reverse("D U1~")   =>  "U0  U1  D   L"
             */
            t0 = s->ridx.ptr.p_int[i];
            t1 = s->ridx.ptr.p_int[i+1]-d;
            for(k=0; k<=d-1; k++)
            {
                v = s->vals.ptr.p_double[t0+k];
                s->vals.ptr.p_double[t0+k] = s->vals.ptr.p_double[t1+k];
                s->vals.ptr.p_double[t1+k] = v;
            }
            t0 = s->ridx.ptr.p_int[i];
            t1 = s->ridx.ptr.p_int[i]+u;
            while(t1>t0)
            {
                v = s->vals.ptr.p_double[t0];
                s->vals.ptr.p_double[t0] = s->vals.ptr.p_double[t1];
                s->vals.ptr.p_double[t1] = v;
                t0 = t0+1;
                t1 = t1-1;
            }
            t0 = s->ridx.ptr.p_int[i];
            t1 = s->ridx.ptr.p_int[i]+u-d-1;
            while(t1>t0)
            {
                v = s->vals.ptr.p_double[t0];
                s->vals.ptr.p_double[t0] = s->vals.ptr.p_double[t1];
                s->vals.ptr.p_double[t1] = v;
                t0 = t0+1;
                t1 = t1-1;
            }
            t0 = s->ridx.ptr.p_int[i]+u-d;
            t1 = s->ridx.ptr.p_int[i+1]-d-1;
            while(t1>t0)
            {
                v = s->vals.ptr.p_double[t0];
                s->vals.ptr.p_double[t0] = s->vals.ptr.p_double[t1];
                s->vals.ptr.p_double[t1] = v;
                t0 = t0+1;
                t1 = t1-1;
            }
        }
    }
    k = s->uidx.ptr.p_int[n];
    s->uidx.ptr.p_int[n] = s->didx.ptr.p_int[n];
    s->didx.ptr.p_int[n] = k;
}
/*************************************************************************
This function performs copying with transposition of CRS matrix.

INPUT PARAMETERS
    S0      -   sparse matrix in CRS format.

OUTPUT PARAMETERS
    S1      -   sparse matrix, transposed

  -- ALGLIB PROJECT --
     Copyright 23.07.2018 by Bochkanov Sergey
*************************************************************************/
void sparsecopytransposecrs(sparsematrix* s0,
     sparsematrix* s1,
     ae_state *_state)
{

    _sparsematrix_clear(s1);

    sparsecopytransposecrsbuf(s0, s1, _state);
}


/*************************************************************************
This function performs copying with transposition of CRS matrix  (buffered
version which reuses memory already allocated by  the  target as  much  as
possible).

INPUT PARAMETERS
    S0      -   sparse matrix in CRS format.

OUTPUT PARAMETERS
    S1      -   sparse matrix, transposed; previously allocated memory  is
                reused if possible.

  -- ALGLIB PROJECT --
     Copyright 23.07.2018 by Bochkanov Sergey
*************************************************************************/
void sparsecopytransposecrsbuf(sparsematrix* s0,
     sparsematrix* s1,
     ae_state *_state)
{
    ae_int_t oldn;
    ae_int_t oldm;
    ae_int_t newn;
    ae_int_t newm;
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    ae_int_t kk;
    ae_int_t j0;
    ae_int_t j1;


    ae_assert(s0->matrixtype==1, "SparseCopyTransposeCRSBuf: only CRS matrices are supported", _state);
    oldn = s0->n;
    oldm = s0->m;
    newn = oldm;
    newm = oldn;
    
    /*
     * Update matrix size
     */
    s1->matrixtype = 1;
    s1->n = newn;
    s1->m = newm;
    
    /*
     * Fill RIdx by number of elements per row:
     * RIdx[I+1] stores number of elements in I-th row.
     *
     * Convert RIdx from row sizes to row offsets.
     * Set NInitialized
     */
    isetallocv(newm+1, 0, &s1->ridx, _state);
    for(i=0; i<=oldm-1; i++)
    {
        j0 = s0->ridx.ptr.p_int[i];
        j1 = s0->ridx.ptr.p_int[i+1]-1;
        for(j=j0; j<=j1; j++)
        {
            k = s0->idx.ptr.p_int[j]+1;
            s1->ridx.ptr.p_int[k] = s1->ridx.ptr.p_int[k]+1;
        }
    }
    for(i=0; i<=newm-1; i++)
    {
        s1->ridx.ptr.p_int[i+1] = s1->ridx.ptr.p_int[i+1]+s1->ridx.ptr.p_int[i];
    }
    s1->ninitialized = s1->ridx.ptr.p_int[newm];
    
    /*
     * Allocate memory and move elements to Vals/Idx.
     */
    ivectorsetlengthatleast(&s1->didx, newm, _state);
    for(i=0; i<=newm-1; i++)
    {
        s1->didx.ptr.p_int[i] = s1->ridx.ptr.p_int[i];
    }
    rvectorsetlengthatleast(&s1->vals, s1->ninitialized, _state);
    ivectorsetlengthatleast(&s1->idx, s1->ninitialized, _state);
    for(i=0; i<=oldm-1; i++)
    {
        j0 = s0->ridx.ptr.p_int[i];
        j1 = s0->ridx.ptr.p_int[i+1]-1;
        for(j=j0; j<=j1; j++)
        {
            kk = s0->idx.ptr.p_int[j];
            k = s1->didx.ptr.p_int[kk];
            s1->idx.ptr.p_int[k] = i;
            s1->vals.ptr.p_double[k] = s0->vals.ptr.p_double[j];
            s1->didx.ptr.p_int[kk] = k+1;
        }
    }
    
    /*
     * Initialization 'S.UIdx' and 'S.DIdx'
     */
    sparseinitduidx(s1, _state);
}
/*************************************************************************
This function converts matrix to CRS format.

Some  algorithms  (linear  algebra ones, for example) require matrices in
CRS format. This function allows to perform in-place conversion.

INPUT PARAMETERS
    S           -   sparse M*N matrix in any format

OUTPUT PARAMETERS
    S           -   matrix in CRS format
    
NOTE: this   function  has  no  effect  when  called with matrix which is
      already in CRS mode.
      
NOTE: this function allocates temporary memory to store a   copy  of  the
      matrix. If you perform a lot of repeated conversions, we  recommend
      you  to  use  SparseCopyToCRSBuf()  function,   which   can   reuse
      previously allocated memory.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
void sparseconverttocrs(sparsematrix* s, ae_state *_state)
{
    ae_frame _frame_block;
    ae_int_t m;
    ae_int_t i;
    ae_int_t j;
    ae_vector tvals;
    ae_vector tidx;
    ae_vector temp;
    ae_vector tridx;
    ae_int_t nonne;
    ae_int_t k;
    ae_int_t offs0;
    ae_int_t offs1;

    ae_frame_make(_state, &_frame_block);
    memset(&tvals, 0, sizeof(tvals));
    memset(&tidx, 0, sizeof(tidx));
    memset(&temp, 0, sizeof(temp));
    memset(&tridx, 0, sizeof(tridx));
    ae_vector_init(&tvals, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tidx, 0, DT_INT, _state, ae_true);
    ae_vector_init(&temp, 0, DT_INT, _state, ae_true);
    ae_vector_init(&tridx, 0, DT_INT, _state, ae_true);

    m = s->m;
    if( s->matrixtype==0 )
    {
        
        /*
         * From Hash-table to CRS.
         * First, create local copy of the hash table.
         */
        s->matrixtype = 1;
        k = s->tablesize;
        ae_swap_vectors(&s->vals, &tvals);
        ae_swap_vectors(&s->idx, &tidx);
        
        /*
         * Fill RIdx by number of elements per row:
         * RIdx[I+1] stores number of elements in I-th row.
         *
         * Convert RIdx from row sizes to row offsets.
         * Set NInitialized
         */
        nonne = 0;
        ivectorsetlengthatleast(&s->ridx, s->m+1, _state);
        for(i=0; i<=s->m; i++)
        {
            s->ridx.ptr.p_int[i] = 0;
        }
        for(i=0; i<=k-1; i++)
        {
            if( tidx.ptr.p_int[2*i]>=0 )
            {
                s->ridx.ptr.p_int[tidx.ptr.p_int[2*i]+1] = s->ridx.ptr.p_int[tidx.ptr.p_int[2*i]+1]+1;
                nonne = nonne+1;
            }
        }
        for(i=0; i<=s->m-1; i++)
        {
            s->ridx.ptr.p_int[i+1] = s->ridx.ptr.p_int[i+1]+s->ridx.ptr.p_int[i];
        }
        s->ninitialized = s->ridx.ptr.p_int[s->m];
        
        /*
         * Allocate memory and move elements to Vals/Idx.
         * Initially, elements are sorted by rows, but unsorted within row.
         * After initial insertion we sort elements within row.
         */
        ae_vector_set_length(&temp, s->m, _state);
        for(i=0; i<=s->m-1; i++)
        {
            temp.ptr.p_int[i] = 0;
        }
        rvectorsetlengthatleast(&s->vals, nonne, _state);
        ivectorsetlengthatleast(&s->idx, nonne, _state);
        for(i=0; i<=k-1; i++)
        {
            if( tidx.ptr.p_int[2*i]>=0 )
            {
                s->vals.ptr.p_double[s->ridx.ptr.p_int[tidx.ptr.p_int[2*i]]+temp.ptr.p_int[tidx.ptr.p_int[2*i]]] = tvals.ptr.p_double[i];
                s->idx.ptr.p_int[s->ridx.ptr.p_int[tidx.ptr.p_int[2*i]]+temp.ptr.p_int[tidx.ptr.p_int[2*i]]] = tidx.ptr.p_int[2*i+1];
                temp.ptr.p_int[tidx.ptr.p_int[2*i]] = temp.ptr.p_int[tidx.ptr.p_int[2*i]]+1;
            }
        }
        for(i=0; i<=s->m-1; i++)
        {
            tagsortmiddleir(&s->idx, &s->vals, s->ridx.ptr.p_int[i], s->ridx.ptr.p_int[i+1]-s->ridx.ptr.p_int[i], _state);
        }
        
        /*
         * Initialization 'S.UIdx' and 'S.DIdx'
         */
        sparseinitduidx(s, _state);
        ae_frame_leave(_state);
        return;
    }
    if( s->matrixtype==1 )
    {
        
        /*
         * Already CRS
         */
        ae_frame_leave(_state);
        return;
    }
    if( s->matrixtype==2 )
    {
        ae_assert(s->m==s->n, "SparseConvertToCRS: non-square SKS matrices are not supported", _state);
        
        /*
         * From SKS to CRS.
         *
         * First, create local copy of the SKS matrix (Vals,
         * Idx, RIdx are stored; DIdx/UIdx for some time are
         * left in the SparseMatrix structure).
         */
        s->matrixtype = 1;
        ae_swap_vectors(&s->vals, &tvals);
        ae_swap_vectors(&s->idx, &tidx);
        ae_swap_vectors(&s->ridx, &tridx);
        
        /*
         * Fill RIdx by number of elements per row:
         * RIdx[I+1] stores number of elements in I-th row.
         *
         * Convert RIdx from row sizes to row offsets.
         * Set NInitialized
         */
        ivectorsetlengthatleast(&s->ridx, m+1, _state);
        s->ridx.ptr.p_int[0] = 0;
        for(i=1; i<=m; i++)
        {
            s->ridx.ptr.p_int[i] = 1;
        }
        nonne = 0;
        for(i=0; i<=m-1; i++)
        {
            s->ridx.ptr.p_int[i+1] = s->didx.ptr.p_int[i]+s->ridx.ptr.p_int[i+1];
            for(j=i-s->uidx.ptr.p_int[i]; j<=i-1; j++)
            {
                s->ridx.ptr.p_int[j+1] = s->ridx.ptr.p_int[j+1]+1;
            }
            nonne = nonne+s->didx.ptr.p_int[i]+1+s->uidx.ptr.p_int[i];
        }
        for(i=0; i<=s->m-1; i++)
        {
            s->ridx.ptr.p_int[i+1] = s->ridx.ptr.p_int[i+1]+s->ridx.ptr.p_int[i];
        }
        s->ninitialized = s->ridx.ptr.p_int[s->m];
        
        /*
         * Allocate memory and move elements to Vals/Idx.
         * Initially, elements are sorted by rows, and are sorted within row too.
         * No additional post-sorting is required.
         */
        ae_vector_set_length(&temp, m, _state);
        for(i=0; i<=m-1; i++)
        {
            temp.ptr.p_int[i] = 0;
        }
        rvectorsetlengthatleast(&s->vals, nonne, _state);
        ivectorsetlengthatleast(&s->idx, nonne, _state);
        for(i=0; i<=m-1; i++)
        {
            
            /*
             * copy subdiagonal and diagonal parts of I-th block
             */
            offs0 = tridx.ptr.p_int[i];
            offs1 = s->ridx.ptr.p_int[i]+temp.ptr.p_int[i];
            k = s->didx.ptr.p_int[i]+1;
            for(j=0; j<=k-1; j++)
            {
                s->vals.ptr.p_double[offs1+j] = tvals.ptr.p_double[offs0+j];
                s->idx.ptr.p_int[offs1+j] = i-s->didx.ptr.p_int[i]+j;
            }
            temp.ptr.p_int[i] = temp.ptr.p_int[i]+s->didx.ptr.p_int[i]+1;
            
            /*
             * Copy superdiagonal part of I-th block
             */
            offs0 = tridx.ptr.p_int[i]+s->didx.ptr.p_int[i]+1;
            k = s->uidx.ptr.p_int[i];
            for(j=0; j<=k-1; j++)
            {
                offs1 = s->ridx.ptr.p_int[i-k+j]+temp.ptr.p_int[i-k+j];
                s->vals.ptr.p_double[offs1] = tvals.ptr.p_double[offs0+j];
                s->idx.ptr.p_int[offs1] = i;
                temp.ptr.p_int[i-k+j] = temp.ptr.p_int[i-k+j]+1;
            }
        }
        
        /*
         * Initialization 'S.UIdx' and 'S.DIdx'
         */
        sparseinitduidx(s, _state);
        ae_frame_leave(_state);
        return;
    }
    ae_assert(ae_false, "SparseConvertToCRS: invalid matrix type", _state);
    ae_frame_leave(_state);
}
/*************************************************************************
This function checks matrix storage format and returns True when matrix is
stored using SKS representation.

INPUT PARAMETERS:
    S   -   sparse matrix.

RESULT:
    True if matrix type is SKS
    False if matrix type is not SKS
    
  -- ALGLIB PROJECT --
     Copyright 20.07.2012 by Bochkanov Sergey
*************************************************************************/
ae_bool sparseissks(sparsematrix* s, ae_state *_state)
{
    ae_bool result;


    ae_assert((((s->matrixtype==0||s->matrixtype==1)||s->matrixtype==2)||s->matrixtype==-10081)||s->matrixtype==-10082, "SparseIsSKS: invalid matrix type", _state);
    result = s->matrixtype==2;
    return result;
}
/*************************************************************************
The function returns number of rows of a sparse matrix.

RESULT: number of rows of a sparse matrix.
    
  -- ALGLIB PROJECT --
     Copyright 23.08.2012 by Bochkanov Sergey
*************************************************************************/
ae_int_t sparsegetnrows(sparsematrix* s, ae_state *_state)
{
    ae_int_t result;


    result = s->m;
    return result;
}


/*************************************************************************
The function returns number of columns of a sparse matrix.

RESULT: number of columns of a sparse matrix.
    
  -- ALGLIB PROJECT --
     Copyright 23.08.2012 by Bochkanov Sergey
*************************************************************************/
ae_int_t sparsegetncols(sparsematrix* s, ae_state *_state)
{
    ae_int_t result;


    result = s->n;
    return result;
}
/*************************************************************************
This is hash function.

  -- ALGLIB PROJECT --
     Copyright 14.10.2011 by Bochkanov Sergey
*************************************************************************/
static ae_int_t sparse_hash(ae_int_t i,
     ae_int_t j,
     ae_int_t tabsize,
     ae_state *_state)
{
    ae_frame _frame_block;
    hqrndstate r;
    ae_int_t result;

    ae_frame_make(_state, &_frame_block);
    memset(&r, 0, sizeof(r));
    _hqrndstate_init(&r, _state, ae_true);

    hqrndseed(i, j, &r, _state);
    result = hqrnduniformi(&r, tabsize, _state);
    ae_frame_leave(_state);
    return result;
}
void _sparsematrix_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    sparsematrix *p = (sparsematrix*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_init(&p->vals, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->idx, 0, DT_INT, _state, make_automatic);
    ae_vector_init(&p->ridx, 0, DT_INT, _state, make_automatic);
    ae_vector_init(&p->didx, 0, DT_INT, _state, make_automatic);
    ae_vector_init(&p->uidx, 0, DT_INT, _state, make_automatic);
}




void _sparsematrix_clear(void* _p)
{
    sparsematrix *p = (sparsematrix*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_clear(&p->vals);
    ae_vector_clear(&p->idx);
    ae_vector_clear(&p->ridx);
    ae_vector_clear(&p->didx);
    ae_vector_clear(&p->uidx);
}
#endif
#if defined(AE_COMPILE_TRFAC) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
Cache-oblivious Cholesky decomposition

The algorithm computes Cholesky decomposition  of  a  symmetric  positive-
definite matrix. The result of an algorithm is a representation  of  A  as
A=U^T*U  or A=L*L^T

INPUT PARAMETERS:
    A       -   upper or lower triangle of a factorized matrix.
                array with elements [0..N-1, 0..N-1].
    N       -   size of matrix A.
    IsUpper -   if IsUpper=True, then A contains an upper triangle of
                a symmetric matrix, otherwise A contains a lower one.

OUTPUT PARAMETERS:
    A       -   the result of factorization. If IsUpper=True, then
                the upper triangle contains matrix U, so that A = U^T*U,
                and the elements below the main diagonal are not modified.
                Similarly, if IsUpper = False.

RESULT:
    If  the  matrix  is  positive-definite,  the  function  returns  True.
    Otherwise, the function returns False. Contents of A is not determined
    in such case.

  ! FREE EDITION OF ALGLIB:
  ! 
  ! Free Edition of ALGLIB supports following important features for  this
  ! function:
  ! * C++ version: x64 SIMD support using C++ intrinsics
  ! * C#  version: x64 SIMD support using NET5/NetCore hardware intrinsics
  !
  ! We  recommend  you  to  read  'Compiling ALGLIB' section of the ALGLIB
  ! Reference Manual in order  to  find  out  how to activate SIMD support
  ! in ALGLIB.

  ! COMMERCIAL EDITION OF ALGLIB:
  ! 
  ! Commercial Edition of ALGLIB includes following important improvements
  ! of this function:
  ! * high-performance native backend with same C# interface (C# version)
  ! * multithreading support (C++ and C# versions)
  ! * hardware vendor (Intel) implementations of linear algebra primitives
  !   (C++ and C# versions, x86/x64 platform)
  ! 
  ! We recommend you to read 'Working with commercial version' section  of
  ! ALGLIB Reference Manual in order to find out how to  use  performance-
  ! related features provided by commercial edition of ALGLIB.

  -- ALGLIB routine --
     15.12.2009
     Bochkanov Sergey
*************************************************************************/
ae_bool spdmatrixcholesky(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector tmp;
    ae_bool result;

    ae_frame_make(_state, &_frame_block);
    memset(&tmp, 0, sizeof(tmp));
    ae_vector_init(&tmp, 0, DT_REAL, _state, ae_true);

    if( n<1 )
    {
        result = ae_false;
        ae_frame_leave(_state);
        return result;
    }
    result = spdmatrixcholeskyrec(a, 0, n, isupper, &tmp, _state);
    ae_frame_leave(_state);
    return result;
}
/*************************************************************************
Sparse Cholesky decomposition for skyline matrixm using in-place algorithm
without allocating additional storage.

The algorithm computes Cholesky decomposition  of  a  symmetric  positive-
definite sparse matrix. The result of an algorithm is a representation  of
A as A=U^T*U or A=L*L^T

This function allows to perform very efficient decomposition of low-profile
matrices (average bandwidth is ~5-10 elements). For larger matrices it  is
recommended to use supernodal Cholesky decomposition: SparseCholeskyP() or
SparseCholeskyAnalyze()/SparseCholeskyFactorize().

INPUT PARAMETERS:
    A       -   sparse matrix in skyline storage (SKS) format.
    N       -   size of matrix A (can be smaller than actual size of A)
    IsUpper -   if IsUpper=True, then factorization is performed on  upper
                triangle. Another triangle is ignored (it may contant some
                data, but it is not changed).
    

OUTPUT PARAMETERS:
    A       -   the result of factorization, stored in SKS. If IsUpper=True,
                then the upper  triangle  contains  matrix  U,  such  that
                A = U^T*U. Lower triangle is not changed.
                Similarly, if IsUpper = False. In this case L is returned,
                and we have A = L*(L^T).
                Note that THIS function does not  perform  permutation  of
                rows to reduce bandwidth.

RESULT:
    If  the  matrix  is  positive-definite,  the  function  returns  True.
    Otherwise, the function returns False. Contents of A is not determined
    in such case.

NOTE: for  performance  reasons  this  function  does NOT check that input
      matrix  includes  only  finite  values. It is your responsibility to
      make sure that there are no infinite or NAN values in the matrix.

  -- ALGLIB routine --
     16.01.2014
     Bochkanov Sergey
*************************************************************************/
ae_bool sparsecholeskyskyline(sparsematrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    ae_int_t jnz;
    ae_int_t jnza;
    ae_int_t jnzl;
    double v;
    double vv;
    double a12;
    ae_int_t nready;
    ae_int_t nadd;
    ae_int_t banda;
    ae_int_t offsa;
    ae_int_t offsl;
    ae_bool result;


    ae_assert(n>=0, "SparseCholeskySkyline: N<0", _state);
    ae_assert(sparsegetnrows(a, _state)>=n, "SparseCholeskySkyline: rows(A)<N", _state);
    ae_assert(sparsegetncols(a, _state)>=n, "SparseCholeskySkyline: cols(A)<N", _state);
    ae_assert(sparseissks(a, _state), "SparseCholeskySkyline: A is not stored in SKS format", _state);
    result = ae_false;
    
    /*
     * transpose if needed
     */
    if( isupper )
    {
        sparsetransposesks(a, _state);
    }
    
    /*
     * Perform Cholesky decomposition:
     * * we assume than leading NReady*NReady submatrix is done
     * * having Cholesky decomposition of NReady*NReady submatrix we
     *   obtain decomposition of larger (NReady+NAdd)*(NReady+NAdd) one.
     *
     * Here is algorithm. At the start we have
     *
     *     (      |   )
     *     (  L   |   )
     * S = (      |   )
     *     (----------)
     *     (  A   | B )
     *
     * with L being already computed Cholesky factor, A and B being
     * unprocessed parts of the matrix. Of course, L/A/B are stored
     * in SKS format.
     *
     * Then, we calculate A1:=(inv(L)*A')' and replace A with A1.
     * Then, we calculate B1:=B-A1*A1'     and replace B with B1
     *
     * Finally, we calculate small NAdd*NAdd Cholesky of B1 with
     * dense solver. Now, L/A1/B1 are Cholesky decomposition of the
     * larger (NReady+NAdd)*(NReady+NAdd) matrix.
     */
    nready = 0;
    nadd = 1;
    while(nready<n)
    {
        ae_assert(nadd==1, "SkylineCholesky: internal error", _state);
        
        /*
         * Calculate A1:=(inv(L)*A')'
         *
         * Elements are calculated row by row (example below is given
         * for NAdd=1):
         * * first, we solve L[0,0]*A1[0]=A[0]
         * * then, we solve  L[1,0]*A1[0]+L[1,1]*A1[1]=A[1]
         * * then, we move to next row and so on
         * * during calculation of A1 we update A12 - squared norm of A1
         *
         * We extensively use sparsity of both A/A1 and L:
         * * first, equations from 0 to BANDWIDTH(A1)-1 are completely zero
         * * second, for I>=BANDWIDTH(A1), I-th equation is reduced from
         *     L[I,0]*A1[0] + L[I,1]*A1[1] + ... + L[I,I]*A1[I] = A[I]
         *   to
         *     L[I,JNZ]*A1[JNZ] + ... + L[I,I]*A1[I] = A[I]
         *   where JNZ = max(NReady-BANDWIDTH(A1),I-BANDWIDTH(L[i]))
         *   (JNZ is an index of the firts column where both A and L become
         *   nonzero).
         *
         * NOTE: we rely on details of SparseMatrix internal storage format.
         *       This is allowed by SparseMatrix specification.
         */
        a12 = 0.0;
        if( a->didx.ptr.p_int[nready]>0 )
        {
            banda = a->didx.ptr.p_int[nready];
            for(i=nready-banda; i<=nready-1; i++)
            {
                
                /*
                 * Elements of A1[0:I-1] were computed:
                 * * A1[0:NReady-BandA-1] are zero (sparse)
                 * * A1[NReady-BandA:I-1] replaced corresponding elements of A
                 *
                 * Now it is time to get I-th one.
                 *
                 * First, we calculate:
                 * * JNZA  - index of the first column where A become nonzero
                 * * JNZL  - index of the first column where L become nonzero
                 * * JNZ   - index of the first column where both A and L become nonzero
                 * * OffsA - offset of A[JNZ] in A.Vals
                 * * OffsL - offset of L[I,JNZ] in A.Vals
                 *
                 * Then, we solve SUM(A1[j]*L[I,j],j=JNZ..I-1) + A1[I]*L[I,I] = A[I],
                 * with A1[JNZ..I-1] already known, and A1[I] unknown.
                 */
                jnza = nready-banda;
                jnzl = i-a->didx.ptr.p_int[i];
                jnz = ae_maxint(jnza, jnzl, _state);
                offsa = a->ridx.ptr.p_int[nready]+(jnz-jnza);
                offsl = a->ridx.ptr.p_int[i]+(jnz-jnzl);
                v = 0.0;
                k = i-1-jnz;
                for(j=0; j<=k; j++)
                {
                    v = v+a->vals.ptr.p_double[offsa+j]*a->vals.ptr.p_double[offsl+j];
                }
                vv = (a->vals.ptr.p_double[offsa+k+1]-v)/a->vals.ptr.p_double[offsl+k+1];
                a->vals.ptr.p_double[offsa+k+1] = vv;
                a12 = a12+vv*vv;
            }
        }
        
        /*
         * Calculate CHOLESKY(B-A1*A1')
         */
        offsa = a->ridx.ptr.p_int[nready]+a->didx.ptr.p_int[nready];
        v = a->vals.ptr.p_double[offsa];
        if( ae_fp_less_eq(v,a12) )
        {
            result = ae_false;
            return result;
        }
        a->vals.ptr.p_double[offsa] = ae_sqrt(v-a12, _state);
        
        /*
         * Increase size of the updated matrix
         */
        inc(&nready, _state);
    }
    
    /*
     * transpose if needed
     */
    if( isupper )
    {
        sparsetransposesks(a, _state);
    }
    result = ae_true;
    return result;
}
/*************************************************************************
Advanced interface for SPDMatrixCholesky, performs no temporary allocations.

INPUT PARAMETERS:
    A       -   matrix given by upper or lower triangle
    Offs    -   offset of diagonal block to decompose
    N       -   diagonal block size
    IsUpper -   what half is given
    Tmp     -   temporary array; allocated by function, if its size is too
                small; can be reused on subsequent calls.
                
OUTPUT PARAMETERS:
    A       -   upper (or lower) triangle contains Cholesky decomposition

RESULT:
    True, on success
    False, on failure

  -- ALGLIB routine --
     15.12.2009
     Bochkanov Sergey
*************************************************************************/
ae_bool spdmatrixcholeskyrec(/* Real    */ ae_matrix* a,
     ae_int_t offs,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* tmp,
     ae_state *_state)
{
    ae_int_t n1;
    ae_int_t n2;
    ae_int_t tsa;
    ae_int_t tsb;
    ae_bool result;


    tsa = matrixtilesizea(_state);
    tsb = matrixtilesizeb(_state);
    
    /*
     * Allocate temporaries
     */
    if( tmp->cnt<2*n )
    {
        ae_vector_set_length(tmp, 2*n, _state);
    }
    
    /*
     * Basecases
     */
    if( n<1 )
    {
        result = ae_false;
        return result;
    }
    if( n==1 )
    {
        if( ae_fp_greater(a->ptr.pp_double[offs][offs],(double)(0)) )
        {
            a->ptr.pp_double[offs][offs] = ae_sqrt(a->ptr.pp_double[offs][offs], _state);
            result = ae_true;
        }
        else
        {
            result = ae_false;
        }
        return result;
    }
    if( n<=tsb )
    {
        if( spdmatrixcholeskymkl(a, offs, n, isupper, &result, _state) )
        {
            return result;
        }
    }
    if( n<=tsa )
    {
        result = trfac_spdmatrixcholesky2(a, offs, n, isupper, tmp, _state);
        return result;
    }
    
    /*
     * Split task into smaller ones
     */
    if( n>tsb )
    {
        
        /*
         * Split leading B-sized block from the beginning (block-matrix approach)
         */
        n1 = tsb;
        n2 = n-n1;
    }
    else
    {
        
        /*
         * Smaller than B-size, perform cache-oblivious split
         */
        tiledsplit(n, tsa, &n1, &n2, _state);
    }
    result = spdmatrixcholeskyrec(a, offs, n1, isupper, tmp, _state);
    if( !result )
    {
        return result;
    }
    if( n2>0 )
    {
        if( isupper )
        {
            rmatrixlefttrsm(n1, n2, a, offs, offs, isupper, ae_false, 1, a, offs, offs+n1, _state);
            rmatrixsyrk(n2, n1, -1.0, a, offs, offs+n1, 1, 1.0, a, offs+n1, offs+n1, isupper, _state);
        }
        else
        {
            rmatrixrighttrsm(n2, n1, a, offs, offs, isupper, ae_false, 1, a, offs+n1, offs, _state);
            rmatrixsyrk(n2, n1, -1.0, a, offs+n1, offs, 0, 1.0, a, offs+n1, offs+n1, isupper, _state);
        }
        result = spdmatrixcholeskyrec(a, offs+n1, n2, isupper, tmp, _state);
        if( !result )
        {
            return result;
        }
    }
    return result;
}



/*************************************************************************
Level-2 Cholesky subroutine

  -- LAPACK routine (version 3.0) --
     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
     Courant Institute, Argonne National Lab, and Rice University
     February 29, 1992
*************************************************************************/
static ae_bool trfac_spdmatrixcholesky2(/* Real    */ ae_matrix* aaa,
     ae_int_t offs,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* tmp,
     ae_state *_state)
{
    ae_int_t i;
    ae_int_t j;
    double ajj;
    double v;
    double r;
    ae_bool result;


    result = ae_true;
    if( n<0 )
    {
        result = ae_false;
        return result;
    }
    
    /*
     * Quick return if possible
     */
    if( n==0 )
    {
        return result;
    }
    if( isupper )
    {
        
        /*
         * Compute the Cholesky factorization A = U'*U.
         */
        for(j=0; j<=n-1; j++)
        {
            
            /*
             * Compute U(J,J) and test for non-positive-definiteness.
             */
            v = ae_v_dotproduct(&aaa->ptr.pp_double[offs][offs+j], aaa->stride, &aaa->ptr.pp_double[offs][offs+j], aaa->stride, ae_v_len(offs,offs+j-1));
            ajj = aaa->ptr.pp_double[offs+j][offs+j]-v;
            if( ae_fp_less_eq(ajj,(double)(0)) )
            {
                aaa->ptr.pp_double[offs+j][offs+j] = ajj;
                result = ae_false;
                return result;
            }
            ajj = ae_sqrt(ajj, _state);
            aaa->ptr.pp_double[offs+j][offs+j] = ajj;
            
            /*
             * Compute elements J+1:N-1 of row J.
             */
            if( j<n-1 )
            {
                if( j>0 )
                {
                    ae_v_moveneg(&tmp->ptr.p_double[0], 1, &aaa->ptr.pp_double[offs][offs+j], aaa->stride, ae_v_len(0,j-1));
                    rmatrixmv(n-j-1, j, aaa, offs, offs+j+1, 1, tmp, 0, tmp, n, _state);
                    ae_v_add(&aaa->ptr.pp_double[offs+j][offs+j+1], 1, &tmp->ptr.p_double[n], 1, ae_v_len(offs+j+1,offs+n-1));
                }
                r = 1/ajj;
                ae_v_muld(&aaa->ptr.pp_double[offs+j][offs+j+1], 1, ae_v_len(offs+j+1,offs+n-1), r);
            }
        }
    }
    else
    {
        
        /*
         * Compute the Cholesky factorization A = L*L'.
         */
        for(j=0; j<=n-1; j++)
        {
            
            /*
             * Compute L(J+1,J+1) and test for non-positive-definiteness.
             */
            v = ae_v_dotproduct(&aaa->ptr.pp_double[offs+j][offs], 1, &aaa->ptr.pp_double[offs+j][offs], 1, ae_v_len(offs,offs+j-1));
            ajj = aaa->ptr.pp_double[offs+j][offs+j]-v;
            if( ae_fp_less_eq(ajj,(double)(0)) )
            {
                aaa->ptr.pp_double[offs+j][offs+j] = ajj;
                result = ae_false;
                return result;
            }
            ajj = ae_sqrt(ajj, _state);
            aaa->ptr.pp_double[offs+j][offs+j] = ajj;
            
            /*
             * Compute elements J+1:N of column J.
             */
            if( j<n-1 )
            {
                r = 1/ajj;
                if( j>0 )
                {
                    ae_v_move(&tmp->ptr.p_double[0], 1, &aaa->ptr.pp_double[offs+j][offs], 1, ae_v_len(0,j-1));
                    rmatrixmv(n-j-1, j, aaa, offs+j+1, offs, 0, tmp, 0, tmp, n, _state);
                    for(i=0; i<=n-j-2; i++)
                    {
                        aaa->ptr.pp_double[offs+j+1+i][offs+j] = (aaa->ptr.pp_double[offs+j+1+i][offs+j]-tmp->ptr.p_double[n+i])*r;
                    }
                }
                else
                {
                    for(i=0; i<=n-j-2; i++)
                    {
                        aaa->ptr.pp_double[offs+j+1+i][offs+j] = aaa->ptr.pp_double[offs+j+1+i][offs+j]*r;
                    }
                }
            }
        }
    }
    return result;
}

#endif
#if defined(AE_COMPILE_NORMESTIMATOR) || !defined(AE_PARTIAL_BUILD)


/*************************************************************************
This procedure initializes matrix norm estimator.

USAGE:
1. User initializes algorithm state with NormEstimatorCreate() call
2. User calls NormEstimatorEstimateSparse() (or NormEstimatorIteration())
3. User calls NormEstimatorResults() to get solution.
   
INPUT PARAMETERS:
    M       -   number of rows in the matrix being estimated, M>0
    N       -   number of columns in the matrix being estimated, N>0
    NStart  -   number of random starting vectors
                recommended value - at least 5.
    NIts    -   number of iterations to do with best starting vector
                recommended value - at least 5.

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

    
NOTE: this algorithm is effectively deterministic, i.e. it always  returns
same result when repeatedly called for the same matrix. In fact, algorithm
uses randomized starting vectors, but internal  random  numbers  generator
always generates same sequence of the random values (it is a  feature, not
bug).

Algorithm can be made non-deterministic with NormEstimatorSetSeed(0) call.

  -- ALGLIB --
     Copyright 06.12.2011 by Bochkanov Sergey
*************************************************************************/
void normestimatorcreate(ae_int_t m,
     ae_int_t n,
     ae_int_t nstart,
     ae_int_t nits,
     normestimatorstate* state,
     ae_state *_state)
{

    _normestimatorstate_clear(state);

    ae_assert(m>0, "NormEstimatorCreate: M<=0", _state);
    ae_assert(n>0, "NormEstimatorCreate: N<=0", _state);
    ae_assert(nstart>0, "NormEstimatorCreate: NStart<=0", _state);
    ae_assert(nits>0, "NormEstimatorCreate: NIts<=0", _state);
    state->m = m;
    state->n = n;
    state->nstart = nstart;
    state->nits = nits;
    state->seedval = 11;
    hqrndrandomize(&state->r, _state);
    ae_vector_set_length(&state->x0, state->n, _state);
    ae_vector_set_length(&state->t, state->m, _state);
    ae_vector_set_length(&state->x1, state->n, _state);
    ae_vector_set_length(&state->xbest, state->n, _state);
    ae_vector_set_length(&state->x, ae_maxint(state->n, state->m, _state), _state);
    ae_vector_set_length(&state->mv, state->m, _state);
    ae_vector_set_length(&state->mtv, state->n, _state);
    ae_vector_set_length(&state->rstate.ia, 3+1, _state);
    ae_vector_set_length(&state->rstate.ra, 2+1, _state);
    state->rstate.stage = -1;
}


/*************************************************************************

  -- ALGLIB --
     Copyright 06.12.2011 by Bochkanov Sergey
*************************************************************************/
ae_bool normestimatoriteration(normestimatorstate* state,
     ae_state *_state)
{
    ae_int_t n;
    ae_int_t m;
    ae_int_t i;
    ae_int_t itcnt;
    double v;
    double growth;
    double bestgrowth;
    ae_bool result;


    
    /*
     * Reverse communication preparations
     * I know it looks ugly, but it works the same way
     * anywhere from C++ to Python.
     *
     * This code initializes locals by:
     * * random values determined during code
     *   generation - on first subroutine call
     * * values from previous call - on subsequent calls
     */
    if( state->rstate.stage>=0 )
    {
        n = state->rstate.ia.ptr.p_int[0];
        m = state->rstate.ia.ptr.p_int[1];
        i = state->rstate.ia.ptr.p_int[2];
        itcnt = state->rstate.ia.ptr.p_int[3];
        v = state->rstate.ra.ptr.p_double[0];
        growth = state->rstate.ra.ptr.p_double[1];
        bestgrowth = state->rstate.ra.ptr.p_double[2];
    }
    else
    {
        n = 359;
        m = -58;
        i = -919;
        itcnt = -909;
        v = 81;
        growth = 255;
        bestgrowth = 74;
    }
    if( state->rstate.stage==0 )
    {
        goto lbl_0;
    }
    if( state->rstate.stage==1 )
    {
        goto lbl_1;
    }
    if( state->rstate.stage==2 )
    {
        goto lbl_2;
    }
    if( state->rstate.stage==3 )
    {
        goto lbl_3;
    }
    
    /*
     * Routine body
     */
    n = state->n;
    m = state->m;
    if( state->seedval>0 )
    {
        hqrndseed(state->seedval, state->seedval+2, &state->r, _state);
    }
    bestgrowth = (double)(0);
    state->xbest.ptr.p_double[0] = (double)(1);
    for(i=1; i<=n-1; i++)
    {
        state->xbest.ptr.p_double[i] = (double)(0);
    }
    itcnt = 0;
lbl_4:
    if( itcnt>state->nstart-1 )
    {
        goto lbl_6;
    }
    do
    {
        v = (double)(0);
        for(i=0; i<=n-1; i++)
        {
            state->x0.ptr.p_double[i] = hqrndnormal(&state->r, _state);
            v = v+ae_sqr(state->x0.ptr.p_double[i], _state);
        }
    }
    while(ae_fp_eq(v,(double)(0)));
    v = 1/ae_sqrt(v, _state);
    ae_v_muld(&state->x0.ptr.p_double[0], 1, ae_v_len(0,n-1), v);
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->x0.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->needmv = ae_true;
    state->needmtv = ae_false;
    state->rstate.stage = 0;
    goto lbl_rcomm;
lbl_0:
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->mv.ptr.p_double[0], 1, ae_v_len(0,m-1));
    state->needmv = ae_false;
    state->needmtv = ae_true;
    state->rstate.stage = 1;
    goto lbl_rcomm;
lbl_1:
    ae_v_move(&state->x1.ptr.p_double[0], 1, &state->mtv.ptr.p_double[0], 1, ae_v_len(0,n-1));
    v = (double)(0);
    for(i=0; i<=n-1; i++)
    {
        v = v+ae_sqr(state->x1.ptr.p_double[i], _state);
    }
    growth = ae_sqrt(ae_sqrt(v, _state), _state);
    if( ae_fp_greater(growth,bestgrowth) )
    {
        v = 1/ae_sqrt(v, _state);
        ae_v_moved(&state->xbest.ptr.p_double[0], 1, &state->x1.ptr.p_double[0], 1, ae_v_len(0,n-1), v);
        bestgrowth = growth;
    }
    itcnt = itcnt+1;
    goto lbl_4;
lbl_6:
    ae_v_move(&state->x0.ptr.p_double[0], 1, &state->xbest.ptr.p_double[0], 1, ae_v_len(0,n-1));
    itcnt = 0;
lbl_7:
    if( itcnt>state->nits-1 )
    {
        goto lbl_9;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->x0.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->needmv = ae_true;
    state->needmtv = ae_false;
    state->rstate.stage = 2;
    goto lbl_rcomm;
lbl_2:
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->mv.ptr.p_double[0], 1, ae_v_len(0,m-1));
    state->needmv = ae_false;
    state->needmtv = ae_true;
    state->rstate.stage = 3;
    goto lbl_rcomm;
lbl_3:
    ae_v_move(&state->x1.ptr.p_double[0], 1, &state->mtv.ptr.p_double[0], 1, ae_v_len(0,n-1));
    v = (double)(0);
    for(i=0; i<=n-1; i++)
    {
        v = v+ae_sqr(state->x1.ptr.p_double[i], _state);
    }
    state->repnorm = ae_sqrt(ae_sqrt(v, _state), _state);
    if( ae_fp_neq(v,(double)(0)) )
    {
        v = 1/ae_sqrt(v, _state);
        ae_v_moved(&state->x0.ptr.p_double[0], 1, &state->x1.ptr.p_double[0], 1, ae_v_len(0,n-1), v);
    }
    itcnt = itcnt+1;
    goto lbl_7;
lbl_9:
    result = ae_false;
    return result;
    
    /*
     * Saving state
     */
lbl_rcomm:
    result = ae_true;
    state->rstate.ia.ptr.p_int[0] = n;
    state->rstate.ia.ptr.p_int[1] = m;
    state->rstate.ia.ptr.p_int[2] = i;
    state->rstate.ia.ptr.p_int[3] = itcnt;
    state->rstate.ra.ptr.p_double[0] = v;
    state->rstate.ra.ptr.p_double[1] = growth;
    state->rstate.ra.ptr.p_double[2] = bestgrowth;
    return result;
}


/*************************************************************************
Matrix norm estimation results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    Nrm     -   estimate of the matrix norm, Nrm>=0

  -- ALGLIB --
     Copyright 06.12.2011 by Bochkanov Sergey
*************************************************************************/
void normestimatorresults(normestimatorstate* state,
     double* nrm,
     ae_state *_state)
{

    *nrm = 0;

    *nrm = state->repnorm;
}


/*************************************************************************
This  function  restarts estimator and prepares it for the next estimation
round.

INPUT PARAMETERS:
    State   -   algorithm state
  -- ALGLIB --
     Copyright 06.12.2011 by Bochkanov Sergey
*************************************************************************/
void normestimatorrestart(normestimatorstate* state, ae_state *_state)
{


    ae_vector_set_length(&state->rstate.ia, 3+1, _state);
    ae_vector_set_length(&state->rstate.ra, 2+1, _state);
    state->rstate.stage = -1;
}

void _normestimatorstate_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    normestimatorstate *p = (normestimatorstate*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_init(&p->x0, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->x1, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->t, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->xbest, 0, DT_REAL, _state, make_automatic);
    _hqrndstate_init(&p->r, _state, make_automatic);
    ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->mv, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->mtv, 0, DT_REAL, _state, make_automatic);
    _rcommstate_init(&p->rstate, _state, make_automatic);
}

void _normestimatorstate_clear(void* _p)
{
    normestimatorstate *p = (normestimatorstate*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_clear(&p->x0);
    ae_vector_clear(&p->x1);
    ae_vector_clear(&p->t);
    ae_vector_clear(&p->xbest);
    _hqrndstate_clear(&p->r);
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->mv);
    ae_vector_clear(&p->mtv);
    _rcommstate_clear(&p->rstate);
}

#endif
}

