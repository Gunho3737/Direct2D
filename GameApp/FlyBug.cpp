#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "FlyBug.h"
#include <GameApp/Map.h>



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

void FlyBug::Die()
{
	Off();
}

void FlyBug::Start()
{
	{
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->SetImage("FlyBug.png");
		//	
		//		//�߸� �̹����� ���° ��������Ʈ�� ������� ����(�ִϸ��̼��� �ƴ� )
		//		PlayerImageRenderer->SetIndex(10);
		//	

		//�ִϸ��̼� ����
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Idle", 1, 6, 0.1f);
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Die", 21, 23, 0.1f);
		//	
		//		//�ִϸ��̼��� ù������/������ ������/�ִϸ��̼���x��°�������� ������ Ư�� �Լ��� ����ǵ����Ѵ�
		//		PlayerImageRenderer->SetStartCallBack("Test", std::bind(&FlyBug::TestStartCallBack, this));
		PlayerImageRenderer->SetEndCallBack("Die", std::bind(&FlyBug::Die, this));
		//		PlayerImageRenderer->SetFrameCallBack("Test", 5, std::bind(&FlyBug::TestEndCallBack, this));

		PlayerImageRenderer->SetChangeAnimation("Idle");
		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 300.0f, 300.0f, 1.0f });


	}

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 100.0f, 90.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({-10.0f, 40.0f, -10.0f});



}

void FlyBug::Update(float _DeltaTime)
{

	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
	}

	//Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::ATTACK,
	//	[this](GameEngineCollision* _OtherCollision)
	//	{
	//		if (HP <= 0)
	//		{
	//			PlayerImageRenderer->SetChangeAnimation("Die");
	//		}
	//		HP -= 1;
	//	}
	//);
}