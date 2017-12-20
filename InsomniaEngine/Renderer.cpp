#include "Renderer.h"
#include <windows.h>
#include <iostream>
#include "logger.h"
#pragma comment(lib, "winmm.lib")
#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT 800

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
//Meshes
LPD3DXMESH          g_pMesh = NULL; // Our mesh object in sysmem
D3DMATERIAL9*       g_pMeshMaterials = NULL; // Materials for our mesh
LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL; // Textures for our mesh
DWORD               g_dwNumMaterials = 0L;   // Number of mesh materials
LPDIRECT3DSWAPCHAIN9 g_swapChain_0 = NULL; // Direct3D swap chain 1 & 2 for multiple windows
LPDIRECT3DSWAPCHAIN9 g_swapChain_1 = NULL; 

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	cleanD3D();
}

bool Renderer::initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	//d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//anti ailising
	//d3dpp.MultiSampleType = D3DMULTISAMPLE_;

	// create a device class using this information and the info from the d3dpp stuc
	if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &d3ddev))) {
		MessageBox(0, TEXT("Failed to create Direct3D Device"), TEXT("Error"), MB_OK);
		return false;
	}

	// After CreateDevice, the first swap chain already exists, so just get it...
	d3ddev->GetSwapChain(0, &g_swapChain_0);

	// create second swap chain
	d3ddev->CreateAdditionalSwapChain(&d3dpp, &g_swapChain_1);

	//d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//Onderse 3 setrstate misg weg?
	//d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting

	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
	d3ddev->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	//d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	// wireframe action
	return true;
}

HRESULT Renderer::InitGeometry()
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX(L"Tiger.x", D3DXMESH_SYSTEMMEM,
		d3ddev, NULL,
		&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
		&g_pMesh)))
	{
		// If model is not in current folder, try parent folder
		if (FAILED(D3DXLoadMeshFromX(L"..\\Tiger.x", D3DXMESH_SYSTEMMEM,
			d3ddev, NULL,
			&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
			&g_pMesh)))
		{
			MessageBox(NULL, L"Could not find tiger.x", L"Meshes.exe", MB_OK);
			return E_FAIL;
		}
	}

	// We need to extract the material properties and texture names from the 
	// pD3DXMtrlBuffer
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	if (g_pMeshMaterials == NULL)
		return E_OUTOFMEMORY;
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
	if (g_pMeshTextures == NULL)
		return E_OUTOFMEMORY;

	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Copy the material
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

		g_pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			// Create the texture
			if (FAILED(D3DXCreateTextureFromFileA(d3ddev,
				d3dxMaterials[i].pTextureFilename,
				&g_pMeshTextures[i])))
			{
				// If texture is not in current folder, try parent folder
				const CHAR* strPrefix = "..\\";
				CHAR strTexture[MAX_PATH];
				strcpy_s(strTexture, MAX_PATH, strPrefix);
				strcat_s(strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename);
				// If texture is not in current folder, try parent folder
				if (FAILED(D3DXCreateTextureFromFileA(d3ddev,
					strTexture,
					&g_pMeshTextures[i])))
				{
					MessageBox(NULL, L"Could not find texture map", L"Meshes.exe", MB_OK);
				}
			}
		}
	}

	// Done with the material buffer
	pD3DXMtrlBuffer->Release();

	return S_OK;
}

void Renderer::SetupMatrices()
{
	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
	d3ddev->SetTransform(D3DTS_WORLD, &matWorld);

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(0.0f, 10.0f, -10.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	d3ddev->SetTransform(D3DTS_VIEW, &matView);

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	d3ddev->SetTransform(D3DTS_PROJECTION, &matProj);
}

//window 1
void Renderer::render_scene(HWND hwnd) {
	if (d3ddev == NULL)
		return;

	LPDIRECT3DSURFACE9 pBackBuffer = NULL;
	g_swapChain_0->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	d3ddev->SetRenderTarget(0, pBackBuffer);

	// clear params bewerken   // Clear the backbuffer and the zbuffer
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(d3ddev->BeginScene()))
	{
		// Rendering of scene objects can happen here
		// Setup the world, view, and projection matrices
		SetupMatrices();

		// Meshes are divided into subsets, one for each material. Render them in
		// a loop
		for (DWORD i = 0; i < g_dwNumMaterials; i++)
		{
			// Set the material and texture for this subset
			d3ddev->SetMaterial(&g_pMeshMaterials[i]);
			d3ddev->SetTexture(0, g_pMeshTextures[i]);

			// Draw the mesh subset
			g_pMesh->DrawSubset(i);
		}
		// End the scene
		d3ddev->EndScene();
	}

	// Present the backbuffer contents to the display
	g_swapChain_0->Present(NULL, NULL, hwnd, NULL,0);
	pBackBuffer->Release();
}

//window 2
void Renderer::render_scene2(HWND hwnd) {
	if (d3ddev == NULL)
		return;

	LPDIRECT3DSURFACE9 pBackBuffer = NULL;
	g_swapChain_1->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	d3ddev->SetRenderTarget(0, pBackBuffer);

	// clear params bewerken   // Clear the backbuffer and the zbuffer
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(d3ddev->BeginScene()))
	{
		// Rendering of scene objects can happen here
		// Setup the world, view, and projection matrices
		SetupMatrices();

		// Meshes are divided into subsets, one for each material. Render them in
		// a loop
		for (DWORD i = 0; i < g_dwNumMaterials; i++)
		{
			// Set the material and texture for this subset
			d3ddev->SetMaterial(&g_pMeshMaterials[i]);
			d3ddev->SetTexture(0, g_pMeshTextures[i]);

			// Draw the mesh subset
			g_pMesh->DrawSubset(i);
		}
		// End the scene
		d3ddev->EndScene();
	}

	// Present the backbuffer contents to the display
	g_swapChain_1->Present(NULL, NULL, hwnd, NULL,0);
	pBackBuffer->Release();
}

void Renderer::clear(D3DCOLOR color) {
	// clear the window
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void Renderer::cleanD3D() {
	if (g_pMeshMaterials != NULL)
		delete[] g_pMeshMaterials;

	if (g_pMeshTextures)
	{
		for (DWORD i = 0; i < g_dwNumMaterials; i++)
		{
			if (g_pMeshTextures[i])
				g_pMeshTextures[i]->Release();
		}
		delete[] g_pMeshTextures;
	}

	if (g_swapChain_0 != NULL)
		g_swapChain_0->Release();

	if (g_swapChain_1 != NULL)
		g_swapChain_1->Release();


	if (g_pMesh != NULL)
		g_pMesh->Release();

	if (d3ddev != NULL)
		d3ddev->Release();

	if (d3d != NULL)
		d3d->Release();
}


