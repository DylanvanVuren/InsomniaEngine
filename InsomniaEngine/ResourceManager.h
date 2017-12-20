#include "Texture.h"
#include <iostream>
//here i need a vector too

class ResourceManager
{
public:
	//constructor and destructor
	ResourceManager(void);
	void LoadTexture(IDirect3DDevice9* device, char* fileName);

private:
	~ResourceManager(void);

	//some method for vector

	static ResourceManager m_instance;

};