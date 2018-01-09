// include the basic windows header files
#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Window.h"
#include "DxRenderer.h"

// define the screen resolution
#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT 800

// include the Direct3D Library file
//#pragma comment (lib, "d3d9.lib")
//#pragma comment (lib, "d3dx9.lib")

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Window window;
	DxRenderer renderer;

	renderer.initD3D(window.getHandle());

	// enter the main loop:
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	if (SUCCEEDED(renderer.initD3D(window.getHandle()))) {

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				renderer.SetupMatrices();
			}
		}
		
	}
	return msg.wParam;
}