#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <string.h>
#define Max_long_cad 31
#define num_lineas 13


int main(){
    FILE *archivoE;
    FILE *archivoS;
    char aEntrada[20]="nombres.txt",aSalida[20]="ruta_nombres.txt",command[50]="",inst[20]="",inst1[20]="";
    char palabras[num_lineas][Max_long_cad];
    char buferArchivo[Max_long_cad];
	  char letras[50]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    int numero_Columnas, numero_Filas, i, j,contador_letras=0,cont;
    int pid;

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

    

    switch(pid=fork()){
      case -1:
        printf ("\nError al crear el proceso");
        exit(0);
      break;
      case 0: 
        for(int i=1;i<=2;i++){
          if(i==1){
            //para validar existencia 
            strcat(inst1,"ls . ");
            strcat(inst1,aSalida);
            strcat(inst1,">>error 2>&1");
            strcpy( command, inst1);
            if (system(command)==0){
              printf("\t Hijo %d -----> (PID= %d )\n",i,getpid());
              printf("\t Hijo %d -----> (PID= %d )\t\tEl archivo ya existe\n",i,getpid());
              printf("\t Hijo %d -----> (PID= %d )\t\tSe realizara el borrado del mismo....\n\n\n",i,getpid());
              //Eliminar archivo 
              strcat(inst1,"rm ");
              strcat(inst1,aSalida);
              strcpy( command, inst1);
              printf("\t Hijo %d -----> (PID= %d )\t\tSe borro el archivo con exito.\n",i,getpid());
              //crear archivo
              strcat(inst,"touch ");
              strcat(inst,aSalida);
              strcpy( command, inst);
              printf("\t Hijo %d -----> (PID= %d )\t\tSe creo el archivo de salida con exito.\n",i,getpid());
              system(command);
              printf("\t\t\t================Hijo %d: Termine (pid=%i)================\n\n",i, getpid());
              exit(0);
              
            }else{
              printf("\t Hijo %d -----> (PID= %d )\n",i,getpid());
              strcat(inst,"touch ");
              strcat(inst,aSalida);
              strcpy( command, inst);
              printf("\t Hijo %d -----> (PID= %d )\t\tSe creo el archivo de salida con exito.\n",i,getpid());
              system(command);
              printf("\t\t\t================Hijo %d: Termine (pid=%i)================\n\n",i, getpid());
              exit(0);
              
            }
            break;
            
          }else{
            printf("\t Hijo (PID= %d )   ---> num hijo %d  \n",getppid(),i); 
            



          }
          
        }

      break;
      default:
        
        while((pid=waitpid(-1,NULL,0))>0){
          printf("=====>Padre (pid=%i) : llego mi hijo 1 (pid=%i), mi archivo de salida está listo. \n\n",getpid(),pid);
        };


        archivoE=fopen(aEntrada,"r");
        printf("\nHola soy el Padre (PID= %d )   ---> y lei mi archivo  %s \n",getppid(),aEntrada);
        if(archivoE == NULL) {
          printf("El archivo no se ha podido abrir, no existe.");
        } else {
            i=0;
          while (fgets(buferArchivo, Max_long_cad, archivoE)){
          strtok(buferArchivo, "\n");
          memcpy(palabras[i], buferArchivo, Max_long_cad);
          i++;
          cont=i;
        }

        fclose(archivoE);
        //imprime nombres del archivo 
          for (i = 0; i < cont; i++){
            printf("Nombres: %s\n", palabras[i]);
          }
        }

    };
    return 0;
}