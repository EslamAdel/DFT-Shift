#include <stdio.h>
#include <tgmath.h>
#include <stdlib.h>
#define pi acos(-1)
int  m,n;
double complex  Dft(int x[500][500],int a,int b);
double mainCode(int i,int j,int shiftx,int shifty)
{
int l,t,z,w,x,y,u,v;
double value1 = 180/pi;
double value2 = pi/180;
double ref_phase;
  m=i;
  n=j;

  int image[m][n];
  int shifted_image[m][n];
  for( z=0;z<m;z++)
       {
      for( w=0;w<n;w++){
        if(z>=(0.25*m) && z<=(0.75*m -1) && w>=(0.25*n) && w<=(0.75*n -1))
          
                    image[z][w]=1;
             else
                    image[z][w]=0;
        }
}

u=1;
v=1;
double complex ref_dft=Dft(image,u,v);
printf("ref_dft = %f %+fi\n",creal(ref_dft),cimag(ref_dft));
ref_phase =atan(cimag(ref_dft)/creal(ref_dft));
printf("ref_phase = %f\n",ref_phase);
x=shiftx;
y=shifty;
for (l=0;l<m;l++)
       {
      for( t=0;t<n;t++)
         {
          if((l>=((0.25*m) + x) && l<=((0.75*m -1) + x) && t>=(0.25*n) + y) && t<=((0.75*n -1) + y))

                    shifted_image[l][t]=1;
             else
                    shifted_image[l][t]=0;

        }
}

printf("compute DFT of the shifted image ......................................... \n ");
double complex shifted_dft=Dft(shifted_image,u,v);
printf("shifted_dft = %f %+fi\n",creal(shifted_dft),cimag(shifted_dft));
double shifted_phase = atan(cimag(shifted_dft)/creal(shifted_dft));
printf("shifted_phase = %f\n",shifted_phase);
double shift =shifted_phase - ref_phase;
double actual_shift;
actual_shift=shift*m/(-2*pi*u);
printf("shift = %f\n",fabs(actual_shift));
return actual_shift;
}

double complex Dft(int x[500][500],int a,int b)
{
int q,k;
double M =500;
double N=500;
double complex Result =0;
double inbox;

for( q=0;q<500;q++)
   {  
 for( k=0;k<500;k++)
     {    
	   inbox=((q*a)/M) + ((k*b)/N);
           Result +=x[q][k]*exp(-2*pi*I*inbox);
      }
    }
return Result ;
}

