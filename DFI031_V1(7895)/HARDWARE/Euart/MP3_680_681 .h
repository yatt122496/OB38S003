#ifndef __680_881_MP3_H__
#define __680_881_MP3_H__

extern u8 Vol;
extern u8  MusicTime50ms;
extern void VolKey(void);

extern void EuartInit(void);
extern void Music_stop();
extern void Specify_Volume(void);
extern void MusicCon(void);
extern void Cycle_play(u8 num);

#endif