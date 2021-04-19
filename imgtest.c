#include <stdio.h>
#include <tgmath.h>
#include <stdlib.h>

#define pi acos(-1)
#define WIDTH 500
#define HEIGHT 500

double complex Dft(int x[WIDTH][HEIGHT], int a, int b);
double mainCode(int shiftX, int shiftY)
{
       int l, t, z, w, u, v;
       double ref_phase;

       //The original image
       int image[WIDTH][HEIGHT];
       int shifted_image[WIDTH][HEIGHT];
       for (z = 0; z < WIDTH; z++)
       {
              for (w = 0; w < HEIGHT; w++)
              {
                     if (z >= (0.25 * WIDTH) && z <= (0.75 * WIDTH - 1) && w >= (0.25 * HEIGHT) && w <= (0.75 * HEIGHT - 1))

                            image[z][w] = 1;
                     else
                            image[z][w] = 0;
              }
       }

       u = 1;
       v = 1;
       double complex ref_dft = Dft(image, u, v);
       printf("ref_dft = %f %+fi\n", creal(ref_dft), cimag(ref_dft));
       ref_phase = atan(cimag(ref_dft) / creal(ref_dft));
       printf("ref_phase = %f\n", ref_phase);

       //Shifted Image
       for (l = 0; l < WIDTH; l++)
       {
              for (t = 0; t < HEIGHT; t++)
              {
                     if ((l >= ((0.25 * WIDTH) + shiftX) && l <= ((0.75 * WIDTH - 1) + shiftX) && t >= (0.25 * HEIGHT) + shiftY) && t <= ((0.75 * HEIGHT - 1) + shiftY))

                            shifted_image[l][t] = 1;
                     else
                            shifted_image[l][t] = 0;
              }
       }

       printf("compute DFT of the shifted image ......................................... \n ");
       double complex shifted_dft = Dft(shifted_image, u, v);
       printf("shifted_dft = %f %+fi\n", creal(shifted_dft), cimag(shifted_dft));
       double shifted_phase = atan(cimag(shifted_dft) / creal(shifted_dft));
       printf("shifted_phase = %f\n", shifted_phase);
       double shift = shifted_phase - ref_phase;
       double actual_shift;

       //Phase shift calculation
       actual_shift = shift * WIDTH / (-2 * pi * u);
       printf("shift = %f\n", fabs(actual_shift));
       return actual_shift;
}

double complex Dft(int x[WIDTH][HEIGHT], int a, int b)
{
       int q, k;
       double complex Result = 0;
       double inbox;

       for (q = 0; q < WIDTH; q++)
       {
              for (k = 0; k < HEIGHT; k++)
              {
                     inbox = ((q * a) / (double)WIDTH) + ((k * b) / (double)HEIGHT);
                     Result += x[q][k] * exp(-2 * pi * I * inbox);
              }
       }
       return Result;
}
