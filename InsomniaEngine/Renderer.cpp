#include "Renderer.h"

#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT 800


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
	d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
	d3dpp.BackBufferWidth = SCREEN_WIDTH;    // set the width of the buffer
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;    // set the height of the buffer
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//anti ailising
	//d3dpp.MultiSampleType = D3DMULTISAMPLE_;

	// create a device class using this information and the info from the d3dpp stuc

	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//Onderse 3 setrstate misg weg?
	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting

	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer

	d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	// wireframe action

	if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &d3ddev))) {
		MessageBox(0, TEXT("Failed to create Direct3D Device"), TEXT("Error"), MB_OK);
		return false;
	}

	return true;
}

void Renderer::render_scene() {
	if (d3ddev == NULL)
		return;

	// Clear the backbuffer to a blue color
	clear(D3DCOLOR_XRGB(0, 0, 255));

	// Begin the scene
	if (SUCCEEDED(d3ddev->BeginScene()))
	{
		// Rendering of scene objects can happen here

		// End the scene
		d3ddev->EndScene();
	}

	// Present the backbuffer contents to the display
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Renderer::clear(D3DCOLOR color) {
	// clear the window
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void Renderer::cleanD3D() {
	if (d3ddev != NULL)
		d3ddev->Release();

	if (d3d != NULL)
		d3d->Release();
}