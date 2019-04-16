#include "DXUT.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	Release();
}


void SceneManager::AddScene(Scene * scene)
{
	isSceneChange = true;
	nextScene = scene;
}

void SceneManager::Update()
{
	if (isSceneChange)
	{
		if (nowScene)
		{
			nowScene->Release();
			delete nowScene;
		}
		nowScene = nextScene;
		nextScene = nullptr;
		nowScene->Init();
		isSceneChange = false;
	}
	if (nowScene)
		nowScene->Update();
}

void SceneManager::Render()
{
	if (nowScene)
		nowScene->Render();
}

void SceneManager::Release()
{
	SAFE_RELEASE(nowScene);
	SAFE_RELEASE(nextScene);
	SAFE_DELETE(nowScene);
	SAFE_DELETE(nextScene);
}
