#include "PreCompile.h"
#include "CollapseFloor.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>


CollapseFloor::CollapseFloor() // default constructer ����Ʈ ������
{

}

CollapseFloor::~CollapseFloor() // default destructer ����Ʈ �Ҹ���
{

}

void CollapseFloor::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	//ImageRenderer->SetImage("CollapseFloor_2.png");
	//ImageRenderer->GetTransform()->SetLocalScaling(ImageRenderer->GetCurrentTexture()->GetTextureSize());

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::FLOOR));
	Collision->GetTransform()->SetLocalScaling({1000.0f, 30.0f});
	Collision->GetTransform()->SetLocalPosition({0.0f,140.0f,-10.0f });
	//1600,1040
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