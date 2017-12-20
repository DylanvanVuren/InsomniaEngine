//i'm following a book and a tutorial 
//and trying to implement it but without a shader

//---------------------------------------------------------------------------------------------------------
/* INFO:

Direct3D uses a texture coordinate system that consists of a u-axis that
runs horizontally and a v-axis that runs vertically. A pair of u, v coordinates
identifies an element on the texture called a texel.


(0,0)_ _ __ _ __(1,0) +U
|
|  ()_()
|  (^.^)_*
|  (_____)
|          .
(0,1) +V	        (1,1)

For each 3D triangle, we want to define a corresponding (2d) triangle on the texture that is
to be mapped to the 3D triangle.

*/
//---------------------------------------------------------------------------------------------------------

#include "Texture.h"


//constructor
Texture::Texture(void)
{
	m_texture = 0;
	m_width = 0;
	m_height = 0;
}

//destructor
Texture::~Texture(void)
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}

	m_name.clear(); //maybe not necessary?
}


//this is a wrapper for all that needs to be done to initialize a texture
bool Texture::Initialize(IDirect3DDevice9* device, LPCTSTR fileName)
{
	HRESULT result;

	//getting a name based on what the file is called
	m_name = CT2A(fileName); // CT2A is converting CHAR to std::string, it's an ATL(Active Template Library) conversion helper "CX2Y", where X is a current state and Y a state you want to convert to
	int pos = (int)m_name.find_last_of("/"); //find the last forward slash
	if (pos >= 0)
	{
		m_name = m_name.substr(pos + 1, m_name.length()); //if it has a root directory - remove it
	}
	m_name = m_name.substr(0, m_name.find_last_of(".")); //remove the extention. UPD: i think it needs the extention after all

														 //loading the texture from an image file	
	result = D3DXCreateTextureFromFile(device, fileName, &m_texture);
	if (FAILED(result))
	{
		return false;
		std::cout << "D3DXCreateTextureFromFile failed";
	}

	//get raw data (width and height)
	D3DSURFACE_DESC desc; //this is a struct, the type is a member of the D3DRESOURCETYPE enumerated type, identifying this resource as a surface.
	m_texture->GetLevelDesc(0, &desc);

	m_width = desc.Width;
	m_height = desc.Height;


	return true;
}

LPDIRECT3DTEXTURE9 Texture::GetTexture()
{
	return m_texture;
}

std::string Texture::GetName()
{
	return m_name;
}


int Texture::GetHeight()
{
	return m_height;
}


int Texture::GetWidth()
{
	return m_width;
}
