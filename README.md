# Upwelling segmentation and index

### Anass El Aouni (INRIA Bordeaux)


License This software is made public for research use only. It may be modified and redistributed under the terms of the GNU General Public License.

The present code allows you to identify and extract the North-West African upwelling spans (20°51N-36°21N and 4°26W-19°97W).
It also allows you to calculate the spatial and temporal variation of the upwelling index and its spatial extension.

Please cite the following paper if you use the code in your own work:

Segmentation, quantification and dynamics of coastal Upwelling using SST satellite images
Anass El Aouni, Khalid Daoudi, Khalid Minaoui, Hussein Yahia
IEEE Transactions on Geoscience and Remote Sensing (TGRS), submitted on January 2018


Instalation notes:


required library:

NetCDF-C https://www.unidata.ucar.edu/downloads/netcdf/index.jsp

OpenCv-c https://opencv.org/

After you unzipped the files, you'll find 3 folders:


-SstNorm: use the codes inside to calculate the nonlinear normalization of the sea surface temperature.

-Segmentation: use the codes inside to segment the upwelling region.

-Index: use the code inside to calculate the coastal upwelling index and its extension.



all the folders contain an example of use. 


The SST products used in this work are from MODIS-Terra and distributed by NASA OceanColor (https://oceancolor.gsfc.nasa.gov/)
