#include "PreCompile.h"
#include "CollapseFloor.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>

CollapseFloor* CollapseFloor::FinalBossRoomFloor = nullptr;

CollapseFloor::CollapseFloor() // default constructer 디폴트 생성자
{

}

CollapseFloor::~CollapseFloor() // default destructer 디폴트 소멸자
{

}

void CollapseFloor::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->SetImage("CollapseFloor_2.png");
	ImageRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize());

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::FLOOR));
	Collision->GetTransform()->SetLocalScaling({1000.0f, 30.0f});
	Collision->GetTransform()->SetLocalPosition({0.0f,140.0f,-10.0f });
	{
		CollapseFloorPieces.reserve(12);
		for (int i = 0; i < 10; i++)
		{
		GameEngineImageRenderer* ImageRenderer = nullptr;
		ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		int RockNumber = i % 4;
		
		switch (RockNumber)
		{
		case 0:
			ImageRenderer->SetImage("rock_00.png");
			break;
		case 1:
			ImageRenderer->SetImage("rock_01.png");
			break;
		case 2:
			ImageRenderer->SetImage("rock_02.png");
			break;
		case 3:
			ImageRenderer->SetImage("rock_03.png");
			break;
		default:
			break;
		}
		ImageRenderer->GetTransform()->SetLocalScaling(float4{20.0f, 20.0f, 1.0f});
		ImageRenderer->Off();
		CollapseFloorPieces.push_back(ImageRenderer);
		}
	}
}

void CollapseFloor::Update(float _DeltaTime)
{
	if (true == GetLevel()->IsDebugCheck())
	{
		if (true == Collision->IsUpdate())
		{
			GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
		}
	}

	//Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
	//	[&](GameEngineCollision* _OtherCollision)
	//	{
	//		ImageRenderer->Off();
	//		Collision->Off();
	//	}
	//);
}