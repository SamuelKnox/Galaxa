#ifndef _SOUND_MGR_H_
#define _SOUND_MGR_H_

#include "jsy/types.h"

#include "fmod/fmod.hpp"

using namespace FMOD;

class SoundManager
{
public:
    static SoundManager	*CreateInstance();
    static SoundManager	*GetInstance() { return sInstance; };
    ~SoundManager();

    void init();

    // Load a sound from local audio file, and the sound resource id
    uint32_t LoadSound(const char * fileName);
    // Play the sound resource
    void PlaySoundResource(uint32_t id);

private:

    // node of the sound resources list
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
    // the sound resources list
    SoundNode_t * listSounds = NULL;
    SoundNode_t * tailSounds = NULL;

    // This function is for fixing FMOD bug
    void putChannel(Channel * channel);
    // This function is for fixing FMOD bug
    void resumeChannel();
};

#endif