
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int type_liq=2;  // 2 Fuel Oils   - диэтопливо
                 // 5 Gazolines   - бензин
                 // 1 Crude Oils

//
// значения коэффициентов и формулы согласно API Standard 2540 from 1980
// (из документа Saab Rosemount "TankMaster,Inventory Calculations")
//
#define Kerosene (4)

float KK0[7]={ //type_liq
613.9723,     //0 Crude Oils
613.9723,     //1 Crude Oils
186.9696,     //2 Fuel Oils   - диэтопливо
594.5418,     //3 Jet  group
594.5418,     //4 Kerosene
346.42278,    //5 Gazolines   - бензин
0.0,          //6 Lubricating Oils
};

float KK1[7]={ //type_liq
0.0,          //0 Crude Oils
0.0,          //1 Crude Oils
0.48618,       //2 Fuel Oils
0.00,         //3 Jet  group
0.00,         //4 Kerosene
0.43884,       //5 Gazolines
0.62780,      //6 Lubricating Oils
};

float Aa= -0.00336312, Bb= 2680.3206;

float f_get_VCF(float Temp,float D_ref, float T_ref)
{
// по текущей температуре , референсной плотности и референсной температуре
// вычисляет VCF
// использует type_liq - тип продукта
//
//  V_ref=V_obs * f_get_VCF(Temp,D_ref,T_Ref);
//

double TecTref;
double  dT;
float VCF;

  if((type_liq > 6) || (type_liq < 1)) return 1.;
  if(D_ref==0) return 1;

  dT=Temp-T_ref;

  if(type_liq != Kerosene)
     TecTref = (KK0[type_liq]+KK1[type_liq]* D_ref)/(D_ref*D_ref);
  else
     TecTref= Aa + Bb/(D_ref*D_ref);

  if(T_ref == 20.0)
    VCF=exp( -TecTref * dT * (1.0 + (8.0*TecTref) + (0.8*TecTref*dT) ));
  else
    VCF=exp( -TecTref * dT * (1.0 + (0.8*TecTref*dT) ));

 return VCF;
}
/*-------------------------------------------*/
#define n_max 10
#define MinDNS 0.001


float f_get_ref_Dns(float D_obs, float Temp, float T_Ref)
{
// по наблюдаемой плотности D_obs и текущей температуре Temp
// вычисляет референсную плотность для заданной референсной температуры T_Ref

int i;
float D_ref_new,D_ref_old;
float VCF_ref;

  D_ref_old=D_obs;

  for(i=0;i<n_max;i++)
  {
    VCF_ref= f_get_VCF( Temp,D_ref_old,T_Ref);
    if(VCF_ref == 0) return 1;
    D_ref_new=D_obs / VCF_ref;
    if( fabs(D_ref_old-D_ref_new) < MinDNS) break;
    D_ref_old=D_ref_new;
  }

//  printf("\n\r f_get_ref_Dns, i= %d,D_ref=%g,VCF=%g",i,D_ref_new,VCF_ref);

  return D_ref_new;
}
/*----------------------------------------------------*/
/*----------------------------------------------------*/
float f_get_T(float D1,float D_ref, float T_ref)
{
// return Temperature for current D1 for known D_ref,T_ref

double TecTref;
double  dT;
float Temp;
double A,B,C,DD,VCF;

  if((type_liq > 6) || (type_liq < 1)) return -1000.;
  if(D_ref==0) return -1000.;
  VCF=D1/D_ref;

  if(type_liq != Kerosene)
     TecTref = (KK0[type_liq]+KK1[type_liq]* D_ref)/(D_ref*D_ref);
  else
     TecTref= Aa + Bb/(D_ref*D_ref);
/*
  if(T_ref == 20.0)
    VCF=exp( -TecTref * dT * (1.0 + (8.0*TecTref) + (0.8*TecTref*dT) ));
  else
    VCF=exp( -TecTref * dT * (1.0 + (0.8*TecTref*dT) ));
*/
  if(T_ref == 20.0)
  {
   A= -TecTref  * 0.8 * TecTref;
   B= -TecTref * (1.0 + 8.0*TecTref);
   C= -log(VCF);
  }
  else
  {
   A= -TecTref  * 0.8 * TecTref;
   B= -TecTref ;
   C= -log(VCF);
  }
  DD= (B*B-4.0*A*C);
  dT=(-B - sqrt(DD) )/(2.0*A);
  Temp = dT + T_ref;
  return Temp;
}
/*----------------------------------------------------*/
/*
void main()
{
    float D_ref=820, D_obs=800, Temp=23, T_Ref=15;
    float D1=200,Mass,Vol,T1,VCF;

m1:
    printf( "\nEnter Density, Temp : " );
    if(scanf ("%f %f", &D_obs,&Temp ))
    {
      D_ref=f_get_ref_Dns( D_obs, Temp,T_Ref);
      printf("\n D_ref(%f)=%f",T_Ref,D_ref);
    }
    else exit(0);
m2:
    printf( "\nEnter D1: " );
    if( scanf("%f",&D1 ) )
    {
  //      D1=Mass*1000./Vol;
      T1=f_get_T( D1,D_ref, T_Ref);
      printf("\n D1=%f kg/m3,T1=%f",D1,T1);
    }
    else exit(0);

    goto m2;
}
*/
/*----------------------------------------------------*/

