#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"
#include "UserGame_Resources_Shader.h"


void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectory SoundDir;
		//현재 프로젝트 위치 받아옴
		//FileSystm을 이용해서 주소를 받아왔다


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

	AppShaderLoad();

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
		GameEngineVertexBufferManager::GetInst().Create("Box", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	//정육면체 Box
	{
		{
			std::vector<UINT> RectIndex;

			for (int i = 0; i < 6; i++)
			{
				RectIndex.push_back(i * 4 + 0);
				RectIndex.push_back(i * 4 + 1);
				RectIndex.push_back(i * 4 + 2);

				RectIndex.push_back(i * 4 + 0);
				RectIndex.push_back(i * 4 + 2);
				RectIndex.push_back(i * 4 + 3);
			}

			GameEngineIndexBufferManager::GetInst().Create("Box", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		}
	}


	//사각형 Rect
	{
		//기본 사각형 Rect
		{

			std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

			{
				// 앞면
				RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }) };
				RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }) };
				RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }) };
				RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }) };
			}

			GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		}

		{
			std::vector<UINT> RectIndex;

			RectIndex.push_back(0);
			RectIndex.push_back(1);
			RectIndex.push_back(2);

			RectIndex.push_back(0);
			RectIndex.push_back(2);
			RectIndex.push_back(3);

			GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		}


		//화면 전체를 덮는 사각형 FullRect
		{
		
			std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

			{
				// 앞면
				RectVertex[0] = { float4({ -1.0f, 1.0f, 0.0f }) };
				RectVertex[1] = { float4({ 1.0f, 1.0f, 0.0f }) };
				RectVertex[2] = { float4({ 1.0f, -1.0f, 0.0f }) };
				RectVertex[3] = { float4({ -1.0f, -1.0f, 0.0f }) };
			}

			GameEngineVertexBufferManager::GetInst().Create("FullRect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		}

		{
			std::vector<UINT> RectIndex;

			RectIndex.push_back(0);
			RectIndex.push_back(1);
			RectIndex.push_back(2);

			RectIndex.push_back(0);
			RectIndex.push_back(2);
			RectIndex.push_back(3);

			GameEngineIndexBufferManager::GetInst().Create("FullRect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
		}



	}


	//버텍스 쉐이더 설명
	/*
	{
		GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
			{
				//	//크기행렬
				//	float4x4 ScaleMat;
				//	ScaleMat.Scaling({ 20.0f, 20.0f, 20.0f });
				//
				//	//자전행렬
				//	float4x4 RotMat;
				//	RotMat.RotationDeg({ 0.0f, 0.0f, 0.0F });
				//	//RotMat.RotationDeg({ 0.0f, 0.0f, RotAngle });
				//
				//
				//	//이동행렬
				//	float4x4 PosMat;
				//	//PosMat.Translation({ 0.0f, 0.0f, 0.0f });
				//	PosMat.Translation(BoxPos);
				//
				//	float4 ZeroPos = float4::ZERO;
				//
				//	float4 FDir = { 1.0f, 0.0f, 1.0f };
				//	FDir.Normalize3D();
				//
				//
				//	//뷰 행렬
				//	float4x4 ViewMat;
				//
				//	// 내가 어떠한 물체를 바라보고 있다.
				//	// ViewMat.ViewAtLH({ 0.0f, 0.0f, -2000.0f }, {0, 0, 0}, { 0.0f, 1.0f, 0.0f });
				//
				//	// 내가 이 방향으로 바라보고 있다.
				//	// 관측자 위치는 z축 -2000, FDir방향으로 바라보고 있고, 세계에서 위방향이 y축이 된다
				//	ViewMat.ViewToLH({ 0.0f, 0.0f, -2000.0f }, FDir, { 0.0f, 1.0f, 0.0f });
				//
				//	//뷰행렬 적용(곱)시 관측자 위치가 원점이 된다
				//	//그래서 모든물체가
				//	//이동 -> z축으로 2000 이동
				//	//회전 -> 관측자가 바라보는 방향만큼 회전
				//	//이게 모든물체에 적용 되는것
				//
				//	//원근 투영행렬
				//	float4x4 PerspectiveMat;
				//	PerspectiveMat.PerspectiveFovLH(60.0f, 1280.0f, 720.0f, 0.1f, 1000.0f);
				//
				//	//직교 투영행렬
				//	float4x4 OrthographicMat;
				//	OrthographicMat.OrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);
				//
				//	{
				//
				//		// float4 VectorTest = { 0.0f, 0.0f, 100.0f, 2.0f };
				//		float4 VectorTest = { 0.0f, 0.0f, 100.0f, 1.0f };
				//
				//		float4x4 TestMat;
				//
				//		TestMat.vx = { 0.1f, 0.0f , 0.0f , 0.0f };
				//		TestMat.vy = { 0.0f, 0.1f , 0.0f , 0.0f };
				//		TestMat.vz = { 0.0f, 0.0f , 0.1f , 1.0f };
				//		TestMat.vw = { 0.0f, 0.0f , 0.0f , 0.0f };
				//
				//		// 이 방식으로 월드 뷰까지 곱해졌을때의 z를 이미 w에 보관한겁니다.
				//		VectorTest *= TestMat;
				//
				//		int a = 0;
				//
				//	}
				//	float4x4 WorldMat = ScaleMat * RotMat * PosMat;
				//	float4x4 WorldView = WorldMat * ViewMat;
				//
				//	float4x4 WorldViewProjectionMat = WorldMat * ViewMat * PerspectiveMat;
				//
				//	float4x4 WorldViewOrthographicMat = WorldMat * ViewMat * OrthographicMat;

				//float4 PersPos = _Value;
				//  PersPos *= WorldViewProjectionMat;

				//	float4 OrthPos = _Value;
				//	OrthPos *= WorldViewOrthographicMat;
				float4 PersPos = _Value;
				return PersPos;
			}
		);
	}*/


	{
	D3D11_RASTERIZER_DESC Info = { D3D11_FILL_MODE::D3D11_FILL_SOLID, };

	Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

	// 무조건그려라
	// Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	// 시계반대방향으로 그려진것들을 그려라
	Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	Info.AntialiasedLineEnable = true;
	Info.MultisampleEnable = true;

	//// 화면 바깥에 나간 면들을 잘라낸다.
	// Info.FrontCounterClockwise = true;
	//Info.ScissorEnable = true;
	//Info.SlopeScaledDepthBias = 0;

	//// 깊이관련은 추후 설명할겁니다.
	//// 깊이버퍼를 설명하고 들어야 합니다.
	//Info.DepthBias = 0;
	//Info.DepthBiasClamp = 0;
	//Info.DepthClipEnable = FALSE;
	//Info.MultisampleEnable = TRUE;

	GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
	Ptr->SetViewPort(800.0f, 600.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("ColorRendering");
		
		// 이런 기본적인 vertex들이 있다.
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");

		// 그 vertex을 이렇게 위치시키겠다.
		Pipe->SetVertexShader("Color_VS");

		// 그 vertex을 3개 묶어서 면으로 그리겠다. 순서는 인덱스 버퍼의 순서대로
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Color_PS");
	}

}

