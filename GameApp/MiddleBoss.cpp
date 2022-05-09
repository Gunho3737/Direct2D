#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>

#include <GameApp/BitMap.h>
#include "MiddleBoss.h"
#include "Player.h"


MiddleBoss::MiddleBoss() // default constructer 디폴트 생성자
	: HP(15), Speed(300.0f)
{

}

MiddleBoss::~MiddleBoss() // default destructer 디폴트 소멸자
{

}

void MiddleBoss::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("MiddleBoss.png", "Idle", 6, 12, 0.1f);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "Wait", 6, 12, 0.1f);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "Walk", 15, 24, 0.05f);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "Attack", 39, 48, 0.05f);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 1200.0f, 1200.0f, 1.0f });

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 350.0f, 350.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 0.0f, 175.0f, -10.0f });

	RangeCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	RangeCollision->GetTransform()->SetLocalScaling(float4{ 700.0f, 700.0f, 1.0f });
	RangeCollision->GetTransform()->SetLocalPosition({ 0.0f, 175.0f, -10.0f });

	ViewCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	ViewCollision->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f });
	ViewCollision->GetTransform()->SetLocalPosition({ 0.0f, 175.0f, -10.0f });

	AttackCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	//AttackCollision->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f });
	//AttackCollision->GetTransform()->SetLocalPosition({ 0.0f, 175.0f, -10.0f });

	StateManager_.CreateState("Wait", std::bind(&MiddleBoss::Wait, this));
	StateManager_.CreateState("Idle", std::bind(&MiddleBoss::Idle, this));
	StateManager_.CreateState("Walk", std::bind(&MiddleBoss::Walk, this));

	StateManager_.ChangeState("Idle");

	StartX = GetTransform()->GetWorldPosition().x;

	SetCallBackFunc();
}

void MiddleBoss::Update(float _DeltaTime)
{
	StateManager_.Update();

	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(RangeCollision->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(ViewCollision->GetTransform(), CollisionType::Rect);
	}

}

void MiddleBoss::Wait()
{
	if (PrevState_ == "Walk")
	{
		ImageRenderer->SetChangeAnimation("Wait");
		return;
	}
}

void MiddleBoss::Idle()
{
	ImageRenderer->SetChangeAnimation("Idle");


	ViewCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
		{
			PrevState_ = "Idle";
			StateManager_.ChangeState("Walk");
		}
	);
}

void  MiddleBoss::Walk()
{
	ImageRenderer->SetChangeAnimation("Walk");


	if (Player::MainPlayer->GetTransform()->GetWorldPosition().x >= Collision->GetTransform()->GetWorldPosition().x)
	{
		Direction = LeftRight::RIGHT;
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
	}
	else if (Player::MainPlayer->GetTransform()->GetWorldPosition().x < Collision->GetTransform()->GetWorldPosition().x)
	{
		Direction = LeftRight::LEFT;
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}

	RangeCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
		{
			PrevState_ = "Walk";
			StateManager_.ChangeState("Wait");
		}
	);


	DirectionCheck();

}

void  MiddleBoss::Turn()
{}

void  MiddleBoss::Attack()
{}

void  MiddleBoss::JumpReady()
{}

void  MiddleBoss::Jump()
{}

void  MiddleBoss::GetUp()
{}

void  MiddleBoss::Death()
{}

void MiddleBoss::SetCallBackFunc()
{

}

void MiddleBoss::DirectionCheck()
{
	if (Direction == LeftRight::RIGHT)
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f });
	}
	else
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f } *= float4::XFLIP);
	}
}