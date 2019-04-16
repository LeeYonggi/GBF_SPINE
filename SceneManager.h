#pragma once
#include "Singleton.h"
class SceneManager :
	public Singleton<SceneManager>
{
public:
	SceneManager();
	virtual ~SceneManager();

private:
	Scene *nowScene = nullptr;
	Scene *nextScene = nullptr;
	bool isSceneChange = false;

public:
	void AddScene(Scene *scene);
	void Update();
	void Render();
private:
	void Release();
};

#define SCENEMANAGER SceneManager::GetInstance()