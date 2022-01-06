#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

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

	GameEngineSound::GetInst().Initialize();
	return;
}

void UserGame::ResourcesLoad() 
{
	{
		GameEngineDirectroy SoundDir;
		//현재 프로젝트 위치 받아옴


		SoundDir.MoveParent("Popol");
		//포폴 폴더로 이동

		SoundDir.MoveChild("Resources");
		//리소스 폴더로 이동

		SoundDir.MoveChild("Sound");
		//사운드 폴더로 이동


		GameEngineSound::GetInst().LoadSound("Green_Greens.mp3", SoundDir.PathToPlusFileName("Green_Greens.mp3"));
	}



	GameEngineSound::GetInst().PlaySoundOneShot("Green_Greens.mp3");

}

void UserGame::Release() 
{
	GameEngineSound::Destroy();
}

void UserGame::GameLoop()
{
	switch (_getch())
	{
	case 'q':
	case 'Q':
		EngineDestroy();
		return;
	default:
		break;
	};
}