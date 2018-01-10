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

	while (!m_meshList.empty())
	{
		delete m_meshList[0];
		m_meshList.erase(m_meshList.begin());
	}


}

void ResourceManager::LoadTextureRM(IDirect3DDevice9* device, char* fileName) 
{
	Texture* texture = new Texture();

	LPCTSTR fileNameLPCTSRT = CA2W(fileName); //convert a char array to pointer with the ATL conversion helper
	if (!texture->LoadTexture(device, fileNameLPCTSRT)) //if it doesn't Initialize, send a message
	{
		delete texture;
		std::cout << "Could not Initialize texture " << fileName << std::endl;
		return;
	}
	//else add it to the list of textures
	m_textureList.push_back(texture);
	std::cout << "Successfully loaded the texture " << fileName << std::endl;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTextureByName(char* textureName)
{
	for (int i=0; i<(int)m_textureList.size(); i++) //loop through the list of textures
	{
		Texture* texture = m_textureList[i];
		std::string l_textureName = texture->GetName(); //get a local texture name

		if (!strcmp(textureName, l_textureName.c_str())) //compare each l_textureName with the input textureName
		{
			return texture->GetTexture();
		}
	}

	return NULL;
}

void ResourceManager::LoadMeshRM(IDirect3DDevice9* device, char* fileName)
{
	Mesh* mesh = new Mesh();

	LPCTSTR fileNameLPCTSRT = CA2W(fileName); //convert a char array to pointer with the ATL conversion helper
	if (!mesh->LoadMesh(device, fileNameLPCTSRT)) //if it doesn't load, send a message
	{
		delete mesh;
		std::cout << "Could not Initialize mesh " << fileName << std::endl;
		return;
	}
	//else add it to the list of meshes
	m_meshList.push_back(mesh);
	std::cout << "Successfully loaded the mesh " << fileName << std::endl;
}


//here we check if an instance exists, and if it doesn't - we make one (it's a bit trippy with the pointers though, idk if it works)
//remember that the constructor for ResourceManager is private, because we need just one of it
ResourceManager* ResourceManager::GetInstance()
{
	if(m_instance.m_pInstance == NULL )  //m_instance.m_pInstance because a nonstatic member reference 
										//must be relative to a specific object
	{
		m_instance = ResourceManager(); //stack variable, is there even an instance? CHECK THIS
	}

	return m_instance.m_pInstance;

}