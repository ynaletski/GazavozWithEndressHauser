
//#define ZeroPage 0
//#define ZeroPage 6
//#define ZeroPage 8

#define Adr_ASN (AddrSlv)

#if((Add_pmp == 0) || (Add_pmp == 1))

char *list_md_add[]={
" ��� �������",   //0
" ��� �������",   //1
" � �������� " ,  //2
//" ������� N1 " ,  //2
" ������� N2 " ,  //3
" ������� N3 " ,  //4
" ������� N4 " ,  //5
};

#endif

#define n_mmi_str 7 // ������⢮ ��ப �� ��ᯫ�� MMI
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
//  ���� ᮤ�ন� ᨬ����� ����� � DOS ����஢�� ᨬ�����.
//  ��� �⮡ࠦ���� �� ��ᯫ�� MMI ����室��� ��४���஢��� �
//  ����஢�� Windows (�믮������ �������� dos_win.exe � .bat)
//



float MassStamp=-1000.;
float VolStamp=-1000.;

float vBIG_P=BIG_P;

long int fl_zeroing=0;
#define Time_zeroing (50000)
long int zero_time;

char s_empty[]="                              ";
char str_ESC[]="ESC  ������";

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

  MmiGotoxy(0,0); MmiPrintf("�������������������ͻ         ");
  MmiGotoxy(0,1); MmiPrintf("�����,��  � ��.,�  �         ");
  MmiGotoxy(0,2); MmiPrintf("�������������������͹         ");
  MmiGotoxy(0,3); MmiPrintf("�         �         �         ");
  MmiGotoxy(0,4); MmiPrintf("�������������������Ķ         ");
  MmiGotoxy(0,5); MmiPrintf("�         �         �         ");
  MmiGotoxy(0,6); MmiPrintf("�         �         �         ");
  MmiGotoxy(0,7); MmiPrintf("�������������������ͼ         ");

#endif


#if defined(MMI_ICP)
            //  MmiPrintf("                              ");
  MmiGotoxy(1,1);  MmiPrintf("  ���⥬� ��� ���᪠  ");
  MmiGotoxy(1,2);  MmiPrintf("  ���⥯த�⮢.��� %d.   ",Adr_ASN);
            //             "  ��������� ���稪�          "

     //     if(PageD==0)
          {
  MmiGotoxy(0,3) ; MmiPrintf("����       :                ");
  MmiGotoxy(0,4) ; MmiPrintf("��ꥬ       :                ");


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
  MmiGotoxy(0,3) ; MmiPrintf("��ꥬ       :                ");
  MmiGotoxy(0,4) ; MmiPrintf("��������    :                ");
  MmiGotoxy(0,5) ; MmiPrintf("��������� :                 ");
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
  MmiGotoxy(1,1);  MmiPrintf("  ���⥬� ��� ���᪠  ");
  MmiGotoxy(1,2);  MmiPrintf("  ���⥯த�⮢.��� %d.   ",Adr_ASN);
  MmiGotoxy(0,3) ; MmiPrintf("!�� ���४⥭ ID=%ld ",n_id);
  MmiGotoxy(0,4) ; MmiPrintf(" SN %08lX %08lX",*( unsigned long int *)(ID_ADDR),*( unsigned long int *)(ID_ADDR+4) );
  MmiGotoxy(0,5) ; MmiPrintf("������� � ���⠢騪� �� ID ");
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
            MmiPrintf(" ����  %g ��",dose_dlvr);
          else
            MmiPrintf(" ����  %g � ",dose_dlvr);
         }
        else
           MmiPrintf(" ���� ��� ����");

       MmiGotoxy(0,6);  MmiPuts("ESC - ����");

}
//-------------------------------------
int un_mmi1=1;
int un_mmi2=2;
int un_mmi3=3;
char *list_un_mmi[]={
"",
" ��ꥬ,�   " ,  //1
"�㬬�,��  " ,  //2
"����,��/� " ,  //3
"����,��   " ,  //4
"�㬬�,��  " ,  //5
"����,��/��" ,  //6
};
//-------------------------------------
int CRC_err=0;
//-------------------------------------
void f_prn_CRC_error()
{
 MmiGotoxy(0,1);   MmiPrintf(" ��� %d.",Adr_ASN);
 MmiGotoxy(0,2);   MmiPrintf("!�訡�� ����஫쭮� �㬬�   ");
 MmiGotoxy(0,3);   MmiPrintf("!��ࠬ���� ������         ");
 MmiGotoxy(0,4);   MmiPrintf("!����室��� ��७���ன��   ");
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
              MmiGotoxy(0,4);  MmiPuts(" ���⭮���     |   ���室      ");
              MmiGotoxy(0,5);MmiPrintf("%8.2f ��/�3 | %8.1f ��/�  ",s_MVD[0].Dens,s_MVD[0].FlowM);
            }
            else
            {
    //        MmiGotoxy(0,4);  MmiPuts(" ���⭮���     |   ���室      ");
    //        MmiGotoxy(0,5);MmiPrintf("%8.2f ��/�3 | %8.1f �/�  ",s_MVD[0].Dens,s_MVD[0].FlowV);

              if( flag_AD != 0)
              {
                MmiGotoxy(0,4);  MmiPuts("  ���⭮���    |���������   ");
                MmiGotoxy(0,5);  MmiPrintf("%7.2f ��/�3  | %7.2f C     ",Dens_a,Temp_a);
              }
              else
              {

                if(s_MVD[0].TempR < -49.5)
                {
                MmiGotoxy(0,4);  MmiPuts("����,��/�3|����MVD,C|����,�/� ");
                 MmiGotoxy(0,5); MmiPrintf(" %8.2f  | %7.2f |%8.1f ",s_MVD[0].Dens,s_MVD[0].Temp,s_MVD[0].FlowV);
                }
                else
                {
                MmiGotoxy(0,4);  MmiPuts("����,��/�3|������.,C|����,�/� ");
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
              MmiGotoxy(0,4);  MmiPuts(" ��15,��/�3|��ꥬ15,�|����,���");
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
  if(valve_mode==1)      MmiPuts("����.���:");
  else if(valve_mode==2) MmiPuts("����� ��:");
  else if(valve_mode==3) MmiPuts("���.���:");

     if( OUT_VAR & OUT2  )
       MmiPuts("1       ");
     else
       MmiPuts("0       ");

     MmiGotoxy( 0,5);
  if(valve_mode==1)      MmiPuts("����.���:");
  else if(valve_mode==2) MmiPuts("����� ��:");
  else if(valve_mode==3) MmiPuts("~��.����:");
     if( OUT_VAR & OUT1  )
       MmiPuts("1       ");
     else
       MmiPuts("0       ");



     MmiGotoxy(15,4);   MmiPuts("������� :");
     if( OUT_VAR & OUT5  )
       MmiPuts("1  ");
     else if( OUT_VAR & OUT6  )
       MmiPuts("2  ");
     else
       MmiPuts("0  ");

     MmiGotoxy(26,4);   MmiPuts("�:");
     if( OUT_VAR & OUT3  )
       MmiPuts("1      ");
     else
       MmiPuts("0      ");

     MmiGotoxy(15,5);   MmiPuts("��.���. :");
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
         MmiPrintf("�ᥣ� %7.1f ��, %7.1f �  ",s_MVD[0].MassI-MassStamp,s_MVD[0].VolI-VolStamp);
/*
  if ( Flag_mass != 0 )
    MmiPrintf("  �ᥣ� ���饭� %8.2f ��  ",s_MVD[0].MassI-MassStamp);
  else
    MmiPrintf("  �ᥣ� ���饭� %8.2f �   ",s_MVD[0].VolI-VolStamp);
 */
}
//-------------------------------------
void f_prn_MassSt_rcv()
{
  MmiGotoxy(0,1);
  if ( Flag_mass != 0 )
    MmiPrintf("   �ᥣ� �ਭ�� %8.2f ��  ",s_MVD[0].MassI-MassStamp);
  else
    MmiPrintf("   �ᥣ� �ਭ�� %8.2f �   ",s_MVD[0].VolI-VolStamp);
}
//-------------------------------------
void f_prn_error()
{
   f_clr_scr_MMI();

//#if( Test == 0)
   if(flag_mvd_ton)
   {
  MmiGotoxy(1,1);  MmiPrintf("  ���⥬� ��� ���᪠  ");
  MmiGotoxy(1,2);  MmiPrintf("  ���⥯த�⮢.��� %d.   ",Adr_ASN);

  MmiGotoxy(0,3);  MmiPuts(s_empty);
  MmiGotoxy(0,4);  MmiPrintf("  !���樠������ ��室���� ");
  MmiGotoxy(0,5);  MmiPuts(s_empty);
   }
   else
//#endif
   {

    MmiGotoxy(0,1);   MmiPrintf(" ��� %d.",Adr_ASN);
    MmiGotoxy(0,2);   MmiPrintf("!�訡�� �㭪樮��஢���� ");
    MmiGotoxy(0,3);   MmiPrintf("Sht-F1 �⮡ࠦ���� �訡��");
    MmiGotoxy(0,4);   MmiPrintf("Sht-ESC ���⪠ �訡��   ");
   }
}
//-------------------------------------
void  f_disp_error()
{ // �ᯥ��뢠�� �訡��

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
 MmiGotoxy(0,i1++);   MmiPrintf("�訡�� � �ࠩ��� %9s:",ICPl_DEV->name );
  }
  else
  {
 MmiGotoxy(0,i1++);   MmiPrintf("�訡�� ��⥬� ���:           ");
  }
    if(i1 >= n_mmi_str) return;
    itmp=ICP_error[i];
  if(i != icp_lst_max)
  {
    if(itmp & RD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("�訡�� �⥭�� ���ன�⢠");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WR_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("�訡�� ����� � ���ன�⢮");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("�訡�� Watch Dog");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Drive_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("�訡�� � ���ன�⢥,%02X", (itmp>>8) & 0xff);
    if(i1 >= n_mmi_str) return;
    }

  }
  else //(i == icp_lst_max)
  {
    if(itmp == EEE_CRC_error)
    {
MmiGotoxy(0,i1++); MmiPrintf("�訡�� CRC EEPROM ������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_erase_error )
    {
MmiGotoxy(0,i1++); MmiPrintf("�訡�� ��࠭�� FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_wr_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("�訡�� ����� �� FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_gas_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("���室���� �� ��������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_Z_mass_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("����-� �� ���㫨� �����");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_F_dat_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("��� ������.������ ��� ��ୠ��");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & DNS_not_off)
    {
MmiGotoxy(0,i1++); MmiPrintf("��窠 �� ���� ");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_Press)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ �������� �� ���� ");
    if(i1 >= n_mmi_str) return;
    }
//  if(itmp & exm_err )
//  {
//MmiGotoxy(0,i1++); MmiPrintf("������� ����� �����⨬���");
//    if(i1 >= n_mmi_str) return;
//  }
//    if(itmp & exp_err )
//    {
//MmiGotoxy(0,i1++); MmiPrintf("��५�� ����� �����⨬���");
//    if(i1 >= n_mmi_str) return;
//    }
    if(itmp & Gun_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("���� �⪫�祭 �� ���᪥");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == WD_host)
    {
MmiGotoxy(0,i1++); MmiPrintf("��� �裡 � HOST");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == No_flow )
    {
MmiGotoxy(0,i1++); MmiPrintf("��⮪ �४�⨫��");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & ES_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ES �� ���᪥");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & UZA_off )
    {
     switch (flagE_UZA)
     {
      case UZA_E:
MmiGotoxy(0,i1++); MmiPrintf("��� ��� �� ���᪥");
        if(i1 >= n_mmi_str) return;
        break;
      case LVL_E:
MmiGotoxy(0,i1++); MmiPrintf("������ �஢��� �� ���᪥");
        if(i1 >= n_mmi_str) return;
        break;
      case ID_E:
MmiGotoxy(0,i1++); MmiPrintf("�����४�� ID ");
        if(i1 >= n_mmi_str) return;
        break;
      case TRAP_E:
MmiGotoxy(0,i1++); MmiPrintf("�࠯ �� � ࠡ.����樨 ");
        if(i1 >= n_mmi_str) return;
        break;
      case CONS_E:
MmiGotoxy(0,i1++); MmiPrintf("���᮫� �� � ࠡ.����樨 ");
        if(i1 >= n_mmi_str) return;
        break;
     }
    }
    if(itmp & MVD_cfg )
    {
MmiGotoxy(0,i1++); MmiPrintf("�訡�� ����.��室-� ");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == MotNotStop )
    {
MmiGotoxy(0,i1++); MmiPrintf("���� ���� �� ��.");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp == DLT_off)
    {
MmiGotoxy(0,i1++); MmiPrintf("���� �몫. �� ���᪥");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & MVD_com)== MVD_com )
    {
MmiGotoxy(0,i1++); MmiPrintf("��� �裡 � ��夬.");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & Hst_alm)==Hst_alm)
    {
MmiGotoxy(0,i1++); MmiPrintf("����� �� Host");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & No_Drv)==No_Drv)
    {
MmiGotoxy(0,i1++); MmiPrintf("�ࠩ���� MVD,7060 �� ����祭�");
    if(i1 >= n_mmi_str) return;
    }
  }
   }
   if(i2==0)
   {
    MmiGotoxy(5,2); MmiPrintf("�訡�� ���");
    MmiGotoxy(2,4); MmiPrintf("Enter - �த������");
   }
}
//-------------------------------------
void f_drv_list_MMI(int *nn)
{ // �������� ᯨ᮪ �ࠩ��஢ ���ன��
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
    MmiGotoxy(0,0); MmiPuts("        ���᮪ �ࠩ��஢      ");
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
{ // �������� ����⨪� �ࠩ��஢ ���ன��
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
    MmiGotoxy(0,0);  MmiPuts(" ����⨪� ࠡ��� �ࠩ��஢");
    MmiGotoxy(0,1);  MmiPuts(" N     ���    ��᫠��  �訡��");
    for(i2=0;i<i1;i++,i2++)
    {
      ICPl_DEV=ICP_dd[i];
      if(ICPl_DEV==NULL) break;
      MmiGotoxy(0,3+i2);
//         MmiPuts(" N     ���    ��᫠��  �訡��");
//                 "xx.....xxxxx  xxxxxxx xxxxxxx"
         MmiPrintf("%2d%10s  %7ld %7ld",i+1,ICPl_DEV->name,ICPl_DEV->n_transaction,ICPl_DEV->n_timeout_error+ICPl_DEV->n_CRC_error);
    }
}
//-------------------------------
//-------------------------------
void f_mod_list_MMI(int *nn)
{ // �������� ᯨ᮪ �����㦥���� ���㫥�
int i,i1,i2;
 char str[31];

  struct icp_mod *ICPl_MOD;

  i1=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
  f_clr_scr_MMI();
  if(i1==0)
  {
    MmiGotoxy(3,2);   MmiPuts("    ���᮪ ����." );
    MmiGotoxy(3,3);   MmiPuts("�ᯮ���� ���� ���" );
    MmiGotoxy(3,4);   MmiPuts("  ���������� ᯨ᪠." );
  }
  else
  {
    MmiGotoxy(0,0);    MmiPuts(" ���᮪ �����㦥���� ���㫥�  ");
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
{ // �������� ���ﭨ� ���᪠ �� ⥪�騩 ������
  int year,month,day,hour,min,sec;
 MmiGotoxy(0,0);   MmiPrintf("T���饥 ���祭�� ���稪�");
 MmiGotoxy(0,3);   MmiPrintf("  ���     �६�     ����,��");
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
 //  �⮡ࠦ���� �����,���⭮��,⥬�������,��������
 //  ����饥 ���祭��.
 MmiGotoxy(0,0);   MmiPrintf("����騥 ��������� ��室����");
 MmiGotoxy(0,1);   MmiPrintf(" ����      %10.3f ��",s_MVD[0].MassT);
 MmiGotoxy(0,2);   MmiPrintf(" ��ꥬ      %10.3f � ",s_MVD[0].VolT);
// MmiGotoxy(0,1);   MmiPrintf(" ����      %10.3f ��",s_MVD[0].MassI);
// MmiGotoxy(0,2);   MmiPrintf(" ��ꥬ      %10.3f � ",s_MVD[0].VolI);
// MmiGotoxy(0,2);   MmiPrintf(" ��ꥬ      %10.3f ��",s_MVD[0].MassT);
 MmiGotoxy(0,3);   MmiPrintf(" ���室    %10.2f ��/�",s_MVD[0].FlowM);
 MmiGotoxy(0,4);   MmiPrintf(" ���⭮��� %10.2f ��/�3",s_MVD[0].Dens);
// MmiGotoxy(0,2);   MmiPrintf(" ��������     %6.3f ���  ",s_MVD[0].Press);
// MmiGotoxy(0,3);   MmiPrintf(" ���������  %6.2f �ࠤ.C",s_MVD[0].TempR);
 MmiGotoxy(0,5);   MmiPrintf(" ����.��夬.  %6.2f �ࠤ.C",s_MVD[0].Temp);
 MmiGotoxy(0,6);   MmiPuts(" ESC-����,F2-��.�.⥪.");
}
//-------------------------------
void f_prn_lst_hour()
{ // �������� ���ﭨ� ���᪠ �� ��᫥���� ���. ��

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // ⥪�饥 �६�

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
   MmiGotoxy(5,3);   MmiPrintf("����� ����������");
  }
  else
  {
  m_ok:
 MmiGotoxy(0,0);   MmiPrintf("   ���祭�� ���稪� ��� ");
 MmiGotoxy(0,1);   MmiPrintf(" �� ��᫥���� ����� �� ");

 MmiGotoxy(0,3);   MmiPrintf("  ���     �६�     ����,��");
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
{ // �������� ���ﭨ� ���᪠ �� 㪠������ ����

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;
 // ��।������ �६��� ��᫥���� ����� � ��ୠ�

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // ⥪�饥 �६�

 tim_000=adate00;
 tim_000.hour=ahour00.hour;
 tim_000.min=ahour00.min;
 tim_000.sec=ahour00.sec;

 ltime0=f_get_time_t(&tim_000);

 MmiGotoxy(0,0);   MmiPrintf("   ���祭�� ���稪� ���");
 MmiGotoxy(0,1);   MmiPrintf("     �� 㪠������ ����  ");

 MmiGotoxy(0,3);   MmiPrintf("  ���     �६�     ����,��");
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
{ // �������� ���ﭨ� ���᪠ �� ��᫥���� 5 ��⮪

 struct tm *tdat;

int year,month,day,hour,min,sec,i;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // ⥪�饥 �६�

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
   ltime2= f_get_time(ar_str_ptr); // ��᫥���� ������

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

 MmiGotoxy(0,0);   MmiPrintf("  ���     �६�     ����,��");
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
    MmiGotoxy(0,6);   MmiPuts("ESC,Enter - �த������");

  }
 }
 else goto m_ok;
 return;

 m_bad:
   MmiGotoxy(5,3);   MmiPrintf("����� ����������");
 return;
}
//-------------------------------
char *rcv_mm[]={
"����",
"�ਥ�",
};
char *Rcv_mm[]={
"����",
"�ਥ�",
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
     MmiPrintf("%10.3f ��",a_str->MassI);
  else
     MmiPrintf(" ------- " );
// i_ret=i_n+1;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;

 MoveToXY(0,i_ret);

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
    MmiPrintf("���� %s�.",rcv_mm[f_rcv]);
    goto m_val0;
  case evt_start_f:
    MmiPrintf("���� %s�.",rcv_mm[f_rcv]);

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

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

   MmiPrintf("����.%6.3f��/�3;" ,a_str->u.fill.Density);
   MmiPrintf("�=%6.2fC;" ,a_str->u.fill.Temp);

   i_ret++;
// i_ret=i_n+3;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%6.3f ���;" ,a_str->u.fill.UnitPrice);
//  MmiPrintf("�=%6.2fC;" ,a_str->u.fill.Amount);

    break;

  case evt_cont_f:
    MmiPrintf(" �த������� %s�,",rcv_mm[f_rcv]);
    goto m_val;
  case evt_exm_f:
    MmiPrintf(" �����襭�,������� ");

m_val:

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    if(a_str->u.fill.VolT != vBIG_P)
         MmiPrintf(" ��.%9.3f ��,%9.3f �",a_str->u.fill.VolT,a_str->u.fill.Amount );

// i_ret=i_n+3;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("����.%6.3f ��/�3;" ,a_str->u.fill.Density);
    MmiPrintf("�=%6.2fC;" ,a_str->u.fill.Temp);

// i_ret=i_n+4;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%6.3f ��� ;" ,a_str->u.fill.UnitPrice);
//    MmiPrintf("�=%6.2fC;" ,a_str->u.fill.Amount);

    break;

  case evt_exp_f:
    MmiPrintf(" �����襭�,��५��");
    goto m_val;

  case evt_end_gas:
    MmiPrintf(" %s ���.��� ���.䠧�",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_end_f:
    MmiPrintf(" �����襭� ��  ");
    goto m_val;

  case evt_est_f:
    MmiPrintf(" %s ��ࢠ� ��������",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_est_fh:
    MmiPrintf(" %s ��ࢠ� Host ",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_err_f:
    MmiPrintf(" %s ��ࢠ� �訡���",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_eq_pr :
    MmiPrintf("���� ���.����. ��஢�� 䠧");
    goto m_val;
  case evt_stop_eq :
  printf("������.���.����. ��஢�� 䠧");
    goto m_val;

  case evt_ep1_f:
    MmiPrintf(" %s ��ࢠ�,Host",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_overfl:
    MmiPrintf(" %s ��ࢠ� ���.��⮪�",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_ES_off:
    MmiPrintf(" %s ���.����.������� ES",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_UZA_off:
    MmiPrintf(" %s ���.��� ᨣ���� ���",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_LVL_off:
    MmiPrintf(" %s  ��ࢠ�: �஢���.",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_TRAP_off:
    MmiPrintf(" %s  ��ࢠ�: �࠯.",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_CONS_off:
    MmiPrintf(" %s  ��ࢠ�: ���᮫�.",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_DLT_off:
    MmiPrintf(" %s ���.���� �� ����祭",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_wd_pmp:
    MmiPrintf(" %s ���.WD PMLAN",Rcv_mm[f_rcv]);
    goto m_val;


  case evt_no_dev:
    MmiPrintf(" ���� �� �ਭ��.�� ���.�ࠩ�");
    goto m_val;

  case evt_clr_err:
    MmiPrintf(" ���� �訡��. ");
    break;

  case evt_MVD_CL_strt:
    MmiPrintf(" ���� �����஢�� ��室����");
    break;

  case evt_MVD_CL_BS1 :
    MmiPrintf(" !����⪠ ���.���.�� ��.");
    break;

  case evt_MVD_CL_BS2 :
    MmiPrintf(" !���� �� ���� ���.���.");
    break;

  case evt_MVD_CL_OK :
    MmiPrintf(" �����஢�� ��室���� OK");
    break;

  case evt_MVD_CL_TM :
    MmiPrintf(" ������� �����஢�� ��室��.");
          //  |                              |

    break;

  case evt_ch_date:
    MmiPrintf(" ��� ��������.");
    break;

  case evt_ch_time:
    MmiPrintf(" �६� ��������.");
    break;
  case evt_ch_sum:
    MmiPrintf(" ���室 �� ��⭥� �६�.");
    break;
  case evt_ch_win:
    MmiPrintf(" ���室 �� ������ �६�.");
    break;
  case evt_res:
    MmiPrintf(" ������� ����");
    break;
  case evt_Slot:
    MmiPrintf(" MVD:���䨣���-� ���ன�⢠");
    break;
  case evt_chg_param:
    if(a_str->u.fill.VolT == Par_VF)
    {
     MmiPrintf(" !���.����.��ꥬ�");
    }
    else if(a_str->u.fill.VolT == Par_MF)
    {
     MmiPrintf(" !���.����.�����");
    }
    else if(a_str->u.fill.VolT == Par_MC)
    {
     MmiPrintf(" !���.�१.�.���.");
    }
    else if(a_str->u.fill.VolT == Par_PASS)
    {
     MmiPrintf(" !������� ��஫�");
    }
    else if(a_str->u.fill.VolT == Par_ID)
    {
     MmiPrintf(" !������� ID");
    i_ret++;
    if(i_ret>=n_mmi_str) return i_ret;
    MoveToXY(0,i_ret);

    MmiPrintf("�뫮 :%ld; ",(long int)a_str->u.fill.Amount  );
    MmiPrintf("�⠫�:%ld" ,(long int)a_str->u.fill.UnitPrice);
    break;
    }
    else
     {
//    MmiPrintf(" !���. ��ࠬ. ");
      MmiPrintf(" !������� ��ࠬ��� ");
      MmiPrintf("N%g ",a_str->u.fill.VolT );
     }

// i_ret=i_n+2;
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    MmiPrintf("�뫮:%g; ",a_str->u.fill.Amount  );
    MmiPrintf("�⠫�:%g" ,a_str->u.fill.UnitPrice);
    break;
  case evt_exit:
    MmiPrintf(" ������� ��室 � ���");
    break;
  case evt_re:
    MmiPrintf(" �⥭�� ����.�� EEPROM");
    break;
  case evt_re_err:
    MmiPrintf(" �訡�� �⥭�� ����.�� EEPROM");
    break;
  case evt_we:
    MmiPrintf(" ������ ����. � EEPROM");
    break;
  case evt_we_err:
    MmiPrintf(" ��.����� ����. � EEPROM");
    break;

  case evt_wrong_start:
    MmiPrintf(" C��� �� �ਭ��.�訡��.");
    goto m_val;

  case evt_err:
  case evt_none:
 mm_0:
    itmp=0;
    for(ii=0;ii<=icp_lst_max ;ii++)
      itmp |= a_str->u.err.err[ii];
  if(itmp)
  {
    MmiPrintf(" �訡��:");
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
 MmiPrintf(" �訡�� ��� ");

  break;

  case evt_t_on:
 MmiPrintf(" ����祭�� ���ன�⢠");
    break;
  case evt_t_off:
 MmiPrintf(" �몫�祭�� ���ன�⢠");
    break;
  default:
 MmiPrintf(" ����⨥ �� �����⭮");
   break;
 }
 return i_ret;
}

//----------------------------------
void f_MVD_M1()
{
// �⮡ࠦ��� ��ࠬ���� MVD  �� MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� �⥭�� MVD");
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
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("TXM �����: %d",s_MVD[0].i);}
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
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("�����⥫� �����:     %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=281;
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("�����⥫� ��ꥬ�:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 33:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=283;
   sw_mvd_m1=14;
   break;

  case 14:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("�����⥫� ���⭮��: %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 34:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=195;
   sw_mvd_m1=15;
   break;

  case 15:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("�१ ����.��室�:   %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 35:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=197;
   sw_mvd_m1=16;
   break;

  case 16:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("�१ ��. ��室�:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 36:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=149;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,sw_MMI_cur++); MmiPrintf("�१ ���⭮�� :     %.6f",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  }

}
/* ---------------------------------------- */
void f_MVD_M1f()
{
// �⮡ࠦ��� ��ࠬ���� ���४樨 ��室�  MVD  �� MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
     MoveToXY(0,4); MmiPrintf(" !������� �⥭�� MVD");
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
   { MoveToXY(0,4);MmiPrintf("�����⥫� �����:    %.6f",s_MVD[0].f);}
     k_m_flow=s_MVD[0].f;

  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=281; // �����⥫� ��ꥬ�
//   s_MVD[0].r_addr=195;  // Cuttoff for mass flow
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,5);MmiPrintf("�����⥫� ��ꥬ�:   %.6f",s_MVD[0].f);}
// { MoveToXY(0,5); MmiPrintf("�१ �.���.: %10.2f ��/�",s_MVD[0].f);}
   k_v_flow=s_MVD[0].f;
   ff_serv=NULL;
   Flag_f_corr=1;
   break;
 }
}
/* ---------------------------------------- */
void f_MVD_M1s()
{
// �⮡ࠦ��� ��ࠬ���� ���४樨 ��室�  MVD  �� MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
     MoveToXY(0,4); MmiPrintf(" !������� �⥭�� MVD");
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
   { MoveToXY(0,4); MmiPrintf("�१ �. ���.: %8.2f ��/�",s_MVD[0].f);}
     k_m_flow=s_MVD[0].f;

  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=197;  // Cuttoff for mass flow
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,5); MmiPrintf("�१ ��.���.: %8.3f �/ᥪ",s_MVD[0].f);}
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
// �⮡ࠦ��� ����� MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� �⥭�� MVD");
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("���室 �. : %f %s",s_MVD[0].f,unit1);}
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("���� ���.: %10.3f %s",s_MVD[0].f,unit2);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("���� ���.: %10.2f %s",s_MVD[0].f,unit2); }
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("���室 ��.: %f %s",s_MVD[0].f,unit3);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("��ꥬ ���.: %10.3f %s",s_MVD[0].f,unit4);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("��ꥬ ���.: %10.2f %s",s_MVD[0].f,unit4);}
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
      MoveToXY(0,sw_MMI_cur++);MmiPrintf("���⭮���  :%.5f %s",s_MVD[0].f,unit5);
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
    MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.��⮪�: %.3f %s",s_MVD[0].f,unit6);
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

}
/* ---------------------------------------- */
void f_MVD_MM2()
{
char *unit;
// �⮡ࠦ��� ����� MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� �⥭�� MVD");
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("���室 �. : %f %s",s_MVD[0].f,unit1);}
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("���� ���.: %10.3f %s",s_MVD[0].f,unit2);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("���� ���.: %10.2f %s",s_MVD[0].f,unit2); }
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("���室 ��.: %f %s",s_MVD[0].f,unit3);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("��ꥬ ���.: %10.3f %s",s_MVD[0].f,unit4);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("��ꥬ ���.: %10.2f %s",s_MVD[0].f,unit4);}
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
     MoveToXY(0,sw_MMI_cur++); MmiPrintf("���⭮���  :%.5f %s",s_MVD[0].f,unit5);
     MMIDens=s_MVD[0].f;
  }
  else
  {
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("�訡�� �⥭��");
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
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.��⮪�: %.3f %s",s_MVD[0].f,unit6);
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

}
/* ---------------------------------------- */
void f_MVD_M3()
{
int i,i2;
unsigned long int ltmp,i1;
// �⮡ࠦ��� �訡�� MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� �⥭�� MVD");
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
   MoveToXY(0,3); MmiPrintf("         �訡�� ���.          ");
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
          MmiPrintf("   �訡�� ��室����:");
      else if( i>1)
          MmiPrintf("   �訡�� ��室����:");
       i2=1;
     }
     else
     {

      MoveToXY(0,0);
         MmiPrintf("����ﭨ�/�訡�� ��室����:");
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

"MMI:�����",                 //  0
"������ ��᫥ ���.1",         //  1
"������ ��᫥ ���.2",         //  2
"������ ��᫥ ���.3",         //  3
"��ࠬ��� �����. 1",          //  4
"MMI:���� CRC",               //  5

"7017/1:�����",                //  6
"�����.१���஢",            //  7
"����.1 N १-�",              //  8
"����.2 N १-�",              //  9
"P_demand",             // 10
"K_D",               // 11
"K_P         ",                // 12
"K_I         ",           // 13
"Mode P    ",                 // 14
"Addr Modbus  ",             // 15
"Delta :�����",                // 16
"���� Slave      ",             // 17

"7060/1:�����",                 // 18
"K_FD",                   // 19
"K_FP",                   // 20
"K_FI",                   // 21
"���� ���.����.",        // 22
"",               // 23

"����.1 ��/�3",           // 24
"����.2 ��/�3",           // 25
"����.���-�,�/�",        // 26
"���.���.���-�,��",      // 27
"V �஬뢪�,� ",          // 28
"T ���.�� ���.,��",       // 29

"T ���.��᫥ ���,��",          // 30
"T �ࠡ.���-�,��",       // 31
"���.T �몫.�-�,��",     // 32
"V �।�.���,� ",          // 33

#if(Add_pmp == 1)
"������ N ���.",            // 34
#else
"���.���.�2 N ���.",            // 34
#endif

"��.�-� N ���.",           // 35

"����.ICP:CRC 䫠�",            // 36

"WDOG/1:�����",                // 37
"WDOG/1:����� ����",           // 38
"WDOG/1:��ਮ�,�� ",            // 39
"WDOG/1:����প�,��",           // 40
"WDOG/1:���� CRC",              // 41

"T �஢.�.�.,��  ",                // 42
"T ��⨤�,��",           // 43
"��⮪ ����,��/�",            // 44
"P min , ���",           // 45
"",              // 46

"",           // 47
"",        // 48

"7060/2:�����.WD",           // 49
"7060/2:����.WD,0.1�",        // 50

"MVD:�����",                 //  51
"",         //  52
"",                  //  53
"",              //  54
"",             //  55

"TSD:�����",       //  56
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
"COM3 �������",           // 72

"COM4 �������",           // 73
"",              // 74
"",           // 75
"",           // 76

"",        // 77
"����� �室� Gun",         // 78
"�����-� �室� Gun",       // 79

"������ ��� N ���.",        // 80
"������ ��� N ���.",        // 81
"���� ���.����.",        // 82
"���� PUMALAN",            // 83
"����� PUMALAN",           // 84
"",        // 85
"",        // 86
"",        // 87
"��� ��.�롮ન",           // 88
"���室 �� ���.��.",       // 89
"------------------",       // 90
"P ������ 誠��,���",       // 91
"P ᬥ饭��,    ���",       // 92
"T ������ 誠��,C",         // 93
"T ᬥ饭��,    C",         // 94
"��ࠬ��� �����. 2",        // 95
"��ࠬ��� �����. 3",        // 96
"������-� �����,��",        // 97
"���.���� �.��.1",         // 98    p1-p6.CLV
"���.���� �.��.2",         // 99
"�६� �ࠡ��.���.1",       // 100
"�६� �ࠡ��.���.2",       // 101
"���.����.��.MMI,��",      // 102
"����.����.�.MMI,��",       // 103
"������.�� M 0...1",        // 104   p1-p3.KA
"������.�� T 0...1",        // 105
"���-�� ���.���.,��",       // 106

"��⮢� ०�� 1/0",       // 107    p1.CTRL
"���-�� ���.MVD,��",       // 108    p2.CTRL
"�१ ���.��� TST",        // 109    p3.CTRL

"��ࢨ筠� M,��",           // 110    p1-p5.DSC
"���࠯����-� M,��",        // 111
"��室 �� �ࠡ.��",       // 112
"���४�� M,��",            // 113
"���४�� T,��",           // 114


"���.'�������' N ��.",      // 115
"���.'�������'�.���",      // 116
"T ����� ���.��.,�� ",      // 117
"T ����� �몫.��.,�� ",     // 118
"����� t ��.0-2",          // 119
"����� ���᪠ 1-3",        // 1 2 0

// DNC
"����.㬥���.����",        // 121
"���� �⠡-�.����",       // 122
"����প� ���.��1,��",      // 123
"Tmin �몫. ��1,��",       // 124
"Tmin ���.  ��1,��",        // 125

"���稪 �஢�� N ��.",      // 126
"���稪 �஢. �.���",      // 127
"��.  =Start=  N ��.",        // 128
"��.  =Start= �.���",      // 129
"��.  =Stop=   N ��.",      // 130
"��.  =Stop=  �.���",      // 131
"������ '����' N ��.",      // 132
"������ '����'�.���",      // 133
"MAX �������",              // 134
"MAX ��५��",              // 135
"WD ���.MASTER,��",        // 136
// FLCH
"T ����� ��, ⨪",       // 137
"M ���.����.��, ��",       // 138
"M ��।.��९ BIG",        // 139
"M ��।.��९ LTL",        // 140
"�६� ��९���,⨪",       // 141

#if(Add_pmp == 1)
"���.���� N ���.",        // 142
#else
"���.���.�1 N ���.",        // 142

#endif

"���਩��� ��. N ��.",      // 143
"���਩��� ��.�.���",      // 144
"������ ���  . N ��.",      // 145
"������ ��� 䫠� ���",      // 146
"��������-� N ���.",       // 147
"�������� N ����.��.",     // 148
"�������.N ����.��.",     // 149
"-------------------",     // 150
"f  ����, 0.01 ��",     // 151
"T ࠧ�.����,0.1�",      // 152
"����প� ���.��2,��",     // 153
"���.�몫.����,��",      // 154
"T ��.����,0.1�",      // 155
"���.Vol   �.��.1",        // 156   p1-p2.CLM
"���.Vol   �.��.2",        // 157
"���.���.��/�. ",         // 158
"���� 1,��  ",            // 159
"����.1,��/�. ",           // 160
"���� 2,��  ",            // 161
"����.2,��/�. ",           // 162
"���� 3,��  ",            // 163
"����.3,��/�. ",           // 164
"��� ���⥯த��",       // 165
"",
};
//-------------------------------

char *list2_dsr[]={
" �����.������",            //  0
" ����.���,����.",         //  1
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
   {  // ������� �᫮��� ���祭��
     key=DATA;  // �ਧ��� ����砭�� ����� ��ப�
     sw_fst=0;
   }
   else if(i==fst_ESC)
   {
     key=DATA_ESC;  // �ਧ��� ����砭�� ����� ��ப�
     sw_fst=0;
   }
   else if( MmiKbhit())
   {  // ���� ����㯨�襣� ᨬ���� �� ����������
    key=MmiGetch();

    if(key==F1)
    {
      OUT_VAR ^= OUT8;
      return 0;
    }

   }
   else if(sw_fst==0)
   {
    key=PASS; // �ਧ��� 宫��⮣� ��室� (��� ���������� ᨬ����)
              // �ᯮ������ ��� ������樨 ����������� ���祭��
   }
   else return 0;

   switch(sw_mmi)
    {
     case 0: /*���������*/


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
          MmiPuts("������ ID:" );
          sprintf( fst_str,"%8ld",n_id);
          fst_n=9;
          sw_fst=1;
          MmiGotoxy(10,3);
  //      MmiGotoxy(15,3);
          SetDisplayPage(15); // ���� ���祭��
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
          MmiPuts("������ ����� ��࠭���:" );
          sprintf( fst_str,"%d",num_page);
          fst_n=2;
          sw_fst=1;
//        MmiGotoxy(10,3);
          MmiGotoxy(15,3);
          SetDisplayPage(15); // ���� ���祭��
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
        {  // ���⪠ �訡��

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);
          sw_mmi=26;
          f_cl_error();
          MmiGotoxy(5,2);    MmiPuts("   �訡�� ��饭�   ");
          MmiGotoxy(0,4);    MmiPuts(" Enter - �த������ ");

        }
        else if (key==Sht_F1)
        {  // �ᯥ�⪠ �訡��

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
          MmiPrintf(" �訡�� ����᪠ �����஢�� ");
          f_wr_evt(evt_MVD_CL_BS2);
  m_SF2:
          MmiGotoxy(0,6); MmiPuts("ESC,ENTER  ������");
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
            MmiGotoxy(0,0);    MmiPrintf("��� %d.   ���� ",Adr_ASN);

          if((WD_PMP_Fl != 0) && (flag_Slv == 2));
          else
            {
              MmiGotoxy(0,1);    MmiPuts("1  ���� ���⥯த�⮢");
              flag_resv=0;
            }

           if( NN_resv > 0)
           {


#if((Add_pmp == 0) || (Add_pmp == 1))
            MmiGotoxy(0,2);    MmiPuts("2  ���� ०��� ࠡ���");
#endif

#if(Add_pmp == 2)
            MmiGotoxy(0,2);    MmiPuts("2  ���� ����� १����");
#endif



           }
            MmiGotoxy(0,3);    MmiPuts("3  ��ᬮ�� ��ୠ�� ᮡ�⨩");
            MmiGotoxy(0,4);    MmiPuts("4  ��ࢨ�� �㭪樨");
            MmiGotoxy(0,5);    MmiPuts("5  ����騥 ��������� ��夬.");
            MmiGotoxy(0,6);    MmiPuts("ESC  ������");

#endif

#if defined(MMI_NEW)

  MmiGotoxy(0,0); MmiPrintf("�������������������ͻ         ");
  MmiGotoxy(0,1); MmiPrintf("�����,��  � ��.,�  �         ");
  MmiGotoxy(0,2); MmiPrintf("�������������������͹         ");
  MmiGotoxy(0,3); MmiPrintf("� 1234    �         �         ");
  MmiGotoxy(0,4); MmiPrintf("�������������������Ķ         ");
  MmiGotoxy(0,5); MmiPrintf("�Test NN  �  LOAD   �         ");
  MmiGotoxy(0,6); MmiPrintf("�         �  731    �         ");
  MmiGotoxy(0,7); MmiPrintf("�������������������ͼ         ");

#endif



          break;
       }
       else if(key==PASS)
        {  // �⮡ࠦ���� ���� � �६���

         if( id_ok ==0) break;
         if((FL_err|CRC_err) == 0)
         {
          //if(PageD==0)
            {
               MmiGotoxy(14,3);  MmiPrintf("%9.2f ��    ",s_MVD[0].MassI);
               MmiGotoxy(14,4);  MmiPrintf("%9.2f �     ",s_MVD[0].VolI);

              if(I7017C[0].status)
              {
               MmiGotoxy(2,5);   MmiPrintf("%5.3f ���  ",s_MVD[0].Press);
               MmiGotoxy(17,5);  MmiPrintf("%6.2f �ࠤ.C",s_MVD[0].TempR);
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
    case 11:  /*���� �롮� �窨 ��� ��ᬮ�� ��ࠬ��஢ */
       n_adc_mm=0;
       if(key==ESC)    /* ���室 � ���� M3, ��ࢨ�� �㭪樨 */
       {
         goto m_m3;
       }
       else if(key=='1')  // ������ ᯨ᮪ #1
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=0;
        }
       else if(key=='2')  // ������ ᯨ᮪ #2
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=max_par/5;
        }
       else if(key=='3')   // ������ ᯨ᮪ #3
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*2)/5;
        }
       else if(key=='4')  // ������ ᯨ᮪ #4
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*3)/5;
        }
       else if(key=='5')  // �������⥫�� ᯨ᮪
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*4)/5;
        }

 /*
       else if(key=='6')  // ������ ���४樨 ��������
        {
         n_adc_mm=0;
         ds_list=ds_list2;
         max_par=max_list2;
         mmi_prm=0;
        }
       else if(key=='7')  // ������ ���४樨 ⥬�������
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
       SetDisplayPage(EmptPage);    // ����� ��࠭��
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
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"�। \"F3\"���� \"Enter\"���. ");
       }
       else
       {
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\",\"F3\",\"ESC\",\"Enter\"         ");
         MmiGotoxy(2,nn_chg);  MmiPuts("#");
       }
       sw_mmi=14;
       break;
 /*========================================*/
    case 14:/* ��ᬮ�� �� 6 ��ࠬ��஢ */
       if(key==Sht_F2)    /* ��࠭���� ��������� � EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptPage);    // ����� ��࠭��
        MmiGotoxy(0,1);    MmiPuts("���࠭���� ������ � EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    ���࠭���");
        MmiGotoxy(0,4);    MmiPuts("ESC   �� ��࠭���,�த������");
        sw_mmi=15;
        break;
       }
/*
       if(key==Sht_F1)    // ���� COR
       {
        f_init_COR(0);
        f_init_COR(1);
        f_clr_scr_MMI();
        SetDisplayPage(EmptPage);    // ����� ��࠭��
        goto par_out14;
       }
*/
       if(key==Sht_F3)    /* �⥭�� ������ �� EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptPage);    // ����� ��࠭��
        MmiGotoxy(0,1);    MmiPuts("�⥭�� ������ �� EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    ������ ");
        MmiGotoxy(0,4);    MmiPuts("ESC   �� ���뢠��,�த������");
        sw_mmi=16;
        break;
       }
       if(flag_chg==0)
       {
         if(key==ESC)    /* ���室 � ���� �롮� �窨 ��� ��ᬮ��*/
         {
          goto m_m3_3;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=n_mmi_str_1)
           {
            mmi_prm -=n_mmi_str_1;
            f_clr_scr_MMI();
            SetDisplayPage(EmptPage);    // ����� ��࠭��
            goto par_out14;
           }
           else
           {
            mmi_prm = 0;
            f_clr_scr_MMI();
            SetDisplayPage(EmptPage);    // ����� ��࠭��
            goto par_out14;
           }
         else if((key== F3 )&& (mmi_prm < (max_par-n_mmi_str_1)) )
         {
          mmi_prm +=n_mmi_str_1;
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��
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
         if(key==ESC)    // ���⪠ 䫠�� ।���஢����
         {
          flag_chg=0;
/*
          if((ds_list[0].descr == list2_dsr)&&
               (ds_list[0].ind == 0 ))
          {
            f_init_COR(0);
            f_init_COR(1);
            f_clr_scr_MMI();
       //   SetDisplayPage(EmptPage);    // ����� ��࠭��
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
            SetDisplayPage(EmptPage);    // ����� ��࠭��
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
         if(key==ENTER)    // ।���஢���� ��ࠬ���
         {
          if(PassW != Password)
          {
           pass_ret=0;
m_pass:
           MmiGotoxy(1,1);
           f_clr_scr_MMI();
           MmiPuts("������ ��஫�:" );
           sprintf( fst_str,"******");
           SetDisplayPage(17);    // ���� ��஫�
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
       if(key==DATA)    // ���� ����祭��� ������
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
    case 15:/* ��࠭���� ������ � EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* ������ � �⮡ࠦ���� ��ࠬ��஢ */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��
          goto par_out14;
         }
         else if(key=='1')    // ��࠭��� �����
         {

           if(f_wrt_eee()<0)
           {
              f_wr_evt(evt_we_err);
              MmiGotoxy(0,5);   MmiPuts("�訡�� �� ��࠭���� ������");
           }
           else
           {
              f_wr_evt(evt_we);
              MmiGotoxy(0,5);   MmiPuts(" ����� ��࠭��� �ᯥ譮");
           }
              MmiGotoxy(0,6);   MmiPuts("      Enter - �த������");
         }
         break;
 /*========================================*/
    case 16:/* �⥭�� ������ �� EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* ������ � �⮡ࠦ���� ��ࠬ��஢ */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��
          goto par_out14;
         }
         else if(key=='1')    // ������
         {

           f_chk_EEE_CRC();
           if(f_rd_eee()<0)
           {
              f_wr_evt(evt_re_err);
              MmiGotoxy(0,5);   MmiPuts("�訡�� �� �⥭�� ������");
              CRC_err=1;
           }
           else
           {
              f_wr_evt(evt_re);
              MmiGotoxy(0,5);   MmiPuts("  ����� ��⠭� �ᯥ譮");
              CRC_err=0;
           }
           f_rd_cor();

           MmiGotoxy(0,6);   MmiPuts("      Enter - �த������");
         }
         break;
 /*========================================*/
    case 18:
       if( f_timer(zero_time,Time_zeroing ))
       {
             f_clr_scr_MMI();
             MoveToXY(3,3);
            MmiPrintf(" ������� �����஢��");
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
         MmiPrintf("�����஢�� �����襭� �ᯥ譮");
//                |                              |
             f_wr_evt(evt_MVD_CL_OK);
             goto m_SF2;
           }
           fl_rd_err=0;
           sw_mvd_m1=0;  // ���.��ࠬ���
           ff_serv=f_MVD_M3;
          }

         GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
         MoveToXY(4,6);
         MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
         break;
 /*========================================*/
    case 120:  // �᭮���� ����

       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
       {
mm00:      sw_mmi=0;

           PageD=0;
//         SetDisplayPage(6);
           SetDisplayPage(ZeroPage);
           f_clr_scr_MMI();
           f_prn_begin();
           break;
       }
//     else if((key== '1') && (id_ok !=0) && (mode_hst == 0) ) //  1  ���� ���⥯த�⮢
       else if((key== '1') && (id_ok !=0) ) //  1  ���� ���⥯த�⮢
       {

        if((WD_PMP_Fl != 0) && (flag_Slv == 2)) break;

        if(mode_hst == 0 ) //  1  ���� ���⥯த�⮢
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



        MmiGotoxy(0,0);    MmiPrintf("��� %d. ���� ���⥯த�⮢.",Adr_ASN);
        if((id_ok !=0)&& (mode_hst == 0) )
        {
            f_prn_MassSt_dlv();
            MmiGotoxy(0,2);    MmiPuts("1 ���� ���� ");
            MmiGotoxy(0,3);    MmiPuts("2 ���� ��� ����஢��");

          if((WD_PMP_Fl != 0) && (flag_Slv == 2)) ;
          else
            if(flag_prn_mass != 0)
          {  MmiGotoxy(0,4);    MmiPuts("3 �த������:");

            if(dose_dlvr != vBIG_P)
             {
              if ( Flag_mass != 0 )
                MmiPrintf("�=%8.2f ��    ",dose_dlvr);
              else
                MmiPrintf("�=%8.2f �    ",dose_dlvr);
             }
            else
                MmiPrintf("��� ����஢�� ");

            MmiGotoxy(0,5);
        //    MmiGotoxy(15,5);
            MmiPrintf("�=%8.2f ��,%8.2f � ",s_MVD[0].MassT,s_MVD[0].VolT);
          }
        }
         MmiGotoxy(0,6);    MmiPuts("4-��ࠬ.���.���.; ESC ������");
         sw_mmi=190;
         break;
       }
       else if(key== 'A') //  A  ��������� ���稪� ���
       {
         f_prepare_t ( &adate00);
m_m1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts("���� 2.��������� ���稪� ���");
            /*

            MmiGotoxy(0,1);    MmiPuts("1  �� ��᫥���� ���. ��");
            MmiGotoxy(0,2);    MmiPuts("2  �� ��᫥���� 5 ��⮪");

            MmiGotoxy(0,3);    MmiPuts("3  �� 㪠������ ����");
            MmiGotoxy(0,4);    MmiPuts("4  �� ⥪�騩 ������");
            MmiGotoxy(0,5);    MmiPuts("5  ���祭�� ���⭮�� ��");
            */
            MmiGotoxy(0,6);    MmiPuts("ESC  ������");
         sw_mmi=130;
         break;
       }


       else if((key== '2') && ( NN_resv > 0) )//  2  ���� ����� १����
        { // ���� ����� १����
  m_11s:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         N_resv_tmp=N_resv;


         MmiGotoxy(0,0);    MmiPrintf("��� %d. ���� ०��� ࠡ���.",Adr_ASN);



#if((Add_pmp == 0) || (Add_pmp == 1))
         MmiGotoxy(0,1);  MmiPuts("����騩 ०��:");  MmiPuts(list_md_add[N_resv_tmp] );
         MmiGotoxy(0,3);  MmiPuts("1 - ��� �������");
         MmiGotoxy(0,4);  MmiPuts("2 - � ��������");
/*
         MmiGotoxy(0,5);  MmiPuts("2 - ������� N1");
         MmiGotoxy(0,5);  MmiPuts("3 - ������� N2");
*/

#endif


#if(Add_pmp == 2)
         MmiGotoxy(0,1);  MmiPuts("����騩 ०��:");  MmiPrintf("���.N%d",N_resv_dsp[N_resv_tmp] );
         MmiGotoxy(0,3);  MmiPrintf("1 - ������� N%d",N_resv_dsp[1]);
         MmiGotoxy(0,4);  MmiPrintf("2 - ������� N%d",N_resv_dsp[2]);
/*
         MmiGotoxy(0,5);  MmiPrintf("3 - ������� N%d",N_resv_dsp[3]);
*/

#endif

         MmiGotoxy(0,6);  MmiPuts("ESC-������,Enter-����");
        sw_mmi=128;
/*
          sprintf( fst_str,"%2d",N_resv);
          fst_n=3;
          sw_fst=1;
          MmiGotoxy(10,3);
*/
         break;
        }
       else if(key== '3') // 3  ��ᬮ�� ��ୠ�� ᮡ�⨩
       {
m_m2:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

            i= f_get_max_n_arch();
            ar_str_ptr=f_get_fst_stor();
         MmiGotoxy(0,0);    MmiPrintf("��� %d. ��ୠ� ᮡ�⨩.",Adr_ASN);
            MmiGotoxy(0,1);    MmiPrintf("%4d  ",i);
            j=i%100;
            if((j<=20)&& (j>5))
              MmiPrintf("����ᥩ");
            else
            switch(i%10)
            {
             case 1:
             MmiPrintf("������");
             break;

             case 2:
             case 3:
             case 4:
             MmiPrintf("�����");
             break;

             case 0:
             case 5:
             case 6:
             case 7:
             case 8:
             case 9:
             MmiPrintf("����ᥩ");
             break;
            }

   tdat = localtime( &ar_str_ptr->time );
//   MmiPrintf(" � %02d.%02d.%02d %02d:%02d:%02d",
//   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
   MmiPrintf(" � %02d.%02d.%02d",
   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100);

            MmiGotoxy(0,2);    MmiPuts(" ��ᬮ�� ��ୠ�� ᮡ�⨩");
            MmiGotoxy(0,3);    MmiPuts("1  �� ���");
            MmiGotoxy(0,4);    MmiPuts("2  �� ������ �����");
            MmiGotoxy(0,5);    MmiPuts("3  ��᫥���� �����");
            MmiGotoxy(0,6);    MmiPuts("ESC  ������");

         PassW=0;
         sw_mmi=140;
         break;
       }
       else if(key== '4') // 4  ��ࢨ�� �㭪樨
       {
m_m3:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("��� %d. ��ࢨ�� �㭪樨.",Adr_ASN);
            MmiGotoxy(0,1);    MmiPuts("1  ���᮪ �ࠩ��஢");
            MmiGotoxy(0,2);    MmiPuts("2  ����⨪�  �ࠩ��஢");
            MmiGotoxy(0,3);    MmiPuts("3  ��ᬮ��/���� ��ࠬ��஢");
            MmiGotoxy(0,4);    MmiPuts("4  ��㣨� �㭪樨");
            MmiGotoxy(0,5);    MmiPuts("5  �६�, ���");
            MmiGotoxy(0,6);    MmiPuts("ESC  ������");
         sw_mmi=150;
         PassW=0;
       }

       else if(key== '5') // 5 ����騥 ��������� ��室����
       {
m_m4:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_prn_den_t();
         flg_ch=0;
         sw_mmi=122;
         break;

       }
       else if(key== '6') // 6 �⮡ࠦ���� ���������� �室��
       {
m_m6:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("��� %d. ��������� �室�:",Adr_ASN);
   MmiGotoxy(0,1); MmiPrintf("    I7017C, ������ ���");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625


   MmiGotoxy(0,4); MmiPrintf(" ����ﭨ� ������� �室��:");

  _fmemset( &ADC_c[0],0xff,sizeof(ADC)); // ���⪠ ���� �࠭�
  INP_VAR_c=0xffff;
         sw_mmi=25;
         break;

       }
       else if(key== '7') // 7 �⮡ࠦ���� ����.��室��
       {
m_m7:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("��� %d. ������ ��室�:",Adr_ASN);
   MmiGotoxy(0,6);   MmiPuts(" ESC   - ������ � ����");

         OUT_VAR_c=0xffff;
         sw_mmi=28;
         break;

       }
       else if(key== '8') // 8 ����� sw
       {
m_m8:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

         MmiGotoxy(0,0);    MmiPrintf("��� %d. ",Adr_ASN);
      MmiGotoxy(0,3);   MmiPrintf("   VER %s",sw_ver);
      MmiGotoxy(0,6);   MmiPuts(" ESC   - ������ � ����");
         sw_mmi=27;
         break;
       }
       else if(key== '-' )// SHT_9  ���४�� ��室�
       {
m_m9:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("��� %d. ���४�� ��室�.",Adr_ASN);
            MmiGotoxy(0,1);    MmiPuts("1 ���४�� ���ᮢ��� ��室�");
            MmiGotoxy(0,2);    MmiPuts("2 ���४�� ��ꥬ���� ��室�");
  //        MoveToXY(0,4);   MmiPrintf("�����⥫� �����:     %.6f",s_MVD[0].f);
  //        MoveToXY(0,5);   MmiPrintf("�����⥫� ��ꥬ�:    %.6f",s_MVD[0].f);
            MmiGotoxy(0,6);    MmiPuts("ESC  ������");

         Flag_f_corr=0;
         sw_mvd_m1=31;
         tm_mvd=TimeStamp;
         ff_serv=f_MVD_M1f;
         sw_mmi=125;
         break;
       }
       else if(key== '9' )// 9  �१ ��室�
       {
m_m9s:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);    MmiPrintf("��� %d. �१ ��室�.",Adr_ASN);
            MmiGotoxy(0,1);    MmiPuts("1 �१ ���ᮢ��� ��室�");
            MmiGotoxy(0,2);    MmiPuts("2 �१ ��ꥬ���� ��室�");
  //        MoveToXY(0,4);   MmiPrintf("�����⥫� �����:     %.6f",s_MVD[0].f);
  //        MoveToXY(0,5);   MmiPrintf("�����⥫� ��ꥬ�:    %.6f",s_MVD[0].f);
            MmiGotoxy(0,6);    MmiPuts("ESC  ������");

         Flag_f_corr=0;
         sw_mvd_m1=31;
         tm_mvd=TimeStamp;
         ff_serv=f_MVD_M1s;
         sw_mmi=127;
         break;
       }
       break;
 /*========================================*/
    case 121: // // ���� ��஫� �� ��������� ������
       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��

 m121:
          switch(pass_ret)
          { // ��஫� �� ������
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
          SetDisplayPage(EmptPage);    // ����� ��࠭��
          switch(pass_ret)
          { // ��஫� ������ ���४⭮
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
          SetDisplayPage(EmptPage);    // ����� ��࠭��
          goto m121;
        }

 /*========================================*/
    case 122:
 //  �⮡ࠦ���� ���⭮��,⥬�������,��⠢�
 //  ����饥 ���祭��.
       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
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
 //  ���� 9.���४�� ��室�.
       if((key==ESC)||(key==ENTER) )    /* ���室 � ���� */
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
          SetDisplayPage(EmptPage); // ���� ���祭��
          f_clr_scr_MMI();
          MmiPuts("������ ���४�� �����:" );
          k_mv_tmp=k_m_flow;
          flag_mass=1;
m_m9_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"ESC - ������");
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
          SetDisplayPage(EmptPage); // ���� ���祭��
          f_clr_scr_MMI();
          MmiPuts("������ ���४�� ��ꥬ�:" );
//        MmiPuts("������ �१ ����.���.��/�:" );
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

      // ��������� ���祭�� � k_mv_tmp
          if(flag_mass)
          {
           s_MVD[0].r_addr=279; // �����⥫� �����.

           chg_nn_par=Par_MF;
           chg_old=k_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else
          {
           s_MVD[0].r_addr=281; // �����⥫� ��ꥬ�.
           chg_nn_par=Par_VF;

//         s_MVD[0].r_addr=195; // �१ ����.��室�
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
 //  ���� 1.4.���४�� ��ࠬ��஢ ��砫쭮�� ����������
       if((key==ESC)||(key==ENTER) )    /* ���室 � ���� */
       {
         goto m_m5;
       }

     if(valve_mode != 1)
       if(key=='2')
       {

m_m5_4_1:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ���祭��
          f_clr_scr_MMI();
          MmiPuts("������ ��砫�� ��室,��/�:" );
          k_mv_tmp=Flow_beg;
          flag_mass=1;
m_m5_4_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("ESC-������,Enter-���� ������");
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
          SetDisplayPage(EmptPage); // ���� ���祭��
          f_clr_scr_MMI();
          MmiPuts("������ ��砫�� ��ꥬ,� :" );
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

      // ��������� ���祭�� � k_mv_tmp
          if(flag_mass)
          {

           chg_nn_par=Par_FB;
           chg_old= Flow_beg;
           chg_new= k_mv_tmp;

           Flow_beg=k_mv_tmp; // ��砫�� ��室,��/�
           f_wr_evt(evt_chg_param);
          }
          else
          {
           chg_nn_par=Par_VB;

           chg_old=Vol_beg;
           chg_new= k_mv_tmp;
           Vol_beg=k_mv_tmp;   // ��砫�� ��ꥬ,�
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
 //  ���� 9S.�१  ��室�.
       if((key==ESC)||(key==ENTER) )    /* ���室 � ���� */
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
          SetDisplayPage(EmptPage); // ���� ���祭��
          f_clr_scr_MMI();
          MmiPuts("������ �१ �.���.��/�:" );
          k_mv_tmp=k_m_flow;
          flag_mass=1;
m_m9s_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"ESC - ������");
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
          SetDisplayPage(EmptPage); // ���� ���祭��
          f_clr_scr_MMI();
          MmiPuts("������ �१ ��.���.�/ᥪ:" );
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

      // ��������� ���祭�� � k_mv_tmp
          if(flag_mass)
          {
           s_MVD[0].r_addr=195; // �१ ����.���.

           chg_nn_par=Par_MC;
           chg_old=k_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else
          {
           s_MVD[0].r_addr=197; // �१ ��. ���.
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
 //  ���� 1S.����� १����.
       if((key==ESC)||(key==ENTER) )    // ���室 � ����
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

      // ��������� ���祭�� � N_resv_tmp

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
 //  ���� 1S.����� ࠡ���.

#if((Add_pmp == 0) || (Add_pmp == 1))
       MmiGotoxy(0,1);  MmiPuts("����騩 ०��:");  MmiPuts(list_md_add[N_resv_tmp] );
#endif

#if(Add_pmp == 2)
         MmiGotoxy(0,1);  MmiPuts("����騩 ०��:");  MmiPrintf("���.N%d",N_resv_dsp[N_resv_tmp] );
#endif

       if(key==ESC)    /* ���室 � ���� */
       {
         goto main_menu;
       }
       if(key==ENTER)     /* ���室 � ���� */
       {

          if(N_resv_tmp != N_resv)
          {
      // ��������� ���祭�� � N_resv_tmp

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
    case 130: // //  1  ����ﭨ� ���᪠ ���⥯த�⮢

       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
       {
           goto main_menu;
       }

       else if(key== '1')  // 1  �� ��᫥���� ���. ��
       {
m_m1_1:
  //     mmi_str=0;
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_prn_lst_hour();
         sw_mmi=131;
       }
       else if(key== '2')  // 2  �� ��᫥���� 5 ��⮪
       {
m_m1_2:
  //     mmi_str=0;

//printf("\r\n===0===");
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();

         f_prn_5day();
         sw_mmi=131;
       }
       else if(key== '3')  // 3  �� 㪠������ ����
       {
m_m1_3:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   ��� ���ﭨ� ���稪�");
           MmiGotoxy(0,1);    MmiPuts("      ����.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - �⬥����");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=134;
       }
       else if(key== '4')  //4  �� ⥪�騩 ������
       {
m_m1_4:
    //   mmi_str=0;
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_prn_current();
         sw_mmi=132;
       }
       else if(key== '5')  //5  ���祭�� ���⭮�� ��
       {
m_m1_5:
      // mmi_str=0;
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("  ���祭�� ���⭮�� ��");
           MmiGotoxy(0,1);    MmiPuts("       ���.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.00.00");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - �⬥����");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)ahour00.hour,(int)ahour00.min,(int)ahour00.sec );
          fst_n=9;
          sw_fst=1;
          sw_mmi=133;
       }
       break;
 /*========================================*/
    case 131:
 //  �⮡ࠦ���� ����ﭨ� ���᪠ ���⥯த�⮢.
 // �� ��᫥���� ���. �� .
       if((key==ESC)||(key==ENTER))    /* ���室 � ������饥 ���� */
       {
         goto m_m1;
       }
       break;
 /*========================================*/
    case 132:
 //  �⮡ࠦ���� ����ﭨ� ���᪠ ���⥯த�⮢.
 //  ����饥 ���祭��.
       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
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
 //  �⮡ࠦ���� ���⭮�� ��.
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ���室 � ���� */
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
              MmiGotoxy(0,5);   MmiPuts("�訡�� �� ��࠭���� ������");
              sw_mmi=131;
           }
           else goto m_m1;

          break;
        }
       break;
 /*========================================*/
    case 134:
 //  ���� ����
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ���室 � ���� */
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
            // ��� �������
            // �⮡ࠦ���� ���祭�� ���᪠
            SetDisplayPage(EmptPage);
            f_clr_scr_MMI();
            f_prn_date();
            sw_mmi=131;

          break;
        }
       break;
 /*========================================*/
    case 140: // 2  ��ᬮ�� ��ୠ�� ᮡ�⨩

       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
       {
           goto main_menu;
       }
        else if (key==DEL)
        {

          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��
          MmiGotoxy(0,1);    MmiPuts(" 1 - ��१���㧪�");
          MmiGotoxy(0,2);    MmiPuts(" 6 - ��室 �� �ணࠬ�� � ��");
          MmiGotoxy(0,3);    MmiPuts("    (��  �⫠���)");
          MmiGotoxy(0,5);    MmiPuts("ESC   �⬥��");
          sw_mmi=142;
          break;
        }
       else if(key== '1')  //1  �� ���
       {
m_m2_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   ��� ����� ��ୠ�� ");
           MmiGotoxy(0,1);    MmiPuts("      ����.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - �⬥����");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=143;
          break;
       }
       else if(key== '2')  //2  �� ������ �����
       {
m_m2_2:
          max_par= f_get_max_n_arch();
          MmiGotoxy(1,1);
          f_clr_scr_MMI();
          MmiPuts("������ ����� �����:" );
          sprintf( fst_str,"%d",max_par);
          fst_n=4;
          sw_fst=1;
          MmiGotoxy(15,3);
          SetDisplayPage(15); // ���� ���祭��
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
       else if(key== '3')  //3  ��᫥���� �����
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
         SetDisplayPage(EmptPage);    // ����� ��࠭��

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
        MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"�। \"F3\"���� \"ESC\"�⬥��");

        sw_mmi=141;
       }
       break;
 /*========================================*/
    case 141:/*��ᬮ�� 2 ����ᥩ ��ୠ��*/
         if(key==ESC)    /* ���室 � ���� �롮� �窨 ��� ��ᬮ��*/
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
    case 142:/* ��室 �� �ணࠬ�� */
             /* ������ � ��ᬮ��� */
       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
         {
          goto m_m2;
         }
         else if(key== '1' )
         { //  1 - ��१���㧪�
           f_wr_evt(evt_res);
           _asm cli
           _asm hlt
         }
         else if(key== '6' )
         {// 6 - ��室 �� �ணࠬ�� � ��
            f_wr_evt(evt_exit);
            return 1; // ��室 �� �ணࠬ�� *.exe � ��
         }
         break;
 /*========================================*/
    case 143:

 //  ���� ����
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ���室 � ���� */
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
            // ��� �������

m_m2_1_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   �६� ����� ��ୠ�� ");
           MmiGotoxy(0,1);    MmiPuts("       ��� ���.");
        // MmiGotoxy(0,2);    MmiPuts("        08.01");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - �⬥����");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d",(int)adate00.hour,(int)adate00.min );
          fst_n=6;
          sw_fst=1;
          sw_mmi=144;
       }
          break;

 /*========================================*/
    case 144:
 //  ���� �६���
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ���室 � ���� */
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
            // �६� �������

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
    case 150: // 3  ��ࢨ�� �㭪樨

       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
       {
           goto main_menu;
       }

       else if(key== '1')  // 1  ���᮪ �ࠩ��஢
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_2:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_drv_list_MMI(&mmi_str);
         sw_mmi=22;
       }
       else if(key== '2')  // ����⨪�  �ࠩ��஢
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_3:
         SetDisplayPage(EmptPage);  // ���� �࠭
         f_clr_scr_MMI();
         f_drv_stat_MMI(&mmi_str);
         pass_cnt=0;
         sw_mmi=23;
       }
       else if(key== '3')   //  3  ��ᬮ��/���� ��ࠬ��஢
       {
m_m3_3:

   //     PassW=0;
        // ���室 � ���� �롮� �窨 ��� ��ᬮ�� ��ࠬ��஢
//          SetDisplayPage(11);
          sw_mmi=11;
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� �롮� ᯨ᪠ ��ᬮ��");
            MmiGotoxy(0,2);    MmiPuts("1...5 ���᮪ ��ࠬ��஢");
  //        MmiGotoxy(0,3);    MmiPuts("6 ����.���.���稪� ��������");
  //        MmiGotoxy(0,4);    MmiPuts("7 ����.���.���稪� ⥬����.");
            MmiGotoxy(0,6);    MmiPuts("ESC  ������");
          break;
       }
       else if(key== '4')   //  4  ��㣨� �㭪樨
       {
m_m3_4:
         SetDisplayPage(EmptPage);  // ���� �࠭
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� 4.4.��㣨� �㭪樨. ");
            MmiGotoxy(0,1);    MmiPuts("1  ��������� ��室����");
            MmiGotoxy(0,2);    MmiPuts("2  ��ࠬ���� ��室����");
            MmiGotoxy(0,3);    MmiPuts("3  �訡�� ��室����");
            MmiGotoxy(0,4);    MmiPuts("4  ���� ICP/RTU ���㫥�");
            MmiGotoxy(0,5);    MmiPuts("5  ���᮪ ��������� ���㫥�");
            MmiGotoxy(0,6);    MmiPuts("ESC  ������");
         sw_mmi=160;
          break;
       }
       else if(key== '5')   //  5  �६�, ���
       {
m_m3_5:
         f_prepare_t ( &adate00);
         adate11=adate00;
         SetDisplayPage(EmptPage);  // ���� �࠭
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("      ������ ��� ");
           MmiGotoxy(0,1);    MmiPuts("      ����.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("���室 ���/���.�६� �몫�祭");
else                          MmiPuts("���室 ���/���.�६� ����祭");

/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - ��⭥�
                              MmiPuts("      ��⭥� �६�");
     else                     MmiPuts("      ������ �६�");
*/
            MmiGotoxy(0,4);   MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);   MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);   MmiPuts(" ESC   - �⬥����");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=165;
          break;
       }
       else if(key== '6')   //  6  �������� ��஫�
       {
m_m3_6:
         SetDisplayPage(EmptPage);  // ���� �࠭
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� 4.6.��������� ��஫� ");
            MmiGotoxy(0,2);    MmiPuts("1  �������� ��஫�");
            f_d_ESC();
         sw_mmi=162;
          break;
       }
       break;
 /*========================================*/
    case 160: // M3.4  ��㣨� �㭪樨

       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
       {
           goto m_m3;
       }
       else if(key== '1') //  1  ��������� ��室����
       {
         max_par=10;
         mmi_prm=0;

m_m3_4_1v:

         if(ff_serv==NULL)
         {
          SetDisplayPage(EmptPage);
          f_clr_scr_MMI();
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"�। \"F3\"���� \"ESC\"�⬥��");
          sw_MMI_cur=0; // ��ப� MMI
          sw_mvd_m1=mmi_prm+20;  // ���.��ࠬ���
          sw_MMI_lim=6; // ����筠� ��ப�
          MMIDens=-1;
          MMITemp=-300;
          ff_serv=f_MVD_M2;
          sw_mmi=171;
         }
         else
          sw_mmi=173;
         break;
       }

       else if(key== '2') //  2  ��ࠬ���� ��室����
       {
         max_par=17;
         mmi_prm=0;

m_m3_4_2v:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"�। \"F3\"���� \"ESC\"�⬥��");

         if(ff_serv==NULL)
         {
          sw_MMI_cur=0; // ��ப� MMI
          sw_mvd_m1=mmi_prm+20;  // ���.��ࠬ���
          sw_MMI_lim=6; // ����筠� ��ப�

          ff_serv=f_MVD_M1;
          sw_mmi=172;
         }
         else
          sw_mmi=174;
         break;
       }
       else if(key== '3') // 3  �訡�� ��室����
       {
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,6);    MmiPuts("ESC,ENTER  ������");
         sw_mvd_m1=0;
         ff_serv=f_MVD_M3;
         sw_mmi=180;

         break;

       }

       else if(key== '5') //  5  ���᮪ ������祭��� ���㫥�
       {
         mmi_str=0;
         max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
m20_1:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         f_mod_list_MMI(&mmi_str);
         sw_mmi=21;
       }
       else if(key== '4')  // 4  ���� ICP/RTU ���㫥�
       {
m20_4:
          f_clr_scr_MMI();
          MmiGotoxy(1,1);
          MmiPuts("������ ����� ���� : " );
          sprintf( fst_str,"%2d",mmi_com);
          fst_n=3;
          sw_fst=1;
          MmiGotoxy(13,3);
          SetDisplayPage(15);
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
         MmiGotoxy(0,0);     MmiPrintf("ICP COM%d: ⠩���� %d ��",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("����.��� %d,䫠� CRC=%d",licp_amax,LICP_Rqst.CRC_flag);
       }
       else
       {
         MmiGotoxy(0,0);     MmiPrintf("RTU COM%d: ⠩���� %d ��",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("����.��� %d",licp_amax);
       }

       MmiGotoxy(0,6);  MmiPuts("  Enter - �த������");
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
 //  ��������� ��஫�
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ���室 � ���� */
       {
         goto m_m3;
       }
       else if(key== '1')   // 1  �������� ��஫�
       {

          if(PassW != Password)
          {
           pass_ret=3;
           goto m_pass;
          }
m_m3_6_1:

          MmiGotoxy(0,1);
          SetDisplayPage(EmptPage); // ���� ���祭��
          f_clr_scr_MMI();
          MmiPuts("������ ���� ��஫�(1-� ࠧ):" );
           pass1=-1;
           sprintf( fst_str,"******");
           SetDisplayPage(17);    // ���� ��஫�
           sw_mmi=163;
           fst_n=7;
           sw_fst=1;
           MmiGotoxy(11,3);
           break;
       }
       break;
 /*========================================*/
    case 163: // // ���� ������ ��஫� 1 ࠧ
       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��
 m163:
          goto m_m3;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&pass1);
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��
           // ��஫� ������ ���४⭮
           if(pass1>= 0)
           {
             MmiGotoxy(0,1);
             SetDisplayPage(EmptPage); // ���� ���祭��
             f_clr_scr_MMI();
             MmiPuts("������ ���� ��஫�(2-� ࠧ):" );
             pass2=-1;
             sprintf( fst_str,"******");
             SetDisplayPage(17);    // ���� ��஫�
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
          SetDisplayPage(EmptPage);    // ����� ��࠭��
          goto m163;
        }

 /*========================================*/
    case 164: // // ���� ������ ��஫� 2 ࠧ
       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��
          goto m163;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&pass2);
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��
           // ��஫� ������ ���४⭮
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
                MmiGotoxy(1,3);   MmiPuts("�訡�� �� ��࠭���� ��஫�");
             }
             else
             {
                f_wr_evt(evt_we);
                MmiGotoxy(3,3);   MmiPuts("��஫� ��࠭�� �ᯥ譮");
             }
             f_wr_cor();
             MmiGotoxy(0,6);   MmiPuts("      Enter - �த������");
             break;
           }
           else goto m_m3_6_1;

        }
       else if(key==DATA_ESC)
        {
          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);    // ����� ��࠭��
          goto m163;
        }

 /*========================================*/

 /*========================================*/
    case 165:

 //  ���� ���� ��� ���������
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ���室 � ���� */
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
            // ��� �������
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
           MmiGotoxy(0,0);    MmiPuts("      ����饥 �६� ");
           MmiGotoxy(0,1);    MmiPuts("       ��� ��� ���");
        // MmiGotoxy(0,2);    MmiPuts("         08.01.00");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("���室 ���/���.�६� �몫�祭");
else                          MmiPuts("���室 ���/���.�६� ����祭");
/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - ��⭥�
                              MmiPuts("      ��⭥� �६�");
     else                     MmiPuts("      ������ �६�");
*/





            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - �⬥����");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)adate00.hour,(int)adate00.min,(int)adate00.sec);
          fst_n=9;
          sw_fst=1;
          sw_mmi=166;
       }
          break;

 /*========================================*/
    case 166:
 //  ���� �६���
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ���室 � ���� */
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
            // �६� �������
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
    case 21:  // ��ᬮ�� ᯨ᪠ ���㫥�

       max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
       if((key==ESC)||(key==ENTER))   /* ���室 � ���� �롮� �窨 ��� ��ᬮ��*/
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
    case 22: // ��ᬮ�� ᯨ᪠ �ࠩ��஢

       if((key==ESC)||(key==ENTER))    /* ���室 � ���� �롮� �窨 ��� ��ᬮ��*/
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
    case 23: // ��ᬮ�� ����⨪� �ࠩ��஢

       if((key==ESC)||(key==ENTER))    /* ���室 � ���� �롮� �窨 ��� ��ᬮ��*/
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
        {  // ���㫥��� ���稪�� �訡��
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
    case 24: // �⮡ࠦ���� ᪠��஢���� ����
       if((key==ESC)||(key==ENTER))
       {
           goto m_m3_4; //  4  ��㣨� �㭪樨
       }
       else //PASS
       {
          MmiGotoxy(0,3);  MmiPrintf("���襭�   %3d",licp_addr);
          MmiGotoxy(0,4);  MmiPrintf("�����㦥�� %3d",licp_fnd);
       }
       break;
 /*========================================*/
    case 25: // �⮡ࠦ���� ���������� �室��

       if((key==ESC)||(key==ENTER))
       {
           goto m0_f1;
       }
       else // PASS
       {
// MmiGotoxy(0,0); MmiPrintf(" ����ﭨ� ���������� �室��:");
// MmiGotoxy(0,1); MmiPrintf("       7017C/1 , ��");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625

   if( _fmemcmp( &ADC[0], &ADC_c[0], sizeof(ADC_c4)) != 0)
   {
   MmiGotoxy(0,2); MmiPrintf(" ��������     %8g (In%d)",(float)ADC[0],analog_num[0]-1);
   MmiGotoxy(0,3); MmiPrintf(" ���������  %8g (In%d)",(float)ADC[1],analog_num[1]-1);
    _fmemcpy( &ADC_c[0], &ADC[0], sizeof(ADC_c4));
   }
/*
   if( _fmemcmp( &ADC_c[4], &ADC[4], sizeof(ADC_c4)) != 0)
   {
    MmiGotoxy(0,3); MmiPrintf(" %6.2f %6.2f %6.2f %6.2f",(float)ADC[4],(float)ADC[5],(float)ADC[6],(float)ADC[7]);
    _fmemcpy( &ADC_c[4], &ADC[4], sizeof(ADC_c4));
   }
//  MmiGotoxy(0,4); MmiPrintf("       7017C/2 , ��");
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

     MmiGotoxy(0,5); MmiPuts(" ���=");
     if(INP_VARi & UZA_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy( 7,5); MmiPuts("����.=");
     if(INP_VARi & LVL_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy(16,5); MmiPuts("�����=");
     if(INP_VARi & STRT_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy( 0,6); MmiPuts("����=");
     if(INP_VARi & TRAP_IN)
       MmiPuts("1");
     else
       MmiPuts("0");
     MmiGotoxy( 7,6); MmiPuts("����.=");
     if(INP_VARi & CONS_IN)
       MmiPuts("1");
     else
       MmiPuts("0");

     MmiGotoxy(16,6); MmiPuts("���� =");
     if(INP_VARi & STOP_IN)
       MmiPuts("1");
     else
       MmiPuts("0");
    }
       }

       break;
 /*========================================*/
    case 26:/* �������� ������ ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
          goto m_main;
         }
         break;
 /*========================================*/
    case 27:/* �������� ������ ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
           goto m0_f1;
         }
         break;
 /*========================================*/
    case 28: // �⮡ࠦ���� ������� ��室��
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
      MmiPuts("��.����让");
  else if(valve_mode==2)
      MmiPuts("����� ��  ");
  else if(valve_mode==3)
         MmiPuts("~����.����");

          if(OUT_VAR & OUT1)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(16,2);
  if(valve_mode==1)
         MmiPuts("  ��.����");
  else if(valve_mode==2)
         MmiPuts("  ����� ��");
  else if(valve_mode==3)
      MmiPuts("����.��� ");

          if(OUT_VAR & OUT2)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");


          MmiGotoxy(3,3); MmiPuts("����  ");
          if(OUT_VAR & OUT3)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

          MmiGotoxy(0,4);
      MmiPuts(" ���-� ");

          if(OUT_VAR & OUT7)
            MmiPuts(":1");
          else
            MmiPuts(":0");


          MmiGotoxy(12,4);
         MmiPuts("��.���.");

          if(OUT_VAR & OUT5)
            MmiPuts(":1");
          else
            MmiPuts(":0");
/*
          MmiGotoxy(22,4);
         MmiPuts("�.�2");

          if(OUT_VAR & OUT6)
            MmiPuts(":1");
          else
            MmiPuts(":0");
*/


          MmiGotoxy(0,5); MmiPuts("MMI ��� ");
          if(OUT_VAR & OUT8)
            MmiPuts(":1 ");
          else
            MmiPuts(":0 ");

         }

       }

       break;
 /*========================================*/
 /*========================================*/
    case 171://  1  ��������� ��室����
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
           sw_MMI_cur=0; // ��ப� MMI
           sw_mvd_m1=mmi_prm+20;  // ���.��ࠬ���
           sw_MMI_lim=6; // ����筠� ��ப�
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

    case 172://  2  ��ࠬ���� ��室����
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
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"�। \"F3\"���� \"ESC\"�⬥��");
           sw_MMI_cur=0; // ��ப� MMI
           sw_mvd_m1=mmi_prm+20;  // ���.��ࠬ���
           sw_MMI_lim=6; // ����筠� ��ப�
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
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"�। \"F3\"���� \"ESC\"�⬥��");
           sw_MMI_cur=0; // ��ப� MMI
           sw_mvd_m1=mmi_prm+20;  // ���.��ࠬ���
           sw_MMI_lim=6; // ����筠� ��ப�

           ff_serv=f_MVD_M1;
           sw_mmi=172;
          }
         }
         break;
 /*========================================*/
    case 180:

       if((key==ESC)||(key==ENTER))  /* ���室 �� ��砫��� ��࠭��� */
       {
         if(ff_serv==f_MVD_M3) ff_serv=NULL;
            goto m_m3_4;
       }
       break;
 /*========================================*/
    case 190: //  1  ���� ���⥯த�⮢

       if((key==ESC)||(key==ENTER))    /* ���室 � ���� */
       {
           goto main_menu;
       }

       else if((key== '1') && (id_ok !=0) && (mode_hst == 0) )  // 1  ���� ����
       {
m_m5_1:

          if((WD_PMP_Fl != 0) && (flag_Slv == 2)) break;

         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);       MmiPuts("   ���� ���� ");
         f_prn_MassSt_dlv();

         MmiGotoxy(0,2);
          if ( Flag_mass != 0 )
             MmiPuts(" ������ ���� ���᪠,��");
          else
             MmiPuts(" ������ ���� ���᪠,� ");

         MmiGotoxy(0,6); MmiPuts(" Enter - ���� ������  ");

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
   //      MmiGotoxy(0,0);       MmiPuts("���� ������ 䠧�.      ");
          MmiGotoxy(0,0);
          if(dose_dlvr != vBIG_P)
          {
            if ( Flag_mass != 0 )
              MmiPrintf(" ���� ���� %g ��",dose_dlvr);
            else
              MmiPrintf(" ���� ���� %g � ",dose_dlvr);
          }
          else
             MmiPrintf(" ���� ��� ����஢��");

         MmiGotoxy(0,6);       MmiPuts("ESC - ��������.");

         sw_dlv_liq=1;
         sw_mmi=193;
m_m5_1d:
/*==========
          MmiGotoxy(0,2);      MmiPuts("  ����        |  ���饭�");
                //             MmiPuts("xxxxx.xx ��    | xxxxx.xx ��");
          MmiGotoxy(0,3);
          if(flag_prn_mass)   MmiPrintf("%8.2f ��    | %8.2f ��   ",s_MVD[0].MassI,s_MVD[0].MassT);  // VolT_id, VolT_int
          else  MmiPrintf("%8.2f ��    | %8.2f ��   ",s_MVD[0].MassI,(float)0.);  // VolT_id, VolT_int
===========*/
          if(NN_resv != 0)
          {

#if((Add_pmp == 0) || (Add_pmp == 1))
            MmiGotoxy(0,2);  MmiPrintf("��� %d. %s,���饭�",Adr_ASN,list_md_add[N_resv]);
#endif

#if(Add_pmp == 2)
            MmiGotoxy(0,2);  MmiPrintf("��� %d. ���.N%d, ���饭�",Adr_ASN,N_resv_dsp[N_resv]);
#endif


          }

          else
          {
            MmiGotoxy(0,2);      MmiPrintf("��� %d.    ���饭�          ",Adr_ASN);
          }

//        MmiGotoxy(0,2);      MmiPuts("  M,��   --���饭�-- V,�    ");
//        MmiGotoxy(0,2);      MmiPuts("  ����        |  ���饭�");
                //             MmiPuts("xxxxx.xx ��    | xxxxx.xx ��");
          MmiGotoxy(0,3);
          if(flag_prn_mass)   MmiPrintf("�=%9.2f �� |�= %9.2f �  ",s_MVD[0].MassT,s_MVD[0].VolT);  // VolT_id, VolT_int
          else                MmiPrintf("�=%9.2f �� |�= %9.2f �  ",(float)0.,(float)0.);  // VolT_id, VolT_int

m_m5_1e:
          f_prn_proc();
          break;
        }
       else if(key==DATA_ESC)
        {
          goto m_m5;
        }
//     else if(key== '2')  // 2  ���� �� ���஦�����
       else if((key== '2') && (id_ok !=0) && (mode_hst == 0) )
       {
m_m5_2:

         if((WD_PMP_Fl != 0) && (flag_Slv == 2)) break;

         dose_dlvr=vBIG_P;
         flag_dlv_fst=0;
         flag_prn_mass=0;
         goto m_m5_1o;
       }
//     else if(key== '3')  // 3 �த������ � �����. �����
       else if((key== '3') && (id_ok !=0) && (mode_hst == 0) )
       {

        if((WD_PMP_Fl != 0) && (flag_Slv == 2)) break;


         if(flag_prn_mass)
          {
           goto m_m5_1o;
          }
       }

       else if(key== '4' )//  4  ���४�� ��ࠬ��஢ ��砫쭮�� ����������
       {
m_m5_4:
         SetDisplayPage(EmptPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts("��ࠬ.��砫쭮�� ���������� ");
            MmiGotoxy(0,1);    MmiPuts("1 �������� ��砫�� ��ꥬ ");
            MoveToXY(0,4);   MmiPrintf("��砫�� ��ꥬ :%6.0f �",Vol_beg);
       if(valve_mode != 1)
       {
            MmiGotoxy(0,2);    MmiPuts("2 �������� ��砫�� ��室 ");
            MoveToXY(0,5);   MmiPrintf("��砫�� ��室:%6ld ��/�",Flow_beg);
       }
            MmiGotoxy(0,6);    MmiPuts("ESC  ������");

         sw_mmi=126;
         break;
       }

       else  if(mode_hst == 0 )
          f_prn_MassSt_dlv();

       break;
 /*========================================*/
//===========================================
    case 193: //  ����
       if(key==F2)    // �������� ��������,���������
       {
           PageD=0;
       }
       else if(key==F3)    // �������� ���⭮���,���⠢
       {
           PageD=1;
       }
       else if(key=='1')    // �������� ��室��
       {
           PageD=3;
       }

       key=f_dlv_liq(key);
       if(key==ESC)    // ���室 � ����
       {
        if(mode_hst == 0)   goto m_m5;
        else
        {
         sw_mmi=0;
         break;
        }
       }
  // �⮡ࠦ���� ��饩 � ���饭��� �����
       goto m_m5_1d;

 /*========================================*/
 /*========================================*/
       default:
       if((key==ESC)||(key==ENTER))  /* ���室 �� ��砫��� ��࠭��� */
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