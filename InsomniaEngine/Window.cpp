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
	wc.lpfnWndProc = WndProc;
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
	hWnd = CreateWindowEx(NULL,L"Window_1", L"Insomnia Engine Window 1",
		WS_OVERLAPPEDWINDOW, 100, 100, width, height,
		NULL, NULL, wc.hInstance, NULL);

	if (hWnd == NULL)
		return E_FAIL;

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) for centering
	hWnd2 = CreateWindowEx(NULL,L"Window_1", L"Insomnia Engine Window 2",
		WS_OVERLAPPEDWINDOW, 100, 100, width, height,
		NULL, NULL, wc.hInstance, NULL);

	if (hWnd2 == NULL)
		return E_FAIL;

	ShowWindow(hWnd2, SW_SHOWDEFAULT);
	UpdateWindow(hWnd2);

	return true;
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

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

HWND Window::getHandle2()
{
	return hWnd2;
}