#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Window.h"
#include "DxRenderer.h"

class Kernel
{
public:
	Kernel();
	~Kernel();

	bool Init();
	void Draw();
private:
	Window* window;
	DxRenderer* renderer;
};