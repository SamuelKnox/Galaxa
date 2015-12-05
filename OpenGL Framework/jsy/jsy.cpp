#ifndef _JSYMANAGER_H
#define _JSYMANAGER_H

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#ifdef _XBOX
#else
#include <windows.h> // Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#endif


#include "jsy_internal.h"



#ifdef _XBOX

#define CONTROL_LEFTTHUMBSTICK  0
#define CONTROL_RIGHTTHUMBSTICK 1
#define CONTROL_BODY            2
#define CONTROL_BACKBUTTON      3
#define CONTROL_STARTBUTTON     4
#define CONTROL_ABUTTON         5
#define CONTROL_BBUTTON         6
#define CONTROL_XBUTTON         7
#define CONTROL_YBUTTON         8
#define CONTROL_WHITEBUTTON     9
#define CONTROL_BLACKBUTTON    10
#define CONTROL_CORDSTUB       11
#define CONTROL_GASKETS        12
#define CONTROL_MEMCARDSLOT    13
#define CONTROL_LEFTTRIGGER    14
#define CONTROL_RIGHTTRIGGER   15
#define CONTROL_DPAD           16
#define CONTROL_JEWEL          17
#define NUM_CONTROLS           18

#include <XBApp.h>
#include <XBFont.h>
#include <XBMesh.h>
#include <XBUtil.h>
#include <XBResource.h>
#include <xgraphics.h>
#include "Resource.h"

    // Members to init the XINPUT devices.
    DWORD                  m_dwNumInputDeviceTypes;
    XBGAMEPAD* m_Gamepad;
    XBGAMEPAD              m_DefaultGamepad;


#else

#ifndef		CDS_FULLSCREEN										// CDS_FULLSCREEN Is Not Defined By Some
#define		CDS_FULLSCREEN 4									// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors

static GL_Window g_window;




static void TerminateApplication(GL_Window* window)							// Terminate The Application
{
    PostMessage(window->hWnd, WM_QUIT, 0, 0);							// Send A WM_QUIT Message
}

static void ReshapeGL(int width, int height)									// Reshape The Window When It's Moved Or Resized
{
    glViewport(0, 0, (GLsizei)(width), (GLsizei)(height));				// Reset The Current Viewport
    glMatrixMode(GL_PROJECTION);										// Select The Projection Matrix
    glLoadIdentity();													// Reset The Projection Matrix

                                                                        // Define the dimensions of the Orthographic Viewing Volume
                                                                        //glOrtho(-width, height, -width, height, -800.0, 800.0);
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -500.0f, 500.0);


    glMatrixMode(GL_MODELVIEW);										// Select The Modelview Matrix
    glLoadIdentity();													// Reset The Modelview Matrix
}

static BOOL CreateWindowApp(GL_Window* window)									// This Code Creates Our OpenGL Window
{
    DWORD windowStyle = WS_OVERLAPPEDWINDOW;							// Define Our Window Style
    DWORD windowExtendedStyle = WS_EX_APPWINDOW;						// Define The Window's Extended Style

    ShowCursor(TRUE);
#pragma warning(disable : 4838)


    RECT windowRect = { 0, 0, window->init.width, window->init.height };	// Define Our Window Coordinates


                                                                        // Adjust Window, Account For Window Borders
    AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle);

    // Create The OpenGL Window
    window->hWnd = CreateWindowEx(windowExtendedStyle,					// Extended Style
        window->init.application.className,	// Class Name
        "",					                    // Window Title
        windowStyle,							// Window Style
        0, 0,								// Window X,Y Position
        windowRect.right - windowRect.left,	// Window Width
        windowRect.bottom - windowRect.top,	// Window Height
        HWND_DESKTOP,						// Desktop Is Window's Parent
        0,									// No Menu
        window->init.application.hInstance, // Pass The Window Instance
        window);

    ShowWindow(window->hWnd, SW_NORMAL);

    return true;
}

static BOOL CreateWindowGL(GL_Window* window, int colorDepth) {

    PIXELFORMATDESCRIPTOR pfd =											// pfd Tells Windows How We Want Things To Be
    {
        sizeof(PIXELFORMATDESCRIPTOR),									// Size Of This Pixel Format Descriptor
        1,																// Version Number
        PFD_DRAW_TO_WINDOW |											// Format Must Support Window
        PFD_SUPPORT_OPENGL |											// Format Must Support OpenGL
        PFD_DOUBLEBUFFER,												// Must Support Double Buffering
        PFD_TYPE_RGBA,													// Request An RGBA Format
        colorDepth,
        0, 0, 0, 0, 0, 0,												// Color Bits Ignored
        0,																// No Alpha Buffer
        0,																// Shift Bit Ignored
        0,																// No Accumulation Buffer
        0, 0, 0, 0,														// Accumulation Bits Ignored
        16,																// 16Bit Z-Buffer (Depth Buffer)  
        0,																// No Stencil Buffer
        0,																// No Auxiliary Buffer
        PFD_MAIN_PLANE,													// Main Drawing Layer
        0,																// Reserved
        0, 0, 0															// Layer Masks Ignored
    };


    if (window->hWnd == 0)												// Was Window Creation A Success?
    {
        return FALSE;													// If Not Return False
    }

    window->hDC = GetDC(window->hWnd);									// Grab A Device Context For This Window
    if (window->hDC == 0)												// Did We Get A Device Context?
    {
        // Failed
        DestroyWindow(window->hWnd);									// Destroy The Window
        window->hWnd = 0;												// Zero The Window Handle
        return FALSE;													// Return False
    }

    GLuint PixelFormat;													// Will Hold The Selected Pixel Format

    PixelFormat = ChoosePixelFormat(window->hDC, &pfd);				// Find A Compatible Pixel Format
    if (PixelFormat == 0)												// Did We Find A Compatible Format?
    {
        // Failed
        ReleaseDC(window->hWnd, window->hDC);							// Release Our Device Context
        window->hDC = 0;												// Zero The Device Context
        DestroyWindow(window->hWnd);									// Destroy The Window
        window->hWnd = 0;												// Zero The Window Handle
        return FALSE;													// Return False
    }

    if (SetPixelFormat(window->hDC, PixelFormat, &pfd) == FALSE)		// Try To Set The Pixel Format
    {
        // Failed
        ReleaseDC(window->hWnd, window->hDC);							// Release Our Device Context
        window->hDC = 0;												// Zero The Device Context
        DestroyWindow(window->hWnd);									// Destroy The Window
        window->hWnd = 0;												// Zero The Window Handle
        return FALSE;													// Return False
    }

    window->hRC = wglCreateContext(window->hDC);						// Try To Get A Rendering Context
    if (window->hRC == 0)												// Did We Get A Rendering Context?
    {
        // Failed
        ReleaseDC(window->hWnd, window->hDC);							// Release Our Device Context
        window->hDC = 0;												// Zero The Device Context
        DestroyWindow(window->hWnd);									// Destroy The Window
        window->hWnd = 0;												// Zero The Window Handle
        return FALSE;													// Return False
    }

    // Make The Rendering Context Our Current Rendering Context
    if (wglMakeCurrent(window->hDC, window->hRC) == FALSE)
    {
        // Failed
        wglDeleteContext(window->hRC);									// Delete The Rendering Context
        window->hRC = 0;												// Zero The Rendering Context
        ReleaseDC(window->hWnd, window->hDC);							// Release Our Device Context
        window->hDC = 0;												// Zero The Device Context
        DestroyWindow(window->hWnd);									// Destroy The Window
        window->hWnd = 0;												// Zero The Window Handle
        return FALSE;													// Return False
    }

    ShowWindow(window->hWnd, SW_NORMAL);								// Make The Window Visible
    window->isVisible = TRUE;											// Set isVisible To True

    ReshapeGL(window->init.width, window->init.height);				// Reshape Our GL Window

    window->lastTickCount = GetTickCount();							// Get Tick Count

    return TRUE;														// Window Creating Was A Success
                                                                        // Initialization Will Be Done In WM_CREATE
}

static BOOL DestroyWindowGL(GL_Window* window)								// Destroy The OpenGL Window & Release Resources
{
    if (window->hDC != 0)											// Does The Window Have A Device Context?
    {
        wglMakeCurrent(window->hDC, 0);							// Set The Current Active Rendering Context To Zero
        if (window->hRC != 0)										// Does The Window Have A Rendering Context?
        {
            wglDeleteContext(window->hRC);							// Release The Rendering Context
            window->hRC = 0;										// Zero The Rendering Context

        }
        ReleaseDC(window->hWnd, window->hDC);						// Release The Device Context
        window->hDC = 0;											// Zero The Device Context
    }
    ShowCursor(TRUE);
    return TRUE;														// Return True
}

static BOOL DestroyWindow(GL_Window* window)								// Destroy The OpenGL Window & Release Resources
{
    if (window->hWnd != 0)												// Does The Window Have A Handle?
    {
        DestroyWindow(window->hWnd);									// Destroy The Window
        window->hWnd = 0;												// Zero The Window Handle
    }
    return TRUE;														// Return True
}

// Process Window Message Callbacks
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Get The Window Context
    GL_Window* window = (GL_Window*)(GetWindowLong(hWnd, GWL_USERDATA));
    switch (uMsg)														// Evaluate Window Message
    {

    case WM_SYSCOMMAND:												// Intercept System Commands
    {
        switch (wParam)												// Check System Calls
        {
        case SC_SCREENSAVE:										// Screensaver Trying To Start?
        case SC_MONITORPOWER:									// Monitor Trying To Enter Powersave?
            return 0;												// Prevent From Happening
        }
        break;														// Exit
    }
    return 0;

    case WM_CREATE:													// Window Creation
    {
        CREATESTRUCT* creation = (CREATESTRUCT*)(lParam);			// Store Window Structure Pointer
        window = (GL_Window*)(creation->lpCreateParams);
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)(window));
    }
    return 0;														// Return

    case WM_CLOSE:													// Closing The Window
        TerminateApplication(window);								// Terminate The Application
        return 0;														// Return

    case WM_SIZE:													// Size Action Has Taken Place
        switch (wParam)												// Evaluate Size Action
        {
        case SIZE_MINIMIZED:									// Was Window Minimized?
            window->isVisible = FALSE;							// Set isVisible To False
            return 0;												// Return

        case SIZE_MAXIMIZED:									// Was Window Maximized?
            window->isVisible = TRUE;							// Set isVisible To True
            ReshapeGL(LOWORD(lParam), HIWORD(lParam));		// Reshape Window - LoWord=Width, HiWord=Height
            return 0;												// Return

        case SIZE_RESTORED:										// Was Window Restored?
            window->isVisible = TRUE;							// Set isVisible To True
            ReshapeGL(LOWORD(lParam), HIWORD(lParam));		// Reshape Window - LoWord=Width, HiWord=Height
            return 0;												// Return
        }
        break;															// Break
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);					// Pass Unhandled Messages To DefWindowProc
}

static BOOL RegisterWindowClass(Application* application)						// Register A Window Class For This Application.
{																		// TRUE If Successful
                                                                        // Register A Window Class
    WNDCLASSEX windowClass;												// Window Class
    ZeroMemory(&windowClass, sizeof(WNDCLASSEX));						// Make Sure Memory Is Cleared
    windowClass.cbSize = sizeof(WNDCLASSEX);					// Size Of The windowClass Structure
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraws The Window For Any Movement / Resizing
    windowClass.lpfnWndProc = (WNDPROC)(WindowProc);				// WindowProc Handles Messages
    windowClass.hInstance = application->hInstance;				// Set The Instance
    windowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);			// Class Background Brush Color
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
    windowClass.lpszClassName = application->className;				// Sets The Applications Classname
    if (RegisterClassEx(&windowClass) == 0)							// Did Registering The Class Fail?
    {
        // NOTE: Failure, Should Never Happen
        MessageBox(HWND_DESKTOP, "RegisterClassEx Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;													// Return False (Failure)
    }
    return TRUE;														// Return True (Success)
}


#endif


#ifdef _XBOX

JSY_ERROR_T JsyAppInit_XBOX(AppLoop func)
#else
JSY_ERROR_T JsyAppInit_Win(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int width, int height, AppLoop func)
#endif
{


	while (func()) {
	}
#ifdef _MY_DEBUG_
    AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;
#endif
#ifdef _XBOX
#else
    ZeroMemory(&g_window, sizeof(GL_Window));							// Make Sure Memory Is Zeroed

    // Fill Out Application Data
    g_window.init.application.className = "OpenGL";									// Application Class Name
    g_window.init.application.hInstance = hInstance;									// Application Instance
    g_window.init.width = width;						// Window Width
    g_window.init.height = height;						// Window Height


    // Register A Class For Our Window To Use
    if (RegisterWindowClass(&g_window.init.application) == FALSE)					// Did Registering A Class Fail?
    {
        // Failure
        MessageBox(HWND_DESKTOP, "Error Registering Window Class!", "Error", MB_OK | MB_ICONEXCLAMATION);
        return JSY_ERROR_INTERNAL;														// Terminate Application
    }

   BOOL test=  CreateWindowApp(&g_window);
    MSG msg;
    BOOL isMessagePumpActive = TRUE;								// Set isMessagePumpActive To TRUE
    while (isMessagePumpActive == TRUE)						// While The Message Pump Is Active
    {
        // Success Creating Window.  Check For Window Messages
        if (PeekMessage(&msg, g_window.hWnd, 0, 0, PM_REMOVE) != 0)
        {
            // Check For WM_QUIT Message
            if (msg.message != WM_QUIT)						// Is The Message A WM_QUIT Message?
            {
                DispatchMessage(&msg);						// If Not, Dispatch The Message
            }
            else											// Otherwise (If Message Is WM_QUIT)
            {
                isMessagePumpActive = FALSE;				// Terminate The Message Pump
            }
        }
        else												// If There Are No Messages
        {
            if (!func())
                TerminateApplication(&g_window);
        }
    }
#endif
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyAppClose() {
#ifdef _XBOX
#else
    DestroyWindow(&g_window);

    UnregisterClass(g_window.init.application.className, g_window.init.application.hInstance);
#endif
    return JSY_SUCCEED;
}

uint32_t JsyGetTickCount() {
#ifdef _XBOX
	return (uint32_t)GetTickCount();
#else
    return (uint32_t)GetTickCount();
#endif
}

JSY_ERROR_T JsyInputOpen(JSYInputHandle * pHandle) {
    JsyInputInternalT * handle = (JsyInputInternalT *)malloc(sizeof(JsyInputInternalT));
    memset(handle, 0, sizeof(JsyInputInternalT));
    if (!handle)
        return JSY_ERROR_OOM;

    *pHandle = (JsyInputInternalT *)handle;

		    // Initialize core peripheral port support. Note: If these parameters
    // are 0 and NULL, respectively, then the default number and types of 
    // controllers will be initialized.
    //XInitDevices( m_dwNumInputDeviceTypes, m_InputDeviceTypes );
	XInitDevices( 0, NULL );
    // Create the gamepad devices
    XBInput_CreateGamepads( &m_Gamepad );


    return JSY_SUCCEED;
}

JSY_ERROR_T JsyInputClose(JSYInputHandle handle) {
    if (!handle) {
        free(handle);
    }
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyInputGetInput(JSYInputHandle handle, JSY_INPUT_T input, float_t * value) {
#ifdef _XBOX

XBInput_GetInput( m_Gamepad );

    switch (input) {
        case JSY_INPUT_UP:
			*value = m_Gamepad[0].fY1;
			break;
        case JSY_INPUT_DOWN:
			*value = -m_Gamepad[0].fY1;
			break;
        case JSY_INPUT_LEFT:
			*value = -m_Gamepad[0].fX1;
			break;
        case JSY_INPUT_RIGHT:
			*value = m_Gamepad[0].fX1;
			break;
        case JSY_INPUT_A: 
			*value = m_Gamepad[0].bLastAnalogButtons[XINPUT_GAMEPAD_A] ? 1.0f : 0.0f;
			break;
        case JSY_INPUT_B: 
			*value = m_Gamepad[0].bLastAnalogButtons[XINPUT_GAMEPAD_B] ? 1.0f : 0.0f;
			break;
        case JSY_INPUT_START: 
			//*value = ???;
			*value = m_Gamepad[0].bLastAnalogButtons[XINPUT_GAMEPAD_B] ? 1.0f : 0.0f;
			break;
        case JSY_INPUT_BACK: 
			//*value = ???;
			break;
        default:
			*value = 0.0f;
            break;
    }


#else
    int winType;
    switch (input) {
        case JSY_INPUT_UP: winType = VK_UP;break;
        case JSY_INPUT_DOWN: winType = VK_DOWN; break;
        case JSY_INPUT_LEFT: winType = VK_LEFT; break;
        case JSY_INPUT_RIGHT:winType = VK_RIGHT; break;
        case JSY_INPUT_A: winType = VK_SPACE; break;
        case JSY_INPUT_B: winType = VK_SHIFT; break;
        case JSY_INPUT_START: winType = VK_RETURN; break;
        case JSY_INPUT_BACK: winType = VK_ESCAPE; break;
        default:
            break;
    }

    SHORT winvalue = GetKeyState(winType);
    if ((winvalue & 0x8000)) {
        *value = 1.0f;
    }
    else {
        *value = 0.0f;
    }
#endif
    return JSY_SUCCEED;
}

#ifdef _XBOX

static HRESULT InitD3D(JsyGInternalT * handle)
{
    // Create the D3D object.
    if( NULL == ( handle->g_pD3D = Direct3DCreate8( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice.
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.BackBufferWidth        = 640;
    d3dpp.BackBufferHeight       = 480;
    d3dpp.BackBufferFormat       = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount        = 1;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;

    // Create the Direct3D device.
    if( FAILED( handle->g_pD3D->CreateDevice( 0, D3DDEVTYPE_HAL, NULL,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &d3dpp, &handle->g_pd3dDevice ) ) )
        return E_FAIL;

    // Turn off culling
    handle->g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting
    handle->g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    // Turn on the zbuffer
    handle->g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	handle->g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	handle->g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	handle->g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    return S_OK;
}

static HRESULT LoadPackedResource(JsyGInternalT * handle)
{
    // Open the file to read the XPR headers
    FILE* file = fopen( "D:\\Media\\Resource.xpr", "rb" );
    if( NULL == file )
        return E_FAIL;

    // Read in and verify the XPR magic header
    XPR_HEADER xprh;
    if( fread( &xprh, sizeof(XPR_HEADER), 1, file ) != 1 )
    {
        fclose(file);
        return E_FAIL;
    }

    if( xprh.dwMagic != XPR_MAGIC_VALUE )
    {
        OutputDebugStringA( "ERROR: Invalid Xbox Packed Resource (.xpr) file" );
        fclose( file );
        return E_INVALIDARG;
    }

    // Compute memory requirements
    DWORD dwSysMemDataSize = xprh.dwHeaderSize - sizeof(XPR_HEADER);
    DWORD dwVidMemDataSize = xprh.dwTotalSize - xprh.dwHeaderSize;

    // Allocate memory
    handle->g_pResourceSysMemData = new BYTE[dwSysMemDataSize];
    handle->g_pResourceVidMemData = (BYTE*)D3D_AllocContiguousMemory( dwVidMemDataSize, D3DTEXTURE_ALIGNMENT );

    // Read in the data from the file
    if( fread( handle->g_pResourceSysMemData, dwSysMemDataSize, 1, file ) != 1 ||
        fread( handle->g_pResourceVidMemData, dwVidMemDataSize, 1, file ) != 1 )
        
    {
        delete[] handle->g_pResourceSysMemData;
        D3D_FreeContiguousMemory( handle->g_pResourceVidMemData );
        fclose( file );
        return E_FAIL;
    }

    // Done with the file
    fclose( file );
    
    // Loop over resources, calling Register()
    BYTE* pData = handle->g_pResourceSysMemData;

    for( DWORD i = 0; i < resource_NUM_RESOURCES; i++ )
    {
        // Get the resource
        LPDIRECT3DRESOURCE8 pResource = (LPDIRECT3DRESOURCE8)pData;

        // Register the resource
        pResource->Register( handle->g_pResourceVidMemData );
    
        // Advance the pointer
        switch( pResource->GetType() )
        {
            case D3DRTYPE_TEXTURE:       pData += sizeof(D3DTexture);       break;
            case D3DRTYPE_VOLUMETEXTURE: pData += sizeof(D3DVolumeTexture); break;
            case D3DRTYPE_CUBETEXTURE:   pData += sizeof(D3DCubeTexture);   break;
            case D3DRTYPE_VERTEXBUFFER:  pData += sizeof(D3DVertexBuffer);  break;
            case D3DRTYPE_INDEXBUFFER:   pData += sizeof(D3DIndexBuffer);   break;
            case D3DRTYPE_PALETTE:       pData += sizeof(D3DPalette);       break;
            default:                     return E_FAIL;
        }
    }

    return S_OK;
}

static void PostInitialize(JsyGInternalT * handle) 
{
	D3DXMATRIX Ortho2D;	
	D3DXMATRIX Identity;
	
	D3DXMatrixOrthoLH(&Ortho2D, XBOX_WIN_Width, XBOX_WIN_Height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&Identity);

	handle->g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &Ortho2D);
	handle->g_pd3dDevice->SetTransform(D3DTS_WORLD, &Identity);
	handle->g_pd3dDevice->SetTransform(D3DTS_VIEW, &Identity);
	handle->g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Load the packed resource
    LoadPackedResource(handle);

	handle->g_pd3dDevice->CreateVertexBuffer(4 * sizeof(PANELVERTEX), D3DUSAGE_WRITEONLY,
									D3DFVF_PANELVERTEX, D3DPOOL_MANAGED, &handle->g_pVertices);

	//PANELVERTEX* pVertices = NULL;
	//g_pVertices->Lock(0, 4 * sizeof(PANELVERTEX), (BYTE**)&pVertices, 0);

	////Set all the colors to white
	//pVertices[0].color = pVertices[1].color = pVertices[2].color = pVertices[3].color = 0xffffffff;

	////Set positions and texture coordinates
	//pVertices[0].x = pVertices[3].x = -PanelWidth / 2.0f;
	//pVertices[1].x = pVertices[2].x = PanelWidth / 2.0f;

	//pVertices[0].y = pVertices[1].y = PanelHeight / 2.0f;
	//pVertices[2].y = pVertices[3].y = -PanelHeight / 2.0f;

	//pVertices[0].z = pVertices[1].z = pVertices[2].z = pVertices[3].z = 1.0f;

	//pVertices[1].u = pVertices[2].u = 1.0f;
	//pVertices[0].u = pVertices[3].u = 0.0f;

	//pVertices[0].v = pVertices[1].v = 0.0f;
	//pVertices[2].v = pVertices[3].v = 1.0f;

	//g_pVertices->Unlock();
}

#endif

JSY_ERROR_T JsyGOpen(JSYGHandle * pHandle, int32_t colorDepth) {
	JsyGInternalT * handle = (JsyGInternalT *)malloc(sizeof(JsyGInternalT));
#ifdef _XBOX
	memset(handle, 0, sizeof(JsyGInternalT));
	InitD3D(handle);

	PostInitialize(handle);
#else
    
    ZeroMemory(handle, sizeof(JsyGInternalT));
    if (!handle)
        return JSY_ERROR_OOM;

#pragma warning(disable : 4996)
    handle->window = &g_window;
    CreateWindowGL(handle->window, colorDepth);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// Background Color
    glClearDepth(1.0f);											// Depth Buffer Setup
    glDepthFunc(GL_LEQUAL);										// Type Of Depth Testing
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending
    glEnable(GL_BLEND);											// Enable Blending
    glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
    glEnable(GL_CULL_FACE);										// Remove Back Face
#endif
    *pHandle = (JSYGHandle *)handle;
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGClose(JSYGHandle handle) {
    JsyGInternalT * Internal_handle = (JsyGInternalT *)handle;
#ifdef _XBOX
#else
    DestroyWindowGL(Internal_handle->window);
#endif
    if (!handle) {
        free(handle);
    }

    return JSY_SUCCEED;
}

#ifdef _XBOX
JSY_ERROR_T JStGLoadTexture(JSYGHandle handle, uint32_t fileName, uint32_t * resourceId) {
#else
JSY_ERROR_T JStGLoadTexture(JSYGHandle handle, const char * fileName, uint32_t * resourceId) {
#endif
	JsyGInternalT * Internal_handle = (JsyGInternalT *)handle;
#ifdef _XBOX

    // Get access to the texture
    Internal_handle->g_pTexture[Internal_handle->textureCnt++] = (LPDIRECT3DTEXTURE8)&Internal_handle->g_pResourceSysMemData[ fileName ];



#else
    Internal_handle->texture[Internal_handle->textureCnt++].soilTextureId = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
#endif
    *resourceId = Internal_handle->textureCnt-1;
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGDrawBackGround(JSYGHandle handle, uint32_t resourceId, float_t width, float_t height,
    float_t yTexCoord, uint32_t numSprites) {

    JsyGInternalT * Internal_handle = (JsyGInternalT *)handle;
#ifdef _XBOX
	float_t ratio = XBOX_WIN_Height / height;
	width = width * ratio;
	height = height * ratio;
	/*g_pd3dDevice->CreateVertexBuffer(4 * sizeof(PANELVERTEX), D3DUSAGE_WRITEONLY,
									D3DFVF_PANELVERTEX, D3DPOOL_MANAGED, &g_pVertices);*/
	PANELVERTEX* pVertices = NULL;
	Internal_handle->g_pVertices->Lock(0, 4 * sizeof(PANELVERTEX), (BYTE**)&pVertices, 0);

	//Set all the colors to white
	pVertices[0].color = pVertices[1].color = pVertices[2].color = pVertices[3].color = 0xffffffff;

	//Set positions and texture coordinates
	float_t yTexCoordUp = 1-yTexCoord;
    float_t yTexCoordDown = 1-yTexCoord + (1.0f / numSprites);

	// 0 - xleft, ytop
	// 1 - xright, ytop
	// 2 - xright, ybot
	// 3 - xleft, ybot

	// Left
	pVertices[0].u = pVertices[3].u = 0.0f;
	pVertices[0].x = pVertices[3].x = -width / 2.0f;

	// Right
	pVertices[1].u = pVertices[2].u = 1.0f;
	pVertices[1].x = pVertices[2].x = width / 2.0f;

	// Bot
	pVertices[0].v = pVertices[1].v = yTexCoordDown;
	pVertices[0].y = pVertices[1].y = -height / 2.0f;

	// Top 
	pVertices[2].v = pVertices[3].v = yTexCoordUp;
	pVertices[2].y = pVertices[3].y = height / 2.0f;

	/*pVertices[0].x = pVertices[3].x = xPosLeft;
	pVertices[1].x = pVertices[2].x = xPosRight;

	pVertices[0].y = pVertices[1].y = yPosTop;
	pVertices[2].y = pVertices[3].y = yPosBot;*/

	pVertices[0].z = pVertices[1].z = pVertices[2].z = pVertices[3].z = 1.0f;

	Internal_handle->g_pVertices->Unlock();

	Internal_handle->g_pd3dDevice->SetTexture(0, Internal_handle->g_pTexture[resourceId]);
	Internal_handle->g_pd3dDevice->SetVertexShader(D3DFVF_PANELVERTEX);
	Internal_handle->g_pd3dDevice->SetStreamSource(0, Internal_handle->g_pVertices, sizeof(PANELVERTEX));
	Internal_handle->g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);

#else
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
#endif
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGClear(JSYGHandle handle) {
    // Clear the window
	
#ifdef _XBOX
	JsyGInternalT * Internal_handle = (JsyGInternalT *)handle;
	Internal_handle->g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
    
    // Begin the scene
    Internal_handle->g_pd3dDevice->BeginScene();
#else
    glClear(GL_COLOR_BUFFER_BIT);
    // Set the modelview matrix to be the identity matrix
    glLoadIdentity()
#endif
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGSwapBuffer(JSYGHandle handle) {
#ifdef _XBOX
	JsyGInternalT * Internal_handle = (JsyGInternalT *)handle;
	    // End the scene
    Internal_handle->g_pd3dDevice->EndScene();

	// Present the backbuffer contents to the display
    Internal_handle->g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
#else
    SwapBuffers(g_window.hDC);					// Swap Buffers (Double Buffering)
#endif
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGDrawLine(JSYGHandle handle, float_t startX, float_t startY, float_t endX, float_t endY,
    char8_t r, char8_t g, char8_t b, float_t lineWidth) {

    JsyGInternalT * Internal_handle = (JsyGInternalT *)handle;
#ifdef _XBOX
#else
    glColor3ub(r, g, b);
    // Draw filtered lines
    glEnable(GL_LINE_SMOOTH);

    glLineWidth(lineWidth);

    glBegin(GL_LINE_STRIP);
    glVertex2f(startX, startY);
    glVertex2f(endX, endY);
    glEnd();
#endif
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyGDrawSprite(JSYGHandle handle, uint32_t resourceId, bool8_t isFlipped, float_t xPosLeft, float_t xPosRight,
    float_t yPosTop, float_t yPosBot, float_t xTexCoord, uint32_t numSprites) {

    JsyGInternalT * Internal_handle = (JsyGInternalT *)handle;
#ifdef _XBOX

	/*g_pd3dDevice->CreateVertexBuffer(4 * sizeof(PANELVERTEX), D3DUSAGE_WRITEONLY,
									D3DFVF_PANELVERTEX, D3DPOOL_MANAGED, &g_pVertices);*/
	PANELVERTEX* pVertices = NULL;
	Internal_handle->g_pVertices->Lock(0, 4 * sizeof(PANELVERTEX), (BYTE**)&pVertices, 0);

	//Set all the colors to white
	pVertices[0].color = pVertices[1].color = pVertices[2].color = pVertices[3].color = 0xffffffff;

	//Set positions and texture coordinates
	xPosLeft *= RATIO;
	xPosRight *= RATIO;
	yPosTop *= RATIO;
	yPosBot *= RATIO;


	float_t xTexCoordLeft = xTexCoord;
    float_t xTexCoordRight = xTexCoord;

    if (isFlipped)
    {
        xTexCoordLeft += (1.0f / numSprites);
    }
    else
    {
        xTexCoordRight += (1.0f / numSprites);
    }

	// Left
	pVertices[0].u = pVertices[3].u = xTexCoordLeft;
	pVertices[0].x = pVertices[3].x = xPosLeft;

	// Right
	pVertices[1].u = pVertices[2].u = xTexCoordRight;
	pVertices[1].x = pVertices[2].x = xPosRight;

	// Bot
	pVertices[0].v = pVertices[1].v = 1.0f;
	pVertices[2].y = pVertices[3].y = yPosBot;

	// Top 
	pVertices[2].v = pVertices[3].v = 0.0f;
	pVertices[0].y = pVertices[1].y = yPosTop;


	pVertices[0].z = pVertices[1].z = pVertices[2].z = pVertices[3].z = 1.0f;

	Internal_handle->g_pVertices->Unlock();

	Internal_handle->g_pd3dDevice->SetTexture(0, Internal_handle->g_pTexture[resourceId]);
	Internal_handle->g_pd3dDevice->SetVertexShader(D3DFVF_PANELVERTEX);
	Internal_handle->g_pd3dDevice->SetStreamSource(0, Internal_handle->g_pVertices, sizeof(PANELVERTEX));
	Internal_handle->g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);


#else
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
#endif
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyAudioOpen(JSYAudioHandle * pHandle) {

    JsyAudioInternalT * handle = (JsyAudioInternalT *)malloc(sizeof(JsyAudioInternalT));
#ifdef _XBOX
#else
    ZeroMemory(handle, sizeof(JsyAudioInternalT));
    if (!handle)
        return JSY_ERROR_OOM;

    // Create the FMOD sound obj
    FMOD_RESULT res = FMOD::System_Create(&handle->soundSystem);
    if (res != FMOD_OK) {
        printf("Sound System init failed: %d", res);
    }

    // Init the FMOD sound obj
    handle->soundSystem->init(32, FMOD_INIT_NORMAL, NULL);

    memset(&handle->channels, 0, sizeof(FMOD::Channel*) * 32);

    *pHandle = (JSYAudioHandle *)handle;
#endif
    return JSY_SUCCEED;
}

JSY_ERROR_T JsyAudioClose(JSYAudioHandle handle) {
    JsyAudioInternalT * localhandle = (JsyAudioInternalT *)handle;
#ifdef _XBOX
#else
    SoundNode_t* currentSoundNode = localhandle->listSounds;
    while (currentSoundNode != NULL) {
        SoundNode_t* tmp = currentSoundNode->nextSound;
        free(currentSoundNode);
        currentSoundNode = tmp;
    }
    localhandle->listSounds = NULL;

    if (!localhandle) {
        free(localhandle);
    }
#endif
    return JSY_SUCCEED;
}

uint32_t JsyAudioLoad(JSYAudioHandle handle, const char8_t * fileName) {
    JsyAudioInternalT * localhandle = (JsyAudioInternalT *)handle;
#ifdef _XBOX
	return 0;
#else
    // Load the sound file into the SoundManager
    SoundNode_t * newNode = (SoundNode_t*)malloc(sizeof(SoundNode_t));
    // Put into the internal list
    newNode->id = ++(localhandle->id_cnt);
    newNode->nextSound = NULL;
    if (localhandle->listSounds == NULL) {
        localhandle->listSounds = newNode;
    }
    if (localhandle->tailSounds != NULL) {
        localhandle->tailSounds->nextSound = newNode;
    }
    localhandle->tailSounds = newNode;

    // Load sound file
    FMOD_RESULT res = localhandle->soundSystem->createSound(fileName, FMOD_DEFAULT, 0, &(newNode->sound));
    if (res != FMOD_OK) {
        printf("Sound System load failed: %d", res);
    }
    // Init it
    newNode->sound->setMode(FMOD_LOOP_OFF);

    return newNode->id;
#endif
}
#ifdef _XBOX
#else
// This function is for fixing FMOD bug
static void resumeChannel(JsyAudioInternalT * localhandle) {
    // Find all channel and modify their priority, the one that is curreny playing has high priority
    for (int i = 0; i < 32; i++) {
        if (localhandle->channels[i] != NULL) {
            bool isPlaying = false;
            localhandle->channels[i]->isPlaying(&isPlaying);
            if (isPlaying) {
                localhandle->channels[i]->setPriority(0);
            }
            else {
                localhandle->channels[i]->setPriority(256);
                localhandle->channels[i]->stop();
            }
        }
    }
}

// This function is for fixing FMOD bug
static void putChannel(JsyAudioInternalT * localhandle, FMOD::Channel * channel) {
    int index = 0;
    int low_priority = 0;
    channel->setPriority(0);
    // Find empty or low priority, modify the priority, and put the new channel handle into our array
    for (int i = 0; i < 32; i++) {
        if (localhandle->channels[i] == NULL) {
            index = i;
            break;
        }
        else {
            bool isPlaying = false;
            localhandle->channels[i]->isPlaying(&isPlaying);
            if (isPlaying) {
                localhandle->channels[i]->setPriority(0);
            }
            else {
                index = i;
                break;
            }
        }
    }
    localhandle->channels[index] = channel;
}
#endif

JSY_ERROR_T JsyAudioPlaySound(JSYAudioHandle handle, uint32_t resourceId) {
    JsyAudioInternalT * localhandle = (JsyAudioInternalT *)handle;
#ifdef _XBOX
#else
    SoundNode_t* currentSoundNode = localhandle->listSounds;
    if (currentSoundNode == NULL) return JSY_SUCCEED;
    // Loop through the list until we find the sound resource
    while (currentSoundNode->id != resourceId) {
        currentSoundNode = currentSoundNode->nextSound;
        if (currentSoundNode == NULL)
            return JSY_SUCCEED;
    }

    if (currentSoundNode->id == resourceId) {
        // Fixing FMOD bug, all channels will stop if it randomly pick a low prioirty channel
        // Use resumeChannel to set higher priority for the channel that is playing
        resumeChannel(localhandle);
        FMOD::Channel * channel = NULL;
        localhandle->soundSystem->playSound(currentSoundNode->sound, 0, false, &channel);
        // An old channel handle will become invalid if the sound system pick a channel, it makes the old channel handle invalid.
        // So we need to store the new channel handle even the channel is included in our list
        putChannel(localhandle, channel);
    }
#endif
    return JSY_SUCCEED;
}

#endif