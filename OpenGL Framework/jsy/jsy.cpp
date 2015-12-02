#include "jsy_internal.h"

JSY_ERROR_T JsyGInit(JSYGHandle * pHandle) {
    JsyInternalT * handle = (JsyInternalT *)malloc(sizeof(JsyInternalT));
    memset(handle,0, sizeof(JsyInternalT));
    if (!handle)
        return JSY_ERROR_OOM;

    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// Background Color
    //glClearDepth(1.0f);											// Depth Buffer Setup
    //glDepthFunc(GL_LEQUAL);										// Type Of Depth Testing
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending
    //glEnable(GL_BLEND);											// Enable Blending
    //glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
    //glEnable(GL_CULL_FACE);										// Remove Back Face

    //g_window = window;
    //g_keys = keys;

    *pHandle = (JSYGHandle *)handle;

    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGClose(JSYGHandle handle) {
    if (!handle) {
        free(handle);
    }
    return JSY_SUCCEED;
}

JSY_ERROR_T JStGLoadTexture(JSYGHandle handle, const char * fileName, uint32_t * resourceId) {
    JsyInternalT * Internal_handle = (JsyInternalT *)handle;
    Internal_handle->texture[Internal_handle->textureCnt++].soilTextureId = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    *resourceId = Internal_handle->textureCnt-1;
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGDrawBackGround(JSYGHandle handle, uint32_t resourceId, float_t width, float_t height,
    float_t yTexCoord, uint32_t numSprites) {

    JsyInternalT * Internal_handle = (JsyInternalT *)handle;

    GLfloat yTexCoordUp = yTexCoord;
    GLfloat yTexCoordDown = yTexCoord + (1.0f / numSprites);

    // Draws full background assuming window width and height are matching
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Internal_handle->texture[resourceId].soilTextureId);
    glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
    glBegin(GL_QUADS);
    {
        // Top-Left
        glTexCoord2f(0.0f, yTexCoordUp);
        glVertex3f(-width / 2.0f, -height / 2.0f, 0.0f);

        // Top-Right
        glTexCoord2f(1.0f, yTexCoordUp);
        glVertex3f(width / 2.0f, -height / 2.0f, 0.0f);

        // Bot-Right
        glTexCoord2f(1.0f, yTexCoordDown);
        glVertex3f(width / 2.0f, height / 2.0f, 0.0f);

        // Bot-Left
        glTexCoord2f(0.0f, yTexCoordDown);
        glVertex3f(-width / 2.0f, height / 2.0f, 0.0f);
    }
    glEnd();
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGDrawLine(JSYGHandle handle, float_t startX, float_t startY, float_t endX, float_t endY,
    char8_t r, char8_t g, char8_t b, float_t lineWidth) {

    JsyInternalT * Internal_handle = (JsyInternalT *)handle;

    glColor3ub(r, g, b);
    // Draw filtered lines
    glEnable(GL_LINE_SMOOTH);

    glLineWidth(lineWidth);

    glBegin(GL_LINE_STRIP);
    glVertex2f(startX, startY);
    glVertex2f(endX, endY);
    glEnd();
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGDrawSprite(JSYGHandle handle, uint32_t resourceId, bool8_t isFlipped, float_t xPosLeft, float_t xPosRight,
    float_t yPosTop, float_t yPosBot, float_t xTexCoord, uint32_t numSprites) {

    JsyInternalT * Internal_handle = (JsyInternalT *)handle;

    GLfloat xTexCoordLeft = xTexCoord;
    GLfloat xTexCoordRight = xTexCoord;

    if (isFlipped)
    {
        xTexCoordLeft += (1.0f / numSprites);
    }
    else
    {
        xTexCoordRight += (1.0f / numSprites);
    }

    // Draw texture as quad 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Internal_handle->texture[resourceId].soilTextureId);
    glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
    glBegin(GL_QUADS);
    {
        // Top-Left
        glTexCoord2f(xTexCoordLeft, 0.0f);
        glVertex3f(xPosLeft, yPosTop, 0.0f);

        // Top-Right
        glTexCoord2f(xTexCoordRight, 0.0f);
        glVertex3f(xPosRight, yPosTop, 0.0f);

        // Bot-Right
        glTexCoord2f(xTexCoordRight, 1.0f);
        glVertex3f(xPosRight, yPosBot, 0.0f);

        // Bot-Left
        glTexCoord2f(xTexCoordLeft, 1.0f);
        glVertex3f(xPosLeft, yPosBot, 0.0f);
    }
    glEnd();
    return JSY_SUCCEED;
}