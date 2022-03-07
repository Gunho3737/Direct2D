#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "Monster.h"
#include "Bullet.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::TestStartCallBack()
{
	int a = 0;
}

void Monster::TestEndCallBack()
{
	Death();
}

void Monster::Start()
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
//		PlayerImageRenderer->SetImage("Animation.png");
//	
//		//�߸� �̹����� ���° ��������Ʈ�� ������� ����(�ִϸ��̼��� �ƴ� )
//		PlayerImageRenderer->SetIndex(10);
//	
//		//�ִϸ��̼� ����
//		PlayerImageRenderer->CreateAnimation("Test", 0, 20, 0.5f);
//	
//		//�ִϸ��̼��� ù������/������ ������/�ִϸ��̼���x��°�������� ������ Ư�� �Լ��� ����ǵ����Ѵ�
//		PlayerImageRenderer->SetStartCallBack("Test", std::bind(&Monster::TestStartCallBack, this));
//		PlayerImageRenderer->SetEndCallBack("Test", std::bind(&Monster::TestEndCallBack, this));
//		PlayerImageRenderer->SetFrameCallBack("Test", 5, std::bind(&Monster::TestEndCallBack, this));
//	
//		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
//		PlayerImageRenderer->SetChangeAnimation("Test");
		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });


	}

	{
		GameEngineCollision* Collision = CreateTransformComponent<GameEngineCollision>(20);
		Collision->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });
	}

}

void Monster::Update(float _DeltaTime)
{

}