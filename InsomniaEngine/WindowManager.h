#pragma once

#include "Window.h"
#include <list>

class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	void MakeWindow(std::string name);

	HWND getHandle();

private:
	std::list<Window> windows;
};

