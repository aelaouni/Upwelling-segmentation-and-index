#include "netcdf_functions.h"
#include "display_functions.h"
#include "index.h"



int main(int argc ,char **argv)
{

  Modis_data data,mask;
  data=read_netCDF_Modis(argv[1]);
  //mask=read_netCDF_Modis("mask.nc");
  IplImage *rgb;
  CvMat *mat,*land,*rg,*out_img,*can;
  //    showCvMat(mask.chlo);
	Files files ;
  // files.fp1 = fopen("out/ffc.txt", "a");
   files.fp2 = fopen(argv[3], "a");
   files.fp3 = fopen(argv[4], "a");
   //files.fp3 = fopen("out/exten.txt", "a");
   //fprintf(files.fp1, "\n");
//   fprintf(files.fp2, "\n");
   //fprintf(files.fp3, "\n");

  IplImage *in_img,*dst_img;
  int i,j;
    int wind_key=0;float wind_speed,lat;int test=0,extension=0,key_ext=0,extcalc=0;

  in_img= cvLoadImage(argv[2], 0 );
    dst_img = line(340,47,80,370,in_img,data,files);
  
}
