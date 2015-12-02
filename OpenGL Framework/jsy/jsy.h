#ifndef _JSY_H_
#define _JSY_H_

#include "types.h"

// This is JSY virtual platform library for PC and XBOX

// Error codes for JSY functions
typedef enum JSY_ERROR_S {
    JSY_SUCCEED = 0,
    JSY_ERROR_OOM = -100,
    JSY_ERROR_INITED = -101,
} JSY_ERROR_T;

///////////////////////
// Simple Graphic APIs

// The Graphic handle
typedef void * JSYGHandle;

typedef void * JSYGHandle;

// Invalid handle
#define JSYG_INVALID_HANDLE 0

JSY_ERROR_T JsyGInit(JSYGHandle * pHandle);

JSY_ERROR_T JsyGClose(JSYGHandle handle);

JSY_ERROR_T JStGLoadTexture(JSYGHandle handle, const char * fileName, uint32_t * pTextureId);

JSY_ERROR_T JsyGDrawBackGround(JSYGHandle handle, uint32_t textureId, float_t width, float_t height,
    float_t yTexCoord, uint32_t numSprites);

JSY_ERROR_T JsyGDrawLine(JSYGHandle handle, float_t startX, float_t startY, float_t endX, float_t endY,
    char8_t r, char8_t g, char8_t b, float_t lineWidth);

JSY_ERROR_T JsyGDrawSprite(JSYGHandle handle, uint32_t textureId, bool8_t isFlipped, float_t xPosLeft, float_t xPosRight,
    float_t yPosTop, float_t yPosBot, float_t xTexCoord, uint32_t numSprites);

#endif // include guard