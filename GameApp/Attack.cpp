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

	// ���� ����������Ұ� ���� �༮�Դϴ�.
	// �������μ� ������ �� �׸����ִ� ���ɼ��� ������ �ִ� �༮.
	{
		ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		ImageRenderer->CreateAnimationFolder("SlashEffect", "SlashEffect", 0.02f);
		ImageRenderer->SetChangeAnimation("SlashEffect");
		ImageRenderer->GetTransform()->SetLocalScaling({157.0f,114.0f, 1.0f});
	//	ImageRenderer->GetTransform()->SetLocalPosition(/*�÷��̾��� ��ġ*/);

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
	//ImageRenderer->GetTransform()->SetLocalPosition(/*�÷��̾��� ��ġ*/);


	ImageRenderer->SetEndCallBack("SlashEffect", [this]()
		{
		Death();

		}
	);
}