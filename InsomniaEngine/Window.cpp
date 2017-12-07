#include "Window.h"


Window::Window()
{
	//UNREFERENCED_PARAMETER(hInst);
	//
	// Register the window class
	wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"Window_1", NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	hWnd = CreateWindow(L"Window_1", L"Insomnia Engine Window",
		WS_OVERLAPPEDWINDOW, 100, 100, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

}


Window::~Window()
{
}

LRESULT WINAPI Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Window *pThis;

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		//Render();
		ValidateRect(hWnd, NULL);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND Window::getHandle()
{
	return hWnd;
}
