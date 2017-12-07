#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Window.h"
#include <tchar.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class Renderer
{
public: //declaring publics
	void cleanup(); //cleanup the mess
	void renderObject(); //
	void renderFrame();//render 1 frame

	//direct3d dingen
	void initD3D(HWND hWnd);    // sets up and initializes Direct3D
	void render_frame(void);    // renders a single frame
	void cleanD3D(void);		// closes Direct3D and releases memory
	void init_graphics(void);   // 3D declarations


private: //declaring privates
	Renderer(Window window);


};