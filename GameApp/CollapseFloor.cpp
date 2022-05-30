#include "PreCompile.h"
#include "CollapseFloor.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>

CollapseFloor* CollapseFloor::FinalBossRoomFloor = nullptr;
bool CollapseFloor::CollapseOn = false;

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

	CollapseImageRenderer0 = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	CollapseImageRenderer0->SetImage("breakfloor_00.png");
	CollapseImageRenderer0->GetTransform()->SetLocalScaling(CollapseImageRenderer0->GetCurrentTexture()->GetTextureSize());
	CollapseImageRenderer0->GetTransform()->SetLocalPosition({ -300.0f,-50.0f,0.0f });
	CollapseImageRenderer0->Off();

	CollapseImageRenderer1 = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	CollapseImageRenderer1->SetImage("breakfloor_01.png");
	CollapseImageRenderer1->GetTransform()->SetLocalScaling(CollapseImageRenderer1->GetCurrentTexture()->GetTextureSize());
	CollapseImageRenderer1->GetTransform()->SetLocalPosition({ 0.0f,0.0f,0.0f });
	CollapseImageRenderer1->Off();

	CollapseImageRenderer2 = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	CollapseImageRenderer2->SetImage("breakfloor_02.png");
	CollapseImageRenderer2->GetTransform()->SetLocalScaling(CollapseImageRenderer2->GetCurrentTexture()->GetTextureSize());
	CollapseImageRenderer2->GetTransform()->SetLocalPosition({ 300.0f,100.0f,0.0f });
	CollapseImageRenderer2->Off();

	//{
	//	CollapseFloorPieces.reserve(20);
	//	for (int i = 0; i < 15; i++)
	//	{
	//	GameEngineImageRenderer* ImageRenderer = nullptr;
	//	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	//	int RockNumber = i % 4;
	//	float RockLine = (float)(i / 4);
	//	ImageRenderer->GetTransform()->SetLocalScaling(float4{ 20.0f, 20.0f, 1.0f });
	//
	//	switch (RockNumber)
	//	{
	//	case 0:
	//		ImageRenderer->SetImage("rock_00.png");
	//		break;
	//	case 1:
	//		ImageRenderer->SetImage("rock_01.png");
	//		break;
	//	case 2:
	//		ImageRenderer->SetImage("rock_02.png");
	//		break;
	//	case 3:
	//		ImageRenderer->SetImage("rock_03.png");
	//		break;
	//	default:
	//		break;
	//	}
	//
	//	float FRockNumber = (float)RockNumber;
	//	ImageRenderer->GetTransform()->SetLocalPosition(float4{ FRockNumber *= 70.0f, RockLine *= 70.0f});
	//	//ImageRenderer->Off();
	//	CollapseFloorPieces.push_back(ImageRenderer);
	//	}
    //
	//}
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

	if (CollapseFloor::CollapseOn == true)
	{
		Collision->Off();
		ImageRenderer->Off();
		CollapseImageRenderer0->On();
		CollapseImageRenderer1->On();
		CollapseImageRenderer2->On();
	
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 1000.0f);

		if (-2500.0f >= GetTransform()->GetLocalPosition().y)
		{
			CollapseImageRenderer0->Off();
			CollapseImageRenderer1->Off();
			CollapseImageRenderer2->Off();
		}


	}

}