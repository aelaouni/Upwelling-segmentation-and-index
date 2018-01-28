#include "netcdf_functions.h"
#include "display_functions.h"
#include "clustering_functions.h"
#include "RB_segmentation_functions.h"
#include "edge_detector_functions.h"



int main(int argc ,char **argv)
{
  Clust_data clust_data;
  Modis_data data,mask;
  Gebco_data gdata;
  data=read_netCDF_Modis(argv[1]);
   mask=read_netCDF_Modis("norm.nc");
  IplImage *rgb;
  CvMat *mat,*land,*rg,*out_img,*can;

  //rg = cvCreateMat(data.chlo->rows,data.chlo->cols, CV_32SC1);
  //can = cvCreateMat(data.chlo->rows,data.chlo->cols, CV_32SC1);
  //cvZero(rg);
  out_img = cvCreateMat(data.chlo->rows,data.chlo->cols, CV_32SC1 );
  cvZero(out_img);
  int i,j,key=0,x,ff_cost=0;

  for(i=0;i<mask.chlo->rows*mask.chlo->cols;i++)
    mask.chlo->data.fl[i]=mask.chlo->data.fl[i]==65535?0:1;
    
  double min,max;CvPoint m,M;
  cvMinMaxLoc(data.chlo,&min,&max,&m,&M,NULL);
  //   printf("%d",Mx);   


  clust_data=kmeans_function2(data.chlo,2,65535); 
    
  mat=extract_upwelling(clust_data.mat,clust_data.index);
  
  for(j=1;j<mask.chlo->rows;j+=4){
    ff_cost=0;key=0;
    for(i=mask.chlo->cols;i>0;i--)
      {
	if( mask.chlo->data.fl[j*mask.chlo->cols+i-1]==1&&key==0&&ff_cost<1)
	  {key=1;x=i;ff_cost++;}
      }
    out_img= RegionGrowing_function(x,j-1,mat,out_img); /*apply RG for first coordinates*/
    // printf("%d,%d  ",x,j);
  }
  /*end of seeking */

  //out_img= RegionGrowing_function(x,84,mat,out_img); /*apply RG for first coordinates*/
  printf("done");
  IplImage *src_;
    CvSize ImageSize1 = cvSize(mat->cols,mat->rows);
  src_ = cvCreateImage(ImageSize1,IPL_DEPTH_8U,1);

  for(i=0;i<mat->rows;i++)for(j=0;j<mat->cols;j++){

      src_->imageData[i*src_->widthStep+j] =mat->data.i[i*mat->cols+j]==10?255:0 ;

    }
  
  IplImage *src;
  //  shownsave(ind2rgb(out_img));
  src=canny(out_img);
   saveIpl(src,argv[2]);
//   saveIpl(src_,"ff.png");

  return 0;
  
}
