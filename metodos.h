#ifndef __METODOS_H
#define __METODOS_H
#include <stdlib.h>

//void rk33(int neq,double **A,double *CI,double p, double h, double ti, double tf, FILE *f);
//funcao que resolve o sistema de EDOs pelo Metodo de Runge-Kutta 3-3

//void rk44(int neq,double **A,double *CI,double p, double h, double ti, double tf, FILE *f);
//funcao que resolve o sistema de EDOs pelo Metodo de Runge-Kutta 4-4

void rkf45(int neq,double **A,double *CI,double p, double h, double ti, double tf, FILE *f);
//funcao que resolve o sistema de EDOs pelo Metodo de Runge-Kutta 4-5

//void rkf56(int neq,double **A,double *CI,double p, double h, double ti, double tf, FILE *f);
//funcao que resolve o sistema de EDOs pelo Metodo de Runge-Kutta 5-6

//void rkf(int neq,double **A,double *CI,double p, double h, double ti, double tf, FILE *f);
//funcao que resolve o sistema de EDOs pelo Metodo de Runge-Kutta-Fehlberg


#endif
