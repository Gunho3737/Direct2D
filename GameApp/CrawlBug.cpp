#include "PreCompile.h"
#include "CrawlBug.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>


CrawlBug::CrawlBug()
	: HP(3), Speed(50.0f), StartX(0.0f), MoveDistance(200.0f)
{

}

CrawlBug::~CrawlBug() // default destructer 디폴트 소멸자
{

}

void CrawlBug::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("CrawlBug.png", "Walk", 0, 3, 0.1f);
	ImageRenderer->SetChangeAnimation("Walk");
	ImageRenderer->GetTransform()->SetLocalScaling({ 250.0f, 250.0f, 1.0f });

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 80.0f, 80.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 0.0f, -0.0f, -10.0f });

	StateManager_.CreateState("Walk", std::bind(&CrawlBug::Walk, this));
	StateManager_.CreateState("Spin", std::bind(&CrawlBug::Spin, this));
	StateManager_.CreateState("Death", std::bind(&CrawlBug::Death, this));

	StateManager_.ChangeState("Walk");

	StartX = GetTransform()->GetWorldPosition().x;
}

void CrawlBug::Update(float _DeltaTime)
{
	StateManager_.Update();

	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
	}

	if (Direction == LeftRight::RIGHT)
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 250.0f, 250.0f, 1.0f });
	}
	else
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 250.0f, 250.0f, 1.0f } *= float4::XFLIP);
	}
}

void CrawlBug::Walk()
{
	ImageRenderer->SetChangeAnimation("Walk");


	switch (Direction)
	{
	case LeftRight::LEFT:
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		if ((StartX - (GetTransform()->GetWorldPosition().x)) >= MoveDistance)
		{
			Direction = LeftRight::RIGHT;
		}
	}
		break;
	case LeftRight::RIGHT:
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		if ((StartX - (GetTransform()->GetWorldPosition().x)) <= 0.0f)
		{
			Direction = LeftRight::LEFT;
		}
	}
		break;
	default:
		break;
	}

}

void CrawlBug::Spin()
{

}

void CrawlBug::Death()
{

}