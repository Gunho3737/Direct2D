#include "PreCompile.h"
#include "Door.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>


Door::Door()
	: DoorOn(false)
{

}

Door::~Door() // default destructer 디폴트 소멸자
{

}

void Door::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	ImageRenderer->CreateAnimation("Door.png", "DoorDown", 0, 4, 0.1f, false);
	ImageRenderer->CreateAnimation("Door.png", "DoorOff", 6, 11, 0.1f, false);
	ImageRenderer->GetTransform()->SetLocalScaling(float4{100.0f, 300.0f, 1.0f});
	ImageRenderer->SetChangeAnimation("DoorOff");

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::WALL));
	Collision->GetTransform()->SetLocalScaling({ 50.0f, 300.0f });
	Collision->Off();
}

void Door::Update(float _DeltaTime)
{
	if (true == GetLevel()->IsDebugCheck())
	{
		if (true == Collision->IsUpdate())
		{
			GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
		}
	}

	if (DoorOn == true)
	{
		ImageRenderer->SetChangeAnimation("DoorDown");
		Collision->On();
	}
	else if (DoorOn == false)
	{
		ImageRenderer->SetChangeAnimation("DoorOff");
		Collision->Off();
	}
}