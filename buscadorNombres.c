#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <string.h>
#define Max_long_cad 18
#define num_lineas 10
#define size 310

int main(){
  FILE *archivoE;
  FILE *archivoS;
  char aEntrada[20]="nombres.txt",aSalida[20]="ruta_nombres.txt",command[50]="",inst[20]="",inst1[20]="",buffer[size]="Mensaje XD";
  char palabras[num_lineas][Max_long_cad],buferArchivo[Max_long_cad];
  char letras[50]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
  int numero_Columnas, numero_Filas, i, j,contador_letras=0,cont;
  int b[2],a[2]; // Comunica hijo a padre
  char msg[size];
  pid_t pid,pidHijo1,pidHijo2,pidPadre;


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
  pid=fork();
  switch(pid){
    case -1:
      printf ("\nError al crear el proceso");
      exit(0);
    break;
    case 0:
      //para validar existencia 
      strcat(inst1,"ls . ");
      strcat(inst1,aSalida);
      strcat(inst1,">>error 2>&1");
      strcpy( command, inst1);
      if (system(command)==0){
        printf("\t Hijo 1 -----> (PID= %d )\n",getpid());
        printf("\t Hijo 1 -----> (PID= %d )\t\tEl archivo ya existe\n",getpid());
        printf("\t Hijo 1 -----> (PID= %d )\t\tSe realizara el borrado del mismo....\n\n\n",getpid());
        strcat(inst1,"rm ");
        strcat(inst1,aSalida);
        strcpy( command, inst1);
        printf("\t Hijo 1 -----> (PID= %d )\t\tSe borro el archivo con exito.\n",getpid());
        //crear archivo
        strcat(inst,"touch ");
        strcat(inst,aSalida);
        strcpy( command, inst);
        printf("\t Hijo 1 -----> (PID= %d )\t\tSe creo el archivo de salida con exito.\n",getpid());
        system(command);
        printf("\t\t\t================Hijo 1: Termine (pid=%i)================\n\n", getpid());
        exit(0); 
        break;         
      }else{
        printf("\t Hijo 1 -----> (PID= %d )\n",getpid());
        strcat(inst,"touch ");
        strcat(inst,aSalida);
        strcpy( command, inst);
        printf("\t Hijo 1 -----> (PID= %d )\t\tSe creo el archivo de salida con exito.\n",getpid());
        system(command);
        printf("\t\t\t================Hijo 1: Termine (pid=%i)================\n\n", getpid());
        exit(0); 
        break;         
      }  
    break;         
    default:
      printf("\nHola soy el Padre (PID= %d )   ---> y lei mi archivo  %s \n",getpid(),aEntrada);
      pidHijo1=pid;
    break;
    }

  while((waitpid(pidHijo1,NULL,0))>0){
    printf("=====>Padre (pid=%i) : llego mi hijo 1 (pid=%i), mi archivo de salida está listo. \n\n",getpid(),pidHijo1);  
  };
  if (pipe(a)<0){
     perror("pipe");
    exit(1);
  }
  if (pipe(b)<0){
    perror("pipe");
    exit(1);
  }
    pid=fork();
    switch(pid){
      case -1:
        printf ("\nError al crear el proceso");
        exit(0);
      break;
      case 0:
        printf("\t Hijo 2 -----> (PID= %d )\n",getpid());
        //dialogo padre-hijo HIJO
        close(a[0]); //CIERRA PIPE DE ESCRITURA
        close(b[1]); //CIERRA PIPE DE LECTURA
        printf("\n  Hijo 2 (pid =  %i ), esperando mensaje de mi padre...\n ",getpid());
        read(b[0], buffer,size); //es
        printf("\n  \t Hijo 2 (pid =  %i ), lee mensaje del pipe: %s \n", getpid(),buffer);
        write(a[1],/*buffer*/"mensaje de busqueda de letra ",size);//escribe en el pide del padre
        close(a[1]);  
        close(b[0]);
        //  exit(0);
      break;         
      default:
        archivoE=fopen(aEntrada,"r");
        
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
        }
      //sacar letra 
      for (i = 0; i < cont; i++){
        printf("------%d---------%ld---------",cont,sizeof(palabras[i]));
        for (j = 0; j < sizeof(palabras[i]); j++){
          if((palabras[i][j]!='\0') && ((int)palabras[i][j])!=13){
            printf("Nombres: %c\n", palabras[i][j]);
          }
        }
      }
      close(b[0]); //CIERRA PIPE DE LECTURA
      close(a[1]); //CIERRA PIPE DE ESCRITURA
      write(b[1],/*buffer*/"a",size);//escribe en el pide del hijo, escribe el mensaje del padre
      read(a[0],buffer,size); 
      printf("\n  \t Padre (pid =  %i ), lee mensaje del pipe: %s \n", getpid(), buffer);
      close(a[0]);
      close(b[1]);
      printf("(%s)\n",buffer );
      break;
    }

  }