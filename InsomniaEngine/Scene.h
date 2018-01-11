#pragma once

class Scene
{

public:

	Scene();
	~Scene();

	void Scene::setScene(Scene* scene);
	Scene* Scene::getScene();

	void makeScene();
	bool Scene::Init();

	void drawEntity();

	void Scene::AddEntity(Entity* entity);
	void Scene::removeEntity(Entity* entity);

	void Scene::addChild(Entity* child);
	void Scene::removeChild(Entity* child);

private:

};
