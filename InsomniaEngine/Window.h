#pragma once

#include <Windows.h>

class Window
{
public:

	Window();
	~Window();

	HWND getHandle();

private:

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	WNDCLASSEX wc;
	
	HWND hWnd;
};

