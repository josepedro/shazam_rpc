#include <stdio.h>
#include <math.h>

int main(){

int x[32],y[32];

int n,m;/* n:length of FFT:must be a power of two*/

n=8;m=3;/* m: n = 2**m*/

int i,j,k,n1,n2;
int c,s,a,t1,t2;   
int e;
printf("Enter the length of signal array\n");
    
    printf("Input the real and imaginary parts of the signal\n",i);

    for(i=0;i<n;i++)
    {
                    printf("Enter the real part %d:\t",i);
                    scanf("%d",&x[i]);
                    printf("Enter the imaginary part %d:\t",i);
                    scanf("%d",&y[i]);   
    }    
  /*print statement*/
    for(i=0;i<n;i++){printf("x[%d]=%d%+dj\n",i,x[i],y[i]);}
    
/* bit-reverse */
j = 0;
n2 = n/2;
for (i=1; i < n - 1; i++)
{
  n1 = n2;
  while ( j >= n1 )
   {
    j = j - n1;
    n1 = n1/2;
   }
  j = j + n1;
               
  if (i < j)
   {
    t1 = x[i];
    x[i] = x[j];
    x[j] = t1;
    t1 = y[i];
    y[i] = y[j];
    y[j] = t1;
   }
}
/*print statement*/
printf("After reversal:\n");
    for(i=0;i<n;i++){printf("x[%d]=%d%+dj\n",i,x[i],y[i]);}                                        

/* FFT */
n1 = 0; 
n2 = 1;
                                             
for (i=0; i < m; i++)
{
  n1 = n2;
  n2 = n2 + n2;
  e = (long)-6.28/n2;
  a = 0;
                                             
  for (j=0; j < n1; j++)
   {
    c=1; //c = cos(a)
    s=0; //s = sin(a)
    a = a + e;
                                            
    for (k=j; k < n; k=k+n2)
     {
      t1 = c*x[k+n1] - s*y[k+n1];
      t2 = s*x[k+n1] + c*y[k+n1];
      x[k+n1] = x[k] - t1;
      y[k+n1] = y[k] - t2;
      x[k] = x[k] + t1;
      y[k] = y[k] + t2;
     }
   }
}
/*print statement*/
printf("After Conversion:\n");
    for(i=0;i<n;i++){printf("x[%d]=%d%+dj\n",i,x[i],y[i]);}                                     
                                    

return 0;
}                         
