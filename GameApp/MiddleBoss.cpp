#include "PreCompile.h"
#include "MiddleBoss.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>


MiddleBoss::MiddleBoss() // default constructer 디폴트 생성자
{

}

MiddleBoss::~MiddleBoss() // default destructer 디폴트 소멸자
{

}

void MiddleBoss::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("MiddleBoss.png", "Idle", 6, 12, 0.1f);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "Walk", 15, 24, 0.1f);
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

	StateManager_.CreateState("Idle", std::bind(&MiddleBoss::Idle, this));

	StateManager_.ChangeState("Idle");

	StartX = GetTransform()->GetWorldPosition().x;
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

void MiddleBoss::Idle()
{
	ImageRenderer->SetChangeAnimation("Idle");
}

void  MiddleBoss::Wake()
{}

void  MiddleBoss::Walk()
{
	//ImageRenderer->SetChangeAnimation("Walk");
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
