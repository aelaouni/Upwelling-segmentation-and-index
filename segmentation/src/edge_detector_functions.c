#include"edge_detector_functions.h"
IplImage *canny(CvMat *in_img)
{
 //canny
  //  cvSmooth( src, dst,3,0,0,0 );
  IplImage *src,*dst;
  CvSize ImageSize1 = cvSize(in_img->cols,in_img->rows);
  src = cvCreateImage(ImageSize1,IPL_DEPTH_8U,1);
  dst = cvCreateImage(ImageSize1,IPL_DEPTH_8U,1);
  int i,j;
  for(i=0;i<in_img->rows;i++)for(j=0;j<in_img->cols;j++){

      src->imageData[i*src->widthStep+j] =in_img->data.i[i*in_img->cols+j]==1?255:0 ;

    }
  
  
 cvCanny(src, dst, 1,2, 5); 
 //
    
 /* cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE);  */
 /* cvMoveWindow("mainWin", 100, 100); */
 /* cvShowImage("mainWin", dst ); */
 /* // wait for a key */
 /* cvWaitKey(0); */
 /* // release the image */
 /* cvReleaseImage(&src); */
 
 return src;
}
