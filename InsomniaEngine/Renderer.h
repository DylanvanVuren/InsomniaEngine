#include <d3d9.h>
#include <d3dx9.h>

class Renderer
{
public:

	Renderer();
	~Renderer();

	// global declarations
	LPDIRECT3D9 d3d;	// the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;	// the pointer to the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;	// the pointer to the vertex buffer	
	LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;	// the pointer to the index buffer
	LPDIRECT3DTEXTURE9 g_pTexture = NULL;	// Our texture

											// function prototypes
	bool initD3D(HWND hWnd);    // sets up and initializes Direct3D
	void render_frame(void);    // renders a single frame
	void clear(D3DCOLOR color);
	void render_scene();
	void cleanD3D(void);    // closes Direct3D and releases memory
	void init_graphics(void);    // 3D declarations
	struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; };
private:
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};


