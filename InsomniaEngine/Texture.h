#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <d3d9.h>
#include <d3dx9.h>
#include <D3DX9tex.h>
#include <string>
#include <iostream> //just for cout
#include <stdio.h> //need these for the ATL conversion helper
#include <atldef.h>
#include <atlstr.h>

class Texture
{
public:
	//constructor and destructor
	Texture(void);
	~Texture(void);

	//getters
	LPDIRECT3DTEXTURE9 GetTexture(); //i did this instead of a shader resource view but it's probably wrong. //maybe it's HRESULT GetTexture(); ? or just Texture*? or IDirect3Dtexture9*?
	std::string GetName();
	int GetWidth();
	int GetHeight();

	bool Initialize(IDirect3DDevice9* device, LPCTSTR fileName);

private:
	int m_width;  // m_... means a member variable (as opposed to a local variable), it's not necessary but good practice
	int m_height;
	LPDIRECT3DTEXTURE9 m_texture;  //overload for the pointer IDirect3Dtexture9*, needed as a parameter for the D3DXCreateTextureFromFile later
	std::string m_name;
};

#endif
