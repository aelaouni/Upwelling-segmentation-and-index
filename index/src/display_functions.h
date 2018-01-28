#ifndef DISPLAY_FUNCTIONS_H_INCLUDED
#define DISPLAY_FUNCTIONS_H_INCLUDED
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <string.h>
#include <netcdf.h>

IplImage * ind2rgb(CvMat *in_img);
void shownsave(IplImage *in_img);
void showCvMat(CvMat *in_img);
void saveIpl(IplImage *in_img,char *file_name);

#endif
