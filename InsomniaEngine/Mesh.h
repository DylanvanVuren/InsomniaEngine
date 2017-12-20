#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	LPD3DXMESH          g_pMesh = NULL; // Our mesh object in sysmem
	D3DMATERIAL9*       g_pMeshMaterials = NULL; // Materials for our mesh
	LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL; // Textures for our mesh
	DWORD               g_dwNumMaterials = 0L;   // Number of mesh materials

	HRESULT InitGeometry(LPDIRECT3DDEVICE9 g_pd3dDevice);

	VOID Cleanup(LPDIRECT3DDEVICE9 g_pd3dDevice, LPDIRECT3D9 g_pD3D);

	VOID Render(LPDIRECT3DDEVICE9 g_pd3dDevice);
	
	VOID SetupMatrices();

};

