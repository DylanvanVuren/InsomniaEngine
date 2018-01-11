#pragma once
#include <string>

class SceneManager
{

public:

	SceneManager();
	~SceneManager();

	void loadMenu();
	std::string loadLevel(std::string levelName);

	void SceneManager::setSceneManager(SceneManager man);
	SceneManager* SceneManager::getSceneManager();

	//void draw();
	//void GetTransform()

private:

};
