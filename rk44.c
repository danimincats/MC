#include <stdio.h>
#include <math.h>

#include "metodos.h"

void rk44(int neq,double **A,double *CI,double p, double h, double ti, double tf, FILE *f)
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

        fprintf(f,"\n%+14.8f",ti+h*k);

		for (int i=0; i<neq; i++) {
      		X1[i]=0.0;
			for (int j=0; j<neq; j++){
				//X1[i]+=A[i][j]*X0[j]+18.0*(ti+h*k);
				X1[i]+=A[i][j]*X0[j];
 			}
		}
		for (int i=0; i<neq; i++) {
      		X2[i]=0.0;
			for (int j=0; j<neq; j++){
				//X2[i]+=A[i][j]*(X0[j]+0.5*h*X1[i]+18.0*(ti+h*k)+0.5*h);
				X2[i]+=A[i][j]*(X0[j]+0.5*h*X1[i]);
			}
		}
		for (int i=0; i<neq; i++) {
      		X3[i]=0.0;
			for (int j=0; j<neq; j++){
   				//X3[i]+=A[i][j]*(X0[j]+0.5*h*X2[i]+18.0*(ti+h*k)+0.5*h);
				X3[i]+=A[i][j]*(X0[j]+0.5*h*X2[i]);
			}
		}
		for (int i=0; i<neq; i++) {
  			X4[i]=0.0;
			for (int j=0; j<neq; j++){
   				//X4[i]+=A[i][j]*(X0[j]+h*X3[i]+18.0*(ti+h*k)+h);
				X4[i]+=A[i][j]*(X0[j]+h*X3[i]);
			}
		}

  		for (int i=0; i<neq; i++) {
    		X[i]=X0[i]+(h/6.0)*(X1[i]+2.0*X2[i]+2.0*X3[i]+X4[i]);
            fprintf(f,"\t%+14.8e",X[i]);
            X0[i]=X[i];
		}

    }

    //for (int i=0; i<neq; i++) {
    //    fprintf(f,"\n%+14.8f",tf);
    //    fprintf(f,"\t%+14.8e",X[i]);
    //}

}
