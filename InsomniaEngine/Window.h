#pragma once

#include <Windows.h>

class Window
{
public:

	Window();
	~Window();

	HWND getHandle();
	HWND getHandle2();
	bool Init(int width, int height);
	HWND hWnd;
	HWND hWnd2;

private:

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	WNDCLASSEX wc;
	HINSTANCE hInstance;
};

