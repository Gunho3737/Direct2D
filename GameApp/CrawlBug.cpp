#include "PreCompile.h"
#include "CrawlBug.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>


CrawlBug::CrawlBug() // default constructer ����Ʈ ������
{

}

CrawlBug::~CrawlBug() // default destructer ����Ʈ �Ҹ���
{

}

void CrawlBug::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("CrawlBug.png", "Walk", 0, 3, 0.1f);
	ImageRenderer->SetChangeAnimation("Walk");
	ImageRenderer->GetTransform()->SetLocalScaling({ 250.0f, 250.0f, 1.0f });

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 100.0f, 90.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -10.0f });

	StateManager_.CreateState("Walk", std::bind(&CrawlBug::Walk, this));
	StateManager_.CreateState("Spin", std::bind(&CrawlBug::Spin, this));
	StateManager_.CreateState("Death", std::bind(&CrawlBug::Death, this));

	StateManager_.ChangeState("Walk");
}

void CrawlBug::Update(float _DeltaTime)
{
	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
	}

	if (Direction == LeftRight::LEFT)
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
}

void CrawlBug::Spin()
{

}

void CrawlBug::Death()
{

}