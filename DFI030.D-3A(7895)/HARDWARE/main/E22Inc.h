/***********************************************************
*  文件说明：
************************************************************
*  日期:
*
*  作者:
*  说明:
*
************************************************************
*  硬件：sh79f083
************************************************************
* 【版权】 Copyright(C)鹏林电子
* 【声明】
***********************************************************/
#ifndef __E22_INC_H__
#define __E22_INC_H__

#define   DFI030_YY_IO_EN    1 //DFI030 IO KEY   4BE7H
#define   DFI030_HD_IO_EN    0 //DFI030 IO KEY   4CDAH

#define   DFI030_YY_AD_EN    0 //DFI030 AD KEY
#define   DFI030_HD_AD_EN    0 //DFI030 AD KEY

#define   DFI040_AD_EN       0 //DFI040 AD_KEY

#define   DFI040_YY_AD_EN    0 //DFI040 AD_KEY 弧形5键  5955H
#define   DFI040_HD_AD_EN    0 //DFI040 AD_KEY HD  5键  592CH


#define   ERROR    (DFI030_YY_IO_EN + DFI030_HD_IO_EN + /*DFI030 IO KEY */ \
                    DFI030_YY_AD_EN + DFI030_HD_AD_EN + /*DFI030 AD KEY */ \
                    DFI040_AD_EN    + DFI040_YY_AD_EN + DFI040_HD_AD_EN)  /*DFI040 AD_KEY */

#if  ((ERROR == 0) || (ERROR > 1))
  #if (ERROR == 0)
    #error "错误:你没有选中任何机型..."
  #else
    #error "错误:你不能同时选中多种机型,你只能选择其中的一种?"
  #endif
  #define IR_OTP          0
  #define IO_AD_KEY_OTP   0
  #define D030_040_KEY    0
#else

#endif
  /***********************************************************/
  #if (DFI030_YY_IO_EN == 1)
    #define IR_YY_HD_OTP    0
    #define IO_AD_KEY_OTP   0
    #define D030_040_KEY    0
  #endif

  #if (DFI030_HD_IO_EN == 1)
    #define IR_YY_HD_OTP    1
    #define IO_AD_KEY_OTP   0
    #define D030_040_KEY    0
  #endif
  /***********************************************************/
  #if (DFI030_YY_AD_EN == 1)
    #define IR_YY_HD_OTP    0
    #define IO_AD_KEY_OTP   1
    #define D030_040_KEY    0
  #endif

  #if (DFI030_HD_AD_EN == 1)
    #define IR_YY_HD_OTP    1
    #define IO_AD_KEY_OTP   1
    #define D030_040_KEY    0
  #endif
  /***********************************************************/
  #if (DFI040_AD_EN == 1)
    #define IR_YY_HD_OTP    2
    #define IO_AD_KEY_OTP   1
    #define D030_040_KEY    1
  #endif
  /***********************************************************/
  #if (DFI040_YY_AD_EN == 1)
    #define IR_YY_HD_OTP    3
    #define IO_AD_KEY_OTP   1
    #define D030_040_KEY    1
  #endif
  /***********************************************************/
  #if (DFI040_HD_AD_EN == 1)
    #define IR_YY_HD_OTP    4
    #define IO_AD_KEY_OTP   1
    #define D030_040_KEY    1
  #endif
  /***********************************************************/
#define FLA_MAX    6   //E23 火焰6档
//#define   DWL_EN   1   //使能顶灯
#define   FC_EN    1   //1 : UK  0 : UL

#endif