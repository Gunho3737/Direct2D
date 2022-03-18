#include "PreCompile.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include "Attack.h"
#include "GameEngine/GameEngineCollision.h"
#include "Player.h"

Attack::Attack()
{
}

Attack::~Attack()
{
}



void Attack::Start()
{

	// 정말 세팅해줘야할게 많은 녀석입니다.
	// 랜더러로서 뭐든지 다 그릴수있는 가능성을 가지고 있는 녀석.
	{
		ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		ImageRenderer->CreateAnimationFolder("SlashEffect", "SlashEffect", 0.02f);
		ImageRenderer->SetChangeAnimation("SlashEffect");
		ImageRenderer->GetTransform()->SetLocalScaling({157.0f,114.0f, 1.0f});
	//	ImageRenderer->GetTransform()->SetLocalPosition(/*플레이어의 위치*/);

	}

	{
		Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::ATTACK));
		Collision->GetTransform()->SetLocalScaling(float4{ 157.0f, 114.0f, 1.0f });
		Collision->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -10.0f });
	}
}

void Attack::Update(float _DeltaTime)
{
	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
	}
	//ImageRenderer->GetTransform()->SetLocalPosition(/*플레이어의 위치*/);


	ImageRenderer->SetEndCallBack("SlashEffect", [this]()
		{
		Death();

		}
	);
}