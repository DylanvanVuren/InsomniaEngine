//i'm following following a tutorial 
//and trying to implement it but without a shader
//will add comments later 

#include <d3d11.h>
#include <D3DX11tex.h>
#include <string>

class Texture
{
public:
	Texture(void);
	~Texture(void);

	bool Initialize(ID3D11Device* device, LPCSTR fileName);

	Texture::Texture GetTexture(); //i did this instead of a shader resource view
	std::string GetName();

	int GetWidth();
	int GetHeight();

private:
	std::string m_name;

	int m_width;
	int m_height;

	Texture::Texture(void)
	{
		m_texture = 0;
		m_width = 0;
		m_height = 0;
	}

	Texture::~Texture(void)
	{
		if (m_texture)
		{
			m_texture->Release();
			m_texture = NULL;
		}

		m_name.clear();
	}

	bool Texture::Initialize(ID3D11Device* device, LPCSTR fileName)
	{
		HRESULT result;

		m_name = fileName;

		int pos = m_name.find_last_of("/");
		if (pos >= 0)
		{
			m_name = m_name.substr(pos + 1, m_name.length());
		}
		m_name = m_name.substr(0, m_name.find_last_of("."));
	
		//load the texture
		//result = shader resource view from file, not sure yet how to do it without a shader
		result = something;
		if (FAILED(result))
		{
			return false;
		}

		//get width and height
		ID3D11Resource* resource = 0;
		m_texture->GetResource(&resource);

		

	}



};