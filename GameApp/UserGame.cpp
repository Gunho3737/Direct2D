#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

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

float RotAngle = 0.0f;

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

	{
		//정육면체를 생성
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
			//현재 공부중
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
	//실제 게임이 돌아가는 루프

	GameEngineRenderingPipeLine Pipe;

	Pipe.SetInputAssembler1("Rect");
	Pipe.SetVertexShader("TestShader");
	Pipe.SetInputAssembler2("Rect");

	RotAngle += 30.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();
	
}