#ifndef _JSY_INTERNAL_H_
#define _JSY_INTERNAL_H_

#ifdef _XBOX
#include <stdlib.h>
#include <string.h>
#else
// Win32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#endif
#include "soil.h"
#include "fmod/fmod.hpp"
#include "jsy.h"

#define NULL 0

#ifdef _XBOX
#else

typedef struct {									// Contains Information Vital To Applications
    HINSTANCE		hInstance;						// Application Instance
    const char*		className;						// Application ClassName
} Application;										// Application

typedef struct {									// Window Creation Info
    Application 		application;				// Application Structure
    int					width;						// Width
    int					height;						// Height
} GL_WindowInit;									// GL_WindowInit

typedef struct {									// Contains Information Vital To A Window
    HWND				hWnd;						// Window Handle
    HDC					hDC;						// Device Context
    HGLRC				hRC;						// Rendering Context
    GL_WindowInit		init;						// Window Init
    BOOL				isVisible;					// Window Visible?
    DWORD				lastTickCount;				// Tick Counter
} GL_Window;// GL_Window

#endif

typedef struct JsyTextureS
{
#ifdef _XBOX
	unsigned int textureId;
#else
    unsigned int soilTextureId; //Win32
#endif
} JsyTextureT;

///////////////
// Input APIs
typedef struct JsyInputInternalS {

} JsyInputInternalT;


///////////////
// Graphic APIs
typedef struct JsyGInternalS {
#ifdef _XBOX
#else
    GL_Window * window;
#endif
    JsyTextureT texture[256]; // FIXME: Now only support 256 texture, means 256 texture id
    uint32_t textureCnt;
} JsyGInternalT;

///////////////
// Audio APIs

// node of the sound resources list
typedef struct SoundNode_s {
    uint32_t id;
    FMOD::Sound * sound;
    struct SoundNode_s * nextSound;
} SoundNode_t;


typedef struct JsyAudioInternalS {
    // FMOD stuff
    FMOD::System *soundSystem;
    FMOD::Channel * channels[32];
    // the sound resources list
    SoundNode_t * listSounds;
    SoundNode_t * tailSounds;
    uint32_t id_cnt;
} JsyAudioInternalT;

#endif