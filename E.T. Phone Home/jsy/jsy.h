#ifndef _JSY_H_
#define _JSY_H_

#include "types.h"

// This is JSY virtual platform library for PC and XBOX

// Error codes for bitstream functions
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

JSY_ERROR_S JsyGInit();

JSY_ERROR_S JsyGClose();

JSY_ERROR_S JsyGDrawCircle();

JSY_ERROR_S JsyGDrawLine();

JSY_ERROR_S JsyGDrawSprite();

#endif // include guard