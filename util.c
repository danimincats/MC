#include <stdio.h>
#include <stdlib.h>
//
void syntax(void)
{
	printf("Uso: edo -i <arq_entrada> -o <arq_saida>\n\n");
	exit(EXIT_FAILURE);
}
//
void fatal(const char *msg)
{
	fprintf(stderr,"FATAL: %s\n",msg);
	exit(EXIT_FAILURE);
}
