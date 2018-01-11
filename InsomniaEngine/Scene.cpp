#include "Scene.h"
#include "SceneManager.h"
#include "SceneLoader.h"

//#include <iostream>
#include <list>
#include <d3d9.h>



//loader xml file
//loads scne with entities
//loader gaat door entities entities List

//scene entities
//elke scene door de lijst render jezelf

PDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9   d3Scene = NULL; // Our rendering device
Scene current_scene;

Scene::Scene() {
	Scene current_scene;
}

Scene::~Scene() {
	std::list<Entity> entities;
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
	entities.clear();
	cout << "Entities is being deleted" << endl;
}

bool Scene::Init()
{
	Entity* entity;
	std::list<Entity> entities;                              // empty list of entities

}


void makeScene() {

	// clear the window to a dark blue
	
	d3Scene->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(d3Scene->BeginScene()))   // begins the 3D scene
	{
		// do/call the rendering methode

		d3Scene->EndScene();    // ends the 3D scene
	}

	d3Scene->Present(NULL, NULL, NULL, NULL);    // displays the created frame

}


void Scene::setScene(Scene* scene) {
	//this->current_scene = scene;

}

Scene* Scene::getScene() {
	return //this->current_scene;
}

std::list<Entity> getEntitiesList() {
	std::list<Entity> entityLijst;
	return entityLijst;
}


void Scene::AddEntity(Entity* entity)
{
	//check if exists/ if doesnt add it //vec_object are gameObjectfrom Scene
	std::list<Entity*>::iterator it = std::find(this->vec_objects.begin(), this->vec_objects.end(), entity);
	//vec_object==GameObject==gameEntity

	if (it == this->vec_objects.end())
	{
		entity->SetScene(this);
		entitiesToAdd.getEntitiesList();
		// This entity will be added in the end of the list
		entitiesToAdd.push_back(entity);
		//this->vec_objects.push_back(entity);

	}
}


void Scene::removeEntity(Entity* entity)
{
	//check if Entity exists
	std::list<Entity*>::iterator it = std::find(this->vec_objects.begin(), this->vec_objects.end(), entity);

	if (it != this->vec_objects.end())
	{
		this->vec_objects.remove(entity);

	}
}

//addChild not really used
//vec_childeren==GameObject==gameEntity
void Scene::addChild(Entity* child)
{
	std::vector<Entity*>::iterator it = std::find(this->vec_childeren.begin(), this->vec_childeren.end(), child);
	if (it == this->vec_childeren.end())
	{
		this->vec_childeren.push_back(child);
		child->setParent(this);
		child->setScene(getScene());
	}
}


void Scene::removeChild(Entity* child)
{
	std::vector<Entity*>::iterator it = std::find(this->vec_childeren.begin(), this->vec_childeren.end(), child);
	if (it != this->vec_childeren.end())
	{
		this->vec_childeren.remove(child);

	}
}

void drawEntity(std::list<Entity> enList) {

	enList.getEntitiesList();

	for (list<Entity>::iterator iter = enList.begin(); iter != enList.end(); iter++) {
		cout << *iter << endl;
	}
	//   << print to  file && load from file // in loader
}

}
