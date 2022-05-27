#include "PreCompile.h"
#include "CrawlBug.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include <GameApp/BitMap.h>
#include "Player.h"

CrawlBug::CrawlBug()
	: HP(3), Speed(50.0f), StartX(0.0f), MoveDistance(200.0f), SpinTime(0.0f), ImmuneTime(0.0f)
{

}

CrawlBug::~CrawlBug() // default destructer 디폴트 소멸자
{

}

void CrawlBug::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("CrawlBug.png", "Walk", 0, 3, 0.1f);
	ImageRenderer->CreateAnimation("CrawlBug.png", "Spin", 6, 12, 0.03f);
	ImageRenderer->CreateAnimation("CrawlBug.png", "Death", 13, 14, 0.1f);
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

	{
		DeathEffectRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

		DeathEffectRenderer->CreateAnimationFolder("MonsterStunEffect", "CrawlBugStun", 0.07f, false);
		DeathEffectRenderer->SetChangeAnimation("CrawlBugStun");
		DeathEffectRenderer->GetTransform()->SetLocalScaling(DeathEffectRenderer->GetFolderTextureImageSize());
		DeathEffectRenderer->GetTransform()->SetLocalPosition(float4{ 0.0f, 50.0f, 0.0f });
		DeathEffectRenderer->Off();


		DeathEffectRenderer->SetEndCallBack("CrawlBugStun", [&]()
			{
				DeathEffectRenderer->Off();
			}
		);
	}
}

void CrawlBug::Update(float _DeltaTime)
{
	StateManager_.Update(_DeltaTime);

	MapBotCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 0.0f, 0.0f});

	//스프라이트는 렌더러의 절반부분이 머리가된다
	MapTopCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 125.0f, 0.0f});
	MapLeftCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {-30.0f, 0.0f, 0.0f});
	MapRightCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {30.0f, 0.0f, 0.0f});

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


	if (HP <= 0)
	{
		SpinTime = 0.2f;
		HP = 99;
		DeathEffectRenderer->On();
		DeathEffectRenderer->SetChangeAnimation("CrawlBugStun", true);
		StateManager_.ChangeState("Spin");
	}

	if (true == GetDamage)
	{
		ImmuneTime -= _DeltaTime;

		float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		float4 MonsterPos = Collision->GetTransform()->GetWorldPosition();

		if (PlayerPos.x < MonsterPos.x)
		{
			if (MapRightCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 300.0f);
			}
		}
		else if (PlayerPos.x >= MonsterPos.x)
		{
			if (MapLeftCollisionColor != float4::BLACK)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 300.0f);
			}
		}

		if (ImmuneTime <= 0.0f)
		{
			GetDamage = false;
			Collision->On();
			ImageRenderer->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
		}
	}

	if (false == GetDamage)
	{
		Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::ATTACK,
			[&](GameEngineCollision* _OtherCollision)
			{
				HP -= 1;
				GetDamage = true;
				ImmuneTime = 0.2f;
				Collision->Off();
				if ("Death" != ImageRenderer->GetCurrentAnimationName())
				{
					ImageRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
				}
			}
		);
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
	ImageRenderer->SetChangeAnimation("Spin");
	Collision->Off();

	SpinTime -= GameEngineTime::GetInst().GetDeltaTime();

	if (Direction == LeftRight::LEFT)
	{
		if (MapRightCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 500.0f);
		}
	}
	else if (Direction == LeftRight::RIGHT)
	{
		if (MapLeftCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 500.0f);
		}
	}

	if (SpinTime <= 0.0f)
	{
		StateManager_.ChangeState("Death");
	}
}

void CrawlBug::Death()
{
	ImageRenderer->SetChangeAnimation("Death");

	if (Direction == LeftRight::LEFT)
	{
		if (MapRightCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 500.0f);
		}
	}
	else if (Direction == LeftRight::RIGHT)
	{
		if (MapLeftCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 500.0f);
		}
	}

	if (MapBotCollisionColor != float4::BLACK)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 500.0f);
	}

	ImageRenderer->SetEndCallBack("Death", [&]()
		{
			StateManager_.ChangeState("Walk");
			Off();
		}
	);
}