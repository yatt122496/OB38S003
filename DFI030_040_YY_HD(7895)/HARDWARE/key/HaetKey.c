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
#include "HARDWARE\main\SysInc.h"
//-----------------------
bit HeatOnOff;
bit HeatLock;
//-----------------------

void HeatKey(void)
{
  if(HeatLock)
  {
//    if(!Standby)
//	{
//	  Standby = 1;
//	  Specify_Volume();
//	  KeySaveDat();
//	}
    LookFlhWood();
  }else
  {
//    if(!Standby)
//    {
//      Standby = 1;
//	  Specify_Volume();
//	  if(!HeatOnOff)
//      goto OnHeat;
//    }else
    {
//      OnHeat:
	  HeatOnOff = ~HeatOnOff;
      if(HeatOnOff)
  	  Hot3min();
    }
    KeySaveDat();
  }
}

/************************************************************
*
* 		   ������
************************************************************/
void HeatLook( void )
{
  if(Standby){
//  Standby   = 1;
    HeatLock  = ~HeatLock;
  //HeatOnOff = 0;
    KeySaveDat();
    LookFlhWood();
  }
}