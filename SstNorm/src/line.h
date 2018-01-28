
#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <string.h>
#include <netcdf.h>

typedef struct line_struct{
  float *max;
  float min;
  CvMat* mat;
}Line_struct;

Line_struct line(int x0, int y0, int x1, int y1, Line_struct li,CvMat *mat);
Line_struct line_(int x0, int y0, int x1, int y1, Line_struct li,CvMat *mat);
Line_struct line__(int x0, int y0, int x1, int y1, Line_struct li,CvMat *mat,float mmin);
CvMat* scui(int x0, int y0, int x1, int y1, Line_struct li, CvMat *mat);
CvMat* scui_(int x0, int y0, int x1, int y1, Line_struct li, CvMat *mat);


#endif
