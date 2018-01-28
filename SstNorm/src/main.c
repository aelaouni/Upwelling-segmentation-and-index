#include "netcdf_functions.h"
#include "line.h"

#include <stdio.h>
#include <string.h>



int main(int argc ,char **argv)
{

  Modis_data data,mask;
  IplImage *in_img,*dst_img;

   mask=read_netCDF_Modis(argv[1]);
   
   //printf("%f",mask.chlo->data.fl[0]);
   float *max=0 ,*smooth_array=0,*min=0;
     max = (float *)malloc(sizeof(float)*755);
     smooth_array = (float *)malloc(sizeof(float)*755);
     min = (float *)malloc(sizeof(float)*377);

     CvMat *hg;
     hg= cvCreateMat(378,378, CV_32FC1 );
     CvMat *hg1;
     hg1= cvCreateMat(378,378, CV_32FC1 );
     

   int i,j;
   for(i=0;i<755;i++)
     max[i]=0;


   Line_struct bar;
   int s=0;


   bar.mat= cvCreateMat(378,378, CV_32FC1 );
     bar.max=(float*)malloc(7*sizeof(float));

     for(i=0;i<378;i++){
       bar=line_(0,377-i,i,377,bar,mask.chlo);
       min[s]=bar.min;

       s++;}
     s=0;


     for(i=0;i<378;i++){
       bar=line(0,377-i,i,377,bar,mask.chlo);
       max[s]=bar.max[6];
       s++;}

     for(i=376;i>-1;i--){
       bar=line(377,i,377-i,0,bar,mask.chlo);
       max[s]=bar.max[6];
       s++;}

     s=0;
for (i = 0; i<739; i++)
    smooth_array[i]=(max[i] + max[i+1] +max[i+2]+max[i+3] + max[i+4] +max[i+5]+max[i+6] + max[i+7] +max[i+8]+max[i+9]+max[i+10]+max[i+11]+max[i+12]+max[i+13]+max[i+14]+max[i+15])/16;

for (i = 730; i<756; i++)
smooth_array[i]=max[734];

/*  for (i = 50; i<100; i++) */
/* smooth_array[i]=max[120]; */

/*  for (i = 0; i<50; i++) */
/*    smooth_array[i]=max[90]+0.05; */
/*  for (i = 40; i<60; i++) */
/*    smooth_array[i]=max[90]+0.5; */

 



 


     for(i=0;i<378;i++){
       bar.max[6]=smooth_array[s];
       bar.mat=scui(0,377-i,i,377,bar,mask.chlo);
       s++;
          }
     for(i=376;i>-1;i--){
       bar.max[6]=smooth_array[s];
       bar.mat=scui(377,i,377-i,0,bar,mask.chlo);
       s++;}
     /* for(i=0;i<320;i++) */
     /*   bar.mat=scui(0,i,290,0,bar,mask.chlo); */
     
      create_nc(bar.mat,mask.chlo,argv[2]);
   return 0;
  
}


