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