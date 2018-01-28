
#ifndef NETCDF_FUNCTIONS_H_INCLUDED
#define NETCDF_FUNCTIONS_H_INCLUDED
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <string.h>
#include <netcdf.h>
typedef struct modis_data {
  CvMat  *chlo;


} Modis_data;


Modis_data read_netCDF_Modis (char *file_name );
void create_nc(CvMat *in_mat,CvMat *dst_mat,char *file_name);


#endif
