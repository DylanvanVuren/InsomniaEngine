#include "Window.h"

Window::Window()
{
	Init(500, 500);
}


Window::~Window()
{
}

bool Window::Init(int width, int height) {

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;  // Register the callback function for the window procedure
	wc.hInstance = hInstance;
	//wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION));
	//wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("Window_1", "Insomnia Engine Window");
	wc.hIconSm = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(0, TEXT("Failure. Window was not made."), NULL, 0);
		return false;
	}

	//GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) for centering
	hWnd = CreateWindow(L"Window_1", L"Insomnia Engine Window",
		WS_OVERLAPPEDWINDOW, 100, 100, width, height,
		NULL, NULL, wc.hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	return true;
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	/*Window *pThis;

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

	}*/
	//Renderer r;
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return 0;
	}
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


HWND Window::getHandle()
{
	return hWnd;
}