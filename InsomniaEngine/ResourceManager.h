#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "Texture.h"
#include "Mesh.h"
#include "Renderer.h"
#include <iostream>
#include <vector>

/*will set and release the texture*/

class ResourceManager
{
public:
	~ResourceManager(void);

	void LoadTextureRM(IDirect3DDevice9* device, char* fileName);
	LPDIRECT3DTEXTURE9 GetTextureByName(char* TextureName);

	void LoadMeshRM(IDirect3DDevice9* device, char* fileName);

	static ResourceManager* GetInstance();

private:
	ResourceManager(void);//constructor is private because we only need one of these
	std::vector<Texture*> m_textureList; //a resource manager must have access to multiple textures
	std::vector<Mesh*> m_meshList; //and meshes

	static ResourceManager m_instance;
	ResourceManager* m_pInstance = &m_instance; //making a pointer for this instance
};

#endif