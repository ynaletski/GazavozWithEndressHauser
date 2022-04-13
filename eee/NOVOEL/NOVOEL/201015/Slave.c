
//----------------------------------
// ����� �ਭ������ ᢥ���
int    CMD_IN   = 0;
int    CMD_OUT_p = 0;

void (*ff_Slv)() = NULL;

int flag_Slv=0;

int ComPortSlv = 4;
int AddrSlv=1;
int cod_float=1;
int State_SLV=0;
int Last_evt=0;
int sw_mmi_slv=0;
int sw_dlv_slv=0;

int  WD_PMP_flag=0;
int  WD_PMP_Fl=0;
long int WD_PMP_time=0;
long int WD_PMP_t1=0;
long int WD_PMP_Per=20000; // ����稭� ⠩���� �� �ਥ�� ᮮ�饭��

int Slv_fict=0;
int Slv_fict1=0;
int Slv_fict2=0;
int Slv_fict3=0;
int Slv_fict4=0;

void *list_Slv_int[]={

&n_sl_int1,      // 0 �����.��६ int
&n_sl_flt1,      // 1 �����.��६ float

&sw_mmi_slv,     // 2 ����.���� ���
&sw_dlv_slv,     // 3 ����.���᪠

&sw_ver[0],      // 4  ����� ��, 6 ASCII ᨬ�����
&sw_ver[2],      // 5
&sw_ver[4],      // 6

&CMD_IN ,   // &Slv_int[6],     // 7   CMD_REG ॣ���� �������

&State_SLV,      // 8   ����ﭨ� ���᪠
&Last_evt,       // 9   ��᫥���� ᮡ�⨥ ����ᠭ��� � ��ୠ�
&Reg_err,        // 10    &FL_err,         // 10  ���� �訡��, 0 - OK

&ICP_error[7],   // 11  ��� �訡�� �㭪樮��஢����
&ICP_error[8],       // 12  ���७�� ॣ���� �訡��
&ICP_error[1],   // 13  ॣ���� �訡�� �ࠩ��� MVD
&ICP_error[2],   // 14  ॣ���� �訡�� �ࠩ��� 7060
&ICP_error[3],   // 15  ॣ���� �訡�� �ࠩ��� 7017
&ICP_error[6],   // 16  ॣ���� �訡�� �ࠩ��� DELTA
&WD_PMP_Per,     // 17  ��ਮ� ��஦����� ⠩��� Host,ms
                 //     0 - ⠩��� �⪫�祭
&mode_hst,       // 18  1 - ����� ����� ���� �� ���
&Slv_int[10],    // 19  ���⢥ত���� ���� ��� ������ = Strt_cmd(0x55)
&Slv_int[11],    // 20

&INP_VARi,       // 21 ॣ���� ����.�室�� � ��⮬ �����ᨨ
&OUT_VAR,        // 22 ॣ���� ����.��室��

&DriveState[0],    // 23 ॣ���� ����ﭨ� DELTA
&DriveError[0],    // 24 ॣ���� �訡��
&DriveCurrent[0],  //&Delta_current[0],  // 25 ⮪ � ����

&DriveSV[0],       // 26 ⥪.����. �����  �ਢ���
&DriveSA[0],       // 27 ⥪.����. �६��� ࠧ����
&DriveSD[0],       // 28 ⥪.����. �६��� ����������

&Drive_SV_beg[0],   // 29 ���.����. ����� �ਢ���
&Drive_SA_beg[0],   // 30 ���.����. �६��� ࠧ����
&Drive_SD_beg[0],   // 31 ���.����. �६��� ����������

//&cod_float,         // 32 ⨯ ����஢�� float (�������祭 ॣ. 521 MVD,Byte order code for float registers)
&Slv_int[2],        // 32 䨪⨢��� ��६�����
                        // ॣ����� 7060
&i7060_out[0],      // 33
&i7060_inp[0],      // 34
&s_MVD[0].reg_err,  // 35 ॣ���� �訡�� MVD
&type_liq,          // 36  1 Crude Oils
                    //     2 Fuel Oils   - ���⮯����
                    //     3 Jet group
                    //     4 Kerosene
                    //     5 Gazolines   - ������
                    //     6 Lubricating Oils
//&mode_r,            // 37 ०�� �ࠢ�.���������
&Slv_int[2],        // 37 䨪⨢��� ��६�����
NULL                //

};

int n_sl_int=(sizeof(list_Slv_int) / sizeof(list_Slv_int[0])) - 1 ;
int n_sl_int1=(sizeof(list_Slv_int) / sizeof(list_Slv_int[0])) - 1 ;

float *list_Slv_flt[]={
&Slv_float[0],      //1000 0 ���࠭� �������
&Slv_float[1],      //1002 1 ����� ���࠭��
              // १�ࢭ� ��६����
&Vol_beg,           // 1004 2  ��ꥬ ����� �� �஢�� ����㦥��� �㪠��,�
&P_min_valve,       // 1006 3  �������쭮� ��������  ���, �� ���஬ �������� 㢥����� �⥯���
                    //    ������ ���⨫�
&T_Ref,             // 1008 4  ���७᭠� ⥬������,C (15)
&D_ref,             // 1010 5  ���⭮��� �ਢ������� � ��७᭮� ⥬������
&V_ref,             // 1012 6  ��ꥬ ���᪠ �ਢ������ � ��७᭮� ⥬������
&Temp_a,            // 1014 7  ��������� ���饭���� ���⥯த��
&Dens_a,            // 1016 8  ���⭮��� ���饭���� ���⥯த��
&Slv_float[9],      // 1018 9
              // ����� �� ��室����
&s_MVD[0].MassI,    // 1020 10  ���� ������ୠ� ( ����������騩 ���稪) Mass inventory ,I263
&s_MVD[0].MassT,    // 1022 11  ���� � ⥪�饩 ����樨 ���᪠ (total)   Mass total     ,I259
&s_MVD[0].FlowM,    // 1024 12  ���ᮢ� ��室, ��/�                      Mass flow      ,I247
&s_MVD[0].Dens,     // 1026 13  ���⭮��� ��/�3                            Density        ,I249
&s_MVD[0].Temp,     // 1028 14  ���������,                               Temperature    ,I251
&s_MVD[0].VolI,     // 1030 15  ��ꥬ �������� ( ����������騩 ���稪) Volume invnt�ry,I265

&s_MVD[0].VolT,     // 1032 16  ��ꥬ � ⥪�饩 ����樨 ���᪠ (total)
&s_MVD[0].FlowV,    // 1034 17  ��ꥬ�� ��室, �/�
&s_MVD[0].PressG,   // 1036 18

                    // ����� ���������� ���稪��
&s_MVD[0].TempR,    // 1038 19  ⥬������ �� ���譥�� ���稪�
&s_MVD[0].Press,    // 1040 20  �������� �� ���譥�� ���稪�

NULL

};
long int Com_Baud_Slave=9600;
long int *list_Slv_lng[]={
                    // Addr = 1042
&P_dem,             //  1042 21  �������� ��������  10000 = 1 ���
&LIM_P,             //  1044 22  ���� ���� max,12800 = 1 ��
&LIM_M,             //  1046 23  ���� ���� min,12800 = 1 ��
&Flow_beg,          //  1048 24  ���室 ��砫��, �/�
&Flow_nom,          //  1050 25  ���室 ���������, �/�
&Flow_min,          //  1052 26  ���室 ����������  , �/�
&Flow_min1,         //  1054 27  ���室 ���������� 1, �/�
&Flow_min2,         //  1056 28  ���室 ���������� 2, �/�
&Com_Baud_Slave,    //  1058 29  ����� ������ �� Modbus

NULL
};

int n_sl_lng=(sizeof(list_Slv_lng) / sizeof(&FL_err)) - 1 ;
int n_sl_lng1=(sizeof(list_Slv_lng) / sizeof(&FL_err)) - 1 ;

int n_sl_flt=((sizeof(list_Slv_flt) / sizeof(&FL_err)) - 1)+ ((sizeof(list_Slv_lng) / sizeof(&FL_err)) - 1) ;
int n_sl_flt1=((sizeof(list_Slv_flt) / sizeof(&FL_err)) - 1)+ ((sizeof(list_Slv_lng) / sizeof(&FL_err)) - 1) ;
int n_sl_flt0=(sizeof(list_Slv_flt) / sizeof(&FL_err)) - 1 ;

int Slv_int[20]={
  0,0,0,0,0,
  0,0,0,0,0,
};

//--------------------------------
float Slv_float[20]={
0,
0,
2,
3,
4,
5,
};
//--------------------------------
long int Slv_lng[10]={
  0,1,2,3,4,
  5,6,7,8,9,
};

struct eee_dat S1D;  //T_INT T_INT_L T_FLOAT

// Addr2Slot1 2000
//  �����, �⠥�� ���孨� ����஫��஬

struct eee_dat Slv2_Slot1[]=
{
&CMD_IN             , T_INT   ,  //1   I7     CMD_OUT_p
&State_SLV          , T_INT   ,  //1   I8
&Reg_err            , T_INT   ,  //1   I10
&INP_VARi           , T_INT   ,  //1   I21
&OUT_VAR            , T_INT   ,  //1   I22
&s_MVD[0].MassI     , T_FLOAT ,  //2  F1020     ���� ������ୠ� ( ����������騩 ���稪)
&s_MVD[0].MassT     , T_FLOAT ,  //2  F1022     ���� � ⥪�饩 ����樨 ���᪠ (total)
&s_MVD[0].FlowM     , T_FLOAT ,  //2  F1024     ���ᮢ� ��室, ��/�
&s_MVD[0].Dens      , T_FLOAT ,  //2  F1026     ���⭮��� ��/�3
&s_MVD[0].Temp      , T_FLOAT ,  //2  F1028     ���������,C
&s_MVD[0].VolI      , T_FLOAT ,  //2  F1030     ��ꥬ �������� ( ����������騩 ���稪)
&s_MVD[0].VolT      , T_FLOAT ,  //2  F1032     ��ꥬ � ⥪�饩 ����樨 ���᪠ (total)
&Temp_a             , T_FLOAT ,  //2  F1014     ��������� ���饭���� ���⥯த��
&Dens_a             , T_FLOAT ,  //2  F1016     ���⭮��� ���饭���� ���⥯த��
&T_Ref              , T_FLOAT ,  //2  F1008     ���७᭠� ⥬������,C (15)
&D_ref              , T_FLOAT ,  //2  F1010     ���⭮��� �ਢ������� � ��७᭮� ⥬������
&V_ref              , T_FLOAT ,  //2  F1012     ��ꥬ ���᪠ �ਢ������ � ��७᭮� ⥬������
&type_liq           , T_INT   ,  //1  I36       ⨯ ���⥯த��  1 - ⮢�ୠ� �����, 2 - ���⮯����, 5 - ������
};

int Slv2_slt1_lgth= 30 ;
int Slv2_slt1_max=sizeof(Slv2_Slot1) / sizeof(S1D) ;

//---------------------------------------
//---------------------------------------
// Addr2Slot2   3000
// �����, �����뢠��� ���孨� ����஫��஬

struct eee_dat Slv2_Slot2[]=
{
&CMD_IN        , T_INT   ,       // 1   I7     ॣ���� �������
&Slv_float[0]  , T_FLOAT ,       // 2   F1000  ���࠭� �������
&Vol_beg       , T_FLOAT ,       // 2   F1004  ��ꥬ ����� �� �஢�� ����㦥��� �㪠��,�
&Flow_beg      , T_INT_L         // 2   F1048  ���室 ��砫��, �/�
};
int Slv2_slt2_lgth= 7 ;
int Slv2_slt2_max=sizeof(Slv2_Slot2) / sizeof(S1D) ;
//---------------------------------------
//---------------------------------------

unsigned long ComBaudSlv =9600L;
int Com_lgthSlv  =8;
int Com_paritySlv=0;// None  //0-(None);1-(Even);2-(Odd);3-(MARK, always 1); 4-(SPACE,always 0)
int Com_stopSlv  =1;
struct stor_buf *bf_Slv;
int uk_beg_Slv=0;
int uk_fin_Slv=0;

void f_SlaveRTU()
{
int itmp;
//  int  hour,min,sec;
// ������ ������� �� Host (PC) � ��������� �� �� ��⮪��� Modbus RTU


         if(ffgets_SlvRTU(ComPortSlv))
         {

          f_stor_Slv(M_RD,cb_COM[ComPortSlv],n_bcom[ComPortSlv]);
      /*
          if(IsCom(ComPortSlv))
          {
           n_bcom[ComPortSlv]=0;
           return ;
          }

          if(IsTxBufEmpty(ComPortSlv) == 0)
          {
            n_bcom[ComPortSlv]=0;
            return ;
          }
       */
          _fmemcpy(intrpr.bfcom,&cb_COM[ComPortSlv][0],(long int)(n_bcom[ComPortSlv]-2) );
          n_bcom[ComPortSlv]=0;
          f_intr_SlvRTU();
         }
}
/*-------------------------------------------*/
void f_get_SlvBuf()
{
  unsigned long int count=0xffff;

    if( ( bf_Slv = (struct stor_buf *)malloc( (size_t)count )) == NULL )
    {
      printf("\n\r!Slave buffer is not allocated.\n\r");
      RestoreCom(1);
      RestoreCom(2);
      RestoreCom(3);
      while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */
      RestoreCom(4);
      exit (0);
    }
}
/*-------------------------------------------*/
void f_free_SlvBuf()
{
  free( bf_Slv );
}
/*-------------------------------------------*/
void f_stor_Slv( char type,char *buf,int buf_n)
{
  long int nn;

 bf_Slv[uk_fin_Slv].time = TimeStamp;

 if(buf_n >= mess_lgth ) nn=mess_lgth;
 else nn=buf_n;

 bf_Slv[uk_fin_Slv].type_n=type | (char)nn;

 _fmemcpy(bf_Slv[uk_fin_Slv].messg,buf,nn );
 uk_fin_Slv=(uk_fin_Slv+1)&Slv_b_lgth_1;
}
/*-------------------------------------------*/
#define RTU_min 6
#define n_max_fn 5
#define NN_fict 1000
// ������⢮ ���� � ������� Host

/* =============
// �㭪�� ,  ����� � �����.�㬬.
  1,8, // �⥭�� Coil
  3,8, // �⥭�� Int
  5,8, // ������ Coil
  6,8, // ������ Int
  16,NN_fict, // ������ ��᪮�쪨� ���祭��
=============== */

int n_max_rcv=NN_fict;

int ffgets_SlvRTU(int ComPort)
{

//  �㭪�� �ਭ����� ᨬ���� �� ���� COM ComPort  � ���� cb_COM[ComPort].
//  �� ⠩���� ������� ��⠥��� ��������� � �㭪�� �����頥�
// ���祭�� 1.
//

/* ComPort - ����� COM   1...4 */
 char tmp;
 int tmp1;
 int i;
m1:
     if(IsCom(ComPort)==0)
     {
         if( WD_PMP_Per !=0 )
           if( f_timer(WD_PMP_time,WD_PMP_Per ))
           { // ��� �ᯥ譮�� �ਥ��

            if(WD_PMP_flag != 0)
            {
              WD_PMP_flag=0;
              f_icp_errS(WD_host);
            }
            WD_PMP_time=TimeStamp;
           }

           if( f_timer(WD_PMP_t1,WD_PMP_P1 ))
           { // ��� �ᯥ譮�� �ਥ��
            WD_PMP_Fl=0;
            WD_PMP_t1=TimeStamp;
           }

         if( f_timer(time_snd[ComPort],ToutAns[ComPort]))
         { // ��⥪ ⠩���� �ਥ�� �⢥� �� �������
            time_snd[ComPort]= TimeStamp;
m_end:
            if((n_bcom[ComPort] >= RTU_min)&& (cb_COM[ComPort][0]==AddrSlv))
            {
              if(f_check_crc_RTU(cb_COM[ComPort],n_bcom[ComPort])==0)
               {
                  goto m_err;
               }
              n_max_rcv= NN_fict;

   //       WD_PMP_flag=1;
              WD_PMP_time=TimeStamp;
              WD_PMP_t1=TimeStamp;
              WD_PMP_Fl=1;

              if(ICP_error[icp_lst_max] & WD_host)
              {
               ICP_error[icp_lst_max] &= ~(unsigned int)WD_host;
               ICP_error_c[icp_lst_max]=ICP_error[icp_lst_max];
               for(i=0,tmp1=0;i<=icp_lst_max;i++)
               {
                 tmp1 |=ICP_error[i];
               }
//              printf("\r\n tmp1= %04x",tmp1);

               if(tmp1==0)
               {
                FL_err=0;
                if(sw_mmi==0) f_prn_begin();
               }
              }
              return 1;
            }
            else
             {
m_err:
               n_bcom[ComPort]=0;
               n_max_rcv= NN_fict;
               return 0;
             }
         }
         return 0;
     }
     tmp=ReadCom(ComPort);
#if(Slv_deb != 0)
     printf("%02x ",(int)tmp & 0xff);
#endif

     ToutAns[ComPort]=byte_timout_rtu[ComPort];

     cb_COM[ComPort][n_bcom[ComPort]]=tmp;
     if( (++n_bcom[ComPort]) >= n_bufcom )
      {
        n_bcom[ComPort]--;
  /*
        printf("\n Command buffer overflow !\n--");
        puts(cb_COM1);
  */
      }

      if(n_bcom[ComPort] == 2)
         n_max_rcv=f_get_numRTU2(ComPort);
      else if ((n_bcom[ComPort] == 7) && (n_max_rcv == NN_fict)  )
         n_max_rcv=f_get_numRTU7(ComPort);

      if(n_bcom[ComPort]>= n_max_rcv) goto m_end;

      time_snd[ComPort]= TimeStamp;
      goto m1;
}
/*-------------------------------------------*/
int f_get_numRTU2(int ComPort)
{// �� ᮤ�ন���� cb_COM[ComPort][] � ������⢮� ���� n_bcom[ComPort]
 // ������ ����� ���뫪� RTU. �᫨ ����� �� ��।����� - �����頥� NN_fict
 int i_ret;
 switch ((int) cb_COM[ComPort][1])
 {
  case 1:
  case 3:
  case 5:
  case 6:
         i_ret=8;
         break;

  default: i_ret=NN_fict;
 }
 return i_ret;
}
/*-------------------------------------------*/
int f_get_numRTU7(int ComPort)
{// �� ᮤ�ন���� cb_COM[ComPort][] � ������⢮� ���� n_bcom[ComPort]
 // ������ ����� ���뫪� RTU. �᫨ ����� �� ��।����� - �����頥� NN_fict

 int i_ret;

 if( cb_COM[ComPort][1] == 16 )
   i_ret=(((int)cb_COM[ComPort][6]) & 0xff) + 9;
 else
   i_ret=NN_fict;

 return i_ret;
}
/*-------------------------------------------*/
  unsigned char buf_tmp[n_buf_RTU_s];
void  f_intr_SlvRTU()
{
  int exc;
  int fn_cod;
  int addr_beg,i,i1,i2,itmp;
  int Slv_addrO,Slv_nmbO;
  float ftmp;
  union  { float f; unsigned long l; } o;
  struct eee_dat *LIn_D;

  // �ਭ��� ������� �஢�७� �� ����஫��� �㬬� � ��室���� � intrpr.bfcom
  //  (��� ����஫쭮� �㬬�)

//---------------------------------------------------
  fn_cod=intrpr.bfcom[1];

  _fmemcpy(buf_tmp,intrpr.bfcom,(long int)(8) );
  if(fn_cod== 3)
  {   // �⥭�� Int
    Slv_addrO=f_get_intS(&intrpr.bfcom[2]);
    Slv_nmbO=f_get_intS(&intrpr.bfcom[4]);

    if(Slv_nmbO>125)
        goto m_err_addr;

    if( f_is_int(Slv_addrO) &&  f_is_int(Slv_addrO+Slv_nmbO-1) )
    { // ����襭� ����� int

      buf_tmp[0]=AddrSlv;
      buf_tmp[1]=fn_cod;
      buf_tmp[2]=Slv_nmbO+Slv_nmbO;

      for(i1=3,i=0;(i<Slv_nmbO)&&(i1< (n_buf_RTU_s-3)) ;i++)
       {
//       itmp=Slv_int[Slv_addrO+i];
         itmp=*(int *)list_Slv_int[Slv_addrO+i];
         buf_tmp[i1++]=(itmp>>8) & 0xff;
         buf_tmp[i1++]= itmp & 0xff;
       }
      goto out_b;
    }
    else
     if( f_is_float(Slv_addrO) &&  f_is_float(Slv_addrO+Slv_nmbO-2) )
     { // ����襭� ����� float
      if(Slv_addrO & 0x01) goto m_err_addr;
      if(Slv_nmbO  & 0x01) goto m_err_val;

      buf_tmp[0]=AddrSlv;
      buf_tmp[1]=fn_cod;
      buf_tmp[2]=Slv_nmbO+Slv_nmbO;
      Slv_nmbO=Slv_nmbO>>1;

      addr_beg=(Slv_addrO-AddrLowFloat)>> 1;
      for(i1=3,i=0;(i<Slv_nmbO)&&(i1< (n_buf_RTU_s-3));i++,i1+=4)
       {
         if((addr_beg+i) < n_sl_flt0)
           f_set_float( &buf_tmp[i1],*list_Slv_flt[addr_beg+i],cod_float);
         else
           f_set_float( &buf_tmp[i1],(float)*list_Slv_lng[addr_beg+i-n_sl_flt0],cod_float);
//         f_set_long( &buf_tmp[i1],*list_Slv_lng[addr_beg+i-n_sl_flt0]);
       }
      goto out_b;

     }
     else if((Slv_addrO == Addr2Slot1 ) && ( Slv_nmbO <= Slv2_slt1_lgth))
     {  // �⥭�� ���孨� ����஫��஬ ������ Slot1

      LIn_D=&Slv2_Slot1[0];

m_slt:
      buf_tmp[0]=AddrSlv;
      buf_tmp[1]=fn_cod;
      buf_tmp[2]=Slv_nmbO+Slv_nmbO;

      for(i1=3,i=0,i2=0;(i<Slv_nmbO)&&(i1< (n_buf_RTU_s-3)) ;i2++)
       {
             switch( LIn_D[i2].l )
             {
              case T_INT:
                f_set_int( &buf_tmp[i1], *((int *) LIn_D[i2].ptr)  );
                i1+=2;
                i++;
                break;

              case T_INT_L:
                f_set_long( &buf_tmp[i1], *((long int *) LIn_D[i2].ptr) );
                i1+=4;
                i+=2;
                break;

              case T_FLOAT:
                f_set_float( &buf_tmp[i1], *((float *) LIn_D[i2].ptr),1 );
                i1+=4;
                i+=2;
                break;
             }
       }
      goto out_b;

     }
    else goto m_err_addr;
  }
  if(fn_cod== 6)
  {   // ������ Int
    Slv_addrO=f_get_intS(&intrpr.bfcom[2]);
    if( f_is_int(Slv_addrO) )
    { // ������ ������ int
      *(int *)list_Slv_int[Slv_addrO]=f_get_intS(&intrpr.bfcom[4]);
      if((exc=f_int_fnc(Slv_addrO)) != 0)
       {
         CMD_OUT_p = CMD_IN | 0x8000;
         goto m_err;
       }

      CMD_OUT_p = CMD_IN; //  | 0x4000;
      i1=6;
      goto out_b;
    }
    else goto m_err_addr;
  }
  if(fn_cod == 16 )
  {   // ������ ��᪮�쪨� ���祭��
    Slv_addrO=f_get_intS(&intrpr.bfcom[2]);
    Slv_nmbO=f_get_intS(&intrpr.bfcom[4]);
    if( f_is_int(Slv_addrO) &&  f_is_int(Slv_addrO+Slv_nmbO-1) )
    { //   ����� int

     for(i1=7,i=0;i<Slv_nmbO;i++,i1+=2)
     {
      *(int *)list_Slv_int[Slv_addrO+i]=f_get_intS(&intrpr.bfcom[i1]);
      if((exc=f_int_fnc(Slv_addrO+i)) != 0)
         goto m_err;
     }

     i1=6;
     goto out_b;

    }
    else
     if( f_is_float(Slv_addrO) &&  f_is_float(Slv_addrO+Slv_nmbO-2) )
     { //  ����� float
      if(Slv_addrO & 0x01) goto m_err_addr;
      if(Slv_nmbO  & 0x01) goto m_err_val;

      addr_beg=(Slv_addrO-AddrLowFloat)>> 1;
      Slv_nmbO=Slv_nmbO>>1;
      // i1=7-3;
      for(i1=4,i=0;i<Slv_nmbO;i++,i1+=4 )
      {
         if((addr_beg+i) < n_sl_flt0)
            *list_Slv_flt[addr_beg+i]=f_get_float( &intrpr.bfcom[i1], cod_float);
         else
            *list_Slv_lng[addr_beg+i-n_sl_flt0]=f_get_float( &intrpr.bfcom[i1], cod_float);
      }
      i1=6;
      goto out_b;
     }
    else if((Slv_addrO == Addr2Slot2 ) && ( Slv_nmbO <= Slv2_slt2_lgth))
    {
     // Slot2  - �ਭ�� ������� � ���࠭� �������
// printf("\r\n SlvSlot2");
      if(f_set_slv( &Slv2_Slot2[0],Slv_nmbO )) goto m_err_val;
// printf("\r\n CMD_IN=%d",CMD_IN);
      if((exc=f_int_fnc(7)) != 0)
       {

// printf("\r\n exc=%d",exc);
         CMD_OUT_p = CMD_IN | 0x8000;
         goto m_err;
       }
      CMD_OUT_p = CMD_IN; //  | 0x4000;
      i1=6;
      goto out_b;

    }
    else goto m_err_addr;
  }
  else  goto m_err_fn ;

//---------------------------------------------------
m_err_fn  : // �㭪�� �� �ᯮ�����
 exc=01;
 goto m_err;

m_err_addr: // �������⨬� ����
 exc=02;
 goto m_err;

m_err_val : // �������⨬� �����
 exc=03;
 goto m_err;

m_err_slv : // �訡�� � Slave
 exc=04;
 goto m_err;

m_err:

 fn_cod |= 0x80;

 buf_tmp[0]=AddrSlv;
 buf_tmp[1]=fn_cod;
 buf_tmp[2]=exc;
 i2=3;

#if(Slv_deb != 0)

 printf("\n\r====");
 for(i=0;i<i2;i++)
 {
  printf("%02X ",buf_tmp[i]);
 }
 printf("====\n\r");
#endif

 f_stor_Slv(M_WR,buf_tmp,i2);
 f_prepareRTU(buf_tmp,&i2);

 ToComBufn(ComPortSlv,buf_tmp,i2);
 return;

out_b:

 buf_tmp[0]=AddrSlv;
 buf_tmp[1]=fn_cod;

 i2=i1;

#if(Slv_deb != 0)

 printf("\n\r====");
 for(i=0;i<i2;i++)
 {
  printf("%02X ",buf_tmp[i]);
 }
 printf("====\n\r");

#endif

  f_stor_Slv(M_WR,buf_tmp,i2);
// MmiGotoxy(0,1);    MmiPrintf("Before prep i2= %d    ",i2);
 if(f_prepareRTU1(buf_tmp,&i2)) goto m_err_val;
/*
 MmiGotoxy(0,2);    MmiPrintf("After prep i2= %d     ",i2);
 MmiGotoxy(0,3);    MmiPrintf("%2x %2x %2x %2x %2x %2x     ",buf_tmp[0],buf_tmp[1],buf_tmp[2],buf_tmp[3],buf_tmp[4],buf_tmp[5]);
 MmiGotoxy(0,4);    MmiPrintf("                             ");
 MmiGotoxy(0,5);    MmiPrintf("                              ");
*/
 ToComBufn(ComPortSlv,buf_tmp,i2);


 if(ff_Slv != NULL)
 {
  (*ff_Slv)(); // ���� �㭪樨
  ff_Slv = NULL;
 }
 return;

}
/*-------------------------------------------*/
/*-------------------------------------------*/
int f_is_int(int addr)
{
 if((addr >= AddrLowInt) && (addr <= AddrHighInt) )
    return 1;
 else return 0;
}
/*-------------------------------------------*/
int f_is_float(int addr)
{
 if((addr >= AddrLowFloat) && (addr <= AddrHighFloat) )
    return 1;
 else return 0;
}
/*-------------------------------------------*/
int  f_int_fnc(int Addr)
{ // return 1 - error, 0 - OK
 int i_ret;
 i_ret=0;
 switch( Addr)
 {
  case Cmd_reg:
       switch(*(int *)list_Slv_int[Addr] )
       {
        case 1:
         i_ret= f_start_dlv();
         break;
        case 2:
         i_ret= f_stop_dlv();
         break;
        case 3:
         i_ret= f_alm_stop();
         break;
        case 4:
         i_ret= f_rst_slv();
         break;
        case 5:
         i_ret= f_CE_slv();
         break;
        case 6:
         i_ret= f_WE_slv();
         break;
        case 7:
         i_ret= f_Baud_slv();
         break;
        case 11:
         i_ret= f_start_dlv11();
         break;
        case 17:  // fls
         i_ret= f_fls();
         break;

        default:
           f_cmd_prn();
           i_ret= RTU_Val;
         break;
       }
   default:
       break;

 }
 return i_ret;
}
/*-------------------------------------------*/
int f_stop_dlv()
{ // return 1 - error, 0 - OK
    if(sw_dlv_liq==3)
    {
       MmiGotoxy(0,0);   MmiPuts(list_avt[30]);  //" ���� ��⠭�����            ",//30
       MmiGotoxy(0,1);   MmiPuts(list_avt[35]);  //"      �� ������� Host   =     ",//35
       State_SLV=Cmd_brk;
       sw_dlv_liq=-1;
    }
    else if(sw_dlv_liq>0)
    {
      //  f_stop_cnt();
      //  fl_GO=0;
      //  fl_EQ=0;
      //  OUT_VAR=0;
          sw_dlv_liq=30;
          key__1 = STOP_H;
    }
    else return RTU_Val;
    return 0;
}
/*-------------------------------------------*/
int f_alm_stop()
{ // return 1 - error, 0 - OK

   f_icp_errS(Hst_alm);
   f_alarm();
// f_stop_cnt();

 return 0;
}
/*-------------------------------------------*/
int f_rst_slv()
{ // return 1 - error, 0 - OK

    f_wr_evt(evt_res);
    _asm cli
    _asm hlt

 return 0;
}
/*-------------------------------------------*/
int f_fls()
{ // return 1 - error, 0 - OK
 flag_Slv=0;

 RestoreCom(ComPortHost);
 InstallCom(ComPortHost,115200L,8,0,1);

 return 0;
}
/*-------------------------------------------*/
int f_CE_slv()
{ // return 1 - error, 0 - OK
 f_cl_error();
 return 0;
}
/*-------------------------------------------*/
int f_WE_slv()
{ // return 1 - error, 0 - OK
 ff_Slv=ff_we_slv;
 return 0;
}
/*-------------------------------------------*/
void ff_we_slv()
{
        if(f_wrt_eee()<0)
        {
          f_wr_evt(evt_we_err);
        }
        else
        {
          f_wr_evt(evt_we);
        }
}
/*-------------------------------------------*/
int f_start_dlv()
{ // return 1 - error, 0 - OK

int i_ret;

   i_ret=0;
 //  State_SLV = Cmd_err;

   if(FL_err)
    i_ret=RTU_Slv_err;
   else if(Slv_float[0] <= 0)
    i_ret = RTU_Val;
   else if(sw_dlv_liq<=0)
   {
       MassStamp=s_MVD[0].MassI;
       VolStamp=s_MVD[0].VolI;
       flag_dlv_fst=0;
       flag_prn_mass=0;

       *(int *)list_Slv_int[i_cfm]=0;
       WD_PMP_flag=1;
       State_SLV= Cmd_rcv;
       dose_dlvr= Slv_float[0];
       volume_f = Slv_float[0];
       f_prn_slv1();
       sw_dlv_liq=1;
       sw_mmi=193;
       Slv_float[1]=Slv_float[0];
       Slv_float[0]=0;
   }
   else
     i_ret = RTU_Val;
   return i_ret;
}
/*-------------------------------------------*/
int f_start_dlv11()
{ // return 1 - error, 0 - OK
  // ���� ��� ���㫥��� Totals - ��� �த�������
int i_ret;

   i_ret=0;
 //  State_SLV = Cmd_err;

   if(FL_err)
    i_ret=RTU_Slv_err;
   else if(Slv_float[0] <= 0)
    i_ret = RTU_Val;
   else if(sw_dlv_liq<=0)
   {
     if((MassStamp==-1000.)&& (VolStamp==-1000.))
     {
       MassStamp=s_MVD[0].MassI-s_MVD[0].MassT;
       VolStamp=s_MVD[0].VolI - s_MVD[0].VolT;
     }
       flag_dlv_fst=1;
       flag_prn_mass=1;

       *(int *)list_Slv_int[i_cfm]=0;
       WD_PMP_flag=1;
       State_SLV= Cmd_rcv;
       dose_dlvr= Slv_float[0];
       volume_f = Slv_float[0];
       f_prn_slv1();
       sw_dlv_liq=1;
       sw_mmi=193;
       Slv_float[1]=Slv_float[0];
       Slv_float[0]=0;
   }
   else
     i_ret = RTU_Val;
   return i_ret;
}
/*-------------------------------------------*/
/*-------------------------------------------*/
int f_cmd_prn()
{ // return 1 - error, 0 - OK

#if(Slv_deb != 0)
 printf(" \n\r== Command %d ==",*(int *)list_Slv_int[4]);
#endif

 return 0;
}
/*-------------------------------------------*/
int f_Baud_slv()
{
int i_ret;
   if(f_get_nb(Com_Baud_Slave) < 0  )
   {
 fin_e:
    Com_Baud_Slave=ComBaudSlv;
    i_ret = RTU_Val;
   }
   else
   {
     ComBaudSlv = Com_Baud_Slave;

     RestoreCom(ComPortSlv );
     if( InstallCom(ComPortSlv ,ComBaudSlv,Com_lgthSlv,Com_paritySlv,Com_stopSlv) < 0 ) goto fin_e;
     i_ret = 0;
   }
   return i_ret;
}
//--------------------------------
int f_set_slv( struct eee_dat *LIn_D, int Slv_nmbO )
{
int i,i1,i2;
      for(i1=4,i=0,i2=0;i<Slv_nmbO;i2++ )
      {

             switch( LIn_D[i2].l )
             {
              case T_INT:

                *((int *) LIn_D[i2].ptr)=f_get_int(&intrpr.bfcom[i1]);
                i1+=2;
                i++;
                break;

              case T_INT_L:

                *((long int *) LIn_D[i2].ptr)= f_get_long(&intrpr.bfcom[i1+3]);
                i1+=4;
                i+=2;
                break;

              case T_FLOAT:

                *((float *) LIn_D[i2].ptr)  = f_get_float( &intrpr.bfcom[i1], cod_float);
                i1+=4;
                i+=2;
                break;

              default:
                   return 1;
             }
      }

   return 0;
}
//--------------------------------------
