
#include "Mesh.h"


//constructor
Mesh::Mesh(void)
{
	m_mesh = 0;
}

//destructor
Mesh::~Mesh(void)
{
	if (m_mesh)
	{
		m_mesh->Release();
		m_mesh = NULL;
	}
}

//wrapper for loading mesh
bool Mesh::LoadMesh(IDirect3DDevice9* device, LPCTSTR meshFileName) 
{
	/* Prototype of a D3D function to load mesh from file
	HRESULT D3DXLoadMeshFromX(LPCTSTR pFilename, //This is a pointer to a string that contains the filename of the mesh
                          DWORD Options, //In this parameter we can place all manner of flags to give specifics on how our mesh is to be handled. 
										// The flag to put in here now is D3DXMESH_SYSTEMMEM. This flag tells Direct3D to use the system memory to store this mesh.
                          LPDIRECT3DDEVICE9 pD3DDevice, //pointer to the device
                          LPD3DXBUFFER *ppAdjacency, // is a pointer to a storage buffer used by Direct3D. Adjacency consists of information regarding which triangles are adjacent to which. For now just set it NULL
                          LPD3DXBUFFER *ppMaterials, // This is another buffer, which stores the material information for each subset.
                          LPD3DXBUFFER *ppEffectInstances, // buffer for effects. For now set to NULL
                          DWORD *pNumMaterials, //  In this DWORD will be placed the number of materials that exist. We can use this number to determine how many subset there are in a mesh. Useful. For this parameter, we will create a global DWORD called numMaterials, and place its address here.
                          LPD3DXMESH *ppMesh); */
	
		LPD3DXBUFFER bufMaterial;

		// retrieve the pointer to the buffer containing the material information
		D3DXMATERIAL* tempMaterials = (D3DXMATERIAL*)bufMaterial->GetBufferPointer();

		// create a new material buffer for each material in the mesh
		material = new D3DMATERIAL9[m_numMaterials];

		for (DWORD i = 0; i < m_numMaterials; i++)    // for each material...
		{
			material[i] = tempMaterials[i].MatD3D;    // get the material info
			material[i].Ambient = material[i].Diffuse;    // make ambient the same as diffuse
	    }

		//getting a name based on what the file is called
		m_name = CT2A(meshFileName); // CT2A is converting CHAR to std::string, it's an ATL(Active Template Library) conversion helper "CX2Y", where X is a current state and Y a state you want to convert to
		int pos = (int)m_name.find_last_of("/"); //find the last forward slash
		if (pos >= 0)
		{
			m_name = m_name.substr(pos + 1, m_name.length()); //if it has a root directory - remove it
		}
		m_name = m_name.substr(0, m_name.find_last_of(".")); //remove the extention. UPD: i think it needs the extention after all


		HRESULT result;
		result = D3DXLoadMeshFromX(L"spaceship 2.x",    // load this file
			D3DXMESH_SYSTEMMEM,    // load the mesh into system memory
			device,    // the Direct3D Device
			NULL,    // we aren't using adjacency
			&bufMaterial,    // put the materials here
			NULL,    // we aren't using effect instances
			&m_numMaterials,    // the number of materials in this model
			&m_mesh);    // put the mesh here			
		if (FAILED(result))
		{
			return false;
			std::cout << "D3DXLoadMeshFromX failed";
		}

	return true;

}


//getters
LPD3DXMESH Mesh::GetMesh()
{
	return m_mesh;
}

std::string Mesh::GetName()
{
	return m_name;
}

