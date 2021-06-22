/***********************************************************
*  �ļ�˵����
************************************************************
*  ����:
*
*  ����:
*
************************************************************
*  Ӳ����sh79f083
************************************************************
* ����Ȩ�� Copyright(C)���ֵ���
* ��������
***********************************************************/
#include "HARDWARE/main/SysInc.h"
#include "HARDWARE\Lib\inc\wdt.h"

#if IR_TEST
	extern xdata u8 bData[40], bAD_indx;
#endif

u8 KeyTestSize;
u8 UpKeyValue;

void Delay(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}
void Delay_long(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    Delay(0xffff);
	nCount--;
  }
}

void main(void)
{
#if UART_TEST
#if IR_TEST
	xdata u8 i;
#endif
	xdata unsigned long dwSys_time = 0;
#endif
  FlaInit();
  InitSys();
  //--------------------------
//   RSTSTAT=Bin(00000000);
#if WDT_SWITCH
		WDT_ClearWDT();					//������Ź�������
#endif
  Delay_long(24);
#if WDT_SWITCH
		WDT_ClearWDT();					//������Ź�������
#endif
//   RSTSTAT=Bin(00000000);
  EA   = 1;
  //--------------------------
  UpKeyValue   = 0x55;
  KeyTestSize  = 4;
  while(KeyTestSize)
  {
#if  (IO_AD_KEY_OTP == 0)
    if(KeyNew)
#else
    if(AdKeyNew)
#endif
    {
#if WDT_SWITCH
		WDT_ClearWDT();					//������Ź�������
#endif
      GainAdKeyValue  ();
      if(PcbKeyValue != UpKeyValue)
      UpKeyValue = PcbKeyValue;
	  else
	  {		//���αȽϽ����ͬ��ֵȷ��
        switch(PcbKeyValue)
        {
          case 1    :EepRomBoot(1);KeyTestSize = 0;break;  //�ϵ簴POWER����λϵͳ��
          default   :              KeyTestSize = 0;break;
        }
	  }
	  if(KeyTestSize)
	  KeyTestSize--;
    }
  }
  //--------------------------
  EepromInit(0);
  //--------------------------
  EuartInit();
  Cycle_play(0);
  Delay_long(1);
  //--------------------------
  while(1)
  {
#if UART_TEST
		if (Sys_Time - dwSys_time > 999) {
			dwSys_time = Sys_Time;
			// FOT = !FOT;
			UART1_SendByte(0x5a);
#if IR_TEST
			// UART0_TX(bAD_indx);
			if (bAD_indx) {
				for ( i = 0; i < bAD_indx; i++) {
					// UART0_TX(bData[i]);
					bData[i];
				}
				bAD_indx = 0;
			}
#endif
		}
#endif
#if WDT_SWITCH
		WDT_ClearWDT();					//������Ź�������
#endif
	// RSTSTAT=Bin(00000010);
	KeyValueApart();
	AdNtc();
	ArAd();
    HeatCon();
	SysTimer50ms();
	MusicCon();
  }
}
