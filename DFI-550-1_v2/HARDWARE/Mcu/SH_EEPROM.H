#ifndef __SH_EEPROM_H__
#define __SH_EEPROM_H__


extern unsigned char EEPROM_Error;
extern void EraseEepromMsg( void );
extern bit ReadEepromLike(unsigned char *ReadWriteData);
extern void WriteEepromLike(unsigned char *ReadWriteData,unsigned char *ReadDatBuf);


#endif