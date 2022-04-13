
#define Add_pmp  2
                    // 0 - Отдельные резервары без добавки и с добавкой с индивидуальными насосами
                    //     OUT3  - насос резервуара без добавки
                    //     SW_AD - насос резервуара с добавкой

                    // 1 - автономный импульсный дозатор
                    //     OUT3  - основной насос
                    //     SW_AD - автономный дозатор

                    // 2   Отдельные резервары с индивидуальными насосами
                    //   - OUT3  - насос резервуара N_resv_dsp[1]
                    //     SW_AD - насос резервуара N_resv_dsp[2]


#define Test 0  // 1 - тестовый режим без MVD
#define SIM0 1  // 1 - тестовый режим без MVD

#define PML_P 1 // 1 - протокол Pumalan

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <io.h>
#include <time.h>
#include <sys\types.h>
#include <sys\timeb.h>

#include "device.h"

#include "PROC.h"
#include "MMI.h"
#include "ekd.h"

#include "queue.h"
#include "icp.h"
#include "host.h"
#include "7017c.h"
#include "i7060.h"
#include "eee.h"
#include "rtu.h"
#include "sk.h"
#include "delta.h"
#include "MVD.h"
#include "tsd.h"
#include "arch.h"
#include "avt_ctrl.h"
#include "reg.h"
//#include "cor_adc.h"
#include "slave.h"
#include "valve.h"
#include "ref_t.h"
#include "pmlan.h"

