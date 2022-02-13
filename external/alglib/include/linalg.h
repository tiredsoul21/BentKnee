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
#ifndef _linalg_pkg_h
#define _linalg_pkg_h
#include "alglibmisc.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_SPARSE) || !defined(AE_PARTIAL_BUILD)
typedef struct
{
    ae_vector vals;
    ae_vector idx;
    ae_vector ridx;
    ae_vector didx;
    ae_vector uidx;
    ae_int_t matrixtype;
    ae_int_t m;
    ae_int_t n;
    ae_int_t nfree;
    ae_int_t ninitialized;
    ae_int_t tablesize;
} sparsematrix;
#endif
#if defined(AE_COMPILE_NORMESTIMATOR) || !defined(AE_PARTIAL_BUILD)
typedef struct
{
    ae_int_t n;
    ae_int_t m;
    ae_int_t nstart;
    ae_int_t nits;
    ae_int_t seedval;
    ae_vector x0;
    ae_vector x1;
    ae_vector t;
    ae_vector xbest;
    hqrndstate r;
    ae_vector x;
    ae_vector mv;
    ae_vector mtv;
    ae_bool needmv;
    ae_bool needmtv;
    double repnorm;
    rcommstate rstate;
} normestimatorstate;
#endif

}


/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_ABLAS) || !defined(AE_PARTIAL_BUILD)
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
     ae_state *_state);
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
     ae_state *_state);
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
    ae_int_t j2, ae_state *_state);
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
     ae_state *_state);
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
    ae_int_t j2, ae_state *_state);
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
     ae_state *_state);
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
    ae_bool isupper, ae_state *_state);
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
     ae_state *_state);
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
    ae_int_t jc, ae_state *_state);
#endif
#if defined(AE_COMPILE_SPARSE) || !defined(AE_PARTIAL_BUILD)
void sparsecreate(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     sparsematrix* s,
     ae_state *_state);
void sparsecreatebuf(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     sparsematrix* s,
     ae_state *_state);
void sparsecreatesksband(ae_int_t m,
     ae_int_t n,
     ae_int_t bw,
     sparsematrix* s,
     ae_state *_state);
void sparsecreatesksbandbuf(ae_int_t m,
     ae_int_t n,
     ae_int_t bw,
     sparsematrix* s,
     ae_state *_state);
void sparseset(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     double v,
     ae_state *_state);
double sparseget(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     ae_state *_state);
void sparsemv(sparsematrix* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void sparsemtv(sparsematrix* s,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void sparsetrsv(sparsematrix* s,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_vector* x,
     ae_state *_state);
void sparseresizematrix(sparsematrix* s, ae_state *_state);
void sparseinitduidx(sparsematrix* s, ae_state *_state);
ae_bool sparserewriteexisting(sparsematrix* s,
     ae_int_t i,
     ae_int_t j,
     double v,
     ae_state *_state);
void sparsegetcompressedrow(sparsematrix* s,
     ae_int_t i,
     /* Integer */ ae_vector* colidx,
     /* Real    */ ae_vector* vals,
     ae_int_t* nzcnt,
     ae_state *_state);
void sparsetransposesks(sparsematrix* s, ae_state *_state);
void sparsecopytransposecrs(sparsematrix* s0,
     sparsematrix* s1,
     ae_state *_state);
void sparsecopytransposecrsbuf(sparsematrix* s0,
     sparsematrix* s1,
     ae_state *_state);
void sparseconverttocrs(sparsematrix* s, ae_state *_state);
ae_bool sparseissks(sparsematrix* s, ae_state *_state);
ae_int_t sparsegetnrows(sparsematrix* s, ae_state *_state);
ae_int_t sparsegetncols(sparsematrix* s, ae_state *_state);
void _sparsematrix_init(void* _p, ae_state *_state, ae_bool make_automatic);
void _sparsematrix_clear(void* _p);
ae_bool spdmatrixcholesky(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
ae_bool sparsecholeskyskyline(sparsematrix* a,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
ae_bool spdmatrixcholeskyrec(/* Real    */ ae_matrix* a,
     ae_int_t offs,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* tmp,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_NORMESTIMATOR) || !defined(AE_PARTIAL_BUILD)
void normestimatorcreate(ae_int_t m,
     ae_int_t n,
     ae_int_t nstart,
     ae_int_t nits,
     normestimatorstate* state,
     ae_state *_state);
ae_bool normestimatoriteration(normestimatorstate* state,
     ae_state *_state);
void normestimatorresults(normestimatorstate* state,
     double* nrm,
     ae_state *_state);

void normestimatorrestart(normestimatorstate* state, ae_state *_state);
void _normestimatorstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
void _normestimatorstate_clear(void* _p);
#endif

}
#endif

