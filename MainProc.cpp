#include "DXUT.h"
#include "MainProc.h"

#include "AtlasScene.h"

MainProc::MainProc()
{
}


MainProc::~MainProc()
{
}

void MainProc::Init()
{
	SCENEMANAGER->AddScene(new AtlasScene());
}

void MainProc::Update()
{
	SCENEMANAGER->Update();
	INPUTMANAGER->Update();
}

void MainProc::Render()
{
	IMAGEMANAGER->BeginSprite();

	SCENEMANAGER->Render();

	IMAGEMANAGER->EndSprite();
}

void MainProc::Release()
{
	ImageManager::ReleaseInstance();
	InputManager::ReleaseInstance();
	SceneManager::ReleaseInstance();
}