#include <d3d9.h>
#include <d3dx9.h>

#define WIDTH 4
#define HEIGHT 3

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
	void initD3D(HWND hWnd);    // sets up and initializes Direct3D
	void render_frame(void);    // renders a single frame
	void cleanD3D(void);    // closes Direct3D and releases memory
	void init_graphics(void);    // 3D declarations
	void InitCamera(void);

	LPDIRECT3DDEVICE9 getDevice() { return d3ddev; };

	struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; };
	#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

private: 
	


};
