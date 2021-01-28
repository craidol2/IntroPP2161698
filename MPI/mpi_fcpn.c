/*
  Purpose:
    Find circular prime numbers upto a specific limit
  Licensing:
    This code is distributed under the GNU LGPL license.
  Modified:
    Unknow
  Author:
    Unknow
  OpenMP Modification:
  27 January 2021 by Diego Villamizar, Universidad Industrial de Santander diego.villamizar7@correouis.edu.co                   
  This OpenMP Modification makes a parallelization of the original Code...  
*/

# include "mpi.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>


int flg;
void chkPrime(long int n)
{
    long int i;
    i=n-1;
    while(i>=2)
    {
        if(n%i==0)
        {
            flg=1;
        }
        i--;
    }
}

void AllCombination(long int a)
{
  long int b,c,d,e,i,j,k,s,z,v,x[8],y[8],m;
  b=a;
  i=0;
  while(b>0)
  {
      y[i]=b % 10;
      b=b/10;
      i++;
  }
  c=0;
  for(j=i-1;j>=0;j--)
  {
    x[c]=y[j];
    c++;
  }
  m=i;
  while(m>0)
  {
     c=m-1;
     d=i-1;
     e=0;
     s=0;
     while(e<i)
     {
       z=pow(10,d);
       v=z*x[c%i];
       c++;
       d--;
       e++;
       s=s+v;
     }
     m--;
     chkPrime(s);
  }
}


void solucionParcial(int a, int b){
    int i;
    for (i=a; i <=b; i++)
    {
        flg=0;
        AllCombination(i);
        if(flg==0)
        {
            printf("%li ",i);
            fflush(stdout); //necesario para imprimir en orden
        }
    }
}


int main(int argc, char** argv)
{
    double timeStart, timeEnd;
    long int i,ctr;
    int idProcesoActual, procesosTotales; //variables a usar mpi
    int cantidadCiclos[]={0,0,0,0};
    MPI_Init(&argc, &argv); //inicializo mpi
    MPI_Comm_size(MPI_COMM_WORLD, &procesosTotales);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcesoActual);
    
    //TIEMPO DE INICIO
    MPI_Barrier(MPI_COMM_WORLD);
    timeStart = MPI_Wtime(); 
    if(idProcesoActual==0){ //proceso maestro
    
        printf("\n\n Find Circular Prime Numbers upto a specific limit: \n");
        printf(" ---------------------------------------------------\n");
        printf(" Enter the upper Limit: ");
        scanf("%li",&ctr);
        printf("\n The Circular Prime Numbers less than %li are: \n",ctr);
        
        //TAMANO QUE RECORRERA CADA PROCESO (DINAMICA HASTA MAXIMO np=4)
        for (i = 0; i < procesosTotales; ++i)
        {
          if((i+1)==procesosTotales){ //ultimo
            cantidadCiclos[i]=ctr;
          }else{
            cantidadCiclos[i]=ctr/procesosTotales;
          }
        }
        //EJEMPLO DE DIVISION entrada=900, np=3 [300,600,900]
        solucionParcial(2,cantidadCiclos[0]);
        for (i = 1; i < procesosTotales; ++i)
        {
          MPI_Send(&cantidadCiclos,4,MPI_INT,i,0,MPI_COMM_WORLD); //envia a cada proceso
        }
    }else{
        MPI_Recv(&cantidadCiclos,4,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        solucionParcial(cantidadCiclos[idProcesoActual-1]+1,cantidadCiclos[idProcesoActual]);
      
    }    
    
    //TIEMPO FINAL
    MPI_Barrier(MPI_COMM_WORLD);
    timeEnd = MPI_Wtime(); 
    if(idProcesoActual==0){
        printf("\n TIEMPO DE EJECUCION EN MILISEGUNDOS = %f\n", 1000*(timeEnd-timeStart));
    }
    //finalizo mpi
    MPI_Finalize();
}