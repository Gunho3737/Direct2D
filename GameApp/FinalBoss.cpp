#include "PreCompile.h"
#include "FinalBoss.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>

#include <GameApp/BitMap.h>
#include "Player.h"
#include "GroundWave.h"



FinalBoss::FinalBoss() // default constructer 디폴트 생성자
{

}

FinalBoss::~FinalBoss() // default destructer 디폴트 소멸자
{

}

void FinalBoss::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("FinalBoss.png", "Idle", 0, 4, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Walk", 10, 13, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "AttackReady", 24, 29, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Attack", 30, 32, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "AttackRecover", 33, 37, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Jump", 38, 42, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttack", 43, 44, 0.2f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttackRecover", 45, 48, 0.1f);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 1400.0f, 1400.0f, 1.0f });

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 300.0f, 300.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });

	RangeCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	RangeCollision->GetTransform()->SetLocalScaling(float4{ 500.0f, 500.0f, 1.0f });
	RangeCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });

	ViewCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	ViewCollision->GetTransform()->SetLocalScaling(float4{ 1200.0f, 700.0f, 1.0f });
	ViewCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });



	StateManager_.CreateState("Idle", std::bind(&FinalBoss::Idle, this));
	StateManager_.ChangeState("Idle");
}

void FinalBoss::Update(float _DeltaTime)
{
	StateManager_.Update();

	MapBotCollisionColor = BitMap::GetColor(GetTransform());


	if (true == GetLevel()->IsDebugCheck())
	{
		if (true == Collision->IsUpdate())
		{
			GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
		}

		if (true == RangeCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(RangeCollision->GetTransform(), CollisionType::Rect);
		}

		if (true == ViewCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(ViewCollision->GetTransform(), CollisionType::Rect);
		}

	//	if (true == AttackCollision->IsUpdate())
	//	{
	//		GetLevel()->PushDebugRender(AttackCollision->GetTransform(), CollisionType::Rect);
	//	}
	}
}

void FinalBoss::Idle() 
{
	ImageRenderer->SetChangeAnimation("Idle");
}

void FinalBoss::Walk() 
{}

void FinalBoss::AttackReady()
{}

void FinalBoss::Attack() 
{}

void FinalBoss::AttackRecover()
{}


void FinalBoss::Jump()
{}

void FinalBoss::JumpAttack()
{}

void FinalBoss::JumpAttackRecover()
{}

void FinalBoss::GetUp() 
{}

void FinalBoss::Death() 
{}

void FinalBoss::DirectionCheck()
{
	if (Direction == LeftRight::RIGHT)
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f });
		Collision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });
		RangeCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });
		ViewCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });
	}
	else
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f } *= float4::XFLIP);
		Collision->GetTransform()->SetLocalPosition({ -50.0f, 130.0f, -10.0f });
		RangeCollision->GetTransform()->SetLocalPosition({ -50.0f, 130.0f, -10.0f });
		ViewCollision->GetTransform()->SetLocalPosition({ -50.0f, 130.0f, -10.0f });
	}
}