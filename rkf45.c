#include <stdio.h>
#include <math.h>

#include "metodos.h"

const int CONT=10000;

void rkf45(int neq,double **A,double *CI,double p, double h, double ti, double tf, FILE *f)
/*	neq: numero de equacoes;
	A: matriz dos coeficientes do sistemas;
	CI: vetor com as condicoes iniciais;
	p: precisao;
	h: passo;
	ti: menor extremo do intervalo;
	tf: maior extremo do intervalo;
	N: numero de iteracoes
*/
{
	double X[neq];
	double X0[neq];
	double X1[neq];
	double X2[neq];
	double X3[neq];
	double X4[neq];
	double X5[neq];

	int N=ceil((tf-ti)/h);

  	fprintf(f,"# Parametros de entrada\n\n");

  	fprintf(f, "# neq = %+14d (numero de equacoes do sistema)\n",neq);
  	fprintf(f, "# p   = %+14.8f (precisao desejada)\n",p);
  	fprintf(f, "# h   = %+14.8f (passo)\n",h);
  	fprintf(f, "# ti  = %+14.8f (menor extremo do intervalo)\n",ti);
  	fprintf(f, "# tf  = %+14.8f (maior extremo do intervalo)\n",tf);
  	fprintf(f, "# N   = %+14d (numero de iteracoes)\n",N);

  	fprintf(f,"\n");

  	fprintf(f, "# Matriz A (matriz de coeficientes do sistema)\n");
  	for(int i=0;i<neq;i++) {
    	fprintf(f,"#");
  		for(int j=0;j<neq;j++)
  			fprintf(f, "%+14.8f\t",A[i][j]);
  		fprintf(f,"\n");
  	}

  	fprintf(f,"\n");

  	fprintf(f, "# Vetor CI (vetor com as condicoes iniciais)\n#");
  	for(int i=0;i<neq;i++)
   		fprintf(f, "%+14.8f\t",CI[i]);

  	fprintf(f,"\n\n");

// Processamento

  	fprintf(f, "#Colunas dispostas de acordo com o tempo, tk, e a quantidade em cada compartimento, respectivamente, em cada iteracao:#\n\n");

// Imprime condicoes iniciais
  	fprintf(f,"%+14.8f",ti);
  	for(int i=0;i<neq;i++) {
    	X0[i]=CI[i];
    	fprintf(f,"\t%+14.8f",X0[i]);
  	}

// Imprime os resultados apos cada passo
	for(int k=1; k<=N; k++){
		if( (k % CONT) == 0 ) {
            fprintf(f,"\n%+14.8f",ti+k*h);
		}
		for (int i=0; i<neq; i++) {
      		X1[i]=0.0;
			for (int j=0; j<neq; j++){
				X1[i]+=A[i][j]*X0[j];
 			}
		}
		for (int i=0; i<neq; i++) {
      		X2[i]=0.0;
			for (int j=0; j<neq; j++){
				X2[i]+=A[i][j]*(X0[j]+(1.0/4.0)*h*X1[i]);
			}
		}
		for (int i=0; i<neq; i++) {
      		X3[i]=0.0;
			for (int j=0; j<neq; j++){
   				X3[i]+=A[i][j]*(X0[j]+(3.0/32.0)*h*X1[i]+(9.0/32.0)*h*X2[i]);
			}
		}
		for (int i=0; i<neq; i++) {
  			X4[i]=0.0;
			for (int j=0; j<neq; j++){
   				X4[i]+=A[i][j]*(X0[j]+(1932.0/2197.0)*h*X1[i]-(7200.0/2197.0)*h*X2[i]+(7296.0/2197.0)*h*X3[i]);
			}
		}
		for (int i=0; i<neq; i++) {
			X5[i]=0.0;
			for (int j=0; j<neq; j++) {
				X5[i]+=A[i][j]*(X0[j]+(439.0/216.0)*h*X1[i]-8.0*h*X2[i]+(3680.0/513.0)*h*X3[i]-(845.0/4104.0)*h*X4[i]);
			}
		}


  		for (int i=0; i<neq; i++){
			X[i]=X0[i]+h*((25.0/216.0)*X1[i]+(1408.0/2565.0)*X3[i]+(2197.0/4104.0)*X4[i]-(1.0/5.0)*X5[i]);
            if( (k % CONT) == 0 ) {
              fprintf(f,"\t%+14.8e",X[i]);
			}
			X0[i]=X[i];
		}

	}
		//for (int i=0; i<neq; i++) {
			//fprintf(f,"\n%+14.8f",tf);
            //fprintf(f,"\n");
        	//fprintf(f,"\t%+14.8e",X[i]);
        //}
}
