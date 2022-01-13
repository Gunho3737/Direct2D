#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

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

float RotAngle = 0.0f;

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

	{
		//������ü�� ����
		std::vector<float4> RectVertex = std::vector<float4>(4 * 6);

		{
			RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
			RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
			RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
			RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

			RectVertex[4] = float4::RotateXDegree(RectVertex[0], 180.0f);
			RectVertex[5] = float4::RotateXDegree(RectVertex[1], 180.0f);
			RectVertex[6] = float4::RotateXDegree(RectVertex[2], 180.0f);
			RectVertex[7] = float4::RotateXDegree(RectVertex[3], 180.0f);
		}

		{
			RectVertex[8] = float4::RotateYDegree(RectVertex[0], 90.0f);
			RectVertex[9] = float4::RotateYDegree(RectVertex[1], 90.0f);
			RectVertex[10] = float4::RotateYDegree(RectVertex[2], 90.0f);
			RectVertex[11] = float4::RotateYDegree(RectVertex[3], 90.0f);

			RectVertex[12] = float4::RotateYDegree(RectVertex[0], -90.0f);
			RectVertex[13] = float4::RotateYDegree(RectVertex[1], -90.0f);
			RectVertex[14] = float4::RotateYDegree(RectVertex[2], -90.0f);
			RectVertex[15] = float4::RotateYDegree(RectVertex[3], -90.0f);
		}

		{
			RectVertex[16] = float4::RotateXDegree(RectVertex[0], 90.0f);
			RectVertex[17] = float4::RotateXDegree(RectVertex[1], 90.0f);
			RectVertex[18] = float4::RotateXDegree(RectVertex[2], 90.0f);
			RectVertex[19] = float4::RotateXDegree(RectVertex[3], 90.0f);

			RectVertex[20] = float4::RotateXDegree(RectVertex[0], -90.0f);
			RectVertex[21] = float4::RotateXDegree(RectVertex[1], -90.0f);
			RectVertex[22] = float4::RotateXDegree(RectVertex[2], -90.0f);
			RectVertex[23] = float4::RotateXDegree(RectVertex[3], -90.0f);
		}
		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex);
	}


		{
			//���� ������
			std::vector<int> RectIndex;

			for (size_t i = 0; i < 6; i++)
			{
				RectIndex.push_back(i * 4 + 0);
				RectIndex.push_back(i * 4 + 1);
				RectIndex.push_back(i * 4 + 2);

				RectIndex.push_back(i * 4 + 0);
				RectIndex.push_back(i * 4 + 2);
				RectIndex.push_back(i * 4 + 3);
			}

			GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex);
		}

		{
			GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
				{
					float4 MovePos = { 200.0f, 200.0f };
					float4 Pos = _Value;
					Pos *= 100.0f;
					Pos.RotateXDegree(RotAngle);
					Pos += MovePos;

					return Pos;
				}
			);
		}
}



void UserGame::Release() 
{
	// Resources
	GameEngineIndexBufferManager::Destroy();
	GameEngineVertexShaderManager::Destroy();
	GameEngineVertexBufferManager::Destroy();
	GameEngineTextureManager::Destroy();
	GameEngineSoundManager::Destroy();

	// Base
	GameEngineTime::Destroy();
	GameEngineWindow::Destroy();;
}

void UserGame::GameLoop()
{
	//���� ������ ���ư��� ����

	GameEngineRenderingPipeLine Pipe;

	Pipe.SetInputAssembler1("Rect");
	Pipe.SetVertexShader("TestShader");
	Pipe.SetInputAssembler2("Rect");

	RotAngle += 30.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();
	
}