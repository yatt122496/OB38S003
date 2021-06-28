#ifndef __IIC_H__
#define __IIC_H__

#define  READ    0x01
//-------------------
//extern u8 IicDriverExamine(u8 Driver);
extern u8 IicReadLenData (u8 Driver,u8 len,u8 *ptr);
extern u8 IicWriteLenData(u8 Driver,u8 len,u8 *ptr); 
//-------------------
extern void IicInit(void);
//-------------------
#endif