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
#ifndef _interpolation_pkg_h
#define _interpolation_pkg_h
#include "solvers.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_SPLINE1D) || !defined(AE_PARTIAL_BUILD)
typedef struct
{
    ae_bool periodic;
    ae_int_t n;
    ae_int_t k;
    ae_int_t continuity;
    ae_vector x;
    ae_vector c;
} spline1dinterpolant;
typedef struct
{
    double taskrcond;
    double rmserror;
    double avgerror;
    double avgrelerror;
    double maxerror;
} spline1dfitreport;
#endif
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{
    #if defined(AE_COMPILE_SPLINE1D) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
1-dimensional spline interpolant
*************************************************************************/
class _spline1dinterpolant_owner
{
public:
    _spline1dinterpolant_owner();
    _spline1dinterpolant_owner(const _spline1dinterpolant_owner &rhs);
    _spline1dinterpolant_owner& operator=(const _spline1dinterpolant_owner &rhs);
    virtual ~_spline1dinterpolant_owner();
    alglib_impl::spline1dinterpolant* c_ptr();
    alglib_impl::spline1dinterpolant* c_ptr() const;
protected:
    alglib_impl::spline1dinterpolant *p_struct;
};
class spline1dinterpolant : public _spline1dinterpolant_owner
{
public:
    spline1dinterpolant();
    spline1dinterpolant(const spline1dinterpolant &rhs);
    spline1dinterpolant& operator=(const spline1dinterpolant &rhs);
    virtual ~spline1dinterpolant();

};


/*************************************************************************
Spline fitting report:
    RMSError        RMS error
    AvgError        average error
    AvgRelError     average relative error (for non-zero Y[I])
    MaxError        maximum error

Fields  below are  filled  by   obsolete    functions   (Spline1DFitCubic,
Spline1DFitHermite). Modern fitting functions do NOT fill these fields:
    TaskRCond       reciprocal of task's condition number
*************************************************************************/
class _spline1dfitreport_owner
{
public:
    _spline1dfitreport_owner();
    _spline1dfitreport_owner(const _spline1dfitreport_owner &rhs);
    _spline1dfitreport_owner& operator=(const _spline1dfitreport_owner &rhs);
    virtual ~_spline1dfitreport_owner();
    alglib_impl::spline1dfitreport* c_ptr();
    alglib_impl::spline1dfitreport* c_ptr() const;
protected:
    alglib_impl::spline1dfitreport *p_struct;
};
class spline1dfitreport : public _spline1dfitreport_owner
{
public:
    spline1dfitreport();
    spline1dfitreport(const spline1dfitreport &rhs);
    spline1dfitreport& operator=(const spline1dfitreport &rhs);
    virtual ~spline1dfitreport();
    double &taskrcond;
    double &rmserror;
    double &avgerror;
    double &avgrelerror;
    double &maxerror;

};
#endif

#if defined(AE_COMPILE_SPLINE1D) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
Fitting by smoothing (penalized) cubic spline.

This function approximates N scattered points (some of X[] may be equal to
each other) by cubic spline with M  nodes  at  equidistant  grid  spanning
interval [min(x,xc),max(x,xc)].

The problem is regularized by adding nonlinearity penalty to  usual  least
squares penalty function:

    MERIT_FUNC = F_LS + F_NL

where F_LS is a least squares error  term,  and  F_NL  is  a  nonlinearity
penalty which is roughly proportional to LambdaNS*integral{ S''(x)^2*dx }.
Algorithm applies automatic renormalization of F_NL  which  makes  penalty
term roughly invariant to scaling of X[] and changes in M.

This function is a new edition  of  penalized  regression  spline fitting,
a fast and compact one which needs much less resources that  its  previous
version: just O(maxMN) memory and O(maxMN*log(maxMN)) time.

NOTE: it is OK to run this function with both M<<N and M>>N;  say,  it  is
      possible to process 100 points with 1000-node spline.

INPUT PARAMETERS:
    X           -   points, array[0..N-1].
    Y           -   function values, array[0..N-1].
    N           -   number of points (optional):
                    * N>0
                    * if given, only first N elements of X/Y are processed
                    * if not given, automatically determined from lengths
    M           -   number of basis functions ( = number_of_nodes), M>=4.
    LambdaNS    -   LambdaNS>=0, regularization  constant  passed by user.
                    It penalizes nonlinearity in the regression spline.
                    Possible values to start from are 0.00001, 0.1, 1

OUTPUT PARAMETERS:
    S   -   spline interpolant.
    Rep -   Following fields are set:
            * RMSError      rms error on the (X,Y).
            * AvgError      average error on the (X,Y).
            * AvgRelError   average relative error on the non-zero Y
            * MaxError      maximum error

  -- ALGLIB PROJECT --
     Copyright 27.08.2019 by Bochkanov Sergey
*************************************************************************/
void spline1dfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, const double lambdans, spline1dinterpolant &s, spline1dfitreport &rep, const xparams _xparams = alglib::xdefault);
void spline1dfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, const double lambdans, spline1dinterpolant &s, spline1dfitreport &rep, const xparams _xparams = alglib::xdefault);

/*************************************************************************
This subroutine calculates the value of the spline at the given point X.

INPUT PARAMETERS:
    C   -   spline interpolant
    X   -   point

Result:
    S(x)

  -- ALGLIB PROJECT --
     Copyright 23.06.2007 by Bochkanov Sergey
*************************************************************************/
double spline1dcalc(const spline1dinterpolant &c, const double x, const xparams _xparams = alglib::xdefault);

#endif

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{

#if defined(AE_COMPILE_INTFITSERV) || !defined(AE_PARTIAL_BUILD)
void buildpriorterm1(/* Real    */ ae_vector* xy1,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_int_t modeltype,
     double priorval,
     /* Real    */ ae_matrix* v,
     ae_state *_state);
#endif
    
#if defined(AE_COMPILE_SPLINE1D) || !defined(AE_PARTIAL_BUILD)
void _spline1dinterpolant_init(void* _p, ae_state *_state, ae_bool make_automatic);
void _spline1dinterpolant_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
void _spline1dfitreport_init(void* _p, ae_state *_state, ae_bool make_automatic);
void _spline1dfitreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);

double spline1dcalc(spline1dinterpolant* c, double x, ae_state *_state);

void spline1dfit(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t m,
     double lambdans,
     spline1dinterpolant* s,
     spline1dfitreport* rep,
     ae_state *_state);

void spline1dbuildhermite(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     spline1dinterpolant* c,
     ae_state *_state);

void spline1dbuildcubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     spline1dinterpolant* c,
     ae_state *_state);

void spline1ddiff(spline1dinterpolant* c,
     double x,
     double* s,
     double* ds,
     double* d2s,
     ae_state *_state);

void heapsortdpoints(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     ae_state *_state);

void _spline1dinterpolant_clear(void* _p);
void _spline1dinterpolant_destroy(void* _p);

void _spline1dfitreport_clear(void* _p);
void _spline1dfitreport_destroy(void* _p);
#endif

}


#endif