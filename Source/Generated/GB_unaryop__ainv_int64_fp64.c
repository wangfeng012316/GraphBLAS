//------------------------------------------------------------------------------
// GB_unaryop:  hard-coded functions for each built-in unary operator
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2019, All Rights Reserved.
// http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

//------------------------------------------------------------------------------

// If this file is in the Generated/ folder, do not edit it (auto-generated)

#include "GB.h"
#ifndef GBCOMPACT
#include "GB_unaryop__include.h"

// C=unop(A) is defined by the following types and operators:

// op(A)  function:  GB_unop__ainv_int64_fp64
// op(A') function:  GB_tran__ainv_int64_fp64

// C type:   int64_t
// A type:   double
// cast:     int64_t cij ; GB_CAST_SIGNED(cij,aij,64)
// unaryop:  cij = -aij

// aij = Ax [pA]
#define GB_GETA(aij,Ax,pA)  \
    double aij = Ax [pA]

#define GB_CX(p) Cx [p]

// unary operator
#define GB_OP(z, x)   \
    z = -x ;

// casting
#define GB_CASTING(z, x)   \
    int64_t z ; GB_CAST_SIGNED(z,x,64) ;

//------------------------------------------------------------------------------
// Cx = op(cast(Ax)), apply a unary operator
//------------------------------------------------------------------------------

void GB_unop__ainv_int64_fp64
(
    int64_t *restrict Cx,
    double *restrict Ax,
    int64_t anz,
    int nthreads
)
{ 
    #include "GB_unaryop_apply_op.c"
}

//------------------------------------------------------------------------------
// C = op(cast(A')), transpose, typecast, and apply a unary operator
//------------------------------------------------------------------------------

void GB_tran__ainv_int64_fp64
(
    int64_t *restrict Cp,
    int64_t *restrict Ci,
    int64_t *restrict Cx,
    const GrB_Matrix A
)
{ 
    double *restrict Ax = A->x ;
    #include "GB_unaryop_transpose_op.c"
}

#endif
