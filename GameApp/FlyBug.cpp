#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "FlyBug.h"


FlyBug::FlyBug()
{
}

FlyBug::~FlyBug()
{
}

void FlyBug::TestStartCallBack()
{
	int a = 0;
}

void FlyBug::TestEndCallBack()
{
	Death();
}

void FlyBug::Start()
{
	// ���� ����������Ұ� ���� �༮�Դϴ�.
	// �������μ� ������ �� �׸����ִ� ���ɼ��� ������ �ִ� �༮.
	//{
	//	GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	//	Renderer->SetRenderingPipeLine("Color");
	//	Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
	//	Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(0.0f, 0.0f, 0.0f));
	//}

	{
		GameEngineImageRenderer* PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->SetImage("FlyBug.png");
		//	
		//		//�߸� �̹����� ���° ��������Ʈ�� ������� ����(�ִϸ��̼��� �ƴ� )
		//		PlayerImageRenderer->SetIndex(10);
		//	
		//�ִϸ��̼� ����
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Idle", 1, 6, 0.1f);
		//	
		//		//�ִϸ��̼��� ù������/������ ������/�ִϸ��̼���x��°�������� ������ Ư�� �Լ��� ����ǵ����Ѵ�
		//		PlayerImageRenderer->SetStartCallBack("Test", std::bind(&FlyBug::TestStartCallBack, this));
		//		PlayerImageRenderer->SetEndCallBack("Test", std::bind(&FlyBug::TestEndCallBack, this));
		//		PlayerImageRenderer->SetFrameCallBack("Test", 5, std::bind(&FlyBug::TestEndCallBack, this));

		PlayerImageRenderer->SetChangeAnimation("Idle");
		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 300.0f, 300.0f, 1.0f });


	}

	Collision = CreateTransformComponent<GameEngineCollision>(20);
	Collision->GetTransform()->SetLocalScaling(float4{ 120.0f, 120.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({0.0f, 50.0f});



}

void FlyBug::Update(float _DeltaTime)
{
	GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
}