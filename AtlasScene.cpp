#include "DXUT.h"
#include "AtlasScene.h"

#include "UI.h"
#include "AtlasImage.h"

AtlasScene::AtlasScene()
{
}


AtlasScene::~AtlasScene()
{
}

wstring CreateOpenFile() // OpenFile
{
	OPENFILENAME OFN;
	char str[300];
	TCHAR lpstrFile[MAX_PATH] = L"";
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = DXUTGetHWND();
	OFN.lpstrFilter = L".png";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = L"./";
	if (GetOpenFileName(&OFN) != 0) {
		sprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
	}

	return OFN.lpstrFile;
}

void AtlasScene::Init()
{
	fileOpenUi = new UI([&]() { AddAtlasImage(); }, { 200, 50 }, {200, 100}, "./Image/Open.png");
}

void AtlasScene::Update()
{
	if (atlasImage)
		atlasImage->Update();
	fileOpenUi->Update();
}

void AtlasScene::Render()
{
	if (atlasImage)
		atlasImage->Render();
	fileOpenUi->Render();
}

void AtlasScene::Release()
{
	SAFE_RELEASE(fileOpenUi);
	SAFE_DELETE(fileOpenUi);
	SAFE_RELEASE(atlasImage);
	SAFE_DELETE(atlasImage);
}

void AtlasScene::AddAtlasImage()
{
	wstring wstr = CreateOpenFile();
	string str;
	str.assign(wstr.begin(), wstr.end());

	if (atlasImage)
	{
		SAFE_RELEASE(atlasImage);
		SAFE_DELETE(atlasImage);
		atlasImage = nullptr;
	}

	atlasImage = new AtlasImage(str);
}
