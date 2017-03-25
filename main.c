/*  This programe is to calculate the co-moving free streaming lenghth for a particle with peculiar velocity Vk from a0 
 *  to a.
 */ 
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

#define BIN_NUM 500
#define START_A (1./101.)
#define END_A   (1./3.)
#define VK      1000

#define OMEGA_M 0.3
#define OMEGA_V 0.7
#define H0      100

#define OUTPATH    "./Result/"

double integ_core(double x, void *param);
double fsc(double a1, double a2, double v); 

int main()
{
  int i;
  FILE* fp;
  char file_name[300];
  double a0[BIN_NUM];
  double dx[BIN_NUM];  
  double dist = (END_A - START_A - 1e-3) / (double) BIN_NUM;
  
  sprintf(file_name, "%s%s%d%s%f%s%f%s", OUTPATH, "fsc_vk_", VK, "_a_(", START_A, ",", END_A, ").txt");
  fp = fopen(file_name, "w+");  
  
  for(i=0; i< BIN_NUM; i++)
    {	
	a0[i] = START_A + i * dist;
	dx[i] = fsc(a0[i], END_A, VK);
    fprintf(fp, "%.6e	%.6e\n", a0[i], dx[i]);
    }
  
  fclose(fp);
  return 0;	
}              /* end main */	

double integ_core(double x, void *param)
{
  double h = H0 * sqrt(OMEGA_V + OMEGA_M/x/x/x);
	
  return 1.0/x/x/x/h;		
}     /* end integ_core */	

double fsc(double a1, double a2, double v)
{
  gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);	
	
  double int_result, error;
  
  gsl_function F;
  F.function = &integ_core;
			
  gsl_integration_qags(&F, a1, a2, 0, 1e-7, 1000, w, &int_result, &error);
  
  return a1 * VK * int_result;  	
}     /* end fsc */	
