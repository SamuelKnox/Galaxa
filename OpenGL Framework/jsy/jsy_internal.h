#ifndef _JSY_INTERNAL_H_
#define _JSY_INTERNAL_H_

// Win32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "soil.h"
#include "fmod/fmod.hpp"
#include "jsy.h"

#define NULL 0


#ifdef _XBOX_
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
} GL_Window;										// GL_Window


#endif


typedef struct JsyTextureS
{
    unsigned int soilTextureId; //Win32
} JsyTextureT;

///////////////
// Input APIs
typedef struct JsyInputInternalS {

} JsyInputInternalT;


///////////////
// Graphic APIs
typedef struct JsyGInternalS {
    GL_Window * window;
    JsyTextureT texture[256]; // FIXME: Now only support 256 texture, means 256 texture id
    uint32_t textureCnt = 0;
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
    SoundNode_t * listSounds = NULL;
    SoundNode_t * tailSounds = NULL;
    uint32_t id_cnt = 0;
} JsyAudioInternalT;

#endif