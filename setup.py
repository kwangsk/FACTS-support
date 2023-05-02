#! /usr/bin/env python

# System imports
from distutils.core import *
from distutils      import sysconfig

# Third-party modules - we depend on numpy for everything
import numpy

# Obtain the numpy include directory.  This logic works across numpy versions.
try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()

# inplace extension module
module = Extension("_maeda",
                   ["maeda.i","maeda.c","vsyn_lib.c","vtt_lib.c","complex.c","plot_lib.c","lam_lib.c","vtf_lib.c"],
                   include_dirs = [numpy_include,'../src'])

# NumyTypemapTests setup
setup(  name        = "maeda",
        description = "maeda plant extension for swig, sourced from vtcalcs.",
        author      = "Kwang Seob Kim",
        version     = "1.1",
        ext_modules = [module]
        )