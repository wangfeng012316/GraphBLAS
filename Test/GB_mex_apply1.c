//------------------------------------------------------------------------------
// GB_mex_apply1: C<Mask> = accum(C,op(x,A)) or op(x,A')
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2020, All Rights Reserved.
// http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

//------------------------------------------------------------------------------

// Apply a binary operator to a matrix or vector, binding x to a scalar,

#include "GB_mex.h"

#define USAGE "C = GB_mex_apply1 (C, Mask, accum, op, how, x, A, desc)"

// if how == 0: use the GxB_Scalar and GxB_Matrix/Vector_apply_BinaryOp1st
// if how == 1: use the C scalar   and GrB_Matrix/Vector_apply_BinaryOp1st_T

#define FREE_ALL                        \
{                                       \
    GB_MATRIX_FREE (&C) ;               \
    GB_MATRIX_FREE (&Mask) ;            \
    GB_MATRIX_FREE (&S) ;               \
    GB_MATRIX_FREE (&A) ;               \
    GrB_Descriptor_free_(&desc) ;       \
    GB_mx_put_global (true, 0) ;        \
}

GrB_Matrix C = NULL, S = NULL ;
GxB_Scalar scalar = NULL ;
GrB_Matrix Mask = NULL ;
GrB_Matrix A = NULL ;
GrB_Descriptor desc = NULL ;
GrB_BinaryOp accum = NULL ;
GrB_BinaryOp op = NULL ;
GrB_Info apply1 (bool is_matrix) ;
int how = 0 ;

//------------------------------------------------------------------------------

GrB_Info apply1 (bool is_matrix)
{
    GrB_Info info ;
    GrB_Type stype ;
    GxB_Scalar_type (&stype, scalar) ;

    if (is_matrix && how == 1)
    {
        if (stype == GrB_BOOL)
        {
            bool x = *((bool *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_BOOL_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_INT8)
        {
            int8_t x = *((int8_t *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_INT8_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_INT16)
        {
            int16_t x = *((int16_t *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_INT16_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_INT32)
        {
            int32_t x = *((int32_t *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_INT32_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_INT64)
        {
            int64_t x = *((int64_t *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_INT64_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_UINT8)
        {
            uint8_t x = *((uint8_t *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_UINT8_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_UINT16)
        {
            uint16_t x = *((uint16_t *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_UINT16_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_UINT32)
        {
            uint32_t x = *((uint32_t *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_UINT32_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_UINT64)
        {
            uint64_t x = *((uint64_t *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_UINT64_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_FP32)
        {
            float x = *((float *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_FP32_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_FP64)
        {
            double x = *((double *) (scalar->x)) ;
            info = GrB_Matrix_apply_BinaryOp1st_FP64_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GxB_FC32)
        {
            GxB_FC32_t x = *((GxB_FC32_t *) (scalar->x)) ;
            info = GxB_Matrix_apply_BinaryOp1st_FC32_
                (C, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GxB_FC64)
        {
            GxB_FC64_t x = *((GxB_FC64_t *) (scalar->x)) ;
            info = GxB_Matrix_apply_BinaryOp1st_FC64_
                (C, Mask, accum, op, x, A, desc) ;
        }
    }
    else if (is_matrix && how == 0)
    {
        info = GxB_Matrix_apply_BinaryOp1st_
            (C, Mask, accum, op, scalar, A, desc) ;
    }
    else if (!is_matrix && how == 1)
    {
        GrB_Vector w = (GrB_Vector) C ;
        GrB_Vector m = (GrB_Vector) Mask ;
        GrB_Vector a = (GrB_Vector) A ;
        if (stype == GrB_BOOL)
        {
            bool x = *((bool *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_BOOL_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_INT8)
        {
            int8_t x = *((int8_t *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_INT8_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_INT16)
        {
            int16_t x = *((int16_t *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_INT16_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_INT32)
        {
            int32_t x = *((int32_t *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_INT32_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_INT64)
        {
            int64_t x = *((int64_t *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_INT64_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_UINT8)
        {
            uint8_t x = *((uint8_t *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_UINT8_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_UINT16)
        {
            uint16_t x = *((uint16_t *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_UINT16_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_UINT32)
        {
            uint32_t x = *((uint32_t *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_UINT32_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_UINT64)
        {
            uint64_t x = *((uint64_t *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_UINT64_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_FP32)
        {
            float x = *((float *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_FP32_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GrB_FP64)
        {
            double x = *((double *) (scalar->x)) ;
            info = GrB_Vector_apply_BinaryOp1st_FP64_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GxB_FC32)
        {
            GxB_FC32_t x = *((GxB_FC32_t *) (scalar->x)) ;
            info = GxB_Vector_apply_BinaryOp1st_FC32_
                (w, Mask, accum, op, x, A, desc) ;
        }
        else if (stype == GxB_FC64)
        {
            GxB_FC64_t x = *((GxB_FC64_t *) (scalar->x)) ;
            info = GxB_Vector_apply_BinaryOp1st_FC64_
                (w, Mask, accum, op, x, A, desc) ;
        }
    }
    else if (!is_matrix && how == 0)
    {
        GrB_Vector w = (GrB_Vector) C ;
        GrB_Vector m = (GrB_Vector) Mask ;
        GrB_Vector a = (GrB_Vector) A ;
        info = GxB_Vector_apply_BinaryOp1st_
            (w, m, accum, op, scalar, a, desc) ;
    }

    return (info) ;
}

//------------------------------------------------------------------------------

void mexFunction
(
    int nargout,
    mxArray *pargout [ ],
    int nargin,
    const mxArray *pargin [ ]
)
{

    bool malloc_debug = GB_mx_get_global (true) ;

    // check inputs
    GB_WHERE (USAGE) ;
    if (nargout > 1 || nargin < 7 || nargin > 8)
    {
        mexErrMsgTxt ("Usage: " USAGE) ;
    }

    // get C (make a deep copy)
    #define GET_DEEP_COPY \
    C = GB_mx_mxArray_to_Matrix (pargin [0], "C input", true, true) ;
    #define FREE_DEEP_COPY GB_MATRIX_FREE (&C) ;
    GET_DEEP_COPY ;
    if (C == NULL)
    {
        FREE_ALL ;
        mexErrMsgTxt ("C failed") ;
    }

    // get Mask (shallow copy)
    Mask = GB_mx_mxArray_to_Matrix (pargin [1], "Mask", false, false) ;
    if (Mask == NULL && !mxIsEmpty (pargin [1]))
    {
        FREE_ALL ;
        mexErrMsgTxt ("Mask failed") ;
    }

    // get how.  0: use GxB_Scalar, 1: use bare C scalar
    GET_SCALAR (4, int, how, 0) ;

    // get scalar (shallow copy)
    S = GB_mx_mxArray_to_Matrix (pargin [5], "scalar input", false, true) ;
    if (S == NULL || S->magic != GB_MAGIC)
    {
        FREE_ALL ;
        mexErrMsgTxt ("scalar failed") ;
    }
    GrB_Index snrows, sncols, snvals ;
    GrB_Matrix_nrows (&snrows, S) ;
    GrB_Matrix_ncols (&sncols, S) ;
    GrB_Matrix_nvals (&snvals, S) ;
    GxB_Format_Value fmt ;
    GxB_Matrix_Option_get_(S, GxB_FORMAT, &fmt) ;
    if (snrows != 1 || sncols != 1 || snvals != 1 || fmt != GxB_BY_COL)
    {
        FREE_ALL ;
        mexErrMsgTxt ("scalar failed") ;
    }
    scalar = (GxB_Scalar) S ;
    GrB_Info info = GxB_Scalar_fprint (scalar, "scalar", GxB_SILENT, NULL) ;
    if (info != GrB_SUCCESS)
    {
        FREE_ALL ;
        mexErrMsgTxt ("scalar failed") ;
    }

    // get A (shallow copy)
    A = GB_mx_mxArray_to_Matrix (pargin [6], "A input", false, true) ;
    if (A == NULL || A->magic != GB_MAGIC)
    {
        FREE_ALL ;
        mexErrMsgTxt ("A failed") ;
    }

    // get accum, if present
    bool user_complex = (Complex != GxB_FC64)
        && (C->type == Complex || A->type == Complex) ;
    if (!GB_mx_mxArray_to_BinaryOp (&accum, pargin [2], "accum",
        C->type, user_complex))
    {
        FREE_ALL ;
        mexErrMsgTxt ("accum failed") ;
    }

    // get op
    if (!GB_mx_mxArray_to_BinaryOp (&op, pargin [3], "op",
        A->type, user_complex) || op == NULL)
    {
        FREE_ALL ;
        mexErrMsgTxt ("UnaryOp failed") ;
    }

    // get desc
    if (!GB_mx_mxArray_to_Descriptor (&desc, PARGIN (7), "desc"))
    {
        FREE_ALL ;
        mexErrMsgTxt ("desc failed") ;
    }

// printf ("\nin GB_mex_apply1 ---------------------------\n")  ;
// printf ("input:\n") ; GxB_print (C, 3) ;
// GxB_print (accum, 3) ;
// GxB_print (op, 3) ;
// GxB_print (scalar, 3) ;
// GxB_print (A, 3) ;

    // C<Mask> = accum(C,op(x,A))
    if (GB_NCOLS (C) == 1 && (desc == NULL || desc->in0 == GxB_DEFAULT))
    {
        // this is just to test the Vector version
        METHOD (apply1 (false)) ;
    }
    else
    {
        METHOD (apply1 (true)) ;
    }

// printf ("result:\n") ; GxB_print (C, 3) ;

    // return C to MATLAB as a struct and free the GraphBLAS C
    pargout [0] = GB_mx_Matrix_to_mxArray (&C, "C output", true) ;

    FREE_ALL ;
}

