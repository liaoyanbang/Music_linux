#ifndef __VOICE__H
#define __VOICE__H

#include <alsa/asoundlib.h>

extern long volume;

#define MIN_VOICE 60

void Initvoice(void);
int setMasterVolume(long volume);
long getCurrentVolume(void);




#endif

