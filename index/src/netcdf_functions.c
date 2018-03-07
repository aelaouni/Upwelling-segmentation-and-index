#include "netcdf_functions.h"

#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); /* return 2; */}



Modis_data read_netCDF_Modis(char *file_name)
{
#define NI 378
#define NJ 378

  // Variable definitions.  The comments contain the dimension names.
  size_t start[3], count[3];
  int ncid, l3m_data_varid,lat_dimid,lat_varid;
  int i,j;
  float *l3m_data;                 // lat, lon
  l3m_data = (float *)malloc(sizeof(float)*NI*NJ);

  int l3m_data_var;

  int retval;

  double *lat;
  long lat_dim;
  if ((retval = nc_open(file_name, NC_NOWRITE, &ncid)))
    ERR(retval);
  if ((retval = nc_inq_varid(ncid, "SST", &l3m_data_var)))
    ERR(retval);
  //   printf("%d",sea_surface_temperature_var);
  if ((retval = nc_get_var_float(ncid, l3m_data_var, l3m_data)))
    ERR(retval);

  /* get lat_dim */
  if ((retval = nc_inq_dimid(ncid, "latitude", &lat_dimid)))
    ERR(retval);
  if ((retval = nc_inq_dimlen(ncid, lat_dimid, &lat_dim)))
    ERR(retval);
  lat = (double *)malloc(sizeof(double)*lat_dim);
  if ((retval = nc_inq_varid(ncid, "latitude", &lat_varid)))
    ERR(retval);
  if ((retval = nc_get_var_double(ncid, lat_varid, lat)))
    ERR(retval);

  Modis_data data;
  data.chlo=0;
  data.chlo= cvCreateMat(NI,NJ, CV_32FC1 );
  data.lats=lat;
  data.latd=lat_dim;

  for(i=0;i<NI;i++)for(j=0;j<NJ;j++){
      
      data.chlo->data.fl[i*NJ+j]=l3m_data[NJ*(NI-i-1)+j] ;
      //      data.chlo->data.fl[i+NI*(NJ-j-1)]=l3m_data[NI*j+i] ;
      //      printf("%f",l3m_data[NJ*(NI-i-1)+j]);
    }

  return data;}




