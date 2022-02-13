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
#include "interpolation.h"

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

#if defined(AE_COMPILE_SPLINE1D) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
1-dimensional spline interpolant
*************************************************************************/
_spline1dinterpolant_owner::_spline1dinterpolant_owner()
{
    jmp_buf _break_jump;
    alglib_impl::ae_state _state;
    
    alglib_impl::ae_state_init(&_state);
    if( setjmp(_break_jump) )
    {
        if( p_struct!=NULL )
        {
            alglib_impl::_spline1dinterpolant_destroy(p_struct);
            alglib_impl::ae_free(p_struct);
        }
        p_struct = NULL;
#if !defined(AE_NO_EXCEPTIONS)
        _ALGLIB_CPP_EXCEPTION(_state.error_msg);
#else
        _ALGLIB_SET_ERROR_FLAG(_state.error_msg);
        return;
#endif
    }
    alglib_impl::ae_state_set_break_jump(&_state, &_break_jump);
    p_struct = NULL;
    p_struct = (alglib_impl::spline1dinterpolant*)alglib_impl::ae_malloc(sizeof(alglib_impl::spline1dinterpolant), &_state);
    memset(p_struct, 0, sizeof(alglib_impl::spline1dinterpolant));
    alglib_impl::_spline1dinterpolant_init(p_struct, &_state, ae_false);
    ae_state_clear(&_state);
}

_spline1dinterpolant_owner::_spline1dinterpolant_owner(const _spline1dinterpolant_owner &rhs)
{
    jmp_buf _break_jump;
    alglib_impl::ae_state _state;
    
    alglib_impl::ae_state_init(&_state);
    if( setjmp(_break_jump) )
    {
        if( p_struct!=NULL )
        {
            alglib_impl::_spline1dinterpolant_destroy(p_struct);
            alglib_impl::ae_free(p_struct);
        }
        p_struct = NULL;
#if !defined(AE_NO_EXCEPTIONS)
        _ALGLIB_CPP_EXCEPTION(_state.error_msg);
#else
        _ALGLIB_SET_ERROR_FLAG(_state.error_msg);
        return;
#endif
    }
    alglib_impl::ae_state_set_break_jump(&_state, &_break_jump);
    p_struct = NULL;
    alglib_impl::ae_assert(rhs.p_struct!=NULL, "ALGLIB: spline1dinterpolant copy constructor failure (source is not initialized)", &_state);
    p_struct = (alglib_impl::spline1dinterpolant*)alglib_impl::ae_malloc(sizeof(alglib_impl::spline1dinterpolant), &_state);
    memset(p_struct, 0, sizeof(alglib_impl::spline1dinterpolant));
    alglib_impl::_spline1dinterpolant_init_copy(p_struct, const_cast<alglib_impl::spline1dinterpolant*>(rhs.p_struct), &_state, ae_false);
    ae_state_clear(&_state);
}

_spline1dinterpolant_owner& _spline1dinterpolant_owner::operator=(const _spline1dinterpolant_owner &rhs)
{
    if( this==&rhs )
        return *this;
    jmp_buf _break_jump;
    alglib_impl::ae_state _state;
    
    alglib_impl::ae_state_init(&_state);
    if( setjmp(_break_jump) )
    {
#if !defined(AE_NO_EXCEPTIONS)
        _ALGLIB_CPP_EXCEPTION(_state.error_msg);
#else
        _ALGLIB_SET_ERROR_FLAG(_state.error_msg);
        return *this;
#endif
    }
    alglib_impl::ae_state_set_break_jump(&_state, &_break_jump);
    alglib_impl::ae_assert(p_struct!=NULL, "ALGLIB: spline1dinterpolant assignment constructor failure (destination is not initialized)", &_state);
    alglib_impl::ae_assert(rhs.p_struct!=NULL, "ALGLIB: spline1dinterpolant assignment constructor failure (source is not initialized)", &_state);
    alglib_impl::_spline1dinterpolant_destroy(p_struct);
    memset(p_struct, 0, sizeof(alglib_impl::spline1dinterpolant));
    alglib_impl::_spline1dinterpolant_init_copy(p_struct, const_cast<alglib_impl::spline1dinterpolant*>(rhs.p_struct), &_state, ae_false);
    ae_state_clear(&_state);
    return *this;
}

_spline1dinterpolant_owner::~_spline1dinterpolant_owner()
{
    if( p_struct!=NULL )
    {
        alglib_impl::_spline1dinterpolant_destroy(p_struct);
        ae_free(p_struct);
    }
}

alglib_impl::spline1dinterpolant* _spline1dinterpolant_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::spline1dinterpolant* _spline1dinterpolant_owner::c_ptr() const
{
    return const_cast<alglib_impl::spline1dinterpolant*>(p_struct);
}
spline1dinterpolant::spline1dinterpolant() : _spline1dinterpolant_owner() 
{
}

spline1dinterpolant::spline1dinterpolant(const spline1dinterpolant &rhs):_spline1dinterpolant_owner(rhs) 
{
}

spline1dinterpolant& spline1dinterpolant::operator=(const spline1dinterpolant &rhs)
{
    if( this==&rhs )
        return *this;
    _spline1dinterpolant_owner::operator=(rhs);
    return *this;
}

spline1dinterpolant::~spline1dinterpolant()
{
}


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
_spline1dfitreport_owner::_spline1dfitreport_owner()
{
    jmp_buf _break_jump;
    alglib_impl::ae_state _state;
    
    alglib_impl::ae_state_init(&_state);
    if( setjmp(_break_jump) )
    {
        if( p_struct!=NULL )
        {
            alglib_impl::_spline1dfitreport_destroy(p_struct);
            alglib_impl::ae_free(p_struct);
        }
        p_struct = NULL;
#if !defined(AE_NO_EXCEPTIONS)
        _ALGLIB_CPP_EXCEPTION(_state.error_msg);
#else
        _ALGLIB_SET_ERROR_FLAG(_state.error_msg);
        return;
#endif
    }
    alglib_impl::ae_state_set_break_jump(&_state, &_break_jump);
    p_struct = NULL;
    p_struct = (alglib_impl::spline1dfitreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::spline1dfitreport), &_state);
    memset(p_struct, 0, sizeof(alglib_impl::spline1dfitreport));
    alglib_impl::_spline1dfitreport_init(p_struct, &_state, ae_false);
    ae_state_clear(&_state);
}

_spline1dfitreport_owner::_spline1dfitreport_owner(const _spline1dfitreport_owner &rhs)
{
    jmp_buf _break_jump;
    alglib_impl::ae_state _state;
    
    alglib_impl::ae_state_init(&_state);
    if( setjmp(_break_jump) )
    {
        if( p_struct!=NULL )
        {
            alglib_impl::_spline1dfitreport_destroy(p_struct);
            alglib_impl::ae_free(p_struct);
        }
        p_struct = NULL;
#if !defined(AE_NO_EXCEPTIONS)
        _ALGLIB_CPP_EXCEPTION(_state.error_msg);
#else
        _ALGLIB_SET_ERROR_FLAG(_state.error_msg);
        return;
#endif
    }
    alglib_impl::ae_state_set_break_jump(&_state, &_break_jump);
    p_struct = NULL;
    alglib_impl::ae_assert(rhs.p_struct!=NULL, "ALGLIB: spline1dfitreport copy constructor failure (source is not initialized)", &_state);
    p_struct = (alglib_impl::spline1dfitreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::spline1dfitreport), &_state);
    memset(p_struct, 0, sizeof(alglib_impl::spline1dfitreport));
    alglib_impl::_spline1dfitreport_init_copy(p_struct, const_cast<alglib_impl::spline1dfitreport*>(rhs.p_struct), &_state, ae_false);
    ae_state_clear(&_state);
}

_spline1dfitreport_owner& _spline1dfitreport_owner::operator=(const _spline1dfitreport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    jmp_buf _break_jump;
    alglib_impl::ae_state _state;
    
    alglib_impl::ae_state_init(&_state);
    if( setjmp(_break_jump) )
    {
#if !defined(AE_NO_EXCEPTIONS)
        _ALGLIB_CPP_EXCEPTION(_state.error_msg);
#else
        _ALGLIB_SET_ERROR_FLAG(_state.error_msg);
        return *this;
#endif
    }
    alglib_impl::ae_state_set_break_jump(&_state, &_break_jump);
    alglib_impl::ae_assert(p_struct!=NULL, "ALGLIB: spline1dfitreport assignment constructor failure (destination is not initialized)", &_state);
    alglib_impl::ae_assert(rhs.p_struct!=NULL, "ALGLIB: spline1dfitreport assignment constructor failure (source is not initialized)", &_state);
    alglib_impl::_spline1dfitreport_destroy(p_struct);
    memset(p_struct, 0, sizeof(alglib_impl::spline1dfitreport));
    alglib_impl::_spline1dfitreport_init_copy(p_struct, const_cast<alglib_impl::spline1dfitreport*>(rhs.p_struct), &_state, ae_false);
    ae_state_clear(&_state);
    return *this;
}

_spline1dfitreport_owner::~_spline1dfitreport_owner()
{
    if( p_struct!=NULL )
    {
        alglib_impl::_spline1dfitreport_destroy(p_struct);
        ae_free(p_struct);
    }
}

alglib_impl::spline1dfitreport* _spline1dfitreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::spline1dfitreport* _spline1dfitreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::spline1dfitreport*>(p_struct);
}
spline1dfitreport::spline1dfitreport() : _spline1dfitreport_owner() ,taskrcond(p_struct->taskrcond),rmserror(p_struct->rmserror),avgerror(p_struct->avgerror),avgrelerror(p_struct->avgrelerror),maxerror(p_struct->maxerror)
{
}

spline1dfitreport::spline1dfitreport(const spline1dfitreport &rhs):_spline1dfitreport_owner(rhs) ,taskrcond(p_struct->taskrcond),rmserror(p_struct->rmserror),avgerror(p_struct->avgerror),avgrelerror(p_struct->avgrelerror),maxerror(p_struct->maxerror)
{
}

spline1dfitreport& spline1dfitreport::operator=(const spline1dfitreport &rhs)
{
    if( this==&rhs )
        return *this;
    _spline1dfitreport_owner::operator=(rhs);
    return *this;
}

spline1dfitreport::~spline1dfitreport()
{
}


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
double spline1dcalc(const spline1dinterpolant &c, const double x, const xparams _xparams)
{
    jmp_buf _break_jump;
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    if( setjmp(_break_jump) )
    {
#if !defined(AE_NO_EXCEPTIONS)
        _ALGLIB_CPP_EXCEPTION(_alglib_env_state.error_msg);
#else
        _ALGLIB_SET_ERROR_FLAG(_alglib_env_state.error_msg);
        return 0;
#endif
    }
    ae_state_set_break_jump(&_alglib_env_state, &_break_jump);
    if( _xparams.flags!=0x0 )
        ae_state_set_flags(&_alglib_env_state, _xparams.flags);
    double result = alglib_impl::spline1dcalc(const_cast<alglib_impl::spline1dinterpolant*>(c.c_ptr()), x, &_alglib_env_state);
    alglib_impl::ae_state_clear(&_alglib_env_state);
    return *(reinterpret_cast<double*>(&result));
}

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
void spline1dfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, const double lambdans, spline1dinterpolant &s, spline1dfitreport &rep, const xparams _xparams)
{
    jmp_buf _break_jump;
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    if( setjmp(_break_jump) )
    {
#if !defined(AE_NO_EXCEPTIONS)
        _ALGLIB_CPP_EXCEPTION(_alglib_env_state.error_msg);
#else
        _ALGLIB_SET_ERROR_FLAG(_alglib_env_state.error_msg);
        return;
#endif
    }
    ae_state_set_break_jump(&_alglib_env_state, &_break_jump);
    if( _xparams.flags!=0x0 )
        ae_state_set_flags(&_alglib_env_state, _xparams.flags);
    alglib_impl::spline1dfit(const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::ae_vector*>(y.c_ptr()), n, m, lambdans, const_cast<alglib_impl::spline1dinterpolant*>(s.c_ptr()), const_cast<alglib_impl::spline1dfitreport*>(rep.c_ptr()), &_alglib_env_state);
    alglib_impl::ae_state_clear(&_alglib_env_state);
    return;
}

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
#if !defined(AE_NO_EXCEPTIONS)
void spline1dfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, const double lambdans, spline1dinterpolant &s, spline1dfitreport &rep, const xparams _xparams)
{
    jmp_buf _break_jump;
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;
    if( (x.length()!=y.length()))
        _ALGLIB_CPP_EXCEPTION("Error while calling 'spline1dfit': looks like one of arguments has wrong size");
    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    if( setjmp(_break_jump) )
        _ALGLIB_CPP_EXCEPTION(_alglib_env_state.error_msg);
    ae_state_set_break_jump(&_alglib_env_state, &_break_jump);
    if( _xparams.flags!=0x0 )
        ae_state_set_flags(&_alglib_env_state, _xparams.flags);
    alglib_impl::spline1dfit(const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::ae_vector*>(y.c_ptr()), n, m, lambdans, const_cast<alglib_impl::spline1dinterpolant*>(s.c_ptr()), const_cast<alglib_impl::spline1dfitreport*>(rep.c_ptr()), &_alglib_env_state);

    alglib_impl::ae_state_clear(&_alglib_env_state);
    return;
}
#endif

#endif

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS IMPLEMENTATION OF COMPUTATIONAL CORE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{

#if defined(AE_COMPILE_SPLINE1D) || !defined(AE_PARTIAL_BUILD)
static double spline1d_lambdareg = 1.0e-9;
static double spline1d_cholreg = 1.0e-12;
static void spline1d_spline1dgriddiffcubicinternal(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_vector* a1,
     /* Real    */ ae_vector* a2,
     /* Real    */ ae_vector* a3,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* dt,
     ae_state *_state);
static void spline1d_heapsortppoints(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     ae_state *_state);
static void spline1d_solvetridiagonal(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* c,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     ae_state *_state);
static void spline1d_solvecyclictridiagonal(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* c,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     ae_state *_state);
#endif

#if defined(AE_COMPILE_INTFITSERV) || !defined(AE_PARTIAL_BUILD)
void buildpriorterm1(/* Real    */ ae_vector* xy1,
     ae_int_t n,
     ae_int_t nx,
     ae_int_t ny,
     ae_int_t modeltype,
     double priorval,
     /* Real    */ ae_matrix* v,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_int_t i;
    ae_int_t j;
    ae_int_t j0;
    ae_int_t j1;
    ae_int_t ew;
    double rj;
    ae_matrix araw;
    ae_matrix amod;
    ae_matrix braw;
    ae_vector tmp0;
    double lambdareg;
    ae_int_t rfsits;

    ae_frame_make(_state, &_frame_block);
    memset(&araw, 0, sizeof(araw));
    memset(&amod, 0, sizeof(amod));
    memset(&braw, 0, sizeof(braw));
    memset(&tmp0, 0, sizeof(tmp0));
    ae_matrix_clear(v);
    ae_matrix_init(&araw, 0, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&amod, 0, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&braw, 0, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tmp0, 0, DT_REAL, _state, ae_true);

    ae_assert(n>=0, "BuildPriorTerm: N<0", _state);
    ae_assert(nx>0, "BuildPriorTerm: NX<=0", _state);
    ae_assert(ny>0, "BuildPriorTerm: NY<=0", _state);
    ew = nx+ny;
    ae_matrix_set_length(v, ny, nx+1, _state);
    for(i=0; i<=v->rows-1; i++)
    {
        for(j=0; j<=v->cols-1; j++)
        {
            v->ptr.pp_double[i][j] = (double)(0);
        }
    }
    if( n==0 )
    {
        if( modeltype==0 )
        {
            for(i=0; i<=ny-1; i++)
            {
                v->ptr.pp_double[i][nx] = priorval;
            }
            ae_frame_leave(_state);
            return;
        }
        if( modeltype==1 )
        {
            ae_frame_leave(_state);
            return;
        }
        if( modeltype==2 )
        {
            ae_frame_leave(_state);
            return;
        }
        if( modeltype==3 )
        {
            ae_frame_leave(_state);
            return;
        }
        ae_assert(ae_false, "BuildPriorTerm: unexpected model type", _state);
    }
    if( modeltype==0 )
    {
        for(i=0; i<=ny-1; i++)
        {
            v->ptr.pp_double[i][nx] = priorval;
        }
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=ny-1; j++)
            {
                xy1->ptr.p_double[i*ew+nx+j] = xy1->ptr.p_double[i*ew+nx+j]-priorval;
            }
        }
        ae_frame_leave(_state);
        return;
    }
    if( modeltype==2 )
    {
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=ny-1; j++)
            {
                v->ptr.pp_double[j][nx] = v->ptr.pp_double[j][nx]+xy1->ptr.p_double[i*ew+nx+j];
            }
        }
        for(j=0; j<=ny-1; j++)
        {
            v->ptr.pp_double[j][nx] = v->ptr.pp_double[j][nx]/coalesce((double)(n), (double)(1), _state);
        }
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=ny-1; j++)
            {
                xy1->ptr.p_double[i*ew+nx+j] = xy1->ptr.p_double[i*ew+nx+j]-v->ptr.pp_double[j][nx];
            }
        }
        ae_frame_leave(_state);
        return;
    }
    if( modeltype==3 )
    {
        ae_frame_leave(_state);
        return;
    }
    ae_assert(modeltype==1, "BuildPriorTerm: unexpected model type", _state);
    lambdareg = 0.0;
    ae_matrix_set_length(&araw, nx+1, nx+1, _state);
    ae_matrix_set_length(&braw, nx+1, ny, _state);
    ae_vector_set_length(&tmp0, nx+1, _state);
    ae_matrix_set_length(&amod, nx+1, nx+1, _state);
    for(i=0; i<=nx; i++)
    {
        for(j=0; j<=nx; j++)
        {
            araw.ptr.pp_double[i][j] = (double)(0);
        }
    }
    for(i=0; i<=n-1; i++)
    {
        for(j=0; j<=nx-1; j++)
        {
            tmp0.ptr.p_double[j] = xy1->ptr.p_double[i*ew+j];
        }
        tmp0.ptr.p_double[nx] = 1.0;
        for(j0=0; j0<=nx; j0++)
        {
            for(j1=0; j1<=nx; j1++)
            {
                araw.ptr.pp_double[j0][j1] = araw.ptr.pp_double[j0][j1]+tmp0.ptr.p_double[j0]*tmp0.ptr.p_double[j1];
            }
        }
    }
    for(rfsits=1; rfsits<=3; rfsits++)
    {
        for(i=0; i<=nx; i++)
        {
            for(j=0; j<=ny-1; j++)
            {
                braw.ptr.pp_double[i][j] = (double)(0);
            }
        }
        for(i=0; i<=n-1; i++)
        {
            for(j=0; j<=nx-1; j++)
            {
                tmp0.ptr.p_double[j] = xy1->ptr.p_double[i*ew+j];
            }
            tmp0.ptr.p_double[nx] = 1.0;
            for(j=0; j<=ny-1; j++)
            {
                rj = xy1->ptr.p_double[i*ew+nx+j];
                for(j0=0; j0<=nx; j0++)
                {
                    rj = rj-tmp0.ptr.p_double[j0]*v->ptr.pp_double[j][j0];
                }
                for(j0=0; j0<=nx; j0++)
                {
                    braw.ptr.pp_double[j0][j] = braw.ptr.pp_double[j0][j]+rj*tmp0.ptr.p_double[j0];
                }
            }
        }
        for(;;)
        {
            for(i=0; i<=nx; i++)
            {
                for(j=0; j<=nx; j++)
                {
                    amod.ptr.pp_double[i][j] = araw.ptr.pp_double[i][j];
                }
                amod.ptr.pp_double[i][i] = amod.ptr.pp_double[i][i]+lambdareg*coalesce(amod.ptr.pp_double[i][i], (double)(1), _state);
            }
            if( spdmatrixcholesky(&amod, nx+1, ae_true, _state) )
            {
                break;
            }
            lambdareg = coalesce(10*lambdareg, 1.0E-12, _state);
        }
        rmatrixlefttrsm(nx+1, ny, &amod, 0, 0, ae_true, ae_false, 1, &braw, 0, 0, _state);
        rmatrixlefttrsm(nx+1, ny, &amod, 0, 0, ae_true, ae_false, 0, &braw, 0, 0, _state);
        for(i=0; i<=nx; i++)
        {
            for(j=0; j<=ny-1; j++)
            {
                v->ptr.pp_double[j][i] = v->ptr.pp_double[j][i]+braw.ptr.pp_double[i][j];
            }
        }
    }
    for(i=0; i<=n-1; i++)
    {
        for(j=0; j<=nx-1; j++)
        {
            tmp0.ptr.p_double[j] = xy1->ptr.p_double[i*ew+j];
        }
        tmp0.ptr.p_double[nx] = 1.0;
        for(j=0; j<=ny-1; j++)
        {
            rj = 0.0;
            for(j0=0; j0<=nx; j0++)
            {
                rj = rj+tmp0.ptr.p_double[j0]*v->ptr.pp_double[j][j0];
            }
            xy1->ptr.p_double[i*ew+nx+j] = xy1->ptr.p_double[i*ew+nx+j]-rj;
        }
    }
    ae_frame_leave(_state);
}


#endif
    
#if defined(AE_COMPILE_SPLINE1D) || !defined(AE_PARTIAL_BUILD)
void _spline1dinterpolant_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    spline1dinterpolant *p = (spline1dinterpolant*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->c, 0, DT_REAL, _state, make_automatic);
}

void _spline1dinterpolant_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    spline1dinterpolant *dst = (spline1dinterpolant*)_dst;
    spline1dinterpolant *src = (spline1dinterpolant*)_src;
    dst->periodic = src->periodic;
    dst->n = src->n;
    dst->k = src->k;
    dst->continuity = src->continuity;
    ae_vector_init_copy(&dst->x, &src->x, _state, make_automatic);
    ae_vector_init_copy(&dst->c, &src->c, _state, make_automatic);
}

void _spline1dfitreport_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    spline1dfitreport *p = (spline1dfitreport*)_p;
    ae_touch_ptr((void*)p);
}


void _spline1dfitreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    spline1dfitreport *dst = (spline1dfitreport*)_dst;
    spline1dfitreport *src = (spline1dfitreport*)_src;
    dst->taskrcond = src->taskrcond;
    dst->rmserror = src->rmserror;
    dst->avgerror = src->avgerror;
    dst->avgrelerror = src->avgrelerror;
    dst->maxerror = src->maxerror;
}

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
double spline1dcalc(spline1dinterpolant* c, double x, ae_state *_state)
{
    ae_int_t l;
    ae_int_t r;
    ae_int_t m;
    double t;
    double result;


    ae_assert(c->k==3, "Spline1DCalc: internal error", _state);
    ae_assert(!ae_isinf(x, _state), "Spline1DCalc: infinite X!", _state);
    
    /*
     * special case: NaN
     */
    if( ae_isnan(x, _state) )
    {
        result = _state->v_nan;
        return result;
    }
    
    /*
     * correct if periodic
     */
    if( c->periodic )
    {
        apperiodicmap(&x, c->x.ptr.p_double[0], c->x.ptr.p_double[c->n-1], &t, _state);
    }
    
    /*
     * Binary search in the [ x[0], ..., x[n-2] ] (x[n-1] is not included)
     */
    l = 0;
    r = c->n-2+1;
    while(l!=r-1)
    {
        m = (l+r)/2;
        if( c->x.ptr.p_double[m]>=x )
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }
    
    /*
     * Interpolation
     */
    x = x-c->x.ptr.p_double[l];
    m = 4*l;
    result = c->c.ptr.p_double[m]+x*(c->c.ptr.p_double[m+1]+x*(c->c.ptr.p_double[m+2]+x*c->c.ptr.p_double[m+3]));
    return result;
}


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
void spline1dfit(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t m,
     double lambdans,
     spline1dinterpolant* s,
     spline1dfitreport* rep,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector _x;
    ae_vector _y;
    ae_int_t bfrad;
    double xa;
    double xb;
    ae_int_t i;
    ae_int_t j;
    ae_int_t k;
    ae_int_t k0;
    ae_int_t k1;
    double v;
    double dv;
    double d2v;
    ae_int_t gridexpansion;
    ae_vector xywork;
    ae_matrix vterm;
    ae_vector sx;
    ae_vector sy;
    ae_vector sdy;
    ae_vector tmpx;
    ae_vector tmpy;
    spline1dinterpolant basis1;
    sparsematrix av;
    sparsematrix ah;
    sparsematrix ata;
    ae_vector targets;
    double meany;
    ae_int_t lsqrcnt;
    ae_int_t nrel;
    double rss;
    double tss;
    ae_int_t arows;
    ae_vector tmp0;
    ae_vector tmp1;
    linlsqrstate solver;
    linlsqrreport srep;
    double creg;
    double mxata;
    ae_int_t bw;
    ae_vector nzidx;
    ae_vector nzval;
    ae_int_t nzcnt;
    double scaletargetsby;
    double scalepenaltyby;

    ae_frame_make(_state, &_frame_block);
    memset(&_x, 0, sizeof(_x));
    memset(&_y, 0, sizeof(_y));
    memset(&xywork, 0, sizeof(xywork));
    memset(&vterm, 0, sizeof(vterm));
    memset(&sx, 0, sizeof(sx));
    memset(&sy, 0, sizeof(sy));
    memset(&sdy, 0, sizeof(sdy));
    memset(&tmpx, 0, sizeof(tmpx));
    memset(&tmpy, 0, sizeof(tmpy));
    memset(&basis1, 0, sizeof(basis1));
    memset(&av, 0, sizeof(av));
    memset(&ah, 0, sizeof(ah));
    memset(&ata, 0, sizeof(ata));
    memset(&targets, 0, sizeof(targets));
    memset(&tmp0, 0, sizeof(tmp0));
    memset(&tmp1, 0, sizeof(tmp1));
    memset(&solver, 0, sizeof(solver));
    memset(&srep, 0, sizeof(srep));
    memset(&nzidx, 0, sizeof(nzidx));
    memset(&nzval, 0, sizeof(nzval));
    ae_vector_init_copy(&_x, x, _state, ae_true);
    x = &_x;
    ae_vector_init_copy(&_y, y, _state, ae_true);
    y = &_y;
    _spline1dinterpolant_clear(s);
    _spline1dfitreport_clear(rep);
    ae_vector_init(&xywork, 0, DT_REAL, _state, ae_true);
    ae_matrix_init(&vterm, 0, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&sx, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&sy, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&sdy, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tmpx, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tmpy, 0, DT_REAL, _state, ae_true);
    _spline1dinterpolant_init(&basis1, _state, ae_true);
    _sparsematrix_init(&av, _state, ae_true);
    _sparsematrix_init(&ah, _state, ae_true);
    _sparsematrix_init(&ata, _state, ae_true);
    ae_vector_init(&targets, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tmp0, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&tmp1, 0, DT_REAL, _state, ae_true);
    _linlsqrstate_init(&solver, _state, ae_true);
    _linlsqrreport_init(&srep, _state, ae_true);
    ae_vector_init(&nzidx, 0, DT_INT, _state, ae_true);
    ae_vector_init(&nzval, 0, DT_REAL, _state, ae_true);

    ae_assert(n>=1, "Spline1DFit: N<1!", _state);
    ae_assert(m>=1, "Spline1DFit: M<1!", _state);
    ae_assert(x->cnt>=n, "Spline1DFit: Length(X)<N!", _state);
    ae_assert(y->cnt>=n, "Spline1DFit: Length(Y)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "Spline1DFit: X contains infinite or NAN values!", _state);
    ae_assert(isfinitevector(y, n, _state), "Spline1DFit: Y contains infinite or NAN values!", _state);
    ae_assert(ae_isfinite(lambdans, _state), "Spline1DFit: LambdaNS is infinite!", _state);
    ae_assert(ae_fp_greater_eq(lambdans,(double)(0)), "Spline1DFit: LambdaNS<0!", _state);
    bfrad = 2;
    lsqrcnt = 10;
    
    /*
     * Sort points.
     * Determine actual area size, make sure that XA<XB
     */
    tagsortfastr(x, y, &tmpx, &tmpy, n, _state);
    xa = x->ptr.p_double[0];
    xb = x->ptr.p_double[n-1];
    if( ae_fp_eq(xa,xb) )
    {
        v = xa;
        if( ae_fp_greater_eq(v,(double)(0)) )
        {
            xa = v/2-1;
            xb = v*2+1;
        }
        else
        {
            xa = v*2-1;
            xb = v/2+1;
        }
    }
    ae_assert(ae_fp_less(xa,xb), "Spline1DFit: integrity error", _state);
    
    /*
     * Perform a grid correction according to current grid expansion size.
     */
    m = ae_maxint(m, 4, _state);
    gridexpansion = 1;
    v = (xb-xa)/m;
    xa = xa-v*gridexpansion;
    xb = xb+v*gridexpansion;
    m = m+2*gridexpansion;
    
    /*
     * Convert X/Y to work representation, remove linear trend (in
     * order to improve condition number).
     *
     * Compute total-sum-of-squares (needed later for R2 coefficient).
     */
    ae_vector_set_length(&xywork, 2*n, _state);
    for(i=0; i<=n-1; i++)
    {
        xywork.ptr.p_double[2*i+0] = (x->ptr.p_double[i]-xa)/(xb-xa);
        xywork.ptr.p_double[2*i+1] = y->ptr.p_double[i];
    }
    buildpriorterm1(&xywork, n, 1, 1, 1, 0.0, &vterm, _state);
    meany = (double)(0);
    for(i=0; i<=n-1; i++)
    {
        meany = meany+y->ptr.p_double[i];
    }
    meany = meany/n;
    tss = (double)(0);
    for(i=0; i<=n-1; i++)
    {
        tss = tss+ae_sqr(y->ptr.p_double[i]-meany, _state);
    }
    
    /*
     * Build 1D compact basis function
     * Generate design matrix AV ("vertical") and its transpose AH ("horizontal").
     */
    ae_vector_set_length(&tmpx, 7, _state);
    ae_vector_set_length(&tmpy, 7, _state);
    tmpx.ptr.p_double[0] = -(double)3/(double)(m-1);
    tmpx.ptr.p_double[1] = -(double)2/(double)(m-1);
    tmpx.ptr.p_double[2] = -(double)1/(double)(m-1);
    tmpx.ptr.p_double[3] = (double)0/(double)(m-1);
    tmpx.ptr.p_double[4] = (double)1/(double)(m-1);
    tmpx.ptr.p_double[5] = (double)2/(double)(m-1);
    tmpx.ptr.p_double[6] = (double)3/(double)(m-1);
    tmpy.ptr.p_double[0] = (double)(0);
    tmpy.ptr.p_double[1] = (double)(0);
    tmpy.ptr.p_double[2] = (double)1/(double)12;
    tmpy.ptr.p_double[3] = (double)2/(double)6;
    tmpy.ptr.p_double[4] = (double)1/(double)12;
    tmpy.ptr.p_double[5] = (double)(0);
    tmpy.ptr.p_double[6] = (double)(0);
    spline1dbuildcubic(&tmpx, &tmpy, tmpx.cnt, 2, 0.0, 2, 0.0, &basis1, _state);
    arows = n+2*m;
    sparsecreate(arows, m, 0, &av, _state);
    setlengthzero(&targets, arows, _state);
    scaletargetsby = 1/ae_sqrt((double)(n), _state);
    scalepenaltyby = 1/ae_sqrt((double)(m), _state);
    for(i=0; i<=n-1; i++)
    {
        
        /*
         * Generate design matrix row #I which corresponds to I-th dataset point
         */
        k = ae_ifloor(boundval(xywork.ptr.p_double[2*i+0]*(m-1), (double)(0), (double)(m-1), _state), _state);
        k0 = ae_maxint(k-(bfrad-1), 0, _state);
        k1 = ae_minint(k+bfrad, m-1, _state);
        for(j=k0; j<=k1; j++)
        {
            sparseset(&av, i, j, spline1dcalc(&basis1, xywork.ptr.p_double[2*i+0]-(double)j/(double)(m-1), _state)*scaletargetsby, _state);
        }
        targets.ptr.p_double[i] = xywork.ptr.p_double[2*i+1]*scaletargetsby;
    }
    for(i=0; i<=m-1; i++)
    {
        
        /*
         * Generate design matrix row #(I+N) which corresponds to nonlinearity penalty at I-th node
         */
        k0 = ae_maxint(i-(bfrad-1), 0, _state);
        k1 = ae_minint(i+(bfrad-1), m-1, _state);
        for(j=k0; j<=k1; j++)
        {
            spline1ddiff(&basis1, (double)i/(double)(m-1)-(double)j/(double)(m-1), &v, &dv, &d2v, _state);
            sparseset(&av, n+i, j, lambdans*d2v*scalepenaltyby, _state);
        }
    }
    for(i=0; i<=m-1; i++)
    {
        
        /*
         * Generate design matrix row #(I+N+M) which corresponds to regularization for I-th coefficient
         */
        sparseset(&av, n+m+i, i, spline1d_lambdareg, _state);
    }
    sparseconverttocrs(&av, _state);
    sparsecopytransposecrs(&av, &ah, _state);
    
    /*
     * Build 7-diagonal (bandwidth=3) normal equations matrix and perform Cholesky
     * decomposition (to be used later as preconditioner for LSQR iterations).
     */
    bw = 3;
    sparsecreatesksband(m, m, bw, &ata, _state);
    mxata = (double)(0);
    for(i=0; i<=m-1; i++)
    {
        for(j=i; j<=ae_minint(i+bw, m-1, _state); j++)
        {
            
            /*
             * Get pattern of nonzeros in one of the rows (let it be I-th one)
             * and compute dot product only for nonzero entries.
             */
            sparsegetcompressedrow(&ah, i, &nzidx, &nzval, &nzcnt, _state);
            v = (double)(0);
            for(k=0; k<=nzcnt-1; k++)
            {
                v = v+sparseget(&ah, i, nzidx.ptr.p_int[k], _state)*sparseget(&ah, j, nzidx.ptr.p_int[k], _state);
            }
            
            /*
             * Update ATA and max(ATA)
             */
            sparseset(&ata, i, j, v, _state);
            if( i==j )
            {
                mxata = ae_maxreal(mxata, ae_fabs(v, _state), _state);
            }
        }
    }
    mxata = coalesce(mxata, 1.0, _state);
    creg = spline1d_cholreg;
    for(;;)
    {
        
        /*
         * Regularization
         */
        for(i=0; i<=m-1; i++)
        {
            sparseset(&ata, i, i, sparseget(&ata, i, i, _state)+mxata*creg, _state);
        }
        
        /*
         * Try Cholesky factorization.
         */
        if( !sparsecholeskyskyline(&ata, m, ae_true, _state) )
        {
            
            /*
             * Factorization failed, increase regularizer and repeat
             */
            creg = coalesce(10*creg, 1.0E-12, _state);
            continue;
        }
        break;
    }
    
    /*
     * Solve with preconditioned LSQR:
     *
     * use Cholesky factor U of squared design matrix A'*A to
     * transform min|A*x-b| to min|[A*inv(U)]*y-b| with y=U*x.
     *
     * Preconditioned problem is solved with LSQR solver, which
     * gives superior results to normal equations approach. Due
     * to Cholesky preconditioner being utilized we can solve
     * problem in just a few iterations.
     */
    rvectorsetlengthatleast(&tmp0, arows, _state);
    rvectorsetlengthatleast(&tmp1, m, _state);
    linlsqrcreatebuf(arows, m, &solver, _state);
    linlsqrsetb(&solver, &targets, _state);
    linlsqrsetcond(&solver, 1.0E-14, 1.0E-14, lsqrcnt, _state);
    while(linlsqriteration(&solver, _state))
    {
        if( solver.needmv )
        {
            for(i=0; i<=m-1; i++)
            {
                tmp1.ptr.p_double[i] = solver.x.ptr.p_double[i];
            }
            
            /*
             * Use Cholesky factorization of the system matrix
             * as preconditioner: solve TRSV(U,Solver.X)
             */
            sparsetrsv(&ata, ae_true, ae_false, 0, &tmp1, _state);
            
            /*
             * After preconditioning is done, multiply by A
             */
            sparsemv(&av, &tmp1, &solver.mv, _state);
        }
        if( solver.needmtv )
        {
            
            /*
             * Multiply by design matrix A
             */
            sparsemtv(&av, &solver.x, &solver.mtv, _state);
            
            /*
             * Multiply by preconditioner: solve TRSV(U',A*Solver.X)
             */
            sparsetrsv(&ata, ae_true, ae_false, 1, &solver.mtv, _state);
        }
    }
    linlsqrresults(&solver, &tmp1, &srep, _state);
    sparsetrsv(&ata, ae_true, ae_false, 0, &tmp1, _state);
    
    /*
     * Generate output spline as a table of spline valued and first
     * derivatives at nodes (used to build Hermite spline)
     */
    ae_vector_set_length(&sx, m, _state);
    ae_vector_set_length(&sy, m, _state);
    ae_vector_set_length(&sdy, m, _state);
    for(i=0; i<=m-1; i++)
    {
        sx.ptr.p_double[i] = (double)i/(double)(m-1);
        sy.ptr.p_double[i] = (double)(0);
        sdy.ptr.p_double[i] = (double)(0);
    }
    for(i=0; i<=m-1; i++)
    {
        k0 = ae_maxint(i-(bfrad-1), 0, _state);
        k1 = ae_minint(i+bfrad, m-1, _state);
        for(j=k0; j<=k1; j++)
        {
            spline1ddiff(&basis1, (double)j/(double)(m-1)-(double)i/(double)(m-1), &v, &dv, &d2v, _state);
            sy.ptr.p_double[j] = sy.ptr.p_double[j]+tmp1.ptr.p_double[i]*v;
            sdy.ptr.p_double[j] = sdy.ptr.p_double[j]+tmp1.ptr.p_double[i]*dv;
        }
    }
    
    /*
     * Calculate model values
     */
    sparsemv(&av, &tmp1, &tmp0, _state);
    for(i=0; i<=n-1; i++)
    {
        tmp0.ptr.p_double[i] = tmp0.ptr.p_double[i]/scaletargetsby;
    }
    rss = 0.0;
    nrel = 0;
    rep->rmserror = (double)(0);
    rep->maxerror = (double)(0);
    rep->avgerror = (double)(0);
    rep->avgrelerror = (double)(0);
    for(i=0; i<=n-1; i++)
    {
        v = xywork.ptr.p_double[2*i+1]-tmp0.ptr.p_double[i];
        rss = rss+v*v;
        rep->rmserror = rep->rmserror+ae_sqr(v, _state);
        rep->avgerror = rep->avgerror+ae_fabs(v, _state);
        rep->maxerror = ae_maxreal(rep->maxerror, ae_fabs(v, _state), _state);
        if( ae_fp_neq(y->ptr.p_double[i],(double)(0)) )
        {
            rep->avgrelerror = rep->avgrelerror+ae_fabs(v/y->ptr.p_double[i], _state);
            nrel = nrel+1;
        }
    }
    rep->rmserror = ae_sqrt(rep->rmserror/n, _state);
    rep->avgerror = rep->avgerror/n;
    rep->avgrelerror = rep->avgrelerror/coalesce((double)(nrel), 1.0, _state);
    
    /*
     * Append prior term.
     * Transform spline to original coordinates.
     * Output.
     */
    for(i=0; i<=m-1; i++)
    {
        sy.ptr.p_double[i] = sy.ptr.p_double[i]+vterm.ptr.pp_double[0][0]*sx.ptr.p_double[i]+vterm.ptr.pp_double[0][1];
        sdy.ptr.p_double[i] = sdy.ptr.p_double[i]+vterm.ptr.pp_double[0][0];
    }
    for(i=0; i<=m-1; i++)
    {
        sx.ptr.p_double[i] = sx.ptr.p_double[i]*(xb-xa)+xa;
        sdy.ptr.p_double[i] = sdy.ptr.p_double[i]/(xb-xa);
    }
    spline1dbuildhermite(&sx, &sy, &sdy, m, s, _state);
    ae_frame_leave(_state);
}

/*************************************************************************
This subroutine builds Hermite spline interpolant.

INPUT PARAMETERS:
    X           -   spline nodes, array[0..N-1]
    Y           -   function values, array[0..N-1]
    D           -   derivatives, array[0..N-1]
    N           -   points count (optional):
                    * N>=2
                    * if given, only first N points are used to build spline
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))

OUTPUT PARAMETERS:
    C           -   spline interpolant.


ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.

  -- ALGLIB PROJECT --
     Copyright 23.06.2007 by Bochkanov Sergey
*************************************************************************/
void spline1dbuildhermite(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     spline1dinterpolant* c,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector _x;
    ae_vector _y;
    ae_vector _d;
    ae_int_t i;
    double delta;
    double delta2;
    double delta3;

    ae_frame_make(_state, &_frame_block);
    memset(&_x, 0, sizeof(_x));
    memset(&_y, 0, sizeof(_y));
    memset(&_d, 0, sizeof(_d));
    ae_vector_init_copy(&_x, x, _state, ae_true);
    x = &_x;
    ae_vector_init_copy(&_y, y, _state, ae_true);
    y = &_y;
    ae_vector_init_copy(&_d, d, _state, ae_true);
    d = &_d;
    _spline1dinterpolant_clear(c);

    ae_assert(n>=2, "Spline1DBuildHermite: N<2!", _state);
    ae_assert(x->cnt>=n, "Spline1DBuildHermite: Length(X)<N!", _state);
    ae_assert(y->cnt>=n, "Spline1DBuildHermite: Length(Y)<N!", _state);
    ae_assert(d->cnt>=n, "Spline1DBuildHermite: Length(D)<N!", _state);
    
    /*
     * check and sort points
     */
    ae_assert(isfinitevector(x, n, _state), "Spline1DBuildHermite: X contains infinite or NAN values!", _state);
    ae_assert(isfinitevector(y, n, _state), "Spline1DBuildHermite: Y contains infinite or NAN values!", _state);
    ae_assert(isfinitevector(d, n, _state), "Spline1DBuildHermite: D contains infinite or NAN values!", _state);
    heapsortdpoints(x, y, d, n, _state);
    ae_assert(aredistinct(x, n, _state), "Spline1DBuildHermite: at least two consequent points are too close!", _state);
    
    /*
     * Build
     */
    ae_vector_set_length(&c->x, n, _state);
    ae_vector_set_length(&c->c, 4*(n-1)+2, _state);
    c->periodic = ae_false;
    c->k = 3;
    c->n = n;
    c->continuity = 1;
    for(i=0; i<=n-1; i++)
    {
        c->x.ptr.p_double[i] = x->ptr.p_double[i];
    }
    for(i=0; i<=n-2; i++)
    {
        delta = x->ptr.p_double[i+1]-x->ptr.p_double[i];
        delta2 = ae_sqr(delta, _state);
        delta3 = delta*delta2;
        c->c.ptr.p_double[4*i+0] = y->ptr.p_double[i];
        c->c.ptr.p_double[4*i+1] = d->ptr.p_double[i];
        c->c.ptr.p_double[4*i+2] = (3*(y->ptr.p_double[i+1]-y->ptr.p_double[i])-2*d->ptr.p_double[i]*delta-d->ptr.p_double[i+1]*delta)/delta2;
        c->c.ptr.p_double[4*i+3] = (2*(y->ptr.p_double[i]-y->ptr.p_double[i+1])+d->ptr.p_double[i]*delta+d->ptr.p_double[i+1]*delta)/delta3;
    }
    c->c.ptr.p_double[4*(n-1)+0] = y->ptr.p_double[n-1];
    c->c.ptr.p_double[4*(n-1)+1] = d->ptr.p_double[n-1];
    ae_frame_leave(_state);
}

/*************************************************************************
Internal subroutine. Tridiagonal solver. Solves

( B[0] C[0]                      
( A[1] B[1] C[1]                 )
(      A[2] B[2] C[2]            )
(            ..........          ) * X = D
(            ..........          )
(           A[N-2] B[N-2] C[N-2] )
(                  A[N-1] B[N-1] )

*************************************************************************/
static void spline1d_solvetridiagonal(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* c,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector _b;
    ae_vector _d;
    ae_int_t k;
    double t;

    ae_frame_make(_state, &_frame_block);
    memset(&_b, 0, sizeof(_b));
    memset(&_d, 0, sizeof(_d));
    ae_vector_init_copy(&_b, b, _state, ae_true);
    b = &_b;
    ae_vector_init_copy(&_d, d, _state, ae_true);
    d = &_d;

    if( x->cnt<n )
    {
        ae_vector_set_length(x, n, _state);
    }
    for(k=1; k<=n-1; k++)
    {
        t = a->ptr.p_double[k]/b->ptr.p_double[k-1];
        b->ptr.p_double[k] = b->ptr.p_double[k]-t*c->ptr.p_double[k-1];
        d->ptr.p_double[k] = d->ptr.p_double[k]-t*d->ptr.p_double[k-1];
    }
    x->ptr.p_double[n-1] = d->ptr.p_double[n-1]/b->ptr.p_double[n-1];
    for(k=n-2; k>=0; k--)
    {
        x->ptr.p_double[k] = (d->ptr.p_double[k]-c->ptr.p_double[k]*x->ptr.p_double[k+1])/b->ptr.p_double[k];
    }
    ae_frame_leave(_state);
}

/*************************************************************************
Internal subroutine. Cyclic tridiagonal solver. Solves

( B[0] C[0]                 A[0] )
( A[1] B[1] C[1]                 )
(      A[2] B[2] C[2]            )
(            ..........          ) * X = D
(            ..........          )
(           A[N-2] B[N-2] C[N-2] )
( C[N-1]           A[N-1] B[N-1] )
*************************************************************************/
static void spline1d_solvecyclictridiagonal(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* c,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector _b;
    ae_int_t k;
    double alpha;
    double beta;
    double gamma;
    ae_vector y;
    ae_vector z;
    ae_vector u;

    ae_frame_make(_state, &_frame_block);
    memset(&_b, 0, sizeof(_b));
    memset(&y, 0, sizeof(y));
    memset(&z, 0, sizeof(z));
    memset(&u, 0, sizeof(u));
    ae_vector_init_copy(&_b, b, _state, ae_true);
    b = &_b;
    ae_vector_init(&y, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&z, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&u, 0, DT_REAL, _state, ae_true);

    if( x->cnt<n )
    {
        ae_vector_set_length(x, n, _state);
    }
    beta = a->ptr.p_double[0];
    alpha = c->ptr.p_double[n-1];
    gamma = -b->ptr.p_double[0];
    b->ptr.p_double[0] = 2*b->ptr.p_double[0];
    b->ptr.p_double[n-1] = b->ptr.p_double[n-1]-alpha*beta/gamma;
    ae_vector_set_length(&u, n, _state);
    for(k=0; k<=n-1; k++)
    {
        u.ptr.p_double[k] = (double)(0);
    }
    u.ptr.p_double[0] = gamma;
    u.ptr.p_double[n-1] = alpha;
    spline1d_solvetridiagonal(a, b, c, d, n, &y, _state);
    spline1d_solvetridiagonal(a, b, c, &u, n, &z, _state);
    for(k=0; k<=n-1; k++)
    {
        x->ptr.p_double[k] = y.ptr.p_double[k]-(y.ptr.p_double[0]+beta/gamma*y.ptr.p_double[n-1])/(1+z.ptr.p_double[0]+beta/gamma*z.ptr.p_double[n-1])*z.ptr.p_double[k];
    }
    ae_frame_leave(_state);
}

/*************************************************************************
This subroutine builds cubic spline interpolant.

INPUT PARAMETERS:
    X           -   spline nodes, array[0..N-1].
    Y           -   function values, array[0..N-1].
    
OPTIONAL PARAMETERS:
    N           -   points count:
                    * N>=2
                    * if given, only first N points are used to build spline
                    * if not given, automatically detected from X/Y sizes
                      (len(X) must be equal to len(Y))
    BoundLType  -   boundary condition type for the left boundary
    BoundL      -   left boundary condition (first or second derivative,
                    depending on the BoundLType)
    BoundRType  -   boundary condition type for the right boundary
    BoundR      -   right boundary condition (first or second derivative,
                    depending on the BoundRType)

OUTPUT PARAMETERS:
    C           -   spline interpolant

ORDER OF POINTS

Subroutine automatically sorts points, so caller may pass unsorted array.

SETTING BOUNDARY VALUES:

The BoundLType/BoundRType parameters can have the following values:
    * -1, which corresonds to the periodic (cyclic) boundary conditions.
          In this case:
          * both BoundLType and BoundRType must be equal to -1.
          * BoundL/BoundR are ignored
          * Y[last] is ignored (it is assumed to be equal to Y[first]).
    *  0, which  corresponds  to  the  parabolically   terminated  spline
          (BoundL and/or BoundR are ignored).
    *  1, which corresponds to the first derivative boundary condition
    *  2, which corresponds to the second derivative boundary condition
    *  by default, BoundType=0 is used

PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:

Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
However, this subroutine doesn't require you to specify equal  values  for
the first and last points - it automatically forces them  to  be  equal by
copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
Y[last_point]. However it is recommended to pass consistent values of Y[],
i.e. to make Y[first_point]=Y[last_point].

  -- ALGLIB PROJECT --
     Copyright 23.06.2007 by Bochkanov Sergey
*************************************************************************/
void spline1dbuildcubic(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     spline1dinterpolant* c,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector _x;
    ae_vector _y;
    ae_vector a1;
    ae_vector a2;
    ae_vector a3;
    ae_vector b;
    ae_vector dt;
    ae_vector d;
    ae_vector p;
    ae_int_t ylen;

    ae_frame_make(_state, &_frame_block);
    memset(&_x, 0, sizeof(_x));
    memset(&_y, 0, sizeof(_y));
    memset(&a1, 0, sizeof(a1));
    memset(&a2, 0, sizeof(a2));
    memset(&a3, 0, sizeof(a3));
    memset(&b, 0, sizeof(b));
    memset(&dt, 0, sizeof(dt));
    memset(&d, 0, sizeof(d));
    memset(&p, 0, sizeof(p));
    ae_vector_init_copy(&_x, x, _state, ae_true);
    x = &_x;
    ae_vector_init_copy(&_y, y, _state, ae_true);
    y = &_y;
    _spline1dinterpolant_clear(c);
    ae_vector_init(&a1, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&a2, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&a3, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&b, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&dt, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&d, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&p, 0, DT_INT, _state, ae_true);

    
    /*
     * check correctness of boundary conditions
     */
    ae_assert(((boundltype==-1||boundltype==0)||boundltype==1)||boundltype==2, "Spline1DBuildCubic: incorrect BoundLType!", _state);
    ae_assert(((boundrtype==-1||boundrtype==0)||boundrtype==1)||boundrtype==2, "Spline1DBuildCubic: incorrect BoundRType!", _state);
    ae_assert((boundrtype==-1&&boundltype==-1)||(boundrtype!=-1&&boundltype!=-1), "Spline1DBuildCubic: incorrect BoundLType/BoundRType!", _state);
    if( boundltype==1||boundltype==2 )
    {
        ae_assert(ae_isfinite(boundl, _state), "Spline1DBuildCubic: BoundL is infinite or NAN!", _state);
    }
    if( boundrtype==1||boundrtype==2 )
    {
        ae_assert(ae_isfinite(boundr, _state), "Spline1DBuildCubic: BoundR is infinite or NAN!", _state);
    }
    
    /*
     * check lengths of arguments
     */
    ae_assert(n>=2, "Spline1DBuildCubic: N<2!", _state);
    ae_assert(x->cnt>=n, "Spline1DBuildCubic: Length(X)<N!", _state);
    ae_assert(y->cnt>=n, "Spline1DBuildCubic: Length(Y)<N!", _state);
    
    /*
     * check and sort points
     */
    ylen = n;
    if( boundltype==-1 )
    {
        ylen = n-1;
    }
    ae_assert(isfinitevector(x, n, _state), "Spline1DBuildCubic: X contains infinite or NAN values!", _state);
    ae_assert(isfinitevector(y, ylen, _state), "Spline1DBuildCubic: Y contains infinite or NAN values!", _state);
    spline1d_heapsortppoints(x, y, &p, n, _state);
    ae_assert(aredistinct(x, n, _state), "Spline1DBuildCubic: at least two consequent points are too close!", _state);
    
    /*
     * Now we've checked and preordered everything,
     * so we can call internal function to calculate derivatives,
     * and then build Hermite spline using these derivatives
     */
    if( boundltype==-1||boundrtype==-1 )
    {
        y->ptr.p_double[n-1] = y->ptr.p_double[0];
    }
    spline1d_spline1dgriddiffcubicinternal(x, y, n, boundltype, boundl, boundrtype, boundr, &d, &a1, &a2, &a3, &b, &dt, _state);
    spline1dbuildhermite(x, y, &d, n, c, _state);
    c->periodic = boundltype==-1||boundrtype==-1;
    c->continuity = 2;
    ae_frame_leave(_state);
}


/*************************************************************************
Internal subroutine. Heap sort.

Accepts:
    X, Y    -   points
    P       -   empty or preallocated array
    
Returns:
    X, Y    -   sorted by X
    P       -   array of permutations; I-th position of output
                arrays X/Y contains (X[P[I]],Y[P[I]])
*************************************************************************/
static void spline1d_heapsortppoints(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Integer */ ae_vector* p,
     ae_int_t n,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector rbuf;
    ae_vector ibuf;
    ae_int_t i;

    ae_frame_make(_state, &_frame_block);
    memset(&rbuf, 0, sizeof(rbuf));
    memset(&ibuf, 0, sizeof(ibuf));
    ae_vector_init(&rbuf, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&ibuf, 0, DT_INT, _state, ae_true);

    if( p->cnt<n )
    {
        ae_vector_set_length(p, n, _state);
    }
    ae_vector_set_length(&rbuf, n, _state);
    for(i=0; i<=n-1; i++)
    {
        p->ptr.p_int[i] = i;
    }
    tagsortfasti(x, p, &rbuf, &ibuf, n, _state);
    for(i=0; i<=n-1; i++)
    {
        rbuf.ptr.p_double[i] = y->ptr.p_double[p->ptr.p_int[i]];
    }
    ae_v_move(&y->ptr.p_double[0], 1, &rbuf.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_frame_leave(_state);
}

/*************************************************************************
Internal subroutine. Heap sort.
*************************************************************************/
void heapsortdpoints(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* d,
     ae_int_t n,
     ae_state *_state)
{
    ae_frame _frame_block;
    ae_vector rbuf;
    ae_vector ibuf;
    ae_vector rbuf2;
    ae_vector ibuf2;
    ae_int_t i;

    ae_frame_make(_state, &_frame_block);
    memset(&rbuf, 0, sizeof(rbuf));
    memset(&ibuf, 0, sizeof(ibuf));
    memset(&rbuf2, 0, sizeof(rbuf2));
    memset(&ibuf2, 0, sizeof(ibuf2));
    ae_vector_init(&rbuf, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&ibuf, 0, DT_INT, _state, ae_true);
    ae_vector_init(&rbuf2, 0, DT_REAL, _state, ae_true);
    ae_vector_init(&ibuf2, 0, DT_INT, _state, ae_true);

    ae_vector_set_length(&ibuf, n, _state);
    ae_vector_set_length(&rbuf, n, _state);
    for(i=0; i<=n-1; i++)
    {
        ibuf.ptr.p_int[i] = i;
    }
    tagsortfasti(x, &ibuf, &rbuf2, &ibuf2, n, _state);
    for(i=0; i<=n-1; i++)
    {
        rbuf.ptr.p_double[i] = y->ptr.p_double[ibuf.ptr.p_int[i]];
    }
    ae_v_move(&y->ptr.p_double[0], 1, &rbuf.ptr.p_double[0], 1, ae_v_len(0,n-1));
    for(i=0; i<=n-1; i++)
    {
        rbuf.ptr.p_double[i] = d->ptr.p_double[ibuf.ptr.p_int[i]];
    }
    ae_v_move(&d->ptr.p_double[0], 1, &rbuf.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_frame_leave(_state);
}

/*************************************************************************
Internal version of Spline1DGridDiffCubic.

Accepts pre-ordered X/Y, temporary arrays (which may be  preallocated,  if
you want to save time, or not) and output array (which may be preallocated
too).

Y is passed as var-parameter because we may need to force last element  to
be equal to the first one (if periodic boundary conditions are specified).

  -- ALGLIB PROJECT --
     Copyright 03.09.2010 by Bochkanov Sergey
*************************************************************************/
static void spline1d_spline1dgriddiffcubicinternal(/* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_int_t n,
     ae_int_t boundltype,
     double boundl,
     ae_int_t boundrtype,
     double boundr,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_vector* a1,
     /* Real    */ ae_vector* a2,
     /* Real    */ ae_vector* a3,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* dt,
     ae_state *_state)
{
    ae_int_t i;


    
    /*
     * allocate arrays
     */
    if( d->cnt<n )
    {
        ae_vector_set_length(d, n, _state);
    }
    if( a1->cnt<n )
    {
        ae_vector_set_length(a1, n, _state);
    }
    if( a2->cnt<n )
    {
        ae_vector_set_length(a2, n, _state);
    }
    if( a3->cnt<n )
    {
        ae_vector_set_length(a3, n, _state);
    }
    if( b->cnt<n )
    {
        ae_vector_set_length(b, n, _state);
    }
    if( dt->cnt<n )
    {
        ae_vector_set_length(dt, n, _state);
    }
    
    /*
     * Special cases:
     * * N=2, parabolic terminated boundary condition on both ends
     * * N=2, periodic boundary condition
     */
    if( (n==2&&boundltype==0)&&boundrtype==0 )
    {
        d->ptr.p_double[0] = (y->ptr.p_double[1]-y->ptr.p_double[0])/(x->ptr.p_double[1]-x->ptr.p_double[0]);
        d->ptr.p_double[1] = d->ptr.p_double[0];
        return;
    }
    if( (n==2&&boundltype==-1)&&boundrtype==-1 )
    {
        d->ptr.p_double[0] = (double)(0);
        d->ptr.p_double[1] = (double)(0);
        return;
    }
    
    /*
     * Periodic and non-periodic boundary conditions are
     * two separate classes
     */
    if( boundrtype==-1&&boundltype==-1 )
    {
        
        /*
         * Periodic boundary conditions
         */
        y->ptr.p_double[n-1] = y->ptr.p_double[0];
        
        /*
         * Boundary conditions at N-1 points
         * (one point less because last point is the same as first point).
         */
        a1->ptr.p_double[0] = x->ptr.p_double[1]-x->ptr.p_double[0];
        a2->ptr.p_double[0] = 2*(x->ptr.p_double[1]-x->ptr.p_double[0]+x->ptr.p_double[n-1]-x->ptr.p_double[n-2]);
        a3->ptr.p_double[0] = x->ptr.p_double[n-1]-x->ptr.p_double[n-2];
        b->ptr.p_double[0] = 3*(y->ptr.p_double[n-1]-y->ptr.p_double[n-2])/(x->ptr.p_double[n-1]-x->ptr.p_double[n-2])*(x->ptr.p_double[1]-x->ptr.p_double[0])+3*(y->ptr.p_double[1]-y->ptr.p_double[0])/(x->ptr.p_double[1]-x->ptr.p_double[0])*(x->ptr.p_double[n-1]-x->ptr.p_double[n-2]);
        for(i=1; i<=n-2; i++)
        {
            
            /*
             * Altough last point is [N-2], we use X[N-1] and Y[N-1]
             * (because of periodicity)
             */
            a1->ptr.p_double[i] = x->ptr.p_double[i+1]-x->ptr.p_double[i];
            a2->ptr.p_double[i] = 2*(x->ptr.p_double[i+1]-x->ptr.p_double[i-1]);
            a3->ptr.p_double[i] = x->ptr.p_double[i]-x->ptr.p_double[i-1];
            b->ptr.p_double[i] = 3*(y->ptr.p_double[i]-y->ptr.p_double[i-1])/(x->ptr.p_double[i]-x->ptr.p_double[i-1])*(x->ptr.p_double[i+1]-x->ptr.p_double[i])+3*(y->ptr.p_double[i+1]-y->ptr.p_double[i])/(x->ptr.p_double[i+1]-x->ptr.p_double[i])*(x->ptr.p_double[i]-x->ptr.p_double[i-1]);
        }
        
        /*
         * Solve, add last point (with index N-1)
         */
        spline1d_solvecyclictridiagonal(a1, a2, a3, b, n-1, dt, _state);
        ae_v_move(&d->ptr.p_double[0], 1, &dt->ptr.p_double[0], 1, ae_v_len(0,n-2));
        d->ptr.p_double[n-1] = d->ptr.p_double[0];
    }
    else
    {
        
        /*
         * Non-periodic boundary condition.
         * Left boundary conditions.
         */
        if( boundltype==0 )
        {
            a1->ptr.p_double[0] = (double)(0);
            a2->ptr.p_double[0] = (double)(1);
            a3->ptr.p_double[0] = (double)(1);
            b->ptr.p_double[0] = 2*(y->ptr.p_double[1]-y->ptr.p_double[0])/(x->ptr.p_double[1]-x->ptr.p_double[0]);
        }
        if( boundltype==1 )
        {
            a1->ptr.p_double[0] = (double)(0);
            a2->ptr.p_double[0] = (double)(1);
            a3->ptr.p_double[0] = (double)(0);
            b->ptr.p_double[0] = boundl;
        }
        if( boundltype==2 )
        {
            a1->ptr.p_double[0] = (double)(0);
            a2->ptr.p_double[0] = (double)(2);
            a3->ptr.p_double[0] = (double)(1);
            b->ptr.p_double[0] = 3*(y->ptr.p_double[1]-y->ptr.p_double[0])/(x->ptr.p_double[1]-x->ptr.p_double[0])-0.5*boundl*(x->ptr.p_double[1]-x->ptr.p_double[0]);
        }
        
        /*
         * Central conditions
         */
        for(i=1; i<=n-2; i++)
        {
            a1->ptr.p_double[i] = x->ptr.p_double[i+1]-x->ptr.p_double[i];
            a2->ptr.p_double[i] = 2*(x->ptr.p_double[i+1]-x->ptr.p_double[i-1]);
            a3->ptr.p_double[i] = x->ptr.p_double[i]-x->ptr.p_double[i-1];
            b->ptr.p_double[i] = 3*(y->ptr.p_double[i]-y->ptr.p_double[i-1])/(x->ptr.p_double[i]-x->ptr.p_double[i-1])*(x->ptr.p_double[i+1]-x->ptr.p_double[i])+3*(y->ptr.p_double[i+1]-y->ptr.p_double[i])/(x->ptr.p_double[i+1]-x->ptr.p_double[i])*(x->ptr.p_double[i]-x->ptr.p_double[i-1]);
        }
        
        /*
         * Right boundary conditions
         */
        if( boundrtype==0 )
        {
            a1->ptr.p_double[n-1] = (double)(1);
            a2->ptr.p_double[n-1] = (double)(1);
            a3->ptr.p_double[n-1] = (double)(0);
            b->ptr.p_double[n-1] = 2*(y->ptr.p_double[n-1]-y->ptr.p_double[n-2])/(x->ptr.p_double[n-1]-x->ptr.p_double[n-2]);
        }
        if( boundrtype==1 )
        {
            a1->ptr.p_double[n-1] = (double)(0);
            a2->ptr.p_double[n-1] = (double)(1);
            a3->ptr.p_double[n-1] = (double)(0);
            b->ptr.p_double[n-1] = boundr;
        }
        if( boundrtype==2 )
        {
            a1->ptr.p_double[n-1] = (double)(1);
            a2->ptr.p_double[n-1] = (double)(2);
            a3->ptr.p_double[n-1] = (double)(0);
            b->ptr.p_double[n-1] = 3*(y->ptr.p_double[n-1]-y->ptr.p_double[n-2])/(x->ptr.p_double[n-1]-x->ptr.p_double[n-2])+0.5*boundr*(x->ptr.p_double[n-1]-x->ptr.p_double[n-2]);
        }
        
        /*
         * Solve
         */
        spline1d_solvetridiagonal(a1, a2, a3, b, n, d, _state);
    }
}

/*************************************************************************
This subroutine differentiates the spline.

INPUT PARAMETERS:
    C   -   spline interpolant.
    X   -   point

Result:
    S   -   S(x)
    DS  -   S'(x)
    D2S -   S''(x)

  -- ALGLIB PROJECT --
     Copyright 24.06.2007 by Bochkanov Sergey
*************************************************************************/
void spline1ddiff(spline1dinterpolant* c,
     double x,
     double* s,
     double* ds,
     double* d2s,
     ae_state *_state)
{
    ae_int_t l;
    ae_int_t r;
    ae_int_t m;
    double t;

    *s = 0;
    *ds = 0;
    *d2s = 0;

    ae_assert(c->k==3, "Spline1DDiff: internal error", _state);
    ae_assert(!ae_isinf(x, _state), "Spline1DDiff: infinite X!", _state);
    
    /*
     * special case: NaN
     */
    if( ae_isnan(x, _state) )
    {
        *s = _state->v_nan;
        *ds = _state->v_nan;
        *d2s = _state->v_nan;
        return;
    }
    
    /*
     * correct if periodic
     */
    if( c->periodic )
    {
        apperiodicmap(&x, c->x.ptr.p_double[0], c->x.ptr.p_double[c->n-1], &t, _state);
    }
    
    /*
     * Binary search
     */
    l = 0;
    r = c->n-2+1;
    while(l!=r-1)
    {
        m = (l+r)/2;
        if( c->x.ptr.p_double[m]>=x )
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }
    
    /*
     * Differentiation
     */
    x = x-c->x.ptr.p_double[l];
    m = 4*l;
    *s = c->c.ptr.p_double[m]+x*(c->c.ptr.p_double[m+1]+x*(c->c.ptr.p_double[m+2]+x*c->c.ptr.p_double[m+3]));
    *ds = c->c.ptr.p_double[m+1]+2*x*c->c.ptr.p_double[m+2]+3*ae_sqr(x, _state)*c->c.ptr.p_double[m+3];
    *d2s = 2*c->c.ptr.p_double[m+2]+6*x*c->c.ptr.p_double[m+3];
}

void _spline1dinterpolant_clear(void* _p)
{
    spline1dinterpolant *p = (spline1dinterpolant*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->c);
}
   
void _spline1dinterpolant_destroy(void* _p)
{
    spline1dinterpolant *p = (spline1dinterpolant*)_p;
    ae_touch_ptr((void*)p);
    ae_vector_destroy(&p->x);
    ae_vector_destroy(&p->c);
}

void _spline1dfitreport_clear(void* _p)
{
    spline1dfitreport *p = (spline1dfitreport*)_p;
    ae_touch_ptr((void*)p);
}

void _spline1dfitreport_destroy(void* _p)
{
    spline1dfitreport *p = (spline1dfitreport*)_p;
    ae_touch_ptr((void*)p);
}

#endif

}