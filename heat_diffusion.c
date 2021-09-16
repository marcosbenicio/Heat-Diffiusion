#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define D       0.3
#define dx      1
#define dt      1
#define T       1024
#define X       1000 
#define Tprint  1024
#define Xmin    0.000000001
int main()
{
  int t,x,i;
  double u[X+1],ua[X+1],Desv;
  char arquivo[500];
  FILE *pta,*ptd;
  
  sprintf(arquivo,"difusao_D%.1lf_t%i.txt",D,Tprint);  
  pta=fopen(arquivo,"w");
  if(!pta) exit(0); 
  
  ptd=fopen("dispersao_d0,3.txt","a");
  if(!ptd) exit(0);
  Desv=0;
  //------------condição inicial----------------//  
  for(x=0;x<=X;x++) u[x]=0;  //todos os pontos da barra estão com temperatura nula
  u[0]=1;// menos no centro dela, com 1ºC
  //--------------------------------------------//
  fprintf(pta,"#x\t\t\t\t\t\t#u\n");
  for(t=1;t<=T;t++){  
     
     for(x=0;x<=X;x++) ua[x]=u[x];
 
     u[0]=ua[0]+D*(dt/(dx*dx))*(ua[1]-2.0*ua[0]+ua[1]);
     for(x=1;x<=X;x++){
         
         u[x]=ua[x]+D*(dt/(dx*dx))*(ua[x+1]-2.0*ua[x]+ua[x-1]);
         
     } 
           
     if(t==Tprint){
       
        for(x=0;x<=X;x++)if(u[x]>Xmin || u[x]==0.0){//para x=L/2 
           fprintf(pta,"%i\t\t\t\t\t\t%lf\n",x,u[x]);
           i++;  
           Desv+=x*x*u[x];
        }else break;
                      
        for(x=0;x<=i;x++){//para x=-L/2          
          fprintf(pta,"%i\t\t\t\t\t\t%lf\n",-(i-x),u[i-x]);     
        }
        fprintf(ptd,"%i\t\t\t\t\t\t%lf\n",Tprint,sqrt(2*Desv));
     }  
  }
  fclose(pta);   
  fclose(ptd);
}   





