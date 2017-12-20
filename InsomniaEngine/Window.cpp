#include "Window.h"



Window::Window()
{

	//UNREFERENCED_PARAMETER(hInst);
	//
	// Register the window class
	wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L,
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

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window *pThis;

	if (msg == WM_NCCREATE)
	{
		
		pThis = static_cast<Window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
		{
			if (GetLastError() != 0)
				return FALSE;
		}
	}
	else
	{
		pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pThis)
	{
		// use pThis->member as needed...
	}

	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_KEYDOWN:
		if (wParam == 0x57) // W-key pressed
		{
			MessageBox(0, L"W Key pressed", L"Key Pressed", MB_OK);
		}

		if (wParam == 0x53)	//S-key pressed
		{
			MessageBox(0, L"S Key pressed", L"Key Pressed", MB_OK);
		}

		if (wParam == 0x41)	//A-key pressed
		{
			MessageBox(0, L"A Key pressed", L"Key Pressed", MB_OK);
		}

		if (wParam == 0x44)	//D-key pressed
		{
			MessageBox(0, L"D Key pressed", L"Key Pressed", MB_OK);
		}


		break;

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

HWND Window::getHandle()
{
	return hWnd;
}
