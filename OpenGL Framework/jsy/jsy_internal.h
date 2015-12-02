#ifndef _JSY_INTERNAL_H_
#define _JSY_INTERNAL_H_

// Win32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "soil.h"

#include "jsy.h"

#define NULL 0

typedef struct JsyTextureS
{
    unsigned int soilTextureId; //Win32
} JsyTextureT;


typedef struct JsyInternalS {


    JsyTextureT texture[256]; // FIXME: Now only support 256 texture, means 256 texture id
    uint32_t textureCnt = 0;
} JsyInternalT;





#endif