#include "voice.h"

snd_mixer_t* handle = NULL;

snd_mixer_elem_t* element_handle = NULL;

long minVolume,maxVolume;

long volume = MIN_VOICE;

void Initvoice(void)
{
    int res = 0;
    snd_mixer_selem_id_t* sid = NULL;
    const char* card = "default";
    const char* selem_name = "Playback";
    //1. 打开混音设备 
    res = snd_mixer_open(&handle,0);

    //2. attach HCTL to open mixer
    res = snd_mixer_attach(handle,card);

    //3. Register mixer simple element class.
    snd_mixer_selem_register(handle,NULL,NULL);

    //4. 取得第一個 element，也就是 Master
    snd_mixer_load(handle);

    //5. allocate an invalid snd_mixer_selem_id_t using standard alloca
    snd_mixer_selem_id_alloca(&sid);

    //6. 设置元素ID的位置
    snd_mixer_selem_id_set_index(sid,0);

    //7. 设置元素ID的名字
    snd_mixer_selem_id_set_name(sid,selem_name);

    //8. 查找元素
    element_handle = snd_mixer_find_selem(handle,sid);

    res = snd_mixer_selem_get_playback_volume_range(element_handle,&minVolume,&maxVolume);

    setMasterVolume(volume);
}


int setMasterVolume(long volume)
{
    if(volume<MIN_VOICE) volume = MIN_VOICE;
    long alsaVolume = volume * (maxVolume - minVolume) /100;

    if(snd_mixer_selem_set_playback_volume_all(element_handle,alsaVolume)<0){
        if(handle)
        snd_mixer_close(handle);
        return -1;
    }

    return 0;
}


long getCurrentVolume(void)
{
    long alsaVolume;
    if(snd_mixer_selem_get_playback_volume(element_handle,SND_MIXER_SCHN_MONO,&alsaVolume)<0)
    {
        if(handle)
        {
            snd_mixer_close(handle);
            return -1;
        }
    }
    return (alsaVolume*100)/(maxVolume - minVolume);
}

