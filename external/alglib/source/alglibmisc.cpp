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
#include "alglibmisc.h"

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
#if defined(AE_COMPILE_HQRND) || !defined(AE_PARTIAL_BUILD)
static ae_int_t hqrnd_hqrndmax = 2147483561;
static ae_int_t hqrnd_hqrndm1 = 2147483563;
static ae_int_t hqrnd_hqrndm2 = 2147483399;
static ae_int_t hqrnd_hqrndmagic = 1634357784;
static ae_int_t hqrnd_hqrndintegerbase(hqrndstate* state,
     ae_state *_state);


#endif
#if defined(AE_COMPILE_HQRND) || !defined(AE_PARTIAL_BUILD)
/*************************************************************************
HQRNDState  initialization  with  random  values  which come from standard
RNG.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
void hqrndrandomize(hqrndstate* state, ae_state *_state)
{
    ae_int_t s0;
    ae_int_t s1;

    _hqrndstate_clear(state);

    s0 = ae_randominteger(hqrnd_hqrndm1, _state);
    s1 = ae_randominteger(hqrnd_hqrndm2, _state);
    hqrndseed(s0, s1, state, _state);
}
/*************************************************************************
HQRNDState initialization with seed values

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
void hqrndseed(ae_int_t s1,
     ae_int_t s2,
     hqrndstate* state,
     ae_state *_state)
{

    _hqrndstate_clear(state);

    
    /*
     * Protection against negative seeds:
     *
     *     SEED := -(SEED+1)
     *
     * We can use just "-SEED" because there exists such integer number  N
     * that N<0, -N=N<0 too. (This number is equal to 0x800...000).   Need
     * to handle such seed correctly forces us to use  a  bit  complicated
     * formula.
     */
    if( s1<0 )
    {
        s1 = -(s1+1);
    }
    if( s2<0 )
    {
        s2 = -(s2+1);
    }
    state->s1 = s1%(hqrnd_hqrndm1-1)+1;
    state->s2 = s2%(hqrnd_hqrndm2-1)+1;
    state->magicv = hqrnd_hqrndmagic;
}

/*************************************************************************
This function generates random real number in (0,1),
not including interval boundaries

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
double hqrnduniformr(hqrndstate* state, ae_state *_state)
{
    double result;


    result = (double)(hqrnd_hqrndintegerbase(state, _state)+1)/(double)(hqrnd_hqrndmax+2);
    return result;
}
/*************************************************************************
This function generates random integer number in [0, N)

1. State structure must be initialized with HQRNDRandomize() or HQRNDSeed()
2. N can be any positive number except for very large numbers:
   * close to 2^31 on 32-bit systems
   * close to 2^62 on 64-bit systems
   An exception will be generated if N is too large.

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
ae_int_t hqrnduniformi(hqrndstate* state, ae_int_t n, ae_state *_state)
{
    ae_int_t maxcnt;
    ae_int_t mx;
    ae_int_t a;
    ae_int_t b;
    ae_int_t result;


    ae_assert(n>0, "HQRNDUniformI: N<=0!", _state);
    maxcnt = hqrnd_hqrndmax+1;
    
    /*
     * Two branches: one for N<=MaxCnt, another for N>MaxCnt.
     */
    if( n>maxcnt )
    {
        
        /*
         * N>=MaxCnt.
         *
         * We have two options here:
         * a) N is exactly divisible by MaxCnt
         * b) N is not divisible by MaxCnt
         *
         * In both cases we reduce problem on interval spanning [0,N)
         * to several subproblems on intervals spanning [0,MaxCnt).
         */
        if( n%maxcnt==0 )
        {
            
            /*
             * N is exactly divisible by MaxCnt.
             *
             * [0,N) range is dividided into N/MaxCnt bins,
             * each of them having length equal to MaxCnt.
             *
             * We generate:
             * * random bin number B
             * * random offset within bin A
             * Both random numbers are generated by recursively
             * calling HQRNDUniformI().
             *
             * Result is equal to A+MaxCnt*B.
             */
            ae_assert(n/maxcnt<=maxcnt, "HQRNDUniformI: N is too large", _state);
            a = hqrnduniformi(state, maxcnt, _state);
            b = hqrnduniformi(state, n/maxcnt, _state);
            result = a+maxcnt*b;
        }
        else
        {
            
            /*
             * N is NOT exactly divisible by MaxCnt.
             *
             * [0,N) range is dividided into Ceil(N/MaxCnt) bins,
             * each of them having length equal to MaxCnt.
             *
             * We generate:
             * * random bin number B in [0, Ceil(N/MaxCnt)-1]
             * * random offset within bin A
             * * if both of what is below is true
             *   1) bin number B is that of the last bin
             *   2) A >= N mod MaxCnt
             *   then we repeat generation of A/B.
             *   This stage is essential in order to avoid bias in the result.
             * * otherwise, we return A*MaxCnt+N
             */
            ae_assert(n/maxcnt+1<=maxcnt, "HQRNDUniformI: N is too large", _state);
            result = -1;
            do
            {
                a = hqrnduniformi(state, maxcnt, _state);
                b = hqrnduniformi(state, n/maxcnt+1, _state);
                if( b==n/maxcnt&&a>=n%maxcnt )
                {
                    continue;
                }
                result = a+maxcnt*b;
            }
            while(result<0);
        }
    }
    else
    {
        
        /*
         * N<=MaxCnt
         *
         * Code below is a bit complicated because we can not simply
         * return "HQRNDIntegerBase() mod N" - it will be skewed for
         * large N's in [0.1*HQRNDMax...HQRNDMax].
         */
        mx = maxcnt-maxcnt%n;
        do
        {
            result = hqrnd_hqrndintegerbase(state, _state);
        }
        while(result>=mx);
        result = result%n;
    }
    return result;
}
/*************************************************************************
Random number generator: normal numbers

This function generates one random number from normal distribution.
Its performance is equal to that of HQRNDNormal2()

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
double hqrndnormal(hqrndstate* state, ae_state *_state)
{
    double v1;
    double v2;
    double result;


    hqrndnormal2(state, &v1, &v2, _state);
    result = v1;
    return result;
}
/*************************************************************************
Random number generator: normal numbers

This function generates two independent random numbers from normal
distribution. Its performance is equal to that of HQRNDNormal()

State structure must be initialized with HQRNDRandomize() or HQRNDSeed().

  -- ALGLIB --
     Copyright 02.12.2009 by Bochkanov Sergey
*************************************************************************/
void hqrndnormal2(hqrndstate* state,
     double* x1,
     double* x2,
     ae_state *_state)
{
    double u;
    double v;
    double s;

    *x1 = 0;
    *x2 = 0;

    for(;;)
    {
        u = 2*hqrnduniformr(state, _state)-1;
        v = 2*hqrnduniformr(state, _state)-1;
        s = ae_sqr(u, _state)+ae_sqr(v, _state);
        if( ae_fp_greater(s,(double)(0))&&ae_fp_less(s,(double)(1)) )
        {
            
            /*
             * two Sqrt's instead of one to
             * avoid overflow when S is too small
             */
            s = ae_sqrt(-2*ae_log(s, _state), _state)/ae_sqrt(s, _state);
            *x1 = u*s;
            *x2 = v*s;
            return;
        }
    }
}
/*************************************************************************
This function returns random integer in [0,HQRNDMax]

L'Ecuyer, Efficient and portable combined random number generators
*************************************************************************/
static ae_int_t hqrnd_hqrndintegerbase(hqrndstate* state,
     ae_state *_state)
{
    ae_int_t k;
    ae_int_t result;


    ae_assert(state->magicv==hqrnd_hqrndmagic, "HQRNDIntegerBase: State is not correctly initialized!", _state);
    k = state->s1/53668;
    state->s1 = 40014*(state->s1-k*53668)-k*12211;
    if( state->s1<0 )
    {
        state->s1 = state->s1+2147483563;
    }
    k = state->s2/52774;
    state->s2 = 40692*(state->s2-k*52774)-k*3791;
    if( state->s2<0 )
    {
        state->s2 = state->s2+2147483399;
    }
    
    /*
     * Result
     */
    result = state->s1-state->s2;
    if( result<1 )
    {
        result = result+2147483562;
    }
    result = result-1;
    return result;
}
void _hqrndstate_init(void* _p, ae_state *_state, ae_bool make_automatic)
{
    hqrndstate *p = (hqrndstate*)_p;
    ae_touch_ptr((void*)p);
}

void _hqrndstate_clear(void* _p)
{
    hqrndstate *p = (hqrndstate*)_p;
    ae_touch_ptr((void*)p);
}
#endif

}

