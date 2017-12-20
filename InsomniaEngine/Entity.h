#include <string>
#include "Texture.h"
#include <d3dx9.h>

class Entity{
	public:
		Entity(float x, float y, float z);
		~Entity();

		Entity getEntity();
		void draw(LPDIRECT3DDEVICE9 d3ddev);
		void Update();
	private:
		D3DVECTOR pos;
		std::string entityName;
		Texture texture;
};