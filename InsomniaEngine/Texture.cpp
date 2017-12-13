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
		|
   (0,1) +V

   For each 3D triangle, we want to define a corresponding (2d) triangle on the texture that is
   to be mapped to the 3D triangle

*/
//---------------------------------------------------------------------------------------------------------

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

	//maybe create an empty texture first?
	//bool Create(int width, int height);  //maybe not needed?

	//getters
	Texture::Texture GetTexture(); //i did this instead of a shader resource view but it's probably wrong. 
	//maybe it's HRESULT GetTexture(); ?
	std::string GetName();
	int GetWidth();
	int GetHeight();

private:

	int m_width;  // m_ means a member variable (as opposed to a local variable), it's not necessary but good practice
	int m_height;

	LPDIRECT3DTEXTURE9 m_pTexture;  //overload for the pointer IDirect3Dtexture9*, needed as a parameter for the D3DXCreateTextureFromFile later
	HRESULT m_texture; //HRESULT is type a long, but it's actually a call by result, so in this case it'll return a Texture

	std::string m_name;
	int m_width;
	int m_height;

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
		int pos = m_name.find_last_of("/"); //find the last forward slash
		if (pos >= 0)
		{
		m_name = m_name.substr(pos + 1, m_name.length()); //if it has a root directory - remove it
		}
		m_name = m_name.substr(0, m_name.find_last_of(".")); //remove the extention
	
		//loading the texture from an image file	
		result = D3DXCreateTextureFromFile(device, fileName, &m_pTexture);
		if (FAILED(result))
		{
			return false;
			std::cout << "CreateTextureFromFile failed";
		}

		//get raw data (width and height)
		IDirect3DDevice9* resource = 0;
		m_texture->GetResource(&resource);
		
	}

};