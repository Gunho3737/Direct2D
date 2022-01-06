#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

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

	GameEngineSound::GetInst().Initialize();
	return;
}

void UserGame::ResourcesLoad() 
{
	{
		GameEngineDirectroy SoundDir;
		//���� ������Ʈ ��ġ �޾ƿ�


		SoundDir.MoveParent("Popol");
		//���� ������ �̵�

		SoundDir.MoveChild("Resources");
		//���ҽ� ������ �̵�

		SoundDir.MoveChild("Sound");
		//���� ������ �̵�


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