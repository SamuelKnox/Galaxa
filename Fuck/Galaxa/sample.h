#ifndef _SAMPLE_H
#define _SAMPLE_H

#include "jsy/jsy.h"

//-----------------------------------------------------------------------------
// Name: class CGamepadMesh
// Desc: The gamepad mesh. This is overridden from the base class so that we can
//       provide a custom RenderCallback() function.
//-----------------------------------------------------------------------------
class CGamepadMesh : public CXBMesh
{
public:
    BOOL    RenderCallback( DWORD dwSubset, XBMESH_SUBSET* pSubset, DWORD dwFlags );
};
//-----------------------------------------------------------------------------
// Name: class CXBoxSample
// Desc: Application class. The base class provides just about all the
//       functionality we want, so we're just supplying stubs to interface with
//       the non-C++ functions of the app.
//-----------------------------------------------------------------------------
class CXBoxSample : public CXBApplication
{
    // Valid app states
    enum APPSTATE 
    { 
        APPSTATE_CONTROLTEST=0, 
        APPSTATE_VIBRATIONTEST,
        APPSTATE_DEADZONECALIBRATION,
        APPSTATE_BUTTONQUANTIZATION,
        APPSTATE_MEMORYUNITDETECTION,
        APPSTATE_MAX,
    };

    // General application members
    APPSTATE           m_AppState;         // State of the app
    CXBPackedResource  m_xprResource;      // Packed resources for the app
    CXBFont            m_Font16;           // 16-point font class
    CXBFont            m_Font12;           // 12-point font class

    // Active gamepad
    DWORD              m_dwNumInsertedGamepads;
    XBGAMEPAD*         m_pGamepad;

    // Geometry
    CGamepadMesh       m_GamepadMesh;      // Geometry for the US gamepad
    CGamepadMesh       m_GamepadSMesh;     // Geometry for the Japan gamepad
    CGamepadMesh*      m_pGamepadMesh;     // Geometry for the active gamepad

    // Vibration motor values
    FLOAT              m_fLeftMotorSpeed;
    FLOAT              m_fRightMotorSpeed;

    // Deadzone calibration page
    FLOAT              m_fDeadZone;

    // Control quantization page
    BYTE*              m_pQuantizedThumbStickValues;
    BYTE*              m_pQuantizedButtonValues;

    // Internal members
    VOID    ShowTexture( LPDIRECT3DTEXTURE8 pTexture );
    HRESULT DrawBox( FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2,
                     DWORD dwFillColor, DWORD dwOutlineColor );
    HRESULT RenderInsertRemoveControllerPage();
    HRESULT RenderControlTestPage();
    HRESULT RenderVibrationTestPage();
    HRESULT RenderDeadZoneCalibrationPage();
    HRESULT RenderButtonQuantizationPage();

protected:
    HRESULT Initialize();
    HRESULT FrameMove();
    HRESULT Render();

public:
    CXBoxSample();
};

#endif