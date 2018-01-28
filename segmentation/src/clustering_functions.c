#include "clustering_functions.h"


/*
***
***
***
*/

CvMat *kmeans_function(CvMat *in_img, int n_clusters){
  int i,j;
  CvMat  *points = 0 ,*clusters=0,*dst_img;
  CvMat *centers = cvCreateMat( n_clusters, 1, CV_32FC1);


  points   = cvCreateMat(in_img->rows*in_img->cols,1, CV_32FC1 );
  clusters = cvCreateMat(in_img->rows*in_img->cols, 1, CV_32SC1 );

  for(i=0;i<in_img->rows;i++)for(j=0;j<in_img->cols;j++){
      points->data.fl[i+in_img->rows*j]=in_img->data.fl[i+in_img->rows*j] ;
    }

  cvKMeans2( points, n_clusters, clusters,
	     cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10000, 0.0001 ),
	     2, 0, 3, centers, 0);


  for(i=0;i<in_img->rows;i++)for(j=0;j<in_img->cols;j++){
      in_img->data.fl[i+in_img->rows*j]=clusters->data.fl[i+in_img->rows*j];
    }

  return in_img;

}



/*
***
***
***
*/



int land_counting(CvMat *in_img,int land_index){
  int i,j,c=0;
  for(i=0;i<in_img->rows;i++)for(j=0;j<in_img->cols;j++){
      c+=in_img->data.fl[i+in_img->rows*j]==land_index?1:0 ;
    }

  return c;


}



/*
***
***
***
*/

CvMat *extract_upwelling(CvMat *in_img, int upwelling_index){
  int i,j;

  for(i=0;i<in_img->rows;i++)for(j=0;j<in_img->cols;j++){
      in_img->data.i[i+in_img->rows*j]=(in_img->data.i[i+in_img->rows*j]!=upwelling_index && in_img->data.i[i+in_img->rows*j]!=12 )?10:11;
    }
  return in_img;
}



Clust_data kmeans_function2(CvMat *in_img, int n_clusters , int land_index){

  int i,j,c,s=0,d;
  CvMat  *points = 0 ,*clusters=0,*land;
  CvMat *centers = cvCreateMat( n_clusters, 1, CV_32FC1);
  Clust_data clus_out;
  
  c=in_img->rows*in_img->cols-land_counting(in_img,land_index);/* number of sea pixels */

  points   = cvCreateMat(c,1, CV_32FC1 );
  clusters = cvCreateMat(c, 1, CV_32SC1 );
  land = cvCreateMat(1, 1, CV_32FC1 );
  land->data.i[0]=12;
  //  printf("%f",  land->data.fl[0]);
  /* beging CvMat of sea pixels */
  for(i=0;i<in_img->rows;i++)for(j=0;j<in_img->cols;j++){

      if(in_img->data.fl[i+in_img->rows*j]!=land_index){

		points->data.fl[s]=in_img->data.fl[i+in_img->rows*j] ;s++;
      }
    }

  /* end CvMat of sea pixels */

  cvKMeans2( points, n_clusters, clusters,
  	     cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10000, 0.0001 ),
  	     2, 0, 3, centers, 0);

    double min,max;CvPoint min_loc,max_loc;
  cvMinMaxLoc(centers,&min,&max,&min_loc,&max_loc,NULL);

  //  printf("-----%d---",min_loc.y);
  d=min_loc.y;
  /* /\* get upwelling index *\/ */
  /* if(n_clusters==3){ */

  /* if(centers->data.fl[0]<centers->data.fl[1]&&centers->data.fl[0]<centers->data.fl[2]) */
  /*   d=0; */
  /* else if(centers->data.fl[1]<centers->data.fl[0]&&centers->data.fl[1]<centers->data.fl[2]) */
  /*   d=1; */
  /* else */
  /*   d=2;} */
  /* else{ */



  /* if(centers->data.fl[0]<centers->data.fl[1]&&centers->data.fl[0]<centers->data.fl[2]&&centers->data.fl[0]<centers->data.fl[3]) */
  /*   d=0; */
  /* else if(centers->data.fl[1]<centers->data.fl[0]&&centers->data.fl[1]<centers->data.fl[2]&&centers->data.fl[1]<centers->data.fl[3]) */
  /*   d=1; */
  /* else if(centers->data.fl[2]<centers->data.fl[0]&&centers->data.fl[2]<centers->data.fl[1]&&centers->data.fl[2]<centers->data.fl[3]) */
  /*   d=2; */
  /* else */
  /*   d=3; */
  /* } */

 
  /* /\* enf og getting upwelling index *\/ */

  
  s=0;
  for(i=0;i<in_img->rows;i++)for(j=0;j<in_img->cols;j++){

  if(in_img->data.fl[i+in_img->rows*j]!=land_index){
    in_img->data.fl[i+in_img->rows*j]= clusters->data.fl[s];s++;
  }
  else
    in_img->data.fl[i+in_img->rows*j]=land->data.fl[0];

    }
  clus_out.mat=in_img;
  clus_out.index=d;
  //in_img=extract_upwelling(in_img,d);
  
  return clus_out;

}
