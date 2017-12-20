#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "Texture.h"
#include "Renderer.h"
#include <iostream>
#include <vector>

class ResourceManager
{
public:
	~ResourceManager(void);

	void LoadTexture(IDirect3DDevice9* device, char* fileName);
	LPDIRECT3DTEXTURE9 GetTextureByName(char* TextureName);
	static ResourceManager* GetInstance();

private:
	ResourceManager(void);//constructor is private because we only need one of these
	std::vector<Texture*> m_textureList; //a resource manager must have access to multiple textures


	static ResourceManager m_instance;
	ResourceManager* m_pInstance = &m_instance; //making a pointer for this instance
};

#endif