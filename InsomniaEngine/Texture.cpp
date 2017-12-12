////i'm following a book and a tutorial 
////and trying to implement it but without a shader
//
 
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



#include <d3d9.h>
#include <D3DX9tex.h>
#include <string>

class Texture
{
public:
	//constructor and destructor
	Texture(void);
	~Texture(void);

	//maybe create an empty texture first?
	//bool Create(int width, int height);  //maybe not needed?

	Texture::Texture GetTexture(); //i did this instead of a shader resource view but it's probably wrong. 
	//maybe it's HRESULT GetTexture(); ?
	std::string GetName();

	int GetWidth();
	int GetHeight();

private:
	int m_width;
	int m_height;
	
	HRESULT m_texture; //not sure what type it is?
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


	bool Texture::Initialize(IDirect3DDevice9* device, LPCTSTR fileName)
	{
		HRESULT result;

		m_name = fileName;
		//int pos = m_name.find_last_of("/");
		//if (pos >= 0)
		//{
		//m_name = m_name.substr(pos + 1, m_name.length());
		//}
		//m_name = m_name.substr(0, m_name.find_last_of("."));
	
		//loading the texture
		result = D3DXCreateTextureFromFile(device, fileName);
		if (FAILED(result))
		{
			return false;
		}

		//get width and height
		IDirect3DDevice9* resource = 0;
		m_texture->GetResource(&resource);

		
	}


};