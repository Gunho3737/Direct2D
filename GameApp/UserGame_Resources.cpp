#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"
#include "UserGame_Resources_Shader.h"


void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectory SoundDir;
		//���� ������Ʈ ��ġ �޾ƿ�
		//FileSystm�� �̿��ؼ� �ּҸ� �޾ƿԴ�


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

	AppShaderLoad();

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
		GameEngineVertexBufferManager::GetInst().Create("Box", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	//������ü Box
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


	//�簢�� Rect
	{
		//�⺻ �簢�� Rect
		{

			std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

			{
				// �ո�
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


		//ȭ�� ��ü�� ���� �簢�� FullRect
		{
		
			std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

			{
				// �ո�
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


	//���ؽ� ���̴� ����
	/*
	{
		GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
			{
				//	//ũ�����
				//	float4x4 ScaleMat;
				//	ScaleMat.Scaling({ 20.0f, 20.0f, 20.0f });
				//
				//	//�������
				//	float4x4 RotMat;
				//	RotMat.RotationDeg({ 0.0f, 0.0f, 0.0F });
				//	//RotMat.RotationDeg({ 0.0f, 0.0f, RotAngle });
				//
				//
				//	//�̵����
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
				//	//�� ���
				//	float4x4 ViewMat;
				//
				//	// ���� ��� ��ü�� �ٶ󺸰� �ִ�.
				//	// ViewMat.ViewAtLH({ 0.0f, 0.0f, -2000.0f }, {0, 0, 0}, { 0.0f, 1.0f, 0.0f });
				//
				//	// ���� �� �������� �ٶ󺸰� �ִ�.
				//	// ������ ��ġ�� z�� -2000, FDir�������� �ٶ󺸰� �ְ�, ���迡�� �������� y���� �ȴ�
				//	ViewMat.ViewToLH({ 0.0f, 0.0f, -2000.0f }, FDir, { 0.0f, 1.0f, 0.0f });
				//
				//	//����� ����(��)�� ������ ��ġ�� ������ �ȴ�
				//	//�׷��� ��繰ü��
				//	//�̵� -> z������ 2000 �̵�
				//	//ȸ�� -> �����ڰ� �ٶ󺸴� ���⸸ŭ ȸ��
				//	//�̰� ��繰ü�� ���� �Ǵ°�
				//
				//	//���� �������
				//	float4x4 PerspectiveMat;
				//	PerspectiveMat.PerspectiveFovLH(60.0f, 1280.0f, 720.0f, 0.1f, 1000.0f);
				//
				//	//���� �������
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
				//		// �� ������� ���� ����� ������������ z�� �̹� w�� �����Ѱ̴ϴ�.
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

	// �����Ǳ׷���
	// Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	// �ð�ݴ�������� �׷����͵��� �׷���
	Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	Info.AntialiasedLineEnable = true;
	Info.MultisampleEnable = true;

	//// ȭ�� �ٱ��� ���� ����� �߶󳽴�.
	// Info.FrontCounterClockwise = true;
	//Info.ScissorEnable = true;
	//Info.SlopeScaledDepthBias = 0;

	//// ���̰����� ���� �����Ұ̴ϴ�.
	//// ���̹��۸� �����ϰ� ���� �մϴ�.
	//Info.DepthBias = 0;
	//Info.DepthBiasClamp = 0;
	//Info.DepthClipEnable = FALSE;
	//Info.MultisampleEnable = TRUE;

	GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
	Ptr->SetViewPort(800.0f, 600.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("ColorRendering");
		
		// �̷� �⺻���� vertex���� �ִ�.
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");

		// �� vertex�� �̷��� ��ġ��Ű�ڴ�.
		Pipe->SetVertexShader("Color_VS");

		// �� vertex�� 3�� ��� ������ �׸��ڴ�. ������ �ε��� ������ �������
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Color_PS");
	}

}

