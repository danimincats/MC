#include <stdio.h>
#include <math.h>
#include<stdlib.h>

static double **aloca (int neq)
{
	double **mat=(double **) malloc(neq*sizeof(double *));
	for(int i=0;i<neq;i++) {
		mat[i]=(double *) malloc(neq*sizeof(double));
	}
	return mat;
}
//
static void libera(int neq, double **mat)
{
	for(int i=0;i<neq;i++) {
		free(mat[i]);
	}
	free(mat);
}
//
static inline double max(double a, double b) /*compara dois valores e apresenta o maximo*/
{
	return a > b ? a : b;
}
//
static double norma(int neq,double **m) /*calcula a norma de uma matriz*/
{
	double n=0.0,r=0.0;	/*n:norma; r:resultado para comparacao e obtencao da norma*/
	for(int i=0;i<neq;i++) {
		n=0.0;
		for(int j=0;j<neq;j++) {
			n+=fabs(m[i][j]);
		}
		r=max(r,n);
	}
	return r;
}
