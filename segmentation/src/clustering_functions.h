#ifndef CLUSTERING_FUNCTIONS_H_INCLUDED
#define CLUSTERING_FUNCTIONS_H_INCLUDED
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <string.h>
#include <netcdf.h>
typedef struct clust_data {
  CvMat  *mat;
  int index;

} Clust_data;

CvMat *kmeans_function(CvMat *in_img,int n_clusters);
int land_counting(CvMat *in_img,int land_index);
CvMat *extract_upwelling(CvMat *in_img, int upwelling_index);
Clust_data kmeans_function2(CvMat *in_img,int n_clusters,int land_index);


#endif
