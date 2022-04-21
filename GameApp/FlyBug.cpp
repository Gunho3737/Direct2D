#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "FlyBug.h"
#include <GameApp/BitMap.h>



FlyBug::FlyBug()
	: HP(3), Immune(false), ImmuneTime(0.5f)
{
}

FlyBug::~FlyBug()
{
}


void FlyBug::Start()
{
	{
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->SetImage("FlyBug.png");
		//	
		//		//잘린 이미지중 몇번째 스프라이트를 사용할지 선택(애니메이션이 아닌 )
		//		PlayerImageRenderer->SetIndex(10);
		//	

		//애니메이션 제작
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Idle", 1, 6, 0.1f);
		PlayerImageRenderer->CreateAnimation("FlyBug.png", "Die", 21, 23, 0.1f);
		//	
		//		//애니메이션의 첫프레임/마지막 프레임/애니메이션의x번째프레임을 지정해 특정 함수가 실행되도록한다
		//		PlayerImageRenderer->SetStartCallBack("Test", std::bind(&FlyBug::TestStartCallBack, this));
		//		PlayerImageRenderer->SetFrameCallBack("Test", 5, std::bind(&FlyBug::TestEndCallBack, this));

		PlayerImageRenderer->SetChangeAnimation("Idle");
		PlayerImageRenderer->GetTransform()->SetLocalScaling({ 300.0f, 300.0f, 1.0f });


	}

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 100.0f, 90.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({-10.0f, 40.0f, -10.0f});

	StateManager_.CreateState("Idle", std::bind(&FlyBug::Idle, this));
	StateManager_.CreateState("Die", std::bind(&FlyBug::Die, this));
	StateManager_.CreateState("Attack", std::bind(&FlyBug::Attack, this));

	StateManager_.ChangeState("Idle");


}

void FlyBug::Update(float _DeltaTime)
{
	StateManager_.Update();

	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
	}

	if (HP <= 0)
	{
		StateManager_.ChangeState("Die");
	}

	Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::ATTACK,
		[this](GameEngineCollision* _OtherCollision)
		{
			if (true == Immune)
			{
				return;
			}
			else if (false == Immune)
			{
				HP -= 1;
				Immune = true;
			}


		}
	);


	if (true == Immune)
	{
		GetLevel()->AddTimeEvent(0.7f, std::bind(&FlyBug::ImmuneOff, this));
	}
}

void FlyBug::ImmuneOff()
{ 
	if (Immune == false)
	{
		return;
	}
	else if (Immune == true)
	{
		Immune = false;
	}
}

void FlyBug::Idle()
{
	PlayerImageRenderer->SetChangeAnimation("Idle");
}

void FlyBug::Die()
{
	PlayerImageRenderer->SetChangeAnimation("Die");

	PlayerImageRenderer->SetEndCallBack("Die", [&]()
		{
			StateManager_.ChangeState("Idle");
			Off();
		}
	);

}

void FlyBug::Attack()
{

}