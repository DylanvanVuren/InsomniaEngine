#pragma once

#include <Windows.h>

class Window
{
public:

	Window();
	~Window();

	static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	

	HWND getHandle();

private:

	WNDCLASSEX wc;
	
	HWND hWnd;
};

