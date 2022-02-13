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
#ifndef _alglibmisc_pkg_h
#define _alglibmisc_pkg_h
#include "ap.h"
#include "alglibinternal.h"

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_HQRND) || !defined(AE_PARTIAL_BUILD)
typedef struct
{
    ae_int_t s1;
    ae_int_t s2;
    ae_int_t magicv;
} hqrndstate;
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
#if defined(AE_COMPILE_HQRND) || !defined(AE_PARTIAL_BUILD)
void hqrndrandomize(hqrndstate* state, ae_state *_state);
void hqrndseed(ae_int_t s1,
     ae_int_t s2,
     hqrndstate* state,
     ae_state *_state);

double hqrnduniformr(hqrndstate* state, ae_state *_state);
ae_int_t hqrnduniformi(hqrndstate* state, ae_int_t n, ae_state *_state);
double hqrndnormal(hqrndstate* state, ae_state *_state);
void hqrndnormal2(hqrndstate* state,
     double* x1,
     double* x2,
     ae_state *_state);
void _hqrndstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
void _hqrndstate_clear(void* _p);
#endif
}
#endif

