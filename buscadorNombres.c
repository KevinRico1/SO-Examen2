#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <string.h>
#define MAXIMA_LONGITUD_CADENA 31
#define CANTIDAD_LINEAS 13


int main(){
    FILE *archivoE;
    FILE *archivoS;
    char aEntrada[20],aSalida[20];
    char palabras[CANTIDAD_LINEAS][MAXIMA_LONGITUD_CADENA];
    char buferArchivo[MAXIMA_LONGITUD_CADENA];
	  char letras[50]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    int numero_Columnas, numero_Filas, i, j,contador_letras=0,cont;
    int pidh;

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


//    printf ("\n\n\tIngrese el nombre del archivo de entrada: ");
//    scanf("%s",aEntrada);
//    printf ("\n\n\tIngrese el nombre del archivo de salida: ");
//    scanf("%s",aSalida);

    

    switch(pidh=fork()){
      case -1:
        printf ("\nError al crear el proceso");
        exit(0);
      break;
      case 0:
        printf("\nPadre (PID= %d )   --->  Hijo (pid= %d ) \n",getppid(),getpid());  
        for(int i=1;i<=2;i++)//--tiene dos hijos 
          printf("\t Hijo (PID= %d )   ---> hijo %d  \n",getppid(),i); 
              //exit(0);
      break;
      default:
        archivoE=fopen(/*aEntrada*/"nombres.txt","r");

        if(archivoE == NULL) {
          printf("El fichero no se ha podido abrir, no existe.");
        } else {
            i=0;
          while (fgets(buferArchivo, MAXIMA_LONGITUD_CADENA, archivoE)){
          strtok(buferArchivo, "\n");
          memcpy(palabras[i], buferArchivo, MAXIMA_LONGITUD_CADENA);
          i++;
          cont=i;
        }

          fclose(archivoE);

          for (i = 0; i < cont; i++){
            printf("Nombres: %s\n", palabras[i]);
          }
        }

    };
    return 0;
}