#ifndef __SH_EEPROM_H__
#define __SH_EEPROM_H__

//-------------------------------------------------
bit EepRomBoot(unsigned char PowerErase);
void EraseEepromMsg( void );
void EraseEepromMsg1( void );
bit ReadEepromLike(unsigned char *ReadWriteData);
void WriteEepromLike(unsigned char *ReadWriteData);
//-------------------------------------------------
extern bit SaveSet;
//-------------------------------------------------
void EepromInit( unsigned char PowerErase );
void SaveSetCall( void );
//-------------------------------------------------


#endif