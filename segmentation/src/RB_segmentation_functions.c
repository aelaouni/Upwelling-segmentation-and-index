#include "RB_segmentation_functions.h"



/* CvMat *RegionGrowing_function(int x,int y,CvMat *in_img,CvMat *out_img){ */
/*       printf("(%d %d) ",x,in_img->data.i[y*in_img->rows+x]); */

/*   if(out_img->data.i[y*out_img->rows+x]==0){ */
/*     if(in_img->data.i[y*in_img->rows+x]==4){ */

/*       out_img->data.i[y*in_img->rows+x]=1; */

/*       if (x > 2 && out_img->data.i[y*out_img->rows+(x-1)]==0 ) */
/* 	return RegionGrowing_function(x-1,y,in_img,out_img); */
/*       if (y > 2 && out_img->data.i[(y-1)*out_img->rows+x]==0 ) */
/* 	return RegionGrowing_function(x,y-1,in_img,out_img); */
/*       if (x < in_img->cols - 2 && out_img->data.i[y*out_img->rows+(x+1)]==0) */
/* 	return RegionGrowing_function(x+1,y,in_img,out_img); */
/*       if (y < in_img->rows - 2 && out_img->data.i[(y+1)*out_img->rows+x]==0) */
/* 	return RegionGrowing_function(x,y+1,in_img,out_img); */

/* 	} */
    
/*   } */

/*   return out_img; */
/* } */


CvMat *RegionGrowing_function(int x,int y,CvMat *in_img ,CvMat *out_img){
  //printf("(%d %d %d ) ",x,y,in_img->data.i[y*in_img->rows+x]);
  if(out_img->data.i[y*out_img->cols+x]==0){


if(in_img->data.i[y*in_img->cols+x]==10){
  //printf("%f ",in_img->data.i[y*in_img->rows+x]);

      out_img->data.i[y*in_img->cols+x]=1;

      if (x > 2 && out_img->data.i[y*out_img->cols+(x-1)]==0 )
	out_img = RegionGrowing_function(x-1,y,in_img,out_img);
      if (y > 2 && out_img->data.i[(y-1)*out_img->cols+x]==0 )
	out_img = RegionGrowing_function(x,y-1,in_img,out_img);
      if (x>-1 && x < in_img->cols - 2 && out_img->data.i[y*out_img->cols+(x+1)]==0)
	out_img = RegionGrowing_function(x+1,y,in_img,out_img);
      if (y>-1 && y < in_img->rows - 2 && out_img->data.i[(y+1)*out_img->cols+x]==0)
	out_img = RegionGrowing_function(x,y+1,in_img,out_img);

	}
    
  }
  return out_img;
  
}






/* void *RegionGrowing_function(int x,int y,CvMat *in_img){ */
/*   //printf("(%d %d %d ) ",x,y,in_img->data.i[y*in_img->rows+x]); */
/*   if(out_img->data.fl[y*out_img->cols+x]==0){ */


/* if(in_img->data.fl[y*in_img->cols+x]==255){ */
/* printf("%f ",in_img->data.i[y*in_img->rows+x]); */

/*       out_img->data.fl[y*in_img->cols+x]=255; */

/*       if (x > 2 && out_img->data.i[y*out_img->cols+(x-1)]==0 ) */
/* 	RegionGrowing_function(x-1,y,in_img); */
/*       if (y > 2 && out_img->data.i[(y-1)*out_img->cols+x]==0 ) */
/* 	RegionGrowing_function(x,y-1,in_img); */
/*       if (x>-1 && x < in_img->cols - 2 && out_img->data.i[y*out_img->cols+(x+1)]==0) */
/* 	RegionGrowing_function(x+1,y,in_img); */
/*       if (y>-1 && y < in_img->rows - 2 && out_img->data.i[(y+1)*out_img->cols+x]==0) */
/* 	RegionGrowing_function(x,y+1,in_img); */

/* 	} */
    
/*   } */

  
/* } */


