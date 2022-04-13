
//#define ZeroPage 0
//#define ZeroPage 6
//#define ZeroPage 8

#define Adr_ASN (AddrSlv)

#if((Add_pmp == 0) || (Add_pmp == 1))

char *list_md_add[]={
" Без добавок",   //0
" Без добавок",   //1
" С добавкой " ,  //2
//" Добавка N1 " ,  //2
" Добавка N2 " ,  //3
" Добавка N3 " ,  //4
" Добавка N4 " ,  //5
};

#endif

#define n_mmi_str 7 // количество строк на дисплее MMI
#define n_mmi_str_1 (n_mmi_str-1)
#define n_mmi_str_2 (n_mmi_str-2)
#define n_mmi_str_3 (n_mmi_str-3)
#define n_mmi_str_4 (n_mmi_str-4)
float ftmp_DP=1;
float ftmp_LP=0;
int mode_hst = 0;
int flag_resv=0;
int N_resv=1;
int NN_resv=0;
int N_resv_tmp=0;
int N_resv_dsp[5]={0,1,2,3,4};


//
//  Файл содержит символьные данные в DOS кодировке символов.
//  Для отображения на дисплее MMI необходимо перекодировать в
//  кодировку Windows (выполняется командой dos_win.exe в .bat)
//



float MassStamp=-1000.;
float VolStamp=-1000.;

float vBIG_P=BIG_P;

long int fl_zeroing=0;
#define Time_zeroing (50000)
long int zero_time;

char s_empty[]="                              ";
char str_ESC[]="ESC  Возврат";

void f_d_ESC()
{
  MmiGotoxy(0,6); MmiPuts(str_ESC);
}

int PageD=0;
int flg_ch=0;
int Flag_f_corr=0,flag_mass=0,pass_ret=0;
float k_v_flow=1,k_m_flow=1;
float k_mv_tmp;
long int pass1=0,pass2=0;

void f_prn_ID();
void  f_prn_begin()
{

  if( id_ok==0) f_prn_ID();
  else if(CRC_err) f_prn_CRC_error();
  else if(FL_err) f_prn_error();
  else
  {
    f_clr_scr_MMI();


#if defined(MMI_NEW)

  MmiGotoxy(0,0); MmiPrintf("╔═════════╦═════════╗         ");
  MmiGotoxy(0,1); MmiPrintf("║Доза,кг  ║ Отп.,л  ║         ");
  MmiGotoxy(0,2); MmiPrintf("╠═════════╬═════════╣         ");
  MmiGotoxy(0,3); MmiPrintf("║         ║         ║         ");
  MmiGotoxy(0,4); MmiPrintf("╟─────────╫─────────╢         ");
  MmiGotoxy(0,5); MmiPrintf("║         ║         ║         ");
  MmiGotoxy(0,6); MmiPrintf("║         ║         ║         ");
  MmiGotoxy(0,7); MmiPrintf("╚═════════╩═════════╝         ");

#endif


#if defined(MMI_ICP)
            //  MmiPrintf("                              ");
  MmiGotoxy(1,1);  MmiPrintf("  Система учета отпуска  ");
  MmiGotoxy(1,2);  MmiPrintf("  нефтепродуктов.АСН %d.   ",Adr_ASN);
            //             "  Показания счетчика          "

     //     if(PageD==0)
          {
  MmiGotoxy(0,3) ; MmiPrintf("Масса       :                ");
  MmiGotoxy(0,4) ; MmiPrintf("Объем       :                ");


 if(I7017C[0].status)
 {
  MmiGotoxy(0,5) ; MmiPrintf("P=            ");
  MmiGotoxy(15,5); MmiPrintf("T=            ");
 }
          }
#endif

        /*
          if(PageD==1)
          {
  MmiGotoxy(0,3) ; MmiPrintf("Объем       :                ");
  MmiGotoxy(0,4) ; MmiPrintf("Давление    :                ");
  MmiGotoxy(0,5) ; MmiPrintf("Температура :                 ");
          }
        */
//MmiGotoxy(0,4); MmiPrintf("        |         |          ");
//MmiGotoxy(0,5); MmiPrintf("        |         |          ");
//MmiGotoxy(4,6);     MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
  }
}
//-------------------------------------
void f_prn_ID()
{
    f_clr_scr_MMI();
            //  MmiPrintf("                              ");
  MmiGotoxy(1,1);  MmiPrintf("  Система учета отпуска  ");
  MmiGotoxy(1,2);  MmiPrintf("  нефтепродуктов.АСН %d.   ",Adr_ASN);
  MmiGotoxy(0,3) ; MmiPrintf("!Не корректен ID=%ld ",n_id);
  MmiGotoxy(0,4) ; MmiPrintf(" SN %08lX %08lX",*( unsigned long int *)(ID_ADDR),*( unsigned long int *)(ID_ADDR+4) );
  MmiGotoxy(0,5) ; MmiPrintf("Обратитесь к поставщику за ID ");
  MmiGotoxy(0,6) ; MmiPrintf(" F2 - ввод ID ");
}
//-------------------------------------
void f_prn_slv1()
{

        SetDisplayPage(EmptPage);
        f_clr_scr_MMI();

        MmiGotoxy(0,0);
        if(dose_dlvr != vBIG_P)
         {
          if ( Flag_mass != 0 )
            MmiPrintf(" Отпуск  %g кг",dose_dlvr);
          else
            MmiPrintf(" Отпуск  %g л ",dose_dlvr);
         }
        else
           MmiPrintf(" Отпуск без дозы");

       MmiGotoxy(0,6);  MmiPuts("ESC - СТОП");

}
//-------------------------------------
int un_mmi1=1;
int un_mmi2=2;
int un_mmi3=3;
char *list_un_mmi[]={
"",
" Объем,л   " ,  //1
"Сумма,руб  " ,  //2
"Цена,руб/л " ,  //3
"Масса,кг   " ,  //4
"Сумма,руб  " ,  //5
"Цена,руб/кг" ,  //6
};
//-------------------------------------
int CRC_err=0;
//-------------------------------------
void f_prn_CRC_error()
{
 MmiGotoxy(0,1);   MmiPrintf(" АСН %d.",Adr_ASN);
 MmiGotoxy(0,2);   MmiPrintf("!Ошибка контрольной суммы   ");
 MmiGotoxy(0,3);   MmiPrintf("!Параметры потеряны         ");
 MmiGotoxy(0,4);   MmiPrintf("!Необходима перенастройка   ");
 MmiGotoxy(0,5);   MmiPuts(s_empty);
 CRC_err=1;
}
//-------------------------------------
void f_prn_proc()
{
 float V_tmp;
          if(PageD==0)
          {
            if ( Flag_mass != 0 )
            {
              MmiGotoxy(0,4);  MmiPuts(" Плотность     |   Расход      ");
              MmiGotoxy(0,5);MmiPrintf("%8.2f кг/м3 | %8.1f кг/ч  ",s_MVD[0].Dens,s_MVD[0].FlowM);
            }
            else
            {
    //        MmiGotoxy(0,4);  MmiPuts(" Плотность     |   Расход      ");
    //        MmiGotoxy(0,5);MmiPrintf("%8.2f кг/м3 | %8.1f л/ч  ",s_MVD[0].Dens,s_MVD[0].FlowV);

              if( flag_AD != 0)
              {
                MmiGotoxy(0,4);  MmiPuts("  Плотность    |Температура   ");
                MmiGotoxy(0,5);  MmiPrintf("%7.2f кг/м3  | %7.2f C     ",Dens_a,Temp_a);
              }
              else
              {

                if(s_MVD[0].TempR < -49.5)
                {
                MmiGotoxy(0,4);  MmiPuts("Плотн,кг/м3|ТемпMVD,C|Расх,л/ч ");
                 MmiGotoxy(0,5); MmiPrintf(" %8.2f  | %7.2f |%8.1f ",s_MVD[0].Dens,s_MVD[0].Temp,s_MVD[0].FlowV);
                }
                else
                {
                MmiGotoxy(0,4);  MmiPuts("Плотн,кг/м3|Темпер.,C|Расх,л/ч ");
                 MmiGotoxy(0,5); MmiPrintf(" %8.2f  | %7.2f |%8.1f ",s_MVD[0].Dens,s_MVD[0].TempR,s_MVD[0].FlowV);
                }
              }
            }
          }
          else if(PageD==1)
          {
              if( flag_AD == 0)
              {
                if(s_MVD[0].TempR < -49.5)
                {
                  Temp_AD=s_MVD[0].Temp;
                }
                else
                {
                  Temp_AD=s_MVD[0].TempR;
                }

                D_ref=f_get_ref_Dns( s_MVD[0].Dens, Temp_AD,T_Ref);
                if(D_ref==0) D_ref=0.001;
                V_ref=s_MVD[0].MassT*1000./ D_ref;
              }
              MmiGotoxy(0,4);  MmiPuts(" Пл15,кг/м3|Объем15,л|Давл,МПа");
              MmiGotoxy(0,5);
              if(flag_prn_mass != 0)
                V_tmp=V_ref;
              else
                V_tmp=0.;
              if(D_ref< 400)
                MmiPrintf(" --------  | ------- | %8.3f ",s_MVD[0].Press);
              else
                MmiPrintf(" %8.2f  |%8.2f | %8.3f ",D_ref,V_tmp,s_MVD[0].Press);
          }
          else if(PageD==3)
          {

     MmiGotoxy(0,4);
  if(valve_mode==1)      MmiPuts("Клап.мнш:");
  else if(valve_mode==2) MmiPuts("Пилот НЗ:");
  else if(valve_mode==3) MmiPuts("Здв.откр:");

     if( OUT_VAR & OUT2  )
       MmiPuts("1       ");
     else
       MmiPuts("0       ");

     MmiGotoxy( 0,5);
  if(valve_mode==1)      MmiPuts("Клап.блш:");
  else if(valve_mode==2) MmiPuts("Пилот НО:");
  else if(valve_mode==3) MmiPuts("~Зд.закр:");
     if( OUT_VAR & OUT1  )
       MmiPuts("1       ");
     else
       MmiPuts("0       ");



     MmiGotoxy(15,4);   MmiPuts("Добавка :");
     if( OUT_VAR & OUT5  )
       MmiPuts("1  ");
     else if( OUT_VAR & OUT6  )
       MmiPuts("2  ");
     else
       MmiPuts("0  ");

     MmiGotoxy(26,4);   MmiPuts("Н:");
     if( OUT_VAR & OUT3  )
       MmiPuts("1      ");
     else
       MmiPuts("0      ");

     MmiGotoxy(15,5);   MmiPuts("Кл.доб. :");
     if( OUT_VAR & OUT7  )
       MmiPuts("1      ");
     else
       MmiPuts("0      ");
          }
}
//-------------------------------------
void f_prn_MassSt_dlv()
{
  MmiGotoxy(0,1);
         MmiPrintf("Всего %7.1f кг, %7.1f л  ",s_MVD[0].MassI-MassStamp,s_MVD[0].VolI-VolStamp);
/*
  if ( Flag_mass != 0 )
    MmiPrintf("  Всего отпущено %8.2f кг  ",s_MVD[0].MassI-MassStamp);
  else
    MmiPrintf("  Всего отпущено %8.2f л   ",s_MVD[0].VolI-VolStamp);
 */
}
//-------------------------------------
void f_prn_MassSt_rcv()
{
  MmiGotoxy(0,1);
  if ( Flag_mass != 0 )
    MmiPrintf("   Всего принято %8.2f кг  ",s_MVD[0].MassI-MassStamp);
  else
    MmiPrintf("   Всего принято %8.2f л   ",s_MVD[0].VolI-VolStamp);
}
//-------------------------------------
void f_prn_error()
{
   f_clr_scr_MMI();

//#if( Test == 0)
   if(flag_mvd_ton)
   {
  MmiGotoxy(1,1);  MmiPrintf("  Система учета отпуска  ");
  MmiGotoxy(1,2);  MmiPrintf("  нефтепродуктов.АСН %d.   ",Adr_ASN);

  MmiGotoxy(0,3);  MmiPuts(s_empty);
  MmiGotoxy(0,4);  MmiPrintf("  !Инициализация расходомера ");
  MmiGotoxy(0,5);  MmiPuts(s_empty);
   }
   else
//#endif
   {

    MmiGotoxy(0,1);   MmiPrintf(" АСН %d.",Adr_ASN);
    MmiGotoxy(0,2);   MmiPrintf("!Ошибка функционирования ");
    MmiGotoxy(0,3);   MmiPrintf("Sht-F1 отображение ошибок");
    MmiGotoxy(0,4);   MmiPrintf("Sht-ESC очистка ошибок   ");
   }
}
//-------------------------------------
void  f_disp_error()
{ // распечатывает ошибки

 struct s_icp_dev *ICPl_DEV;
int i,i1,i2;
int itmp;
   i1=0;
   i2=0;
 for(i=0;i<=icp_lst_max;i++)
   if(ICP_error[i])
   {
    i2++;
    ICPl_DEV=ICP_dd[i];
  if(i != icp_lst_max)
  {
 MmiGotoxy(0,i1++);   MmiPrintf("Ошибка в драйвере %9s:",ICPl_DEV->name );
  }
  else
  {
 MmiGotoxy(0,i1++);   MmiPrintf("Ошибка системы учета:           ");
  }
    if(i1 >= n_mmi_str) return;
    itmp=ICP_error[i];
  if(i != icp_lst_max)
  {
    if(itmp & RD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка чтения устройства");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WR_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка записи в устройство");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка Watch Dog");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Drive_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка в устройстве,%02X", (itmp>>8) & 0xff);
    if(i1 >= n_mmi_str) return;
    }

  }
  else //(i == icp_lst_max)
  {
    if(itmp == EEE_CRC_error)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка CRC EEPROM процессора");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_erase_error )
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка стирания FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_wr_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка записи во FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_gas_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("Расходомер не заполнен");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_Z_mass_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("Расх-р не обнулил массу");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_F_dat_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("Нет обновл.данных для журнала");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & DNS_not_off)
    {
MmiGotoxy(0,i1++); MmiPrintf("Утечка при старте ");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_Press)
    {
MmiGotoxy(0,i1++); MmiPrintf("Низкое давление при старте ");
    if(i1 >= n_mmi_str) return;
    }
//  if(itmp & exm_err )
//  {
//MmiGotoxy(0,i1++); MmiPrintf("Недолив больше допустимого");
//    if(i1 >= n_mmi_str) return;
//  }
//    if(itmp & exp_err )
//    {
//MmiGotoxy(0,i1++); MmiPrintf("Перелив больше допустимого");
//    if(i1 >= n_mmi_str) return;
//    }
    if(itmp & Gun_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("Насос отключен при отпуске");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == WD_host)
    {
MmiGotoxy(0,i1++); MmiPrintf("Нет связи с HOST");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == No_flow )
    {
MmiGotoxy(0,i1++); MmiPrintf("Поток прекратился");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & ES_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("Кнопка ES при отпуске");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & UZA_off )
    {
     switch (flagE_UZA)
     {
      case UZA_E:
MmiGotoxy(0,i1++); MmiPrintf("Нет УЗА при отпуске");
        if(i1 >= n_mmi_str) return;
        break;
      case LVL_E:
MmiGotoxy(0,i1++); MmiPrintf("Низкий уровень при отпуске");
        if(i1 >= n_mmi_str) return;
        break;
      case ID_E:
MmiGotoxy(0,i1++); MmiPrintf("Некорректный ID ");
        if(i1 >= n_mmi_str) return;
        break;
      case TRAP_E:
MmiGotoxy(0,i1++); MmiPrintf("Трап не в раб.позиции ");
        if(i1 >= n_mmi_str) return;
        break;
      case CONS_E:
MmiGotoxy(0,i1++); MmiPrintf("Консоль не в раб.позиции ");
        if(i1 >= n_mmi_str) return;
        break;
     }
    }
    if(itmp & MVD_cfg )
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка конф.расход-ра ");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == MotNotStop )
    {
MmiGotoxy(0,i1++); MmiPrintf("Сбой насоса при торм.");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == DLT_off)
    {
MmiGotoxy(0,i1++); MmiPrintf("Насос выкл. при отпуске");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & MVD_com)== MVD_com )
    {
MmiGotoxy(0,i1++); MmiPrintf("Нет связи с расхдм.");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & Hst_alm)==Hst_alm)
    {
MmiGotoxy(0,i1++); MmiPrintf("Авария от Host");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & No_Drv)==No_Drv)
    {
MmiGotoxy(0,i1++); MmiPrintf("Драйверы MVD,7060 не включены");
    if(i1 >= n_mmi_str) return;
    }
  }
   }
   if(i2==0)
   {
    MmiGotoxy(5,2); MmiPrintf("Ошибок нет");
    MmiGotoxy(2,4); MmiPrintf("Enter - продолжить");
   }
}
//-------------------------------------
void f_drv_list_MMI(int *nn)
{ // показать список драйверов устройств
int i,i1,i2;
char str[31];
  struct s_icp_dev *ICPl_DEV;

   f_clr_scr_MMI();

  //  if( (*nn+n_mmi_str_3) > icp_lst_max) i=icp_lst_max-n_mmi_str_3;
  //  else
    i=*nn;
    if(i<0) i=0;
    if((i+n_mmi_str_3) < icp_lst_max) i1=i+n_mmi_str_3;
    else i1=icp_lst_max;

    *nn=i;
    MmiGotoxy(0,0); MmiPuts("        Список драйверов      ");
    MmiGotoxy(0,1); MmiPuts(" N     Имя   Сост. Порт Адр.");
   for(i2=0;i<i1;i++,i2++)
    {
      ICPl_DEV=ICP_dd[i];
      if(ICPl_DEV==NULL) break;
      MmiGotoxy(0,3+i2);
//         MmiPuts(" N      Имя   Сост. Порт Адр.");
//                 "xx.....xxxxx  .x    .x   xx"
      MmiPrintf("%2d%10s  %2d    %2d   %02X",i+1,ICPl_DEV->name,ICPl_DEV->status,ICPl_DEV->port,ICPl_DEV->addr);
    }
}
//-------------------------------
void f_drv_stat_MMI(int *nn)
{ // показать статистику драйверов устройств
int i,i1,i2;
char str[31];
  struct s_icp_dev *ICPl_DEV;

   f_clr_scr_MMI();

//  if( (*nn+n_mmi_str_3) > icp_lst_max) i=icp_lst_max-n_mmi_str_3;
//  else
    i=*nn;
    if(i<0) i=0;
    if((i+n_mmi_str_3) < icp_lst_max) i1=i+n_mmi_str_3;
    else i1=icp_lst_max;

    *nn=i;
    MmiGotoxy(0,0);  MmiPuts(" Статистика работы драйверов");
    MmiGotoxy(0,1);  MmiPuts(" N     Имя    Послано  Ошибок");
    for(i2=0;i<i1;i++,i2++)
    {
      ICPl_DEV=ICP_dd[i];
      if(ICPl_DEV==NULL) break;
      MmiGotoxy(0,3+i2);
//         MmiPuts(" N     Имя    Послано  Ошибок");
//                 "xx.....xxxxx  xxxxxxx xxxxxxx"
         MmiPrintf("%2d%10s  %7ld %7ld",i+1,ICPl_DEV->name,ICPl_DEV->n_transaction,ICPl_DEV->n_timeout_error+ICPl_DEV->n_CRC_error);
    }
}
//-------------------------------
//-------------------------------
void f_mod_list_MMI(int *nn)
{ // показать список обнаруженных модулей
int i,i1,i2;
 char str[31];

  struct icp_mod *ICPl_MOD;

  i1=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
  f_clr_scr_MMI();
  if(i1==0)
  {
    MmiGotoxy(3,2);   MmiPuts("    Список пуст." );
    MmiGotoxy(3,3);   MmiPuts("Используйте поиск для" );
    MmiGotoxy(3,4);   MmiPuts("  обновления списка." );
  }
  else
  {
    MmiGotoxy(0,0);    MmiPuts(" Список обнаруженных модулей  ");
    MmiGotoxy(0,1);    MmiPuts(" N    Имя Порт.Адр.Скор. TT FF");

      i=*nn;
    if(i<0) i=0;
    if((i+n_mmi_str_3) < i1) i1=i+n_mmi_str_3;
    *nn=i;

    for(i2=0;i<i1;i++,i2++)
    {
      ICPl_MOD=f_get_mod_str(i);
      if(ICPl_MOD==NULL) break;
      MmiGotoxy(0,3+i2);

//         MmiPuts(" N    Имя Порт.Адр.Скор. TT FF");
//                 "xx.....xxxx  x xx xxxxxx xx xx"
      MmiPrintf("%2d%9s  %1d %02X %6ld %02X %02X",i+1,ICPl_MOD->name,ICPl_MOD->port,ICPl_MOD->addr,baudrate_val[ICPl_MOD->CC],ICPl_MOD->TT,ICPl_MOD->FF);
    }
  }
}
//-------------------------------
int mode_prn=1;
void f_prn_current()
{ // показать состояние отпуска на текущий момент
  int year,month,day,hour,min,sec;
 MmiGotoxy(0,0);   MmiPrintf("Tекущее значение счетчика");
 MmiGotoxy(0,3);   MmiPrintf("  Дата     Время     Масса,кг");
//MmiGotoxy(0,3);  MmiPrintf("21.02.09 12:10:11  _123456.90");

 GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
 MoveToXY(0,5); MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
 MmiGotoxy(18,5);  MmiPrintf("%11.3f",s_MVD[0].MassI);
                                   // s_MVD[0].VolI
}
//-------------------------------
void f_prn_den_t()
{
float ftmp,ftmp1;
 //  Отображение Массы,плотности,температуры,давления
 //  Текущее значение.
 MmiGotoxy(0,0);   MmiPrintf("Текущие показания расходомера");
 MmiGotoxy(0,1);   MmiPrintf(" Масса      %10.3f кг",s_MVD[0].MassT);
 MmiGotoxy(0,2);   MmiPrintf(" Объем      %10.3f л ",s_MVD[0].VolT);
// MmiGotoxy(0,1);   MmiPrintf(" Масса      %10.3f кг",s_MVD[0].MassI);
// MmiGotoxy(0,2);   MmiPrintf(" Объем      %10.3f л ",s_MVD[0].VolI);
// MmiGotoxy(0,2);   MmiPrintf(" Объем      %10.3f кг",s_MVD[0].MassT);
 MmiGotoxy(0,3);   MmiPrintf(" Расход    %10.2f кг/ч",s_MVD[0].FlowM);
 MmiGotoxy(0,4);   MmiPrintf(" Плотность %10.2f кг/м3",s_MVD[0].Dens);
// MmiGotoxy(0,2);   MmiPrintf(" Давление     %6.3f МПа  ",s_MVD[0].Press);
// MmiGotoxy(0,3);   MmiPrintf(" Температура  %6.2f град.C",s_MVD[0].TempR);
 MmiGotoxy(0,5);   MmiPrintf(" Темп.расхдм.  %6.2f град.C",s_MVD[0].Temp);
 MmiGotoxy(0,6);   MmiPuts(" ESC-меню,F2-оч.м.тек.");
}
//-------------------------------
void f_prn_lst_hour()
{ // показать состояние отпуска на последний расч. час

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // текущее время

 tim_000.hour=ahour00.hour;
 tim_000.min=ahour00.min;
 tim_000.sec=ahour00.sec;

 ltime0=f_get_time_t(&tim_000);

 if(ltime0 >ltime1) ltime0-=n_sec_day;
 if( f_get_d_dat(ltime0, s_mode) < 0)
 {
  if(ltime0<ltime1)
  {

  if( (ar_str_ptr=f_get_lst_stor()) == NULL) goto m_bad;
  ltime2= f_get_time(ar_str_ptr);

  if(ltime0>ltime2)
   {
    tMassI= s_MVD[0].MassI;
    tVolI = s_MVD[0].VolI;
    f_wr_evt(evt_none);
    goto m_ok;
   }
   else goto m_bad;
  }
  ltime0-=n_sec_day;
  if( f_get_d_dat(ltime0, s_mode) < 0)
  {
  m_bad:
   MmiGotoxy(5,3);   MmiPrintf("Данные отсутствуют");
  }
  else
  {
  m_ok:
 MmiGotoxy(0,0);   MmiPrintf("   Значение счетчика учета ");
 MmiGotoxy(0,1);   MmiPrintf(" на последний расчетный час ");

 MmiGotoxy(0,3);   MmiPrintf("  Дата     Время     Масса,кг");
//MmiGotoxy(0,3);  MmiPrintf("21.02.09 12:10:11  _123456.90");

 MoveToXY(0,5);
    tdat = localtime( &ltime0 );
    MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
MmiGotoxy(18,5);
    if(tMassI != vBIG_P)
       MmiPrintf("%11.3f" ,tMassI);
//  else
//     MmiPrintf(" ------- ");
  }
 }
 else goto m_ok;

 return;
}
//-------------------------------
void f_prn_date()
{ // показать состояние отпуска на указанную дату

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;
 // определение времени последней записи в журнал

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // текущее время

 tim_000=adate00;
 tim_000.hour=ahour00.hour;
 tim_000.min=ahour00.min;
 tim_000.sec=ahour00.sec;

 ltime0=f_get_time_t(&tim_000);

 MmiGotoxy(0,0);   MmiPrintf("   Значение счетчика учета");
 MmiGotoxy(0,1);   MmiPrintf("     на указанную дату  ");

 MmiGotoxy(0,3);   MmiPrintf("  Дата     Время     Масса,кг");
//MmiGotoxy(0,3);  MmiPrintf("21.02.09 12:10:11  _123456.90");

 MoveToXY(0,5);
    tdat = localtime( &ltime0 );
    MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
MmiGotoxy(18,5);

 if( f_get_d_dat(ltime0, s_mode) < 0)
 {

  if( (ar_str_ptr=f_get_lst_stor()) == NULL) goto m_bad;

  ltime2= f_get_time(ar_str_ptr);

  if((ltime0<ltime1)&&(ltime0>ltime2) )
  {
   f_wr_evt(evt_none);
   if( f_get_d_dat(ltime0, s_mode) >= 0)
         goto m_ok;
   else goto m_bad;
  }
  else
  {
  m_bad:
      MmiPrintf("Нет данных");
  }
 }
 else
 {
  m_ok:
    if(tMassI != vBIG_P)
       MmiPrintf("%11.3f",tMassI);
    else
       MmiPrintf(" ------- ");
 }
 return;
}
//-------------------------------
void f_prn_5day()
{ // показать состояние отпуска за последние 5 суток

 struct tm *tdat;

int year,month,day,hour,min,sec,i;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // текущее время

 tim_000.hour=ahour00.hour;
 tim_000.min=ahour00.min;
 tim_000.sec=ahour00.sec;

 ltime0=f_get_time_t(&tim_000);
/*
     tdat = localtime( &ltime0 );
     printf("\n\r%02d.%02d.%02d %02d:%02d:%02d",
        tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
*/

 if( f_get_d_dat(ltime0, s_mode) < 0)
 {
  if(ltime0<ltime1)
  {
   if( (ar_str_ptr=f_get_lst_stor()) == NULL)
   {
//  goto m_bad;
    goto m_ok;
   }
   ltime2= f_get_time(ar_str_ptr); // последняя запись

   if(ltime0>ltime2)
   {
    tMassI= s_MVD[0].MassI;
    tVolI = s_MVD[0].VolI;
    f_wr_evt(evt_none);
    goto m_ok;
   }
   else
   {
//  goto m_bad;
    goto m_ok;
   }
  }
 else
   ltime0-=n_sec_day;
  {
  m_ok:

  ltime1=ltime0 - n_sec_day * 4;

 MmiGotoxy(0,0);   MmiPrintf("  Дата     Время     Масса,кг");
//MmiGotoxy(0,3);  MmiPrintf("21.02.09 12:10:11  _123456.90");


    for(i=1;i<6;i++,ltime1+=n_sec_day)
    {


     MoveToXY(0,i);
        tdat = localtime( &ltime1 );
        MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d",
        tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
    MmiGotoxy(18,i);

     if( f_get_d_dat(ltime1, s_mode) < 0)
     {
           MmiPrintf("Нет данных");
     }
     else
     // if(tMassI>= 0.)
           MmiPrintf("%11.3f" ,tMassI);
     // else
     //    MmiPrintf(" ------- ");
    }
    MmiGotoxy(0,6);   MmiPuts("ESC,Enter - продолжить");

  }
 }
 else goto m_ok;
 return;

 m_bad:
   MmiGotoxy(5,3);   MmiPrintf("Данные отсутствуют");
 return;
}
//-------------------------------
char *rcv_mm[]={
"отпуск",
"прием",
};
char *Rcv_mm[]={
"Отпуск",
"Прием",
};
// rcv_mm[f_rcv]
int  f_prn_mmi_a(struct arch_str *a_str,int i_n)
{
 int ii,itmp,i_ret;
 float ftmp,ftmp1;
 struct tm *tdat;
 int f_rcv;

 if(a_str->event & (int)RCV_FLG)
       f_rcv=1;
 else
       f_rcv=0;

 MoveToXY(0,i_n);
   i_ret=i_n;
   if(i_ret>=n_mmi_str) return i_ret;

//  MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d" ,a_str->day,a_str->month,a_str->year,a_str->hour,a_str->min,a_str->sec);

  tdat = localtime( &a_str->time );
  MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d",
  tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);

  if((a_str->MassI != vBIG_P)&& (a_str->MassI != M_one) )
     MmiPrintf("%10.3f кг",a_str->MassI);
  else
     MmiPrintf(" ------- " );
// i_ret=i_n+1;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;

 MoveToXY(0,i_ret);

  if((a_str->VolI != vBIG_P)&& (a_str->VolI != M_one) )
  {
     MmiPrintf("V=%10.3f л",a_str->VolI);
     i_ret++;
     if(i_ret>=n_mmi_str) return i_ret;
     MoveToXY(0,i_ret);
  }
  /*
  else
     MmiPrintf(" ------- " );
  */
// switch( (int) a_str->event)
 switch( (int)( a_str->event & ~(int)RCV_FLG) )
 {
  case evt_beg_eq:
    MmiPrintf("Старт %sа.",rcv_mm[f_rcv]);
    goto m_val0;
  case evt_start_f:
    MmiPrintf("Старт %sа.",rcv_mm[f_rcv]);

m_val0:
//   i_ret=i_n+2;
// if(i_ret>=n_mmi_str) return i_ret;
// MoveToXY(0,i_ret);
  if(a_str->u.fill.VolT != vBIG_P)
  {
      if ( Flag_mass != 0 )
        MmiPrintf("Доза %8.3fкг ",a_str->u.fill.VolT    );
      else
        MmiPrintf("Доза %8.3f л",a_str->u.fill.VolT    );
  }
  else
      MmiPrintf("Без дозы    ",a_str->u.fill.VolT    );

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

   MmiPrintf("Плотн.%6.3fкг/м3;" ,a_str->u.fill.Density);
   MmiPrintf("Т=%6.2fC;" ,a_str->u.fill.Temp);

   i_ret++;
// i_ret=i_n+3;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%6.3f МПа;" ,a_str->u.fill.UnitPrice);
//  MmiPrintf("Т=%6.2fC;" ,a_str->u.fill.Amount);

    break;

  case evt_cont_f:
    MmiPrintf(" Продолжение %sа,",rcv_mm[f_rcv]);
    goto m_val;
  case evt_exm_f:
    MmiPrintf(" Завершено,недолив ");

m_val:

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    if(a_str->u.fill.VolT != vBIG_P)
         MmiPrintf(" Отп.%9.3f кг,%9.3f л",a_str->u.fill.VolT,a_str->u.fill.Amount );

// i_ret=i_n+3;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("Плотн.%6.3f кг/м3;" ,a_str->u.fill.Density);
    MmiPrintf("Т=%6.2fC;" ,a_str->u.fill.Temp);

// i_ret=i_n+4;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%6.3f МПа ;" ,a_str->u.fill.UnitPrice);
//    MmiPrintf("Т=%6.2fC;" ,a_str->u.fill.Amount);

    break;

  case evt_exp_f:
    MmiPrintf(" Завершено,перелив");
    goto m_val;

  case evt_end_gas:
    MmiPrintf(" %s прерв.нет ждк.фазы",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_end_f:
    MmiPrintf(" Завершено ОК  ");
    goto m_val;

  case evt_est_f:
    MmiPrintf(" %s прерван командой",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_est_fh:
    MmiPrintf(" %s прерван Host ",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_err_f:
    MmiPrintf(" %s прерван ошибкой",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_eq_pr :
    MmiPrintf("Старт выр.давл. паровых фаз");
    goto m_val;
  case evt_stop_eq :
  printf("Заверш.выр.давл. паровых фаз");
    goto m_val;

  case evt_ep1_f:
    MmiPrintf(" %s прерван,Host",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_overfl:
    MmiPrintf(" %s прерван ост.потока",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_ES_off:
    MmiPrintf(" %s прерв.Авар.кнопкой ES",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_UZA_off:
    MmiPrintf(" %s прерв.Нет сигнала УЗА",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_LVL_off:
    MmiPrintf(" %s  прерван: Уровень.",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_TRAP_off:
    MmiPrintf(" %s  прерван: Трап.",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_CONS_off:
    MmiPrintf(" %s  прерван: Консоль.",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_DLT_off:
    MmiPrintf(" %s прерв.Насос не включен",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_wd_pmp:
    MmiPrintf(" %s прерв.WD PMLAN",Rcv_mm[f_rcv]);
    goto m_val;


  case evt_no_dev:
    MmiPrintf(" Старт не принят.Не вкл.драйв");
    goto m_val;

  case evt_clr_err:
    MmiPrintf(" Сброс ошибок. ");
    break;

  case evt_MVD_CL_strt:
    MmiPrintf(" Старт калибровки расходомера");
    break;

  case evt_MVD_CL_BS1 :
    MmiPrintf(" !Попытка клб.расх.при отп.");
    break;

  case evt_MVD_CL_BS2 :
    MmiPrintf(" !Сбой при старте клб.расх.");
    break;

  case evt_MVD_CL_OK :
    MmiPrintf(" Калибровка расходомера OK");
    break;

  case evt_MVD_CL_TM :
    MmiPrintf(" Таймаут калибровки расходом.");
          //  |                              |

    break;

  case evt_ch_date:
    MmiPrintf(" Дата изменена.");
    break;

  case evt_ch_time:
    MmiPrintf(" Время изменено.");
    break;
  case evt_ch_sum:
    MmiPrintf(" Переход на летнее время.");
    break;
  case evt_ch_win:
    MmiPrintf(" Переход на зимнее время.");
    break;
  case evt_res:
    MmiPrintf(" Команда Сброс");
    break;
  case evt_Slot:
    MmiPrintf(" MVD:Конфигурир-е устройства");
    break;
  case evt_chg_param:
    if(a_str->u.fill.VolT == Par_VF)
    {
     MmiPrintf(" !Изм.множ.объема");
    }
    else if(a_str->u.fill.VolT == Par_MF)
    {
     MmiPrintf(" !Изм.множ.массы");
    }
    else if(a_str->u.fill.VolT == Par_MC)
    {
     MmiPrintf(" !Изм.срез.м.расх.");
    }
    else if(a_str->u.fill.VolT == Par_PASS)
    {
     MmiPrintf(" !Изменен пароль");
    }
    else if(a_str->u.fill.VolT == Par_ID)
    {
     MmiPrintf(" !Изменен ID");
    i_ret++;
    if(i_ret>=n_mmi_str) return i_ret;
    MoveToXY(0,i_ret);

    MmiPrintf("Было :%ld; ",(long int)a_str->u.fill.Amount  );
    MmiPrintf("Стало:%ld" ,(long int)a_str->u.fill.UnitPrice);
    break;
    }
    else
     {
//    MmiPrintf(" !Изм. парам. ");
      MmiPrintf(" !Изменен параметр ");
      MmiPrintf("N%g ",a_str->u.fill.VolT );
     }

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    MmiPrintf("Было:%g; ",a_str->u.fill.Amount  );
    MmiPrintf("Стало:%g" ,a_str->u.fill.UnitPrice);
    break;
  case evt_exit:
    MmiPrintf(" Команда Выход в ДОС");
    break;
  case evt_re:
    MmiPrintf(" Чтение конф.из EEPROM");
    break;
  case evt_re_err:
    MmiPrintf(" Ошибка чтения конф.из EEPROM");
    break;
  case evt_we:
    MmiPrintf(" Запись конф. в EEPROM");
    break;
  case evt_we_err:
    MmiPrintf(" Ош.записи конф. в EEPROM");
    break;

  case evt_wrong_start:
    MmiPrintf(" Cтарт не принят.Ошибка.");
    goto m_val;

  case evt_err:
  case evt_none:
 mm_0:
    itmp=0;
    for(ii=0;ii<=icp_lst_max ;ii++)
      itmp |= a_str->u.err.err[ii];
  if(itmp)
  {
    MmiPrintf(" Ошибка:");
 mm_e:

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

 MmiPrintf(" %01X" ,a_str->u.err.err[0] );
 MmiPrintf(" %04X" ,a_str->u.err.err[1] );
 MmiPrintf(" %01X" ,a_str->u.err.err[2] );
 MmiPrintf(" %01X" ,a_str->u.err.err[3] );
 MmiPrintf(" %01X" ,a_str->u.err.err[4] );
 MmiPrintf(" %01X" ,a_str->u.err.err[5] );
 MmiPrintf(" %04X" ,a_str->u.err.err[6] );
 MmiPrintf(" %04X:" ,a_str->u.err.err[7] );
 MmiPrintf("%04X" ,a_str->u.err.err[8] );
  }
  else
 MmiPrintf(" Ошибок нет ");

  break;

  case evt_t_on:
 MmiPrintf(" Включение устройства");
    break;
  case evt_t_off:
 MmiPrintf(" Выключение устройства");
    break;
  default:
 MmiPrintf(" Событие не известно");
   break;
 }
 return i_ret;
}

//----------------------------------
void f_MVD_M1()
{
// отображает параметры MVD  на MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !Таймаут чтения MVD");
     ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 20:
   MVD_fn[0]=MVD_RD_L;
   s_MVD[0].r_addr=127;
   sw_mvd_m1=1;
   break;

  case 1:
  if(MVD_fn[0] != F_FAULT)
   {MoveToXY(0,sw_MMI_cur++);MmiPrintf("SN   %ld",s_MVD[0].l);}
  if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 21:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].r_addr=425;
   s_MVD[0].n=8;
   sw_mvd_m1=2;
   break;

  case 2:
  if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,sw_MMI_cur++); MmiPrintf("S  : %s",s_MVD[0].a);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 22:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].n=8;
   s_MVD[0].r_addr=96;
   sw_mvd_m1=3;
   break;

  case 3:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("TXM:%s",s_MVD[0].a);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 23:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].r_addr=104;
   s_MVD[0].n=16;
   sw_mvd_m1=4;
   break;

  case 4:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("M:%s",s_MVD[0].a); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 24:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr=16;
   sw_mvd_m1=5;
   break;

  case 5:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("TXM версия: %d",s_MVD[0].i);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 25:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].r_addr=72;
   s_MVD[0].n=5;
   sw_mvd_m1=6;
   break;

  case 6:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Flow : --%s--",s_MVD[0].a);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 26:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].r_addr=80;
   s_MVD[0].n=7;
   sw_mvd_m1=7;
   break;

  case 7:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Тemp.: --%s--",s_MVD[0].a);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 27:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=155;
   sw_mvd_m1=8;
   break;

  case 8:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("D1:                  %.3f",s_MVD[0].f); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 28:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=157;
   sw_mvd_m1=9;
   break;

  case 9:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("D2:                  %.3f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=159;
   sw_mvd_m1=10;
   break;

  case 10:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("K1:                  %.3f",s_MVD[0].f); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 30:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=161;
   sw_mvd_m1=11;
   break;

  case 11:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("K2:                  %.3f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 31:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=279;
   sw_mvd_m1=12;
   break;

  case 12:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Множитель массы:     %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=281;
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Множитель объема:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 33:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=283;
   sw_mvd_m1=14;
   break;

  case 14:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Множитель плотности: %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 34:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=195;
   sw_mvd_m1=15;
   break;

  case 15:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Срез масс.расхода:   %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 35:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=197;
   sw_mvd_m1=16;
   break;

  case 16:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Срез об. расхода:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 36:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=149;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,sw_MMI_cur++); MmiPrintf("Срез плотности :     %.6f",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  }

}
/* ---------------------------------------- */
void f_MVD_M1f()
{
// отображает параметры коррекции расхода  MVD  на MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
     MoveToXY(0,4); MmiPrintf(" !Таймаут чтения MVD");
     ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 31:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=279;
   sw_mvd_m1=12;
   break;

  case 12:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,4);MmiPrintf("Множитель массы:    %.6f",s_MVD[0].f);}
     k_m_flow=s_MVD[0].f;

  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=281; // Множитель объема
//   s_MVD[0].r_addr=195;  // Cuttoff for mass flow
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,5);MmiPrintf("Множитель объема:   %.6f",s_MVD[0].f);}
// { MoveToXY(0,5); MmiPrintf("Срез м.расх.: %10.2f кг/ч",s_MVD[0].f);}
   k_v_flow=s_MVD[0].f;
   ff_serv=NULL;
   Flag_f_corr=1;
   break;
 }
}
/* ---------------------------------------- */
void f_MVD_M1s()
{
// отображает параметры коррекции расхода  MVD  на MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
     MoveToXY(0,4); MmiPrintf(" !Таймаут чтения MVD");
     ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 31:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=195;
   sw_mvd_m1=12;
   break;

  case 12:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,4); MmiPrintf("Срез м. расх.: %8.2f кг/ч",s_MVD[0].f);}
     k_m_flow=s_MVD[0].f;

  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=197;  // Cuttoff for mass flow
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,5); MmiPrintf("Срез об.расх.: %8.3f л/сек",s_MVD[0].f);}
   k_v_flow=s_MVD[0].f;
   ff_serv=NULL;
   Flag_f_corr=1;
   break;
 }
}
/* ---------------------------------------- */
/* ---------------------------------------- */
char *unit1=NULL;//I39
char *unit2=NULL;//I45
char *unit3=NULL;//42 // Volume flow codes
char *unit4=NULL;// Volume totalizer or volume inventory codes I 0046
char *unit5=NULL;// Density codes I0040
char *unit6=NULL;// Temperature codes I0041
float MMITemp,MMIDens,MMICompos;
void f_MVD_M2()
{
char *unit;
int u_cod;
// отображает данные MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !Таймаут чтения MVD");
        ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 20:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr=39; // I039 Mass flow codes
   s_MVD[0].i=-1;
   sw_mvd_m1=1;
   break;

  case 1:
   u_cod=s_MVD[0].i;
    if(u_cod>0)  unit1=f_get_unit(u_cod);
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=247;
   sw_mvd_m1++;
   break;

  case 2:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit1 != NULL)
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Расход м. : %f %s",s_MVD[0].f,unit1);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }

  case 21:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr=45; // Mass totalizer or mass inventory unit codes I 0045
   s_MVD[0].i=-1;
   sw_mvd_m1=3;
   break;

  case 3:
   u_cod=s_MVD[0].i;
    if(u_cod>0)  unit2=f_get_unit(u_cod);
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=259;
   sw_mvd_m1++;
   break;

  case 4:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit2 != NULL)
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Масса общ.: %10.3f %s",s_MVD[0].f,unit2);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 22:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=263;
   sw_mvd_m1=5;
   break;

  case 5:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit2 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Масса инв.: %10.2f %s",s_MVD[0].f,unit2); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 23:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr= 42 ; // Volume flow codes I0042
   s_MVD[0].i=-1;
   sw_mvd_m1=6;
   break;

  case 6:
   u_cod=s_MVD[0].i;
   if(u_cod>0)  unit3=f_get_unit(u_cod);

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=253;
   sw_mvd_m1++;
   break;

  case 7:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit3 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Расход об.: %f %s",s_MVD[0].f,unit3);}
     if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 24:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr= 46 ; // Volume totalizer or volume inventory codes I 0046
   s_MVD[0].i=-1;
   sw_mvd_m1=8;
   break;

  case 8:
   u_cod=s_MVD[0].i;
   if(u_cod>0)  unit4=f_get_unit(u_cod);
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=261;
   sw_mvd_m1++;
   break;

  case 9:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit4 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Объем общ.: %10.3f %s",s_MVD[0].f,unit4);}
     if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 25:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=265;
   sw_mvd_m1=10;
   break;

  case 10:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit4 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Объем инв.: %10.2f %s",s_MVD[0].f,unit4);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 26:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr= 40 ; // Density codes I0040
   s_MVD[0].i=-1;
   sw_mvd_m1=11;
   break;

  case 11:
   u_cod=s_MVD[0].i;
   if(u_cod>0)
   {
     unit5=f_get_unit(u_cod);
//     printf("\n\r density unit :%s",unit5);
   }
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=249;
   sw_mvd_m1++;
   break;

  case 12:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit5 != NULL)
    {
      MoveToXY(0,sw_MMI_cur++);MmiPrintf("Плотность  :%.5f %s",s_MVD[0].f,unit5);
      MMIDens=s_MVD[0].f;
    }
   else sw_MMI_cur++;
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  else sw_MMI_cur++;
  case 27:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr= 41 ; // Temperature codes I0041
   s_MVD[0].i=-1;
   sw_mvd_m1=13;
   break;

  case 13:
   u_cod=s_MVD[0].i;
   if(u_cod>0)  unit6=f_get_unit(u_cod);
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=251;
   sw_mvd_m1++;
   break;

  case 14:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit6 != NULL)
   {
    MoveToXY(0,sw_MMI_cur++);MmiPrintf("Темп.потока: %.3f %s",s_MVD[0].f,unit6);
    MMITemp=s_MVD[0].f;
   }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 28:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=383;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Темп.платы : %.3f C",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=385;
   sw_mvd_m1=18;
   break;

  case 18:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Напр.пит.  : %.3f V",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  default:
     ff_serv=NULL;
  }

}
/* ---------------------------------------- */
void f_MVD_MM2()
{
char *unit;
// отображает данные MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !Таймаут чтения MVD");
        ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 20:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=247;
   sw_mvd_m1=2;
   break;

  case 2:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit1 != NULL)
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Расход м. : %f %s",s_MVD[0].f,unit1);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }

  case 21:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=259;
   sw_mvd_m1=4;
   break;

  case 4:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit2 != NULL)
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Масса общ.: %10.3f %s",s_MVD[0].f,unit2);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 22:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=263;
   sw_mvd_m1=5;
   break;

  case 5:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit2 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Масса инв.: %10.2f %s",s_MVD[0].f,unit2); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 23:

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=253;
   sw_mvd_m1=7;
   break;

  case 7:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit3 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Расход об.: %f %s",s_MVD[0].f,unit3);}
     if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 24:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=261;
   sw_mvd_m1=9;
   break;

  case 9:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit4 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Объем общ.: %10.3f %s",s_MVD[0].f,unit4);}
     if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 25:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=265;
   sw_mvd_m1=10;
   break;

  case 10:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit4 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Объем инв.: %10.2f %s",s_MVD[0].f,unit4);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 26:

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=249;
   sw_mvd_m1=12;
   break;

  case 12:
  if((MVD_fn[0] != F_FAULT)&&(unit5 != NULL))
  {
     MoveToXY(0,sw_MMI_cur++); MmiPrintf("Плотность  :%.5f %s",s_MVD[0].f,unit5);
     MMIDens=s_MVD[0].f;
  }
  else
  {
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("Ошибка чтения");
  }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 27:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=251;
   sw_mvd_m1=14;
   break;

  case 14:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit6 != NULL)
    {
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("Темп.потока: %.3f %s",s_MVD[0].f,unit6);
     MMITemp=s_MVD[0].f;
    }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 28:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=383;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Темп.платы : %.3f C",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=385;
   sw_mvd_m1=18;
   break;

  case 18:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Напр.пит.  : %.3f V",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  default:
     ff_serv=NULL;
  }

}
/* ---------------------------------------- */
void f_MVD_M3()
{
int i,i2;
unsigned long int ltmp,i1;
// отображает ошибки MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !Таймаут чтения MVD");
        ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 0:

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=245;
   sw_mvd_m1++;
   break;

  case 1:
   if(MVD_fn[0] != F_FAULT)
   {
     ltmp=(unsigned long int)s_MVD[0].f &0xffffff;
     fl_zeroing=ltmp;
     if(ltmp==0)
     {
   MoveToXY(0,3); MmiPrintf("         Ошибок нет.          ");
        ff_serv=NULL;
        return;
     }
     else
     {
       i2=0;
       for(i=0,i1=1;i<24;i++,i1=i1<<1)
       {
         if(ltmp & i1)
         {
          i2++;
         }
       }


     if(sw_mmi!=18)
     {
      MoveToXY(0,0);

      if(i2==1)
          MmiPrintf("   Ошибка расходомера:");
      else if( i>1)
          MmiPrintf("   Ошибки расходомера:");
       i2=1;
     }
     else
     {

      MoveToXY(0,0);
         MmiPrintf("Состояние/ошибки расходомера:");
       i2=2;
     }

       for(i=0,i1=1;i<24;i++,i1=i1<<1)
       {
         if(ltmp & i1)
         {
           MoveToXY(0,i2++);
           MmiPrintf("!%s",err_F425[i]);
           if(i2>=7)
           {
            ff_serv=NULL;
            return;
           }
         }
       }
       for(;i2<6;i2++)
       {
           MoveToXY(0,i2);
           MmiPuts(s_empty);
       }
     }
   }
   ff_serv=NULL;
   break;
  }
}
//------------------------
/* ---------------------------------------- */
//-------------------------------

char *list1_dsr[]={

"MMI:Статус",                 //  0
"Знаков после зпт.1",         //  1
"Знаков после зпт.2",         //  2
"Знаков после зпт.3",         //  3
"Параметр индик. 1",          //  4
"MMI:Флаг CRC",               //  5

"7017/1:Статус",                //  6
"Колич.резервуаров",            //  7
"Пист.1 N рез-ра",              //  8
"Пист.2 N рез-ра",              //  9
"P_demand",             // 10
"K_D",               // 11
"K_P         ",                // 12
"K_I         ",           // 13
"Mode P    ",                 // 14
"Addr Modbus  ",             // 15
"Delta :Статус",                // 16
"Флаг Slave      ",             // 17

"7060/1:Статус",                 // 18
"K_FD",                   // 19
"K_FP",                   // 20
"K_FI",                   // 21
"Флаг пер.плотн.",        // 22
"",               // 23

"Конц.1 мл/м3",           // 24
"Конц.2 мл/м3",           // 25
"Расх.доз-ра,л/с",        // 26
"Мин.имп.доз-ра,мл",      // 27
"V промывки,л ",          // 28
"T нас.до доз.,мс",       // 29

"T нас.после доз,мс",          // 30
"T сраб.доз-ра,мс",       // 31
"Мин.T выкл.д-ра,мс",     // 32
"V предв.доб,л ",          // 33

#if(Add_pmp == 1)
"Дозатор N вых.",            // 34
#else
"Вкл.нас.П2 N вых.",            // 34
#endif

"Кл.д-ра N вых.",           // 35

"Скан.ICP:CRC флаг",            // 36

"WDOG/1:Статус",                // 37
"WDOG/1:Номер порта",           // 38
"WDOG/1:Период,мс ",            // 39
"WDOG/1:Задержка,мс",           // 40
"WDOG/1:Флаг CRC",              // 41

"T пров.Н.У.,мс  ",                // 42
"T антидр,мс",           // 43
"Поток макс,кг/ч",            // 44
"P min , МПа",           // 45
"",              // 46

"",           // 47
"",        // 48

"7060/2:Разреш.WD",           // 49
"7060/2:Знач.WD,0.1с",        // 50

"MVD:Статус",                 //  51
"",         //  52
"",                  //  53
"",              //  54
"",             //  55

"TSD:Статус",       //  56
"",            //  57
"",                  //  58
"",              //  59
"",             //  60

"",                // 61
"",                // 62
"",                // 63
"",                // 64

"",           // 65
"",           // 66
"",           // 67
"",           // 68

"",           // 69
"",           // 70
"",           // 71
"COM3 Скорость",           // 72

"COM4 Скорость",           // 73
"",              // 74
"",           // 75
"",           // 76

"",        // 77
"Номер входа Gun",         // 78
"Инвер-я входа Gun",       // 79

"Клапан Блш N вых.",        // 80
"Клапан Мнш N вых.",        // 81
"Флаг расш.отчета.",        // 82
"Адрес PUMALAN",            // 83
"Статус PUMALAN",           // 84
"",        // 85
"",        // 86
"",        // 87
"Тип уч.выборки",           // 88
"Переход на лет.вр.",       // 89
"------------------",       // 90
"P полная шкала,МПа",       // 91
"P смещение,    МПа",       // 92
"T полная шкала,C",         // 93
"T смещение,    C",         // 94
"Параметр индик. 2",        // 95
"Параметр индик. 3",        // 96
"Обновл-е индик,мс",        // 97
"ост.масса Б.кл.1",         // 98    p1-p6.CLV
"ост.масса М.кл.2",         // 99
"время срабат.Бкл.1",       // 100
"время срабат.Мкл.2",       // 101
"нач.запр.оп.MMI,мс",      // 102
"длит.запр.о.MMI,мс",       // 103
"подстр.по M 0...1",        // 104   p1-p3.KA
"подстр.по T 0...1",        // 105
"зад-ка зап.отч.,мс",       // 106

"тестовый режим 1/0",       // 107    p1.CTRL
"зад-ка прох.MVD,мс",       // 108    p2.CTRL
"срез расх.для TST",        // 109    p3.CTRL

"первичная M,кг",           // 110    p1-p5.DSC
"экстраполир-я M,кг",        // 111
"расход при сраб.кл",       // 112
"коррекция M,кг",            // 113
"коррекция T,мс",           // 114


"Сгн.'КОНСОЛЬ' N вх.",      // 115
"Сгн.'КОНСОЛЬ'фл.инв",      // 116
"T между вкл.кл.,мс ",      // 117
"T между выкл.кл.,мс ",     // 118
"Режим t отп.0-2",          // 119
"Режим отпуска 1-3",        // 1 2 0

// DNC
"Скор.уменьш.плотн",        // 121
"Зона стаб-ти.плотн",       // 122
"Задержка вкл.кл1,мс",      // 123
"Tmin выкл. кл1,мс",       // 124
"Tmin вкл.  кл1,мс",        // 125

"Датчик уровня N вх.",      // 126
"Датчик уров. фл.инв",      // 127
"Кн.  =Start=  N вх.",        // 128
"Кн.  =Start= фл.инв",      // 129
"Кн.  =Stop=   N вх.",      // 130
"Кн.  =Stop=  фл.инв",      // 131
"Сигнал 'ТРАП' N вх.",      // 132
"Сигнал 'ТРАП'фл.инв",      // 133
"MAX недолив",              // 134
"MAX перелив",              // 135
"WD пер.MASTER,мс",        // 136
// FLCH
"T запрета прп, тик",       // 137
"M нач.кнтр.прп, кг",       // 138
"M опред.переп BIG",        // 139
"M опред.переп LTL",        // 140
"Время переполн,тик",       // 141

#if(Add_pmp == 1)
"Вкл.насоса N вых.",        // 142
#else
"Вкл.нас.П1 N вых.",        // 142

#endif

"Аварийная кн. N вх.",      // 143
"Аварийная кн.фл.инв",      // 144
"Сигнал УЗА  . N вх.",      // 145
"Сигнал УЗА флаг инв",      // 146
"Сигнализ-я N вых.",       // 147
"Давление N анлг.вх.",     // 148
"Температ.N анлг.вх.",     // 149
"-------------------",     // 150
"f  насоса, 0.01 Гц",     // 151
"T разг.насоса,0.1с",      // 152
"Задержка вкл.кл2,мс",     // 153
"Зад.выкл.насоса,мс",      // 154
"T торм.насоса,0.1с",      // 155
"ост.Vol   Б.кл.1",        // 156   p1-p2.CLM
"ост.Vol   М.кл.2",        // 157
"Ном.расх.кг/ч. ",         // 158
"Масса 1,кг  ",            // 159
"Расх.1,кг/ч. ",           // 160
"Масса 2,кг  ",            // 161
"Расх.2,кг/ч. ",           // 162
"Масса 3,кг  ",            // 163
"Расх.3,кг/ч. ",           // 164
"Тип нефтепродукта",       // 165
"",
};
//-------------------------------

char *list2_dsr[]={
" Колич.данных",            //  0
" Знач.АЦП,дискр.",         //  1
" Знач.Давл.,МПа",          //  2
" Знач.Темп.,C",            //  3
};
//-------------------------------
//#define mmi_page   page_MMI_c
#define mmi_page   page_MMI
char mmi_point=0;
//#define size_max 29
int mmi_prm=0;
int mmi_flag=0;

int num_page=0.;
int sw_mmi=0;
int mmi_str=0;
int mmi_com=1;
int flag_chg=0;
int nn_chg=0;
unsigned int pass_cnt;
int max_par=1;
#define NumPlace 22

int FlagWinSum=1;

struct arch_str_t adate11;

struct dis_set_MMI *ds_list=NULL;


long int Password=5555;
long int PassW=0;
int k_ext=0;
int k_ext1=0;
float chg_nn_par=0,chg_old=0,chg_new=0;
float dose_dlvr=0;
int n_adc_mm=0;
int f_menu_MMI()
{
  time_t ltime1;
  time_t ltime2;
  int year,month,day,hour,min,sec;
  int key;
  char str[31];
  int i,j,k;
  struct s_icp_dev *ICPl_DEV;
struct arch_str *ar_str_ptr;
long int ltmp;
 struct tm *tdat;

//   s_MVD[0].Press=( ADC[0] + analog_offset[0]) * analog_scale[0];
   sw_mmi_slv= sw_mmi;
   if((i=fstin())==fst_OK)
   {  // введено числовое значение
     key=DATA;  // признак окончания ввода строки
     sw_fst=0;
   }
   else if(i==fst_ESC)
   {
     key=DATA_ESC;  // признак окончания ввода строки
     sw_fst=0;
   }
   else if( MmiKbhit())
   {  // ввод поступившего символа из клавиатуры
    key=MmiGetch();

    if(key==F1)
    {
      OUT_VAR ^= OUT8;
      return 0;
    }

   }
   else if(sw_fst==0)
   {
    key=PASS; // признак холостого прохода (без введенного символа)
              // используется для индикации изменяющихся значений
   }
   else return 0;

   switch(sw_mmi)
    {
     case 0: /*заголовок*/


//---------------------------------
       if((key==F2) && (id_ok !=0) )
        {
         PageD=0;
         f_prn_begin();
        }
       else if(key==F3)
        {
         PageD=1;
         f_prn_begin();
        }
       else if ((key==F2) && (id_ok ==0) )
        {
       m_0f2:
          MmiGotoxy(1,1);
          f_clr_scr_MMI();

           chg_nn_par=Par_ID;
           chg_old=n_id;
          MmiPuts("Введите ID:" );
          sprintf( fst_str,"%8ld",n_id);
          fst_n=9;
          sw_fst=1;
          MmiGotoxy(10,3);
  //      MmiGotoxy(15,3);
          SetDisplayPage(15); // ввод значения
          break;
        }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&n_id);
          if(n_id<0) { n_id=0; goto m_0f2;}

           chg_new= n_id;
           f_wr_evt(evt_chg_param);
           if( f_check_id(n_id) == 0)
           {
            id_ok=1;
        if(f_wrt_eee()<0)
        {
          f_wr_evt(evt_we_err);
        }
        else
        {
          f_wr_evt(evt_we);
        }
           }
           else
           {
            id_ok=0;
           }
          goto mm00;
        }
       else if(key==DATA_ESC)
        {
          goto mm00;
        }
   /*
       m_0f2:
          MmiGotoxy(1,1);
          f_clr_scr_MMI();
          MmiPuts("Введите номер страницы:" );
          sprintf( fst_str,"%d",num_page);
          fst_n=2;
          sw_fst=1;
//        MmiGotoxy(10,3);
          MmiGotoxy(15,3);
          SetDisplayPage(15); // ввод значения
          break;
        }
       else if(key==DATA)
        {
          sscanf(fst_str,"%d",&num_page);
          if(num_page<0) { num_page=0; goto m_0f2;}
          else if(num_page > 63) {num_page=63; goto m_0f2;}

          SetDisplayPage((int)num_page);
          sw_mmi=100;
          f_clr_scr_MMI();
          break;
        }
       else if(key==DATA_ESC)
        {
          goto m0_f1;
        }
      */
        else
//---------------------------------
        if (key==Sht_ESC)
        {  // очистка ошибок

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);
          sw_mmi=26;
          f_cl_error();
          MmiGotoxy(5,2);    MmiPuts("   Ошибки очищены   ");
          MmiGotoxy(0,4);    MmiPuts(" Enter - продолжить ");

        }
        else if (key==Sht_F1)
        {  // распечатка ошибок

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);
          sw_mmi=26;
          f_disp_error();
        }
        else if(key==Sht_F2)
        {  // MVD zeroing

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);

          if(f_reset_zer_MVD() == 0)
          {
          MoveToXY(0,3);
          MmiPrintf(" Ошибка запуска калибровки ");
          f_wr_evt(evt_MVD_CL_BS2);
  m_SF2:
          MmiGotoxy(0,6); MmiPuts("ESC,ENTER  Возврат");
          sw_mmi=-1;
          break;
          }
          f_wr_evt(evt_MVD_CL_strt);
          sw_mmi=18;
          zero_time=TimeStamp;
          fl_zeroing=1;
          break;
        }
       else if(key==ESC)
       {
m0_f1:
main_menu:
          PageD=0;
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);
          f_prepare_t (&adate00);
          sw_mmi=120;

          Out_off(OUT4);  // Air switch off
          PassW=0;

#if defined(MMI_ICP)
            MmiGotoxy(0,0);    MmiPrintf("АСН %d.   Меню ",Adr_ASN);

          if((WD_PMP_Fl != 0) && (flag_Slv == 2));
          else
            {
              MmiGotoxy(0,1);    MmiPuts("1  Отпуск нефтепродуктов");
              flag_resv=0;
            }

           if( NN_resv > 0)
           {


#if((Add_pmp == 0) || (Add_pmp == 1))
            MmiGotoxy(0,2);    MmiPuts("2  Ввод режима работы");
#endif

#if(Add_pmp == 2)
            MmiGotoxy(0,2);    MmiPuts("2  Ввод номера резервуара");
#endif



           }
            MmiGotoxy(0,3);    MmiPuts("3  Просмотр журнала событий");
            MmiGotoxy(0,4);    MmiPuts("4  Сервисные функции");
            MmiGotoxy(0,5);    MmiPuts("5  Текущие показания расхдм.");
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");

#endif

#if defined(MMI_NEW)

  MmiGotoxy(0,0); MmiPrintf("╔═════════╦═════════╗         ");
  MmiGotoxy(0,1); MmiPrintf("║Доза,кг  ║ Отп.,л  ║         ");
  MmiGotoxy(0,2); MmiPrintf("╠═════════╬═════════╣         ");
  MmiGotoxy(0,3); MmiPrintf("║ 1234    ║         ║         ");
  MmiGotoxy(0,4); MmiPrintf("╟─────────╫─────────╢         ");
  MmiGotoxy(0,5); MmiPrintf("║Test NN  ║  LOAD   ║         ");
  MmiGotoxy(0,6); MmiPrintf("║         ║  731    ║         ");
  MmiGotoxy(0,7); MmiPrintf("╚═════════╩═════════╝         ");

#endif



          break;
       }
       else if(key==PASS)
        {  // отображение даты и времени

         if( id_ok ==0) break;
         if((FL_err|CRC_err) == 0)
         {
          //if(PageD==0)
            {
               MmiGotoxy(14,3);  MmiPrintf("%9.2f кг    ",s_MVD[0].MassI);
               MmiGotoxy(14,4);  MmiPrintf("%9.2f л     ",s_MVD[0].VolI);

              if(I7017C[0].status)
              {
               MmiGotoxy(2,5);   MmiPrintf("%5.3f МПа  ",s_MVD[0].Press);
               MmiGotoxy(17,5);  MmiPrintf("%6.2f град.C",s_MVD[0].TempR);
              }

              // MmiGotoxy(18,4);
              // f_prn_comps();
            }
         }
          GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
          MoveToXY(4,6);
          if((WD_PMP_Fl != 0) && (flag_Slv != 0))
            MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d  Link " ,day,month,year-2000 ,hour,min,sec);
          else
            MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d       " ,day,month,year-2000 ,hour,min,sec);
        }

        break;
 /*========================================*/
    case 11:  /*меню выбора точки для просмотра параметров */
       n_adc_mm=0;
       if(key==ESC)    /* переход в меню M3, Сервисные функции */
       {
         goto m_m3;
       }
       else if(key=='1')  // Базовый список #1
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=0;
        }
       else if(key=='2')  // Базовый список #2
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=max_par/5;
        }
       else if(key=='3')   // Базовый список #3
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*2)/5;
        }
       else if(key=='4')  // Базовый список #4
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*3)/5;
        }
       else if(key=='5')  // Дополнительный список
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*4)/5;
        }

 /*
       else if(key=='6')  // Таблица коррекции давления
        {
         n_adc_mm=0;
         ds_list=ds_list2;
         max_par=max_list2;
         mmi_prm=0;
        }
       else if(key=='7')  // Таблица коррекции температуры
        {
         n_adc_mm=1;
         ds_list=ds_list3;
         max_par=max_list3;
         mmi_prm=0;
        }
 */
       else break;
       flag_chg=0;
       nn_chg=0;

       f_clr_scr_MMI();
       SetDisplayPage(EmptPage);    // Чистая страница
  par_out14:
       for(i=0;i<n_mmi_str_1;i++)
       {

        k=mmi_prm+i;
        if(k>= max_par) continue;
        MoveToXY(0,i);
           MmiPrintf("%2d %s",k+1,ds_list[k].descr[ds_list[k].ind]);
        MoveToXY(NumPlace,i);
           PrintMmiOp(&ds_list[k],1);
       }
       if(flag_chg==0)
       {
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"Enter\"Изм. ");
       }
       else
       {
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\",\"F3\",\"ESC\",\"Enter\"         ");
         MmiGotoxy(2,nn_chg);  MmiPuts("#");
       }
       sw_mmi=14;
       break;
 /*========================================*/
    case 14:/* просмотр до 6 параметров */
       if(key==Sht_F2)    /* сохранение изменений в EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptPage);    // Чистая страница
        MmiGotoxy(0,1);    MmiPuts("Сохранение данных в EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    Сохранить");
        MmiGotoxy(0,4);    MmiPuts("ESC   Не сохранять,продолжить");
        sw_mmi=15;
        break;
       }
/*
       if(key==Sht_F1)    // инит COR
       {
        f_init_COR(0);
        f_init_COR(1);
        f_clr_scr_MMI();
        SetDisplayPage(EmptPage);    // Чистая страница
        goto par_out14;
       }
*/
       if(key==Sht_F3)    /* чтение данных из EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptPage);    // Чистая страница
        MmiGotoxy(0,1);    MmiPuts("Чтение данных из EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    Прочитать ");
        MmiGotoxy(0,4);    MmiPuts("ESC   Не считывать,продолжить");
        sw_mmi=16;
        break;
       }
       if(flag_chg==0)
       {
         if(key==ESC)    /* переход в меню выбора точки для просмотра*/
         {
          goto m_m3_3;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=n_mmi_str_1)
           {
            mmi_prm -=n_mmi_str_1;
            f_clr_scr_MMI();
            SetDisplayPage(EmptPage);    // Чистая страница
            goto par_out14;
           }
           else
           {
            mmi_prm = 0;
            f_clr_scr_MMI();
            SetDisplayPage(EmptPage);    // Чистая страница
            goto par_out14;
           }
         else if((key== F3 )&& (mmi_prm < (max_par-n_mmi_str_1)) )
         {
          mmi_prm +=n_mmi_str_1;
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
          goto par_out14;
         }
         if(key== ENTER)
         {
          flag_chg=1;

          if((nn_chg+mmi_prm) >= max_par)
             nn_chg=max_par-mmi_prm-1;
          goto par_out14;
         }
       }
       else  // flag_chg!=0
       {
         if(key==ESC)    // очистка флага редактирования
         {
          flag_chg=0;
/*
          if((ds_list[0].descr == list2_dsr)&&
               (ds_list[0].ind == 0 ))
          {
            f_init_COR(0);
            f_init_COR(1);
            f_clr_scr_MMI();
       //   SetDisplayPage(EmptPage);    // Чистая страница
            goto par_out14;
          }
*/
          goto par_out14;
         }
         if(key== F1 )
         {
           if((ds_list[nn_chg+mmi_prm].descr == list2_dsr)&&
               (ds_list[nn_chg+mmi_prm].ind == 1 ))
           {
            if(PassW != Password)
               goto m_pass;
//    printf("\r\n op=%g, ADC[%d]=%g ",*(float*)ds_list[nn_chg+mmi_prm].op,n_adc_mm,ADC[n_adc_mm] );
            *(float*)ds_list[nn_chg+mmi_prm].op=ADC[n_adc_mm];
    //      f_init_COR(0);
    //      f_init_COR(1);
            f_clr_scr_MMI();
            SetDisplayPage(EmptPage);    // Чистая страница
            goto par_out14;
           }
           else
               break;
         }
         if((key== F2 )&& (nn_chg>0) )
         {
          nn_chg -=1;
          goto par_out14;
         }
         else if((key== F3 )&& (nn_chg < n_mmi_str_2) )
         {
          nn_chg +=1;

          if((nn_chg+mmi_prm) >= max_par)
             nn_chg=max_par-mmi_prm-1;
          goto par_out14;
         }
         if(key==ENTER)    // редактирование параметра
         {
          if(PassW != Password)
          {
           pass_ret=0;
m_pass:
           MmiGotoxy(1,1);
           f_clr_scr_MMI();
           MmiPuts("Введите пароль:" );
           sprintf( fst_str,"******");
           SetDisplayPage(17);    // Ввод пароля
           sw_mmi=121;
           fst_n=7;
           sw_fst=1;
           MmiGotoxy(11,3);
//         MmiGotoxy(15,3);
           break;
          }

          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"1...9,SHT-7\"-Ввод,\"SHT-4\"-Уд.");
          MmiGotoxy(2,nn_chg);  MmiPuts(">");
          MoveToXY(NumPlace,nn_chg);

          PrintMmiOp(&ds_list[nn_chg+mmi_prm],0);
          fst_n=8;
          sw_fst=1;
          break;
         }
       }
       if(key==DATA)    // ввод полученных данных
       {
         ScanfMmiOp(&ds_list[nn_chg+mmi_prm]);
         f_after_MMI();
         chg_nn_par=nn_chg+mmi_prm+1;
         f_wr_evt(evt_chg_param);
m_14_ni:
         MoveToXY(NumPlace,nn_chg); MmiPuts("         ");
         goto par_out14;
       }
       else if(key==DATA_ESC)
        {
          goto m_14_ni;
        }
       break;
 /*========================================*/
    case 15:/* сохранение данных в EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* возврат к отображению параметров */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
          goto par_out14;
         }
         else if(key=='1')    // сохранить данные
         {

           if(f_wrt_eee()<0)
           {
              f_wr_evt(evt_we_err);
              MmiGotoxy(0,5);   MmiPuts("Ошибка при сохранении данных");
           }
           else
           {
              f_wr_evt(evt_we);
              MmiGotoxy(0,5);   MmiPuts(" Данные сохранены успешно");
           }
              MmiGotoxy(0,6);   MmiPuts("      Enter - продолжить");
         }
         break;
 /*========================================*/
    case 16:/* чтение данных из EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* возврат к отображению параметров */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
          goto par_out14;
         }
         else if(key=='1')    // прочитать
         {

           f_chk_EEE_CRC();
           if(f_rd_eee()<0)
           {
              f_wr_evt(evt_re_err);
              MmiGotoxy(0,5);   MmiPuts("Ошибка при чтении данных");
              CRC_err=1;
           }
           else
           {
              f_wr_evt(evt_re);
              MmiGotoxy(0,5);   MmiPuts("  Данные считаны успешно");
              CRC_err=0;
           }
           f_rd_cor();

           MmiGotoxy(0,6);   MmiPuts("      Enter - продолжить");
         }
         break;
 /*========================================*/
    case 18:
       if( f_timer(zero_time,Time_zeroing ))
       {
             f_clr_scr_MMI();
             MoveToXY(3,3);
            MmiPrintf(" Таймаут калибровки");
          fl_zeroing=0;
          ff_serv=NULL;
          f_wr_evt(evt_MVD_CL_TM);
          goto m_SF2;
       }
          if(ff_serv==NULL)
          {
           if(fl_zeroing==0)
           {
             f_clr_scr_MMI();
             MoveToXY(1,3);
         MmiPrintf("Калибровка завершена успешно");
//                |                              |
             f_wr_evt(evt_MVD_CL_OK);
             goto m_SF2;
           }
           fl_rd_err=0;
           sw_mvd_m1=0;  // нач.параметр
           ff_serv=f_MVD_M3;
          }

         GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
         MoveToXY(4,6);
         MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
         break;
 /*========================================*/
    case 120:  // Основное меню

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
mm00:      sw_mmi=0;

           PageD=0;
//         SetDisplayPage(6);
           SetDisplayPage(ZeroPage);
           f_clr_scr_MMI();
           f_prn_begin();
           break;
       }
//     else if((key== '1') && (id_ok !=0) && (mode_hst == 0) ) //  1  Отпуск нефтепродуктов
       else if((key== '1') && (id_ok !=0) ) //  1  Отпуск нефтепродуктов
       {

        if((WD_PMP_Fl != 0) && (flag_Slv == 2)) break;

        if(mode_hst == 0 ) //  1  Отпуск нефтепродуктов
        {
         MassStamp=s_MVD[0].MassI;
         VolStamp=s_MVD[0].VolI;
         dose_dlvr=0;
         flag_dlv_fst=0;
         flag_prn_mass=0;
         PageD=0;
        }
         f_prepare_t ( &adate00);
m_m5:
         flag_AD=0;
         Out_on(OUT4);  // Air switch on
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();



        MmiGotoxy(0,0);    MmiPrintf("АСН %d. Отпуск нефтепродуктов.",Adr_ASN);
        if((id_ok !=0)&& (mode_hst == 0) )
        {
            f_prn_MassSt_dlv();
            MmiGotoxy(0,2);    MmiPuts("1 Отпуск дозы ");
            MmiGotoxy(0,3);    MmiPuts("2 Отпуск без дозировки");

          if((WD_PMP_Fl != 0) && (flag_Slv == 2)) ;
          else
            if(flag_prn_mass != 0)
          {  MmiGotoxy(0,4);    MmiPuts("3 Продолжить:");

            if(dose_dlvr != vBIG_P)
             {
              if ( Flag_mass != 0 )
                MmiPrintf("Д=%8.2f кг    ",dose_dlvr);
              else
                MmiPrintf("Д=%8.2f л    ",dose_dlvr);
             }
            else
                MmiPrintf("Без дозировки ");

            MmiGotoxy(0,5);
        //    MmiGotoxy(15,5);
            MmiPrintf("О=%8.2f кг,%8.2f л ",s_MVD[0].MassT,s_MVD[0].VolT);
          }
        }
         MmiGotoxy(0,6);    MmiPuts("4-парам.нач.нап.; ESC Возврат");
         sw_mmi=190;
         break;
       }
       else if(key== 'A') //  A  Показания счетчика учета
       {
         f_prepare_t ( &adate00);
m_m1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts("Меню 2.Показания счетчика учета");
            /*

            MmiGotoxy(0,1);    MmiPuts("1  На последний расч. час");
            MmiGotoxy(0,2);    MmiPuts("2  За последние 5 суток");

            MmiGotoxy(0,3);    MmiPuts("3  На указанную дату");
            MmiGotoxy(0,4);    MmiPuts("4  На текущий момент");
            MmiGotoxy(0,5);    MmiPuts("5  Значение расчетного часа");
            */
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
         sw_mmi=130;
         break;
       }


       else if((key== '2') && ( NN_resv > 0) )//  2  ввод номера резервуара
        { // ввод номера резервуара
  m_11s:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         N_resv_tmp=N_resv;


         MmiGotoxy(0,0);    MmiPrintf("АСН %d. Ввод режима работы.",Adr_ASN);



#if((Add_pmp == 0) || (Add_pmp == 1))
         MmiGotoxy(0,1);  MmiPuts("Текущий режим:");  MmiPuts(list_md_add[N_resv_tmp] );
         MmiGotoxy(0,3);  MmiPuts("1 - без добавок");
         MmiGotoxy(0,4);  MmiPuts("2 - с добавкой");
/*
         MmiGotoxy(0,5);  MmiPuts("2 - добавка N1");
         MmiGotoxy(0,5);  MmiPuts("3 - добавка N2");
*/

#endif


#if(Add_pmp == 2)
         MmiGotoxy(0,1);  MmiPuts("Текущий режим:");  MmiPrintf("Рез.N%d",N_resv_dsp[N_resv_tmp] );
         MmiGotoxy(0,3);  MmiPrintf("1 - Резервуар N%d",N_resv_dsp[1]);
         MmiGotoxy(0,4);  MmiPrintf("2 - Резервуар N%d",N_resv_dsp[2]);
/*
         MmiGotoxy(0,5);  MmiPrintf("3 - Резервуар N%d",N_resv_dsp[3]);
*/

#endif

         MmiGotoxy(0,6);  MmiPuts("ESC-Возврат,Enter-ввод");
        sw_mmi=128;
/*
          sprintf( fst_str,"%2d",N_resv);
          fst_n=3;
          sw_fst=1;
          MmiGotoxy(10,3);
*/
         break;
        }
       else if(key== '3') // 3  Просмотр журнала событий
       {
m_m2:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

            i= f_get_max_n_arch();
            ar_str_ptr=f_get_fst_stor();
         MmiGotoxy(0,0);    MmiPrintf("АСН %d. Журнал событий.",Adr_ASN);
            MmiGotoxy(0,1);    MmiPrintf("%4d  ",i);
            j=i%100;
            if((j<=20)&& (j>5))
              MmiPrintf("записей");
            else
            switch(i%10)
            {
             case 1:
             MmiPrintf("запись");
             break;

             case 2:
             case 3:
             case 4:
             MmiPrintf("записи");
             break;

             case 0:
             case 5:
             case 6:
             case 7:
             case 8:
             case 9:
             MmiPrintf("записей");
             break;
            }

   tdat = localtime( &ar_str_ptr->time );
//   MmiPrintf(" с %02d.%02d.%02d %02d:%02d:%02d",
//   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
   MmiPrintf(" с %02d.%02d.%02d",
   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100);

            MmiGotoxy(0,2);    MmiPuts(" Просмотр журнала событий");
            MmiGotoxy(0,3);    MmiPuts("1  По дате");
            MmiGotoxy(0,4);    MmiPuts("2  По номеру записи");
            MmiGotoxy(0,5);    MmiPuts("3  Последние записи");
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");

         PassW=0;
         sw_mmi=140;
         break;
       }
       else if(key== '4') // 4  Сервисные функции
       {
m_m3:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("АСН %d. Сервисные функции.",Adr_ASN);
            MmiGotoxy(0,1);    MmiPuts("1  Список драйверов");
            MmiGotoxy(0,2);    MmiPuts("2  Статистика  драйверов");
            MmiGotoxy(0,3);    MmiPuts("3  Просмотр/ввод параметров");
            MmiGotoxy(0,4);    MmiPuts("4  Другие функции");
            MmiGotoxy(0,5);    MmiPuts("5  Время, дата");
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
         sw_mmi=150;
         PassW=0;
       }

       else if(key== '5') // 5 Текущие показания расходомера
       {
m_m4:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_prn_den_t();
         flg_ch=0;
         sw_mmi=122;
         break;

       }
       else if(key== '6') // 6 Отображение аналоговых входов
       {
m_m6:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("АСН %d. Аналоговые входы:",Adr_ASN);
   MmiGotoxy(0,1); MmiPrintf("    I7017C, дискреты АЦП");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625


   MmiGotoxy(0,4); MmiPrintf(" Состояния дискретных входов:");

  _fmemset( &ADC_c[0],0xff,sizeof(ADC)); // очистка буфера экрана
  INP_VAR_c=0xffff;
         sw_mmi=25;
         break;

       }
       else if(key== '7') // 7 Отображение дискр.выходов
       {
m_m7:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("АСН %d. Дискретные выходы:",Adr_ASN);
   MmiGotoxy(0,6);   MmiPuts(" ESC   - возврат в меню");

         OUT_VAR_c=0xffff;
         sw_mmi=28;
         break;

       }
       else if(key== '8') // 8 Версия sw
       {
m_m8:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

         MmiGotoxy(0,0);    MmiPrintf("АСН %d. ",Adr_ASN);
      MmiGotoxy(0,3);   MmiPrintf("   VER %s",sw_ver);
      MmiGotoxy(0,6);   MmiPuts(" ESC   - возврат в меню");
         sw_mmi=27;
         break;
       }
       else if(key== '-' )// SHT_9  Коррекция расхода
       {
m_m9:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("АСН %d. Коррекция расхода.",Adr_ASN);
            MmiGotoxy(0,1);    MmiPuts("1 Коррекция массового расхода");
            MmiGotoxy(0,2);    MmiPuts("2 Коррекция объемного расхода");
  //        MoveToXY(0,4);   MmiPrintf("Множитель массы:     %.6f",s_MVD[0].f);
  //        MoveToXY(0,5);   MmiPrintf("Множитель объема:    %.6f",s_MVD[0].f);
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");

         Flag_f_corr=0;
         sw_mvd_m1=31;
         tm_mvd=TimeStamp;
         ff_serv=f_MVD_M1f;
         sw_mmi=125;
         break;
       }
       else if(key== '9' )// 9  Срез расхода
       {
m_m9s:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("АСН %d. Срез расхода.",Adr_ASN);
            MmiGotoxy(0,1);    MmiPuts("1 Срез массового расхода");
            MmiGotoxy(0,2);    MmiPuts("2 Срез объемного расхода");
  //        MoveToXY(0,4);   MmiPrintf("Множитель массы:     %.6f",s_MVD[0].f);
  //        MoveToXY(0,5);   MmiPrintf("Множитель объема:    %.6f",s_MVD[0].f);
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");

         Flag_f_corr=0;
         sw_mvd_m1=31;
         tm_mvd=TimeStamp;
         ff_serv=f_MVD_M1s;
         sw_mmi=127;
         break;
       }
       break;
 /*========================================*/
    case 121: // // ввод пароля на изменение данных
       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница

 m121:
          switch(pass_ret)
          { // пароль не введен
          case 0:  goto par_out14;
          case 1:  goto m_m9;
          case 2:  goto m_m9;
          case 3:  goto m_m3;
          case 5:  goto m_m9s;
          case 6:  goto m_m9s;
          default:
                goto main_menu;
          }
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&ltmp);
          if(ltmp == Password)
                PassW=Password;
          else goto m_pass;
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
          switch(pass_ret)
          { // пароль введен корректно
          case 0:  goto par_out14;
          case 1:
                sw_mmi=125;
                goto m_m9_1;
          case 2:
                sw_mmi=125;
                goto m_m9_2;
          case 3:
                sw_mmi=162;
                goto m_m3_6_1;
          case 5:
                sw_mmi=127;
                goto m_m9s_1;
          case 6:
                sw_mmi=127;
                goto m_m9s_2;
          default:
                goto main_menu;
          }
        }
       else if(key==DATA_ESC)
        {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
          goto m121;
        }

 /*========================================*/
    case 122:
 //  Отображение Плотности,температуры,состава
 //  Текущее значение.
       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
         goto main_menu;
       }
       else if(key==PASS)
       {
         f_prn_den_t();
       }
       else if(key==F2)
       {
          MVD_fn[0]=MVD_WR_C;
          s_MVD[0].r_addr=3; // Reset all totalizers
/*
          s_MVD[0].r_addr=04; // Reset all inventories
          s_MVD[0].r_addr=3; // Reset all totalizers
          s_MVD[0].r_addr=56; // Reset mass total
          s_MVD[0].r_addr=57; // Reset volume totales
*/
          s_MVD[0].i=1;
       }
       else if(key==Sht_F1)
       {
        if(flg_ch==2)
        {
          MVD_fn[0]=MVD_WR_C;
          s_MVD[0].r_addr=04; // Reset all inventories
/*
          s_MVD[0].r_addr=56; // Reset mass total
          s_MVD[0].r_addr=04; // Reset all inventories
          s_MVD[0].r_addr=57; // Reset volume totales
*/
          s_MVD[0].i=1;
        }
       }
       else if(key==Sht_F2)
       {
        if(flg_ch==1) flg_ch++;
        else flg_ch=0;
       }
       else if(key==Sht_F3)
       {
        if(flg_ch==0) flg_ch++;
        else flg_ch=0;
       }
       else flg_ch=0;
       break;
 /*========================================*/
    case 125:
 //  Меню 9.Коррекция расхода.
       if((key==ESC)||(key==ENTER) )    /* переход в меню */
       {
         sw_fst=0;
         ff_serv=NULL;
         goto main_menu;
       }

       if((key=='1')&&(Flag_f_corr!=0))
       {

          if(PassW != Password)
          {
           pass_ret=1;
           goto m_pass;
          }

m_m9_1:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ввод значения
          f_clr_scr_MMI();
          MmiPuts("Введите коррекцию массы:" );
          k_mv_tmp=k_m_flow;
          flag_mass=1;
m_m9_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-Ввод,\"SHT-4\"-Уд.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"ESC - возврат");
          if(flag_mass!=0)
          {
           sprintf( fst_str,"%.6f",k_mv_tmp);
           fst_n=9;
          }
          else
          {
//         sprintf( fst_str,"%8.2f",k_mv_tmp);
           sprintf( fst_str,"%.6f",k_mv_tmp);
           fst_n=9;
          }
          sw_fst=1;
          MmiGotoxy(10,3);
          break;
       }
       if((key=='2')&&(Flag_f_corr!=0))
       {
          if(PassW != Password)
          {
           pass_ret=2;
           goto m_pass;
          }
m_m9_2:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ввод значения
          f_clr_scr_MMI();
          MmiPuts("Введите коррекцию объема:" );
//        MmiPuts("Введите срез масс.расх.кг/ч:" );
          k_mv_tmp=k_v_flow;
          flag_mass=0;
          goto m_m9_1_1;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%f",&k_mv_tmp);

         if(flag_mass)
         {
          if((k_mv_tmp<0.8)||(k_mv_tmp>1.2) )
                goto m_m9_1;
         }
         else
         {
          if(k_mv_tmp<0) goto m_m9_2;
         }

      // введенное значение в k_mv_tmp
          if(flag_mass)
          {
           s_MVD[0].r_addr=279; // Множитель массы.

           chg_nn_par=Par_MF;
           chg_old=k_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else
          {
           s_MVD[0].r_addr=281; // Множитель объема.
           chg_nn_par=Par_VF;

//         s_MVD[0].r_addr=195; // Срез масс.расхода
//         chg_nn_par=Par_MC;

           chg_old=k_v_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          MVD_fn[0]=MVD_WR_F;;
          s_MVD[0].f = k_mv_tmp;
          goto m_m9;
        }
       else if(key==DATA_ESC)
        {
          goto m_m9;
        }

       break;
 /*========================================*/
    case 126:
 //  Меню 1.4.Коррекция параметров начального наполнения
       if((key==ESC)||(key==ENTER) )    /* переход в меню */
       {
         goto m_m5;
       }

     if(valve_mode != 1)
       if(key=='2')
       {

m_m5_4_1:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ввод значения
          f_clr_scr_MMI();
          MmiPuts("Введите начальный расход,кг/ч:" );
          k_mv_tmp=Flow_beg;
          flag_mass=1;
m_m5_4_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-Ввод,\"SHT-4\"-Уд.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("ESC-возврат,Enter-ввод данных");
          if(flag_mass!=0)
          {
           sprintf( fst_str,"%6.0f",k_mv_tmp);
           fst_n=7;
          }
          else
          {
           sprintf( fst_str,"%6.0f",k_mv_tmp);
           fst_n=7;
          }
          sw_fst=1;
          MmiGotoxy(10,3);
          break;
       }
       if(key=='1')
       {
m_m5_4_2:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ввод значения
          f_clr_scr_MMI();
          MmiPuts("Введите начальный объем,л :" );
          k_mv_tmp=Vol_beg;
          flag_mass=0;
          goto m_m5_4_1_1;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%f",&k_mv_tmp);

         if(flag_mass)
         {
          if((k_mv_tmp<0)|| (k_mv_tmp> 200000))
                goto m_m5_4_1;
         }
         else
         {
          if((k_mv_tmp<0)|| (k_mv_tmp> 400000))
                goto m_m5_4_2;
         }

      // введенное значение в k_mv_tmp
          if(flag_mass)
          {

           chg_nn_par=Par_FB;
           chg_old= Flow_beg;
           chg_new= k_mv_tmp;

           Flow_beg=k_mv_tmp; // начальный расход,кг/ч
           f_wr_evt(evt_chg_param);
          }
          else
          {
           chg_nn_par=Par_VB;

           chg_old=Vol_beg;
           chg_new= k_mv_tmp;
           Vol_beg=k_mv_tmp;   // начальный объем,л
           f_wr_evt(evt_chg_param);
          }
          goto m_m5_4;
        }
       else if(key==DATA_ESC)
        {
          goto m_m5_4;
        }

       break;
 /*========================================*/
    case 127:
 //  Меню 9S.Срез  расхода.
       if((key==ESC)||(key==ENTER) )    /* переход в меню */
       {
         sw_fst=0;
         ff_serv=NULL;
         goto main_menu;
       }

       if((key=='1')&&(Flag_f_corr!=0))
       {

          if(PassW != Password)
          {
           pass_ret=5;
           goto m_pass;
          }

m_m9s_1:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ввод значения
          f_clr_scr_MMI();
          MmiPuts("Введите срез м.расх.кг/ч:" );
          k_mv_tmp=k_m_flow;
          flag_mass=1;
m_m9s_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-Ввод,\"SHT-4\"-Уд.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"ESC - возврат");
          if(flag_mass!=0)
          {
           sprintf( fst_str,"%8.1f",k_mv_tmp);
           fst_n=9;
          }
          else
          {
           sprintf( fst_str,"%8.3f",k_mv_tmp);
           fst_n=9;
          }
          sw_fst=1;
          MmiGotoxy(10,3);
          break;
       }
       if((key=='2')&&(Flag_f_corr!=0))
       {
          if(PassW != Password)
          {
           pass_ret=6;
           goto m_pass;
          }
m_m9s_2:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ввод значения
          f_clr_scr_MMI();
          MmiPuts("Введите срез об.расх.л/сек:" );
          k_mv_tmp=k_v_flow;
          flag_mass=0;
          goto m_m9s_1_1;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%f",&k_mv_tmp);

         if(flag_mass)
         {
          if((k_mv_tmp<0)||(k_mv_tmp>100000.) )
                goto m_m9s_1;
         }
         else
         {
          if((k_mv_tmp<0)||(k_mv_tmp>1000.) )
                goto m_m9s_2;
         }

      // введенное значение в k_mv_tmp
          if(flag_mass)
          {
           s_MVD[0].r_addr=195; // Срез масс.расх.

           chg_nn_par=Par_MC;
           chg_old=k_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else
          {
           s_MVD[0].r_addr=197; // Срез об. расх.
           chg_nn_par=Par_VC;

           chg_old=k_v_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          MVD_fn[0]=MVD_WR_F;;
          s_MVD[0].f = k_mv_tmp;
          goto m_m9s;
        }
       else if(key==DATA_ESC)
        {
          goto m_m9s;
        }

       break;
 /*========================================*/
 /*

    case 1280:
 //  Меню 1S.Номер резервуара.
       if((key==ESC)||(key==ENTER) )    // переход в меню
       {
         goto main_menu;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%d",&N_resv_tmp);
         if(NN_resv != 0)
         {
          if((N_resv_tmp<1)||(N_resv_tmp>10) )  goto m_11s;
         }
         else
          if(N_resv_tmp!= 0)  goto m_11s;

      // введенное значение в N_resv_tmp

           chg_nn_par=Par_RESV;
           chg_old=N_resv;
           chg_new= N_resv_tmp;
           f_wr_evt(evt_chg_param);
           N_resv=N_resv_tmp;

           WriteNVRAM((int) nr_resv, N_resv );

           break;
        }
       else if(key==DATA_ESC)
        {
          goto main_menu;
        }
       break;

 */
 /*========================================*/
    case 128:
 //  Меню 1S.Режим работы.

#if((Add_pmp == 0) || (Add_pmp == 1))
       MmiGotoxy(0,1);  MmiPuts("Текущий режим:");  MmiPuts(list_md_add[N_resv_tmp] );
#endif

#if(Add_pmp == 2)
         MmiGotoxy(0,1);  MmiPuts("Текущий режим:");  MmiPrintf("Рез.N%d",N_resv_dsp[N_resv_tmp] );
#endif

       if(key==ESC)    /* переход в меню */
       {
         goto main_menu;
       }
       if(key==ENTER)     /* переход в меню */
       {

          if(N_resv_tmp != N_resv)
          {
      // введенное значение в N_resv_tmp

           chg_nn_par=Par_RESV;
           chg_old=N_resv;
           chg_new= N_resv_tmp;
           f_wr_evt(evt_chg_param);
           N_resv=N_resv_tmp;

           WriteNVRAM((int) nr_resv, N_resv );
          }

         goto main_menu;
       }
       else if(key=='1')
        {
         N_resv_tmp=1;
        }
       else if(key=='2')
        {
         N_resv_tmp=2;
        }
/*
       else if(key=='3')
        {
         N_resv_tmp=3;
        }
*/
       break;


 /*========================================*/
    case 130: // //  1  Состояние отпуска нефтепродуктов

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           goto main_menu;
       }

       else if(key== '1')  // 1  На последний расч. час
       {
m_m1_1:
  //     mmi_str=0;
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_prn_lst_hour();
         sw_mmi=131;
       }
       else if(key== '2')  // 2  За последние 5 суток
       {
m_m1_2:
  //     mmi_str=0;

//printf("\r\n===0===");
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

         f_prn_5day();
         sw_mmi=131;
       }
       else if(key== '3')  // 3  На указанную дату
       {
m_m1_3:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   Дата состояния счетчика");
           MmiGotoxy(0,1);    MmiPuts("      День.Мес.Год");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=134;
       }
       else if(key== '4')  //4  На текущий момент
       {
m_m1_4:
    //   mmi_str=0;
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_prn_current();
         sw_mmi=132;
       }
       else if(key== '5')  //5  Значение расчетного часа
       {
m_m1_5:
      // mmi_str=0;
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("  Значение расчетного часа");
           MmiGotoxy(0,1);    MmiPuts("       Час.Мин.Сек");
        // MmiGotoxy(0,2);    MmiPuts("        08.00.00");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)ahour00.hour,(int)ahour00.min,(int)ahour00.sec );
          fst_n=9;
          sw_fst=1;
          sw_mmi=133;
       }
       break;
 /*========================================*/
    case 131:
 //  Отображение Состояния отпуска нефтепродуктов.
 // На последний расч. час .
       if((key==ESC)||(key==ENTER))    /* переход в вышестоящее меню */
       {
         goto m_m1;
       }
       break;
 /*========================================*/
    case 132:
 //  Отображение Состояния отпуска нефтепродуктов.
 //  Текущее значение.
       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
         goto m_m1;
       }
       else if(key==PASS)
       {
         f_prn_current();
       }
       break;
 /*========================================*/
    case 133:
 //  Отображение расчетного часа.
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
       {
         goto m_m1;
       }
       else if(key==DATA)
        {
            hour= ahour00.hour;
            min = ahour00.min ;
            sec = ahour00.sec ;
          sscanf(fst_str,"%d.%d.%d",&hour,&min,&sec);
   // printf("\n\r %d.%d.%d ",hour,min,sec);
          if((hour<0)||(hour > 23)) goto m_m1_5;
          if((min<0)|| (min > 59))  goto m_m1_5;
          if((sec<0)|| (sec > 59))  goto m_m1_5;
          i=0;
          if(ahour00.hour != hour)
          {
            ahour00.hour= hour;
            i=1;
          }
          if(ahour00.min != min);
          {
             ahour00.min = min ;
            i=1;
          }
          if(ahour00.sec != sec)
          {
            ahour00.sec = sec ;
            i=1;
          }
          if(i)
           if(f_wrt_eee()<0)
           {
              MmiGotoxy(0,5);   MmiPuts("Ошибка при сохранении данных");
              sw_mmi=131;
           }
           else goto m_m1;

          break;
        }
       break;
 /*========================================*/
    case 134:
 //  Ввод даты
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
       {
         goto m_m1;
       }
       else if(key==DATA)
        {
          year=(int)(adate00.year+2000);
          month=(int)adate00.month;
          day=(int)adate00.day;

          sscanf(fst_str,"%d.%d.%d",&day,&month,&year);
          if((year<2000)||(year > 2100)) goto m_m1_3;
          if((month<1)|| (month > 12))  goto m_m1_3;
          if((day<1)|| (day > 31))  goto m_m1_3;


             adate00.year = year-2000 ;
             adate00.month = month;
             adate00.day = day;
            // дата введена
            // отображение значения отпуска
            SetDisplayPage(EmptPage);
            f_clr_scr_MMI();
            f_prn_date();
            sw_mmi=131;

          break;
        }
       break;
 /*========================================*/
    case 140: // 2  Просмотр журнала событий

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           goto main_menu;
       }
        else if (key==DEL)
        {

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
          MmiGotoxy(0,1);    MmiPuts(" 1 - Перезагрузка");
          MmiGotoxy(0,2);    MmiPuts(" 6 - Выход из программы в ОС");
          MmiGotoxy(0,3);    MmiPuts("    (при  отладке)");
          MmiGotoxy(0,5);    MmiPuts("ESC   отмена");
          sw_mmi=142;
          break;
        }
       else if(key== '1')  //1  По дате
       {
m_m2_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   Дата записи журнала ");
           MmiGotoxy(0,1);    MmiPuts("      День.Мес.Год");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=143;
          break;
       }
       else if(key== '2')  //2  По номеру записи
       {
m_m2_2:
          max_par= f_get_max_n_arch();
          MmiGotoxy(1,1);
          f_clr_scr_MMI();
          MmiPuts("Введите номер записи:" );
          sprintf( fst_str,"%d",max_par);
          fst_n=4;
          sw_fst=1;
          MmiGotoxy(15,3);
          SetDisplayPage(15); // ввод значения
          break;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%d",&i);
          if(i<1) { goto m_m2_2;}
          else if(i>max_par) { goto m_m2_2;}
          mmi_prm=i-1;
          goto m_m2_3v;
        }
       else if(key==DATA_ESC)
        {
          goto m_m2;
        }
       else if(key== '3')  //3  Последние записи
       {
m_m2_3:
         max_par= f_get_max_n_arch();
         mmi_prm=max_par-2;

m_m2_30:
         if(mmi_prm>(max_par-1))
            mmi_prm=max_par-2;
         if(mmi_prm<0) mmi_prm=0;


m_m2_3v:
         f_clr_scr_MMI();
         SetDisplayPage(EmptPage);    // Чистая страница

   //----------------
        ar_str_ptr= f_get_astr(mmi_prm);
        k=f_prn_mmi_a(ar_str_ptr,0);
        if(k>=3)
        {
          k_ext1=0;
          k_ext=7;
          goto m_m2_32;
        }
  if(mmi_prm==(max_par-1)) goto m_m2_32;

        ar_str_ptr= f_get_astr(mmi_prm+1);
        k_ext=f_prn_mmi_a(ar_str_ptr,k+1);
        k_ext1=0;
  if(mmi_prm==(max_par-2)) goto m_m2_32;

        if(k_ext<4)
        {
          ar_str_ptr= f_get_astr(mmi_prm+2);
          k_ext=f_prn_mmi_a(ar_str_ptr,k_ext+1);
          k_ext1=1;
        }
   //----------------
m_m2_32:
        MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");

        sw_mmi=141;
       }
       break;
 /*========================================*/
    case 141:/*просмотр 2 записей журнала*/
         if(key==ESC)    /* переход в меню выбора точки для просмотра*/
         {
          goto m_m2;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=2)
           {
            mmi_prm -=2;
            goto m_m2_3v;
           }
           else
           {
            mmi_prm = 0;
            goto m_m2_3v;
           }
         else if (key== F3 )
         {
           max_par= f_get_max_n_arch();
           if(mmi_prm <= (max_par-2))
           {
            if(k_ext1==0)
             if(k_ext<=5)
               mmi_prm +=2;
             else
               mmi_prm +=1;
            else
             if(k_ext<=5)
               mmi_prm +=3;
             else
               mmi_prm +=2;
            if(mmi_prm >= max_par)
              mmi_prm=max_par-1;
            goto m_m2_3v;
           }
         }
    break;
 /*========================================*/
    case 142:/* выход из программы */
             /* возврат к просмотру */
       if((key==ESC)||(key==ENTER))    /* переход в меню */
         {
          goto m_m2;
         }
         else if(key== '1' )
         { //  1 - Перезагрузка
           f_wr_evt(evt_res);
           _asm cli
           _asm hlt
         }
         else if(key== '6' )
         {// 6 - Выход из программы в ОС
            f_wr_evt(evt_exit);
            return 1; // выход из программы *.exe в ОС
         }
         break;
 /*========================================*/
    case 143:

 //  Ввод даты
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
       {
         goto m_m2;
       }
       else if(key==DATA)
        {
          year=(int)(adate00.year+2000);
          month=(int)adate00.month;
          day=(int)adate00.day;

          sscanf(fst_str,"%d.%d.%d",&day,&month,&year);
          if((year<2000)||(year > 2100)) goto m_m2_1;
          if((month<1)|| (month > 12))  goto m_m2_1;
          if((day<1)|| (day > 31))  goto m_m2_1;

             adate00.year = year-2000 ;
             adate00.month = month;
             adate00.day = day;
            // дата введена

m_m2_1_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   Время записи журнала ");
           MmiGotoxy(0,1);    MmiPuts("       Час Мин.");
        // MmiGotoxy(0,2);    MmiPuts("        08.01");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d",(int)adate00.hour,(int)adate00.min );
          fst_n=6;
          sw_fst=1;
          sw_mmi=144;
       }
          break;

 /*========================================*/
    case 144:
 //  Ввод времени
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
       {
         goto m_m2_1;
       }
       else if(key==DATA)
        {
          hour=(int)adate00.hour;
          min=(int)adate00.min;

          sscanf(fst_str,"%d.%d",&hour,&min);
          if((min<0)|| (min > 59))  goto m_m2_1_1;
          if((hour<0)|| (hour > 23))  goto m_m2_1_1;


             adate00.min = min;
             adate00.hour = hour;
             adate00.sec = 0;
            // время введено

            SetDisplayPage(EmptPage);
            f_clr_scr_MMI();

         ltime1=f_get_time_t(&adate00);
         k=f_get_dat_n(ltime1);
         if(k<0)
         {
           ltime2=f_get_time(f_get_fst_stor());
           if(ltime1<=ltime2)
           {
             k=0;
           }
           else k=f_get_max_n_arch();
         }
         mmi_prm=k;
         max_par= f_get_max_n_arch();
         goto m_m2_30;
        }
         break;
 /*========================================*/
    case 150: // 3  Сервисные функции

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           goto main_menu;
       }

       else if(key== '1')  // 1  Список драйверов
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_2:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_drv_list_MMI(&mmi_str);
         sw_mmi=22;
       }
       else if(key== '2')  // Статистика  драйверов
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_3:
         SetDisplayPage(EmptPage);  // чистый экран
         f_clr_scr_MMI();
         f_drv_stat_MMI(&mmi_str);
         pass_cnt=0;
         sw_mmi=23;
       }
       else if(key== '3')   //  3  Просмотр/ввод параметров
       {
m_m3_3:

   //     PassW=0;
        // переход в меню выбора точки для просмотра параметров
//          SetDisplayPage(11);
          sw_mmi=11;
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" Меню выбора списка просмотра");
            MmiGotoxy(0,2);    MmiPuts("1...5 Список параметров");
  //        MmiGotoxy(0,3);    MmiPuts("6 Табл.тарир.датчика давления");
  //        MmiGotoxy(0,4);    MmiPuts("7 Табл.тарир.датчика температ.");
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
          break;
       }
       else if(key== '4')   //  4  Другие функции
       {
m_m3_4:
         SetDisplayPage(EmptPage);  // чистый экран
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" Меню 4.4.Другие функции. ");
            MmiGotoxy(0,1);    MmiPuts("1  Показания расходомера");
            MmiGotoxy(0,2);    MmiPuts("2  Параметры расходомера");
            MmiGotoxy(0,3);    MmiPuts("3  Ошибки расходомера");
            MmiGotoxy(0,4);    MmiPuts("4  Поиск ICP/RTU модулей");
            MmiGotoxy(0,5);    MmiPuts("5  Список найденных модулей");
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
         sw_mmi=160;
          break;
       }
       else if(key== '5')   //  5  Время, дата
       {
m_m3_5:
         f_prepare_t ( &adate00);
         adate11=adate00;
         SetDisplayPage(EmptPage);  // чистый экран
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("      Текущая дата ");
           MmiGotoxy(0,1);    MmiPuts("      День.Мес.Год");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("Переход лет/зим.время выключен");
else                          MmiPuts("Переход лет/зим.время включен");

/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - летнее
                              MmiPuts("      Летнее время");
     else                     MmiPuts("      Зимнее время");
*/
            MmiGotoxy(0,4);   MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);   MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);   MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=165;
          break;
       }
       else if(key== '6')   //  6  Изменить пароль
       {
m_m3_6:
         SetDisplayPage(EmptPage);  // чистый экран
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" Меню 4.6.Изменение пароля ");
            MmiGotoxy(0,2);    MmiPuts("1  Изменить пароль");
            f_d_ESC();
         sw_mmi=162;
          break;
       }
       break;
 /*========================================*/
    case 160: // M3.4  Другие функции

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           goto m_m3;
       }
       else if(key== '1') //  1  Показания расходомера
       {
         max_par=10;
         mmi_prm=0;

m_m3_4_1v:

         if(ff_serv==NULL)
         {
          SetDisplayPage(EmptPage);
          f_clr_scr_MMI();
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");
          sw_MMI_cur=0; // строка MMI
          sw_mvd_m1=mmi_prm+20;  // нач.параметр
          sw_MMI_lim=6; // конечная строка
          MMIDens=-1;
          MMITemp=-300;
          ff_serv=f_MVD_M2;
          sw_mmi=171;
         }
         else
          sw_mmi=173;
         break;
       }

       else if(key== '2') //  2  Параметры расходомера
       {
         max_par=17;
         mmi_prm=0;

m_m3_4_2v:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");

         if(ff_serv==NULL)
         {
          sw_MMI_cur=0; // строка MMI
          sw_mvd_m1=mmi_prm+20;  // нач.параметр
          sw_MMI_lim=6; // конечная строка

          ff_serv=f_MVD_M1;
          sw_mmi=172;
         }
         else
          sw_mmi=174;
         break;
       }
       else if(key== '3') // 3  Ошибки расходомера
       {
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,6);    MmiPuts("ESC,ENTER  Возврат");
         sw_mvd_m1=0;
         ff_serv=f_MVD_M3;
         sw_mmi=180;

         break;

       }

       else if(key== '5') //  5  Список подключенных модулей
       {
         mmi_str=0;
         max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
m20_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_mod_list_MMI(&mmi_str);
         sw_mmi=21;
       }
       else if(key== '4')  // 4  Поиск ICP/RTU модулей
       {
m20_4:
          f_clr_scr_MMI();
          MmiGotoxy(1,1);
          MmiPuts("Введите номер порта : " );
          sprintf( fst_str,"%2d",mmi_com);
          fst_n=3;
          sw_fst=1;
          MmiGotoxy(13,3);
          SetDisplayPage(15);
          break;
       }
       else if(key== DATA )
       {
          sscanf(fst_str,"%d",&mmi_com);  // номер COM
          if((mmi_com>0)&&(mmi_com<4)) licp_port=mmi_com;
          else
          {
            if(mmi_com<1)  mmi_com=1;
            else if (mmi_com>3)  mmi_com=3;
            goto m20_4;
          }

          if(ComProt[mmi_com]==0)
          {
            licp_sw=1;
            ff_serv=f_look_ICP;
            flag_print_licp=0;
            LICP_Rqst.timeout=ToutLicpScan;
            licp_crc_flag=LICP_Rqst.CRC_flag;
          }
          else
          {
            licp_sw=1;
            ff_serv=f_look_RTU;
            flag_print_licp=0;
            LICP_Rqst_RTU.timeout=ToutLicpScan;
          }

       f_clr_scr_MMI();
       SetDisplayPage(EmptPage);

       if(ComProt[mmi_com]==0)
       {
         MmiGotoxy(0,0);     MmiPrintf("ICP COM%d: таймаут %d мс",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("Макс.Адр %d,флаг CRC=%d",licp_amax,LICP_Rqst.CRC_flag);
       }
       else
       {
         MmiGotoxy(0,0);     MmiPrintf("RTU COM%d: таймаут %d мс",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("Макс.Адр %d",licp_amax);
       }

       MmiGotoxy(0,6);  MmiPuts("  Enter - продолжить");
       sw_mmi=24;
       break;
       }
       else if(key==DATA_ESC)
        {
          goto m_m3_4;
        }
       break;
 /*========================================*/
    case 162:
 //  Изменение пароля
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
       {
         goto m_m3;
       }
       else if(key== '1')   // 1  Изменить пароль
       {

          if(PassW != Password)
          {
           pass_ret=3;
           goto m_pass;
          }
m_m3_6_1:

          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ввод значения
          f_clr_scr_MMI();
          MmiPuts("Введите новый пароль(1-й раз):" );
           pass1=-1;
           sprintf( fst_str,"******");
           SetDisplayPage(17);    // Ввод пароля
           sw_mmi=163;
           fst_n=7;
           sw_fst=1;
           MmiGotoxy(11,3);
           break;
       }
       break;
 /*========================================*/
    case 163: // // ввод нового пароля 1 раз
       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
 m163:
          goto m_m3;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&pass1);
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
           // пароль введен корректно
           if(pass1>= 0)
           {
             MmiGotoxy(0,1);
             SetDisplayPage(EmptPage); // ввод значения
             f_clr_scr_MMI();
             MmiPuts("Введите новый пароль(2-й раз):" );
             pass2=-1;
             sprintf( fst_str,"******");
             SetDisplayPage(17);    // Ввод пароля
             fst_n=7;
             sw_fst=1;
             MmiGotoxy(11,3);
             sw_mmi=164;
             break;
           }
           else goto m_m3_6_1;
        }
       else if(key==DATA_ESC)
        {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
          goto m163;
        }

 /*========================================*/
    case 164: // // ввод нового пароля 2 раз
       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
          goto m163;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&pass2);
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
           // пароль введен корректно
           if(pass2 == pass1)
           {
             chg_nn_par=Par_PASS;
             chg_old=Password;
             chg_new= pass1;
             Password=pass1;
             f_wr_evt(evt_chg_param);

             if(f_wrt_eee()<0)
             {
                f_wr_evt(evt_we_err);
                MmiGotoxy(1,3);   MmiPuts("Ошибка при сохранении пароля");
             }
             else
             {
                f_wr_evt(evt_we);
                MmiGotoxy(3,3);   MmiPuts("Пароль сохранен успешно");
             }
             f_wr_cor();
             MmiGotoxy(0,6);   MmiPuts("      Enter - продолжить");
             break;
           }
           else goto m_m3_6_1;

        }
       else if(key==DATA_ESC)
        {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // Чистая страница
          goto m163;
        }

 /*========================================*/

 /*========================================*/
    case 165:

 //  Ввод даты для изменения
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
       {
         goto m_m3;
       }
       else if(key==DATA)
        {
          year=(int)(adate00.year+2000);
          month=(int)adate00.month;
          day=(int)adate00.day;

          sscanf(fst_str,"%d.%d.%d",&day,&month,&year);
          if((year<2000)||(year > 2100)) goto m_m3_5;
          if((month<1)|| (month > 12))  goto m_m3_5;
          if((day<1)|| (day > 31))  goto m_m3_5;

             adate00.year = year-2000 ;
             adate00.month = month;
             adate00.day = day;
            // дата введена
           if((adate00.year  != adate11.year ) ||
              (adate00.month != adate11.month) ||
              (adate00.day   != adate11.day  ) )
           {

// printf("\n\r %02d.%02d.%02d" ,day,month,year-2000);

            f_wr_evt(evt_none);
            SetDate( year, month, day);

            WriteNVRAM((int)nr_year  ,(int)(year-2000));
            WriteNVRAM((int)nr_month ,(int)month  );
            WriteNVRAM((int)nr_day   ,(int)day    );
            init_win_sum(0);
            f_wr_evt(evt_ch_date);
            adate11=adate00;
//          printf("\n\r Date have changed ");
           }

m_m3_5_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("      Текущее время ");
           MmiGotoxy(0,1);    MmiPuts("       Час Мин Сек");
        // MmiGotoxy(0,2);    MmiPuts("         08.01.00");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("Переход лет/зим.время выключен");
else                          MmiPuts("Переход лет/зим.время включен");
/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - летнее
                              MmiPuts("      Летнее время");
     else                     MmiPuts("      Зимнее время");
*/





            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)adate00.hour,(int)adate00.min,(int)adate00.sec);
          fst_n=9;
          sw_fst=1;
          sw_mmi=166;
       }
          break;

 /*========================================*/
    case 166:
 //  Ввод времени
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
       {
         goto m_m3_5;
       }
       else if(key==DATA)
        {
          hour=(int)adate00.hour;
          min=(int)adate00.min;
          sec=(int)adate00.sec;

          sscanf(fst_str,"%d.%d.%d",&hour,&min,&sec);
          if((min<0)|| (min > 59))  goto m_m3_5_1;
          if((sec<0)|| (sec > 59))  goto m_m3_5_1;
          if((hour<0)|| (hour > 23))  goto m_m3_5_1;

             adate00.min = min;
             adate00.hour = hour;
             adate00.sec = sec;
            // время введено
           if((adate00.hour  != adate11.hour ) ||
              (adate00.min   != adate11.min) ||
              (adate00.sec   != adate11.sec  ) )
           {
//          printf("\n\r Time have changed ");
            f_wr_evt(evt_none);
            SetTime( adate00.hour, adate00.min,adate00.sec);
    WriteNVRAM((int)nr_hour   ,(int)hour   );
    WriteNVRAM((int)nr_min    ,(int)min    );
    WriteNVRAM((int)nr_sec    ,(int)sec    );
            init_win_sum(0);
            f_wr_evt(evt_ch_time);
           }

         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

         goto m_m3;
        }
         break;
 /*========================================*/
 /*========================================*/
    case 21:  // просмотр списка модулей

       max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
       if((key==ESC)||(key==ENTER))   /* переход в меню выбора точки для просмотра*/
       {
          goto m_m3_4;
       }
       else if((key== F2 )&& (mmi_str>0) )
       {
        mmi_str -=n_mmi_str_3;
        goto m20_1;
       }
       else if((key== F3 )&& (mmi_str < (max_par-n_mmi_str_3)) )
       {
        mmi_str +=n_mmi_str_3;
        goto m20_1;
       }
       break;
 /*========================================*/
    case 22: // просмотр списка драйверов

       if((key==ESC)||(key==ENTER))    /* переход в меню выбора точки для просмотра*/
       {
        goto m_m3;
       }
       else if((key== F2 )&& (mmi_str>0) )
       {
        mmi_str -=n_mmi_str_3;
        goto m20_2;
       }
       else if((key== F3 )&& (mmi_str < (max_par-n_mmi_str_3)) )
       {
        mmi_str +=n_mmi_str_3;
        goto m20_2;
       }
       break;
 /*========================================*/
    case 23: // просмотр статистики драйверов

       if((key==ESC)||(key==ENTER))    /* переход в меню выбора точки для просмотра*/
       {
        goto m_m3;
       }
       else if((key== F2 )&& (mmi_str>0) )
       {
        mmi_str -=n_mmi_str_3;
        goto m20_3;
       }
       else if((key== F3 )&& (mmi_str < (max_par-n_mmi_str_3)) )
       {
        mmi_str +=n_mmi_str_3;
        goto m20_3;
       }
       else if (key==Sht_ESC)
        {  // обнуление счетчиков ошибок
           for(i=0;i<icp_lst_max;i++)
           {
             ICPl_DEV=ICP_dd[i];
             if(ICPl_DEV!=NULL)
             {
      //      ICPl_DEV->n_transaction=0;
              ICPl_DEV->n_timeout_error=0;
              ICPl_DEV->n_CRC_error=0;
             }
           }
        }
       else //PASS
       {
         pass_cnt++;
         if((pass_cnt & 0xf) == 0 )
           f_drv_stat_MMI(&mmi_str);
       }
       break;
 /*========================================*/
    case 24: // отображение сканирования порта
       if((key==ESC)||(key==ENTER))
       {
           goto m_m3_4; //  4  Другие функции
       }
       else //PASS
       {
          MmiGotoxy(0,3);  MmiPrintf("Опрошено   %3d",licp_addr);
          MmiGotoxy(0,4);  MmiPrintf("Обнаружено %3d",licp_fnd);
       }
       break;
 /*========================================*/
    case 25: // отображение аналоговых входов

       if((key==ESC)||(key==ENTER))
       {
           goto m0_f1;
       }
       else // PASS
       {
// MmiGotoxy(0,0); MmiPrintf(" Состояния аналоговых входов:");
// MmiGotoxy(0,1); MmiPrintf("       7017C/1 , мА");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625

   if( _fmemcmp( &ADC[0], &ADC_c[0], sizeof(ADC_c4)) != 0)
   {
   MmiGotoxy(0,2); MmiPrintf(" Давление     %8g (In%d)",(float)ADC[0],analog_num[0]-1);
   MmiGotoxy(0,3); MmiPrintf(" Температура  %8g (In%d)",(float)ADC[1],analog_num[1]-1);
    _fmemcpy( &ADC_c[0], &ADC[0], sizeof(ADC_c4));
   }
/*
   if( _fmemcmp( &ADC_c[4], &ADC[4], sizeof(ADC_c4)) != 0)
   {
    MmiGotoxy(0,3); MmiPrintf(" %6.2f %6.2f %6.2f %6.2f",(float)ADC[4],(float)ADC[5],(float)ADC[6],(float)ADC[7]);
    _fmemcpy( &ADC_c[4], &ADC[4], sizeof(ADC_c4));
   }
//  MmiGotoxy(0,4); MmiPrintf("       7017C/2 , мА");
*/
/*
   if( _fmemcmp( &ADC_c[8], &ADC[8], sizeof(ADC_c4)) != 0)
   {
    MmiGotoxy(0,5); MmiPrintf(" %6.2f %6.2f %6.2f %6.2f",(float)ADC[8], (float)ADC[9],(float)ADC[10],(float)ADC[11]);
    _fmemcpy( &ADC_c[8], &ADC[8], sizeof(ADC_c4));
   }
   if( _fmemcmp( &ADC_c[12], &ADC[12], sizeof(ADC_c4)) != 0)
   {
    MmiGotoxy(0,6); MmiPrintf(" %6.2f %6.2f %6.2f %6.2f",(float)ADC[12],(float)ADC[13],(float)ADC[14],(float)ADC[15]);
    _fmemcpy( &ADC_c[12], &ADC[12], sizeof(ADC_c4));
   }
*/
    if(INP_VAR != INP_VAR_c)
    {
     MmiGotoxy(24,5); MmiPuts(" ES=");
     if(INP_VARi & ES_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy(0,5); MmiPuts(" УЗА=");
     if(INP_VARi & UZA_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy( 7,5); MmiPuts("УРОВ.=");
     if(INP_VARi & LVL_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy(16,5); MmiPuts("СТАРТ=");
     if(INP_VARi & STRT_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy( 0,6); MmiPuts("ТРАП=");
     if(INP_VARi & TRAP_IN)
       MmiPuts("1");
     else
       MmiPuts("0");
     MmiGotoxy( 7,6); MmiPuts("КОНС.=");
     if(INP_VARi & CONS_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy(16,6); MmiPuts("СТОП =");
     if(INP_VARi & STOP_IN)
       MmiPuts("1");
     else
       MmiPuts("0");
    }
       }

       break;
 /*========================================*/
    case 26:/* ожидание нажатия ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
          goto m_main;
         }
         break;
 /*========================================*/
    case 27:/* ожидание нажатия ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
           goto m0_f1;
         }
         break;
 /*========================================*/
    case 28: // отображение дискретных выходов
       if((key==ESC)||(key==ENTER))
       {
           OUT_VAR=0;
           goto m0_f1;
       }
       else if(key== '1')
       {
        OUT_VAR ^= OUT1;
       }
       else if(key== '2')
       {
        OUT_VAR ^= OUT2;
       }
       else if(key== '3')
       {
        OUT_VAR ^= OUT3;
       }
       else if(key== '4')
       {
        OUT_VAR ^= OUT7;
       }
       else if(key== '5')
       {
        OUT_VAR ^= OUT5;
       }
       else if(key== '6')
       {
        OUT_VAR ^= OUT6;
       }
       else if(key== '7')
       {
        OUT_VAR ^= OUT8;
       }

       else // PASS
       {
         {
          MmiGotoxy(0,2);
  if(valve_mode==1)
      MmiPuts("Кл.Большой");
  else if(valve_mode==2)
      MmiPuts("Пилот НО  ");
  else if(valve_mode==3)
         MmiPuts("~Задв.закр");

          if(OUT_VAR & OUT1)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(16,2);
  if(valve_mode==1)
         MmiPuts("  Кл.Малый");
  else if(valve_mode==2)
         MmiPuts("  Пилот НЗ");
  else if(valve_mode==3)
      MmiPuts("Задв.откр ");

          if(OUT_VAR & OUT2)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");


          MmiGotoxy(3,3); MmiPuts("Насос  ");
          if(OUT_VAR & OUT3)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(0,4);
      MmiPuts(" Доз-р ");

          if(OUT_VAR & OUT7)
            MmiPuts(":1");
          else
            MmiPuts(":0");


          MmiGotoxy(12,4);
         MmiPuts("Кл.доз.");

          if(OUT_VAR & OUT5)
            MmiPuts(":1");
          else
            MmiPuts(":0");
/*
          MmiGotoxy(22,4);
         MmiPuts("Н.Д2");

          if(OUT_VAR & OUT6)
            MmiPuts(":1");
          else
            MmiPuts(":0");
*/


          MmiGotoxy(0,5); MmiPuts("MMI связь ");
          if(OUT_VAR & OUT8)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

         }

       }

       break;
 /*========================================*/
 /*========================================*/
    case 171://  1  Показания расходомера
         if((key==ESC)||(key==ENTER)  )
         {
          if((ff_serv==f_MVD_MM2)||(ff_serv==f_MVD_M2) ) ff_serv=NULL;
          goto m_m3_4;
         }
         else if(key== PASS )
         {
//        if ((ff_serv==NULL) && ( (flag_nal==0) || (fl_rd_err!=0) ) )
          if ((ff_serv==NULL) && ( (fl_rd_err!=0) ) )
          {
           fl_rd_err=0;
           sw_MMI_cur=0; // строка MMI
           sw_mvd_m1=mmi_prm+20;  // нач.параметр
           sw_MMI_lim=6; // конечная строка
           MMIDens=-1;
           MMITemp=-300;
           ff_serv=f_MVD_MM2;
          }
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=6)
           {
            mmi_prm -=6;
    //       printf("\n\rmmi_prm=%d",mmi_prm);
            goto m_m3_4_1v;
           }
           else
           {
            mmi_prm = 0;
            goto m_m3_4_1v;
           }
         else if (key== F3 )
         {
           if(mmi_prm <= (max_par-6))
           {
            mmi_prm +=6;
      //     printf("\n\rmmi_prm=%d",mmi_prm);
            goto m_m3_4_1v;
           }
         }
 /*========================================*/
         break;

    case 172://  2  Параметры расходомера
         if((key==ESC)||(key==ENTER)  )
         {
          if(ff_serv==f_MVD_M1) ff_serv=NULL;
          goto m_m3_4;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=6)
           {
            mmi_prm -=6;
            goto m_m3_4_2v;
           }
           else
           {
            mmi_prm = 0;
            goto m_m3_4_2v;
           }
         else if (key== F3 )
         {
           if(mmi_prm <= (max_par-6))
           {
            mmi_prm +=6;
            goto m_m3_4_2v;
           }
         }
 /*========================================*/
         break;
 /*========================================*/
    case 173:
         if((key==ESC)||(key==ENTER)  )
         {
          ff_serv=NULL;
          goto m_m3_4;
         }
         if(key==PASS  )
         {
          if(ff_serv==NULL)
          {
           SetDisplayPage(EmptPage);
           f_clr_scr_MMI();
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");
           sw_MMI_cur=0; // строка MMI
           sw_mvd_m1=mmi_prm+20;  // нач.параметр
           sw_MMI_lim=6; // конечная строка
           MMIDens=-1;
           MMITemp=-300;
           ff_serv=f_MVD_M2;
           sw_mmi=171;
          }
         }
         break;
 /*========================================*/
    case 174:
         if((key==ESC)||(key==ENTER)  )
         {
          ff_serv=NULL;
          goto m_m3_4;
         }
         if(key==PASS  )
         {
          if(ff_serv==NULL)
          {
           SetDisplayPage(EmptPage);
           f_clr_scr_MMI();
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");
           sw_MMI_cur=0; // строка MMI
           sw_mvd_m1=mmi_prm+20;  // нач.параметр
           sw_MMI_lim=6; // конечная строка

           ff_serv=f_MVD_M1;
           sw_mmi=172;
          }
         }
         break;
 /*========================================*/
    case 180:

       if((key==ESC)||(key==ENTER))  /* переход на начальную страницу */
       {
         if(ff_serv==f_MVD_M3) ff_serv=NULL;
            goto m_m3_4;
       }
       break;
 /*========================================*/
    case 190: //  1  Отпуск нефтепродуктов

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           goto main_menu;
       }

       else if((key== '1') && (id_ok !=0) && (mode_hst == 0) )  // 1  Отпуск дозы
       {
m_m5_1:

          if((WD_PMP_Fl != 0) && (flag_Slv == 2)) break;

         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);       MmiPuts("   Отпуск дозы ");
         f_prn_MassSt_dlv();

         MmiGotoxy(0,2);
          if ( Flag_mass != 0 )
             MmiPuts(" Введите дозу отпуска,кг");
          else
             MmiPuts(" Введите дозу отпуска,л ");

         MmiGotoxy(0,6); MmiPuts(" Enter - ввод данных  ");

      // sprintf( fst_str,"");
         strcpy( fst_str,"");
         fst_n=5;
         sw_fst=1;
         MmiGotoxy(10,4);
         break;
       }
       else if(key==DATA)
        {
          dose_dlvr=-1;
          sscanf(fst_str,"%f",&dose_dlvr);
          if(dose_dlvr<=0) { dose_dlvr=0; goto m_m5_1;}
//          else if(dose_dlvr > 10000) {dose_dlvr=10000; goto m_m5_1;}
         flag_dlv_fst=0;
         flag_prn_mass=0;

m_m5_1o:
          flag_rcv=0;

         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
   //      MmiGotoxy(0,0);       MmiPuts("Отпуск жидкой фазы.      ");
          MmiGotoxy(0,0);
          if(dose_dlvr != vBIG_P)
          {
            if ( Flag_mass != 0 )
              MmiPrintf(" Отпуск дозы %g кг",dose_dlvr);
            else
              MmiPrintf(" Отпуск дозы %g л ",dose_dlvr);
          }
          else
             MmiPrintf(" Отпуск без дозировки");

         MmiGotoxy(0,6);       MmiPuts("ESC - завершить.");

         sw_dlv_liq=1;
         sw_mmi=193;
m_m5_1d:
/*==========
          MmiGotoxy(0,2);      MmiPuts("  Масса        |  Отпущено");
                //             MmiPuts("xxxxx.xx кг    | xxxxx.xx кг");
          MmiGotoxy(0,3);
          if(flag_prn_mass)   MmiPrintf("%8.2f кг    | %8.2f кг   ",s_MVD[0].MassI,s_MVD[0].MassT);  // VolT_id, VolT_int
          else  MmiPrintf("%8.2f кг    | %8.2f кг   ",s_MVD[0].MassI,(float)0.);  // VolT_id, VolT_int
===========*/
          if(NN_resv != 0)
          {

#if((Add_pmp == 0) || (Add_pmp == 1))
            MmiGotoxy(0,2);  MmiPrintf("АСН %d. %s,Отпущено",Adr_ASN,list_md_add[N_resv]);
#endif

#if(Add_pmp == 2)
            MmiGotoxy(0,2);  MmiPrintf("АСН %d. Рез.N%d, Отпущено",Adr_ASN,N_resv_dsp[N_resv]);
#endif


          }

          else
          {
            MmiGotoxy(0,2);      MmiPrintf("АСН %d.    Отпущено          ",Adr_ASN);
          }

//        MmiGotoxy(0,2);      MmiPuts("  M,кг   --Отпущено-- V,л    ");
//        MmiGotoxy(0,2);      MmiPuts("  Масса        |  Отпущено");
                //             MmiPuts("xxxxx.xx кг    | xxxxx.xx кг");
          MmiGotoxy(0,3);
          if(flag_prn_mass)   MmiPrintf("М=%9.2f кг |О= %9.2f л  ",s_MVD[0].MassT,s_MVD[0].VolT);  // VolT_id, VolT_int
          else                MmiPrintf("М=%9.2f кг |О= %9.2f л  ",(float)0.,(float)0.);  // VolT_id, VolT_int

m_m5_1e:
          f_prn_proc();
          break;
        }
       else if(key==DATA_ESC)
        {
          goto m_m5;
        }
//     else if(key== '2')  // 2  Отпуск до опорожнения
       else if((key== '2') && (id_ok !=0) && (mode_hst == 0) )
       {
m_m5_2:

         if((WD_PMP_Fl != 0) && (flag_Slv == 2)) break;

         dose_dlvr=vBIG_P;
         flag_dlv_fst=0;
         flag_prn_mass=0;
         goto m_m5_1o;
       }
//     else if(key== '3')  // 3 Продолжить с задан. дозой
       else if((key== '3') && (id_ok !=0) && (mode_hst == 0) )
       {

        if((WD_PMP_Fl != 0) && (flag_Slv == 2)) break;


         if(flag_prn_mass)
          {
           goto m_m5_1o;
          }
       }

       else if(key== '4' )//  4  Коррекция параметров начального наполнения
       {
m_m5_4:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts("Парам.Начального Наполнения ");
            MmiGotoxy(0,1);    MmiPuts("1 Изменить начальный объем ");
            MoveToXY(0,4);   MmiPrintf("Начальный объем :%6.0f л",Vol_beg);
       if(valve_mode != 1)
       {
            MmiGotoxy(0,2);    MmiPuts("2 Изменить начальный расход ");
            MoveToXY(0,5);   MmiPrintf("Начальный расход:%6ld кг/ч",Flow_beg);
       }
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");

         sw_mmi=126;
         break;
       }

       else  if(mode_hst == 0 )
          f_prn_MassSt_dlv();

       break;
 /*========================================*/
//===========================================
    case 193: //  Отпуск
       if(key==F2)    // индикация Давление,Температура
       {
           PageD=0;
       }
       else if(key==F3)    // индикация Плотность,Состав
       {
           PageD=1;
       }
       else if(key=='1')    // индикация выходов
       {
           PageD=3;
       }

       key=f_dlv_liq(key);
       if(key==ESC)    // переход в меню
       {
        if(mode_hst == 0)   goto m_m5;
        else
        {
         sw_mmi=0;
         break;
        }
       }
  // отображение общей и отпущенной массы
       goto m_m5_1d;

 /*========================================*/
 /*========================================*/
       default:
       if((key==ESC)||(key==ENTER))  /* переход на начальную страницу */
       {
 m_main:
           SetDisplayPage(ZeroPage);
           sw_mmi=0;
           f_clr_scr_MMI();
           f_prn_begin();
           break;
       }
       break;
    }
    return 0;
}
/*-----------------------------------------*/
int flag_Slv_c=0;
void f_before_MMI()
{
    flag_Slv_c=flag_Slv;
    ftmp_naMMI[0]=analog_scale[0]*NA_scale;
    ftmp_naMMI[1]=analog_scale[1]*NA_scale;
    ftmp_DP=((float)P_dem) / K_F_INT;
    ftmp_LP=(float)LIM_P /k_div;

}
/*-----------------------------------------*/
void f_after_MMI()
{
int i;
    analog_scale[0]=ftmp_naMMI[0]/NA_scale;
    analog_scale[1]=ftmp_naMMI[1]/NA_scale;
    P_dem = (long int)(ftmp_DP * K_F_INT);

    LIM_P =(long int)ftmp_LP  * k_div;

    f_init_mki();
    f_count_cf();

  P_addr=AddrSlv-1;
  if(P_addr < 0) P_addr=0;

    if(flag_Slv_c != flag_Slv)
    {
        flag_Slv_c=flag_Slv;

        if(flag_Slv == 2)
        {
           RestoreCom(ComPortPmp1);
           InstallCom(ComPortPmp1,ComBaudPmp1,Com_lgthPmp1,Com_parityPmp1,Com_stopPmp1);
           ShowCom(ComPortPmp1,Com_lgthPmp1,ComBaudPmp1);
        }
        else if(flag_Slv==1)
        {
          RestoreCom(ComPortSlv);
         if(f_get_nb(ComBaudSlv) <0 ) ComBaudSlv=9600L;
         InstallCom(ComPortSlv,ComBaudSlv,Com_lgthSlv,Com_paritySlv,Com_stopSlv);
         ShowCom(ComPortSlv,Com_lgthSlv,ComBaudSlv);
        }
        else
        {
           RestoreCom( ComPortHost );
           i=ComPortHost;
           InstallCom(i,ComBaud[i],Com_lgth[i],Com_parity[i],Com_stop[i]);
           ShowCom(ComPortHost,Com_lgth[i],ComBaud[i]);
           flag_wdp=0;
        }
    }
}

