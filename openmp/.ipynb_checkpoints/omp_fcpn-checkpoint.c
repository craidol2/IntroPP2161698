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
  25 November 2020 by Diego Villamizar, Universidad Industrial de Santander diego.villamizar7@correouis.edu.co                   
  This OpenMP Modification makes a parallelization of the original Code...  
*/
#include <omp.h>

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>


int flg;
void chkPrime(long int n)
{
    long int i;
    /* Transformé el while en un for para paralelizarlo usando las directivas de openmp */
    #pragma omp parallel for
    for(i=n-1;i>=2;i--)
      {
          if(n%i==0)
            {
                flg=1;
            }
      }
}

void AllCombination(long int a)
{
  long int b,c,d,e,i,j,k,s,z,v,x[8],y[8],m;
  b=a;
  i=0;
  /* No es posible paralelizarlo ya que requiere un orden (requiere que sea secuencial) */
  while(b>0)
  {
      y[i]=b % 10;
      b=b/10;
      i++;
  }
  c=0;
  /* No es posible paralelizarlo ya que requiere un orden (requiere que sea secuencial) */
  for(j=i-1;j>=0;j--)
  {
      x[c]=y[j];
      c++;   
  }
  
  m=i;
  /* No es posible paralelizarlo ya que requiere un orden (requiere que sea secuencial) */
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

int main()
{
    long int i=2,ctr;
	
 printf("\n\n Find Circular Prime Numbers upto a specific limit: \n");
 printf(" ---------------------------------------------------\n");
    printf(" Enter the upper Limit: ");
    scanf("%li",&ctr);
    printf("\n The Circular Prime Numbers less than %li are: \n",ctr);
    while(i<=ctr)
    {
      flg=0;
      AllCombination(i);
      if(flg==0)
      {
          printf("%li ",i);
      }
      i++;
    }
	printf("\n");
}