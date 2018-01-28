#ifndef RG_SEGMENTATION_FUNCTIONS_H_INCLUDED
#define RG_SEGMENTATION_FUNCTIONS_H_INCLUDED
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <string.h>
#include <netcdf.h>
//CvMat *out_img;

//void *RegionGrowing_function(int x,int y,CvMat *in_img);
CvMat *RegionGrowing_function(int x,int y,CvMat *in_img,CvMat *out_img);



#endif
