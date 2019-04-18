#include "DXUT.h"
#include "SpineScene.h"

#include "AtlasScene.h"
#include "UI.h"
#include "ImagePiece.h"
#include "SpineAdmin.h"
#include <fstream>


SpineScene::SpineScene()
{

}


SpineScene::~SpineScene()
{
}

void SpineScene::Init()
{
	fileOpenUi = new UI([&]() { AddAtlasImage(); }, { 200, 50 }, { 200, 100 }, "./Image/Open.png");
}

void SpineScene::Update()
{
	fileOpenUi->Update();
	if(spineAdmin)
		spineAdmin->Update();
}

void SpineScene::Render()
{
	fileOpenUi->Render();
	if (spineAdmin)
		spineAdmin->Render();
}

void SpineScene::Release()
{
	SAFE_RELEASE(fileOpenUi);
	SAFE_DELETE(fileOpenUi);
	SAFE_RELEASE(spineAdmin);
	SAFE_DELETE(spineAdmin);
}

void SpineScene::AddAtlasImage()
{
	wstring imagePathW = CreateOpenFile();
	wstring dataPathW = CreateOpenFile();

	//wstring to string
	string imagePathA;
	string dataPathA;
	imagePathA.assign(imagePathW.begin(), imagePathW.end());
	dataPathA.assign(dataPathW.begin(), dataPathW.begin());

	Texture * atlasImage = IMAGEMANAGER->AddTexture(imagePathA, imagePathA);

	fstream fs;
	fs.open(dataPathW);

	list<ImagePiece*> vImagePiece;
	//Add PieceImage
	while (!fs.eof())
	{
		string name;
		RECT rectImage = { 0 };

		fs >> name >> rectImage.left >> rectImage.top >> rectImage.right >> rectImage.bottom;

		if(name.size() != 0)
			vImagePiece.push_back(new ImagePiece(atlasImage, rectImage, name, 30));
	}

	spineAdmin = new SpineAdmin(vImagePiece);
	spineAdmin->Init();
	fs.close();
}
