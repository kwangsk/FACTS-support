# FACTS-support
This repository contains support files related to the 3rd party modules that need to be compiled for FACTS. Because FACTS (Kim et al., in review) is implemented in Python, other 3rd party model or modules that are part of FACTS have to be compiled in Python. To do this, we used Simplified Wrapper and Interface Generator (SWIG, https://www.swig.org/), a well known compiler that can integrate C and C++ with Python (among many other languages).

Please refer to Kim et al. (in review) for more details.

Author: Kwang S. Kim (kwangkim@purdue.edu)

Date: 04/29/2023


## Installation steps
1. [SWIG](#swig)
2. [Maeda](#maeda)
3. [LWPR](#lwpr)
- [Troubleshoot](#troubleshoot)

## SWIG
1. Download and install [swig](http://swig.org/)
2. Check if SWIG is in Environment Variables path (Windows) or PATH (UNIX). If not found, add swig directory to path. 
3. Make sure you have c compilers like Microsoft Visual Studio or MinGW if you are using windows. If you are on UNIX, gcc should do it.

## Maeda
All source codes for Maeda comes from VocalTractModels developed by Satrajit Ghosh (https://github.com/sensein/VocalTractModels), 
but currently forked at https://github.com/kwangsk/VocalTractModels).

SWIG compilation Version: 1.1


1. Clone source code (VocalTractModels) in a directory that is not a part of the FACTS directory
```bash
git clone https://github.com/kwangsk/VocalTractModels
```
2. Move all the support files (maeda.c, maeda.h, maeda.i, numpy.i, setup.py, mydir.h) in the FACTS-support repository (except README) to the VocalTractModels/vtcalcs/src.

3. It will ask you if you want to replace mydir.h, say yes (we updated the maeda data directory name specified in the file, from "data" to "Maedadata" in order to avoid confusion. 

4. Open a terminal and cd to the same directory and activate the FACTS virtual environment
```gitbash
conda activate facts_env
```
This ensures that your Maeda module will be compiled using the same Python version FACTS will be running on. 

5. From the same terminal, compile
```bash
python setup.py build_ext --inplace
```

6. Move the generated Python extension module (e.g., maeda.cp36-win_amd64.pyd) to 
the FACTS directory, under "FACTS_Modules/"

## LWPR
LWPR: LWPR compiled for Python via SWIG
Version: 1.1
Author:  [lhlmgr](https://github.com/lhlmgr)
All source codes for LWPR are obtained from https://github.com/lhlmgr/lwpr

1. Clone source code (LWPR) in a directory that is not a part of the FACTS directory
```bash
git clone https://github.com/lhlmgr/lwpr
```
   
2. You can open a terminal and cd to lwpr/python

3. Open a terminal and cd to the same directory and activate the FACTS virtual environment
```gitbash
conda activate facts_env
```
This ensures that your Maeda module will be compiled using the same Python version FACTS will be running on. 

4. From the same terminal, compile
```bash
python setup_nolib.py build_ext --inplace
```
	You will see some warnings, that is okay.

5. Move the generated Python extension module (e.g., lwpr.cp36-win_amd64.pyd) to the FACTS directory, under "FACTS_Modules/LWPR_Model/"


## Troubleshoot

### Python not being referenced
If python is not included in your PATH, it will complian about python not being referenced. You can choose to run the compilation by specifying Python's directory, for example:
 ```bash
C:\Users\LSPMC\anaconda3\python setup.py build_ext --inplace
```
or in case for UNIX (assuming that your python file is installed in anaconda3 folder):
```bash
/home/anaconda3/python setup.py build_ext --inplace
```

### Compilation fails with numpy-related issues
It may be either you do not have numpy installed, or if you do have it, it is in the conda directory. If this is the case, you have to
add the library directory to the environment variable path too. In my case, I had to add C:\Users\LSPMC\anaconda3\Library\bin\ to the enviornemnt variable path before compiling.

### Compilation on Windows does not even start and an error message says 'not being able to find vcvarsall.bat' 
You might not have a compiler installed.
If you have a compiler installed and vcvarsall is found but error message is "error executing command /u /c vcvarsall.bat" x86_amd64 && set." then it might be because of anaconda messed up your registry. Go to regedit,
HKEY_CURRENT_USER\Software\Microsoft\Command Processor\AutoRun and clear the value. (will have anaconda3 related stuff like "C:\ProgramData\Anaconda3\condabin\conda_hook.bat").

