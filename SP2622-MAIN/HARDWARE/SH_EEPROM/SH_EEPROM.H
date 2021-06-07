#ifndef __SH_EEPROM_H__
#define __SH_EEPROM_H__

//-------------------------------------------------
extern bit EepRomBoot(unsigned char PowerErase);
extern void EraseEepromMsg( void );
extern void EraseEepromMsg1( void );
extern bit ReadEepromLike(unsigned char *ReadWriteData);
extern void WriteEepromLike(unsigned char *ReadWriteData);
//-------------------------------------------------	 
extern bit SaveSet;
//-------------------------------------------------
extern void EepromInit( unsigned char PowerErase );
extern void SaveSetCall( void );
//-------------------------------------------------


#endif