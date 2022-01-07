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

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			//���� �ȿ� �ִ� ��� mp3������ �ε��ߴ�
			GameEngineSound::GetInst().LoadSound(AllFile[i].GetFullPath());
		}
	}




}

void UserGame::Release() 
{
	GameEngineSound::Destroy();
}

void UserGame::GameLoop()
{

}