#include "Static_Sprite.h"

Static_Sprite::Static_Sprite(void)
{
	m_texture = NULL;
}

Static_Sprite::~Static_Sprite(void)
{

}

void Static_Sprite::Initialize(char *fileName)
{
	CreateTexture(fileName);
}

void Static_Sprite::CreateTexture(char *fileName)
{
	m_texture = g_dxManager.GetTexture(fileName);
}

void Static_Sprite::Render()
{
	g_dxManager.DrawSprite(m_texture);
}

void Static_Sprite::Render(D3DXVECTOR3 position)
{
	g_dxManager.DrawSprite(m_texture, position);
}

void Static_Sprite::Render(D3DXVECTOR3 position, RECT rect)
{
	g_dxManager.DrawSprite(m_texture, rect, position);
}