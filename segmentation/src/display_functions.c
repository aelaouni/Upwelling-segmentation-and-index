#include "display_functions.h"

/*function convert mastrix to rgb   */
IplImage * ind2rgb(CvMat *in_img){
  
  IplImage *Image1,*Image2,*Image3,*out,*dst;

  CvSize ImageSize1 = cvSize(in_img->cols,in_img->rows);
  Image1 = cvCreateImage(ImageSize1,IPL_DEPTH_8U,1);
  Image2 = cvCreateImage(ImageSize1,IPL_DEPTH_8U,1);
  Image3 = cvCreateImage(ImageSize1,IPL_DEPTH_8U,1);
  dst=cvCreateImage( ImageSize1, 8, 3 ) ;
  int My [5][3];

  //  blue non upwelling
  My[0][0]=255;
  My[0][1]=0;
  My[0][2]=0;
  //black land
  My[1][0]=0;
  My[1][1]=0;
  My[1][2]=0;
  //red
  My[2][0]=0;
  My[2][1]=0;
  My[2][2]=255;
   //wite upwellig 
  My[3][0]=255;
  My[3][1]=255;
  My[3][2]=255;
  //green
  My[4][0]=0;
  My[4][1]=255;
  My[4][2]=0;

  int i,j,k=0;

  for(i=0;i<in_img->rows;i++)for(j=0;j<in_img->cols;j++){

      Image1->imageData[i*Image1->widthStep+j] = My[in_img->data.i[i*in_img->cols+j]][0];
      Image2->imageData[i*Image2->widthStep+j] = My[in_img->data.i[i*in_img->cols+j]][1];
      Image3->imageData[i*Image3->widthStep+j] = My[in_img->data.i[i*in_img->cols+j]][2];

    }
  cvMerge(Image1, Image2, Image3, NULL, dst );
  return dst;
}
void shownsave(IplImage *in_img){
  int p[3];

  p[0] = CV_IMWRITE_PNG_COMPRESSION;
  p[1] = 9;
  

  cvSaveImage("test.png", in_img,p);//

  cvNamedWindow("Red",1);
  cvShowImage("Red",in_img);
  cvWaitKey(0);

  cvReleaseImage(&in_img);
  cvDestroyWindow("Red");
}

void showCvMat(CvMat *in_img){
  int p[3];

  p[0] = CV_IMWRITE_PNG_COMPRESSION;
  p[1] = 9;
  

  cvSaveImage("test1.png", in_img,p);//

  /* cvNamedWindow("Red",1); */
  /* cvShowImage("Red",in_img); */
  /* cvWaitKey(0); */

}
void saveIpl(IplImage *in_img,char *file_name){
  int p[3];

  p[0] = CV_IMWRITE_PNG_COMPRESSION;
  p[1] = 9;
  

  cvSaveImage(file_name, in_img,p);//
}
