#include "PreCompile.h"
#include "GroundWave.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>


GroundWave::GroundWave()
	: Speed(800.0f)
{

}

GroundWave::~GroundWave() // default destructer 디폴트 소멸자
{

}

void GroundWave::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	ImageRenderer->SetImage("BossGroundWave.png");
	ImageRenderer->GetTransform()->SetLocalScaling(float4{300.0f,150.0f, 1.0f});

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 300.0f, 150.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -10.0f });
}

void GroundWave::Update(float _DeltaTime)
{
	if (true == GetLevel()->IsDebugCheck())
	{
		if (true == Collision->IsUpdate())
		{
			GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
		}
	}

	switch (Direction)
	{
	case LeftRight::LEFT:
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}
		break;
	case LeftRight::RIGHT:
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
	}
		break;
	default:
		break;
	}

	Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::MONSTERMOVESTOP,
		[&](GameEngineCollision* _OtherCollision)
		{
			Death();
		}
	);
}