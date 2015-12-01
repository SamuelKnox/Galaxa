#include <windows.h>
#include <iostream>
#include "SoundManager.h"

SoundManager* SoundManager::sInstance = NULL;

SoundManager::SoundManager()
{
    FMOD_RESULT res = FMOD::System_Create(&soundSystem);
    if (res != FMOD_OK) {
        std::cout << "Sound System init failed: " << res << std::endl;
    }

    soundSystem->init(32, FMOD_INIT_NORMAL, NULL);

    memset(channels, 0, sizeof(Channel*) * 32);
}


SoundManager::~SoundManager()
{

}

SoundManager *SoundManager::CreateInstance()
{
    if (sInstance != NULL)return sInstance;
    else
        sInstance = new SoundManager();
    return sInstance;
}

void SoundManager::init()
{

}

uint32_t SoundManager::LoadSound(const char * fileName) {

    SoundNode_t * newNode = (SoundNode_t*)malloc(sizeof(SoundNode_t));
    newNode->id = ++id_cnt;
    newNode->nextSound = NULL;
    if (listSounds == NULL) {
        listSounds = newNode;
    }
    if (tailSounds != NULL) {
        tailSounds->nextSound = newNode;
    }
    tailSounds = newNode;

    // Load sound file
    FMOD_RESULT res = soundSystem->createSound(fileName, FMOD_DEFAULT, 0, &(newNode->sound));
    if (res != FMOD_OK) {
        std::cout << "Sound System load sound failed " << res << std::endl;
    }

    newNode->sound->setMode(FMOD_LOOP_OFF);

    return newNode->id;
}

void SoundManager::PlaySoundResource(uint32_t id) {
    SoundNode_t* currentSoundNode = listSounds;
    if (currentSoundNode == NULL) return;

    while (currentSoundNode->id != id) {
        currentSoundNode = currentSoundNode->nextSound;
    }

    if (currentSoundNode->id == id) {
        resumeChannel();
        Channel * channel = NULL;
        soundSystem->playSound(currentSoundNode->sound, 0, false, &channel);
        putChannel(channel);
    }
}

// This two functions are for fixing FMOD bug
void SoundManager::resumeChannel() {
    for (int i = 0; i < 32; i++) {
        if (channels[i] != NULL) {
            bool isPlaying = false;
            channels[i]->isPlaying(&isPlaying);
            if (isPlaying) {
                channels[i]->setPriority(0);
            }
            else {
                channels[i]->setPriority(256);
                channels[i]->stop();
            }
        }
    }
}

// This two functions are for fixing FMOD bug
void SoundManager::putChannel(Channel * channel) {
    int index = 0;
    int low_priority = 0;
    channel->setPriority(0);
    for (int i = 0; i < 32; i++) {
        if (channels[i] == NULL) {
            index = i;
            break;
        }
        else {
            bool isPlaying = false;
            channels[i]->isPlaying(&isPlaying);
            if (isPlaying) {
                channels[i]->setPriority(0);
            }
            else {
                index = i;
                break;
            }
        }
    }
    channels[index] = channel;
}
