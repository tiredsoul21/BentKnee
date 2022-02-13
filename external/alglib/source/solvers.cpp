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
#include "solvers.h"

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
#if defined(AE_COMPILE_LINLSQR) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
*************************************************************************/
_linlsqrreport_owner::_linlsqrreport_owner()
{
    jmp_buf _break_jump;
    alglib_impl::ae_state _state;
    
    alglib_impl::ae_state_init(&_state);
    if( setjmp(_break_jump) )
    {
        if( p_struct!=NULL )
        {
            alglib_impl::_linlsqrreport_destroy(p_struct);
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
    p_struct = (alglib_impl::linlsqrreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::linlsqrreport), &_state);
    memset(p_struct, 0, sizeof(alglib_impl::linlsqrreport));
    alglib_impl::_linlsqrreport_init(p_struct, &_state, ae_false);
    ae_state_clear(&_state);
}

_linlsqrreport_owner::_linlsqrreport_owner(const _linlsqrreport_owner &rhs)
{
    jmp_buf _break_jump;
    alglib_impl::ae_state _state;
    
    alglib_impl::ae_state_init(&_state);
    if( setjmp(_break_jump) )
    {
        if( p_struct!=NULL )
        {
            alglib_impl::_linlsqrreport_destroy(p_struct);
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
    alglib_impl::ae_assert(rhs.p_struct!=NULL, "ALGLIB: linlsqrreport copy constructor failure (source is not initialized)", &_state);
    p_struct = (alglib_impl::linlsqrreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::linlsqrreport), &_state);
    memset(p_struct, 0, sizeof(alglib_impl::linlsqrreport));
    alglib_impl::_linlsqrreport_init_copy(p_struct, const_cast<alglib_impl::linlsqrreport*>(rhs.p_struct), &_state, ae_false);
    ae_state_clear(&_state);
}

_linlsqrreport_owner& _linlsqrreport_owner::operator=(const _linlsqrreport_owner &rhs)
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
    alglib_impl::ae_assert(p_struct!=NULL, "ALGLIB: linlsqrreport assignment constructor failure (destination is not initialized)", &_state);
    alglib_impl::ae_assert(rhs.p_struct!=NULL, "ALGLIB: linlsqrreport assignment constructor failure (source is not initialized)", &_state);
    alglib_impl::_linlsqrreport_destroy(p_struct);
    memset(p_struct, 0, sizeof(alglib_impl::linlsqrreport));
    alglib_impl::_linlsqrreport_init_copy(p_struct, const_cast<alglib_impl::linlsqrreport*>(rhs.p_struct), &_state, ae_false);
    ae_state_clear(&_state);
    return *this;
}

_linlsqrreport_owner::~_linlsqrreport_owner()
{
    if( p_struct!=NULL )
    {
        alglib_impl::_linlsqrreport_destroy(p_struct);
        ae_free(p_struct);
    }
}

alglib_impl::linlsqrreport* _linlsqrreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::linlsqrreport* _linlsqrreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::linlsqrreport*>(p_struct);
}
linlsqrreport::linlsqrreport() : _linlsqrreport_owner() ,iterationscount(p_struct->iterationscount),nmv(p_struct->nmv),terminationtype(p_struct->terminationtype)
{
}

linlsqrreport::linlsqrreport(const linlsqrreport &rhs):_linlsqrreport_owner(rhs) ,iterationscount(p_struct->iterationscount),nmv(p_struct->nmv),terminationtype(p_struct->terminationtype)
{
}

linlsqrreport& linlsqrreport::operator=(const linlsqrreport &rhs)
{
    if( this==&rhs )
        return *this;
    _linlsqrreport_owner::operator=(rhs);
    return *this;
}

linlsqrreport::~linlsqrreport()
{
}
#endif

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS IMPLEMENTATION OF COMPUTATIONAL CORE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_LINLSQR) || !defined(AE_PARTIAL_BUILD)
static double linlsqr_atol = 1.0E-6;
static double linlsqr_btol = 1.0E-6;
static void linlsqr_clearrfields(linlsqrstate* state, ae_state *_state);
/*************************************************************************
This function initializes linear LSQR Solver.  It  provides  exactly  same
functionality as linlsqrcreate(), but reuses  previously  allocated  space
as much as possible.
  
INPUT PARAMETERS:
    M       -   number of rows in A
    N       -   number of variables, N>0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 14.11.2018 by Bochkanov Sergey
*************************************************************************/
void linlsqrcreatebuf(ae_int_t m,
     ae_int_t n,
     linlsqrstate* state,
     ae_state *_state)
{
    ae_int_t i;


    ae_assert(m>0, "LinLSQRCreateBuf: M<=0", _state);
    ae_assert(n>0, "LinLSQRCreateBuf: N<=0", _state);
    state->m = m;
    state->n = n;
    state->prectype = 0;
    state->epsa = linlsqr_atol;
    state->epsb = linlsqr_btol;
    state->epsc = 1/ae_sqrt(ae_machineepsilon, _state);
    state->maxits = 0;
    state->lambdai = (double)(0);
    state->xrep = ae_false;
    state->running = ae_false;
    state->repiterationscount = 0;
    
    /*
     * * allocate arrays
     * * set RX to NAN (just for the case user calls Results() without 
     *   calling SolveSparse()
     * * set B to zero
     */
    normestimatorcreate(m, n, 2, 2, &state->nes, _state);
    ae_vector_set_length(&state->rx, state->n, _state);
    ae_vector_set_length(&state->ui, state->m+state->n, _state);
    ae_vector_set_length(&state->uip1, state->m+state->n, _state);
    ae_vector_set_length(&state->vip1, state->n, _state);
    ae_vector_set_length(&state->vi, state->n, _state);
    ae_vector_set_length(&state->omegai, state->n, _state);
    ae_vector_set_length(&state->omegaip1, state->n, _state);
    ae_vector_set_length(&state->d, state->n, _state);
    ae_vector_set_length(&state->x, state->m+state->n, _state);
    ae_vector_set_length(&state->mv, state->m+state->n, _state);
    ae_vector_set_length(&state->mtv, state->n, _state);
    ae_vector_set_length(&state->b, state->m, _state);
    for(i=0; i<=n-1; i++)
    {
        state->rx.ptr.p_double[i] = _state->v_nan;
    }
    for(i=0; i<=m-1; i++)
    {
        state->b.ptr.p_double[i] = (double)(0);
    }
    ae_vector_set_length(&state->rstate.ia, 1+1, _state);
    ae_vector_set_length(&state->rstate.ra, 0+1, _state);
    state->rstate.stage = -1;
}
/*************************************************************************
This function sets right part. By default, right part is zero.

INPUT PARAMETERS:
    B       -   right part, array[N].

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
void linlsqrsetb(linlsqrstate* state,
     /* Real    */ ae_vector* b,
     ae_state *_state)
{
    ae_int_t i;


    ae_assert(!state->running, "LinLSQRSetB: you can not change B when LinLSQRIteration is running", _state);
    ae_assert(state->m<=b->cnt, "LinLSQRSetB: Length(B)<M", _state);
    ae_assert(isfinitevector(b, state->m, _state), "LinLSQRSetB: B contains infinite or NaN values", _state);
    state->bnorm2 = (double)(0);
    for(i=0; i<=state->m-1; i++)
    {
        state->b.ptr.p_double[i] = b->ptr.p_double[i];
        state->bnorm2 = state->bnorm2+b->ptr.p_double[i]*b->ptr.p_double[i];
    }
}
/*************************************************************************

  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
ae_bool linlsqriteration(linlsqrstate* state, ae_state *_state)
{
    ae_int_t summn;
    double bnorm;
    ae_int_t i;
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
        summn = state->rstate.ia.ptr.p_int[0];
        i = state->rstate.ia.ptr.p_int[1];
        bnorm = state->rstate.ra.ptr.p_double[0];
    }
    else
    {
        summn = 359;
        i = -58;
        bnorm = -919;
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
    if( state->rstate.stage==4 )
    {
        goto lbl_4;
    }
    if( state->rstate.stage==5 )
    {
        goto lbl_5;
    }
    if( state->rstate.stage==6 )
    {
        goto lbl_6;
    }
    
    /*
     * Routine body
     */
    ae_assert(state->b.cnt>0, "LinLSQRIteration: using non-allocated array B", _state);
    summn = state->m+state->n;
    bnorm = ae_sqrt(state->bnorm2, _state);
    state->userterminationneeded = ae_false;
    state->running = ae_true;
    state->repnmv = 0;
    state->repiterationscount = 0;
    state->r2 = state->bnorm2;
    linlsqr_clearrfields(state, _state);
    
    /*
     *estimate for ANorm
     */
    normestimatorrestart(&state->nes, _state);
lbl_7:
    if( !normestimatoriteration(&state->nes, _state) )
    {
        goto lbl_8;
    }
    if( !state->nes.needmv )
    {
        goto lbl_9;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->nes.x.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmv = ae_true;
    state->rstate.stage = 0;
    goto lbl_rcomm;
lbl_0:
    state->needmv = ae_false;
    ae_v_move(&state->nes.mv.ptr.p_double[0], 1, &state->mv.ptr.p_double[0], 1, ae_v_len(0,state->m-1));
    goto lbl_7;
lbl_9:
    if( !state->nes.needmtv )
    {
        goto lbl_11;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->nes.x.ptr.p_double[0], 1, ae_v_len(0,state->m-1));
    
    /*
     *matrix-vector multiplication
     */
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmtv = ae_true;
    state->rstate.stage = 1;
    goto lbl_rcomm;
lbl_1:
    state->needmtv = ae_false;
    ae_v_move(&state->nes.mtv.ptr.p_double[0], 1, &state->mtv.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    goto lbl_7;
lbl_11:
    goto lbl_7;
lbl_8:
    normestimatorresults(&state->nes, &state->anorm, _state);
    
    /*
     *initialize .RX by zeros
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->rx.ptr.p_double[i] = (double)(0);
    }
    
    /*
     *output first report
     */
    if( !state->xrep )
    {
        goto lbl_13;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    linlsqr_clearrfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 2;
    goto lbl_rcomm;
lbl_2:
    state->xupdated = ae_false;
lbl_13:
    
    /*
     * LSQR, Step 0.
     *
     * Algorithm outline corresponds to one which was described at p.50 of
     * "LSQR - an algorithm for sparse linear equations and sparse least 
     * squares" by C.Paige and M.Saunders with one small addition - we
     * explicitly extend system matrix by additional N lines in order 
     * to handle non-zero lambda, i.e. original A is replaced by
     *         [ A        ]
     * A_mod = [          ]
     *         [ lambda*I ].
     *
     * Step 0:
     *     x[0]          = 0
     *     beta[1]*u[1]  = b
     *     alpha[1]*v[1] = A_mod'*u[1]
     *     w[1]          = v[1]
     *     phiBar[1]     = beta[1]
     *     rhoBar[1]     = alpha[1]
     *     d[0]          = 0
     *
     * NOTE:
     * There are three criteria for stopping:
     * (S0) maximum number of iterations
     * (S1) ||Rk||<=EpsB*||B||;
     * (S2) ||A^T*Rk||/(||A||*||Rk||)<=EpsA.
     * It is very important that S2 always checked AFTER S1. It is necessary
     * to avoid division by zero when Rk=0.
     */
    state->betai = bnorm;
    if( ae_fp_eq(state->betai,(double)(0)) )
    {
        
        /*
         * Zero right part
         */
        state->running = ae_false;
        state->repterminationtype = 1;
        result = ae_false;
        return result;
    }
    for(i=0; i<=summn-1; i++)
    {
        if( i<state->m )
        {
            state->ui.ptr.p_double[i] = state->b.ptr.p_double[i]/state->betai;
        }
        else
        {
            state->ui.ptr.p_double[i] = (double)(0);
        }
        state->x.ptr.p_double[i] = state->ui.ptr.p_double[i];
    }
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmtv = ae_true;
    state->rstate.stage = 3;
    goto lbl_rcomm;
lbl_3:
    state->needmtv = ae_false;
    for(i=0; i<=state->n-1; i++)
    {
        state->mtv.ptr.p_double[i] = state->mtv.ptr.p_double[i]+state->lambdai*state->ui.ptr.p_double[state->m+i];
    }
    state->alphai = (double)(0);
    for(i=0; i<=state->n-1; i++)
    {
        state->alphai = state->alphai+state->mtv.ptr.p_double[i]*state->mtv.ptr.p_double[i];
    }
    state->alphai = ae_sqrt(state->alphai, _state);
    if( ae_fp_eq(state->alphai,(double)(0)) )
    {
        
        /*
         * Orthogonality stopping criterion is met
         */
        state->running = ae_false;
        state->repterminationtype = 4;
        result = ae_false;
        return result;
    }
    for(i=0; i<=state->n-1; i++)
    {
        state->vi.ptr.p_double[i] = state->mtv.ptr.p_double[i]/state->alphai;
        state->omegai.ptr.p_double[i] = state->vi.ptr.p_double[i];
    }
    state->phibari = state->betai;
    state->rhobari = state->alphai;
    for(i=0; i<=state->n-1; i++)
    {
        state->d.ptr.p_double[i] = (double)(0);
    }
    state->dnorm = (double)(0);
    
    /*
     * Steps I=1, 2, ...
     */
lbl_15:
    if( ae_false )
    {
        goto lbl_16;
    }
    
    /*
     * At I-th step State.RepIterationsCount=I.
     */
    state->repiterationscount = state->repiterationscount+1;
    
    /*
     * Bidiagonalization part:
     *     beta[i+1]*u[i+1]  = A_mod*v[i]-alpha[i]*u[i]
     *     alpha[i+1]*v[i+1] = A_mod'*u[i+1] - beta[i+1]*v[i]
     *     
     * NOTE:  beta[i+1]=0 or alpha[i+1]=0 will lead to successful termination
     *        in the end of the current iteration. In this case u/v are zero.
     * NOTE2: algorithm won't fail on zero alpha or beta (there will be no
     *        division by zero because it will be stopped BEFORE division
     *        occurs). However, near-zero alpha and beta won't stop algorithm
     *        and, although no division by zero will happen, orthogonality 
     *        in U and V will be lost.
     */
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->vi.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmv = ae_true;
    state->rstate.stage = 4;
    goto lbl_rcomm;
lbl_4:
    state->needmv = ae_false;
    for(i=0; i<=state->n-1; i++)
    {
        state->mv.ptr.p_double[state->m+i] = state->lambdai*state->vi.ptr.p_double[i];
    }
    state->betaip1 = (double)(0);
    for(i=0; i<=summn-1; i++)
    {
        state->uip1.ptr.p_double[i] = state->mv.ptr.p_double[i]-state->alphai*state->ui.ptr.p_double[i];
        state->betaip1 = state->betaip1+state->uip1.ptr.p_double[i]*state->uip1.ptr.p_double[i];
    }
    if( ae_fp_neq(state->betaip1,(double)(0)) )
    {
        state->betaip1 = ae_sqrt(state->betaip1, _state);
        for(i=0; i<=summn-1; i++)
        {
            state->uip1.ptr.p_double[i] = state->uip1.ptr.p_double[i]/state->betaip1;
        }
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->uip1.ptr.p_double[0], 1, ae_v_len(0,state->m-1));
    state->repnmv = state->repnmv+1;
    linlsqr_clearrfields(state, _state);
    state->needmtv = ae_true;
    state->rstate.stage = 5;
    goto lbl_rcomm;
lbl_5:
    state->needmtv = ae_false;
    for(i=0; i<=state->n-1; i++)
    {
        state->mtv.ptr.p_double[i] = state->mtv.ptr.p_double[i]+state->lambdai*state->uip1.ptr.p_double[state->m+i];
    }
    state->alphaip1 = (double)(0);
    for(i=0; i<=state->n-1; i++)
    {
        state->vip1.ptr.p_double[i] = state->mtv.ptr.p_double[i]-state->betaip1*state->vi.ptr.p_double[i];
        state->alphaip1 = state->alphaip1+state->vip1.ptr.p_double[i]*state->vip1.ptr.p_double[i];
    }
    if( ae_fp_neq(state->alphaip1,(double)(0)) )
    {
        state->alphaip1 = ae_sqrt(state->alphaip1, _state);
        for(i=0; i<=state->n-1; i++)
        {
            state->vip1.ptr.p_double[i] = state->vip1.ptr.p_double[i]/state->alphaip1;
        }
    }
    
    /*
     * Build next orthogonal transformation
     */
    state->rhoi = safepythag2(state->rhobari, state->betaip1, _state);
    state->ci = state->rhobari/state->rhoi;
    state->si = state->betaip1/state->rhoi;
    state->theta = state->si*state->alphaip1;
    state->rhobarip1 = -state->ci*state->alphaip1;
    state->phii = state->ci*state->phibari;
    state->phibarip1 = state->si*state->phibari;
    
    /*
     * Update .RNorm
     *
     * This tricky  formula  is  necessary  because  simply  writing
     * State.R2:=State.PhiBarIP1*State.PhiBarIP1 does NOT guarantees
     * monotonic decrease of R2. Roundoff error combined with 80-bit
     * precision used internally by Intel chips allows R2 to increase
     * slightly in some rare, but possible cases. This property is
     * undesirable, so we prefer to guard against R increase.
     */
    state->r2 = ae_minreal(state->r2, state->phibarip1*state->phibarip1, _state);
    
    /*
     * Update d and DNorm, check condition-related stopping criteria
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->d.ptr.p_double[i] = 1/state->rhoi*(state->vi.ptr.p_double[i]-state->theta*state->d.ptr.p_double[i]);
        state->dnorm = state->dnorm+state->d.ptr.p_double[i]*state->d.ptr.p_double[i];
    }
    if( ae_fp_greater_eq(ae_sqrt(state->dnorm, _state)*state->anorm,state->epsc) )
    {
        state->running = ae_false;
        state->repterminationtype = 7;
        result = ae_false;
        return result;
    }
    
    /*
     * Update x, output report
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->rx.ptr.p_double[i] = state->rx.ptr.p_double[i]+state->phii/state->rhoi*state->omegai.ptr.p_double[i];
    }
    if( !state->xrep )
    {
        goto lbl_17;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    linlsqr_clearrfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 6;
    goto lbl_rcomm;
lbl_6:
    state->xupdated = ae_false;
lbl_17:
    
    /*
     * Check stopping criteria
     * 1. achieved required number of iterations;
     * 2. ||Rk||<=EpsB*||B||;
     * 3. ||A^T*Rk||/(||A||*||Rk||)<=EpsA;
     */
    if( state->maxits>0&&state->repiterationscount>=state->maxits )
    {
        
        /*
         * Achieved required number of iterations
         */
        state->running = ae_false;
        state->repterminationtype = 5;
        result = ae_false;
        return result;
    }
    if( ae_fp_less_eq(state->phibarip1,state->epsb*bnorm) )
    {
        
        /*
         * ||Rk||<=EpsB*||B||, here ||Rk||=PhiBar
         */
        state->running = ae_false;
        state->repterminationtype = 1;
        result = ae_false;
        return result;
    }
    if( ae_fp_less_eq(state->alphaip1*ae_fabs(state->ci, _state)/state->anorm,state->epsa) )
    {
        
        /*
         * ||A^T*Rk||/(||A||*||Rk||)<=EpsA, here ||A^T*Rk||=PhiBar*Alpha[i+1]*|.C|
         */
        state->running = ae_false;
        state->repterminationtype = 4;
        result = ae_false;
        return result;
    }
    if( state->userterminationneeded )
    {
        
        /*
         * User requested termination
         */
        state->running = ae_false;
        state->repterminationtype = 8;
        result = ae_false;
        return result;
    }
    
    /*
     * Update omega
     */
    for(i=0; i<=state->n-1; i++)
    {
        state->omegaip1.ptr.p_double[i] = state->vip1.ptr.p_double[i]-state->theta/state->rhoi*state->omegai.ptr.p_double[i];
    }
    
    /*
     * Prepare for the next iteration - rename variables:
     * u[i]   := u[i+1]
     * v[i]   := v[i+1]
     * rho[i] := rho[i+1]
     * ...
     */
    ae_v_move(&state->ui.ptr.p_double[0], 1, &state->uip1.ptr.p_double[0], 1, ae_v_len(0,summn-1));
    ae_v_move(&state->vi.ptr.p_double[0], 1, &state->vip1.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    ae_v_move(&state->omegai.ptr.p_double[0], 1, &state->omegaip1.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->alphai = state->alphaip1;
    state->betai = state->betaip1;
    state->phibari = state->phibarip1;
    state->rhobari = state->rhobarip1;
    goto lbl_15;
lbl_16:
    result = ae_false;
    return result;
    
    /*
     * Saving state
     */
lbl_rcomm:
    result = ae_true;
    state->rstate.ia.ptr.p_int[0] = summn;
    state->rstate.ia.ptr.p_int[1] = i;
    state->rstate.ra.ptr.p_double[0] = bnorm;
    return result;
}


/*************************************************************************
This function sets stopping criteria.

INPUT PARAMETERS:
    EpsA    -   algorithm will be stopped if ||A^T*Rk||/(||A||*||Rk||)<=EpsA.
    EpsB    -   algorithm will be stopped if ||Rk||<=EpsB*||B||
    MaxIts  -   algorithm will be stopped if number of iterations
                more than MaxIts.

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTE: if EpsA,EpsB,EpsC and MaxIts are zero then these variables will
be setted as default values.
    
  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
void linlsqrsetcond(linlsqrstate* state,
     double epsa,
     double epsb,
     ae_int_t maxits,
     ae_state *_state)
{


    ae_assert(!state->running, "LinLSQRSetCond: you can not call this function when LinLSQRIteration is running", _state);
    ae_assert(ae_isfinite(epsa, _state)&&ae_fp_greater_eq(epsa,(double)(0)), "LinLSQRSetCond: EpsA is negative, INF or NAN", _state);
    ae_assert(ae_isfinite(epsb, _state)&&ae_fp_greater_eq(epsb,(double)(0)), "LinLSQRSetCond: EpsB is negative, INF or NAN", _state);
    ae_assert(maxits>=0, "LinLSQRSetCond: MaxIts is negative", _state);
    if( (ae_fp_eq(epsa,(double)(0))&&ae_fp_eq(epsb,(double)(0)))&&maxits==0 )
    {
        state->epsa = linlsqr_atol;
        state->epsb = linlsqr_btol;
        state->maxits = state->n;
    }
    else
    {
        state->epsa = epsa;
        state->epsb = epsb;
        state->maxits = maxits;
    }
}
/*************************************************************************
LSQR solver: results.

This function must be called after LinLSQRSolve

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[N], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    *  1    ||Rk||<=EpsB*||B||
                    *  4    ||A^T*Rk||/(||A||*||Rk||)<=EpsA
                    *  5    MaxIts steps was taken
                    *  7    rounding errors prevent further progress,
                            X contains best point found so far.
                            (sometimes returned on singular systems)
                    *  8    user requested termination via calling
                            linlsqrrequesttermination()
                * Rep.IterationsCount contains iterations count
                * NMV countains number of matrix-vector calculations
                
  -- ALGLIB --
     Copyright 30.11.2011 by Bochkanov Sergey
*************************************************************************/
void linlsqrresults(linlsqrstate* state,
     /* Real    */ ae_vector* x,
     linlsqrreport* rep,
     ae_state *_state)
{

    ae_vector_clear(x);
    _linlsqrreport_clear(rep);

    ae_assert(!state->running, "LinLSQRResult: you can not call this function when LinLSQRIteration is running", _state);
    if( x->cnt<state->n )
    {
        ae_vector_set_length(x, state->n, _state);
    }
    ae_v_move(&x->ptr.p_double[0], 1, &state->rx.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    rep->iterationscount = state->repiterationscount;
    rep->nmv = state->repnmv;
    rep->terminationtype = state->repterminationtype;
}
/*************************************************************************
Clears request fileds (to be sure that we don't forgot to clear something)
*************************************************************************/
static void linlsqr_clearrfields(linlsqrstate* state, ae_state *_state)
{


    state->xupdated = ae_false;
    state->needmv = ae_false;
    state->needmtv = ae_false;
    state->needmv2 = ae_false;
    state->needvmv = ae_false;
    state->needprec = ae_false;
}
void _linlsqrstate_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    linlsqrstate *p = (linlsqrstate*)_p;
    ae_touch_ptr((void*)p);
    _normestimatorstate_init(&p->nes, _state, make_automatic);
    ae_vector_init(&p->rx, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->b, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->ui, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->uip1, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->vi, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->vip1, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->omegai, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->omegaip1, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->d, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->mv, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->mtv, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->tmpd, 0, DT_REAL, _state, make_automatic);
    ae_vector_init(&p->tmpx, 0, DT_REAL, _state, make_automatic);
    _rcommstate_init(&p->rstate, _state, make_automatic);
}
void _linlsqrreport_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    linlsqrreport *p = (linlsqrreport*)_p;
    ae_touch_ptr((void*)p);
}
void _linlsqrreport_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic)
{
    linlsqrreport *dst = (linlsqrreport*)_dst;
    linlsqrreport *src = (linlsqrreport*)_src;
    dst->iterationscount = src->iterationscount;
    dst->nmv = src->nmv;
    dst->terminationtype = src->terminationtype;
}
void _linlsqrreport_clear(void* _p)
{
    linlsqrreport *p = (linlsqrreport*)_p;
    ae_touch_ptr((void*)p);
}
void _linlsqrreport_destroy(void* _p)
{
    linlsqrreport *p = (linlsqrreport*)_p;
    ae_touch_ptr((void*)p);
}
#endif


}

