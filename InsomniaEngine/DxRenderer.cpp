#include "DxRenderer.h"



DxRenderer::DxRenderer()
{
}

DxRenderer::~DxRenderer()
{
	cleanD3D();
}

bool DxRenderer::initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// create a device class using this information and the info from the d3dpp stuc
	if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &d3ddev))) {
		MessageBox(0, TEXT("Failed to create Direct3D Device"), TEXT("Error"), MB_OK);
		return false;
	}
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
	d3ddev->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	return true;
}

void DxRenderer::clear(D3DCOLOR color) {
	// clear the window
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void DxRenderer::cleanD3D() {
	if (d3ddev != NULL){
		d3ddev->Release();
		d3ddev = NULL;
	}

	if (d3d != NULL){
		d3d->Release();
		d3d = NULL;
	}
}

D3DXMATRIXA16 DxRenderer::transformMatrix(FLOAT xTranslate, FLOAT yTranslate, FLOAT zTranslate, FLOAT yRotate) {
	// Set up world matrix
	D3DXMATRIXA16 matWorld, matTranslate, matScale, matRotate, matYrotation;
	D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matTranslate, xTranslate, yTranslate, zTranslate);
	D3DXMatrixRotationY(&matRotate, yRotate);
	//rotation als je dat leuk vind..
	D3DXMatrixRotationY(&matYrotation, timeGetTime() / 1000.0f);

	matWorld = matScale * matTranslate * matRotate * matYrotation;
	d3ddev->SetTransform(D3DTS_WORLD, &matWorld);

	return(matWorld);
}


void DxRenderer::SetupMatrices()
{
	transformMatrix(0.0, 0.0, 0.0, 0.0);
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(0.0f, 15.0f, -30.0f);
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