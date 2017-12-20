// include the basic windows header files
#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Window.h"
#include "Texture.h"  //just for a test
#include "ResourceManager.h" //just for a test
#include "Renderer.h" //just for a test

// define the screen resolution
#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT 800

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer	
LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;    // the pointer to the index buffer
LPDIRECT3DTEXTURE9      g_pTexture = NULL; // Our texture


											// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);    // closes Direct3D and releases memory
void init_graphics(void);    // 3D declarations

//struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; }
struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; FLOAT u, v;}; //u,v are texture coordinates

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // the WindowProc function prototype

																					// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	
	Window window;

	// set up and initialize Direct3D
	initD3D(window.getHandle());

	// enter the main loop:
	MSG msg;

	/*Sasha tests the ResourceManager -----------*/
	//private: ResourceManager m_resourceManager; //this will go in the Kernel header, when WinMain becomes a Kernel
	ResourceManager m_resourceManager = new ResourceManager();
	m_resourceManager = ResourceManager::GetInstance();


	m_resourceManager.LoadTexture(IDirect3DDevice9* device, char* fileName);
	/*end of tests of the ResourceManager -----------*/

	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;
		render_frame();
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_KEYDOWN:
		if (wParam == 0x57) // W-key pressed
		{
			MessageBox(0, L"W Key pressed", L"Key Pressed", MB_OK);
		}

		if (wParam == 0x53)	//S-key pressed
		{
			MessageBox(0, L"S Key pressed", L"Key Pressed", MB_OK);
		}

		if (wParam == 0x41)	//A-key pressed
		{
			MessageBox(0, L"A Key pressed", L"Key Pressed", MB_OK);
		}

		if (wParam == 0x44)	//D-key pressed
		{
			MessageBox(0, L"D Key pressed", L"Key Pressed", MB_OK);
		}


		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
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

// this is the function used to render a single frame
void render_frame(void)
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


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	v_buffer->Release();    // close and release the vertex buffer
	d3ddev->Release();    // close and release the 3D device
	d3d->Release();    // close and release Direct3D
}

// this is the function that puts the 3D models into video RAM
void init_graphics(void)
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