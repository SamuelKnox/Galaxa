
#include "jsy/jsy.h"

#include "game.h"
#include "gamedefs.h"


bool inited = false;
uint32_t lastTickCount;
bool Initialize()					// Any OpenGL Initialization Goes Here
{
    CGame::CreateInstance();
    CGame::GetInstance()->init();
    lastTickCount = JsyGetTickCount();
    return true;
}

bool gameLoop() {
    if (!inited) {
        Initialize();
        inited = true;
    }
    else {
        uint32_t tickCount = JsyGetTickCount();				// Get The Tick Count
        CGame::GetInstance()->UpdateFrame(tickCount - lastTickCount);	// Update The Counter
        lastTickCount = tickCount;			// Set Last Count To Current Count
        CGame::GetInstance()->DrawScene();			// Draw Our Scene
    }

    return !CGame::GetInstance()->GetQuit();
}

#ifndef _XBOX_
// Program Entry (WinMain)
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    JsyAppInit_Win(hInstance, hPrevInstance, lpCmdLine, nCmdShow, BG_WIDTH, BG_HEIGHT, gameLoop);

    CGame::GetInstance()->shutdown();										// User Defined DeInitialization
    CGame::GetInstance()->DestroyGame();

    JsyAppClose();

	return 0;
}
#endif
