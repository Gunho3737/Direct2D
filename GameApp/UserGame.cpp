#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>

UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}



void UserGame::Initialize() 
{

	GameEngineSoundManager::GetInst().Initialize();
	return;
}

void UserGame::ResourcesLoad() 
{
	{
		GameEngineDirectroy SoundDir;
		//���� ������Ʈ ��ġ �޾ƿ�
		//FileSystrm�� �̿��ؼ� �ּҸ� �޾ƿԴ�


		SoundDir.MoveParent("Popol");
		//���� ������ �̵�

		SoundDir.MoveChild("Resources");
		//���ҽ� ������ �̵�

		SoundDir.MoveChild("Sound");
		//���� ������ �̵�

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			//���� �ȿ� �ִ� ��� mp3������ �ε��ߴ�
			GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
		}
	}




}

static float4 RectPoint[4]
= {
 {0, 0},
 { 100, 0 },
 { 100, 100 },
 { 0, 100 },
};


void UserGame::Release() 
{
	GameEngineSoundManager::Destroy();
	GameEngineWindow::Destroy();
}

void UserGame::GameLoop()
{
	POINT PolyGon[4];

	for (size_t i = 0; i < 4; i++)
	{
		RectPoint[i].Rotatefloat2Degree(45 * GameEngineTime::GetInst().GetDeltaTime());
	}

	for (size_t i = 0; i < 4; i++)
	{
		PolyGon[i] = RectPoint[i].GetWindowPoint();
	}


	Polygon(GameEngineWindow::GetInst().GetWindowDC(), PolyGon, 4);

	// ���� static
	//static float X = 0.0f;
	//X += 10.0f * GameEngineTime::GetInst().GetDeltaTime();
	//Rectangle(GameEngineWindow::GetInst().GetWindowDC(), 0 + X, 0, 100 + X, 100);
}