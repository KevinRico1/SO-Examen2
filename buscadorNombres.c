#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>


int main(){
    char archivo_Entrada[20];
	  char letras[50]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    int numero_Columnas, numero_Filas, i, j,contador_letras=0;

    printf("Este programa realiza la búsqueda de un nombre ");
    printf("dada una matriz realizada de acuerdo al número de");
    printf("columnas ingresado");

    printf("\nIngrese el numero de columnas de la matriz: ");
    scanf("%i",&numero_Columnas);

    numero_Filas = (26/numero_Columnas)+1;
    if (numero_Columnas == 26) numero_Filas=1;

    printf("\n\nNumero de filas: %d    número de columnas: %d\n\n",numero_Filas,numero_Columnas);

    char matriz_principal[numero_Filas][numero_Columnas];
    
    for(i = 0; i<numero_Filas;i++){
        for(j = 0; j<numero_Columnas;j++){
            matriz_principal[i][j] = letras[contador_letras];
            contador_letras++;   
        }
    }    

    for(i = 0; i<numero_Filas;i++){
        for(j = 0; j<numero_Columnas;j++){
            printf("\t%c     ",matriz_principal[i][j]);
        }
        printf("\n\n\n");
    }  

    printf ("\n\n\tIngrese el nombre del archivo de entrada: ");
    scanf("%s",archivo_Entrada);
    

    return 0;
}