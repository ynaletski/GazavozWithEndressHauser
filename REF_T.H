

float f_get_VCF(float Temp, float D_ref);
float f_get_T(float D1,float D_ref, float T_ref);
float f_get_ref_Dns(float D_obs, float Temp,float Press, float T_Ref);
extern int type_liq;  // 2 Fuel Oils   - диэтопливо

void f_init_DNSA();
void f_cnt_DnsA();
extern double Dens_cmn;
extern float Dens_cmn_f;

//18.11.2021 YN
#if defined(weightedAverageTemperature)
extern int waTempOn;
extern float waTemp;
extern double mas_ch_cur_old;
extern double mas_ch_cur;
#endif


//08.02.2022 YN
#if(Shtray==2) //Promass
extern double mas_ch1_cur_old;
extern float MassT_old;
extern double mas_ch1_cur;
extern double vol_ch2_cur;
extern double mas_ch1_start;
extern double vol_ch2_start;
extern double mas_ch1_end;
extern double vol_ch2_end;
#endif