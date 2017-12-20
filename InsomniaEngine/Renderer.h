#include <d3d9.h>
#include <d3dx9.h>
#include <list>
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
	void clear(D3DCOLOR color);
	void render_scene(HWND hwnd);
	void render_scene2(HWND hwnd);
	void cleanD3D();    // closes Direct3D and releases memory

	struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; };
	struct ENTITY { std::wstring meshPath; FLOAT xTranslate, yTranslate, zTranslate, yRotate;}; //we use this untill the entity class and resource loader are completed.
	struct TRANSFORMATION {FLOAT xTranslate, yTranslate, zTranslate, yRotate;};

	std::list<ENTITY*> entitylist;

	void SetupMatrices();
	HRESULT InitGeometry(std::wstring meshPath);
	HRESULT loadEntities();
	void drawEntity(ENTITY entity);

	D3DXMATRIXA16 transformMatrix(FLOAT xTranslate, FLOAT yTranslate, FLOAT zTranslate, FLOAT yRotate);

private:
	HWND hwnd; // Handle to the first window
};


