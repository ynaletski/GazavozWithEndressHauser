
#define HOLD 1
#define UP   2
#define DN   4
#define PMP_START 5
#define PMP_STOP  6

extern void (*ff_valve)();
void f_init_valve();
void f_two_valve();

void f_ADD();

extern int valve_mode;
extern float P_min_valve;

extern long int Per_up_min_v;
extern long int Per_up_max_v;
extern long int Per_dn_min_v;
extern long int Per_dn_max_v;
extern long int Tim_hld     ;
extern long int Per_UP_dl   ;
extern long int Per_DN_dl   ;

extern long int Flow_beg;
extern long int Flow_nom;

extern float Vol_beg;

extern float Mass_min;
extern long int Flow_min;
extern float Mass_min1;
extern long int Flow_min1;
extern float Mass_min2;
extern long int Flow_min2;


extern float conc1;
extern float conc2;
extern float Add_flow;
extern float Vol_add_min ;
extern float Vol_add_beg;
extern float Vol_add_end;

extern long int Tim_P_go;
extern long int Tim_P_st;
extern long int Per_Add_dl;
extern long int Tim_hld_a;

extern float Add_cur;  // текущее количество влитой добавки
extern float Add_dem;  // требумое количество влитой добавки
extern float add_end;

