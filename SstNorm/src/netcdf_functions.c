#include "netcdf_functions.h"
#include <string.h>
#include <stdio.h>

#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); /* return 2; */}



Modis_data read_netCDF_Modis(char *file_name)
{
#define NI 378
#define NJ 378

  // Variable definitions.  The comments contain the dimension names.
  size_t start[3], count[3];
  int ncid, l3m_data_varid;
  int i,j;
  float *l3m_data;                 // lat, lon
  l3m_data = (float *)malloc(sizeof(float)*NI*NJ);

  int l3m_data_var;

  int retval;

  if ((retval = nc_open(file_name, NC_NOWRITE, &ncid)))
    ERR(retval);
  if ((retval = nc_inq_varid(ncid, "SST", &l3m_data_var)))
    ERR(retval);
  //   printf("%d",sea_surface_temperature_var);
  if ((retval = nc_get_var_float(ncid, l3m_data_var, l3m_data)))
    ERR(retval);
  Modis_data data;
  data.chlo=0;
  data.chlo= cvCreateMat(NI,NJ, CV_32FC1 );


  for(i=0;i<NI;i++)for(j=0;j<NJ;j++){
      
      data.chlo->data.fl[i*NJ+j]=l3m_data[NJ*(NI-i-1)+j] ;
      //      data.chlo->data.fl[i+NI*(NJ-j-1)]=l3m_data[NI*j+i] ;
      //      printf("%f",l3m_data[NJ*(NI-i-1)+j]);
    }

  return data;}




void create_nc(CvMat *in_mat,CvMat *dst_mat,char *file_name)
{
/* We are writing 2D data, a 6 x 12 lat-lon grid. We will need two
 * netCDF dimensions. */
#define NDIMS 2
  int NLAT = in_mat->rows;
  int NLON = in_mat->cols;
  char *LAT_NAME = "latitude";
  char *LON_NAME = "longitude";

/* Names of things. */

  char *TEMP_NAME ="SST";
  char *UPWELLING_NAME ="upwelling";
  char *UNITS ="units";
  char *MISS_VAL= "_FillValue";
  float MISSING_VALUE =(65535.);
  char *DEGREES_EAST = "degrees_east";
  char *DEGREES_NORTH = "degrees_north";

/* These are used to construct some example data. */
#define START_LAT 110.54167551
#define START_LON 160.0000128
  int ncid, lon_dimid, lat_dimid, temp_varid,upwelling_varid;

/* In addition to the latitude and longitude dimensions, we will also
   create latitude and longitude netCDF variables which will hold the
   actual latitudes and longitudes. Since they hold data about the
   coordinate system, the netCDF term for these is: "coordinate
   variables." */
   int lat_varid, lon_varid;

   int dimids[NDIMS];

   /* We will write surface temperature and pressure fields. */

   float temp_out[NLAT][NLON];
   float upwelling_out[NLAT][NLON];
   float lats[NLAT], lons[NLON];
   float fill_val;

   /* It's good practice for each netCDF variable to carry a "units"
    * attribute. */

   char temp_units[] = "celsius";

   /* Loop indexes. */
   int lat, lon;
   
   /* Error handling. */
   int retval;

   /* Create some pretend data. If this wasn't an example program, we
    * would have some real data to write, for example, model
    * output. */
   for (lat = 0; lat < NLAT; lat++)
      lats[lat] = START_LAT + lat*0.04166667 - 90.0;
   for (lon = 0; lon < NLON; lon++)
      lons[lon] = -180.0 + START_LON + lon*0.04166667;
   
   for (lat = 0; lat < NLAT; lat++)
      for (lon = 0; lon < NLON; lon++)
      {
	//	 pres_out[lat][lon] =
	//	if(in_img->imageData[NLON*(NLAT-lat-1)+lon]==-1)
	if(dst_mat->data.fl[NLON*(NLAT-lat-1)+lon]!=MISSING_VALUE)
	temp_out[lat][lon] = in_mat->data.fl[NLON*(NLAT-lat-1)+lon];
	else
	temp_out[lat][lon] = MISSING_VALUE;

	if(dst_mat->data.fl[NLON*(NLAT-lat-1)+lon]!=MISSING_VALUE)
	upwelling_out[lat][lon]=dst_mat->data.fl[NLON*(NLAT-lat-1)+lon];
	else
	upwelling_out[lat][lon] = MISSING_VALUE;
	
      }

   /* Create the file. */
   if ((retval = nc_create(file_name, NC_CLOBBER, &ncid)))
      ERR(retval);

   /* Define the dimensions. */
   if ((retval = nc_def_dim(ncid, LAT_NAME, NLAT, &lat_dimid)))
      ERR(retval);
   if ((retval = nc_def_dim(ncid, LON_NAME, NLON, &lon_dimid)))
      ERR(retval);

   /* Define coordinate netCDF variables. They will hold the
      coordinate information, that is, the latitudes and longitudes. A
      varid is returned for each.*/
   if ((retval = nc_def_var(ncid, LAT_NAME, NC_FLOAT, 1, &lat_dimid, 
			    &lat_varid)))
      ERR(retval);
   if ((retval = nc_def_var(ncid, LON_NAME, NC_FLOAT, 1, &lon_dimid, 
			    &lon_varid)))
      ERR(retval);

   /* Define units attributes for coordinate vars. This attaches a
      text attribute to each of the coordinate variables, containing
      the units. Note that we are not writing a trailing NULL, just
      "units", because the reading program may be fortran which does
      not use null-terminated strings. In general it is up to the
      reading C program to ensure that it puts null-terminators on
      strings where necessary.*/
   if ((retval = nc_put_att_text(ncid, lat_varid, UNITS, 
				 strlen(DEGREES_NORTH), DEGREES_NORTH)))
      ERR(retval);
   if ((retval = nc_put_att_text(ncid, lon_varid, UNITS, 
				 strlen(DEGREES_EAST), DEGREES_EAST)))
      ERR(retval);

   /* Define the netCDF variables. The dimids array is used to pass
      the dimids of the dimensions of the variables.*/
   dimids[0] = lat_dimid;
   dimids[1] = lon_dimid;
   if ((retval = nc_def_var(ncid, TEMP_NAME, NC_FLOAT, NDIMS, 
			    dimids, &temp_varid)))
      ERR(retval);

   /* if ((retval = nc_def_var(ncid, UPWELLING_NAME, NC_FLOAT, NDIMS,  */
   /* 			    dimids, &upwelling_varid))) */
   /*    ERR(retval); */

   /* Define units attributes for vars. */
   if ((retval = nc_put_att_text(ncid, temp_varid, UNITS, 
				 strlen(temp_units), temp_units)))
      ERR(retval);

   /* if ((retval = nc_put_att_text(ncid, upwelling_varid, UNITS,  */
   /* 				 strlen(temp_units), temp_units))) */
   /*    ERR(retval); */
   if ((retval = nc_put_att_text(ncid, NC_GLOBAL, "author", 
				 strlen("Anass El Aouni"), "Anass El Aouni")))
      ERR(retval);
   if ((retval = nc_put_att_text(ncid, NC_GLOBAL, "contact", 
				 strlen("anas.elaouni@gmail.com"), "anas.elaouni@gmail.com")))
      ERR(retval);

  char af[strlen(file_name)];
  strcpy(af, file_name);
  af[strlen(file_name)-3]='\0';

  if ((retval = nc_put_att_text(ncid, NC_GLOBAL, "product Name",
      				 strlen(4+af), 4+af)))
      ERR(retval);

   
   fill_val = (float)MISSING_VALUE;


   if ((retval = nc_put_att_float(ncid, temp_varid, "missing_value",
   				  NC_FLOAT,1, &fill_val)))
      ERR(retval);
   /* if ((retval = nc_put_att_float(ncid, upwelling_varid, "missing_value", */
   /* 				  NC_FLOAT,1, &fill_val))) */

   /*  ERR(retval); */

   /* End define mode. */
   if ((retval = nc_enddef(ncid)))
      ERR(retval);

   /* Write the coordinate variable data. This will put the latitudes
      and longitudes of our data grid into the netCDF file. */
   if ((retval = nc_put_var_float(ncid, lat_varid, &lats[0])))
      ERR(retval);
   if ((retval = nc_put_var_float(ncid, lon_varid, &lons[0])))
      ERR(retval);

   /* Write the pretend data. This will write our surface pressure and
      surface temperature data. The arrays of data are the same size
      as the netCDF variables we have defined. */
   if ((retval = nc_put_var_float(ncid, temp_varid, &temp_out[0][0])))
      ERR(retval);

   /* if ((retval = nc_put_var_float(ncid, upwelling_varid, &upwelling_out[0][0]))) */
   /*    ERR(retval); */

 
   
   /* Close the file. */
   if ((retval = nc_close(ncid)))
      ERR(retval);
   
   printf("*** SUCCESS writing nc file\n");

}
