
#define ES_IN    msk_int[num_in1]
#define UZA_IN   msk_int[num_in2]
#define LVL_IN   msk_int[num_in3]
#define STRT_IN  msk_int[num_in4]
#define STOP_IN  msk_int[num_in5]
#define CONS_IN  msk_int[num_in6]
#define TRAP_IN  msk_int[num_in7]

#define UZA_E    2
#define LVL_E    3
#define STOP_E   5
#define CONS_E   6
#define TRAP_E   7
#define ID_E     8
#define STOP_H   9

#define OUT1 msk_int[num_out1]
#define OUT2 msk_int[num_out2]
#define OUT3 msk_int[num_out3]
#define OUT4 msk_int[num_out4]
#define OUT5 msk_int[num_out5]
#define OUT6 msk_int[num_out6]
#define OUT7 msk_int[num_out7]
#define OUT8 msk_int[num_out8]

#define INP1 msk_int[num_in1]
#define INP2 msk_int[num_in2]
#define INP3 msk_int[num_in3]
#define INP4 msk_int[num_in4]
#define INP5 msk_int[num_in5]
#define INP6 msk_int[num_in6]
#define INP7 msk_int[num_in7]
#define INP8 msk_int[num_in8]

#define CLP0 msk_int[0]
#define PUMP msk_int[num_out3]

// клапан дозатора
#define PMP_AD1  msk_int[num_out5]
#define PMP_AD2  msk_int[num_out6]

// дозатор
#define SW_AD    msk_int[num_out7]
#define LNK_MMI  msk_int[num_out8]

/*
#define mski_ES   mski_inp1
#define mski_UZA  mski_inp2
#define mski_LVL  mski_inp3
#define mski_STRT  mski_inp4
#define mski_STOP  mski_inp5
#define mski_TRAP  mski_inp6
#define mski_CONS  mski_inp7
*/

extern unsigned int OUT_VAR;  // состояние дискретных выходов
extern unsigned int INP_VAR;  // состояние дискретных входов
extern unsigned int INP_VAR_c;  // состояние дискретных входов

extern int analog_num[];
extern float analog_scale[];
extern float analog_offset[];

#define RCV_FLG      0x100

#define NA_scale (65535.)
#define MaxADC 65536L


#define UZA_IN   msk_int[num_in2]


#define Out_on(IntMsk)  OUT_VAR |= IntMsk
#define Out_off(IntMsk)  OUT_VAR &= ~IntMsk

#define  T_Mot_Stop (15000L)

extern int fl_GO;
extern int fl_EQ;     // флаг выравнивания давления через MVD
extern int flagS_ES;  // признак останова по нажатию ES
extern int flagS_UZA; // признак останова по отсутствию UZA
extern int flag_dlv_fst;
extern int flag_prn_mass;
extern int flag_rcv_fst;

extern int sw_dlv_liq;
extern int sw_dlv_gas;
extern int sw_rcv_liq;
extern int sw_rcv_gas;
extern float dose_rcv,dose_dlvr;

extern int key__1;
extern int flag_continue;
extern int flag_rcv;

void f_sens();
int f_dlv_liq(int key);
int f_dlv_gas(int key);
int f_rcv_liq(int key);
int f_rcv_gas(int key);
void f_stop_cnt_eq();
void f_stop_EQ();
void f_stop_EQn();
int f_need_EQ_dlv();
int f_need_EQ_rcv();
int f_need_LIQ_dlv();
int f_need_LIQ_rcv();

extern long int time_com_cl    ;
extern long int time_com_cl_off;
extern long int time_cnt_cl_off;
extern long int time_gas_cl_on ;
extern long int time_gas_cl_off;

extern long int time_EQ_rcv;
extern long int time_EQ_dlv;
extern long int time_LIQ_rcv;
extern long int time_LIQ_dlv;


extern int flagS_DLT;
extern unsigned int INP_inv;
extern unsigned int INP_VARi;
extern unsigned int INP_MSK_OK;
extern int flagE_UZA;
extern unsigned int OUT_VAR_c;

void f_inp7188();

extern int *DriveStatus;
extern int DriveSV[];
extern int DriveSA[];
extern int DriveSD[];
extern int DriveState[];
extern int DriveCurrent[];
extern int DriveError[];

extern int (*f_Drive_St_chk)();
extern int (*f_Drive_Rn_chk)();
extern void (*f_Drive_Stop)();
extern void (*f_Drive_Run)();

extern int flag_ext_t;
extern int Drive_SV_beg[];
extern int Drive_SA_beg[];
extern int Drive_SD_beg[];
extern char list_avt[][32];

extern long int Tim_Prep1;
extern long int Tim_Prep_ND;
extern float F_Dns_off;
extern float P_beg_valve;

extern int INP_VARi_1;
