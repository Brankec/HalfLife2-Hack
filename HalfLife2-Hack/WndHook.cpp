#include "WndHook.h"

typedef HRESULT(_stdcall* EndScene)(LPDIRECT3DDEVICE9 pDevice);
HRESULT _stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice);
EndScene oEndScene;
HWND GetProcessWindow();
bool GetD3D9Device(void** pTable, size_t Size);

void*               d3d9Device[119];
WNDPROC             oWndProc;
HWND                window = NULL;
bool                initHook;
IDirect3DDevice9*   g_pd3dDevice;
IDirect3D9*         g_pD3D;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice)
    {
        g_pd3dDevice->Release();
        g_pd3dDevice = NULL;
    }

    if (g_pD3D)
    {
        g_pD3D->Release();
        g_pD3D = NULL;
    }
}

HRESULT __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    Hack::Draw(&window, &pDevice);

    return oEndScene(pDevice);
}

void WndHook::Hook(PVOID base)
{
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
        int fpsLimit = 60;
        int loopNumber = 0;

        if (MH_Initialize() == MH_OK)
        {
            MH_CreateHook((LPVOID)d3d9Device[42], (LPVOID)hkEndScene, (LPVOID*)&oEndScene);
            MH_EnableHook((LPVOID)d3d9Device[42]);
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);

            while (true)
            {
                if (loopNumber >= fpsLimit)
                {
                    loopNumber = 0;
                }
                loopNumber++;

                if (GetAsyncKeyState(VK_END))
                {
                    //CleanupDeviceD3D();
                    break;
                }

                Hack::Run(&fpsLimit, loopNumber);

                //looping "fpsLimit" times per second
                Sleep(1000 / fpsLimit);
            }
        }
    }
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lPAram)
{
    DWORD wndProcID;
    GetWindowThreadProcessId(handle, &wndProcID);

    if (GetCurrentProcessId() != wndProcID)
        return true;

    window = handle;
    return FALSE;
}

HWND GetProcessWindow()
{
    window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return window;
}

bool GetD3D9Device(void** pTable, size_t size)
{
    if (!pTable)
    {
        return false;
    }

    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    if (!g_pD3D)
    {
        return false;
    }

    g_pd3dDevice = NULL;

    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = false;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = GetProcessWindow();

    HRESULT deviceCreated = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);

    if (deviceCreated != S_OK)
    {
        // may fail in windowed fullscreen mode, trying again with windowed mode
        d3dpp.Windowed = !d3dpp.Windowed;

        deviceCreated = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);

        if (deviceCreated != S_OK)
        {
            g_pD3D->Release();
            return false;
        }
    }

    memcpy(pTable, *reinterpret_cast<void***>(g_pd3dDevice), size);

    g_pd3dDevice->Release();
    g_pD3D->Release();
    return true;
}