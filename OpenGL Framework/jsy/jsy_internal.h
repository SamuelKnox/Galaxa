#ifndef _JSY_INTERNAL_H_
#define _JSY_INTERNAL_H_

#ifdef _XBOX
#include <stdlib.h>
#include <string.h>
#include <xtl.h>
#include <xgraphics.h>
#include "Resource.h"
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

///////////////
// Input APIs
typedef struct JsyInputInternalS {

} JsyInputInternalT;

typedef struct JsyTextureS
{
#ifdef _XBOX
	unsigned int textureId;
#else
    unsigned int soilTextureId; //Win32
#endif
} JsyTextureT;

///////////////
// Graphic APIs

#ifdef _XBOX

#define XBOX_WIN_Width 640.0f
#define XBOX_WIN_Height 480.0f

#define RATIO 0.5f

struct PANELVERTEX
{
    FLOAT x, y, z;
    DWORD color;
    FLOAT u, v;
};

#define D3DFVF_PANELVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#endif


typedef struct JsyGInternalS {
#ifdef _XBOX

	LPDIRECT3D8             g_pD3D;          // Used to create the D3DDevice
	LPDIRECT3DDEVICE8       g_pd3dDevice;          // Our rendering device
	BYTE*                   g_pResourceSysMemData; // Sysmem data for the packed resource
	BYTE*                   g_pResourceVidMemData; // Vidmem data for the packed resource
	LPDIRECT3DTEXTURE8      g_pTexture[256]; // Our texture
	LPDIRECT3DVERTEXBUFFER8 g_pVertices;
#else
    GL_Window * window;
    JsyTextureT texture[256]; // FIXME: Now only support 256 texture, means 256 texture id
#endif
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