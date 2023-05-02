#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "plot_lib.h"
#include "lam_lib.h"
#include "vtconfig.h"
#include "vsyn_lib.h"
#include "mydir.h"
#include "vtcalcs.h"
static int size = 0;
static float	*pAf;

#define NP	 29					/* = np        */
extern float2D	ivt[NP];		/* VT inside contours             */
extern float2D	evt[NP];		/* VT exterior contours           */
extern float	lip_w, lip_h;	/* lip-tube width and height      */

void maedaplant(float *outformant, int n1, float* xVTinter, int n2, float* yVTinter, int n3, float* xVTexter, int n4, float* yVTexter, int n5, float* pTCcfg, int n6, float* pPCcfg, int n7, float* AMpar, int n8, float anc)
{
	register int i;
	int ns0 = 29;
	float frm[5]; //clears any formant data from previous runs 06/2020 KSK
	static area_function *af0;
	//read_af(NTAFpath , &nna, &afnt );
	// update all constants and variables
	if((int)(pTCcfg[0]) == RL_CIRCUIT)	rad_boundary = RL_CIRCUIT;
	else	rad_boundary = SHORT_CIRCUIT;
	//printf("Rad_boundary[%d]\n",rad_boundary);
	if((int)(pTCcfg[1]) == YIELDING)	wall = YIELDING;
	else	wall = RIGID;
	//printf("wall[%d]\n",wall);
	if((int)(pTCcfg[2]) == ON)	nasal_tract = ON;
	else	nasal_tract = OFF;
	//printf("nasal_tract[%d]\n",nasal_tract);
	if((int)(pTCcfg[3]) == CLOSE)	glt_boundary = CLOSE;
	else	glt_boundary = OPEN;
	//printf("glt_boundary[%d]\n",glt_boundary);

	ro = (float)(pPCcfg[0]);
	//printf("Air density[%f]\n",ro);
	c = (float)(pPCcfg[1]);
	//printf("Sound velocity[%f]\n",c);
	wall_resi = (float)(pPCcfg[2]);
	//printf("wall_resi[%f]\n",wall_resi);
	wall_mass = (float)(pPCcfg[3]);
	//printf("wall_mass[%f]\n",wall_mass);
	wall_comp = (float)(pPCcfg[4]);
	//printf("wall_comp[%f]\n",wall_comp);
	
//	anc = (float)(pAMcfg[7]);
	//printf("nasal area[%f]\n",anc);
	

		/* Initialization */
	read_model_spec();
	af0 = (area_function *) calloc( ns0, sizeof(area_function) );
	nph = 9;
	nbu = 8;
	nss = nbu + nph;
	afvt  = (area_function *) calloc( nss, sizeof(area_function) );
	convert_scale();
	semi_polar();

	//oAf = mxCreateDoubleMatrix(2,nss, mxREAL);
	//pAf = mxGetPr(oAf);
	/*
	for(i=0;i<7;i++)
	{
		printf("AMpar[%d][%f]\n",i,AMpar[i]);
	}*/
	//printf("nasal area[%f]\n",anc);
	/* Compute VT profile and area function, and plot them */
	lam( AMpar );				/* profile	*/
	//KSK: AMpar makes ivt evt variables which will be used in sagittal_to_areafunction...
	sagittal_to_area( &ns0, af0 );		/* area function */
	/*	for(i=0;i<ns0;i++)
	{
		//printf("af0[%i][%f]\n",i,af0[i].x);;
	}*/
	appro_area_function( ns0, af0, nss, afvt);
	/*
	for(i=0;i<ns0;i++)
	{
		//printf("afvt[%i][%f]\n",i,afvt[i]);;
	}*/
	calplot_tf_FBA(nfrmmax, frm, bw, amp, &nfrms, tfmag, tffreq, &ntf);

	//KSK: then calplot funciton starts with vtf_init function, 
	//which has copy_initial_af in it, which copies the af variable 
	//that we calculated above and use that information to compute 
	//formant frequencies.
	
	//KSK: Next oPdat is the P-output that will be used to plot the contour

	for(i=0;i<NP;i++)
	{
		xVTinter[i] = ivt[i].x;
		yVTinter[i] = ivt[i].y;
		xVTexter[i] = evt[i].x;
		yVTexter[i] = evt[i].y;
	}

	// oPdat2 = mxCreateDoubleMatrix(1,2,mxREAL);
	// pPdat2 = mxGetPr(oPdat2);
	// pPdat2[0] = lip_w; //KSK: This variable (lip width, not protrusion) 
	//                      does not seem to be used in the future.
	// pPdat2[1] = lip_h; //KSK: Already embedded in the yVT variables.
	// KSK: In a similar way, the lip protrusion is embedded in the xVT variables.


	for(i=0;i<n1;i++)
	{
		//printf("Formant[%f]\n",frm[i]);
		outformant[i] = frm[i];
		//  = bw[i];
//		pAmp[i] = amp[i];
	}
	/*
	int j;
    for (j=0; j<n1; j++)
    {
        outvec[j] = AMpar[j+1];
    }*/
	free( afnt );
	free( af0 );
	free( afvt );
}
//%apply (float* IN_ARRAY1, int DIM1) {(float* inar, int n1)};
//void inplace(float *inar, int n1, float *invec, int n2);