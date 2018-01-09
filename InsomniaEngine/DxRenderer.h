#include <d3d9.h>
#include <d3dx9.h>
class DxRenderer
{
public:
	// global declarations
	LPDIRECT3D9 d3d;	// the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;	// the pointer to the device class

	DxRenderer();
	~DxRenderer();

	bool initD3D(HWND hWnd);    // sets up and initializes Direct3D
	void clear(D3DCOLOR color);
	void cleanD3D();    // closes Direct3D and releases memory
	void SetupMatrices();
	D3DXMATRIXA16 transformMatrix(FLOAT xTranslate, FLOAT yTranslate, FLOAT zTranslate, FLOAT yRotate);

private:


};