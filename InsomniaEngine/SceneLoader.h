#pragma once
#include <list>
#include "Scene.h"

class SceneLoader
{

public:

	SceneLoader::SceneLoader();
	SceneLoader::~SceneLoader();

	void SceneLoader::loadEntitiesList(Scene* scene);

	void useResources();

	void SceneLoader::Save();
	void SceneLoader::Load();


};

