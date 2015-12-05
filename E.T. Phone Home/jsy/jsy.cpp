#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "jsy.h"


JSY_ERROR_S JsyGOpen(JSYGHandle * handle) {
    JSY_ERROR_S result = JSY_SUCCEED;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// Background Color
    glClearDepth(1.0f);											// Depth Buffer Setup
    glDepthFunc(GL_LEQUAL);										// Type Of Depth Testing
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending
    glEnable(GL_BLEND);											// Enable Blending
    glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
    glEnable(GL_CULL_FACE);										// Remove Back Face

    handle = nullptr;
    return result;
}

JSY_ERROR_S JsyGClose(JSYGHandle handle) {
    JSY_ERROR_S result = JSY_SUCCEED;


    return result;
}

JSY_ERROR_S JsyGDrawCircle(JSYGHandle handle) {
    JSY_ERROR_S result = JSY_SUCCEED;


    return result;
}

JSY_ERROR_S JsyGDrawLine(JSYGHandle handle) {
    JSY_ERROR_S result = JSY_SUCCEED;


    return result;
}

JSY_ERROR_S JsyGDrawSprite(JSYGHandle handle) {
    JSY_ERROR_S result = JSY_SUCCEED;


    return result;
}