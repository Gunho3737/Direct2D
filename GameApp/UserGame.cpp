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
float4 BoxPos = { 0.0f, 0.0f, 0.0f };

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
			std::vector<int> RectIndex;

			for (int i = 0; i < 6; i++)
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
					//크기행렬
					float4x4 ScaleMat;
					ScaleMat.Scaling({ 20.0f, 20.0f, 20.0f });

					//자전행렬
					float4x4 RotMat;
					RotMat.RotationDeg({ 0.0f, 0.0f, 0.0F });
					//RotMat.RotationDeg({ 0.0f, 0.0f, RotAngle });


					//이동행렬
					float4x4 PosMat;
					//PosMat.Translation({ 0.0f, 0.0f, 0.0f });
					PosMat.Translation(BoxPos);

					float4 ZeroPos = float4::ZERO;

					float4 FDir = { 1.0f, 0.0f, 1.0f };
					FDir.Normalize3D();


					//뷰 행렬
					float4x4 ViewMat;

					// 내가 어떠한 물체를 바라보고 있다.
					// ViewMat.ViewAtLH({ 0.0f, 0.0f, -2000.0f }, {0, 0, 0}, { 0.0f, 1.0f, 0.0f });

					// 내가 이 방향으로 바라보고 있다.
					// 관측자 위치는 z축 -2000, FDir방향으로 바라보고 있고, 세계에서 위방향이 y축이 된다
					ViewMat.ViewToLH({ 0.0f, 0.0f, -2000.0f }, FDir, { 0.0f, 1.0f, 0.0f });

					//뷰행렬 적용(곱)시 관측자 위치가 원점이 된다
					//그래서 모든물체가
					//이동 -> z축으로 2000 이동
					//회전 -> 관측자가 바라보는 방향만큼 회전
					//이게 모든물체에 적용 되는것
				
					//원근 투영행렬
					float4x4 PerspectiveMat;
					PerspectiveMat.PerspectiveFovLH(60.0f, 1280.0f, 720.0f, 0.1f, 1000.0f);

					//직교 투영행렬
					float4x4 OrthographicMat;
					OrthographicMat.OrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);

					{

						// float4 VectorTest = { 0.0f, 0.0f, 100.0f, 2.0f };
						float4 VectorTest = { 0.0f, 0.0f, 100.0f, 1.0f };

						float4x4 TestMat;

						TestMat.vx = { 0.1f, 0.0f , 0.0f , 0.0f };
						TestMat.vy = { 0.0f, 0.1f , 0.0f , 0.0f };
						TestMat.vz = { 0.0f, 0.0f , 0.1f , 1.0f };
						TestMat.vw = { 0.0f, 0.0f , 0.0f , 0.0f };

						// 이 방식으로 월드 뷰까지 곱해졌을때의 z를 이미 w에 보관한겁니다.
						VectorTest *= TestMat;

						int a = 0;

					}
					float4x4 WorldMat = ScaleMat * RotMat * PosMat;
					float4x4 WorldView = WorldMat * ViewMat;

					float4x4 WorldViewProjectionMat = WorldMat * ViewMat * PerspectiveMat;

					float4x4 WorldViewOrthographicMat = WorldMat * ViewMat * OrthographicMat;

					float4 PersPos = _Value;
					PersPos *= WorldViewProjectionMat;

					float4 OrthPos = _Value;
					OrthPos *= WorldViewOrthographicMat;


					//PersPos.x = PersPos.x / PersPos.w;
					//PersPos.y = PersPos.y / PersPos.w;
					//PersPos.z = PersPos.z / PersPos.w;
					//PersPos.w = 1.0f;

					return PersPos;
				}
			);
		}

		{

			GameEngineReasterizer* Ptr = GameEngineReasterizerManager::GetInst().Create("TestReasterizer");

			Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);

		}
}



void UserGame::Release() 
{
	// Resources
	GameEngineManagerHeler::ManagerRelease();


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
	Pipe.SetRasterizer("TestReasterizer");

	RotAngle += 360.0f * GameEngineTime::GetInst().GetDeltaTime();
	BoxPos.x += 10.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();
	
}