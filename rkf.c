#include <stdio.h>
#include <math.h>

#include "metodos.h"

static inline double max(double a, double b){ /*compara dois valorese apresenta o maximo*/
	return a > b ? a : b;
}

void rkf(int neq,double **A,double *CI,double p, double h, double ti, double tf, FILE *f)
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
	double X6[neq];
	double R[neq];

	int N=ceil((tf-ti)/h);

  	fprintf(f,"# Parametros de entrada\n\n");

  	fprintf(f, "# neq = %+14d (numero de equacoes do sistema)\n",neq);
  	fprintf(f, "# p   = %+14.8lf (precisao desejada)\n",p);
  	fprintf(f, "# h   = %+14.8lf (passo)\n",h);
  	fprintf(f, "# ti  = %+14.8lf (menor extremo do intervalo)\n",ti);
  	fprintf(f, "# tf  = %+14.8lf (maior extremo do intervalo)\n",tf);
  	fprintf(f, "# N   = %+14d (numero de iteracoes)\n",N);

  	fprintf(f,"\n");

  	fprintf(f, "# Matriz A (matriz de coeficientes do sistema)\n");
  	for(int i=0;i<neq;i++) {
    	fprintf(f,"#");
  		for(int j=0;j<neq;j++) 
  			fprintf(f, "%+14.8lf\t",A[i][j]);  	
  		fprintf(f,"\n");
  	}	

  	fprintf(f,"\n");

  	fprintf(f, "# Vetor CI (vetor com as condicoes iniciais)\n#");
  	for(int i=0;i<neq;i++)
   		fprintf(f, "%+14.8lf\t",CI[i]);

  	fprintf(f,"\n\n");

// Processamento 

  	fprintf(f, "#Colunas dispostas de acordo com o tempo, tk, e a quantidade em cada compartimento, respectivamente, em cada iteracao:#\n\n");

// Imprime condicoes iniciais
  	fprintf(f,"%+14.8lf",ti);
  	for(int i=0;i<neq;i++) {
    	X0[i]=CI[i];
    	fprintf(f,"\t%+14.8lf",X0[i]);
  	}

// Imprime os resultados apos cada passo
	for(int k=1; k<=N; k++){			
		//fprintf(f,"\n%+14.8lf",ti+k*h);
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
		for (int i=0; i<neq; i++) {
			X6[i]=0.0;
			for (int j=0; j<neq; j++) {
				X6[i]+=A[i][j]*(X0[j]+(-8.0/27.0)*h*X1[i]+2.0*h*X2[i]-(3544.0/2565.0)*h*X3[i]+(1859.0/4104.0)*h*X4[i]-(11.0/40.0)*h*X5[i]);
			}
		}


		for (int i=0; i<neq; i++) {
    		R[i]=(1.0/360.0)*X1[i]-(128.0/4275.0)*X3[i]-(2197.0/75240.0)*X4[i]+(1.0/50.0)*X5[i]+(2.0/55.0)*X6[i];
			//fprintf(f,"\t%+14.8lf",X[i]);      
			//X0[i]=X[i];
			double n=0.0, r=0.0;
			n=fabs(R[i]);
			r=max(r,n);
			if (r <= p){
				X[i]=X0[i]+h*((25.0/216.0)*X1[i]+(1408.0/2565.0)*X3[i]+(2197.0/4104.0)*X4[i]-(1.0/5.0)*X5[i]);
				fprintf(f,"\t%+14.8e",X[i]);      
				h= h*1.5;
				X0[i]=X[i];
			}
			if(r > p){
				h = h*0.25;
			}

		}	


  		  
  }
}
