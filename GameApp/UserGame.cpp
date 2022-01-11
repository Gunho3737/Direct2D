#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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
		//현재 프로젝트 위치 받아옴
		//FileSystrm을 이용해서 주소를 받아왔다


		SoundDir.MoveParent("Popol");
		//포폴 폴더로 이동

		SoundDir.MoveChild("Resources");
		//리소스 폴더로 이동

		SoundDir.MoveChild("Sound");
		//사운드 폴더로 이동

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			//폴더 안에 있는 모든 mp3파일을 로드했다
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

	// 지역 static
	//static float X = 0.0f;
	//X += 10.0f * GameEngineTime::GetInst().GetDeltaTime();
	//Rectangle(GameEngineWindow::GetInst().GetWindowDC(), 0 + X, 0, 100 + X, 100);
}