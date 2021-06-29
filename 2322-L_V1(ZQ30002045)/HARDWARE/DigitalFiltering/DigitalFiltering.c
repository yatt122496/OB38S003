/***********************************************************
*  TM1638驱动                                              
************************************************************
*  日期:2011.9.21 5:00 
*									                                                                                                                                            
*  作者:  cuoiszf                                                                                           
*                                                          
************************************************************
*  硬件：MB95F204K                                                 
************************************************************
* 【版权】 Copyright(C)鹏林电子                           
* 【声明】                                
***********************************************************/
//;************************************************* 
unsigned char code FahrenheitList[129]=	
{
//0	  1	  2	  3	  4	  5	  6	  7	  8	  9	  10  11  12  13  14  15
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,	
//16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,	
//32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47
  32, 32, 32, 32, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
//48  49  50  51  52  53  54  55  56  57  58  59  60  61  62  63
  44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 53, 54, 55, 56, 56, 57,	
//64  65  66  67  68  69  70  71  72  73  74  75  76  77  78  79
  58, 59, 60, 60, 61, 62, 63, 63, 64, 65, 66, 67, 68, 68, 69, 70,
//80  81  82  83  84  85  86  87  88  89  90  91  92  93  94  95		
  70, 71, 71, 72, 73, 73, 74, 75, 75, 76, 77, 77, 78, 79, 79, 80,		
//96  97  98  99  100 101 102 103 104 105 106 107 108 109 110 111
  81, 82, 82, 83, 84, 85, 86, 87, 88, 88, 89, 90, 91, 91, 92, 92,		
//112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127
  93, 94, 94, 95, 95, 96, 97, 98, 98, 99, 99, 99, 99, 99, 99, 99,		
//128
  99		 
}; 
//;*********************************************	
unsigned char code CelsiusList[101]=
{
//0	  1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
//16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31
  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 
//32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47
  0 , 0 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 6 , 6 , 7 , 7 , 8 , 8 ,
//48  49  50  51  52  53  54  55  56  57  58  59  60  61  62  63  
  9 , 9 , 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 16, 16, 17, 17, 		
//64  65  66  67  68  69  70  71  72  73  74  75  76  77  78  79  
  18, 18, 19, 19, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 		
//80  81  82  83  84  85  86  87  88  89  90  91  92  93  94  95  
  26, 27, 28, 28, 29, 29, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 		
//96  97  98  99  100
  36, 36, 37, 37, 37		
};                                     
//;********************************************* 
ctof:
{
//0	  1	  2   3	  4	  5	  6	  7	  8	  9	  10  11  12  13  14  15
  32, 34, 35, 37, 39, 41, 43, 44, 46, 48, 50, 52, 53, 55, 57, 59,
//16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31
  61, 62, 64, 66, 68, 70, 71, 73, 75, 77, 79, 80, 82, 84, 86, 88,
//32  33  34  35  36  37  38  39  40  41
  90, 91, 93, 95, 97, 99, 99, 99, 99, 99
};

unsigned char  AdCh[4]={0x83,0x85;0x87,0x8F};

//外部变量
unsigned char  CelsiusValue;
unsigned char  FahrenheitNowValue;


bit DF_Timer;
bit HotOnCheckErr;

unsigned int AdBuff[4];

unsigned char ErrAdValue1;
unsigned char ErrAdValue2;
unsigned char ErrAdValue3;
unsigned char NtcAdValue ;

unsigned char AdTimes;
unsigned char SensorTimes;

void  DigitalFiltering( void )
{
   if(DF_Timer10ms==0)
   return;
   DF_Timer10ms=0;
   if(ADCON&&0X01)
   return
   //------------------
   Int16Buff=ADDH<<8;
   Int16Buff=ADDL;
   AD_NtcValue=Int16Buff>>2;
   //--------------------     
   AdBuff[AdChChoice]+AD_NtcValue;
   //------------
   if(AdChChoice==3)
   {
     AdChChoice=0;
     AdTimes++;
   }
   else
   AdChChoice++; 
   //------------
   adcm=AdCh[AdChChoice];
   //-------------------
   if(HOT==0)
   HotOnCheckErr=0;
   //--------------------
   if(AdTimes==4)
   {
     if(HotOnCheckErr==1)
     {
       ErrAdValue1=AdBuff[0]/4; 
       ErrAdValue2=AdBuff[1]/4;
       ErrAdValue3=AdBuff[2]/4;
     } 
     AdBuff[0]=0; 
     AdBuff[1]=0;
     AdBuff[2]=0;        
     NtcAdValue=AdBuff[3]/4;
     if( NtcAdValue>128)
     NtcAdValue=128;
     AdBuff[3]=0;
     AdTimes=0;
     HotOnCheckErr=1;
     SensorTimes++;
     if(SensorTimes==1)
	 {
	   FahrenheitNowValue = FahrenheitList[NtcAdValue]  ;
       CelsiusValue       = CelsiusList[FahrenheitNowValue];		
     }
     else
     if(sensor_times>38)
     SensorTimes=0;       
   } 
}





















   unsigned int  data NTC_Buff;
   unsigned char data Result;
   static uchar data NTC_MediValue;
   static uchar data NTC_BackValue;
 
   if(AD_NTC_NEW==1)
   {  
      AD_NTC_NEW=0;
      if(AD_NTC_10MS==1)
      {
        AD_NTC_10MS=0;
        if(NTC_Value<NTC_MediValue)
        {
          if(NTC_BackValue>=NTC_MediValue)
          NTC_Counter=0; 
          else 
          if(NTC_Counter<255)
          NTC_Counter++;                   
        }
        else
        {
          if(NTC_BackValue<NTC_MediValue)
          NTC_Counter=0;
          else             
          if(NTC_Counter<255)
          NTC_Counter++;                                              
        }
        NTC_BackValue=NTC_Value;
        if(NTC_BackValue!=NTC_MediValue)
        {
          if(NTC_BackValue<NTC_MediValue)
          {
            Result=NTC_MediValue-NTC_Value;
            NTC_Buff=Result* NTC_Counter;
            NTC_Buff=NTC_Buff>>8;
            NTC_MediValue=NTC_MediValue-NTC_Buff;
          }
          else
          {
            Result=NTC_Value-NTC_MediValue;
            NTC_Buff=Result* NTC_Counter;
            NTC_Buff=NTC_Buff>>8;
            NTC_MediValue=NTC_MediValue+NTC_Buff;
          }
        }
        if(NTC_MediValue>128)
        NTC_MediValue=128;
		FahrenheitNowValue=FahrenheitList[NTC_MediValue]  ;
        CelsiusValue      =CelsiusList[FahrenheitNowValue];				
      }
   }
}