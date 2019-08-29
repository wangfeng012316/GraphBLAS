function C = rdivide (A, B)
%TIMES C = A./B, sparse matrix element-wise division
% C = A./B when B is a matrix results in a dense matrix C, with all entries
% present.  If A is a matrix and B is a scalar, then C has the pattern of
% A, except if B is zero and A is double, single, or complex.  In that
% case, since 0/0 is NaN, C is a dense matrix.  If the types of A and B
% differ, C has the type of A, and B is typecasted into the type of A
% before computing C=A./B.  A and B can be GraphBLAS matrices or MATLAB
% sparse or full matrices, in any combination.
%
% See also rdivide, gb.emult, gb.eadd.

% SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2019, All Rights Reserved.
% http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

if (isscalar (A))
    if (isscalar (B))
        % both A and B are scalars
        C = gb.emult ('/', A, B) ;
    else
        % A is a scalar, B is a matrix.  A is expanded to full.
        % The result is a dense gb matrix.
        C = gb.eadd ('/', gb.expand (A, true (size (B))), B) ;
    end
else
    if (isscalar (B))
        % A is a matrix, B is a scalar
        if (get_scalar (B) == 0 & isfloat (A))
            % 0/0 is Nan, and thus must be computed computed if A is
            % floating-point.  The result is a dense matrix.
            C = gb.eadd ('/', A, gb.expand (B, true (size (A)))) ;
        else
            % The scalar B is nonzero so just compute A/B in the pattern of
            % A.  The result is sparse (the pattern of A).
            C = gb.emult ('/', A, gb.expand (B, A)) ;
        end
    else
        % both A and B are matrices.  The result is a dense matrix.
        C = gb.eadd ('/', full (A), full (B)) ;
    end
end
