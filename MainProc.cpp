#include "DXUT.h"
#include "MainProc.h"

#include "AtlasScene.h"
#include "SpineScene.h"

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
	if (INPUTMANAGER->KeyDown('Q'))
	{
		SCENEMANAGER->AddScene(new AtlasScene());
	}
	else if (INPUTMANAGER->KeyDown('W'))
	{
		SCENEMANAGER->AddScene(new SpineScene());
	}
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
