#ifndef __SYS_INC_H__
#define __SYS_INC_H__


#include <math.h>
#include <INTRINS.H>
#include "HARDWARE\Mcu\McuInc.h"
//-----------------------------

//#include "HARDWARE\ShTouch\ShTouch.h"
//#include "HARDWARE\IIC\IIC.h"
//#include "HARDWARE\TM2314\TM2314.h"

#include "HARDWARE\Vrad\Vrad.h"
#include "HARDWARE\ad\ad.h"

//-----------------------------
#include "HARDWARE\Disp\Disp.h"
////-----------------------------
#include "HARDWARE\IR\ir.h"
#include "HARDWARE\Key\SysKey.h"
#include "HARDWARE\Key\PowerKey.h"
#include "HARDWARE\Key\FlaKey.h"
#include "HARDWARE\Key\HeatKey.h"
#include "HARDWARE\HeatCon\HeatCon.h"
#include "HARDWARE\SysMem\SysMem.h"
//-----------------------------
 #include "HARDWARE\ErrTest\ErrTest.h"
//-----------------------------
//#define BUZZ         P1_6
//#define CLK          P1_6
////-----------------------------
//#define TM1621_DIO   P1_3
//#define TM1621_WR    P1_4
//#define TM1621_RD    P1_5
//#define TM1621_CS    P1_7
////-----------------------------
//#define BG_LED       P1_0
//#define YG_DENG      P0_3
////-----------------------------
//#define TEST1        P0_4
//#define TEST2        P0_5
/*
     WDT溢出周期控制位
     000：溢出周期最小值 = 4096ms
     001：溢出周期最小值 = 1024ms
     010：溢出周期最小值 = 256ms
     011：溢出周期最小值 = 128ms
     100：溢出周期最小值 = 64ms
     101：溢出周期最小值 = 16ms
     110：溢出周期最小值 = 4ms
     111：溢出周期最小值 = 1ms
*/
#endif