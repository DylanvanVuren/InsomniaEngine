
#include "Renderer.h"

#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT 800

Renderer::Renderer()
{
	
}

Renderer::~Renderer()
{
	
}

void Renderer::initD3D(HWND hWnd)
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

	// create a device class using this information and the info from the d3dpp stuc

	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	init_graphics();    // call the function to initialize the triangle

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting

	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
}

void Renderer::render_frame(void) 
{
	// clear the window
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

							 // do 3D rendering on the back buffer here
							 // select which vertex format we are using
	d3ddev->SetFVF(CUSTOMFVF);


	// SET UP THE PIPELINE

	D3DXMATRIX matRotateY;    // a matrix to store the rotation information
	D3DXMATRIX matRotateX;


	static float index = 0.0f; index += 0.02f;    // an ever-increasing float value

												  // build a matrix to rotate the model based on the increasing float value
	D3DXMatrixRotationY(&matRotateY, index);
	D3DXMatrixRotationX(&matRotateX, index);

	// tell Direct3D about our matrix
	d3ddev->SetTransform(D3DTS_WORLD, &(matRotateX * matRotateY));

	D3DXMATRIX matView;    // the view transform matrix

	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 0.0f, 50.0f),    // the camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),    // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction

	d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

	D3DXMATRIX matProjection;     // the projection transform matrix

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(45),    // the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
		1.0f,    // the near view-plane
		100.0f);    // the far view-plane

	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

															   // select the vertex buffer to display
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

	// copy the vertex buffer to the back buffer
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	d3ddev->EndScene();    // ends the 3D scene

						   // select the vertex and index buffers to use
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->SetIndices(i_buffer);

	// draw the cube
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

	d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}

void Renderer::cleanD3D(void)
{
	v_buffer->Release();    // close and release the vertex buffer
	d3ddev->Release();    // close and release the 3D device
	d3d->Release();    // close and release Direct3D
}

void Renderer::init_graphics(void)
{
	// create the vertices using the CUSTOMVERTEX struct
	CUSTOMVERTEX vertices[] =
	{
		{ -6.0f, 6.0f, -6.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ 6.0f, 6.0f, -6.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ -6.0f, -6.0f, -6.0f, D3DCOLOR_XRGB(255, 0, 0), },
		{ 6.0f, -6.0f, -6.0f, D3DCOLOR_XRGB(0, 255, 255), },
		{ -6.0f, 6.0f, 6.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ 6.0f, 6.0f, 6.0f, D3DCOLOR_XRGB(255, 0, 0), },
		{ -6.0f, -6.0f, 6.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ 6.0f, -6.0f, 6.0f, D3DCOLOR_XRGB(0, 255, 255), },
	};

	// create a vertex buffer interface called v_buffer
	d3ddev->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);

	VOID* pVoid;    // a void pointer

					// lock v_buffer and load the vertices into it
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();

	// create the indices using an int array
	short indices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};

	// create an index buffer interface called i_buffer
	d3ddev->CreateIndexBuffer(36 * sizeof(short),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&i_buffer,
		NULL);

	// lock i_buffer and load the indices into it
	i_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	i_buffer->Unlock();
}