#ifndef _SOUND_MGR_H_
#define _SOUND_MGR_H_

#include "baseTypes.h"

#include "fmod/fmod.hpp"

using namespace FMOD;

class SoundManager
{
public:
    static SoundManager	*CreateInstance();
    static SoundManager	*GetInstance() { return sInstance; };
    ~SoundManager();

    void init();

    uint32_t LoadSound(const char * fileName);
    void PlaySoundResource(uint32_t id);

private:

    typedef struct SoundNode_s {
        uint32_t id;
        Sound * sound;
        struct SoundNode_s * nextSound;
    } SoundNode_t;
    uint32_t id_cnt = 0;


    static SoundManager *sInstance;
    SoundManager();

    // FMOD stuff
    System *soundSystem;
    Channel * channels[32];
    SoundNode_t * listSounds = NULL;
    SoundNode_t * tailSounds = NULL;

    void putChannel(Channel * channel);
    void resumeChannel();
};

#endif