#pragma once
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#define MAX_TEXTURES 250
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class DX_Manager
{
	LPDIRECT3D9 m_d3dObject;	// DirectX Object
	LPDIRECT3DDEVICE9 m_d3dDevice;	// DirectX Device
	LPD3DXSPRITE m_sprite;	// DirectX Interface

	struct texture_data
	{
		LPDIRECT3DTEXTURE9 texture;
		char* fileName;
		bool inUse;
	};
	
	texture_data m_textures[MAX_TEXTURES];

	void CleanUpDirectX();
public:
	DX_Manager(void);
	~DX_Manager(void);

	bool InitializeDirectX(HWND hWnd);
	bool CreateSprite();
	HRESULT BeginScene();
	void StartScene();
	void EndScene();

	void DrawSprite(LPDIRECT3DTEXTURE9 texture, RECT drawRect, D3DXVECTOR3 position);
	void DrawSprite(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR3 position);
	void DrawSprite(LPDIRECT3DTEXTURE9 texture);

	//	Getters
	LPDIRECT3DTEXTURE9 GetTexture(char* fileName);
	LPDIRECT3DDEVICE9 GetDevice() { return m_d3dDevice; }
};

extern DX_Manager g_dxManager;

