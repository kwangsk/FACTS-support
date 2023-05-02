%module maeda
%include "typemaps.i"
%{
    #define SWIG_FILE_WITH_INIT
    #include "maeda.h"
%}

%include "numpy.i"

%init %{
    import_array();
%}

%apply (float* ARGOUT_ARRAY1, int DIM1) {(float* outformant, int n1),(float* xVTinter, int n2),(float* yVTinter, int n3),(float* xVTexter, int n4),(float* yVTexter, int n5)};
%apply (float* IN_ARRAY1, int DIM1) {(float* pTCcfg, int n6)};
%apply (float* IN_ARRAY1, int DIM1) {(float* pPCcfg, int n7)};
%apply (float* IN_ARRAY1, int DIM1) {(float* AMpar, int n8)};
%include "maeda.h"