#pragma once

#include <Windows.h>

class Window
{
public:

	Window();
	~Window();

	HWND getHandle();
	bool Init(int width, int height);

private:

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	WNDCLASSEX wc;
	HINSTANCE hInstance;
	HWND hWnd;
};

