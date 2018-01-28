
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
typedef struct gebco_data {
  CvMat  *bathy;


} Gebco_data;


Modis_data read_netCDF_Modis (char *file_name );
Gebco_data read_netCDF_Gebco(char *file_name);



#endif
