#ifdef OPENGLSTUFF_CPP
#define extern 
#endif

void endOpenGLDrawing();
void startOpenGLDrawing();
void initOpenGLDrawing( GL_Window *window, float backRed, float backGreen, float backBlue);

extern GL_Window*	g_window;

#undef extern