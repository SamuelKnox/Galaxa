#include <iostream>
#include "SoundManager.h"

SoundManager* SoundManager::sInstance = NULL;

SoundManager::SoundManager()
{
	// Create the FMOD sound obj
    FMOD_RESULT res = FMOD::System_Create(&soundSystem);
    if (res != FMOD_OK) {
        std::cout << "Sound System init failed: " << res << std::endl;
    }

	// Init the FMOD sound obj
    soundSystem->init(32, FMOD_INIT_NORMAL, NULL);

    memset(channels, 0, sizeof(Channel*) * 32);
}


SoundManager::~SoundManager()
{
    SoundNode_t* currentSoundNode = listSounds;
    while (currentSoundNode != NULL) {
        SoundNode_t* tmp = currentSoundNode->nextSound;
        free(currentSoundNode);
        currentSoundNode = tmp;
    }
    listSounds = NULL;
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
	// Load the sound file into the SoundManager
    SoundNode_t * newNode = (SoundNode_t*)malloc(sizeof(SoundNode_t));
	// Put into the internal list
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
	// Init it
    newNode->sound->setMode(FMOD_LOOP_OFF);

    return newNode->id;
}

void SoundManager::PlaySoundResource(uint32_t id) {
    SoundNode_t* currentSoundNode = listSounds;
    if (currentSoundNode == NULL) return;
	// Loop through the list until we find the sound resource
    while (currentSoundNode->id != id) {
        currentSoundNode = currentSoundNode->nextSound;
        if (currentSoundNode == NULL)
            return;
    }

    if (currentSoundNode->id == id) {
		// Fixing FMOD bug, all channels will stop if it randomly pick a low prioirty channel
        // Use resumeChannel to set higher priority for the channel that is playing
        resumeChannel();
        Channel * channel = NULL;
        soundSystem->playSound(currentSoundNode->sound, 0, false, &channel);
        // An old channel handle will become invalid if the sound system pick a channel, it makes the old channel handle invalid.
        // So we need to store the new channel handle even the channel is included in our list
        putChannel(channel);
    }
}

// This function is for fixing FMOD bug
void SoundManager::resumeChannel() {
	// Find all channel and modify their priority, the one that is curreny playing has high priority
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

// This function is for fixing FMOD bug
void SoundManager::putChannel(Channel * channel) {
    int index = 0;
    int low_priority = 0;
    channel->setPriority(0);
    // Find empty or low priority, modify the priority, and put the new channel handle into our array
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
