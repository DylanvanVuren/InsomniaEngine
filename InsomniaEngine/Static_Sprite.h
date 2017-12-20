#pragma once
#include "DX_Manager.h"



class Static_Sprite
{
	LPDIRECT3DTEXTURE9 m_texture;
	RECT m_rect;
	void CreateTexture(char* fileName);

public:
	Static_Sprite(void);
	~Static_Sprite(void);

	virtual void Initialize(char* fileName);

	void Render();

	virtual void Render(D3DXVECTOR3 position);

	void Render(D3DXVECTOR3 position, RECT rect);

	//	Getter
	const RECT GetRect()const { return m_rect; }

	// Setter
	void SetRect(RECT rect) { m_rect = rect; }
	void SetRect(int left, int right, int top, int bottom) { m_rect.left = left; m_rect.right = right; m_rect.top = top; m_rect.bottom = bottom; }
};

