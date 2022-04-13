
//---------------------------
// Отпуск нефтепродуктов
//---------------------------
//                        номер входа (команда 'MKS')
// INP_VAR D0   7060-IN1   1
//         D1   7060-IN2   2
//         D2   7060-IN3   3
//         D3   7060-IN4   4
//         D4   7188-DI1   5
//         D5   7188-DI2   6
//---------------------------
//                        номер выхода (команда 'MKO')
// OUT_VAR D0   7060-OUT1  1
//         D1   7060-OUT2  2
//         D2   7060-OUT3  3
//         D3   7060-OUT4  4
//---------------------------
  // Дискретные входы-выходы
 //  " MKS 8 2 1 3 4 5 6"
  // ВХОДЫ
  // p1...p7.MKS
  // inp1 - ES
  // inp2 - UZA           7060-IN2 (p.6) 2
  // inp3 - датчик уровня 7060-IN1 (p.3) 1
  // inp4 - кн. "Start"   7060-IN3 (p.4) 3
  // inp5 - кн. "Stop"    7060-IN4 (p.4) 4
  // inp6   трап          7188-DI1 (p.7) 5
  // inp7   консоль       7188-DI2 (p.7) 6


//  "MKO 2 1 7 3 8"
  //p1.MKO  OUT2 -      - средний клапан 7060-OUT1  (p.5)
  //p2.MKO  OUT1 -      - меньший клапан 7060-OUT2  (p.5)
  //p3.MKO  OUT7 - PUMP - включение насоса , не исп.
  //p4.MKO  OUT3 - Air switch
  //p5.MKO  OUT8 -   - выход сигнала аварии , сигнализация   7060-OUT3  (p.5)

  //p7.MKO  CLP0 -   - больший клапан

//---------------------------
void f_alarm();
unsigned int OUT_VAR=0;    // состояние дискретных выходов
unsigned int INP_VAR=0;    // состояние дискретных входов
unsigned int INP_inv=0;    // маска инверсии входов
unsigned int INP_VAR_c=0;  // копия состояния дискретных входов
unsigned int INP_VARi=0;    // состояние дискретных входов
unsigned int INP_MSK_OK=0;    // состояние дискретных входов
unsigned int OUT_VAR_c=0;  // копия состояния дискретных входов


int flag_ext_t=0;
int Drive_SV_beg[2]={5000,5000};  // 50 Hz, значение частоты вращения
int Drive_SA_beg[2]={20,20}; // текущее состояние времени ускорения 2 сек
int Drive_SD_beg[2]={20,20};  // текущее состояние  замедления 2 сек на 100Гц

int f_St_chk_fict()
{
 return 1;
}
int f_Rn_chk_fict()
{
 return 0;
}
void f_fict()
{
}

int status_fct=0;
int *DriveStatus=&status_fct;

int DriveSV[3]={1000,1000,1000};
int DriveSA[3]={100,100,100};
int DriveSD[3]={100,100,100};
int DriveState[3]={0,0,0};
int DriveCurrent[3]={0,0,0};
int DriveError[3]={0,0,0};

int (*f_Drive_St_chk)()=f_St_chk_fict;
int (*f_Drive_Rn_chk)()=f_Rn_chk_fict;
void (*f_Drive_Stop)()=f_fict;
void (*f_Drive_Run)()=f_fict;



//             температура
//          давление |
//                 | |   0x60
int analog_num[8]={6,7,0,0,0,0,0,0};
float analog_scale[8]={1./MaxADC,1./MaxADC,1./MaxADC,1,1,1,1,1};
float analog_offset[8]= {0,0,0,0,0,0,0,0};

int fl_GO=0;    // флаг отпуска/приема через MVD
int fl_EQ=0;    // флаг выравнивания давления через MVD
int flagS_ES=0; // признак останова по нажатию ES
int flagS_UZA=0; // признак останова по отсутствию UZA
int flagE_UZA=0; // код ошибки


int flagS_DLT=0; // признак останова по состояниию DELTA

int flag_rcv=0;

long int time_com_cl=2000; // мс, время включения клапанов коммутации
long int time_com_cl_off=2000; // мс, время выключения клапанов  коммутации
long int time_cnt_cl_off=2000; // мс, задержка между остановом счета и выключением клапанов коммутации
long int time_gas_cl_on =2000; // мс, время включения клапанов пара
long int time_gas_cl_off=2000; // мс, время выключения клапанов пара

long int time_EQ_rcv=200; // секунд
long int time_EQ_dlv=200; // секунд
long int time_LIQ_rcv=600; // секунд
long int time_LIQ_dlv=600; // секунд

int flag_dlv_fst=0; // 0 - сбросить Mass total перед началом отпуска приема
int flag_prn_mass=0;

int sw_dlv_liq=0;
int sw_dlv_gas=0;
int sw_rcv_liq=0;
int sw_rcv_gas=0;

int flag_continue=0;

//char *list_avt[]={
char list_avt[][32]={

"Действие отменено.ESC - меню",  // 0
"Sht-ESC очистка ошибок      ",  // 1
"   !Нажата аварийная кнопка  ", // 2
"   Действие невозможно.      ", // 3
"    !Нет сигнала УЗА         ", // 4
"Настройка счета расходомера  ", // 5
" !Нет связи с расходомером   ", // 6
"Таймаут связи с расходомером ", // 7
"Обнуление отсчета расходомера", // 8
" !Уровень ниже допустимого   ", // 9
"Включение потока жидкости    ", //10
" Трап не в рабочем положении ",//11
"                              ",//12
" Выключение потока жидкости   ",//13
"Консоль не в рабочем положении",//14
"Действие остановлено.ESC-меню",//15
" Ожидание нажатия кн. =Пуск=  ",//16
"Отпуск.Выр-е давл.паровых фаз ",//17
"",//18
"2-продолжить отпуск жидк.фазы ",//19
"ESC - завершить отпуск        ",//20
" Выключение потока паров      ",//21
"        Ошибки очищены        ",//22
" ESC - продолжить             ",//23
"!Драйверы MVD,7060 не включены",//24
"       !Останов отпуска       ",//25
"         Доза отпущена        ",//26
" В расходомере нет жидкой фазы",//27
" ESC - меню                   ",//28
" Расход снизился до пред.знач.",//29
"      Отпуск остановлен       ",//30
"     Нажата кнопка =ESC=      ",//31
" Авария насоса при торможении ",//32
"     Нажата кнопка =STOP=     ",//33
"       ID не корректен        ",//34
"       по команде Host        ",//35
};

char *list_rcv[]={
"Прием.Выр-е давл.паровых фаз  ",//0 17
"2-продолжить прием жидкой фазы",//1 19
"ESC - завершить прием         ",//2 20
"       !Останов приема        ",//3 25
"        Доза принята          ",//4 26
"      Прием остановлен        ",//5 30
};

long int time_t_snd=0;
long int time_t_swtch=0;
int sw_ret=0;

long int Tim_Prep1  =12000;  // ms
long int Tim_Prep_ND=6000; // ms
float    P_beg_valve=0.2;     // MPa
float    F_Dns_off  =20;        // kg/hour

int Flag_dns_flow=0;

//-----------------------------
int key__1=0;
int f_dlv_liq(int key)
{
// подготовка к отпуску и отпуск жидкой фазы
//
//  если key == ESC - останов потока , после завершения процедуры
//  останова потока возвращает значение ESC.
//
// return: ESC -  поток остановлен , переход в меню отпуска
//          по нажатию кнопки 'ESC'
//
    sw_dlv_slv=sw_dlv_liq;
    if((FL_err) && (sw_dlv_liq != -1))
    {
      f_clr_scr_MMI();
      f_disp_error();

//    MmiGotoxy(0,5);   MmiPuts("Отпуск невозможен.ESC - меню");
//    MmiGotoxy(0,6);   MmiPuts("Sht-ESC очистка ошибок");
      MmiGotoxy(0,5);   MmiPuts(list_avt[0]);
      MmiGotoxy(0,6);   MmiPuts(list_avt[1]);

      fl_GO=0;
      fl_EQ=0;
      OUT_VAR=0;
      sw_dlv_liq=-1;
      Temperature=s_MVD[0].Temp;
      Density=s_MVD[0].Dens;
      f_wr_evt(evt_err_f+flag_rcv);
    }

  switch(sw_dlv_liq)
  {
   // начальное состояние - все клапаны закрыты,
   // насос остановлен
   // подготовка к отпуску жидкой фазы

   case 1:  // начало отпуска с жидкой фазы

    key__1=0;
m1:
   Out_off(OUT4);  // Air switch off
   if( (INP_VARi & ES_IN)==0 )
    {
       f_icp_errS(ES_off);
//     MmiGotoxy(0,1);    MmiPuts("  !Нажата аварийная кнопка   ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[2]);

m_errP:
#if(PML_P != 0)
       flag_prn_mass=0;
       Modef &= ~pmp1_dlvr_bit;
       p1_state |= End_dlvr;
#endif

m_err:
//     MmiGotoxy(0,0);    MmiPuts("  Отпуск невозможен.         ");
       MmiGotoxy(0,0);    MmiPuts(list_avt[3]);
       State_SLV=Cmd_brk;

       sw_dlv_liq=-1;
       return 0;
    }
   if( (INP_VARi & UZA_IN)==0  )
    {
       flagE_UZA=UZA_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("  !Нет сигнала УЗА           ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[4]);
       goto m_errP;
    }
    if( id_ok==0)
    {
       flagE_UZA=ID_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("     Не корректный ID         ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[34]);
       goto m_errP;
    }
   if( (INP_VARi & LVL_IN)==0 )
    {
       flagE_UZA=LVL_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts(" !Уровень ниже допустимого");
       MmiGotoxy(0,1);    MmiPuts(list_avt[9]);
       goto m_errP;
    }
   if( (INP_VARi  & TRAP_IN)==0 )
    {
       flagE_UZA=TRAP_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts(" Трап не в рабочем положении ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[11]);
       goto m_errP;
    }
   if( (INP_VARi  & CONS_IN)==0 )
    {
       flagE_UZA=CONS_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("Консоль не в рабочем положении");
       MmiGotoxy(0,1);    MmiPuts(list_avt[14]);
       goto m_errP;
    }

    sw_dlv_liq=3;
    time_t_swtch=TimeStamp;
    flag_continue=0;

    MmiGotoxy(0,1);    MmiPuts(list_avt[16]);
    break;
//-----------------------------
   case  3:
   if((INP_VARi & STRT_IN) || (key==Sht_F1)  || (*(int *)list_Slv_int[i_cfm] == Strt_cmd) )
   {


     INP_VARi_1=INP_VARi;

     *(int *)list_Slv_int[i_cfm]=0;
     MVD_t_rslt[0]=0;
 MVD_Rqst_T[0].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[0].answ_flt=f_MVD_rd_t;


     if(flag_dlv_fst==0)
       sw_dlv_liq=5;
     else
       sw_dlv_liq=7;
     time_t_swtch=TimeStamp;
   }
   else if( (INP_VARi & STOP_IN)==0)
   {
       MmiGotoxy(0,0);   MmiPuts(list_avt[30]);  //" Отпуск остановлен            ",//30
       MmiGotoxy(0,1);   MmiPuts(list_avt[33]);  //"     Нажата кнопка =STOP=     ",//31
       State_SLV=Cmd_brk;
       sw_dlv_liq=-1;
#if(PML_P != 0)
       flag_prn_mass=0;
     Modef &= ~pmp1_dlvr_bit;
       p1_state |= End_dlvr;
#endif
   }
   else if(key==ESC)
   {
       MmiGotoxy(0,0);   MmiPuts(list_avt[30]);  //" Отпуск остановлен            ",//30
       MmiGotoxy(0,1);   MmiPuts(list_avt[31]);  //" Нажата кнопка   ESC          ",//31
       State_SLV=Cmd_brk;
       sw_dlv_liq=-1;
#if(PML_P != 0)
       flag_prn_mass=0;
       Modef &= ~pmp1_dlvr_bit;
       p1_state |= End_dlvr;
#endif
   }
   else goto m1;
   break;
//-----------------------------
   case  5:
     // обнуление Mass_Total и Volume_Total
 MVD_t_rslt[0]=0;

 Add_cur=0;

 time_t_snd=TimeStamp;
  MmiGotoxy(0,1);    MmiPuts(list_avt[8]); //"Обнуление отсчета расходомера");
   // Reset all totalizers
 if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 3,(int)1,(long int) 0,(float)0)== 0)
 { // ошибка при отправке посылки MVD
       f_icp_errS(MVD_com);
//  MmiGotoxy(0,1);  MmiPuts("!Нет связи с расходомером    ");
    MmiGotoxy(0,1);  MmiPuts(list_avt[6]);
       goto m_err;
 }
  sw_dlv_liq=6;
  break;
//-----------------------------
   case  6:
    // ожидание завершения команды обнуления totalizers
    if( MVD_t_rslt[0]>0)
    {
     sw_dlv_liq=7;
     flag_dlv_fst=1; // Mass Total обнулена

     VolI_beg=s_MVD[0].VolI;
     s_MVD[0].VolT=0;
     s_MVD[0].MassT=0;

     Sim_VolT=0.;
     Sim_MassT=0.;

     flag_prn_mass=1;
     vol2=0;
     VolT_int=0;
     VolT_id=0;
     Add_cur=0;

     break;
    }
    if(key==ESC)    // переход в меню
         return ESC;
m_wait:
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // время вышло
       MmiGotoxy(0,1);  MmiPuts(list_avt[7]); //"Таймаут связи с расходомером ");
       f_icp_errS(MVD_com);
       goto m_err;
    }
    break;
//-----------------------------

   case  7:
  // разрешение расхода расходомера без счета

 MVD_t_rslt[0]=0;
 time_t_snd=TimeStamp;
  MmiGotoxy(0,1);    MmiPuts("Разрешение счета расходомера");

       // Stop totalizers
 if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)0,(long int) 0,(float)0)== 0)
 { // ошибка при отправке посылки MVD

m_err_mvd:
            f_icp_errS(MVD_com);
      //  "!Нет связи с расходомером    "
         MmiGotoxy(0,1);  MmiPuts(list_avt[6]);
            goto m_err;
 }
    sw_dlv_liq=71;
  break;

//-----------------------------
   case  71:

    if( MVD_t_rslt[0]>0)
    {
      MVD_t_rslt[0]=0;
      //
      time_t_snd=TimeStamp;

    // установка значения среза массового расхода для рабочего режима
      if( f_MVD_WR((int)0,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,cutoff_on_M) == 0)
      { // ошибка при отправке посылки MVD
          goto m_err_mvd;
      }
      sw_dlv_liq=8;
    }
    else goto m_wait;
  break;

//-----------------------------
   case 8:
    // ожидание завершения команды установки cutoff for Mass Flow
    if( MVD_t_rslt[0]>0)
    {
      MVD_t_rslt[0]=0;
      time_t_snd=TimeStamp;

   // установка значения среза объемного расхода для рабочего режима
      if( f_MVD_WR((int)0,(int)MVD_WR_F,(int) 197,(int)0,(long int) 0,cutoff_on_V) == 0)
      { // ошибка при отправке посылки MVD
       goto m_err_mvd;
      }
      sw_dlv_liq=9;
      break;
    }
    else goto m_wait;
//-----------------------------
   case  9:
    // ожидание завершения команды установки cutoff for Vol Flow

    if( MVD_t_rslt[0]>0)
    {
       sw_dlv_liq=11;
//     MmiGotoxy(0,1);  MmiPuts("Включение потока жидкости    ");
       MmiGotoxy(0,1);  MmiPuts(list_avt[10]);
       break;
    }
    else goto m_wait;
//-----------------------------
   case  11:
       //  Включение потока жидкости
      volume_f=dose_dlvr;
      vol_f=dose_dlvr;
      Dens0=s_MVD[0].Dens;

      f_init_add();
      f_enable_cnt();
    // запретить открывание клапанов
      Out_en =  ~(OUT1 | OUT2);
//  time_beg_fill=TimeStamp;
//  beg_flch=0;
//  flag_flch=0;
      time_t_swtch=TimeStamp;
      MmiGotoxy(0,0);
       if(dose_dlvr != vBIG_P)
        {
         if ( Flag_mass != 0 )
           MmiPrintf(" Отпуск дозы %g кг         ",dose_dlvr);
         else
           MmiPrintf(" Отпуск дозы %g л          ",dose_dlvr);
        }
       else
          MmiPuts("  Отпуск без дозировки        ");
//    MmiGotoxy(0,1);      MmiPuts("                              ");
      MmiGotoxy(0,1);      MmiPuts(list_avt[12]);
//    MmiGotoxy(0,2);      MmiPuts("                              ");
      MmiGotoxy(0,2);      MmiPuts(list_avt[12]);

        sw_dlv_liq=110;
        t_prep_MVD=TimeStamp;
        t_prep_MVD1=TimeStamp;

        Flag_dns_flow=0;
   break;
//-----------------------------

   case 110:
      // насос работает,все клапаны закрыты
      // проверка состояния

  time_beg_fill=TimeStamp;
  beg_flch=0;
  flag_flch=0;

      if( f_timer(t_prep_MVD, Tim_Prep1 ) == 0 )
       {
         if( s_MVD[0].Press > P_beg_valve);
         else
         {
          Flag_dns_flow=0;
          t_prep_MVD1=TimeStamp;
         }

         if( fabs(s_MVD[0].FlowM) < F_Dns_off) ;
         else
         {
             Flag_dns_flow=1;
             t_prep_MVD1=TimeStamp;
         }
         if( f_timer(t_prep_MVD1, Tim_Prep_ND ) != 0 )
         { // антидребезг прошел
           t_prep_MVD=TimeStamp;
           sw_dlv_liq=111;

             // Start totalizers

           MVD_t_rslt[0]=0;
           time_t_snd=TimeStamp;
           if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)1,(long int) 0,(float)0)== 0)
           { // ошибка при отправке посылки MVD
                 goto m_err_mvd;
           }

         }
       }
      else
       {  // время начальной проверки вышло, есть утечка или нет давления

         if(Flag_dns_flow != 0)
           f_icp_errS(DNS_not_off);
         else
           f_icp_errS(No_Press);
         break;
       }
       break;

//-----------------------------
  case 111:
    // ожидание завершения команды  Start totalizers

  time_beg_fill=TimeStamp;
  beg_flch=0;
  flag_flch=0;
    if( MVD_t_rslt[0]>0)
    {
      Out_en =  0xffff;
      sw_dlv_liq=12;
      break;
    }
    else goto m_wait;
//-----------------------------
   case  12:
       //  отпуск
    if(FL_err)    // переход к процедуре отключения
    {
        key__1=ESC;
        sw_dlv_liq=30;
    }
    else if(key==ESC)       // переход к процедуре отключения
    {
        key__1=key;
        sw_dlv_liq=30;
    }
    if( (INP_VARi & STOP_IN)==0 ) // переход к процедуре отключения
    {
    // нажата кнопка "STOP"
        key__1=STOP_E;
        sw_dlv_liq=30;
    }
    else if(fl_GO==0 ) // переход к завершению по прекращению отпуска
    {
      key__1=-1;
      MmiGotoxy(0,0);   MmiPuts(list_avt[25]);
//    MmiGotoxy(0,1);   MmiPuts(list_avt[25]);
      sw_dlv_liq=30;
    }
    break;
//-----------------------------
   case  30:
      // выключение клапанов регулирующих расход
      // поочередно с задержкой TimDensWt0
/*
      Out_en=~CLP0;
      time_t_snd=TimeStamp;
      sw_dlv_liq=31;
      break;
//-----------------------------
   case  31:

    if( f_timer(time_t_snd,TimDensWt0 ) )
    {  // время вышло
*/

  if(valve_mode==1)
  {
      Out_en=~CLP0;
      Out_en &= ~OUT1;
  }
  else if(valve_mode==2)
  {
      Out_en =  ~OUT1;
      Out_en &= ~OUT2;
  }
  else if(valve_mode==3)
  {
      Out_en =  ~OUT1;
  }
      time_t_snd=TimeStamp;
      sw_dlv_liq=32;

//    }
      break;
//-----------------------------
   case  32:

    if( f_timer(time_t_snd,TimDensWt0 ) )
    {  // время вышло
      if(valve_mode==1)
      {
        Out_en &= ~OUT2;
      }
/*
      else if(valve_mode==2)
      {
      }
      else if(valve_mode==3)
      {
      }
 */
      time_t_snd=TimeStamp;
      sw_dlv_liq=33;
    }
      break;
//-----------------------------
   case  33:

    if( f_timer(time_t_snd,TimDensWt0 ) )
    {  // время вышло
      sw_dlv_liq=40;
    }
      break;
//-----------------------------
//-----------------------------
   case  40:
      // останов потока

       time_t_swtch=TimeStamp;
       Temperature=s_MVD[0].Temp;
       Density=s_MVD[0].Dens;
       f_stop_cnt();
       sw_dlv_liq=41;
//     MmiGotoxy(0,1);  MmiPuts(" Выключение потока жидкости   ");
       MmiGotoxy(0,1);  MmiPuts(list_avt[13]);
       time_t_snd=TimeStamp;

    break;
//-----------------------------
   case  41:
      // ожидание останова двигателя насоса

     if( f_timer(time_t_snd,T_Mot_Stop ) )
     {  // время вышло
m_mot_not:
       f_icp_errS(MotNotStop);
       Temperature=s_MVD[0].Temp;
       Density=s_MVD[0].Dens;
       key__1=0;
       f_alarm();
//     f_wr_evt(evt_est_f+flag_rcv);
//    "      Отпуск остановлен       ", //30
       MmiGotoxy(0,0);  MmiPuts(list_avt[30]);
   // " Авария насоса при торможении ",//32
       MmiGotoxy(0,1);  MmiPuts(list_avt[32]);
   // " ESC - меню                   ",//28
       MmiGotoxy(0,6);  MmiPuts(list_avt[28]);
       sw_dlv_liq=-1;
     }
     else
     {
//     if(Delta[0].status==0)
       if( *DriveStatus ==0)
       {
         sw_dlv_liq=42;
         time_t_snd=TimeStamp;
         break ;
       }
//     if((Delta_State[0] & MSK_RUN_DELTA ) == STP_DELTA )
       if(f_Drive_St_chk() == 1)
       {
         sw_dlv_liq=42;
         time_t_snd=TimeStamp;
       }
     }
      break;
//-----------------------------
//-----------------------------
   case  42:
    // задержка на время между остановом счета и выключением клапанов коммутации
    // time_cnt_cl_off
//  if(OUT_VAR & OUT1) time_t_snd=TimeStamp;
//  if(OUT_VAR & OUT2) time_t_snd=TimeStamp;
    if(OUT_VAR & OUT3) time_t_snd=TimeStamp;
    if( f_timer(time_t_snd,time_cnt_cl_off ) )
    {  // время вышло
//     MmiGotoxy(0,1);    MmiPuts("Выключение клап-в коммутации ");
//    MmiGotoxy(0,1);    MmiPuts(list_avt[14]);
//    Out_off(GAS1);
//    Out_off(GAS2);
//    Out_off(LIQ2);
      time_t_snd=TimeStamp;
      sw_dlv_liq=44;
    }
    break;
//-----------------------------
   case  44:

    if(ff_serv_N== NULL)
    {
       sw_dlv_liq=-1;
       if(key__1== ESC)
       {
m_esc:
        MmiGotoxy(0,0);   MmiPuts(list_avt[30]);  //" Отпуск остановлен            ",//30
        MmiGotoxy(0,1);   MmiPuts(list_avt[31]);  //" Нажата кнопка   ESC          ",//31
        MmiGotoxy(0,6);   MmiPuts(list_avt[28]);  //" ESC - меню                   ",//28
        break;
       }
       else if(key__1== STOP_E)
       {
        MmiGotoxy(0,0);   MmiPuts(list_avt[30]);  //" Отпуск остановлен            ",//30
        MmiGotoxy(0,1);   MmiPuts(list_avt[33]);  //"     Нажата кнопка =STOP=     ",//31
        MmiGotoxy(0,6);   MmiPuts(list_avt[28]);  //" ESC - меню                   ",//28
        break;
       }
       else if(key__1== STOP_H)
       {
        MmiGotoxy(0,0);   MmiPuts(list_avt[30]);  //" Отпуск остановлен            ",//30
        MmiGotoxy(0,1);   MmiPuts(list_avt[35]);  //" по команде Host        ",//31
        MmiGotoxy(0,6);   MmiPuts(list_avt[28]);  //" ESC - меню                   ",//28
        break;
       }
       else if (FL_err)
       {
         f_clr_scr_MMI();
         f_disp_error();
//       MmiGotoxy(0,6);       MmiPuts("Отпуск прерван.ESC - меню    ");
         MmiGotoxy(0,6);       MmiPuts(list_avt[15]);
         break;
       }

//          MmiGotoxy(0,0);   MmiPuts(" Отпуск остановлен            "  );
            MmiGotoxy(0,0);   MmiPuts(list_avt[30]);
//          MmiGotoxy(0,6);       MmiPuts(" ESC - меню    ");
            MmiGotoxy(0,6);       MmiPuts(list_avt[28]);
       if((flag_fill_ok!=0)&&(flag_gas ==0) )
          {
//          MmiGotoxy(0,1);       MmiPuts(" Доза отпущена     ");
            MmiGotoxy(0,1);

         if ( Flag_mass != 0 )
              MmiPrintf(" Доза %g кг отпущена            ",dose_dlvr);
         else
              MmiPrintf(" Доза %g л отпущена             ",dose_dlvr);

//          MmiGotoxy(0,1);  MmiPrintf(" Доза           кг отпущена  ");

            dose_dlvr=vBIG_P;

            break;
          }
          else if(flag_gas !=0)
          {
//          MmiGotoxy(0,1);       MmiPuts(" В расходомере нет жидкой фазы");
            MmiGotoxy(0,1);       MmiPuts(list_avt[27]);
            break;
          }
          else if(flag_flch !=0)
          {
//          MmiGotoxy(0,1);       MmiPuts(" Расход снизился до пред.знач.");
            MmiGotoxy(0,1);       MmiPuts(list_avt[29]);
            break;
          }
          else break;
    }
    else
     if( f_timer(time_t_snd,(t_mvd_cor*3) ) )
     {  // время вышло
       ff_serv_N = NULL;
       f_icp_errS(MVD_com);
      Temperature=s_MVD[0].Temp;
      Density=s_MVD[0].Dens;
       f_wr_evt(evt_est_f+flag_rcv);
//     MmiGotoxy(0,1);  MmiPuts("!Нет связи с расходомером    ");
       MmiGotoxy(0,1);  MmiPuts(list_avt[6]);
       goto m_err;
     }
    break;
//-----------------------------
//-----------------------------
    case -1:
       if((key==ESC)||(key==ENTER)  )    // переход в меню
         return ESC;
       else if (key==Sht_ESC)
        {  // очистка ошибок
          f_clr_scr_MMI();
          SetDisplayPage(23);
          f_cl_error();
//        MmiGotoxy(0,2);    MmiPuts("        Ошибки очищены       ");
//        MmiGotoxy(0,4);    MmiPuts(" ESC - продолжить            ");
          MmiGotoxy(0,5);    MmiPuts(list_avt[22]);
          MmiGotoxy(0,6);    MmiPuts(list_avt[23]);
          return ESC;
        }
       else
         return 0;
//-----------------------------
  }
  return 0;
}
//-----------------------------
//-----------------------------
/*
void Out_on(int msk)
{
 OUT_VAR |= msk;
}
//-----------------------------
void Out_off(int msk)
{
 OUT_VAR &= ~msk;
}
*/
//-----------------------------
void f_alarm()
{
   ff_serv_N=f_MVD_cor;
   tm_mvd_p=TimeStamp;
   t_prep_MVD=TimeStamp;
   State_SLV=Stp_cnt;
   fl_GO=0;
   TimeOut3=TimeStamp-Out3_delay_off;
}
//-----------------------------
int INP_VARi_1=0;
void f_sens()
{ // проверяет состояние кнопки ES и UZA при отпуске/приеме СУГ
  // сигналы исчезают  - отпуск/прием прерывается
  // inp1 - ES
  // inp2 - UZA


//  i7060_out[0] = itmp;

  if( (fl_GO | fl_EQ) != 0)
  {


    if(MVD[0].status == 0)
      if ( (INP_VARi_1  & STRT_IN)==0 )
      {
        if ( (INP_VARi  & STRT_IN)!= 0 )
         {
          flag_O1 ^= 1;
         }
      }

    if( (INP_VARi  & INP_MSK_OK) != INP_MSK_OK )
    {
       if(( INP_VARi  & ES_IN)==0 )
        {
           flagS_ES=1;
           f_icp_errS(ES_off);
           goto m_err1;

        }
       if( (INP_VARi & UZA_IN)==0 )
        {
           flagE_UZA=UZA_E;
m_err:
           flagS_UZA=1;
           f_icp_errS(UZA_off);
m_err1:
           f_alarm();
           f_stop_cnt();
           sw_dlv_liq=-1;
           f_clr_scr_MMI();
           f_disp_error();

//         MmiGotoxy(0,5);   MmiPuts("Отпуск невозможен.ESC - меню");
//         MmiGotoxy(0,6);   MmiPuts("Sht-ESC очистка ошибок");
           MmiGotoxy(0,5);   MmiPuts(list_avt[0]);
           MmiGotoxy(0,6);   MmiPuts(list_avt[1]);
           goto m1;
        }
       if( (INP_VARi & LVL_IN)==0 )
        {
           flagE_UZA=LVL_E;
           goto m_err;
        }
       if( id_ok==0)
        {
          flagE_UZA=ID_E;
          goto m_err;
        }
       if( (INP_VARi  & TRAP_IN)==0 )
        {
           flagE_UZA=TRAP_E;
           goto m_err;
        }
       if( (INP_VARi  & CONS_IN)==0 )
        {
           flagE_UZA=CONS_E;
           goto m_err;
        }
    }
  }
m1:
  if( (flag_O3!=0) && ( (OUT_VAR & (CLP0|OUT1|OUT2) ) != 0) )
  {
//    if(Delta[0].status !=0 )

    if( *DriveStatus != 0)
    {
//     if((Delta_State[0] & MSK_RUN_DELTA ) != RUN_DELTA )
       if(f_Drive_Rn_chk() != 1)
       {
         flagS_DLT=1;
         f_icp_errS(DLT_off);
         f_alarm();
         f_stop_cnt();
       }
    }
  }

  INP_VARi_1=INP_VARi;

  return;
}
//-----------------------------
void f_inp7188()
{
// вводит входные сигналы  I7188 и записывает их в
// D4,D4 INP_VAR

 INP_VAR &= 0xff0f;
 INP_VAR |= (GetDi1() << 4) & 0xf0;
 INP_VAR |= (GetDi2() << 4) & 0xf0;
 INP_VARi = INP_VAR ^ INP_inv;

}
//-----------------------------
