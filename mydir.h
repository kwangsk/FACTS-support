/****
*	File : mydir.h
*	Note : directory specifications.
***/

/* For windows */
#ifdef WINDOWS_COMPILE
	char	*NTAFpath    = "Maedadata\\area\\Nt.are";
/*	char	*VTAFdir     = "data\\area\\"; */

/*	char	*SIGdir      = "data\\sig\\"; 
	char	*tempSIGpath = "data\\sig\\tempsig.sig";
	char	*tempGLTpath = "data\\sig\\tempglt.sig";
*/

	char	*MODELSPECpath = "Maedadata\\specdata\\pb1_spec.dat";
	char	*RADIMPpath    = "Maedadata\\specdata\\rad_imp.dat";
#else
	char	*NTAFpath    = "Maedadata//area//Nt.are";
/*	char	*VTAFdir     = "data//area//";

	char	*SIGdir      = "data//sig//";
	char	*tempSIGpath = "data//sig//tempsig.sig";
	char	*tempGLTpath = "data//sig//tempglt.sig";
*/
	char	*MODELSPECpath = "Maedadata//specdata//pb1_spec.dat";
	char	*RADIMPpath    = "Maedadata//specdata//rad_imp.dat";
#endif
