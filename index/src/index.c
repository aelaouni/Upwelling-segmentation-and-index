#include "index.h"
int sta=0;

/*draw lines*/

IplImage* lines(int x0, int y0, int x1, int y1, IplImage* in_img,Modis_data data,Files files) {

  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
  static const double NaN = 0.0 / 0.0;
  //upwelling var
  float max[2]={1.0,1.0} , min[2]={65000.0,65000.0};
  float far_from_coast=0,ffc=NaN;
  int wind_key=0;float wind_speed,lat;int test=0,extension=0,key_ext=0,extcalc=0;
  for(;;){
    //      in_img->imageData[y0*(in_img->widthStep)+x0] = 100;


    //    begging find max and min old method
    max[0]=(data.chlo->data.fl[y0*in_img->width+x0]>max[0]&&data.chlo->data.fl[y0*in_img->width+x0]!=65535.0)?data.chlo->data.fl[y0*in_img->width+x0]:max[0];
       //       printf("     %.1f",data.chlo->data.fl[y0*in_img->width+x0]);

    //min[0]=(data.sst->data.fl[y0*in_img->width+x0]<min[0]&&far_from_coast<30&&data.sst->data.fl[y0*in_img->width+x0]>10)?data.sst->data.fl[y0*in_img->width+x0]:min[0];

    //in_img->imageData[y0*(in_img->widthStep)+x0] = 1;
    /* end find max and min old method*/

    /* extension */
    if(in_img->imageData[y0*(in_img->widthStep)+x0]==-1&&key_ext==0){
      key_ext=1;
    }
    if(in_img->imageData[y0*(in_img->widthStep)+x0]==0&&key_ext==1){
      key_ext=2;
    }
    if(key_ext==2){extcalc++;}
    if(key_ext==2&&in_img->imageData[y0*(in_img->widthStep)+x0]==-1&&extcalc<20){key_ext=1;extension+=extcalc;key_ext=1;}

    if(in_img->imageData[y0*(in_img->widthStep)+x0]==-1)
      {extension++;
      }

       /*end extension*/

    
        /* begging find max and min our method*/
    /* max[1]=(data.chlo->data.fl[y0*in_img->width+x0]<65534&&data.chlo->data.fl[y0*in_img->width+x0]>max[1]&&in_img->imageData[y0*(in_img->widthStep)+x0]==0)?data.chlo->data.fl[y0*in_img->width+x0]:max[1]; */
    /* far_from_coast++; */

    /* min[1]=(data.chlo->data.fl[y0*in_img->width+x0]<min[1]&&in_img->imageData[y0*(in_img->widthStep)+x0]==-1)?data.chlo->data.fl[y0*in_img->width+x0]:min[1]; */

    /* if(data.chlo->data.fl[y0*in_img->width+x0]<min[1]&&in_img->imageData[y0*(in_img->widthStep)+x0]==-1) */
    /*   { */
    /* 	min[1]=data.chlo->data.fl[y0*in_img->width+x0]; */
    /* 	ffc=far_from_coast; */
    /*   } */


    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }//printf("100%");
  /*begging calc of coastal upwelling index*/
  

  double cui[2]={0};

  /* cui[1]=(max[1]==0.0||min[1]==65000.0)?NaN:max[1]/1000-min[1]/1000; */
  /* cui[0]=max[0]/100-min[0]/100; */
  //  if(sta>144)
    {
//fprintf(files.fp1, "%.f ",ffc);
fprintf(files.fp2, "%f,%.3f\n",data.lats[data.latd-y0-1],max[0]);
fprintf(files.fp3, "%f,%d\n",data.lats[data.latd-y0-1],extension*4);
    }
    /*end calc of coastal upwelling index*/

  return in_img;
  
}
/*draw line*/

IplImage* line(int x0, int y0, int x1, int y1, IplImage* in_img,Modis_data data,Files files) {


  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
  double theta=atan((double)dy/(double)dx);//printf("\narctan=%f",theta);

  for(;;){
    //    setPixel(x0,y0);
    /*   printf(" %d-%d ",x0,y0); */
    /* printf("dx=%d \ndy=%d",dx,dy); */
    double b1=90;
    double a1=x0-90.0*sin(theta)+1;
    double a2=  y0-90.0*cos(theta);
    while(a1<0 || a2<0)
      {
	  a1=x0-b1*sin(theta)+1;
	a2=  y0-b1*cos(theta);
	b1--;
      }

    //printf("%f",data.chlo->data.fl[y0*in_img->width+x0]);
    //    in_img->imageData[y0*(in_img->widthStep)+x0] = 255;
       in_img=lines(x0,y0,a1,a2,in_img,data,files);
       sta++;
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
  return in_img;

}

