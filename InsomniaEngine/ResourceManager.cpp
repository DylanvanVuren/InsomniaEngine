#include "ResourceManager.h"

ResourceManager::ResourceManager(void)
{
}

ResourceManager::~ResourceManager(void)
{
	while (!m_textureList.empty())
	{
		delete m_textureList[0];
		m_textureList.erase(m_textureList.begin());
	}
}

void ResourceManager::LoadTexture(IDirect3DDevice9* device, char* fileName) 
{
	Texture* texture = new Texture();

	LPCTSTR fileNameLPCTSRT = CA2W(fileName); //convert a char array to pointer with the ATL conversion helper
	if (!texture->Initialize(device, fileNameLPCTSRT))
	{
		delete texture;
		std::cout << "Could not Initialize texture" << fileName << std::endl;
		return;
	}

}