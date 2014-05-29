#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "util.h"
#include "metodos.h"

#define MAX_LEN_FILENAME 80

static char filename_in[MAX_LEN_FILENAME];
static char filename_out[MAX_LEN_FILENAME];

static int neq;
static double **A;
static double *CI;
static double p;
static double h;
static double ti;
static double tf;

static void option_check(int argc, char **argv);
static void read_parameters(void);
static void free_parameters(void);

int main(int argc, char **argv)
{
  setlocale(LC_ALL,"pt_BR");
	option_check(argc,argv);
	read_parameters();
	FILE *f=fopen(filename_out,"wt");
	//rk33(neq,A,CI,p,h,ti,tf, f);
	//rk44(neq,A,CI,p,h,ti,tf, f);
    rkf45(neq,A,CI,p,h,ti,tf, f);
	//rkf56(neq,A,CI,p,h,ti,tf, f);
	//rkf(neq,A,CI,p,h,ti,tf, f);
	fclose(f);
	free_parameters();
	return EXIT_SUCCESS;
}

static void option_check(int argc, char **argv)
{
	if(argc!=5)
		syntax();
	for(int i=1;i<=3;i+=2) {
		if(argv[i][0]=='-') {
			if(argv[i][1]=='i' || argv[i][1]=='I') {
				strncpy(filename_in,argv[i+1],MAX_LEN_FILENAME-1);
			} else if(argv[i][1]=='o'||argv[i][1]=='O') {
				strncpy(filename_out,argv[i+1],MAX_LEN_FILENAME-1);
			} else {
				syntax();
			}
		}
	}
	FILE *f=fopen(filename_in,"rt");
	if(f==NULL) {
		fatal("Arquivo de entrada nao encontrado!");
	} else {
		fclose(f);
	}
}
//
static void read_parameters(void)
{
	FILE *f=fopen(filename_in,"rt");
	int r=0;
	r=fscanf(f,"%i",&neq);
	A=(double **) malloc(neq*sizeof(double *));
	for(int i=0;i<neq;i++) {
		A[i]=(double *) malloc(neq*sizeof(double));
	}
	for(int i=0;i<neq;i++) {
		for(int j=0;j<neq;j++) {
			r=fscanf(f,"%lf",&A[i][j]);
		}
	}
	CI=(double *) malloc(neq*sizeof(double));
	for(int i=0;i<neq;i++) {
		r=fscanf(f,"%lf",&CI[i]);
	}
	r=fscanf(f,"%lf",&p);
	r=fscanf(f,"%lf",&h);
	r=fscanf(f,"%lf",&ti);
	r=fscanf(f,"%lf",&tf);
	fclose(f);
}
//
static void free_parameters(void)
{
	for(int i=0;i<neq;i++)
		free(A[i]);
  	free(CI);
	free(A);
}
