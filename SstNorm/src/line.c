#include"line.h"

/*draw line*/

Line_struct line(int x0, int y0, int x1, int y1, Line_struct li, CvMat *mat) {

  /* li.max[0]=0;  li.max[1]=0; */
  /* li.max[2]=0; */
  /* li.max[3]=0; */
  /* li.max[4]=0; */
  /* li.max[5]=0; */
  int i=0;
  li.max[0]=0;
  li.max[1]=0;
  li.max[2]=0;
  li.max[3]=0;
  li.max[4]=0;
  li.max[5]=0;
  li.max[6]=0;
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
  double theta=atan((double)dy/(double)dx);//printf("\narctan=%f",theta);

  for(;;){


    //    setPixel(x0,y0);
    //         printf(" %d ",x0);
    /* printf("dx=%d \ndy=%d",dx,dy); */
    if(mat->data.fl[x0*378+y0]!=65535.&&mat->data.fl[x0*378+y0]>li.max[i])
      {li.max[i]=mat->data.fl[x0*378+y0];
	i=i<6?i+1:0;
      }

    if (x0==x1 && y0==y1) break;
    e2 = err; 
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
  li.max[6]=(li.max[0]+li.max[1]+li.max[2]+li.max[3]+li.max[4]+li.max[5])/6;

  return li;}
Line_struct line_(int x0, int y0, int x1, int y1, Line_struct li, CvMat *mat) {

  /* li.max[0]=0;  li.max[1]=0; */
  /* li.max[2]=0; */
  /* li.max[3]=0; */
  /* li.max[4]=0; */
  /* li.max[5]=0; */
  int i=0,j=0,xx=x0;
  li.max[0]=0;
  li.max[1]=0;
  li.max[2]=0;
  li.max[3]=0;
  li.max[4]=0;
  li.max[5]=0;
  li.max[6]=0;
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
  double theta=atan((double)dy/(double)dx);//printf("\narctan=%f",theta);
  li.min=65355;
  for(;;){
    //    mat->data.fl[x0*378+y0]=65535;
    j++;
    //    setPixel(x0,y0);
    //      printf(" %d-%d ",x0,y0);
    /* printf("dx=%d \ndy=%d",dx,dy); */
    if(mat->data.fl[x0*378+y0]!=65535.&&mat->data.fl[x0*378+y0]>li.max[i]&&mat->data.fl[x0*378+y0]<22.37)
      {li.max[i]=mat->data.fl[x0*378+y0];
	i=i<6?i+1:0;
      }
    if(mat->data.fl[x0*378+y0]!=65535.&&mat->data.fl[x0*378+y0]<li.min)
      {li.min=mat->data.fl[x0*378+y0];

      }

    if (x0==x1 && y0==y1) break;
    e2 = err; 
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
  li.max[6]=(li.max[0]+li.max[1]+li.max[2]+li.max[3]+li.max[4]+li.max[5])/6;
  
  return li;}
Line_struct line__(int x0, int y0, int x1, int y1, Line_struct li, CvMat *mat,float mmin) {

  /* li.max[0]=0;  li.max[1]=0; */
  /* li.max[2]=0; */
  /* li.max[3]=0; */
  /* li.max[4]=0; */
  /* li.max[5]=0; */
  int i=0,j=0,xx=x0;
  li.max[0]=0;
  li.max[1]=0;
  li.max[2]=0;
  li.max[3]=0;
  li.max[4]=0;
  li.max[5]=0;
  li.max[6]=0;
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
  double theta=atan((double)dy/(double)dx);//printf("\narctan=%f",theta);
  li.min=65355;
  for(;;){

    j++;
    //    setPixel(x0,y0);
    //      printf(" %d-%d ",x0,y0);
    /* printf("dx=%d \ndy=%d",dx,dy); */
    if(mat->data.fl[x0*378+y0]!=65535.&&mat->data.fl[x0*378+y0]>li.max[i]&&mat->data.fl[x0*378+y0]-mmin<6)
      {li.max[i]=mat->data.fl[x0*378+y0];
	i=i<6?i+1:0;
      }
    if(mat->data.fl[x0*378+y0]!=65535.&&mat->data.fl[x0*378+y0]<li.min)
      {li.min=mat->data.fl[x0*378+y0];

      }

    if (x0==x1 && y0==y1) break;
    e2 = err; 
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
  li.max[6]=(li.max[0]+li.max[1]+li.max[2]+li.max[3]+li.max[4]+li.max[5])/6;
  
  return li;}

CvMat* scui_(int x0, int y0, int x1, int y1, Line_struct li, CvMat *mat) {

  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
  int xx=x0,j=0;
  double theta=atan((double)dy/(double)dx);//printf("\narctan=%f",theta);

  for(;;){
    j++;
    //    setPixel(x0,y0);
    //      printf(" %d-%d ",x0,y0);
    /* printf("dx=%d \ndy=%d",dx,dy); */
      li.mat->data.fl[x0*378+y0]=65535.;
    if (x0==x1 && y0==y1) break;
    e2 = err; 
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }

  return li.mat;}

CvMat* scui(int x0, int y0, int x1, int y1, Line_struct li, CvMat *mat) {

  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
  double theta=atan((double)dy/(double)dx);//printf("\narctan=%f",theta);

  for(;;){
    //    setPixel(x0,y0);
    //      printf(" %d-%d ",x0,y0);
    /* printf("dx=%d \ndy=%d",dx,dy); */
    if(mat->data.fl[x0*378+y0]!=65535.)
      {li.mat->data.fl[x0*378+y0]=li.max[6]-mat->data.fl[x0*378+y0];
      }
    else
      li.mat->data.fl[x0*378+y0]=65535.;
    if (x0==x1 && y0==y1) break;
    e2 = err; 
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }

  return li.mat;}
