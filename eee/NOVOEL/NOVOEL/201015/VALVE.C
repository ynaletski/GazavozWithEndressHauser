
void f_en_two_valv();

int valve_mode=2; // 1 - два клапана с различными расходами
                  // 2 - регулируемый пилотный клапан NO_NC
                  // 3 - регулируемый клапан с электроприводом UP/DN.



void f_reg_valve();
void (*ff_valve)() = f_two_valve;

void f_init_valve()
{
 switch(valve_mode)
 {
  case 1 : ff_valve=f_two_valve; break;
  case 2 : ff_valve=f_reg_valve; break;
  case 3 : ff_valve=f_reg_valve; break;

  default: ff_valve=NULL; break;
 }
}
//----------------------------------
void f_two_valve()
{
 // отсекание дозы при помощи двух (трех) клапанов с различными расходами

float ftmp;
int itmp,itmp1;
unsigned long int ltmp;
  // CLP0 - самый большой, (#define CLP0 msk_int[num_out7],AVT_CTRL.H )
  // OUT1 - средний клапан, им управляют в функции плотности для снижения
  // расхода
  // OUT2 - меньший клапан
  // OUT3 - включение насоса
  // vol_f - заданная доза отпуска

/*
   if(flag_rcv==0)
   { // отпуск
     VolT_int= -f_int_v2();
   }
   else
*/
     VolT_int= f_int_v2();

//  VolT_int= s_MVD[0].MassT;
//  summ_v_int=VolT_int*cost_v;
  ftmp=  vol_f-VolT_int;

// в ftmp сколько литров осталось

 itmp=0;
 if(fl_GO == 1)
 {
  if(FL_err)
  {
    flag_O3=0;
   if( flag_ext_t == 0)
   //   Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
    f_stop_cnt();
    goto m_end;
  }
  TimeOut3=TimeStamp;

 if ( Flag_mass != 0 )
  {
   if(flag_O0)
    if( (ftmp-k_vol*CL_T0 )> CL_val0) itmp |= CLP0;
    else flag_O0=0;

   if(flag_O1)
    if( (ftmp-k_vol*CL_T1 )> CL_val[0]) itmp |= OUT1;
    else flag_O1=0;

   if( (ftmp-k_vol*CL_T2 )> CL_val[1]) itmp |= OUT2;
  }
  else
  {
   if(flag_O0)
    if( (ftmp-k_vol*CL_T0 )> CL_valV0) itmp |= CLP0;
    else flag_O0=0;

   if(flag_O1)
    if( (ftmp-k_vol*CL_T1 )> CL_valV[0]) itmp |= OUT1;
    else flag_O1=0;

   if( (ftmp-k_vol*CL_T2 )> CL_valV[1]) itmp |= OUT2;

  }
  if(flag_pool==1)
   if( (ftmp-k_vol*CL_T3 )<= 0)
    {
     flag_pool=0;
     ltmp=TimeStamp+CL_T4;
     I7017C[0].time_stamp_pool=ltmp;
//   I7060[0].time_stamp_pool=ltmp;
//   I7060[1].time_stamp_pool=ltmp;
//   MMI.time_stamp_pool=ltmp;
     WDOG[0].time_stamp_pool=ltmp;
    }
  if(itmp == 0)
  {// завершение по достижении заданного объема
    vol_mom=VolT_int;
    vol_mom0=vol2;
    flow_mom=k_vol;

    flag_fill_ok=1;
    f_stop_cnt();

    VolT_id=vol_f;
  }
  else
  {
     if(VolT_id< VolT_int)
             VolT_id= VolT_int;
     if(VolT_id>vol_f)  VolT_id=vol_f;
 //  summ_v_id=VolT_id*cost_v;
  }

//  if(flag_O0|flag_O1)
  {
    f_en_two_valv();
    itmp &= i_dens;
  }
 }  //  if(fl_GO == 1)

 if(flag_O3)
  if( f_timer(TimeOut3,Out3_delay_off ))
  {
   flag_O3=0;
   if( flag_ext_t == 0)
   //  Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
  }
  else
  {

#if((Add_pmp==0) || (Add_pmp==2))
   if(N_resv == 2)
    itmp |= SW_AD;
   else
#endif
    itmp |= OUT3;


    if( flag_ext_t == 0)
   //    Delta_Ctrl[0]=START_FWD_DELTA;
      f_Drive_Run();
  }
 m_end:

// itmp |= lamp_c;

// i7060_out[0] = itmp;

#if(Add_pmp==1)
 OUT_VAR &= ~(CLP0 | OUT1 | OUT2 | OUT3);
#else
 OUT_VAR &= ~(CLP0 | OUT1 | OUT2 | OUT3 | SW_AD);
#endif

 OUT_VAR |= (itmp & Out_en);

 i7060_out[0] = OUT_VAR & 0xff;
 //i7060_out[1] = (OUT_VAR>>4) & 0xf;

 if(flag_prn)
 {
// if(io_1!=itmp)
   if(io_1!=OUT_VAR)
   {
    printf("\r\nOut= %02x,%ld ms",OUT_VAR,TimeStamp-time_beg_fill);
   }
   io_1=OUT_VAR;
 }

 if(I7060[0].status)  f_7060(0);
 if(I7060[1].status)  f_7060(1);

 ServiceCOM(I7060[0].port);
 ServiceCOM(I7060[1].port);
 return;
}
/* ---------------------------------------- */
void f_en_two_valv()
{// функция анализирует состояние плотности и формирует маску выключения
 // клапана CL1: i_dens=~OUT1; при необходимости уменьшения расхода отпуска
 float ftmp;
   i_dens=0xffff;
// ftmp=s_MVD[0].Press - s_MVD[0].PressG;


 if( s_MVD[0].Press < P_min_valve)
 {
    i_dens &=~CLP0;
    i_dens &=~OUT1;
    i_dens &= ~OUT2;
    time_beg_fill=TimeStamp;
    return;
 }

 if( f_timer(time_beg_fill,cl0_delay_off) == 0 )
  { // запретить включение CL0 первые cl0_delay_off мс после начала наполнения
    i_dens &=~CLP0;
    time_chg_den0=TimeStamp;
  }
/* ==========================
 else
  {
    if( f_timer(time_chg_den0,tim_dens0) != 0 )
    {
      switch(ModeReduce)
      {
       default:
       case ReduceDens:
               if( k_Den < (-k_Den0_Off) )
               {  // скорость уменьшения плотности превысила допустимый уровень
                   f_cl0_off();
               }
               else if( fabs(k_Den) <  k_Den0_On)
                   f_cl0_on();
            break;
       //---------------------
       case ReducePress:

            if( ftmp > PressLvl_on0 ) f_cl0_on();
            else if( ftmp < PressLvl_off0) f_cl0_off();
            break;
       //---------------------
      }
    }
  }
============*/

 if( f_timer(time_beg_fill,cl1_delay_off) == 0 )
  { // запретить включение CL1 первые cl1_delay_off мс после начала наполнения
    i_dens &=~OUT1;
    time_chg_den=TimeStamp;
  }
 else if(XdN < 0)
  { // запретить включение CL1 если нет запаса давления по кавитации
    i_dens &=~CLP0;
    i_dens &=~OUT1;
    time_chg_den=TimeStamp;
  }
/*
 if ( Flag_mass != 0 )
 {
  if( (s_MVD[0].MassI-MassStamp) < Value_beg)
  {
    i_dens &=~OUT1;
    time_chg_den=TimeStamp;
  }
 }
 else
*/
  if( (s_MVD[0].VolI-VolStamp) < Vol_beg)
  {
    i_dens &=~OUT1;
    i_dens &=~CLP0;
    time_chg_den=TimeStamp;
  }

/*========================
 else
  {
   if( f_timer(time_chg_den,tim_dens) != 0 )
   {
      switch(ModeReduce)
      {
       default:
       case ReduceDens:
               if( k_Den < (-k_Den_Off) )
               {  // скорость уменьшения плотности превысила допустимый уровень
                   f_cl1_off();
               }
               else if( fabs(k_Den) <  k_Den_On)
                   f_cl1_on();
            break;
       //---------------------
       case ReducePress:

            if( ftmp > PressLvl_on1 ) f_cl1_on();
            else if(( ftmp < PressLvl_off1) && (i_dens & OUT1) ) f_cl1_off();
            break;
       //---------------------
      }
   }
  }
===============*/

  if( f_timer(time_beg_fill,cl2_delay_off) ==0 )
  { // запретить включение CL2 первые cl21_delay_off мс после начала наполнения
    i_dens &= ~OUT2;
    time_chg_den2=TimeStamp;
    beg_flch=0;
  }

/*===============
  else
  {
      switch(ModeReduce)
      {
       default:
       case ReduceDens:
              f_cl2_on();
              break;
       //---------------------
       case ReducePress:
           if( ftmp > PressLvl_on2 )
              f_cl2_on();
           else if( ftmp < PressLvl_off2)
              f_cl2_off();
           break;
       //---------------------
      }
  }
===============*/
}
/* ---------------------------------------- */
/* ---------------------------------------- */
/* ---------------------------------------- */
void  f_en_reg_valv();

float   Vol_beg  =200;  // объем цистерны до уровня погружения рукава,л
long int Flow_beg=10000;  // 3000, начальное значение расхода для заполнения цистерны до
                       // уровня рукава,кг/ч
long int Flow_nom=100000;  // 20000, номинальный расход при наполнении,кг/ч

long int Flow_min=3600;// 3600 расход при отсекании дозы,кг/ч
float    Mass_min=40;  // оставшаяся масса для снижения расхода до значения
                       // Flow_min - подготовка к отсеканию дозы

long int Flow_min1=7200;  // 7200 расход при отсекании дозы,кг/ч
float    Mass_min1=80;    // оставшаяся масса для снижения расхода до значения

long int Flow_min2=15000;  // 15000 расход при отсекании дозы,кг/ч
float    Mass_min2=300;    // оставшаяся масса для снижения расхода до значения

void f_reg_valve()
{
 // отсекание дозы при помощи регулируемого клапана

float ftmp;
int itmp,itmp1;
unsigned long int ltmp;
  //
  // OUT1 - пилот нормально открытый
  // OUT2 - пилот нормально закрытый
  //
  // OUT3 - включение насоса
  // vol_f - заданная доза отпуска

  // при достижении заданной дозы OUT1=0,OUT2=0;

     VolT_int= f_int_v2();

//  VolT_int= s_MVD[0].MassT;
//  summ_v_int=VolT_int*cost_v;
  ftmp=  vol_f-VolT_int;

// в ftmp сколько литров осталось

 itmp=0;
 if(fl_GO == 1)
 {
  if(FL_err)
  {
    flag_O3=0;
   if( flag_ext_t == 0)
   //   Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
    f_stop_cnt();
    goto m_end;
  }

//   определение заданного расхода
     if( VolT_int > Value_beg) Flow_dem = Flow_nom;
     else  Flow_dem = Flow_beg;
     if(ftmp < Mass_min) Flow_dem = Flow_min;

  TimeOut3=TimeStamp;

 if ( Flag_mass != 0 )
  {
//  if( VolT_int > Value_beg) Flow_dem = Flow_nom;
   if( (s_MVD[0].MassI-MassStamp) > Value_beg) Flow_dem = Flow_nom;
   else  Flow_dem = Flow_beg;

   if(ftmp < Mass_min) Flow_dem = Flow_min;

   if( (ftmp-k_vol*CL_T2 )> CL_val[1]) itmp |= OUT2 | OUT1;
  }
 else
  {
// if( VolT_int > Vol_beg) Flow_dem = Flow_nom;
   if( (s_MVD[0].VolI-VolStamp) > Vol_beg) Flow_dem = Flow_nom;
   else  Flow_dem = Flow_beg;

   if(ftmp < Mass_min)
        if(Flow_dem > Flow_min) Flow_dem = Flow_min;

   if(ftmp < Mass_min1)
        if(Flow_dem > Flow_min1) Flow_dem = Flow_min1;

   if(ftmp < Mass_min2)
        if(Flow_dem > Flow_min2) Flow_dem = Flow_min2;

   if( (ftmp-k_vol*CL_T2 )> CL_valV[1]) itmp |= OUT2 | OUT1;
  }
  if(flag_pool==1)
   if( (ftmp-k_vol*CL_T3 )<= 0)
    {
     flag_pool=0;
     ltmp=TimeStamp+CL_T4;
     I7017C[0].time_stamp_pool=ltmp;
//   I7060[0].time_stamp_pool=ltmp;
//   I7060[1].time_stamp_pool=ltmp;
//   MMI.time_stamp_pool=ltmp;
//   WDOG[0].time_stamp_pool=ltmp;
    }
  if(itmp == 0)
  {// завершение по достижении заданного объема
    vol_mom=VolT_int;
    vol_mom0=vol2;
    flow_mom=k_vol;

    flag_fill_ok=1;
    f_stop_cnt();

    VolT_id=vol_f;
  }
  else
  {
     if(VolT_id< VolT_int)
             VolT_id= VolT_int;
     if(VolT_id>vol_f)  VolT_id=vol_f;
 //  summ_v_id=VolT_id*cost_v;
  }

  if(fl_GO == 1)
  {
      f_en_reg_valv();
      itmp &= i_dens;
  }
 }  //  if(fl_GO == 1)

 if(flag_O3)
  if( f_timer(TimeOut3,Out3_delay_off ))
  {
   flag_O3=0;
   if( flag_ext_t == 0)
   //  Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
  }
  else
  {
    itmp |= OUT3;
    if( flag_ext_t == 0)
   //    Delta_Ctrl[0]=START_FWD_DELTA;
      f_Drive_Run();

//    if((fl_GO == 0)&& (valve_mode==3))
//    itmp |= OUT2; // закрыть клапан
  }
 m_end:

// itmp |= lamp_c;
// i7060_out[0] = itmp;

 OUT_VAR &= ~( OUT1 | OUT2 | OUT3);
 OUT_VAR |= (itmp & Out_en);

 if( (fl_GO == 0) && (valve_mode==3) )
       OUT_VAR |= OUT2; // закрыть клапан

 i7060_out[0] = OUT_VAR & 0xff;
// i7060_out[1] = (OUT_VAR>>4) & 0xf;

 if(flag_prn)
 {
   if(io_1!=OUT_VAR)
   {
    printf("\r\nOut= %02x,%ld ms",OUT_VAR,TimeStamp-time_beg_fill);
   }
   io_1=OUT_VAR;
 }

 if(I7060[0].status)  f_7060(0);
 if(I7060[1].status)  f_7060(1);

 ServiceCOM(I7060[0].port);
 ServiceCOM(I7060[1].port);
 return;
}
/* ---------------------------------------- */
float P_min_valve=0.05; // МПа, минимальное давление при котором возможно увеличить степень открытия вентиля
int State_UpDn=HOLD;

void f_UP_DN();

void  f_en_reg_valv()
{
 // функция формирует актуальные значения для OUT1,OUT2 в виде маски выключения
 // на основании циклограммы работы и заданного значения
 // требуемой величины открытия вентиля Hop  и текущего состояния вентиля
 // Hop_cur

   i_dens=0xffff;

  if( f_timer(time_beg_fill,cl2_delay_off) ==0 )
  { // запретить включение CL2 первые cl21_delay_off мс после начала наполнения
//  i_dens &= ~(OUT1|OUT2);
    time_chg_den2=TimeStamp;
    State_UpDn = DN ;
    beg_flch=0;
//  return;
  }
  else f_UP_DN(); // вычисляет состояние вентиля

   // valve_mode :            1     ;            2             ;          3
   // OUT1       : больший клапан   ; пилот нормально открытый ;  UP - открыть клапан
   // OUT2       : меньший клапан   ; пилот нормально закрытый ;  DN - закрыть клапан

  if(valve_mode==2)
  {
    if(State_UpDn == HOLD)  i_dens &= ~(OUT2);            // нормальноотокрытый включен
    else if(State_UpDn == UP ) ;                          // оба включены
    else if(State_UpDn == DN )   i_dens &= ~(OUT1|OUT2);  // оба выключены
  }
  else if(valve_mode==3)
  {
    if(Out_en == ~OUT1)   i_dens &= ~(OUT1);
    else if(State_UpDn == HOLD)  i_dens &= ~(OUT1|OUT2);  // оба выключены
    else if(State_UpDn == UP ) i_dens &= ~(OUT2);    // UP (OUT1) включен
    else if(State_UpDn == DN ) i_dens &= ~(OUT1);    // DN (OUT2) включен
  }
}
/* ---------------------------------------- */
long int Per_up_min_v=50;
long int Per_up_max_v=400;
long int Per_dn_min_v=50;
long int Per_dn_max_v=400;
long int Tim_hld=400;

long int Per_UP_dl=30; // время включения клапана UP
long int Per_DN_dl=30; // время включения клапана DN

long int Tim_up=400;
long int Tim_dn=400;
long int time_ch_v=0;

void f_UP_DN()
{
 // вычисляет состояние вентиля на основании
 // требуемой величины открытия вентиля Hop, текущего состояния вентиля
 // Hop_cur и текущей стадии вентиля
 long int ltmp;

  switch(State_UpDn)
  {
   case HOLD:
    {
      if( f_timer(time_ch_v,Tim_hld) == 0 ) break;
      ltmp= Hop - Hop_cur;
      if(ltmp > Per_up_min_v)
       { // UP
         if( s_MVD[0].Press < P_min_valve)
         {
             Hop= Hop_cur;
             YfN=Hop<<n_shft;
             XfN_2  = 0;
             XfN_1  = 0;
             break;
         }
         if(ltmp > Per_up_max_v) ltmp = Per_up_max_v;
         State_UpDn=UP;
         time_ch_v=TimeStamp;
         Tim_up=ltmp+Per_UP_dl;
         Hop_cur+=ltmp;
       }
      else if(ltmp < -Per_dn_min_v)
       { // DN
         if(ltmp < -Per_dn_max_v) ltmp = -Per_up_max_v;
         State_UpDn=DN;
         time_ch_v=TimeStamp;
         Tim_dn=Per_DN_dl-ltmp;
         Hop_cur+=ltmp;
       }
     break;
    }
   case UP  :
    {
     if( f_timer(time_ch_v,Tim_up) == 0 ) break;
     State_UpDn=HOLD;
     time_ch_v=TimeStamp;
     break;
    }

   case DN  :
    {
     if( f_timer(time_ch_v,Tim_dn) == 0 ) break;
     State_UpDn=HOLD;
     time_ch_v=TimeStamp;
     break;
    }

   default:
         State_UpDn=HOLD;
         time_ch_v=TimeStamp;
  }
}
// ----------------------------------------

float conc1=50;   // мл/м3
float conc2=50;   // мл/м3
float Add_flow=0.00277778; // расход насоса добавки,л/с (мл/мс)
float Vol_add_min=30 ; // мл
float Vol_add_beg=30; // л, объем,который должен протечь до начала ввода добавки
float Vol_add_end=500; // л, объем,который должен протечь после завершения ввода добавки

long int Tim_P_go=20;   // мс, время между включением подающего насоса добавки и включением клапана (дозатора) добавки
long int Tim_P_st=20;   // мс, время между выключением клапана (дозатора) добавки и выключением подающего насоса добавки

long int Per_Add_dl=100;   // мс, время включения клапана Add
long int Tim_hld_a=400;   // мс


float Add_cur=0;  // текущее количество влитой добавки
                  // обнуляется в avt_ctrl.c f_dlv_liq , case  5:

float Add_dem=0;  // требумое количество влитой добавки

float conc_t=50;  // исполняемое значение, мл/м3


long int Tim_add=400;
long int time_ch_add=0;
long int time_ch_add1=0;

int State_Add=HOLD;


float    Add0;
float    Add_cm;
float    Add_cm_end;


float add_mul=1;

float add_end=1;
float add_end2=1;

void  f_init_add()
// вызывается в  avt_ctrl.c f_dlv_liq , case  3:
{
 if( N_resv == 3)
   conc_t=conc2;
 else
   conc_t=conc1;

 if( (vol_f - Vol_add_end) > 0)
    add_mul=  conc_t *0.001 * (vol_f/ (vol_f - Vol_add_end));
 else
    add_mul=conc_t *0.001;

 add_end = vol_f * add_mul;
 add_end2=add_end -  Vol_add_min - Vol_add_min;

 if(flag_prn)
 {
  printf("\r\n vol_f=%f , add_mul=%f, add_end=%f\r\n",vol_f ,add_mul,add_end );
 }


}

// ----------------------------------------
//    Процедура ввода добавки.
//  Для ввода добавки должен быть задан режим - добавка 1 (N_resv==2)
//   или добавка 2 (N_resv==3)
//  Задается концентрация добавки 1 (conc1) и добавки 2 (conc1) в  мл/м3
//
//   После начала отпуска через Vol_add_beg, л, если пройден объем начального
//  наполнения Vol_beg,л  начинается ввод добавки.
//  Добавка вводится порциями согласно заданной концентрации ,исходя из
//  отпущенного количества нефтепродукта  по времени
//  открытого состояния дозатора добавки, исходя из заданного расхода
//  дозатора Add_flow л/с (мл/мс).
//   Минимальная порция добавки задается в Vol_add_min ,мл.
//   За Vol_add_end, л до завершения отпуска нефтепродукта ввод добавки
//  заканчивается , происходит промывка  рукава  от добавки.
//   За Tim_P_go,мс до включения дозатора включается соответствующий
//  насос подачи добавки (1,2).
//   Насос подачи добавки продолжает рботать Tim_P_st,мс после отключения
//  дозатора.
//   Минимальный интервал времени между выключением дозатора и его повторным
//  включением задается в Tim_hld_a,мс.
//   Этот же интервал используется для минимального времени между выключением
//  и повторным включением соответствующего насоса подачи добавки.
//   Задержка включения дозатора задается в Per_Add_dl,мс - это время
//  добавляется к времени дозирования при каждом включении дозатора.
//
//
// ----------------------------------------
void f_ADD()
{
 // вычисляет состояние вентиля добавки на основании
 // требуемой величины открытия вентиля Add_dem, текущего состояния вентиля
 // Add_cur и текущей стадии вентиля

  // vol_f    - заданная доза отпуска
  // VolT_int - отпущенная доза

 float ftmp;
 long int ltmp;

// if((fl_GO == 0) || (N_resv < 2)  ||(  (OUT_VAR & (OUT1| OUT2)) == 0) )
 if((fl_GO == 0) || (N_resv < 2)  ||(  (OUT_VAR & (OUT1)) == 0) )
 {
         State_Add=HOLD;
         time_ch_add=TimeStamp;
         time_ch_add1=TimeStamp;
 }
 else
  switch(State_Add)
  {
   case HOLD:
    {
      if( f_timer(time_ch_add,Tim_hld_a) == 0 ) break;

  m1:
      if(Add_cur == add_end)
      {
        State_Add =  HOLD;
        break;
      }

      if((vol_f - VolT_int) <= Vol_add_end)
      {
        Add_dem=add_end ;
        ftmp=add_end-Add_cur;
        goto m2;
      }
      else
      {
        Add_dem = VolT_int * add_mul ;
  /*
        if( VolT_int <  Vol_beg)
        {

          break;
        }
  */
        if(VolT_int <  Vol_add_beg)
        {

          break;
        }


      }

      ftmp= Add_dem - Add_cur ;
      if(ftmp  > Vol_add_min)
       { // UP
         if(Add_cur >  add_end2)
               ftmp=add_end-Add_cur;

m2:
         Tim_add=ftmp/Add_flow + Per_Add_dl;

         Add0=Add_cur;
         Add_cm= ftmp/Tim_add;
         Add_cm_end= Add_cur+ftmp;
         time_ch_add=TimeStamp;

         if(State_Add==PMP_STOP)
         {

           State_Add=UP;
         }
         else
         {
           State_Add=PMP_START;
         }
       }
     break;
    }

   case PMP_START  :
    { // ожидание проработки насоса добавки
      if( f_timer(time_ch_add,Tim_P_go) == 0 )  break;

      time_ch_add=TimeStamp;
      State_Add=UP;
      break;
    }

   case UP  :
    { // дозирование добавки
      if( f_timer(time_ch_add,Tim_add) == 0 )
      {
          ltmp= (TimeStamp-time_ch_add) & 0xfffffL;
          ftmp=ltmp;
          Add_cur=Add0+Add_cm*ftmp;
          if(Add_cur> Add_cm_end) Add_cur=Add_cm_end;
          break;
      }

      State_Add=PMP_STOP;
      Add_cur=Add_cm_end;
      if( fabs(Add_cur - add_end) < 1.) Add_cur=add_end;

      time_ch_add=TimeStamp;
      time_ch_add1=TimeStamp;
      break;
    }
   case PMP_STOP  :
    { // ожидание проработки насоса добавки после закрытия клапана добавки
      if( f_timer(time_ch_add1,Tim_P_st) == 0 )  goto m1;

      time_ch_add=TimeStamp;
      State_Add=HOLD;
      break;
    }


   default:
         State_Add=HOLD;
         time_ch_add=TimeStamp;
  }


  OUT_VAR &= ~(PMP_AD1 | PMP_AD2 | SW_AD  ) ;
  switch(State_Add)
  {

   case HOLD:
          break;

   case UP  :

          OUT_VAR |= SW_AD;


   case PMP_START  :
   case PMP_STOP  :

       if(N_resv ==2 )
          OUT_VAR |= PMP_AD1;
       else if(N_resv ==3 )
          OUT_VAR |= PMP_AD2;

       break;

   default:
       State_Add=HOLD;
  }

}
// ----------------------------------------



