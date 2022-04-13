//  MMI_NEW

//#define ZeroPage 0
//#define ZeroPage 6

//02.02.2022 YN
#if defined(GAZAVOZ)
int WHOLE = 1;
float beginValue = 12345.0; // �
float beginMassa = 12345.0; // ��
int fillingFlag = 0;

//16.02.2022 YN
extern int flagFirstTurnOn;
#endif
//   f_reg_cmn(0);

int n_pp=0;
int n_ASN=0;

//27.10.2021 YN
#if defined(N_Pipes)
int n_pipe_l=0;
int n_pipe_h=0;
#endif

#if defined(MMI_NEW)

#define d_F2 (4)
#define n_mmi_str 16 // ���������� ����� �� ������� MMI
#endif

#if defined(MMI_ICP)
#define d_F2 (2)
#define n_mmi_str 7 // ���������� ����� �� ������� MMI
#endif


#define n_mmi_str_1 (n_mmi_str-1)
#define n_mmi_str_2 (n_mmi_str-2)
#define n_mmi_str_3 (n_mmi_str-3)
#define n_mmi_str_4 (n_mmi_str-4)
float ftmp_DP=1;
int mode_hst = 0;
//
//  ���� �������� ���������� ������ � DOS ��������� ��������.
//  ��� ����������� �� ������� MMI ���������� �������������� �
//  ��������� Windows (����������� �������� dos_win.exe � .bat)
//

char str_prod[22]=" -------- ";
char str_dsp1[31]="";
char str_dsp2[31]="";
char str_dsp3[31]="";
char str_dsp4[31]="";
char str_dsp5[31]="";
char str_dsp6[31]="";
char str_dsp7[31]="";

int type_dlv=0;
int sect_num=0;
int sect_mass=0;
int sect_vol=0;
int sect_rslt=0;

float MassStamp=-1000.;
float VolStamp=-1000.;

float vBIG_P=BIG_P;
long int tm_md=0;

int flag_prok=0;
char mode_prok[9] ="������";
char otpusk[9]  ="������  ";
char  prok_ka[9]   ="��������";
char str_empt[]="                               ";

//08.02.2022 YN
#if(Shtray==2)
  #define Time_zeroing (70000) //PROMASS
  char str_x_shtray[]="������� ��������� ������:";
  char str_x_0[]="������� ��������� �����:";
  float sdv_m_flow=1.0, sdv_v_flow=1.0, sdv_dens=1.0;
#endif


long int fl_zeroing=0;

//08.02.2022 YN
#if(Shtray!=2)
  #define Time_zeroing (50000)
#endif

long int zero_time;

char s_empty[]="                              ";
char str_ESC[]="ESC  �������";

void f_d_ESC()
{
  MmiGotoxy(0,15); MmiPuts(str_ESC);
}

int PageD=0;
int flg_ch=0;
int Flag_f_corr=0,flag_mass=0,pass_ret=0;
float k_v_flow=1,k_m_flow=1;
float k_dens=1.;

float k_mv_tmp;
long int pass1=0,pass2=0;

#if defined(BIO_1)
  float P_inp=0;
#endif

long int n_id_a=0;

void f_prn_ID();
int flag_esc=1;
void  f_prn_begin()
{
  if(flag_esc == 0) goto m1;

  if( id_ok==0) f_prn_ID();
  else if(CRC_err) f_prn_CRC_error();
  else if(FL_err) f_prn_error();
  else
  {
 m1:
    f_clr_scr_MMI();
            //  MmiPrintf("                              ");

#if defined(MMI_NEW)

  //27.10.2021 YN
  #if defined(N_Pipes)
    if(valve_mode && valve_modeL) 
    {
      MmiGotoxy(0,0);  MmiPrintf("��� %d-%d-%d.",n_ASN,n_pipe_h,n_pipe_l);
    }
    else if(valve_mode==0)
    {
      MmiGotoxy(0,0);  MmiPrintf("��� %d-%d.",n_ASN,n_pipe_l);
    }
    else
    {
      MmiGotoxy(0,0);  MmiPrintf("��� %d-%d.",n_ASN,n_pipe_h);
    }
  #else

    //02.02.2022 YN
    #if defined(GAZAVOZ)
      MmiGotoxy(0,0); MmiPrintf("    ��� ����� �����������     ");
    #else
      MmiGotoxy(0,0);  MmiPrintf("��� %d.",n_ASN);
    #endif

  #endif

  //02.02.2022 YN
  #if defined(GAZAVOZ)
    MmiGotoxy(1,2);   MmiPrintf("    ������� ����� �������     ");
    MmiGotoxy(1,3);   MmiPrintf("     ��� �� ������������      ");
  #else
    MmiGotoxy(1,1);  MmiPrintf("  ������� ����� �������  ");
    MmiGotoxy(1,2);  MmiPrintf("     �������������� ");
  #endif

  MmiGotoxy(17,14);  MmiPrintf(" ESC - ���� ");

#endif


#if defined(MMI_ICP)
  MmiGotoxy(1,1);  MmiPrintf("  ������� ����� �������  ");
  MmiGotoxy(1,2);  MmiPrintf("  ��������������.��� %d. ",n_ASN);
#endif



            //             "  ��������� ��������          "

#if defined(BIO_1)
          if(PageD==0)
          {
  MmiGotoxy(0,3) ; MmiPrintf("�����       :                ");
  MmiGotoxy(0,4) ; MmiPrintf("�����       :                ");
  MmiGotoxy(0,5) ; MmiPrintf("P�� =            ");
  MmiGotoxy(15,5); MmiPrintf("P���=            ");
          }
#else
          if(PageD==0)
          {
//MmiGotoxy(0,3) ; MmiPrintf("�����       :                ");
//MmiGotoxy(0,4) ; MmiPrintf("�����       :                ");
//MmiGotoxy(0,5) ; MmiPrintf("P=            ");
//MmiGotoxy(15,5); MmiPrintf("T=            ");
          }



#endif

          else if(PageD==1)
          {


          }
          else
          {
  MmiGotoxy(0,3) ; MmiPrintf("PageD = %d",PageD);

          }

  }
}
//-------------------------------------
void f_prn_ID()
{
    f_clr_scr_MMI();
            //  MmiPrintf("                              ");

#if defined(BIO_1)
  MmiGotoxy(1,1);  MmiPrintf("  ������� ����� �������  ");
  MmiGotoxy(1,2);  MmiPrintf("      �������������      ");
#else
  //02.02.2022 YN
  #if defined(GAZAVOZ)
    MmiGotoxy(1,2);   MmiPrintf("    ������� ����� �������     ");
    MmiGotoxy(1,3);   MmiPrintf("     ��� �� ������������      ");
  #else
    MmiGotoxy(1,1);  MmiPrintf("  ������� ����� �������  ");
    MmiGotoxy(1,2);  MmiPrintf("      ��������������     ");
  #endif
#endif


  MmiGotoxy(0,3) ; MmiPrintf("!�� ��������� ID=%ld ",n_id);
  MmiGotoxy(0,4) ; MmiPrintf(" SN %08lX %08lX",*( unsigned long int *)(ID_ADDR),*( unsigned long int *)(ID_ADDR+4) );
  MmiGotoxy(0,5) ; MmiPrintf("���������� � ���������� �� ID ");
  MmiGotoxy(0,6) ; MmiPrintf(" F2 - ���� ID ");
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
            //30.09.2021 YN was: MmiPrintf(" ������  %g ��",dose_dlvr);
            MmiPrintf("���%d ������  %g ��",n_ASN,dose_dlvr);
          else
            //30.09.2021 YN was: MmiPrintf(" ������  %g � ",dose_dlvr);
            MmiPrintf("���%d ������  %g � ",n_ASN,dose_dlvr);
         }
        else
        {
          //30.09.2021 YN was: MmiPrintf(" ������ ��� ����");
          MmiPrintf("���%d ������ ��� ����", n_ASN);
        }

       f_prn_mode();
       MmiGotoxy(0,6);  MmiPuts("ESC - ����");

}
//-------------------------------------

//--------------------
void f_prn_no_sig_L( int row)
{
int i;

    if(valve_modeL == 0) return;
    if( (INP_VARi0  & INP_MSK_OK_L) == INP_MSK_OK_L ) return;

  MmiGotoxy(0,row); MmiPuts( str_empt );

  MmiGotoxy(0,row);
    if( valve_mode != 0)
    {
      MmiPuts("����. ���:");
      i=10;
    }
    else
    {
          MmiPuts("���:");
      i=4;
    }

              if( LVL_IN_L==0)
              {
                MmiGotoxy(i,row); MmiPuts(" �������");
               i+=9;

               if(INP_OFP & 0x4000)
                {
                i+=2;
                MmiPuts(" ");
 if((INP_OFP & 1)==0){ MmiPuts("1"); i++; }
 if((INP_OFP & 2)==0){ MmiPuts("2"); i++; }
 if((INP_OFP & 4)==0){ MmiPuts("3"); i++; }
 if((INP_OFP & 8)==0){ MmiPuts("4"); i++; }
 if((INP_OFP & 0x10)==0){ MmiPuts("5"); i++; }
 if((INP_OFP & 0x20)==0){ MmiPuts("6"); i++; }
 if((INP_OFP & 0x100)==0){ MmiPuts("7"); i++; }
 if((INP_OFP & 0x200)==0){ MmiPuts("8"); i++; }
                MmiPuts(" ");
                }
              }
              if( UZA_IN_L==0)
              {
               if((i+4)< 30)
                {
                 MmiGotoxy(i,row); MmiPuts(" ���");
                 i+=4;
                }
              }

              //11.06.2021 YN
              #if defined(PresenceLiquid)
              if( FILTER_FULL==0)
              {
               if((i+8)< 30)
                {
                 MmiGotoxy(i,row); MmiPuts(" �-�����");
                 i+=8;
                }
              }
              #endif

    if( valve_mode != 0)
    {
              if( ES_IN_L==0)
              {
               if((i+11)< 30)
               {
                MmiGotoxy(i,row); MmiPuts(" ��.��.����");
                 i+=11;
               }
              }

          if( Flag_Low != 0)
              if( ES_IN==0)
              {
               if((i+12)< 30)
               {
                MmiGotoxy(i,row); MmiPuts(" ��.��.�����");
                 i+=12;
               }
              }
    }
    else
    {
              if( ES_IN_L==0)
              {
               if((i+12)< 30)
               {
                MmiGotoxy(i,row); MmiPuts(" ����.������");
                 i+=12;
               }
              }
    }


}
//--------------------
void f_prn_no_sig_H( int row)
{
int i;

    if( valve_mode == 0) return;

    if( (INP_VARi0  & INP_MSK_OK) == INP_MSK_OK ) return;


     MmiGotoxy(0,row); MmiPuts( str_empt );
              MmiGotoxy(0,row);


    if( valve_modeL != 0)
    {
      MmiPuts("�����.���:");
      i=10;
    }
    else
    {
      MmiPuts("���:");
      i=4;
    }

              if( TRAP_IN==0)
              {
               if((i+5)< 30)
               {
                 MmiGotoxy(i,row); MmiPuts(" ����");
                 i+=5;
               }
              }

              if( CONS_IN==0)
              {
               if((i+8)< 30)
               {
                 MmiGotoxy(i,row); MmiPuts(" �������");
                 i+=8;
               }
              }

              if( LVL_IN==0)
              {
               if((i+8)< 30)
               {
                MmiGotoxy(i,row); MmiPuts(" �������");
                i+=8;
               }
              }
              if( UZA_IN==0)
              {
               if((i+4)< 30)
               {
                MmiGotoxy(i,row); MmiPuts(" ���");
                i+=4;
               }
              }

              //11.06.2021 YN
              #if defined(PresenceLiquid)
              if( FILTER_FULL==0)
              {
               if((i+8)< 30)
                {
                 MmiGotoxy(i,row); MmiPuts(" �-�����");
                 i+=8;
                }
              }   
              #endif

    if( valve_modeL != 0)
    {
              if( ES_IN==0)
              {
               if((i+12)< 30)
               {
                MmiGotoxy(i,row); MmiPuts(" ��.��.�����");
                 i+=12;
               }
              }

          if( Flag_Low == 0)
              if( ES_IN_L==0)
              {
               if((i+11)< 30)
               {
                MmiGotoxy(i,row); MmiPuts(" ��.��.����");
                 i+=11;
               }
              }
    }
    else
    {
              if( ES_IN==0)
              {
               if((i+12)< 30)
               {
                MmiGotoxy(i,row); MmiPuts(" ����.������");
                 i+=12;
               }
              }
    }
}
//--------------------
//-------------------------------------
int un_mmi1=1;
int un_mmi2=2;
int un_mmi3=3;
char *list_un_mmi[]={
"",
" �����,�   " ,  //1
"�����,���  " ,  //2
"����,���/� " ,  //3
"�����,��   " ,  //4
"�����,���  " ,  //5
"����,���/��" ,  //6
};
//-------------------------------------
int CRC_err=0;
//-------------------------------------
void f_prn_CRC_error()
{
 MmiGotoxy(0,0);  MmiPrintf("��� %d.",n_ASN);
 MmiGotoxy(0,2);   MmiPrintf("!������ ����������� �����   ");
 MmiGotoxy(0,3);   MmiPrintf("!��������� ��������         ");
 MmiGotoxy(0,4);   MmiPrintf("!���������� �������������   ");
 MmiGotoxy(0,5);   MmiPuts(s_empty);
 CRC_err=1;
}
//-------------------------------------
void f_prn_mode()
{
   if((valve_mode != 0) && (valve_modeL != 0))
   {
      if( Flag_Low == 0)
      {
        MmiGotoxy(22,0);

        //27.10.2021 YN
        #if defined(N_Pipes)
          MmiPrintf(" ����-%d        ",n_pipe_h);
        #else
          MmiPuts(" �������        ");
        #endif

      }
      else if( Flag_Low == 1)
      {
        MmiGotoxy(22,0);

        //27.10.2021 YN
        #if defined(N_Pipes)
          MmiPrintf(" ����-%d         ",n_pipe_l);
        #else
          MmiPuts(" ������         ");
        #endif

      }
   }

   //27.10.2021 YN
   #if defined(N_Pipes)
    else if(valve_mode)
    {
      MmiGotoxy(22,0);
      MmiPrintf(" ����-%d        ",n_pipe_h);
    }
    else
    {
      MmiGotoxy(22,0);
      MmiPrintf(" ����-%d         ",n_pipe_l);
    }
   #endif

}
//-------------------------------------
void f_prn_proc()
{
 float V_tmp;


          if(PageD==0)
          {
            {


#if !defined(BIO_1)

              if( flag_AD != 0)
              {
                MmiGotoxy(0,8);  MmiPrintf("�����.������� %7.2f ��/�3   ",Dens_a);

                //18.11.2021 YN
                #if defined(weightedAverageTemperature)
                  if( waTempOn ) 
                  {
                    if(s_MVD[0].MassT != 0)
                    {
                      MmiGotoxy(0,9 ); MmiPrintf("����.�������  %7.2f C       ", (waTemp/s_MVD[0].MassT) );
                    }
                    else
                    {
                      if ((mode_temp==EXT) && (s_MVD[0].TempR > -49.5) )
                      {
                        MmiGotoxy(0,9); MmiPrintf("�����������   %7.2f C        ",s_MVD[0].TempR);
                      }
                      else
                      {
                        //02.02.2022 YN
                        #if defined(GAZAVOZ)
                          MmiGotoxy(0,9); MmiPrintf("�����������    %7.2f C        ",s_MVD[0].Temp);
                        #else
                          MmiGotoxy(0,9); MmiPrintf("������.MVD    %7.2f C        ",s_MVD[0].Temp);
                        #endif
                      }
                    }
                  }
                  else 
                  {
                    MmiGotoxy(0,9 ); MmiPrintf("����.�������  %7.2f C       ",Temp_a);
                  }
                #else
                  MmiGotoxy(0,9 ); MmiPrintf("����.�������  %7.2f C       ",Temp_a);
                #endif

                MmiGotoxy(0,10); MmiPuts( str_empt );
                MmiGotoxy(0,11); MmiPuts( str_empt );

                //02.02.2022 YN
                #if !defined(GAZAVOZ)
                  MmiGotoxy(0,12); MmiPrintf("��������     %8.3f ���     ",s_MVD[0].Press);
                #endif
              }
              else
#endif
              {

                MmiGotoxy(0,8);  MmiPrintf("���������     %7.2f ��/�3   ",s_MVD[0].Dens);

                if ((mode_temp==EXT) && (s_MVD[0].TempR > -49.5) )
                {
                MmiGotoxy(0,9); MmiPrintf("�����������   %7.2f C        ",s_MVD[0].TempR);
                }
                else
                {
                  //02.02.2022 YN
                  #if defined(GAZAVOZ)
                    MmiGotoxy(0,9); MmiPrintf("�����������    %7.2f C        ",s_MVD[0].Temp);
                  #else
                    MmiGotoxy(0,9); MmiPrintf("������.MVD    %7.2f C        ",s_MVD[0].Temp);
                  #endif

                }


                MmiGotoxy(0,11); MmiPrintf("������       %8.1f �/�       ",s_MVD[0].FlowV);

                //22.02.2022 YN
                if(OUT_VAR & OUT2)
                {
                  MmiGotoxy(0,13); MmiPrintf("��������� �������:   ������  ");
                }
                else
                {
                  MmiGotoxy(0,13); MmiPrintf("��������� �������:   ������  ");
                }

                //02.02.2022 YN
                #if !defined(GAZAVOZ)
                  MmiGotoxy(0,12); MmiPrintf("��������     %8.3f ���       ",s_MVD[0].Press);
                #endif

                //27.09.2021 YN
                #if (PressureDrop == 1)
                  MmiGotoxy(0,13);  MmiPrintf("�������      %8.3f ���       ",Press_Drop);
                #elif (PressureDrop == 2)
                  MmiGotoxy(0,13);  MmiPrintf("�������      %8.3f ���       ",P_diff);
                #endif
              }
            }
          }
          else if(PageD==1)
          {
              MmiGotoxy(0,8);  MmiPuts(" ��15,��/�3|�����15,�|����,���");
              MmiGotoxy(0,9);
              if(flag_prn_mass != 0)
                V_tmp=V_ref;
              else
                V_tmp=0.;
              if(D_ref< 400)
                MmiPrintf(" --------  | ------- | %8.3f ",s_MVD[0].Press);
              else
                MmiPrintf(" %8.2f  |%8.2f | %8.3f ",D_ref,V_tmp,s_MVD[0].Press);
                MmiGotoxy(0,11); MmiPuts( str_empt );
                MmiGotoxy(0,12); MmiPuts( str_empt );
          }
          else if(PageD==3)
          {


if( Flag_Low == 0)
{

   MmiGotoxy(0,8);
  if(valve_mode==1)      MmiPuts("����.���.�.:");
  else if(valve_mode==2) MmiPuts("����� ��.�.:");
  else if(valve_mode==3) MmiPuts("��.����.�.:");

     if( OUT_VAR & OUT2  )
       MmiPuts("1       ");
     else
       MmiPuts("0       ");
     MmiGotoxy( 0,9);
  if(valve_mode==1)      MmiPuts("����.���.�.:");
  else if(valve_mode==2) MmiPuts("����� ��.�.:");
  else if(valve_mode==3) MmiPuts("��.����.�.:");
     if( OUT_VAR & OUT1  )
       MmiPuts("1       ");
     else
       MmiPuts("0       ");
}
else if( Flag_Low == 1)
{
   MmiGotoxy(0,8);
  if(valve_modeL==1)      MmiPuts("����.���.�.:");
  else if(valve_modeL==2) MmiPuts("����� ��.�.:");
  else if(valve_modeL==3) MmiPuts("��.����.�.:");

     if( OUT_VAR & OUT6  )
       MmiPuts("1       ");
     else
       MmiPuts("0       ");

     MmiGotoxy( 0, 9);
  if(valve_modeL==1)      MmiPuts("����.���.�.:");
  else if(valve_modeL==2) MmiPuts("����� ��.�.:");
  else if(valve_modeL==3) MmiPuts("��.����.�.:");
     if( OUT_VAR & OUT5  )
       MmiPuts("1       ");
     else
       MmiPuts("0       ");

}

     MmiGotoxy(15,8);
#if(AIR_SW != 0)
                  MmiPuts("������  :");
#endif
#if(CUT_SW != 0)
                  MmiPuts("������� :");
#endif
     if( OUT_VAR & OUT4  )
       MmiPuts("1  ");
     else
       MmiPuts("0  ");



     MmiGotoxy(26,8);   MmiPuts("�:");
     if( OUT_VAR & OUT3  )
       MmiPuts("1      ");
     else
       MmiPuts("0      ");

     MmiGotoxy(15,9 );   MmiPuts("������. :");
     if( OUT_VAR & OUT8  )
       MmiPuts("1      ");
     else
       MmiPuts("0      ");

                MmiGotoxy(0,11); MmiPuts( str_empt );
                MmiGotoxy(0,12); MmiPuts( str_empt );
          }

}
//-------------------------------------
void f_prn_MassSt_dlv()
{
  MmiGotoxy(0,2);
         MmiPrintf("����� %7.1f ��, %7.1f �  ",s_MVD[0].MassI-MassStamp,s_MVD[0].VolI-VolStamp);
/*
  if ( Flag_mass != 0 )
    MmiPrintf("  ����� �������� %8.2f ��  ",s_MVD[0].MassI-MassStamp);
  else
    MmiPrintf("  ����� �������� %8.2f �   ",s_MVD[0].VolI-VolStamp);
 */
}
//-------------------------------------
/*
void f_prn_MassSt_rcv()
{
  MmiGotoxy(0,1);
  if ( Flag_mass != 0 )
    MmiPrintf("   ����� ������� %8.2f ��  ",s_MVD[0].MassI-MassStamp);
  else
    MmiPrintf("   ����� ������� %8.2f �   ",s_MVD[0].VolI-VolStamp);
}
*/
//-------------------------------------
void f_prn_error()
{
   f_clr_scr_MMI();

    //02.02.2022 YN
    #if !defined(GAZAVOZ)
      MmiGotoxy(0,0);  MmiPrintf("��� %d.",n_ASN);
    #endif

#if( Test == 0)
   if(flag_mvd_ton)
   {
#if defined(BIO_1)
  MmiGotoxy(1,1);  MmiPrintf("  ������� ����� �������  ");
  MmiGotoxy(1,2);  MmiPrintf("      �������������      ");
#else
  //02.02.2022 YN
  #if defined(GAZAVOZ)
    MmiGotoxy(1,2);   MmiPrintf("    ������� ����� �������     ");
    MmiGotoxy(1,3);   MmiPrintf("     ��� �� ������������      ");
  #else
    MmiGotoxy(1,1);  MmiPrintf("  ������� ����� �������  ");
    MmiGotoxy(1,2);  MmiPrintf("      ��������������     ");
  #endif
#endif

  //02.02.2022 YN
  #if !defined(GAZAVOZ)
    MmiGotoxy(0,3);  MmiPuts(s_empty);
  #endif
    MmiGotoxy(0,8);  MmiPrintf("  !������������� ����������� ");
    MmiGotoxy(0,5);  MmiPuts(s_empty);
   }
   else
#endif
   {
//  MmiGotoxy(0,1);   MmiPrintf("                        ");
    MmiGotoxy(0,5);   MmiPrintf("!������ ���������������� ");
    MmiGotoxy(0,7);   MmiPrintf("Sht-F1 ����������� ������");
    MmiGotoxy(0,9);   MmiPrintf("Sht-ESC ������� ������   ");
   }
}
//-------------------------------------
void  f_disp_error()
{ // ������������� ������

 struct s_icp_dev *ICPl_DEV;
int i,i1,i2;
unsigned int itmp;
  MmiGotoxy(0,0);  MmiPrintf("��� %d.",n_ASN);
   i1=1;
   i2=0;
 for(i=0;i<=icp_lst_max;i++)
   if(ICP_error[i])
   {
    i2++;
    ICPl_DEV=ICP_dd[i];
  if(i != icp_lst_max)
  {
 MmiGotoxy(0,i1++);   MmiPrintf("������ � �������� %9s:",ICPl_DEV->name );
  }
  else
  {
 MmiGotoxy(0,i1++);   MmiPrintf("������ ������� �����:           ");
  }
    if(i1 >= n_mmi_str) return;
    itmp=ICP_error[i];
  if(i != icp_lst_max)
  {
    if(itmp & RD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ������ ����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WR_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ������ � ����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ Watch Dog");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Drive_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ � ����������,%02X", (itmp>>8) & 0xff);
    if(i1 >= n_mmi_str) return;
    }

  }
  else //(i == icp_lst_max)
  {
    if(itmp == No_Src )
    {
MmiGotoxy(0,i1++); MmiPrintf("�� ����� �������� ��������");
//  if(i1 >= n_mmi_str) return;
      return;
    }
    if(itmp == Err_Key )
    {
MmiGotoxy(0,i1++); MmiPrintf("��.������� � ���������� ���");
//  if(i1 >= n_mmi_str) return;
      return;
    }
    if( (itmp & OPN_H ) == OPN_H )
    {
MmiGotoxy(0,i1++); MmiPrintf("�� ������� ����.�����.������");
//  if(i1 >= n_mmi_str) return;
      return;
    }
    if( (itmp & OPN_L ) == OPN_L )
    {
MmiGotoxy(0,i1++); MmiPrintf("�� ������� ����.����.������");
//  if(i1 >= n_mmi_str) return;
      return;
    }
    if(itmp == EEE_CRC_error)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ CRC EEPROM ����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_erase_error )
    {
MmiGotoxy(0,i1++); MmiPrintf("������ �������� FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_wr_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ������ �� FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_gas_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("���������� �� ��������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_Z_mass_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("����-� �� ������� �����");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_F_dat_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("��� ������.������ ��� �������");
    if(i1 >= n_mmi_str) return;
    }

    if(itmp & DNS_not_off)
    {
      //23.02.2022 YN 
      //MmiGotoxy(0,i1++); MmiPrintf("������ ��� ������ ");
      MmiGotoxy(0,i1++); MmiPrintf(" ������ ��������� ��� ������� ");
    if(i1 >= n_mmi_str) return;
    }

    if(itmp & DNS_st)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ��� ����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_Press)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ �������� ��� ������ ");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Gun_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("����� �������� ��� �������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == WD_host)
    {
MmiGotoxy(0,i1++); MmiPrintf("��� ����� � HOST");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == No_flow )
    {
MmiGotoxy(0,i1++); MmiPrintf("����� �����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & ES_off )
    {
//MmiGotoxy(0,i1++); MmiPrintf("������ ES ��� �������");
MmiGotoxy(0,i1++); MmiPrintf("��� ���������� �� �����");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & UZA_off )
    {
     switch (flagE_UZA)
     {
      case UZA_E:
MmiGotoxy(0,i1++); MmiPrintf("��� ��� ��� �������");
        if(i1 >= n_mmi_str) return;
        break;
      case LVL_E:
MmiGotoxy(0,i1++); MmiPrintf("��������� ���������� �������");
        if(i1 >= n_mmi_str) return;
        break;
      case ID_E:
MmiGotoxy(0,i1++); MmiPrintf("������������ ID ");
        if(i1 >= n_mmi_str) return;
        break;
      case TRAP_E:
MmiGotoxy(0,i1++); MmiPrintf("���� �� � ���.������� ");
        if(i1 >= n_mmi_str) return;
        break;
      case CONS_E:
MmiGotoxy(0,i1++); MmiPrintf("������� �� � ���.������� ");
        if(i1 >= n_mmi_str) return;
        break;

//11.06.2021 
#if defined(PresenceLiquid)
      case FILTER:
MmiGotoxy(0,i1++); MmiPrintf("   ������� �� ���������  ");
        if(i1 >= n_mmi_str) return;
        break;
#endif
        
     }
    }
    if(itmp & MVD_cfg )
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ����.������-�� ");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == MotNotStop )
    {
MmiGotoxy(0,i1++); MmiPrintf("���� ������ ��� ����.");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == DLT_off)
    {
MmiGotoxy(0,i1++); MmiPrintf("����� ����. ��� �������");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & MVD_com)== MVD_com )
    {
MmiGotoxy(0,i1++); MmiPrintf("��� ����� � ������.");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & Hst_alm)==Hst_alm)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ �� Host");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & No_Drv)==No_Drv)
    {
MmiGotoxy(0,i1++); MmiPrintf("�������� MVD,7041 �� ��������");
    if(i1 >= n_mmi_str) return;
    }
  }
   }
   if(i2==0)
   {
    MmiGotoxy(5,2); MmiPrintf("������ ���");
    MmiGotoxy(2,4); MmiPrintf("Enter - ����������");
   }
}
//-------------------------------------
void f_drv_list_MMI(int *nn)
{ // �������� ������ ��������� ���������
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
    MmiGotoxy(0,0); MmiPuts("        ������ ���������      ");
    MmiGotoxy(0,1); MmiPuts(" N     ���   ����. ���� ���.");
   for(i2=0;i<i1;i++,i2++)
    {
      ICPl_DEV=ICP_dd[i];
      if(ICPl_DEV==NULL) break;
      MmiGotoxy(0,3+i2);
//         MmiPuts(" N      ���   ����. ���� ���.");
//                 "xx.....xxxxx  .x    .x   xx"
      MmiPrintf("%2d%10s  %2d    %2d   %02X",i+1,ICPl_DEV->name,ICPl_DEV->status,ICPl_DEV->port,ICPl_DEV->addr);
    }
}
//-------------------------------
void f_drv_stat_MMI(int *nn)
{ // �������� ���������� ��������� ���������
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
    MmiGotoxy(0,0);  MmiPuts(" ���������� ������ ���������");
    MmiGotoxy(0,1);  MmiPuts(" N     ���    �������  ������");
    for(i2=0;i<i1;i++,i2++)
    {
      ICPl_DEV=ICP_dd[i];
      if(ICPl_DEV==NULL) break;
      MmiGotoxy(0,3+i2);
//         MmiPuts(" N     ���    �������  ������");
//                 "xx.....xxxxx  xxxxxxx xxxxxxx"
         MmiPrintf("%2d%10s  %7ld %7ld",i+1,ICPl_DEV->name,ICPl_DEV->n_transaction,ICPl_DEV->n_timeout_error+ICPl_DEV->n_CRC_error);
    }
}
//-------------------------------
//-------------------------------
void f_mod_list_MMI(int *nn)
{ // �������� ������ ������������ �������
int i,i1,i2;
 char str[31];

  struct icp_mod *ICPl_MOD;

  i1=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
  f_clr_scr_MMI();
  if(i1==0)
  {
    MmiGotoxy(3,2);   MmiPuts("    ������ ����." );
    MmiGotoxy(3,3);   MmiPuts("����������� ����� ���" );
    MmiGotoxy(3,4);   MmiPuts("  ���������� ������." );
  }
  else
  {
    MmiGotoxy(0,0);    MmiPuts(" ������ ������������ �������  ");
    MmiGotoxy(0,1);    MmiPuts(" N    ��� ����.���.����. TT FF");

      i=*nn;
    if(i<0) i=0;
    if((i+n_mmi_str_3) < i1) i1=i+n_mmi_str_3;
    *nn=i;

    for(i2=0;i<i1;i++,i2++)
    {
      ICPl_MOD=f_get_mod_str(i);
      if(ICPl_MOD==NULL) break;
      MmiGotoxy(0,3+i2);

//         MmiPuts(" N    ��� ����.���.����. TT FF");
//                 "xx.....xxxx  x xx xxxxxx xx xx"
      MmiPrintf("%2d%9s  %1d %02X %6ld %02X %02X",i+1,ICPl_MOD->name,ICPl_MOD->port,ICPl_MOD->addr,baudrate_val[ICPl_MOD->CC],ICPl_MOD->TT,ICPl_MOD->FF);
    }
  }
}
//-------------------------------
int mode_prn=1;
void f_prn_current()
{ // �������� ��������� ������� �� ������� ������
  int year,month,day,hour,min,sec;
 MmiGotoxy(0,0);   MmiPrintf("T������ �������� ��������");
 MmiGotoxy(0,3);   MmiPrintf("  ����     �����     �����,��");
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
 //  ����������� �����,���������,�����������,��������
 //  ������� ��������.
 MmiGotoxy(0,0);   MmiPrintf("������� ��������� �����������");
 MmiGotoxy(0,2);   MmiPrintf(" ����� ���. %10.3f ��",s_MVD[0].MassT);
 MmiGotoxy(0,3);   MmiPrintf(" ����� ���. %10.3f � ",s_MVD[0].VolT);
 MmiGotoxy(0,5);   MmiPrintf(" ����� ���. %10.3f ��",s_MVD[0].MassI);
 MmiGotoxy(0,6);   MmiPrintf(" ����� ���. %10.3f � ",s_MVD[0].VolI);
 MmiGotoxy(0,8);   MmiPrintf(" ������    %10.2f ��/�",s_MVD[0].FlowM);
 MmiGotoxy(0,9);   MmiPrintf(" ������    %10.2f �/�",s_MVD[0].FlowV);
 MmiGotoxy(0,10);   MmiPrintf(" ��������� %10.2f ��/�3",s_MVD[0].Dens);
 MmiGotoxy(0,11);   MmiPrintf(" ����.������.  %6.1f ����.C",s_MVD[0].Temp);

//02.02.2022 YN
#if !defined(GAZAVOZ)
  MmiGotoxy(0,12);   MmiPrintf(" �����������   %6.2f ����.C",s_MVD[0].TempR);
  MmiGotoxy(0,13);   MmiPrintf(" ��������      %6.3f ���  ",s_MVD[0].Press);
#endif

 MmiGotoxy(0,15);   MmiPuts(" ESC-����");
}
//-------------------------------



































































//10.02.2022 YN
//-------------------------------
void f_prn_lst_hour()
{ // �������� ��������� ������� �� ��������� ����. ���

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // ������� �����

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
   MmiGotoxy(5,3);   MmiPrintf("������ �����������");
  }
  else
  {
  m_ok:
 MmiGotoxy(0,0);   MmiPrintf("   �������� �������� ��� ");
 MmiGotoxy(0,1);   MmiPrintf(" �� ��������� ��������� ���  ");

 MmiGotoxy(0,3);   MmiPrintf("  ����     �����     �����,��");
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
{ // �������� ��������� ������� �� ��������� ����

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;
 // ����������� ������� ��������� ������ � ������

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // ������� �����

 tim_000=adate00;
 tim_000.hour=ahour00.hour;
 tim_000.min=ahour00.min;
 tim_000.sec=ahour00.sec;

 ltime0=f_get_time_t(&tim_000);

 MmiGotoxy(0,0);   MmiPrintf("   �������� �������� ��� ");
 MmiGotoxy(0,1);   MmiPrintf("     �� ��������� ����  ");

 MmiGotoxy(0,3);   MmiPrintf("  ����     �����     �����,��");
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
      MmiPrintf("��� ������");
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
{ // �������� ��������� ������� �� ��������� 5 �����

 struct tm *tdat;

int year,month,day,hour,min,sec,i;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // ������� �����

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
   ltime2= f_get_time(ar_str_ptr); // ��������� ������

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

 MmiGotoxy(0,0);   MmiPrintf("  ����     �����     �����,��");
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
           MmiPrintf("��� ������");
     }
     else
     // if(tMassI>= 0.)
           MmiPrintf("%11.3f" ,tMassI);
     // else
     //    MmiPrintf(" ------- ");
    }
    MmiGotoxy(0,6);   MmiPuts("ESC,Enter - ����������");

  }
 }
 else goto m_ok;
 return;

 m_bad:
   MmiGotoxy(5,3);   MmiPrintf("������ �����������");
 return;
}
//-------------------------------






















































//-------------------------------
char *rcv_mm[]={
"������",
"�����",
};
char *Rcv_mm[]={
"������",
"�����",
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


 if( (a_str->event==slt_wr_jrnI) || (a_str->event==slt_wr_jrnF)  );
 else
  if((a_str->MassI != vBIG_P)&& (a_str->MassI != M_one) )
     MmiPrintf("%10.3f ��",a_str->MassI);
  else
     MmiPrintf(" ------- " );

// i_ret=i_n+1;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;

 MoveToXY(0,i_ret);

 if( (a_str->event==slt_wr_jrnI) || (a_str->event==slt_wr_jrnF)  );
 else
  if((a_str->VolI != vBIG_P)&& (a_str->VolI != M_one) )
  {
     MmiPrintf("V=%10.3f �",a_str->VolI);
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
    MmiPrintf("����� %s�.",rcv_mm[f_rcv]);
    goto m_val0;

  case slt_wr_jrnF:
    MmiPrintf(" ����. MVD,float:");

   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    MmiPrintf("Addr=%5.0f, n= %2.0f:",a_str->MassI,a_str->VolI/2.);
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    MmiPrintf(" %g",a_str->u.fill.VolT);

    if( a_str->VolI  > 2 )
      MmiPrintf(", %g", a_str->u.fill.Amount);

    if( a_str->VolI  > 4 )
      MmiPrintf(", %g,", a_str->u.fill.UnitPrice);
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    if( a_str->VolI  > 6 )
      MmiPrintf(" %g", a_str->u.fill.Density);

    if( a_str->VolI  > 8 )
      MmiPrintf(", %g", a_str->u.fill.Temp);

    break;

  case slt_wr_jrnI:
    MmiPrintf(" ����. MVD,int:");
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf(" Addr=%5.0f, n= %2.0f:",a_str->MassI,a_str->VolI);
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    for(ii=0;ii<a_str->VolI;ii++)
    {
      if((ii== 4) || (ii== 8) )
      {
       i_ret++;
       if(i_ret>=n_mmi_str) return i_ret;
       MoveToXY(0,i_ret);
      }
      MmiPrintf(" %6d",a_str->u.err.err[ii] );
    }
    break;

  case evt_start_fL:
    MmiPrintf("����� ����.");
    goto m_val0;

  case evt_start_f:
    MmiPrintf("����� �����.");

m_val0:
//   i_ret=i_n+2;
// if(i_ret>=n_mmi_str) return i_ret;
// MoveToXY(0,i_ret);
  if(a_str->u.fill.VolT != vBIG_P)
  {
      if ( Flag_mass != 0 )
        MmiPrintf("���� %8.3f�� ",a_str->u.fill.VolT    );
      else
        MmiPrintf("���� %8.3f �",a_str->u.fill.VolT    );
  }
  else
      MmiPrintf("��� ����    ",a_str->u.fill.VolT    );

m_val1:
// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

   MmiPrintf("�����.%6.3f��/�3;" ,a_str->u.fill.Density);
   MmiPrintf("�=%6.2fC;" ,a_str->u.fill.Temp);

   i_ret++;
// i_ret=i_n+3;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%6.3f ���;" ,a_str->u.fill.UnitPrice);
//  MmiPrintf("�=%6.2fC;" ,a_str->u.fill.Amount);

    break;

  case evt_cont_f:
    MmiPrintf(" ����������� %s�,",rcv_mm[f_rcv]);
    goto m_val;
  case evt_exm_f:
    MmiPrintf(" ���������,������� ");

m_val:

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    if(a_str->u.fill.VolT != vBIG_P)
         MmiPrintf(" ���.%9.3f ��,%9.3f �",a_str->u.fill.VolT,a_str->u.fill.Amount );

// i_ret=i_n+3;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("�����.%6.3f ��/�3;" ,a_str->u.fill.Density);
    MmiPrintf("�=%6.2fC;" ,a_str->u.fill.Temp);

// i_ret=i_n+4;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%6.3f ��� ;" ,a_str->u.fill.UnitPrice);
//    MmiPrintf("�=%6.2fC;" ,a_str->u.fill.Amount);

    break;

  case evt_exp_f:
    MmiPrintf(" ���������,�������");
    goto m_val;

  case evt_end_gas:
    MmiPrintf(" %s �����.��� ���.����",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_end_f:
    MmiPrintf(" ��������� ��  ");
    goto m_val;

  case evt_est_f:
    MmiPrintf(" %s ������� ��������",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_est_fh:
    MmiPrintf(" %s ������� Host ",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_err_f:
    MmiPrintf(" %s ������� �������",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_eq_pr :
    MmiPrintf("����� ���.����. ������� ���");
    goto m_val;
  case evt_stop_eq :
  printf("������.���.����. ������� ���");
    goto m_val;

  case evt_ep1_f:
    MmiPrintf(" %s �������,Host",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_overfl:
    MmiPrintf(" %s ������� ���.������",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_ES_off:
//  MmiPrintf(" %s �����.����.������� ES",Rcv_mm[f_rcv]);
    MmiPrintf(" %s �����.������.�� �����",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_UZA_off:
    MmiPrintf(" %s �����.��� ������� ���",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_LVL_off:
    MmiPrintf(" %s  �������: �������.",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_TRAP_off:
    MmiPrintf(" %s  �������: ����.",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_CONS_off:
    MmiPrintf(" %s  �������: �������.",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_DLT_off:
    MmiPrintf(" %s �����.����� �� �������",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_wd_pmp:
    MmiPrintf(" %s �����.WD PMLAN",Rcv_mm[f_rcv]);
    goto m_val;


  case evt_no_dev:
    MmiPrintf(" ����� �� ������.�� ���.�����");
    goto m_val;

  case evt_clr_err:
    MmiPrintf(" ����� ������. ");
    break;

  case evt_MVD_CL_strt:
    MmiPrintf(" ����� ���������� �����������");
    break;

  case evt_MVD_CL_BS1 :
    MmiPrintf(" !������� ���.����.��� ���.");
    break;

  case evt_MVD_CL_BS2 :
    MmiPrintf(" !���� ��� ������ ���.����.");
    break;

  case evt_MVD_CL_OK :
    MmiPrintf(" ���������� ����������� OK");
    break;

  case evt_MVD_CL_TM :
    MmiPrintf(" ������� ���������� ��������.");
          //  |                              |

    break;

  case evt_ch_date:
    MmiPrintf(" ���� ��������.");
    break;

  case evt_ch_time:
    MmiPrintf(" ����� ��������.");
    break;
  case evt_ch_sum:
    MmiPrintf(" ������� �� ������ �����.");
    break;
  case evt_ch_win:
    MmiPrintf(" ������� �� ������ �����.");
    break;
  case evt_res:
    MmiPrintf(" ������� �����");
    break;
  case evt_Slot:
    MmiPrintf(" MVD:����������-� ����������");
    break;
  case evt_chg_param:
    if(a_str->u.fill.VolT == Par_VF)
    {
     MmiPrintf(" !���.����.������");
    }
    else if(a_str->u.fill.VolT == Par_MF)
    {
     MmiPrintf(" !���.����.�����");
    }
    else if(a_str->u.fill.VolT == Par_MC)
    {
     MmiPrintf(" !���.����.�.����.");
    }
    else if(a_str->u.fill.VolT == Par_PASS)
    {
     MmiPrintf(" !������� ������");
    }
    else if(a_str->u.fill.VolT == Par_ID)
    {
     MmiPrintf(" !������� ID");
    i_ret++;
    if(i_ret>=n_mmi_str) return i_ret;
    MoveToXY(0,i_ret);

    MmiPrintf("���� :%ld; ",(long int)a_str->u.fill.Amount  );
    MmiPrintf("�����:%ld" ,(long int)a_str->u.fill.UnitPrice);
    break;
    }
    else
     {
//    MmiPrintf(" !���. �����. ");
      MmiPrintf(" !������� �������� ");
      MmiPrintf("N%g ",a_str->u.fill.VolT );
     }

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    MmiPrintf("����:%g; ",a_str->u.fill.Amount  );
    MmiPrintf("�����:%g" ,a_str->u.fill.UnitPrice);
    break;
  case evt_exit:
    MmiPrintf(" ������� ����� � ���");
    break;
  case evt_re:
    MmiPrintf(" ������ ����.�� EEPROM");
    break;
  case evt_re_err:
    MmiPrintf(" ������ ������ ����.�� EEPROM");
    break;
  case evt_we:
    MmiPrintf(" ������ ����. � EEPROM");
    break;
  case evt_we_err:
    MmiPrintf(" ��.������ ����. � EEPROM");
    break;

  case evt_wrong_start:
    MmiPrintf(" C���� �� ������.������.");
    goto m_val;

  case evt_err:
  case evt_none:
 mm_0:
    itmp=0;
    for(ii=0;(ii<=icp_lst_max)&& (ii<10) ;ii++)
      itmp |= a_str->u.err.err[ii];
  if(itmp)
  {
    MmiPrintf(" ������:");
 mm_e:

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

 MmiPrintf("%X" ,a_str->u.err.err[0] );    // MVD
 MmiPrintf(" %01X" ,a_str->u.err.err[1] );   // 7060
 MmiPrintf(" %01X" ,a_str->u.err.err[2] );   // 7041
 MmiPrintf(" %01X" ,a_str->u.err.err[3] );   // 7017
 MmiPrintf(" %01X" ,a_str->u.err.err[4] );   // TSD[0]
 MmiPrintf(" %01X" ,a_str->u.err.err[5] );   // Drive
 MmiPrintf(" %X" ,a_str->u.err.err[6] );   // OFP
 MmiPrintf(" %01X" ,a_str->u.err.err[7] );   // MMI
 MmiPrintf(" %04X:" ,a_str->u.err.err[8] );  // System
 MmiPrintf("%04X" ,a_str->u.err.err[9] );    // ���
  }
  else
 MmiPrintf(" ������ ��� ");

  break;

  case evt_t_on:
 MmiPrintf(" ��������� ����������");
    break;
  case evt_t_off:
 MmiPrintf(" ���������� ����������");
    break;
  default:
    if( (a_str->event & evt_start_hst) == evt_start_hst )
    {

    ii=a_str->event;
    MmiPrintf("���.Host ");

    if(ii & 4)
      MmiPrintf("����� ");
    else
      MmiPrintf("����� ");

    if(ii & 1)
      MmiPrintf("�.���.");
    else
      MmiPrintf("�.���.");

    if(ii & 2)
    {
      MmiPrintf("�� �����.");
      i_ret++;
      if(i_ret>=n_mmi_str) return i_ret;
      MoveToXY(0,i_ret);
      MmiPrintf("���� %8.3f ��; " ,a_str->u.fill.VolT );
    }
    else
    {
       MmiPrintf("�� ������." );
       i_ret++;
       if(i_ret>=n_mmi_str) return i_ret;
       MoveToXY(0,i_ret);
       MmiPrintf("����  %8.3f � ; " ,a_str->u.fill.VolT );
     }
     goto m_val1;
     }
    else
 MmiPrintf(" ������� �� ��������");
   break;
 }
 return i_ret;
}

//----------------------------------
void f_MVD_M1()
{
// ���������� ��������� MVD  �� MMI

     ff_serv=NULL;
/*

  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� ������ MVD");
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
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("TXM ������: %d",s_MVD[0].i);}
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
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("�emp.: --%s--",s_MVD[0].a);}
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
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("��������� �����:     %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=281;
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("��������� ������:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 33:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=283;
   sw_mvd_m1=14;
   break;

  case 14:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("��������� ���������: %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 34:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=195;
   sw_mvd_m1=15;
   break;

  case 15:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("���� ����.�������:   %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 35:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=197;
   sw_mvd_m1=16;
   break;

  case 16:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("���� ��. �������:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 36:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=149;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,sw_MMI_cur++); MmiPrintf("���� ��������� :     %.6f",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  }
 */
}
/* ---------------------------------------- */
void f_MVD_M1f()
{
// ���������� ��������� ��������� �������  MVD  �� MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
     MoveToXY(0,4); MmiPrintf(" !������� ������ MVD");
     ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
#if(Shtray==0)
  case 31:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=279;
   sw_mvd_m1=12;
   break;

  case 12:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,4);MmiPrintf("��������� �����:    %.6f",s_MVD[0].f);}
     k_m_flow=s_MVD[0].f;

  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=281; // ��������� ������
//   s_MVD[0].r_addr=195;  // Cuttoff for mass flow
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,5);MmiPrintf("��������� ������:   %.6f",s_MVD[0].f);}
   k_v_flow=s_MVD[0].f;

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=283; // ��������� ������
   sw_mvd_m1=14;
   break;

  case 14:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,6);MmiPrintf("��������� �����.:   %.6f",s_MVD[0].f);}
   k_dens=s_MVD[0].f;

//08.02.2022 YN
//#else  // Shtray != 0
#endif
#if(Shtray==1)

 case 31:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr= Scl_Flow_Addr; //279;
   sw_mvd_m1=12;
   break;

  case 12:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,4);MmiPrintf("��������� �����:    %.6f",s_MVD[0].f);}
     k_m_flow=s_MVD[0].f;
/*
  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=281; // ��������� ������

   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,5);MmiPrintf("��������� ������:   %.6f",s_MVD[0].f);}
// { MoveToXY(0,5); MmiPrintf("���� �.����.: %10.2f ��/�",s_MVD[0].f);}
   k_v_flow=s_MVD[0].f;
*/
   k_v_flow=1.0;
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=Scl_Dens_Addr; //283; // ��������� ������
   sw_mvd_m1=14;
   break;

  case 14:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,6);MmiPrintf("��������� �����.:   %.6f",s_MVD[0].f);}
   k_dens=s_MVD[0].f;

#endif

//08.02.2022 YN
#if(Shtray==2)

  case 31:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=5521;
   sw_mvd_m1=12;
   break;

  case 12:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,8);MmiPrintf("����� ����. �������: %.6f",s_MVD[0].f);}
//float sdv_m_flow=1.0, sdv_v_flow=1.0, sdv_dens=1.0;
     sdv_m_flow=s_MVD[0].f;

  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=5519; // ����. ����. //   s_MVD[0].r_addr=195;  // Cuttoff for mass flow
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,9);MmiPrintf("����. ����. �������: %.6f",s_MVD[0].f);}
   k_m_flow=s_MVD[0].f;//   k_v_flow=s_MVD[0].f;

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=5525; //����� �����. �������
   sw_mvd_m1=14;
   break;

  case 14:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,10);MmiPrintf("����� �����.�������: %.6f",s_MVD[0].f);}
   sdv_v_flow=s_MVD[0].f;   //   k_dens=s_MVD[0].f;
//================================================   
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=5523; // ����. �����
   sw_mvd_m1=15;
   break;
  case 15:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,11);MmiPrintf("����. �����.�������: %.6f",s_MVD[0].f);}
   k_v_flow=s_MVD[0].f;

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=5529; // ����� ���������
   sw_mvd_m1=16;
   break;   
  case 16:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,12);MmiPrintf("����� ���������    : %.6f",s_MVD[0].f);}
   sdv_dens=s_MVD[0].f;
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=5527; // ��������� �����.
   sw_mvd_m1=17;
   break;   
  case 17:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,13);MmiPrintf("����. ���������    : %.6f",s_MVD[0].f);}
   k_dens=s_MVD[0].f;

#endif

   ff_serv=NULL;
   Flag_f_corr=1;
   break;
 }
}
/* ---------------------------------------- */
void f_MVD_M1s()
{
// ���������� ��������� ��������� �������  MVD  �� MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
     MoveToXY(0,4); MmiPrintf(" !������� ������ MVD");
     ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {

    //08.02.2022 YN
    #if(Shtray==2) //Promass

      case 31:
        MVD_fn[0]=MVD_RD_F;
        s_MVD[0].r_addr=5138;  //�������� ���������    MM=195
        sw_mvd_m1=12;
      break;

      case 12:
        if(MVD_fn[0] != F_FAULT)
        { 
          MoveToXY(0,4); 
          MmiPrintf(" �������� ���������: %8.1f ��/�",s_MVD[0].f);
        }
        k_m_flow=s_MVD[0].f;

      //17.02.2022 YN
      /*case 32:
        MVD_fn[0]=MVD_RD_F;
        s_MVD[0].r_addr=5104;  //�������� ���������� 0-100%     MM 197 Cuttoff for vol flow
         sw_mvd_m1=13;
      break;

      case 13:
        if(MVD_fn[0] != F_FAULT)                     // Shtray
        { 
          MoveToXY(0,5); 
          MmiPrintf("�������� ����������: %8.1f  %",s_MVD[0].f);
        }
        k_v_flow=s_MVD[0].f;*/

    #else

    case 31:
      MVD_fn[0]=MVD_RD_F;
      s_MVD[0].r_addr=195;
      sw_mvd_m1=12;
    break;

    case 12:
      if(MVD_fn[0] != F_FAULT)
      { 
        MoveToXY(0,4); 
        MmiPrintf("���� �. ����.: %8.1f ��/�",s_MVD[0].f);
      }
      k_m_flow=s_MVD[0].f;

    case 32:
      MVD_fn[0]=MVD_RD_F;
      s_MVD[0].r_addr=197;  // Cuttoff for mass flow
      sw_mvd_m1=13;
    break;

    case 13:
      if(MVD_fn[0] != F_FAULT)                     // Shtray
      { 
        MoveToXY(0,5); 
        MmiPrintf("���� ��.����.: %8.1f  �/�",s_MVD[0].f);
      }
      k_v_flow=s_MVD[0].f;

    #endif

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
// ���������� ������ MVD

        ff_serv=NULL;
/*
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� ������ MVD");
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ �. : %f %s",s_MVD[0].f,unit1);}
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.3f %s",s_MVD[0].f,unit2);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.2f %s",s_MVD[0].f,unit2); }
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ ��.: %f %s",s_MVD[0].f,unit3);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.3f %s",s_MVD[0].f,unit4);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.2f %s",s_MVD[0].f,unit4);}
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
      MoveToXY(0,sw_MMI_cur++);MmiPrintf("���������  :%.5f %s",s_MVD[0].f,unit5);
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
    MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.������: %.3f %s",s_MVD[0].f,unit6);
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.����� : %.3f C",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=385;
   sw_mvd_m1=18;
   break;

  case 18:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.���.  : %.3f V",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  default:
     ff_serv=NULL;
  }
*/
}
/* ---------------------------------------- */
void f_MVD_MM2()
{
char *unit;
// ���������� ������ MVD


        ff_serv=NULL;
/*
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� ������ MVD");
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ �. : %f %s",s_MVD[0].f,unit1);}
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.3f %s",s_MVD[0].f,unit2);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.2f %s",s_MVD[0].f,unit2); }
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ ��.: %f %s",s_MVD[0].f,unit3);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.3f %s",s_MVD[0].f,unit4);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.2f %s",s_MVD[0].f,unit4);}
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
     MoveToXY(0,sw_MMI_cur++); MmiPrintf("���������  :%.5f %s",s_MVD[0].f,unit5);
     MMIDens=s_MVD[0].f;
  }
  else
  {
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ ������");
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
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.������: %.3f %s",s_MVD[0].f,unit6);
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.����� : %.3f C",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=385;
   sw_mvd_m1=18;
   break;

  case 18:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.���.  : %.3f V",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  default:
     ff_serv=NULL;
  }
*/
}
/* ---------------------------------------- */
void f_MVD_M3()
{
int i,i2;
unsigned long int ltmp,i1;
// ���������� ������ MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� ������ MVD");
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
   MoveToXY(0,3); MmiPrintf("         ������ ���.          ");
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
          MmiPrintf("   ������ �����������:");
      else if( i>1)
          MmiPrintf("   ������ �����������:");
       i2=1;
     }
     else
     {

      MoveToXY(0,0);
         MmiPrintf("���������/������ �����������:");
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
void f_MVD_MM4()
{
// ��������� ���� � ������������� ������������� ������� == 0
 if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
 {
   if( f_timer(tm_mvd,f_MVD_tim ) )
   {
    MoveToXY(0,4); MmiPrintf(" !������� ������ MVD");
    f_icp_errS(MVD_com);
    ff_serv=NULL;
   }
   return;
 }
 tm_mvd=TimeStamp;

 switch(sw_mvd_m1)
 {

    //08.02.2022 YN
    #if(Shtray==2)

    #else
      case 20:
        // Stop totalizers
        MVD_fn[0]=MVD_WR_C;
        s_MVD[0].r_addr=2;
        s_MVD[0].i=0;
        s_MVD[0].f=0;
        sw_mvd_m1=30;
      break;

      case 30:   // ���� �. ����.
        MVD_fn[0]=MVD_WR_F;
        s_MVD[0].r_addr=195;
        s_MVD[0].f=0;
        sw_mvd_m1=31;
      break;

    #endif

    case 31:   // ���� �. ����.

      State_SLV = Mod_flow_a;
      f_reg_cmn(Mod_flow_a_cmn);
      ff_serv=NULL;
    break;

    default:
      ff_serv=NULL;
    break;
  }
}
/* ---------------------------------------- */

/* -----PROMASS----------------------------------- */
void f_MVD_M3_Pr()
{
int i,i2;
unsigned long int ltmp,i1;
// ������ ��������� ��� ����������

  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� ������ MVD Promass");
        ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 0:

   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr=6797; //������� ���������
   sw_mvd_m1++;
   break;

  case 1:
   if(MVD_fn[0] != F_FAULT)
   {
//     ltmp=(unsigned long int)s_MVD[0].f &0xffffff;
     ltmp=s_MVD[0].i; 
//printf("Progress =: %3d \n\r", ltmp);
     if(ltmp >= 100) //100 ���������
     {
      fl_zeroing=0;         
      ff_serv=NULL;
      return;
     }     
      
   }
   ff_serv=NULL;
   break;
  }
}
//------------------------


//------------------------
//------------------------
//-------------------------------

char *list1_dsr[]={

"MMI:������",                 //  0
"���� ����� ",         //  1
"���� ��������",         //  2

#if defined(PMP_LG)
"PMP delay,0.1s",         //  3
"PMP on flag",          //  4
#else
"",         //  3
"",          //  4
#endif
"MMI:���� CRC",               //  5

"7017/1:������",                 //  6
"LOW mode",            //  7
"HIGH mode",                  //  8
"N ��� ",              //  9
"P_demand",             // 10
"K_D",               // 11
"K_P         ",                // 12
"K_I         ",           // 13
"Mode P    ",                 // 14
"Addr Modbus  ",             // 15
"Delta :������",                // 16
"���� Slave      ",             // 17

"7044:������",                 // 18
"K_FD",                   // 19
"K_FP",                   // 20
"K_FI",                   // 21
"7041:������",          // 22
"OFP:������",          // 23

"",                // 24
"",           // 25
"",                 // 26
"",             // 27
"",            // 28
"",              // 29

"",                // 30
"COM2 ��������",                // 31
"����.�������,�",                // 32
"",                // 33

"",            // 34
"",           // 35
"",            // 36

"WDOG/1:������",                // 37
"WDOG/1:����� �����",           // 38
"WDOG/1:������,�� ",            // 39
"WDOG/1:��������,��",           // 40
"WDOG/1:���� CRC",              // 41

"Addr reg",   // 42
"n reg",      // 43
"Tim,ms",     // 44
"Mult",       // 45
"nnn=-1",     // 46
"int 1,float 2",// 47
"",        // 48

"",           // 49
"",        // 50

"MVD:������",                 //  51
"",            //  52
"",                  //  53
"",              //  54
"",             //  55

"TSD:������",                 //  56
"",            //  57
"",                  //  58
"",              //  59
"",             //  60

"��.�.=Stop= N ��.",     // 61
"��.�.=Stop=��.���.",    // 62
"��.�.=Start= N ��.",   // 63
"��.�.=Start=��.���",   // 64

"",           // 65
"",           // 66
"",           // 67
"",           // 68

"",           // 69
"",           // 70
"",           // 71
"",           // 72

"",           // 73
"",              // 74
"",           // 75
"",           // 76

"",        // 77
"",         // 78
"",       // 79

"��.�.��� N ���.",        // 80
"��.�.��� N ���.",        // 81
"���� ����.������.",      // 82
"",      // 83
#if(AIR_SW != 0)
"�-����.�.�.N ���.",      // 84
#else
#if(CUT_SW != 0)
"������.��.N ���.",      // 84
#else
"OUT4 N ���.",      // 84
#endif
#endif

"��.�.��� N ���.",     // 85
"��.�.��� N ���.",     // 86
"��� ������ N ���",        // 87
"",           // 88
"������� �� ���.��.",       // 89
"------------------",       // 90
"P ������ �����,���",       // 91
"P ��������,    ���",       // 92
"T ������ �����,C",         // 93
"T ��������,    C",         // 94
"",        // 95
"",        // 96
"",        // 97
"���.Vol � �.��.1",         // 98    p1-p6.CLV
"���.Vol �.�.��.2",         // 99
"T ������.���.1",       // 100
"T ������.���.2",       // 101
"���.����.��.MMI,��",      // 102
"����.����.�.MMI,��",       // 103
"������.�.�. 0...1",        // 104   p1-p2.KA
"������.�.�. 0...1",        // 105
"���-�� ���.���.,��",       // 106

"�������� ����� 1/0",       // 107    p1.CTRL
"",       // 108    p2.CTRL
"���� ����.��� TST",        // 109    p3.CTRL

"��������� M,��",           // 110    p1-p5.DSC
"�����������-� M,��",        // 111
"������ ��� ����.��",       // 112
"��������� M,��",            // 113
"��������� T,��",           // 114


"���.'�������' N ��.",      // 115
"���.'�������'��.���",      // 116
"T ����� ���.��.,�� ",      // 117
"T ����� ����.��.,�� ",     // 118
"����� t ���.0-2",          // 119
"����� ������� 1-3",        // 1 2 0


"���.��.���.N ��.",    // 121
"���.��.���.��.���",   // 122
"���. ���.��1,��",      // 123
"Tmin ����. ��1,��",       // 124
"Tmin ���.  ��1,��",        // 125

"���.��.���.N ��.",      // 126
"���.��.���.��.���",      // 127
"��.�.=Start= N ��.",        // 128
"��.�.=Start=��.���",      // 129
"��.�.=Stop= N ��.",      // 130
"��.�.=Stop=��.���.",      // 131
"����.'����' N ��.",      // 132
"����.'����'��.���.",      // 133
"MAX �������",              // 134
"MAX �������",              // 135
"WD ���.MASTER,��",        // 136


// FLCH
#if defined(GAZAVOZ)
  "����� �����.�.BIG",      // 137
  "����� �����.�.LTL",      // 138
  "����� ���.�����.�.",       // 139
  "����� ��������,���",     // 140
  "����� ����.���.���",    // 141
#else
  "��.��.����. N ��.",      // 137
  "��.��.����.��.���",      // 138
  "����.��� �.N ��.",       // 139
  "����.��� � ��.���.",     // 140
  "���.����.�.�.��/�. ",    // 141
#endif


"���.������ N ���.",        // 142
"��.��.�����. N ��.",      // 143
"��.��.�����.��.���",      // 144
"����.��� �.N ��.",      // 145
"����.��� � ��.���.",      // 146
"",       // 147
"�������� N ����.��.",     // 148
"��������.N ����.��.",     // 149
"-------------------",     // 150
"f ���� ������,0.1��",     // 151
"T ����.������,0.1�",      // 152
"�������� ���.��2,��",     // 153
"���.����.������,��",      // 154
"T ����.������,0.1�",      // 155
"���.Vol �.�.��.1",        // 156   p1-p2.CLM
"���.Vol �.�.��.2",        // 157
"���.����.�.�.��/�",         // 158
"����� 1,��  ",            // 159
"����.1,��/�. ",           // 160
"����� 2,��  ",            // 161
"����.2,��/�. ",           // 162
"����� 3,��  ",            // 163
"����.3,��/�. ",           // 164
"��� �������������",       // 165

//10.06.2021 YN
#if (PressureDrop == 1)
"�������  N ����.��",     //166
"������� �����, ���",     //167
"������� �����. ���",     //168
#else
"",                       //166
"",                       //167
"",                       //168
#endif

#if(PressureDrop == 2)
"����.��� N ����.��",     //169
"����.��� N ����.��",     //170
"P-�� ���� ����,���",     //171
"P-�� ��������, ���",     //172
"P-���� �����,  ���",     //173
"P-���� ����.,  ���",     //174
#else
"",                       //169
"",                       //170
"",                       //171
"",                       //172
"",                       //173
"",                       //174
#endif

//11.06.2021 YN
#if defined(PresenceLiquid)
"���.'������' N ��.",      //175
"���.'������' ��.���",     //176
#else
"",                        //175
"",                        //176
#endif

//27.10.2021 YN
#if defined(N_Pipes)
"N ����� ���.������",    //177
"N ����� ���.������",    //178
#else
"",                        //177
"",                        //178
#endif

//18.11.2021 YN
#if defined(weightedAverageTemperature)
"�����������.����.",       //179
#else
"",                        //179
#endif

"",
};
//-------------------------------

char *list2_dsr[]={
" �����.������",            //  0
" ����.���,�����.",         //  1
" ����.����.,���",          //  2
" ����.����.,C",            //  3
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

int FlagWinSum=0;

struct arch_str_t adate11;

struct dis_set_MMI *ds_list=NULL;


long int Password=5555;
long int PassW=0;
long int Password_m=0;
long int PassWm=0;
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
  int itmp;
  struct s_icp_dev *ICPl_DEV;
struct arch_str *ar_str_ptr;
long int ltmp;
 struct tm *tdat;

//   s_MVD[0].Press=( ADC[0] + analog_offset[0]) * analog_scale[0];
   sw_mmi_slv= sw_mmi;
   if((i=fstin())==fst_OK)
   {  // ������� �������� ��������
     key=DATA;  // ������� ��������� ����� ������
     sw_fst=0;
   }
   else if(i==fst_ESC)
   {
     key=DATA_ESC;  // ������� ��������� ����� ������
     sw_fst=0;
   }
   else if( MmiKbhit())
   {  // ���� ������������ ������� �� ����������
    key=MmiGetch();
    if(key==F1)
    {
      OUT_VAR ^= OUT7;
      return 0;
    }
   }
   else if(sw_fst==0)
   {
    key=PASS; // ������� ��������� ������� (��� ���������� �������)
              // ������������ ��� ��������� ������������ ��������
   }
   else return 0;

   switch(sw_mmi)
    {
     case 0: /*���������*/


//---------------------------------
       if((key==F2) && (id_ok !=0) )
        {
         flag_esc=0;
         PageD=0;
         f_prn_begin();
        }

    //02.02.2022 YN
    #if !defined(GAZAVOZ)
       else if(key==F3)
        {
         flag_esc=0;
         PageD=1;
         f_prn_begin();
        }
    #endif

       else if(key=='1')
        {
         flag_esc=0;
         f_prn_begin();
        }
       else if ((key==F2) && (id_ok ==0) )
        {
       m_0f2:
          flag_esc=1;
          MmiGotoxy(1,1);
          f_clr_scr_MMI();

           chg_nn_par=Par_ID;
           chg_old=n_id;
          MmiPuts("������� ID:" );
          sprintf( fst_str,"%8ld",n_id);
          fst_n=9;
          sw_fst=1;
          MmiGotoxy(10,3);
  //      MmiGotoxy(15,3);
#if defined(MMI_ICP)
          SetDisplayPage(15); // ���� ��������
#endif

#if defined(MMI_NEW)
          SetDisplayPage(2); // ���� ��������
#endif


          break;
        }
       else if(key==DATA)
        {
          flag_esc=1;
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
          flag_esc=1;
          goto mm00;
        }
   /*
       m_0f2:
          MmiGotoxy(1,1);
          f_clr_scr_MMI();
          MmiPuts("������� ����� ��������:" );
          sprintf( fst_str,"%d",num_page);
          fst_n=2;
          sw_fst=1;
//        MmiGotoxy(10,3);
          MmiGotoxy(15,3);
#if defined(MMI_ICP)
          SetDisplayPage(15); // ���� ��������
#endif

#if defined(MMI_NEW)
          SetDisplayPage(2); // ���� ��������
#endif

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
        {  // ������� ������

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);
          sw_mmi=26;
          f_cl_error();
          MmiGotoxy(5,2);    MmiPuts("   ������ �������   ");
          MmiGotoxy(0,4);    MmiPuts(" Enter - ���������� ");
          flag_esc=1;

        }
        else if (key==Sht_F1)
        {  // ���������� ������

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);
          sw_mmi=26;
          f_disp_error();
          flag_esc=1;
        }
        else if(key==Sht_F2)
        {  // MVD zeroing

          flag_esc=1;
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);

          if(f_reset_zer_MVD() == 0)
          {
          MoveToXY(0,3);
          MmiPrintf(" ������ ������� ���������� ");
          f_wr_evt(evt_MVD_CL_BS2);
  m_SF2:
          MmiGotoxy(0,6); MmiPuts("ESC,ENTER  �������");
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

        PassWm=0;


        flag_esc=1;
        if(mode_hst == 0 )
        {
m0_f1:
main_menu:


m_120p:

         if(Password_m != 0)
          if(PassWm != Password_m)
          {
           pass_ret=20;
           goto m_pass;
          }

          PageD=0;
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);
          f_prepare_t (&adate00);
          sw_mmi=120;

#if(AIR_SW != 0)
          Out_off(OUT4);  // Air switch off
#endif
          PassW=0;

            //27.10.2021 YN
            #if defined(N_Pipes)
              if(valve_mode && valve_modeL) 
              {
                MmiGotoxy(0,0);  MmiPrintf("��� %d-%d-%d.   ����",n_ASN,n_pipe_h,n_pipe_l);
              }
              else if(valve_mode==0)
              {
                MmiGotoxy(0,0);  MmiPrintf("��� %d-%d.   ����",n_ASN,n_pipe_l);
              }
              else
              {
                MmiGotoxy(0,0);  MmiPrintf("��� %d-%d.   ����",n_ASN,n_pipe_h);
              }
            #else
              //02.02.2022 YN
              #if defined(GAZAVOZ)
                MmiGotoxy(0,0);  MmiPrintf("            ����              ");
              #else
                MmiGotoxy(0,0);  MmiPrintf("��� %d.   ����",n_ASN);
              #endif
            #endif
            //MmiGotoxy(0,0);  MmiPrintf("��� %d.   ����",n_ASN);

            MmiGotoxy(0,2);


#if defined(BIO_1)

  MmiPuts("1  ������ �������������");
            MmiGotoxy(0,2);    MmiPuts("2  �������� �������� ");
#else
            //02.02.2022 YN
            #if defined(GAZAVOZ)
              MmiPuts("1  ������ ���");
            #else
              MmiPuts("1  ������ ��������������");
            #endif
//          MmiGotoxy(0,2);    MmiPuts("2  �������� ");
//            MmiGotoxy(0,2);    MmiPuts("            ");
            MmiGotoxy(0,4);    MmiPuts("2  ��������� �����������");
#endif

//          MmiGotoxy(0,2);    MmiPuts("2  ������ �� ");
            MmiGotoxy(0,6);    MmiPuts("3  �������� ������� �������");
            MmiGotoxy(0,8);    MmiPuts("4  ��������� �������");
#if !defined(BIO_1)
            MmiGotoxy(0,10);    MmiPuts("5  ���� ���� �������");
#endif

            //02.02.2022 YN
            #if defined(GAZAVOZ)
              MmiGotoxy(0,10);    MmiPuts("5  ������ �������� �������  ");
            #endif

            MmiGotoxy(0,15);    MmiPuts("ESC  �������");
        }
        else
        {
           f_clr_scr_MMI();
           f_prn_begin();
        }

        break;
       }

    //02.02.2022 YN
    #if !defined(GAZAVOZ)   
       else if (key=='-')
        {
          flag_esc=0;
          if(PageD==1)
          { // �������� ��������� OFP
             f_OFP_WR(0,7,1);
             INP_OFP=0xc0ff;
             key=PASS;
          }
          break;
        }
//     else if (key=='0')
       else if (key=='5')
        {
          flag_esc=0;
          if(PageD==1)
          { // ��������� ��������� OFP
             f_OFP_WR(0,7,2);
             INP_OFP=0x0;
          }
          break;
        }
    #endif

       else if(key==PASS)
        {  // ����������� ���� � �������

         if( id_ok ==0) break;
         if( ((FL_err|CRC_err) == 0) || ( flag_esc == 0 ))
         {
          if(PageD==0)
            {

              //02.02.2022 YN
              #if defined(GAZAVOZ)

                //16.02.2022 YN
                if( !flagFirstTurnOn )
                {
                  MmiGotoxy(0,7);  MmiPrintf("       �������� �������...       ");
                }
                else
                {
                  MmiGotoxy(0,6);  MmiPrintf("����� ���.  :%9.1f ��",s_MVD[0].MassI);
                  MmiGotoxy(0,8);  MmiPrintf("����� ���.  :%9.1f � ",s_MVD[0].VolI);
                  MmiGotoxy(0,10); MmiPrintf("���������   :%7.1f ��/�3  ",s_MVD[0].Dens);
                  MmiGotoxy(0,12); MmiPrintf("����������� :%7.1f C      ",s_MVD[0].Temp);
                }
              #else
                MmiGotoxy(0,3);  MmiPrintf("�����       :%9.1f ��",s_MVD[0].MassI);
                MmiGotoxy(0,4);  MmiPrintf("�����       :%9.1f � ",s_MVD[0].VolI);

                MmiGotoxy(0,6);  MmiPrintf("���������   :%7.1f ��/�3  ",s_MVD[0].Dens);
                MmiGotoxy(0,7);  MmiPrintf("����������� :%7.1f C      ",s_MVD[0].Temp);

                MmiGotoxy(0,9);   MmiPrintf("-------- ������� --------  ");
              
                //10.06.2021 YN
                #if (PressureDrop == 1)
                  MmiGotoxy(0,10);  MmiPrintf("����������� :%7.2f C      ",s_MVD[0].TempR);
                  MmiGotoxy(0,11);  MmiPrintf("��������    :%7.4f ���    ",s_MVD[0].Press);
                  MmiGotoxy(0,12);  MmiPrintf("�������     :%7.4f ���    ",Press_Drop);
                #elif (PressureDrop == 2)
                  MmiGotoxy(0,10);  MmiPrintf("����������� :%7.2f C      ",s_MVD[0].TempR);
                  MmiGotoxy(0,11);  MmiPrintf("��������    :%7.4f ���    ",s_MVD[0].Press);
                  if(Filter_for_slave) 
                  {
                    MmiGotoxy(0,12);  MmiPrintf(" ��������! ��������� �������. ");
                    MmiGotoxy(0,13);  MmiPrintf("   ������� : %7.4f ���    ",P_diff);
                  }
                  else
                  {
                    MmiGotoxy(0,12);  MmiPrintf("����.�� �-��:%7.4f ���    ",P_before);
                    MmiGotoxy(0,13);  MmiPrintf("�.����� �-��:%7.4f ���    ",P_after);
                  }
                #else
                  MmiGotoxy(0,11);  MmiPrintf("����������� :%7.2f C      ",s_MVD[0].TempR);
                  MmiGotoxy(0,12);  MmiPrintf("��������    :%7.4f ���    ",s_MVD[0].Press);
                #endif

              #endif  

            }

      //02.02.2022 YN
      #if !defined(GAZAVOZ)

          else if(PageD==1)
            {  // OFP
         if( ((FL_err|CRC_err) == 0) || ( flag_esc == 0 ))
          {

           MmiGotoxy(0,0);  MmiPrintf("��� %d.",n_ASN);
           MmiGotoxy(0,5);     MmiPuts("   ���������� ������������   ");
           if(OFP[0].status==0)
           {
            MmiGotoxy(0,6);MmiPuts( str_empt );
            MmiGotoxy(0,10);MmiPuts( str_empt );
            MmiGotoxy( 10 ,6);         MmiPuts("�������� ");
            MmiGotoxy(0,7);MmiPuts( str_empt );
           }
           else if((INP_OFP & 0xC000) == 0xC000)
           {
            MmiGotoxy(0,6);MmiPuts( str_empt );
            MmiGotoxy(0,8);MmiPuts( str_empt );
            MmiGotoxy(10,8);    MmiPuts("��������");
            MmiGotoxy(0,10);MmiPuts( str_empt );
            MmiGotoxy(0,10);MmiPuts("5 - ����.�����");
           }
           else
           {
           MmiGotoxy(0,6);MmiPuts( str_empt );
           MmiGotoxy(3,6);
            if(INP_OFP & 0x8000)      MmiPuts("5-�� ��������� �������" );
            else if(INP_OFP & 0x4000) MmiPuts("2-� ��������� �������" );
                                else  MmiPuts("������� �� ����������");

           MmiGotoxy(0,7);MmiPuts( str_empt );
           MmiGotoxy(0,8);MmiPuts( str_empt );
           MmiGotoxy(0,8);
            if(INP_OFP & 0x80) MmiPuts("GND   : ������." );
            else   MmiPuts("GND   : ������." );


           MmiGotoxy(0,10);MmiPuts( str_empt );
           MmiGotoxy(0,10);

            if((INP_OFP & 0xc000) && (INP_OFP & 0x80))
            {
              if(INP_OFP & 0x40)
              {
                MmiPuts("�����.: ������." );
              }
              else
              {

                MmiPuts("�����.: ������." );
           /*
                EkdMoveToXY(0,13);EkdPrintf("WET PROBE(S): " );
                EkdMoveToXY(0,14);
                 if((INP_OFP & 0x1)==0) EkdPrintf(" N1");
                 if((INP_OFP & 0x2)==0) EkdPrintf(" N2");
                 if((INP_OFP & 0x4)==0) EkdPrintf(" N3");
                 if((INP_OFP & 0x8)==0) EkdPrintf(" N4");
           */
              }
            }
            else
            {
                MmiPuts("�����.: ������." );
            }

           }
          }
            }
      #endif

           else
           {
  MmiGotoxy(0,3) ; MmiPrintf("PageD = %d",PageD);
           }
         }
          GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
          MoveToXY(4,15);
          if((WD_PMP_Fl != 0) && (flag_Slv != 0))
            MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d  Link " ,day,month,year-2000 ,hour,min,sec);
          else
            MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d       " ,day,month,year-2000 ,hour,min,sec);
        }

        break;
 /*========================================*/
    case 11:  /*���� ������ ����� ��� ��������� ���������� */
       n_adc_mm=0;
       if(key==ESC)    /* ������� � ���� M3, ��������� ������� */
       {
         goto m_m3;
       }
       else if(key=='1')  // ������� ������ #1
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=0;
        }
       else if(key=='2')  // ������� ������ #2
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=15;
  //       mmi_prm=max_par/5;
        }
       else if(key=='3')   // ������� ������ #3
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=30;
//         mmi_prm=(max_par*2)/5;
        }
       else if(key=='4')  // ������� ������ #4
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
//         mmi_prm=(max_par*3)/5;
         mmi_prm=45;
//         mmi_prm=(max_par*3)/5;
        }
       else if(key=='5')  // �������������� ������
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=60;
//         mmi_prm=(max_par*4)/5;
        }
       else if(key=='6')  // �������������� ������
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=75;
//         mmi_prm=(max_par*4)/5;
        }
       else break;
       flag_chg=0;
       nn_chg=0;

       f_clr_scr_MMI();
       SetDisplayPage(EmptPage);    // ������ ��������
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
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"Enter\"���. ");
       }
       else
       {
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\",\"F3\",\"ESC\",\"Enter\"         ");
         MmiGotoxy(2,nn_chg);  MmiPuts("#");
       }
       sw_mmi=14;
       break;
 /*========================================*/
    case 14:/* �������� �� 6 ���������� */
       if(key==Sht_F2)    /* ���������� ��������� � EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptPage);    // ������ ��������
        MmiGotoxy(0,1);    MmiPuts("���������� ������ � EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    ���������");
        MmiGotoxy(0,4);    MmiPuts("ESC   �� ���������,����������");
        sw_mmi=15;
        break;
       }
       if(key==Sht_F1)    /* ���� COR */
       {
//        f_init_COR(0);
//        f_init_COR(1);
        f_clr_scr_MMI();
        SetDisplayPage(EmptPage);    // ������ ��������
        goto par_out14;
       }
       if(key==Sht_F3)    /* ������ ������ �� EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptPage);    // ������ ��������
        MmiGotoxy(0,1);    MmiPuts("������ ������ �� EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    ��������� ");
        MmiGotoxy(0,4);    MmiPuts("ESC   �� ���������,����������");
        sw_mmi=16;
        break;
       }
       if(flag_chg==0)
       {
         if(key==ESC)    /* ������� � ���� ������ ����� ��� ���������*/
         {
          goto m_m3_3;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=n_mmi_str_1)
           {
            mmi_prm -=n_mmi_str_1;
            f_clr_scr_MMI();
            SetDisplayPage(EmptPage);    // ������ ��������
            goto par_out14;
           }
           else
           {
            mmi_prm = 0;
            f_clr_scr_MMI();
            SetDisplayPage(EmptPage);    // ������ ��������
            goto par_out14;
           }
         else if((key== F3 )&& (mmi_prm < (max_par-n_mmi_str_1)) )
         {
          mmi_prm +=n_mmi_str_1;
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
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
         if(key==ESC)    // ������� ����� ��������������
         {
          flag_chg=0;
          if((ds_list[0].descr == list2_dsr)&&
               (ds_list[0].ind == 0 ))
          {
//          f_init_COR(0);
//          f_init_COR(1);
            f_clr_scr_MMI();
       //   SetDisplayPage(EmptPage);    // ������ ��������
            goto par_out14;
          }
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
            SetDisplayPage(EmptPage);    // ������ ��������
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
         if(key==ENTER)    // �������������� ���������
         {
          if(PassW != Password)
          {
           pass_ret=0;
m_pass:
           MmiGotoxy(1,1);
           f_clr_scr_MMI();
#if defined(MMI_NEW)
          SetDisplayPage(2); // ������ ��������
#endif
           MmiPuts("������� ������:" );
           sprintf( fst_str,"******");

#if defined(MMI_ICP)
          SetDisplayPage(17);  // ���� ������
#endif

           sw_mmi=121;
           fst_n=7;
           sw_fst=1;
           MmiGotoxy(11,3);
//         MmiGotoxy(15,3);
           break;
          }

          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(2,nn_chg);  MmiPuts(">");
          MoveToXY(NumPlace,nn_chg);

          PrintMmiOp(&ds_list[nn_chg+mmi_prm],0);
          fst_n=8;
          sw_fst=1;
          break;
         }
       }
       if(key==DATA)    // ���� ���������� ������
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
    case 15:/* ���������� ������ � EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* ������� � ����������� ���������� */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
          goto par_out14;
         }
         else if(key=='1')    // ��������� ������
         {

           if(f_wrt_eee()<0)
           {
              f_wr_evt(evt_we_err);
              MmiGotoxy(0,5);   MmiPuts("������ ��� ���������� ������");
           }
           else
           {
              f_wr_evt(evt_we);
              MmiGotoxy(0,5);   MmiPuts(" ������ ��������� �������");
           }
              MmiGotoxy(0,6);   MmiPuts("      Enter - ����������");
         }
         break;
 /*========================================*/
    case 16:/* ������ ������ �� EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* ������� � ����������� ���������� */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
          goto par_out14;
         }
         else if(key=='1')    // ���������
         {

           f_chk_EEE_CRC();
           if(f_rd_eee()<0)
           {
              f_wr_evt(evt_re_err);
              MmiGotoxy(0,5);   MmiPuts("������ ��� ������ ������");
              CRC_err=1;
           }
           else
           {
              f_wr_evt(evt_re);
              MmiGotoxy(0,5);   MmiPuts("  ������ ������� �������");
              CRC_err=0;
           }
           f_rd_cor();

           MmiGotoxy(0,6);   MmiPuts("      Enter - ����������");
         }
         break;
 /*========================================*/
    case 18:
       if( f_timer(zero_time,Time_zeroing ))
       {
             f_clr_scr_MMI();
             MoveToXY(3,3);
            MmiPrintf(" ������� ����������");
          fl_zeroing=0;
          ff_serv=NULL;
          f_wr_evt(evt_MVD_CL_TM);
          State_SLV = Zer_err;
         f_reg_cmn(Zer_err_cmn);
          goto m_SF2;
       }
          if(ff_serv==NULL)
          {
           if(fl_zeroing==0)
           {
             f_clr_scr_MMI();
             MoveToXY(1,3);
         MmiPrintf("���������� ��������� �������");
         MmiGotoxy(0,1);MmiPrintf("D=%6.1f ��/�3; t =%6.2f C ",s_MVD[0].Dens,s_MVD[0].TempR);

         State_SLV = Zer_end;
         f_reg_cmn(Zer_end_cmn);

//                |                              |
             f_wr_evt(evt_MVD_CL_OK);
             goto m_SF2;
           }
           fl_rd_err=0;
           sw_mvd_m1=0;  // ���.��������

          //08.02.2022 YN
          #if (Shtray==2)  //Promass
            ff_serv=f_MVD_M3_Pr;
          #else
            ff_serv=f_MVD_M3;
          #endif

          }

         MmiGotoxy(0,1);MmiPrintf("D=%6.1f ��/�3; t =%6.2f C ",s_MVD[0].Dens,s_MVD[0].TempR);

         GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
         MoveToXY(4,6);
         MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
         break;
 /*========================================*/
    case 120:  // �������� ����

       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
mm00:      sw_mmi=0;
           PassWm=0;

           PageD=0;
           SetDisplayPage(ZeroPage);
           f_clr_scr_MMI();
           f_prn_begin();
           break;
       }
#if defined(BIO_1)
       else if((key== '/') && (id_ok !=0) ) // Sht_2  ��������
       {
        flag_prok=1;
        strcpy(mode_prok,prok_ka);
        Flag_Low=-1;
        goto m1_1;
       }
       else if((key== '2') && (id_ok !=0) ) // 2  �������� ��������
       {
mm2_b0:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
mm2_b:
            MmiGotoxy(0,0);    MmiPuts(" ���� 2. ��������� ��������.");

            MmiGotoxy(0,1);    MmiPuts("0..3 ����� ����������  ");
//           MmiGotoxy(0,2);    MmiPuts("4 ����� ������         ");
            MmiGotoxy(0,2);    MmiPuts("4 �������� ���������� ������  ");

       itmp= OUT_or & ( CL1_SRC | CL2_SRC);

       MmiGotoxy(0,4);
       if ( itmp == CL1_SRC   )
              MmiPuts(" ���������� ������� 1  ");
       else if ( itmp == CL2_SRC   )
              MmiPuts(" ���������� ������� 2  ");
       else if ( itmp == (CL1_SRC | CL2_SRC)  )
              MmiPuts(" ���������� ������� 1,2");
       else
              MmiPuts(" ������� ���������     ");

       MmiGotoxy(0,5);
          MmiPrintf("�������� ����.������ %6.0f �",T_Pmp_delay/1000.);
/*
       if(OUT_Pmp & Pump_MDB)
           MmiPuts(" ����� ������� ����������    ");
       else
           MmiPuts(" ����� ���������� ��� �������");
*/

            MmiGotoxy(0,6);    MmiPuts("ESC  �������");
         sw_mmi=130;
         break;
       }
#else
       else if((key== '2') && (id_ok !=0) ) // 2  ��������
       {
 /*
        flag_prok=1;
        strcpy(mode_prok,prok_ka);
        Flag_Low=-1;
        goto m1_1;

 */

        goto m_4_4_1;

       }
#endif

       else if((key== '1') && (id_ok !=0) ) //  1  ������ ��������������
       {
//       sw_mmi=190;
#if defined(BIO_1)
 /// nothing
#else
                   flag_prok=0;
#endif
        strcpy(mode_prok,otpusk);
        Flag_Low=-1;
m1_1:
        if(mode_hst == 0 ) //  1  ������ ��������������
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

#if( AIR_SW != 0)
                 if(valve_mode > 0)
               Out_on(OUT4);  // Air switch on
#endif

                 SetDisplayPage(EmptPage);

m_m5_01:
         f_clr_scr_MMI();

    MmiGotoxy(0,0);

#if defined(BIO_1)
    MmiPrintf("���� 1.%s �������������.",mode_prok);
#else
    //02.02.2022 YN
    #if defined(GAZAVOZ)
      MmiPrintf("    ���� 1. ������ ���        ");
    #else
      MmiPrintf("��� %d.%s ��������������.",n_ASN,mode_prok);
    #endif

#endif

    if((dose_dlvr > 0) && (flag_prn_mass == 0))
    {
        MmiGotoxy(0,2);
        if( (valve_mode > 0) && (valve_modeL > 0 ))
        {
          if( Flag_Low == 0)
            MmiPuts("���� �����.������ ");
          else  if( Flag_Low == 1)
            MmiPuts("���� ����. ������ ");
        }

        //02.02.2022 YN
        #if defined(GAZAVOZ)
          else
          {
            if(fillingFlag == WHOLE)
            {
              MmiPuts("����: �� �����������          ");
            }
            else
            {
              MmiPuts("����  ");
              if ( Flag_mass != 0 )
                MmiPrintf("%8.2f ��    ",dose_dlvr);
              else
                MmiPrintf("%8.2f �    ",dose_dlvr);
            }
          }
        #else
          else MmiPuts("����  ");
          if ( Flag_mass != 0 )
            MmiPrintf("%8.2f ��    ",dose_dlvr);
          else
            MmiPrintf("%8.2f �    ",dose_dlvr);
        #endif

    }

 if((id_ok !=0)&& (mode_hst == 0) )
 {
      //    f_prn_MassSt_dlv();

    if( (valve_mode > 0) && (valve_modeL > 0 ))
    {
          //27.10.2021 YN
          #if defined(N_Pipes)
            MmiGotoxy(0,4);    MmiPrintf("1 ������ ���� ����.������(%d)",n_pipe_h);
            MmiGotoxy(0,6);    MmiPrintf("2 ������ ���� ����.������(%d)",n_pipe_l);
          #else
            MmiGotoxy(0,4);    MmiPuts("1 ������ ���� �������� ������");
            MmiGotoxy(0,6);    MmiPuts("2 ������ ���� �������  ������");
          #endif

          if((flag_prn_mass != 0) && (dose_dlvr > 0) )
          {  MmiGotoxy(0,8);
            if( Flag_Low == 0)
               MmiPuts("4 ���������� �����.:");
            else  if( Flag_Low == 1)
               MmiPuts("8 ���������� ����.:");

              if ( Flag_mass != 0 )
                MmiPrintf("�=%8.2f ��    ",dose_dlvr);
              else
                MmiPrintf("�=%8.2f �    ",dose_dlvr);

            MmiGotoxy(0,10);
        //    MmiGotoxy(15,5);
            MmiPrintf("�=%8.2f ��,%8.2f � ",s_MVD[0].MassT,s_MVD[0].VolT);
          }
          else if(dose_dlvr > 0)
          {
            MmiGotoxy(0,8);
            if( Flag_Low == 0)
               MmiPuts("4 ����� ������� �����");
            else if( Flag_Low == 1)
               MmiPuts("8 ����� ������ ����� ");
          }


    }
    else
    {
          //27.10.2021 YN
          #if defined(N_Pipes)
            if(valve_mode) 
            {
              MmiGotoxy(0,4);    MmiPrintf("1 ������ ����. ���� N%d ",n_pipe_h);
            }
            else
            {
              MmiGotoxy(0,4);    MmiPrintf("1 ������ ����. ���� N%d ",n_pipe_l);
            }
          #else

            //02.02.2022 YN
            #if defined(GAZAVOZ)
              MmiGotoxy(0,4);    MmiPuts("1 ������ ���� ������� ��� ");
              MmiGotoxy(0,6);    MmiPuts("2 ������ �� �����������   ");
            #else
              MmiGotoxy(0,4);    MmiPuts("1 ������ ���� ");
            #endif
          #endif

          if((flag_prn_mass != 0)   && (dose_dlvr > 0))
          {  
              //02.02.2022 YN
              #if defined(GAZAVOZ)
                if(fillingFlag == WHOLE)
                {
                  MmiGotoxy(0,2);
                  MmiPrintf("�=%8.2f ��,%8.2f � ",s_MVD[0].MassT,s_MVD[0].VolT);
                  MmiGotoxy(0,10);
                  MmiPuts("4 ���������� �� �����������   ");
                }
                else
                {
                  MmiGotoxy(0,2);
                  MmiPrintf("�=%8.2f ��,%8.2f � ",s_MVD[0].MassT,s_MVD[0].VolT);
                  MmiGotoxy(0,10);
                  MmiPuts("4 ���������� :");
                  if ( Flag_mass != 0 ) MmiPrintf("�=%8.2f ��    ",dose_dlvr);
                  else MmiPrintf("�=%8.2f �    ",dose_dlvr);
                }
              #else
                MmiGotoxy(0,8);
                MmiPuts("4 ���������� :");
                if ( Flag_mass != 0 ) MmiPrintf("�=%8.2f ��    ",dose_dlvr);
                else MmiPrintf("�=%8.2f �    ",dose_dlvr);
                MmiGotoxy(0,5);
                MmiPrintf("�=%8.2f ��,%8.2f � ",s_MVD[0].MassT,s_MVD[0].VolT);
              #endif
          }
          else if(dose_dlvr > 0)
          {
              //02.02.2022 YN
              #if defined(GAZAVOZ)
                MmiGotoxy(0,10);
                if(fillingFlag == WHOLE) MmiPuts("4 ����� �� �����������"); 
                else MmiPuts("4 ����� ");
              #else
                MmiGotoxy(0,8);
                MmiPuts("4 ����� ");
              #endif
          }
    }
 }
//--------------------------
     if( Flag_Low < 0)
     {
       f_prn_no_sig_H( 10) ;
       f_prn_no_sig_L( 11) ;
     }
    else if( Flag_Low == 0)
       f_prn_no_sig_H(10) ;
    else if( Flag_Low == 1)
       f_prn_no_sig_L(10) ;

//--------------------------

#if defined(BIO_1)

          MmiGotoxy(0,6);    MmiPuts("ESC �������");
#else
        
      //02.02.2022 YN
      #if defined(GAZAVOZ) 
        MmiGotoxy(0,13);
        MmiPuts("0-��������� ��������");
      #else 
        if( ( valve_mode > 0) && ( Flag_Low != 1)  )
        {
            MmiGotoxy(0,13);
            MmiPuts("0-���������.���.���.");
        }
      #endif

         MmiGotoxy(0,15);
            MmiPuts("ESC �������");

#endif
         sw_mmi=190;
         break;
       }
       else if(key== '3') // 3  �������� ������� �������
       {
m_m2:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

            i= f_get_max_n_arch();
            ar_str_ptr=f_get_fst_stor();
//            MmiGotoxy(0,0);    MmiPuts(" ���� 3.������ �������.");

            //02.02.2022 YN
            #if defined(GAZAVOZ)
              MmiGotoxy(0,0);  MmiPrintf("      ������ �������. ");
              MmiGotoxy(0,2);    MmiPrintf("%4d  ",i);
            #else
              MmiGotoxy(0,0);  MmiPrintf("��� %d. ������ �������. ",n_ASN);
              MmiGotoxy(0,1);    MmiPrintf("%4d  ",i);
            #endif

            j=i%100;
            if((j<=20)&& (j>5))
              MmiPrintf("�������");
            else
            switch(i%10)
            {
             case 1:
             MmiPrintf("������");
             break;

             case 2:
             case 3:
             case 4:
             MmiPrintf("������");
             break;

             case 0:
             case 5:
             case 6:
             case 7:
             case 8:
             case 9:
             MmiPrintf("�������");
             break;
            }

   tdat = localtime( &ar_str_ptr->time );
//   MmiPrintf(" � %02d.%02d.%02d %02d:%02d:%02d",
//   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
   MmiPrintf(" � %02d.%02d.%02d",
   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100);

            //02.02.2022 YN
            #if defined(GAZAVOZ)
              MmiGotoxy(0,4);    MmiPuts(" �������� ������� �������");
              MmiGotoxy(0,6);    MmiPuts("1  �� ����");
              MmiGotoxy(0,8);    MmiPuts("2  �� ������ ������");
              MmiGotoxy(0,10);    MmiPuts("3  ��������� ������");

              //10.02.2022 YN
              MmiGotoxy(0,12);    MmiPuts("4  ��������� �������� ���");
              
              MmiGotoxy(0,15);    MmiPuts("ESC  �������");
            #else
              MmiGotoxy(0,2);    MmiPuts(" �������� ������� �������");
              MmiGotoxy(0,3);    MmiPuts("1  �� ����");
              MmiGotoxy(0,4);    MmiPuts("2  �� ������ ������");
              MmiGotoxy(0,5);    MmiPuts("3  ��������� ������");
              MmiGotoxy(0,6);    MmiPuts("ESC  �������");
            #endif

         PassW=0;
         sw_mmi=140;
         break;
       }
       else if(key== '4') // 4  ��������� �������
       {
m_m3:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� 4. ��������� �������.");
  //MmiGotoxy(0,0);  MmiPrintf("��� %d. ��������� �������.",n_ASN);
            MmiGotoxy(0,2);    MmiPuts("1  ������ ���������");
            MmiGotoxy(0,4);    MmiPuts("2  ����������  ���������");
            MmiGotoxy(0,6);    MmiPuts("3  ��������/���� ����������");
            //02.02.2022 YN
            #if defined(GAZAVOZ)
              MmiGotoxy(0,8);    MmiPuts("4  �����, ����");
            #else
              MmiGotoxy(0,8);    MmiPuts("4  ������ �������");
              MmiGotoxy(0,10);    MmiPuts("5  �����, ����");
            #endif

            MmiGotoxy(0,15);    MmiPuts("ESC  �������");
         sw_mmi=150;
         PassW=0;
       }

        //02.02.2022 YN
        #if defined(GAZAVOZ) 
          else if(key == '5') // 5 ������ �������� �������
          {

            if(PassW != Password)
            {
              pass_ret=19;
              goto m_pass;
            }
m_19:
            SetDisplayPage(EmptPage);    // ������ ��������
            f_clr_scr_MMI();
            OUT_VAR_c=0xffff;
            MVD_fn[0]=MVD_WR_F;
            s_MVD[0].r_addr=5138; // ���������� �����
            s_MVD[0].f=cutoff_on_M;
            sw_mmi = 50;  
            break;
          }
        #else
          else if(key== '5') // 5  ���� ���� ������� ����������
          {
            sw_mmi=200;
            break;
          }
        #endif

       /*else if(key== '+') // Sht_5  ���� ���� ������
       {
          sw_mmi=210;
          break;
       }*/
       else if(key== '6') // 6 ����������� ���������� ������
       {
m_m6:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
// MmiGotoxy(0,0); MmiPrintf(" ��������� ���������� ������:");
    //02.02.2022 YN
    #if defined(GAZAVOZ)
      MmiGotoxy(0,0);  MmiPrintf("    ��������� ������:    ");
    #else
      MmiGotoxy(0,0);  MmiPrintf("��� %d. ��������� ������:",n_ASN);
    #endif

    MmiGotoxy(0,1); MmiPrintf("    I7017C, �������� ���");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625


// MmiGotoxy(0,4); MmiPrintf(" ��������� ���������� ������:");

//_fmemset( &ADC_c[0],0xff,sizeof(ADC)); // ������� ������ ������
  INP_VAR_c=0xffff;
         sw_mmi=25;
         break;

       }
       else if(key== '7') // 7 ����������� �����.�������
       {
m_m7:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
   MmiGotoxy(0,0); MmiPrintf("��� %d. ��������� �������:",n_ASN);
   MmiGotoxy(0,6);

#if defined(BIO_1)
  MmiPuts(" ESC-�������,1...5 - ��������");
#else
  MmiPuts(" ESC-�������,1...8 - ��������");
#endif
         OUT_VAR_c=0xffff;
         sw_mmi=28;
         break;

       }
       else if(key== '8') // 8 ������ sw
       {
m_m8:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

      //02.02.2022 YN
      #if defined(GAZAVOZ)
        MmiGotoxy(0,0);   MmiPrintf(" VER N 1.27 02 Feb 2022 ");
      #else
        MmiGotoxy(0,0);   MmiPrintf("��� %d. VER %s",n_ASN,sw_ver);
      #endif

      MmiGotoxy(0,2);   MmiPrintf("   MD5 counting ...");
      MmiGotoxy(0,6);   MmiPuts(" ESC   - ������� � ����");
         tm_md=TimeStamp;
         sw_mmi=271;
         break;
       }
       else if(key== '-' )// SHT_9  ��������� �������
       {
m_m9:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            //02.02.2022 YN
            #if defined(GAZAVOZ)
              MmiGotoxy(0,0);  MmiPrintf(" ��������� �������.");
            #else
              MmiGotoxy(0,0);  MmiPrintf("��� %d. ��������� �������.",n_ASN);
            #endif

//08.02.2022 YN
 #if(Shtray==0)
            MmiGotoxy(0,1);    MmiPuts("1 ��������� ��������� �������");
            MmiGotoxy(0,2);    MmiPuts("2 ��������� ��������� �������");
            MmiGotoxy(0,3);    MmiPuts("3 ��������� ���������");            
 #endif
 #if(Shtray==1)
            MmiGotoxy(0,1);    MmiPuts("1 ��������� ��������� �������");
//            MmiGotoxy(0,2);    MmiPuts("2 ��������� ��������� �������");
            MmiGotoxy(0,3);    MmiPuts("3 ��������� ���������");            
 #endif 
#if(Shtray==2)
            MmiGotoxy(0,1);    MmiPuts("1 ����� ��������� �������");
            MmiGotoxy(0,2);    MmiPuts("2 ����. ��������� �������");
            MmiGotoxy(0,3);    MmiPuts("3 ����� ��������� �������");            
            MmiGotoxy(0,4);    MmiPuts("4 ����. ��������� �������");
            MmiGotoxy(0,5);    MmiPuts("5 ����� ���������");
            MmiGotoxy(0,6);    MmiPuts("6 ����. ���������");                        
#endif 

  //        MoveToXY(0,4);   MmiPrintf("��������� �����:     %.6f",s_MVD[0].f);
  //        MoveToXY(0,5);   MmiPrintf("��������� ������:    %.6f",s_MVD[0].f);
  //        MmiGotoxy(0,6);    MmiPuts("ESC  �������");

         Flag_f_corr=0;
         sw_mvd_m1=31;
         tm_mvd=TimeStamp;
         ff_serv=f_MVD_M1f;
         sw_mmi=125;
         break;
       }
       else if(key== '9' )// 9  ���� �������
       {
m_m9s:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            #if defined(GAZAVOZ)
              MmiGotoxy(0,0);  MmiPrintf("     ���� �������.         ");
            #else
              MmiGotoxy(0,0);    MmiPrintf("��� %d. ���� �������.",n_ASN);
            #endif
            MmiGotoxy(0,1);    MmiPuts("1 ���� ��������� �������");

            //17.02.2022 YN MmiGotoxy(0,2);    MmiPuts("2 ���� ��������� �������");
  
  //        MoveToXY(0,4);   MmiPrintf("��������� �����:     %.6f",s_MVD[0].f);
  //        MoveToXY(0,5);   MmiPrintf("��������� ������:    %.6f",s_MVD[0].f);
            MmiGotoxy(0,6);    MmiPuts("ESC  �������");

         Flag_f_corr=0;
         sw_mvd_m1=31;
         tm_mvd=TimeStamp;
         ff_serv=f_MVD_M1s;
         sw_mmi=127;
         break;
       }
       break;
 /*========================================*/
    case 121: // // ���� ������ �� ��������� ������
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������

 m121:
          switch(pass_ret)
          { // ������ �� ������
          case 0:  goto par_out14;
          case 1:  goto m_m9;
          case 2:  goto m_m9;
          case 3:  goto m_m3;
          case 5:  goto m_m9s;
          case 6:  goto m_m9s;
          case 7:  goto m_m9;

          //17.02.2022 YN
          case 8:  goto m_m9;
          case 9:  goto m_m9;
          case 10:  goto m_m9;

          case 19: goto main_menu;
          case 20: goto m_main;

          default:
                goto main_menu;
          }
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&ltmp);

         if(pass_ret < 20)
         {
          if(ltmp == Password)
                PassW=Password;
          else goto m_pass;
         }
         else
         {
          if(ltmp == Password_m)
                PassWm=Password_m;
          else goto m_pass;
         }


          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
          switch(pass_ret)
          { // ������ ������ ���������
          case 0:  goto par_out14;
          case 1:
                sw_mmi=125;
                goto m_m9_1;
          case 2:
                sw_mmi=125;
                goto m_m9_2;
          case 7:
                sw_mmi=125;
                goto m_m9_3;

//17.02.2022 YN
          case 8:
                sw_mmi=125;
                goto m_m9_4;
          case 9:
                sw_mmi=125;
                goto m_m9_5;
          case 10:
                sw_mmi=125;
                goto m_m9_6;

          case 3:
                sw_mmi=162;
                goto m_m3_6_1;
          case 5:
                sw_mmi=127;
                goto m_m9s_1;

          //17.02.2022 YN
          /*case 6:
                sw_mmi=127;
                goto m_m9s_2;*/

          case 19: 
                goto m_19;
          case 20:
                sw_mmi=0;
                goto m_120p;
          default:
                goto main_menu;
          }
        }
       else if(key==DATA_ESC)
        {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
          goto m121;
        }

 /*========================================*/

  //02.02.2022 YN
  #if defined(GAZAVOZ)
    case 50:
      // ������ �������� �������
      MmiGotoxy(0,0); MmiPrintf("����. ������ �������� ������� ");
      MmiGotoxy(0,2); MmiPrintf("������ 1 ��� ����/���� �������");
      if(key==ESC)    /* ������� � ���� */
      {
        MVD_fn[0]=MVD_WR_F;
        s_MVD[0].r_addr=5138; // ������ �����
        s_MVD[0].f=cutoff_off_M;
        goto m0_f1;
      }
      else if(key== '1')
      {
        OUT_VAR ^= OUT2;
      }
      else
      {
        if(OUT_VAR & OUT2)
        {
          MmiGotoxy(0,3); MmiPrintf(" ��������� �������:   ������  ");
        }
        else
        {
          MmiGotoxy(0,3); MmiPrintf(" ��������� �������:   ������  ");
        }
      }

      MmiGotoxy(0,5);   MmiPrintf("����� ���. %10.3f ��",s_MVD[0].MassI);
      MmiGotoxy(0,6);   MmiPrintf("����� ���. %10.3f � ",s_MVD[0].VolI);

      MmiGotoxy(0,8);   MmiPrintf("�����������    %7.2f C        ",s_MVD[0].Temp);
      MmiGotoxy(0,9);   MmiPrintf("���������      %7.2f ��/�3   ",s_MVD[0].Dens);

      MmiGotoxy(0,11);  MmiPrintf("������       %8.1f �/�       ",s_MVD[0].FlowV);

      MmiGotoxy(0,14);    MmiPuts("ESC  ����");

    break;
  #endif

 /*========================================*/

    case 122:
 //  ����������� ���������,�����������,�������
 //  ������� ��������.
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {

         //08.02.2022 YN
         #if(Shtray==2)
          s_MVD[0].r_addr=5138;  //�������� �������
         #else
          s_MVD[0].r_addr=195; // ���� ����.����.
         #endif

         s_MVD[0].f = cutoff_off_M;
         MVD_fn[0]=MVD_WR_F;;


         State_SLV = Mod_flow_e;
         f_reg_cmn(Mod_flow_e_cmn);

         goto main_menu;
       }
       else if(key==PASS)
       {
         f_prn_den_t();
       }
       else if (key==DEL) //Sht_4
       {
          //17.02.2022 YN
          s_MVD[0].MassT = 0;
          s_MVD[0].VolT = 0;
          /*
          MVD_fn[0]=MVD_WR_C;
          s_MVD[0].r_addr=3; // Reset all totalizers
          s_MVD[0].i=1;*/
       }
       else if (key=='*') //Sht_1
       {
          MVD_fn[0]=MVD_WR_F;
          s_MVD[0].r_addr=5138; // ���������� �����
          s_MVD[0].f=cutoff_on_M;
       }
       else if (key=='/') //Sht_2
       {
          MVD_fn[0]=MVD_WR_F;
          s_MVD[0].r_addr=5138; // ������ �����
          s_MVD[0].f=cutoff_off_M;
       }
       else if(key==Sht_F1) 
       {
          if(flg_ch==3)
          {
            MVD_fn[0] = MVD_WR_I;
            s_MVD[0].r_addr = 2808;
            s_MVD[0].i=1;
          }
          if(flg_ch==2)
          {
            //17.02.2022 YN
            MVD_fn[0] = MVD_WR_I;
            s_MVD[0].r_addr = 2608;
            /*MVD_fn[0]=MVD_WR_C;
            s_MVD[0].r_addr=04; // Reset all inventories */
            /*
            s_MVD[0].r_addr=56; // Reset mass total
            s_MVD[0].r_addr=04; // Reset all inventories
            s_MVD[0].r_addr=57; // Reset volume totales */
            s_MVD[0].i=1;
            flg_ch++;
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
 //  ���� 9.��������� �������.
 //17.02.2022 YN
       if((key==ESC)||(key==ENTER) )    /* ������� � ���� */
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
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� ����� ����. �������:" );
          k_mv_tmp = sdv_m_flow;
          flag_mass=1;
m_m9_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"ESC - �������");
          sprintf( fst_str,"%.6f",k_mv_tmp);
          fst_n=9;
          sw_fst=1;
          MmiGotoxy(10,3);
          break;
       }
       if((key=='2')&&(Flag_f_corr!=0))
       {
          //08.02.2022 YN
          //#if(Shtray==0)
          #if ( (Shtray==0) || (Shtray==2) )

          if(PassW != Password)
          {
           pass_ret=2;
           goto m_pass;
          }
m_m9_2:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� �����.����.�������:" );
//        MmiPuts("������� ���� ����.����.��/�:" );
          k_mv_tmp=k_m_flow;
          flag_mass=0;
          goto m_m9_1_1;
#else
m_m9_2:
                  break;
#endif

       }
       if((key=='3')&&(Flag_f_corr!=0))
       {
          if(PassW != Password)
          {
           pass_ret=7;
           goto m_pass;
          }
m_m9_3:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� ����� ������.�������:" );
          k_mv_tmp=sdv_v_flow;
          flag_mass=2;
          goto m_m9_1_1;
       }

       //17.02.2022 YN
       if((key=='4')&&(Flag_f_corr!=0))
       {
          if(PassW != Password)
          {
           pass_ret=8;
           goto m_pass;
          }
m_m9_4:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� �����.������.�������:" );
          k_mv_tmp=k_v_flow;
          flag_mass=3;
          goto m_m9_1_1;
       }
       if((key=='5')&&(Flag_f_corr!=0))
       {
          if(PassW != Password)
          {
           pass_ret=9;
           goto m_pass;
          }
m_m9_5:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� ����� ���������:" );
          k_mv_tmp=sdv_dens;
          flag_mass=4;
          goto m_m9_1_1;
       }
       if((key=='6')&&(Flag_f_corr!=0))
       {
          if(PassW != Password)
          {
           pass_ret=10;
           goto m_pass;
          }
m_m9_6:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� ����������� ���������:" );
          k_mv_tmp=k_dens;
          flag_mass=5;
          goto m_m9_1_1;
       }


       else if(key==DATA)
        {
          sscanf(fst_str,"%f",&k_mv_tmp);

#if(Shtray==0)
         if(flag_mass==1) //key=1
         {
          if((k_mv_tmp<0.8)||(k_mv_tmp>1.2) )
                goto m_m9_1;
         }
         if(flag_mass==2) //key=3
         {
          if((k_mv_tmp<0.8)||(k_mv_tmp>1.2) )
                goto m_m9_3;
         }
         else //key=2
         {
          if(k_mv_tmp<0) goto m_m9_2;
         }
#else // (Shtray != 0)
      // ��������� �������� � k_mv_tmp
         if(flag_mass==1) //key=1
         {
          if((k_mv_tmp<0.0)||(k_mv_tmp>1000) )
                goto m_m9_1;
         }
         if(flag_mass==2) //key=3
         {
          if((k_mv_tmp<0.0)||(k_mv_tmp>1000) )
                goto m_m9_3;
         }

         //17.02.2022 YN
         if(flag_mass==3) //key=4
         {
          if((k_mv_tmp<0.0)||(k_mv_tmp>1000) )
                goto m_m9_4;
         }
         if(flag_mass==4) //key=5
         {
          if((k_mv_tmp<0.0)||(k_mv_tmp>1000) )
                goto m_m9_5;
         }
         if(flag_mass==5) //key=6
         {
          if((k_mv_tmp<0.0)||(k_mv_tmp>1000) )
                goto m_m9_6;
         }

         else //key=2
         {
          if((k_mv_tmp<0.0)||(k_mv_tmp>1000) )
                goto m_m9_2;
         }


#endif

#if(Shtray==0)
          if(flag_mass==1)
          {
           s_MVD[0].r_addr=279; // ��������� �����.

           chg_nn_par=Par_MF;
           chg_old=k_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else if(flag_mass==2)
          {
           s_MVD[0].r_addr=283; // ��������� ���������

           chg_nn_par=Par_DN;
           chg_old=k_dens;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else
          {
           s_MVD[0].r_addr=281; // ��������� ������.
           chg_nn_par=Par_VF;

           chg_old=k_v_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          MVD_fn[0]=MVD_WR_F;
          s_MVD[0].f = k_mv_tmp;
          goto m_m9;

#else  // Shtray != 0
          if(flag_mass==1) //key=1
          {
           s_MVD[0].r_addr=   5521; 

           chg_nn_par=Par_MF;
           chg_old=sdv_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else if(flag_mass==2) //key=3
          {
           s_MVD[0].r_addr= 5525; 

           chg_nn_par=Par_VF;
           chg_old=sdv_v_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }

          //17.02.2022 YN
          else if(flag_mass==3) //key=4
          {
           s_MVD[0].r_addr= 5523; 

           chg_nn_par=Par_VF;
           chg_old=k_v_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else if(flag_mass==4) //key=5
          {
           s_MVD[0].r_addr= 5529; 

           chg_nn_par=Par_DN;
           chg_old=sdv_dens;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else if(flag_mass==5) //key=6
          {
           s_MVD[0].r_addr= 5527; 

           chg_nn_par=Par_DN;
           chg_old=k_dens;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }

          else //key=2
          {
           s_MVD[0].r_addr= 5519; //key=2

           chg_nn_par=Par_MF;
           chg_old=k_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }

          MVD_fn[0]=MVD_WR_F;
          s_MVD[0].f = k_mv_tmp;
          goto m_m9;

#endif

        }
       else if(key==DATA_ESC)
        {
          goto m_m9;
        }

       break;
 /*========================================*/
    case 126:
 //  ���� 1.4.��������� ���������� ���������� ����������
       if((key==ESC)||(key==ENTER) )    /* ������� � ���� */
       {
         goto m_m5;
       }

    //02.02.2022 YN
    #if !defined(GAZAVOZ)
      if(valve_mode != 1)
    #endif
       if(key=='2')
       {

m_m5_4_1:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();

          //02.02.2022 YN
          #if defined(GAZAVOZ)
            MmiPuts("������� �����, �� :" );
            k_mv_tmp = beginMassa;
          #else
            MmiPuts("������� ��������� ������,��/�:" );
          k_mv_tmp=Flow_beg;
          #endif

          flag_mass=1;
m_m5_4_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("ESC-�������,Enter-���� ������");
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
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();

          //02.02.2022 YN
          #if defined(GAZAVOZ)
            MmiPuts("������� �����, � :" );
            k_mv_tmp = beginValue;
          #else
            MmiPuts("������� ��������� �����,� :" );
            k_mv_tmp=Vol_beg;
          #endif

          flag_mass=0;
          goto m_m5_4_1_1;
       }

       //02.02.2022 YN
       #if defined(GAZAVOZ)
        if(key=='3')
        {
          Flag_mass = 1; //������ �� �����
          MmiGotoxy(0,11);    MmiPuts("������ ��: �����, ��.     ");
          //goto m_m5_4;
        }
        if(key=='4')
        {
          Flag_mass = 0; //������ �� ������
          MmiGotoxy(0,11);    MmiPuts("������ ��: ������, �.     ");
          //goto m_m5_4;
        }
       #endif

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

      // ��������� �������� � k_mv_tmp
          if(flag_mass)
          {

           chg_nn_par=Par_FB;

            //02.02.2022 YN 
            #if defined(GAZAVOZ)
              chg_old = beginMassa;
            #else
              chg_old= Flow_beg;
            #endif

           chg_new= k_mv_tmp;
            
            //02.02.2022 YN 
            #if defined(GAZAVOZ)
              beginMassa = k_mv_tmp; //����� ��������� ���������, ��
            #else
              Flow_beg=k_mv_tmp; // ��������� ������,��/�
            #endif

           f_wr_evt(evt_chg_param);
          }
          else
          {
           chg_nn_par=Par_VB;

            //02.02.2022 YN 
            #if defined(GAZAVOZ)
              chg_old = beginValue;
            #else
              chg_old=Vol_beg;
            #endif

           chg_new= k_mv_tmp;
           
            //02.02.2022 YN 
            #if defined(GAZAVOZ)
              beginValue = k_mv_tmp; //����� ��������, �
            #else
              Vol_beg=k_mv_tmp;   // ��������� �����,�
            #endif

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
 //  ���� 9S.����  �������.
       if((key==ESC)||(key==ENTER) )    /* ������� � ���� */
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
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� ���� �.����.��/�:" );
          k_mv_tmp=k_m_flow;
          flag_mass=1;
m_m9s_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"ESC - �������");
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

//17.02.2022 YN
/*       if((key=='2')&&(Flag_f_corr!=0))
       {
          if(PassW != Password)
          {
           pass_ret=6;
           goto m_pass;
          }
m_m9s_2:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� ���� ��.����.�/���:" );
          k_mv_tmp=k_v_flow;
          flag_mass=0;
          goto m_m9s_1_1;
       }*/

       else if(key==DATA)
        {
          sscanf(fst_str,"%f",&k_mv_tmp);

         if(flag_mass)
         {
          if((k_mv_tmp<0)||(k_mv_tmp>100000.) )
                goto m_m9s_1;
         }

         //7.02.2022 YN
         /*else
         {
          if((k_mv_tmp<0)||(k_mv_tmp>1000.) )
                goto m_m9s_2;
         }*/

      // ��������� �������� � k_mv_tmp
          if(flag_mass)
          {

           //08.02.2022 YN
           #if(Shtray==2)
            s_MVD[0].r_addr=5138;  //�������� ���������    MM=195
           #else 
            s_MVD[0].r_addr=195; // ���� ����.����.
           #endif

           chg_nn_par=Par_MC;
           chg_old=k_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }

          //17.02.2022 YN
          /*else
          {
            //08.02.2022 YN
            #if(Shtray==2)
              s_MVD[0].r_addr=5138;  //�������� ���������    MM=195
            #else
              s_MVD[0].r_addr=197; // ���� ��. ����.
            #endif
           chg_nn_par=Par_VC;
           chg_old=k_v_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }*/


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
#if defined(BIO_1)
    case 130: // �������� ��������
       if((key==ESC) || (key==ENTER))    /* ������� � ���� */
       {
           goto main_menu;
       }
        else if (key=='0')
        {
          OUT_or &= ~( CL1_SRC | CL2_SRC);
        }
        else if (key=='1')
        {
          OUT_or &= ~( CL1_SRC | CL2_SRC);
          OUT_or |=  CL1_SRC;
        }
        else if (key=='2')
        {
          OUT_or &= ~( CL1_SRC | CL2_SRC);
          OUT_or |=  CL2_SRC;
        }
        else if (key=='3')
        {
          OUT_or |=  (CL1_SRC | CL2_SRC);
        }
        else if (key=='4')
        {
//         OUT_Pmp  ^=  Pump_MDB;

m_m2_b:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� �������� ����������,�:" );
          k_mv_tmp=T_Pmp_delay/1000.;
m_m2_b_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("ESC-�������,Enter-���� ������");
           sprintf( fst_str,"%6.0f",k_mv_tmp);
           fst_n=7;
          sw_fst=1;
          MmiGotoxy(10,3);
          break;
        }
       else if(key==DATA)
        {
          sscanf(fst_str,"%f",&k_mv_tmp);

          if(k_mv_tmp<0)
                goto m_m2_b_1;

      // ��������� �������� � k_mv_tmp


          T_Pmp_delay=k_mv_tmp * 1000.; // ��������� ������,��/�
          goto mm2_b0;
        }
       else if(key==DATA_ESC)
        {
          goto mm2_b0;
        }



        goto mm2_b;
#endif
 /*========================================*/
    case 140: // 2  �������� ������� �������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           goto main_menu;
       }

        //10.02.2022 YN
        else if(key == '4')
        {
m_m1:
          SetDisplayPage(EmptPage);
          f_clr_scr_MMI();
          MmiGotoxy(0,0);    MmiPuts(" ��������� �������� ���");
          MmiGotoxy(0,3);    MmiPuts("1  �� ��������� ����. ���");
          MmiGotoxy(0,5);    MmiPuts("2  �� ��������� 5 �����");
          MmiGotoxy(0,7);    MmiPuts("3  �� ��������� ����");
          MmiGotoxy(0,9);    MmiPuts("4  �� ������� ������");
          MmiGotoxy(0,11);   MmiPuts("5  �������� ���������� ����");
          f_d_ESC();
          sw_mmi=300;
          break;
        }

       else if (key==DEL)
       {

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
          MmiGotoxy(0,1);    MmiPuts(" 1 - ������������");
          MmiGotoxy(0,2);    MmiPuts(" 6 - ����� �� ��������� � ��");
          MmiGotoxy(0,3);    MmiPuts("    (���  �������)");
          MmiGotoxy(0,5);    MmiPuts("ESC   ������");
          sw_mmi=142;
          break;
       }
       else if(key== '1')  //1  �� ����
       {
m_m2_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   ���� ������ ������� ");
           MmiGotoxy(0,1);    MmiPuts("      ����.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=143;
          break;
       }
       else if(key== '2')  //2  �� ������ ������
       {
m_m2_2:
          max_par= f_get_max_n_arch();
          MmiGotoxy(1,1);
          f_clr_scr_MMI();
          MmiPuts("������� ����� ������:" );
          sprintf( fst_str,"%d",max_par);
          fst_n=4;
          sw_fst=1;
          MmiGotoxy(15,3);

#if defined(MMI_ICP)
          SetDisplayPage(15); // ���� ��������
#endif

#if defined(MMI_NEW)
          SetDisplayPage(2); // ���� ��������
#endif

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
       else if(key== '3')  //3  ��������� ������
       {
m_m2_3:
         max_par= f_get_max_n_arch();
         mmi_prm=max_par-d_F2;

m_m2_30:


m_m2_3v:
         if(mmi_prm>(max_par-1))
            mmi_prm=max_par-2;
         if(mmi_prm<0) mmi_prm=0;
         f_clr_scr_MMI();
         SetDisplayPage(EmptPage);    // ������ ��������

   //----------------

       for(n_pp=0,k=0;k<n_mmi_str_2;n_pp++,k++)
       {
        if((mmi_prm+n_pp)>=max_par)
        {
          n_pp-=1;
          k=0;
          break;
        }
        ar_str_ptr= f_get_astr(mmi_prm+n_pp);
        k=f_prn_mmi_a(ar_str_ptr,k);
       }

       if(k==n_mmi_str_2);
       else n_pp-=1;
       if(n_pp<1) n_pp=1;

   //----------------
m_m2_32:
        MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"ESC\"������");

        sw_mmi=141;
       }
       break;
 /*========================================*/
    case 141:/*�������� 2 ������� �������*/
         if(key==ESC)    /* ������� � ���� ������ ����� ��� ���������*/
         {
          goto m_m2;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=d_F2)
           {
            mmi_prm -=d_F2;
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
           if(mmi_prm <= (max_par-n_pp))
           {
               mmi_prm +=n_pp;
            goto m_m2_3v;
           }
         }
    break;
 /*========================================*/
    case 142:/* ����� �� ��������� */
             /* ������� � ��������� */
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
         {
          goto m_m2;
         }
         else if(key== '1' )
         { //  1 - ������������
           f_wr_evt(evt_res);
  StopUserTimerFun();
  RestoreCom(1);
  RestoreCom(2);
  RestoreCom(3);
  while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */
  RestoreCom(4);
  f_free_SlvBuf();

          _asm cli
          _asm hlt

         }
         else if(key== '6' )
         {// 6 - ����� �� ��������� � ��
            f_wr_evt(evt_exit);
            return 1; // ����� �� ��������� *.exe � ��
         }
         break;
 /*========================================*/
    case 143:

 //  ���� ����
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
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
            // ���� �������

m_m2_1_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   ����� ������ ������� ");
           MmiGotoxy(0,1);    MmiPuts("       ��� ���.");
        // MmiGotoxy(0,2);    MmiPuts("        08.01");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d",(int)adate00.hour,(int)adate00.min );
          fst_n=6;
          sw_fst=1;
          sw_mmi=144;
       }
          break;

 /*========================================*/
    case 144:
 //  ���� �������
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
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
            // ����� �������

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
    case 150: // 3  ��������� �������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           goto main_menu;
       }

       else if(key== '1')  // 1  ������ ���������
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_2:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_drv_list_MMI(&mmi_str);
         sw_mmi=22;
       }
       else if(key== '2')  // ����������  ���������
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_3:
         SetDisplayPage(EmptPage);  // ������ �����
         f_clr_scr_MMI();
         f_drv_stat_MMI(&mmi_str);
         pass_cnt=0;
         sw_mmi=23;
       }
       else if(key== '3')   //  3  ��������/���� ����������
       {
m_m3_3:

   //     PassW=0;
        // ������� � ���� ������ ����� ��� ��������� ����������
          sw_mmi=11;
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� ������ ������ ���������");
            MmiGotoxy(0,7);    MmiPuts("1...6  ����� �������� ");
            MmiGotoxy(0,15);    MmiPuts("ESC  �������");
          break;
       }

       //02.02.2022 YN
       #if !defined(GAZAVOZ)
          else if(key== '4')   //  4  ������ �������
          {
m_m3_4:
            SetDisplayPage(EmptPage);  // ������ �����
            f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� 4.4.������ �������. ");
            MmiGotoxy(0,1);    MmiPuts("1  ��������� �����������");
            MmiGotoxy(0,2);    MmiPuts("2  ��������� �����������");
            MmiGotoxy(0,3);    MmiPuts("3  ������ �����������");
            MmiGotoxy(0,4);    MmiPuts("4  ����� ICP/RTU �������");
            MmiGotoxy(0,5);    MmiPuts("5  ������ ��������� �������");
            MmiGotoxy(0,6);    MmiPuts("ESC  �������");
            sw_mmi=160;
              break;
          }
        #endif

        //02.02.2022 YN
        #if defined(GAZAVOZ)
          else if(key== '4')   //  5  �����, ����
        #else
          else if(key== '5')   //  5  �����, ����
        #endif
       {
m_m3_5:

//02.02.2022 YN
#if defined(GAZAVOZ)
m_m3_4:
#endif

         f_prepare_t ( &adate00);
         adate11=adate00;
         SetDisplayPage(EmptPage);  // ������ �����
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("      ������� ���� ");
           MmiGotoxy(0,1);    MmiPuts("      ����.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("������� ���/���.����� ��������");
else                          MmiPuts("������� ���/���.����� �������");

/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - ������
                              MmiPuts("      ������ �����");
     else                     MmiPuts("      ������ �����");
*/
            MmiGotoxy(0,4);   MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);   MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);   MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=165;
          break;
       }

      //02.02.2022 YN
      #if !defined(GAZAVOZ)
        else if(key== '6')   //  6  �������� ������
        {
m_m3_6:
          SetDisplayPage(EmptPage);  // ������ �����
          f_clr_scr_MMI();
          MmiGotoxy(0,0);    MmiPuts(" ���� 4.6.��������� ������ ");
          MmiGotoxy(0,2);    MmiPuts("1  �������� ������");
          f_d_ESC();
          sw_mmi=162;
        break;
        }
      #endif


       break;
 /*========================================*/
    case 160: // M3.4  ������ �������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           goto m_m3;
       }
       else if(key== '1') //  1  ��������� �����������
       {
m_4_4_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_prn_den_t();
         flg_ch=0;

         State_SLV = Mod_flow_s;
         f_reg_cmn(Mod_flow_s_cmn);

          //17.02.2022 YN WAS: sw_mvd_m1=20;
         sw_mvd_m1=31; 
         ff_serv=f_MVD_MM4;

/*
         s_MVD[0].r_addr=195; // ���� ����.����.
         s_MVD[0].f = 0.;
         MVD_fn[0]=MVD_WR_F;;
*/
         sw_mmi=122;
         break;

       }

       else if(key== '2') //  2  ��������� �����������
       {
         max_par=17;
         mmi_prm=0;

m_m3_4_2v:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"ESC\"������");

         if(ff_serv==NULL)
         {
          sw_MMI_cur=0; // ������ MMI
          sw_mvd_m1=mmi_prm+20;  // ���.��������
          sw_MMI_lim=6; // �������� ������

          ff_serv=f_MVD_M1;
          sw_mmi=172;
         }
         else
          sw_mmi=174;
         break;
       }
       else if(key== '3') // 3  ������ �����������
       {
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,6);    MmiPuts("ESC,ENTER  �������");
         sw_mvd_m1=0;
         ff_serv=f_MVD_M3;
         sw_mmi=180;

         break;

       }

       else if(key== '5') //  5  ������ ������������ �������
       {
         mmi_str=0;
         max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
m20_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_mod_list_MMI(&mmi_str);
         sw_mmi=21;
       }
       else if(key== '4')  // 4  ����� ICP/RTU �������
       {
m20_4:
          f_clr_scr_MMI();
          MmiGotoxy(1,1);
          MmiPuts("������� ����� ����� : " );
          sprintf( fst_str,"%2d",mmi_com);
          fst_n=3;
          sw_fst=1;
          MmiGotoxy(13,3);

#if defined(MMI_ICP)
          SetDisplayPage(15); // ���� ��������
#endif

#if defined(MMI_NEW)
          SetDisplayPage(2); // ���� ��������
#endif

          break;
       }
       else if(key== DATA )
       {
          sscanf(fst_str,"%d",&mmi_com);  // ����� COM
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
         MmiGotoxy(0,0);     MmiPrintf("ICP COM%d: ������� %d ��",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("����.��� %d,���� CRC=%d",licp_amax,LICP_Rqst.CRC_flag);
       }
       else
       {
         MmiGotoxy(0,0);     MmiPrintf("RTU COM%d: ������� %d ��",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("����.��� %d",licp_amax);
       }

       MmiGotoxy(0,6);  MmiPuts("  Enter - ����������");
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
 //  ��������� ������
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
       {
         goto m_m3;
       }
       else if(key== '1')   // 1  �������� ������
       {

          if(PassW != Password)
          {
           pass_ret=3;
           goto m_pass;
          }
m_m3_6_1:

          SetDisplayPage(EmptPage); // ���� ��������
          f_clr_scr_MMI();
          MmiGotoxy(0,1);
          MmiPuts("������� ����� ������(1-� ���):" );
           pass1=-1;
           sprintf( fst_str,"******");
#if defined(MMI_ICP)
          SetDisplayPage(17);  // ���� ������
#endif

//#if defined(MMI_NEW)
//          SetDisplayPage(2); // ���� ��������
//#endif
           sw_mmi=163;
           fst_n=7;
           sw_fst=1;
           MmiGotoxy(11,3);
           break;
       }
       break;
 /*========================================*/
    case 163: // // ���� ������ ������ 1 ���
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
 m163:
          goto m_m3;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&pass1);
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
           // ������ ������ ���������
           if(pass1>= 0)
           {
             f_clr_scr_MMI();
             MmiGotoxy(0,1);
             SetDisplayPage(EmptPage); // ���� ��������
             f_clr_scr_MMI();
             MmiPuts("������� ����� ������(2-� ���):" );
             pass2=-1;
             sprintf( fst_str,"******");
#if defined(MMI_ICP)
          SetDisplayPage(17); // ���� ������
#endif

//#if defined(MMI_NEW)
//          SetDisplayPage(2); // ���� ��������
//#endif
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
          SetDisplayPage(EmptPage);    // ������ ��������
          goto m163;
        }

 /*========================================*/
    case 164: // // ���� ������ ������ 2 ���
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
          goto m163;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&pass2);
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
           // ������ ������ ���������
           if(pass2 == pass1)
           {
             chg_nn_par=Par_PASS;
             chg_old=Password_m;
             chg_new= pass1;
         //  Password=pass1;
             Password_m=pass1;
             f_wr_evt(evt_chg_param);

             if(f_wrt_eee()<0)
             {
                f_wr_evt(evt_we_err);
                MmiGotoxy(1,3);   MmiPuts("������ ��� ���������� ������");
             }
             else
             {
                f_wr_evt(evt_we);
                MmiGotoxy(3,3);   MmiPuts("������ �������� �������");
             }
             f_wr_cor();
             MmiGotoxy(0,6);   MmiPuts("      Enter - ����������");
             break;
           }
           else goto m_m3_6_1;

        }
       else if(key==DATA_ESC)
        {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ������ ��������
          goto m163;
        }

 /*========================================*/

 /*========================================*/
    case 165:

 //  ���� ���� ��� ���������
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
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
            // ���� �������
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
           MmiGotoxy(0,0);    MmiPuts("      ������� ����� ");
           MmiGotoxy(0,1);    MmiPuts("       ��� ��� ���");
        // MmiGotoxy(0,2);    MmiPuts("         08.01.00");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("������� ���/���.����� ��������");
else                          MmiPuts("������� ���/���.����� �������");
/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - ������
                              MmiPuts("      ������ �����");
     else                     MmiPuts("      ������ �����");
*/





            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)adate00.hour,(int)adate00.min,(int)adate00.sec);
          fst_n=9;
          sw_fst=1;
          sw_mmi=166;
       }
          break;

 /*========================================*/
    case 166:
 //  ���� �������
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
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
            // ����� �������
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








































    //10.02.2022 YN
    case 300:

      if((key==ESC)||(key==ENTER))    /* ������� � ���� */
      {
        goto m_m2;
      }

      else if(key== '1')  // 1  �� ��������� ����. ���
      {
m_m1_1:
  //     mmi_str=0;
        SetDisplayPage(EmptPage);
        f_clr_scr_MMI();
        f_prn_lst_hour();
        sw_mmi=301;
      }

      else if(key== '2')  // 2  �� ��������� 5 �����
      {
m_m1_2:

        SetDisplayPage(EmptPage);
        f_clr_scr_MMI();
        f_prn_5day();
        sw_mmi=301;
      }
      else if(key== '3')  // 3  �� ��������� ����
      {
m_m1_3:
        SetDisplayPage(EmptPage);
        f_clr_scr_MMI();
        MmiGotoxy(0,0);    MmiPuts("   ���� ��������� ��������");
        MmiGotoxy(0,1);    MmiPuts("      ����.���.���");
        MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
        MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
        MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
        MmiGotoxy(8,2);
        sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
        fst_n=11;
        sw_fst=1;
        sw_mmi=304;
      }
      else if(key== '4')  //4  �� ������� ������
      {
m_m1_4:
        SetDisplayPage(EmptPage);
        f_clr_scr_MMI();
        f_prn_current();
        sw_mmi=302;
      }
      else if(key== '5')  //5  �������� ���������� ����
      {
m_m1_5:
      SetDisplayPage(EmptPage);
      f_clr_scr_MMI();
      MmiGotoxy(0,0);    MmiPuts("  �������� ���������� ����");
      MmiGotoxy(0,1);    MmiPuts("       ���.���.���");
      MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
      MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
      MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
      MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)ahour00.hour,(int)ahour00.min,(int)ahour00.sec );
      fst_n=9;
      sw_fst=1;
      sw_mmi=303;
      }

    break;

 /*========================================*/
    case 301:
      //  ����������� ��������� ������� ���.
      // �� ��������� ����. ��� .
       if((key==ESC)||(key==ENTER))    /* ������� � ����������� ���� */
       {
         goto m_m1;
       }
       break;
 /*========================================*/
    case 302:
 //  ����������� ��������� ������� ���.
 //  ������� ��������.
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
         goto m_m1;
       }
       else if(key==PASS)
       {
         f_prn_current();
       }
       break;
 /*========================================*/
    case 303:
 //  ����������� ���������� ����.
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
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
              MmiGotoxy(0,5);   MmiPuts("������ ��� ���������� ������");
              sw_mmi=301;
           }
           else goto m_m1;

          break;
        }
       break;
 /*========================================*/
    case 304:
 //  ���� ����
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
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
            // ���� �������
            // ����������� �������� �������
            SetDisplayPage(EmptPage);
            f_clr_scr_MMI();
            f_prn_date();
            sw_mmi=301;

          break;
        }
       break;
 /*========================================*/



























































    case 200:

         // ���� ���� ������� ����������
m1_5:

          PassWm=0;

          sw_mmi=201;
          f_reg_cmn(0);
          f_clr_scr_MMI();
          n_id_a=0;
          n_id_af=0.;
          chg_nn_par=Par_ID;
          chg_old=n_id_a;
          MmiGotoxy(5,6);  MmiPuts("������� ��� �������:" );
//        sprintf( fst_str,"%8ld",n_id_a);
          sprintf( fst_str,"");
          fst_n=9;
          sw_fst=1;
          MmiGotoxy(10,8);
  //      MmiGotoxy(15,3);
#if defined(MMI_ICP)
          SetDisplayPage(15); // ���� ��������
#endif

#if defined(MMI_NEW)
          SetDisplayPage(2); // ���� ��������
#endif
          break;

 /*========================================*/
    case 201:



        if(key==DATA)
        {
          sscanf(fst_str,"%ld",&n_id_a);
          if(n_id_a<=0) { n_id_a=0; goto m1_5;}

           chg_new= n_id_a;
           n_id_af= n_id_a;
           f_wr_evt(evt_chg_param);
                f_reg_cmn(2);
          goto mm00;
        }
       else if(key==DATA_ESC)
        {
          n_id_a=-1;
          n_id_af=-1.;
                f_reg_cmn(1);
          goto mm00;
        }
    break;
/*========================================*/
    case 210:

         // �������� ������ ���� ������


          PassWm=0;
          sect_rslt=0;
          sw_mmi=211;
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);

m210:
          f_reg_cmn(0);

str_prod[20]=0;
 MmiGotoxy(0,2);   MmiPuts("  �����   :");
   if(type_dlv==2) MmiPuts("  �������               ");
   if(type_dlv==1) MmiPuts("   ������                ");
   else            MmiPuts(" --------      ");

MmiGotoxy(0,4); MmiPrintf("  ������� :%s",str_prod);
 MmiPuts( str_empt );


MmiGotoxy(0,6);
if(sect_num>0)
{
  MmiPrintf("  ������ N:     %d  ",sect_num);
}
else
{
  MmiPrintf("  ������ N:     --");
}

MmiGotoxy(0,8);
if((sect_mass != 0) && (sect_vol==0.))
 MmiPrintf("  �����,��:%7d          ",sect_mass);
else if((sect_vol != 0) && (sect_mass == 0.))
 MmiPrintf("  �����, �:%7d          ",sect_vol);
else
 MmiPrintf("  --------: --------");
MmiGotoxy(0,10);
 MmiPuts(" 1-������; 2 - ������� ");

MmiGotoxy(0,15);
 MmiPuts(" ESC - �����  ");

         if((type_dlv==1) || (type_dlv==2))
           if(sect_num>0)
             if (((sect_mass != 0) && (sect_vol==0.)) || ((sect_vol != 0) && (sect_mass == 0.))  )
              {
  MmiPuts(", Enter-����");
              }


          break;

 //========================================
    case 211:

         // �������� ������ ���� ������
         // ������ ������� ������



       if(key==ESC)   // ������� �� ��������� ��������
       {
         sect_rslt=-1;
         type_dlv=0;

         f_reg_cmn(3);
         goto mm00;
       }
       else if(key== '1')
       {
         type_dlv=1;
         sect_rslt=0;

       }
       else if(key== '2')
       {
         type_dlv=2;
         sect_rslt=0;
       }
       if(key==ENTER)    // ������� �� ��������� ��������
       {
         if((type_dlv==1) || (type_dlv==2))
           if(sect_num>0)
             if (((sect_mass != 0) && (sect_vol==0.)) || ((sect_vol != 0) && (sect_mass == 0.))  )
              {
                sect_rslt=1;

                f_reg_cmn(4);
                goto mm00;
              }
       }

       goto m210;

 //========================================
    case 220:

         // �������� ����������� ����� 1-6

        PassWm=0;

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);
          sw_mmi=221;

          f_reg_cmn(0);

str_dsp1[30]=0;
str_dsp2[30]=0;
str_dsp3[30]=0;
str_dsp4[30]=0;
str_dsp5[30]=0;
str_dsp6[30]=0;
str_dsp7[30]=0;

m220:

 MmiGotoxy(0,0);
 MmiPuts(str_dsp1); MmiPuts( str_empt );


 MmiGotoxy(0,1);
 MmiPuts(str_dsp2); MmiPuts( str_empt );


 MmiGotoxy(0,2);
 MmiPuts(str_dsp3); MmiPuts( str_empt );

 MmiGotoxy(0,3);
 MmiPuts(str_dsp4); MmiPuts( str_empt );


 MmiGotoxy(0,4);
 MmiPuts(str_dsp5); MmiPuts( str_empt );


 MmiGotoxy(0,5);
 MmiPuts(str_dsp6); MmiPuts( str_empt );

 MmiGotoxy(0,6);
 MmiPuts(str_dsp7); MmiPuts( str_empt );

          break;

 //========================================
    case 221:

         // �������� ������ ���� ������
         // ������ ������� ������



       if(key==ESC)   // ������� �� ��������� ��������
       {

         f_reg_cmn(5);
         goto mm00;
       }
       if(key==ENTER)    // ������� �� ��������� ��������
       {
         f_reg_cmn(6);
         goto mm00;
       }

       goto m220;

 //========================================
 //========================================
    case 21:  // �������� ������ �������

       max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
       if((key==ESC)||(key==ENTER))   /* ������� � ���� ������ ����� ��� ���������*/
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
    case 22: // �������� ������ ���������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� ������ ����� ��� ���������*/
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
    case 23: // �������� ���������� ���������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� ������ ����� ��� ���������*/
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
        {  // ��������� ��������� ������
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
    case 24: // ����������� ������������ �����
       if((key==ESC)||(key==ENTER))
       {
           goto m_m3_4; //  4  ������ �������
       }
       else //PASS
       {
          MmiGotoxy(0,3);  MmiPrintf("��������   %3d",licp_addr);
          MmiGotoxy(0,4);  MmiPrintf("���������� %3d",licp_fnd);
       }
       break;
 /*========================================*/
    case 25: // ����������� ���������� ������

       if((key==ESC)||(key==ENTER))
       {
           goto m0_f1;
       }
       else if((key== '2') && (id_ok !=0) ) // 2  ��������
       {
        flag_prok=1;
        strcpy(mode_prok,prok_ka);
        Flag_Low=-1;
        goto m1_1;
       }
       else // PASS
       {
// MmiGotoxy(0,0); MmiPrintf(" ��������� ���������� ������:");
// MmiGotoxy(0,1); MmiPrintf("       7017C/1 , ��");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625

// if( _fmemcmp( &ADC[0], &ADC_c[0], sizeof(ADC_c4)) != 0)
    {

      //10.06.2021 YN
      #if (PressureDrop == 1)
        MmiGotoxy(0,2); MmiPrintf(" ��������     %8g (In%d)",(float)ADC[0],analog_num[0]-1);
        MmiGotoxy(0,3); MmiPrintf(" �����������  %8g (In%d)",(float)ADC[1],analog_num[1]-1);
        MmiGotoxy(0,4); MmiPrintf(" �������      %8g (In%d)",(float)ADC[2],analog_num[2]-1);
      #elif (PressureDrop == 2)
        MmiGotoxy(0,2); MmiPrintf(" ��������     %8g (In%d)",(float)ADC[0],analog_num[0]-1);
        MmiGotoxy(0,3); MmiPrintf(" �����������  %8g (In%d)",(float)ADC[1],analog_num[1]-1);
        MmiGotoxy(0,4); MmiPrintf(" ����. ��     %8g (In%d)",(float)ADC[2],analog_num[2]-1);
        MmiGotoxy(0,5); MmiPrintf(" ����. �����  %8g (In%d)",(float)ADC[3],analog_num[3]-1);
      #else
        MmiGotoxy(0,3); MmiPrintf(" ��������     %8g (In%d)",(float)ADC[0],analog_num[0]-1);
        MmiGotoxy(0,4); MmiPrintf(" �����������  %8g (In%d)",(float)ADC[1],analog_num[1]-1);
      #endif

      //    _fmemcpy( &ADC_c[0], &ADC[0], sizeof(ADC_c4));
    }


//-------------------
     MmiGotoxy(0 ,6); MmiPuts("�����.�=");
     if( STRT_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy(12,6); MmiPuts("����.�=");

//   if( STOP_IN)
     if( ES_IN )
       MmiPuts("1");
     else
       MmiPuts("0");

     //11.06.2021 YN
     #if defined(PresenceLiquid)
      MmiGotoxy(23,6); MmiPuts("������");
     if(FILTER_FULL)
       MmiPuts("1");
     else
       MmiPuts("0");
     #endif

//-------------------
     MmiGotoxy(0 ,8); MmiPuts("�����.�=");
     if( STRT_IN_L)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy(12,8); MmiPuts("����.�=");

     if( ES_IN_L )
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy(23,8); MmiPuts("��.�.=");
     if(LVL_IN_L)
       MmiPuts("1");
     else
       MmiPuts("0");

//-------------------
     MmiGotoxy( 0,10); MmiPuts("��.�.=");
     if(LVL_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy( 8,10); MmiPuts("����=");
     if(TRAP_IN)
       MmiPuts("1");
     else
       MmiPuts("0");
     MmiGotoxy(16,10); MmiPuts("����.=");
     if( CONS_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy(24,10); MmiPuts(" ���=");
     if( UZA_IN )
       MmiPuts("1");
     else
       MmiPuts("0");
//-----------------------
     MmiGotoxy( 0,12);  MmiPuts("����.����.����.=");
     if(IN_CLS_L)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy( 0,14); MmiPuts("����.�����.����.=");
     if(IN_CLS_H)
       MmiPuts("1");
     else
       MmiPuts("0");
//-----------------------

       }

       break;
 /*========================================*/
    case 26:/* �������� ������� ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
          goto m_main;
         }
         break;
 /*========================================*/
    case 27:/* �������� ������� ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
           goto m0_f1;
         }
         break;
 /*========================================*/
    case 28: // ����������� ���������� �������
       if((key==ESC)||(key==ENTER))
       {
           goto m0_f1;
       }

#if defined(BIO_1)

       else if(key== '1')
       {
        OUT_VAR ^= OUT2;
       }
       else if(key== '2')
       {
        OUT_VAR ^= OUT1;
       }
       else if(key== '3')
       {
        OUT_VAR ^= OUT5;
       }
       else if(key== '4')
       {
        OUT_VAR ^= OUT6;
       }
       else if(key== '5')
       {
        OUT_VAR ^= OUT3;
       }

#else

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
        OUT_VAR ^= OUT5;
       }
       else if(key== '4')
       {
        OUT_VAR ^= OUT6;
       }


       else if(key== '5')
       {  // ������
        OUT_VAR ^= OUT4;
       }

       else if(key== '6')
       { // �����
        OUT_VAR ^= OUT3;
       }

       else if(key== '7')
       {  // OK
        OUT_VAR ^= OUT7;
       }

       else if(key== '8')
       {  // OK
        OUT_VAR ^= OUT8;
       }
#endif
       else // PASS
       {
         {

#if defined(BIO_1)

          MmiGotoxy(0,2);
     MmiPuts("����.���.:");
     if( OUT_VAR & OUT2  )
       MmiPuts("1       ");
     else
       MmiPuts("0  ");

          MmiGotoxy(15,2);
     MmiPuts("����.���.:");
     if( OUT_VAR & OUT1  )
       MmiPuts("1       ");
     else
       MmiPuts("0  ");

     MmiGotoxy(0,3);              MmiPuts("���. 1:");
     if( i7060_out[0] & OUT5  )
       MmiPuts("1  ");
     else
       MmiPuts("0  ");


     MmiGotoxy(15,3);   MmiPuts("���. 2:");
     if( i7060_out[0] & OUT6  )
       MmiPuts("1  ");
     else
       MmiPuts("0  ");



     MmiGotoxy( 0,4);   MmiPuts("����� :");
     if( i7060_out[0] & OUT3  )
       MmiPuts("1      ");
     else
       MmiPuts("0      ");


#else
          MmiGotoxy(0,2);
      MmiPuts("�.�����:");
  if(valve_mode==1)
      MmiPuts("��.���.");
  else if(valve_mode==2)
      MmiPuts("���.�.�");
  else if(valve_mode==3)
      MmiPuts("��.����");

          if(OUT_VAR & OUT1)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(18,2);
  if(valve_mode==1)
         MmiPuts(" ��.���.");
  else if(valve_mode==2)
         MmiPuts("���.�.�.");
  else if(valve_mode==3)
         MmiPuts("~��.����");

          if(OUT_VAR & OUT2)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(0,3);
      MmiPuts("�.�����:");
  if(valve_modeL==1)
      MmiPuts("��.���.");
  else if(valve_modeL==2)
      MmiPuts("���.�.�");
  else if(valve_modeL==3)
      MmiPuts("��.����");

          if(OUT_VAR & OUT5)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(18,3);
  if(valve_modeL==1)
         MmiPuts(" ��.���.");
  else if(valve_modeL==2)
         MmiPuts("���.�.�.");
  else if(valve_modeL==3)
         MmiPuts("~��.����");

          if(OUT_VAR & OUT6)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(0,4);
#if(AIR_SW != 0)
                  MmiPuts("������ ");
#endif
#if(CUT_SW != 0)
                 MmiPuts("������� ");
#endif

                  if(OUT_VAR & OUT4)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(15,4); MmiPuts("�����  ");
          if(OUT_VAR & OUT3)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(0,5); MmiPuts("�������:");
          if(OUT_VAR & OUT7)
            MmiPuts("1 ");
          else
            MmiPuts("0 ");

          MmiGotoxy(15,5); MmiPuts("��� ������ ");
          if(OUT_VAR & OUT8)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");
#endif

         }
       }
       break;
 /*========================================*/
 /*========================================*/
 /*
    case 171://  1  ��������� �����������
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
           sw_MMI_cur=0; // ������ MMI
           sw_mvd_m1=mmi_prm+20;  // ���.��������
           sw_MMI_lim=6; // �������� ������
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

         break;
*/
 /*========================================*/

    case 172://  2  ��������� �����������
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
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"ESC\"������");
           sw_MMI_cur=0; // ������ MMI
           sw_mvd_m1=mmi_prm+20;  // ���.��������
           sw_MMI_lim=6; // �������� ������
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
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"ESC\"������");
           sw_MMI_cur=0; // ������ MMI
           sw_mvd_m1=mmi_prm+20;  // ���.��������
           sw_MMI_lim=6; // �������� ������

           ff_serv=f_MVD_M1;
           sw_mmi=172;
          }
         }
         break;
 /*========================================*/
    case 180:

       if((key==ESC)||(key==ENTER))  /* ������� �� ��������� �������� */
       {
         if(ff_serv==f_MVD_M3) ff_serv=NULL;
            goto m_m3_4;
       }
       break;
 /*========================================*/
    case 190: //  1  ������ ��������������

       if(key==ESC)    /* ������� � ���� */
       {
           goto main_menu;
       }

       else if((key== '1') && (id_ok !=0) && (mode_hst == 0) )  // 1  ���� ����
       {

         if( (valve_mode > 0) && (valve_modeL > 0 ))  Flag_Low=0;
         else if( valve_mode > 0) Flag_Low=0;
         else if( valve_modeL > 0) Flag_Low=1;
         else
          {
           Flag_Low=-1;
           goto m_m5;
          }
m_m5_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

        //02.02.2022 YN
        #if defined(GAZAVOZ)
          MmiGotoxy(0,0);     MmiPrintf("      ������ ���� ���         ");
          fillingFlag = 0;
        #else
          MmiGotoxy(0,0);     MmiPrintf("��� %d.  %s ���� ",n_ASN,mode_prok);
        #endif

         f_prn_MassSt_dlv();

         MmiGotoxy(0,5);
          if ( Flag_mass != 0 )
             MmiPuts(" ������� ���� �������,�� ");
          else
             MmiPuts(" ������� ���� �������,� ");

         MmiGotoxy(0,15); MmiPuts(" Enter - ���� ������  ");

      // sprintf( fst_str,"");
         strcpy( fst_str,"");
         fst_n=5;
         sw_fst=1;
         flag_dlv_fst=0;
         dose_dlvr= 0;
         flag_prn_mass=0;
         MmiGotoxy(10,8);
         break;
       }

        //02.02.2022 YN
        #if defined(GAZAVOZ)
          else if((key== '2') && (id_ok !=0) && (mode_hst == 0) && (valve_mode == 1) && (valve_modeL == 0 ) )
          {
            Flag_Low=0;
            if(Flag_mass != 0)
            {
              dose_dlvr = beginMassa;
            }
            else
            {
              dose_dlvr = beginValue;
            }
            fillingFlag = WHOLE;
            //dose_dlvr = 12345.0;
            flag_dlv_fst=0;
            flag_prn_mass=0;
            goto m_m5;
          }
        #endif

       else if(key==DATA)
        {
          dose_dlvr=0;
          sscanf(fst_str,"%f",&dose_dlvr);
          if(dose_dlvr<=0) { dose_dlvr=0; goto m_m5_1;}
//          else if(dose_dlvr > 10000) {dose_dlvr=10000; goto m_m5_1;}
         flag_dlv_fst=0;
         flag_prn_mass=0;
         goto m_m5;
m_m5_1o:
          flag_rcv=0;

         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);
          
        //02.02.2022 YN
        #if defined(GAZAVOZ)
          if(fillingFlag == WHOLE)
          {
            MmiPrintf("������ �� �����������, ");
          }
          else
          {
            MmiPrintf("���.���� %g ",dose_dlvr);
          }
        #else
          MmiPrintf("���%d.���.���� %g ",n_ASN,dose_dlvr);
        #endif
         
         if ( Flag_mass != 0 )
           MmiPrintf("��");
         else
           MmiPrintf("� ");

         f_prn_mode();

         MmiGotoxy(0,15);       MmiPuts("ESC - ���������.");

         sw_dlv_liq=1;
         sw_mmi=193;
m_m5_1d:
/*==========
          MmiGotoxy(0,2);      MmiPuts("  �����        |  ��������");
                //             MmiPuts("xxxxx.xx ��    | xxxxx.xx ��");
          MmiGotoxy(0,3);
          if(flag_prn_mass)   MmiPrintf("%8.2f ��    | %8.2f ��   ",s_MVD[0].MassI,s_MVD[0].MassT);  // VolT_id, VolT_int
          else  MmiPrintf("%8.2f ��    | %8.2f ��   ",s_MVD[0].MassI,(float)0.);  // VolT_id, VolT_int
===========*/

//          MmiGotoxy(0,3);      MmiPuts("           ��������          ");
//        MmiGotoxy(0,2);      MmiPuts("  M,��   --��������-- V,�    ");
//        MmiGotoxy(0,2);      MmiPuts("  �����        |  ��������");
                //             MmiPuts("xxxxx.xx ��    | xxxxx.xx ��");


 //    MmiGotoxy(0,4);  MmiPrintf("����� ���.  %9.2f �  ",s_MVD[0].VolT);  // VolT_id, VolT_int
 //    MmiGotoxy(0,6);MmiPrintf("����� ���.  %9.2f �� ",s_MVD[0].MassT);  // VolT_id, VolT_int

       MmiGotoxy(0,4);  MmiPrintf("����� ���.,�");  // VolT_id, VolT_int
           MmiGotoxy(0,6);  MmiPrintf("����� ���.,��");  // VolT_id, VolT_int

        //        Z X  Y    L   Font
  //      SetZone(0,14,30  ,8 , WIN12);
          SetZone(0,14,32  ,8 , WIN8 );
  //      SetZone(0,14,30  ,8 , WIN12);
          SetZone(1,14,48  ,8 , WIN8 );

          if(flag_prn_mass)  // WWWWW
          {

        //        Z X
          Z_MvToX(0,0);
          MmiPrintf("%8.2f",s_MVD[0].VolT);
          Z_MvToX(1,0);
          MmiPrintf("%8.2f",s_MVD[0].MassT);

          }
          else
          {
          Z_MvToX(0,0);
          MmiPrintf("%8.2f",(float)0.);
          Z_MvToX(1,0);
          MmiPrintf("%8.2f",(float)0.);
//     MmiGotoxy(0,4);  MmiPrintf("����� ���.  %9.2f �  ",(float)0.);  // VolT_id, VolT_int
//     MmiGotoxy(0,6);  MmiPrintf("����� ���.  %9.2f �� ",(float)0.);  // VolT_id, VolT_int
          }
m_m5_1e:
          f_prn_proc();
          break;
        }
       else if(key==DATA_ESC)
        {
          goto m_m5;
        }
//     else if(key== '2')  // 2  ���� ������� ������
//---------------------------------------
       else if((key== '2') && (id_ok !=0) && (mode_hst == 0) && (valve_mode > 0) && (valve_modeL > 0 ) )
       {
         Flag_Low=1;
         goto m_m5_1;
       }
//-----------------------------------------------
       else if((key== '4') && ( (Flag_Low == 0) || ( (Flag_Low == 1)  && (valve_mode == 0) ) ) && (id_ok !=0) && (mode_hst == 0) )
       {
         /*
         if((flag_prn_mass) && (dose_dlvr > 0))
          {
           goto m_m5_1o;
          }
         else
          */
         if(dose_dlvr > 0)
               goto m_m5_1o;
       }
       else if((key== '8') && (Flag_Low == 1) && (id_ok !=0) && (mode_hst == 0) && (valve_mode > 0) && (valve_modeL > 0 )  )
       {
         /*
         if((flag_prn_mass)&& (dose_dlvr > 0))
          {
           goto m_m5_1o;
          }
         else
         */
         if(dose_dlvr > 0)
               goto m_m5_1o;
       }

#if !defined(BIO_1)
       else if((key== '0' )&& (Flag_Low != 1)  )//  0  ��������� ���������� ���������� ����������
#else
       else if((key== 'Z' )&& (Flag_Low != 1)  )//  0  ��������� ���������� ���������� ����������
#endif

       {
m_m5_4:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

            //02.02.2022 YN
            #if defined(GAZAVOZ)
              MmiGotoxy(0,0);    MmiPrintf(" ��������� �������� ");
              MmiGotoxy(0,3);    MmiPuts("1 �������� ����� ��������");
              MmiGotoxy(0,4);    MmiPuts("2 �������� ����� ����.�������� ");
              MmiGotoxy(0,5);    MmiPuts("3 ������ �� ����� ");
              MmiGotoxy(0,6);    MmiPuts("4 ������ �� ������ ");
              MoveToXY(0,9);    MmiPrintf("����� ��������  :%6.0f �",beginValue);
              MoveToXY(0,10);   MmiPrintf("����� ����.����.:%6ld ��",(long int)beginMassa);
              if(Flag_mass == 1) 
              {
                MmiGotoxy(0,11);    MmiPuts("������ ��: �����, ��.     ");
              }
              else
              {
                MmiGotoxy(0,11);    MmiPuts("������ ��: ������, �.     ");
              }
            #else
              MmiGotoxy(0,0);    MmiPrintf("��� %d.�����.���.���������� ",n_ASN);
              MmiGotoxy(0,1);    MmiPuts("1 �������� ��������� ����� ");
              MoveToXY(0,4);   MmiPrintf("��������� ����� :%6.0f �",Vol_beg);
              if(valve_mode != 1)
              {
                MmiGotoxy(0,2);    MmiPuts("2 �������� ��������� ������ ");
                MoveToXY(0,5);   MmiPrintf("��������� ������:%6ld ��/�",(long int)Flow_beg);
              }
            #endif

            MmiGotoxy(0,14);    MmiPuts("ESC  �������");

         sw_mmi=126;
         break;
       }

   /*
       else  if(mode_hst == 0 )
          f_prn_MassSt_dlv();
   */

       goto m_m5_01;
//     break;
 /*========================================*/
//===========================================
    case 193: //  ������
       if(key==F2)    // ��������� ��������,�����������
       {
           PageD=0;
       }

       //02.02.2022 YN
       #if !defined(GAZAVOZ)
        else if(key==F3)    // ��������� ���������,������
        {
          PageD=1;
        }
       #endif

       else if(key=='1')    // ��������� �������
       {
           PageD=3;
       }
       else if(key=='\b')    // 'Del'
       {
         f_icp_errS(Err_Key);
       }

       key=f_dlv_liq(key);
       if(key==ESC)    // ������� � ����
       {
        if(mode_hst == 0)
        {
          if(result_dlv == 3)
            goto m1_1;
          else
            goto m_m5;
        }
        else
        {
          goto mm00;
        }
       }

       if(flag_prok)
       {
         MmiGotoxy(0,0);
         MmiPuts( str_empt );
  MmiGotoxy(0,0);  MmiPrintf("���%d.",n_ASN);
         MmiGotoxy(5,0);
         MmiPrintf("��������");
       }

  // ����������� ����� � ���������� �����
       goto m_m5_1d;

 /*========================================*/
    case 271:/* �������� ������� ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
           goto m0_f1;
         }
         if( (f_timer(tm_md,(long int)1000 )) | fl_md_fst )
         {
           f_md5(1);
           sw_mmi=272;
         }
         break;
 /*========================================*/
    case 272:

       if((key==ESC)||(key==ENTER))  /* ������� �� ��������� �������� */
       {
           goto m0_f1;
       }
       break;
 /*========================================*/
       default:
       if((key==ESC)||(key==ENTER))  /* ������� �� ��������� �������� */
       {
 m_main:

           PassWm=0;

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
int flag_Slv_1=0;
void f_before_MMI()
{
    ftmp_naMMI[0]=analog_scale[0]*NA_scale;
    ftmp_naMMI[1]=analog_scale[1]*NA_scale;

    //10.06.2021 YN
    #if (PressureDrop == 1)
      ftmp_naMMI[2]=analog_scale[2]*NA_scale;
    #elif (PressureDrop == 2)
      ftmp_naMMI[2]=analog_scale[2]*NA_scale;
      ftmp_naMMI[3]=analog_scale[3]*NA_scale;
    #endif

    ftmp_DP=((float)P_dem) / K_F_INT;
  flag_Slv_1=flag_Slv;
}
/*-----------------------------------------*/
void f_after_MMI()
{
int i;
    analog_scale[0]=ftmp_naMMI[0]/NA_scale;
    analog_scale[1]=ftmp_naMMI[1]/NA_scale;

    //10.06.2021 YN
    #if (PressureDrop == 1)
      analog_scale[2]=ftmp_naMMI[2]/NA_scale;
    #elif (PressureDrop == 2)
      analog_scale[2]=ftmp_naMMI[2]/NA_scale;
      analog_scale[3]=ftmp_naMMI[3]/NA_scale;
    #endif

    P_dem = (ftmp_DP * K_F_INT);
    f_init_mki();
    f_count_cf();
  if(flag_Slv_1 != flag_Slv)
  {

          if(flag_Slv !=0 )
          {
             RestoreCom(ComPortSlv );
             InstallCom(ComPortSlv ,ComBaudSlv,Com_lgthSlv,Com_paritySlv,Com_stopSlv);
             if(ComPortSlv==4)
                ShowCom(ComPortSlv,Com_lgthSlv,ComBaudSlv);
          }
          else
          {
           RestoreCom( ComPortHost );
           i=ComPortHost;
           InstallCom(i,ComBaud[i],Com_lgth[i],Com_parity[i],Com_stop[i]);

          }

  }
  flag_Slv_1=flag_Slv;
}