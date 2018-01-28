#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <string.h>
#include <netcdf.h>
#include "netcdf_functions.h"

typedef struct files {
  	FILE *fp1 ;
  	FILE *fp2 ;
  	FILE *fp3 ;

} Files;


IplImage* lines(int x0, int y0, int x1, int y1, IplImage* in_img,Modis_data data,Files files);

IplImage* line(int x0, int y0, int x1, int y1, IplImage* in_img,Modis_data data,Files files);

#endif
