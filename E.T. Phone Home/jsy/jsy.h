#ifndef _JSY_H_
#define _JSY_H_

#include "types.h"

// This is JSY virtual platform library for PC and XBOX

// Error codes for JSY functions
typedef enum JSY_ERROR_S {
    JSY_SUCCEED = 0,
    JSY_ERROR_OOM = -100,
} JSY_ERROR_S;

//================================================================================
// Simple Graphic APIs

// The Graphic handle
typedef void * JSYGHandle;

// Invalid handle
#define JSYG_INVALID_HANDLE 0

JSY_ERROR_S JsyGOpen(JSYGHandle * handle);

JSY_ERROR_S JsyGClose(JSYGHandle handle);

JSY_ERROR_S JsyGDrawCircle(JSYGHandle handle);

JSY_ERROR_S JsyGDrawLine(JSYGHandle handle);

JSY_ERROR_S JsyGDrawSprite(JSYGHandle handle);

#endif // include guard