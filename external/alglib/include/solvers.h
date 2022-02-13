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
#ifndef _solvers_pkg_h
#define _solvers_pkg_h
#include "linalg.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_LINLSQR) || !defined(AE_PARTIAL_BUILD)
typedef struct
{
    normestimatorstate nes;
    ae_vector rx;
    ae_vector b;
    ae_int_t n;
    ae_int_t m;
    ae_int_t prectype;
    ae_vector ui;
    ae_vector uip1;
    ae_vector vi;
    ae_vector vip1;
    ae_vector omegai;
    ae_vector omegaip1;
    double alphai;
    double alphaip1;
    double betai;
    double betaip1;
    double phibari;
    double phibarip1;
    double phii;
    double rhobari;
    double rhobarip1;
    double rhoi;
    double ci;
    double si;
    double theta;
    double lambdai;
    ae_vector d;
    double anorm;
    double bnorm2;
    double dnorm;
    double r2;
    ae_vector x;
    ae_vector mv;
    ae_vector mtv;
    double epsa;
    double epsb;
    double epsc;
    ae_int_t maxits;
    ae_bool xrep;
    ae_bool xupdated;
    ae_bool needmv;
    ae_bool needmtv;
    ae_bool needmv2;
    ae_bool needvmv;
    ae_bool needprec;
    ae_int_t repiterationscount;
    ae_int_t repnmv;
    ae_int_t repterminationtype;
    ae_bool running;
    ae_bool userterminationneeded;
    ae_vector tmpd;
    ae_vector tmpx;
    rcommstate rstate;
} linlsqrstate;
typedef struct
{
    ae_int_t iterationscount;
    ae_int_t nmv;
    ae_int_t terminationtype;
} linlsqrreport;
#endif

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{
#if defined(AE_COMPILE_LINLSQR) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************

*************************************************************************/
class _linlsqrreport_owner
{
public:
    _linlsqrreport_owner();
    _linlsqrreport_owner(const _linlsqrreport_owner &rhs);
    _linlsqrreport_owner& operator=(const _linlsqrreport_owner &rhs);
    virtual ~_linlsqrreport_owner();
    alglib_impl::linlsqrreport* c_ptr();
    alglib_impl::linlsqrreport* c_ptr() const;
protected:
    alglib_impl::linlsqrreport *p_struct;
};
class linlsqrreport : public _linlsqrreport_owner
{
public:
    linlsqrreport();
    linlsqrreport(const linlsqrreport &rhs);
    linlsqrreport& operator=(const linlsqrreport &rhs);
    virtual ~linlsqrreport();
    ae_int_t &iterationscount;
    ae_int_t &nmv;
    ae_int_t &terminationtype;

};
#endif


}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_LINLSQR) || !defined(AE_PARTIAL_BUILD)
void linlsqrcreatebuf(ae_int_t m,
     ae_int_t n,
     linlsqrstate* state,
     ae_state *_state);
ae_bool linlsqriteration(linlsqrstate* state, ae_state *_state);
void linlsqrsetb(linlsqrstate* state,
     /* Real    */ ae_vector* b,
     ae_state *_state);
void linlsqrsetcond(linlsqrstate* state,
     double epsa,
     double epsb,
     ae_int_t maxits,
     ae_state *_state);
void linlsqrresults(linlsqrstate* state,
     /* Real    */ ae_vector* x,
     linlsqrreport* rep,
     ae_state *_state);
void _linlsqrstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
void _linlsqrreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
void _linlsqrreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _linlsqrreport_clear(void* _p);
void _linlsqrreport_destroy(void* _p);
#endif



}
#endif

