#ifndef _MESH_H
#define _MESH_H

#include <d3d9.h>
#include <d3dx9.h>
#include <D3DX9tex.h>
#include <string>
#include <iostream> //just for cout
#include <stdio.h> //need these for the ATL conversion helper
#include <atldef.h>
#include <atlstr.h>

class Mesh
{
public:
	//constructor and destructor
	Mesh(void);
	~Mesh(void);

	//getters
	LPD3DXMESH GetMesh();
	std::string GetName();

	bool LoadMesh(IDirect3DDevice9* device, LPCTSTR meshFileName);

private:
	LPD3DXMESH m_mesh;
	D3DMATERIAL9* material; //define the material object
	DWORD m_numMaterials; //the number of materials in a mesh

	std::string m_name;
};

#endif