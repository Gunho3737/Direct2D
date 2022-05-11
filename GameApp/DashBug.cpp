#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>

#include <GameApp/BitMap.h>
#include "DashBug.h"
#include "Player.h"


DashBug::DashBug() // default constructer 디폴트 생성자
	: HP(10), Speed(300.0f), GetDamage(false), ImmuneTime(0.0f), JumpReadyTime(0.0f)
{

}

DashBug::~DashBug() // default destructer 디폴트 소멸자
{

}

void DashBug::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("MiddleBoss.png", "Idle", 6, 12, 0.1f);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 1200.0f, 1200.0f, 1.0f });

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 300.0f, 300.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 0.0f, 175.0f, -10.0f });

	ViewCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	ViewCollision->GetTransform()->SetLocalScaling(float4{ 1000.0f, 700.0f, 1.0f });
	ViewCollision->GetTransform()->SetLocalPosition({ 0.0f, 130.0f, -10.0f });

	RangeCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	RangeCollision->GetTransform()->SetLocalScaling(float4{ 1000.0f, 700.0f, 1.0f });
	RangeCollision->GetTransform()->SetLocalPosition({ 0.0f, 130.0f, -10.0f });



	StateManager_.CreateState("Idle", std::bind(&DashBug::Idle, this));
	StateManager_.CreateState("Walk", std::bind(&DashBug::Walk, this));
	StateManager_.CreateState("Death", std::bind(&DashBug::Death, this));
	StateManager_.CreateState("Dash", std::bind(&DashBug::Dash, this));


	StateManager_.ChangeState("Idle");

	StartX = GetTransform()->GetWorldPosition().x;

	SetCallBackFunc();
}

void DashBug::Update(float _DeltaTime)
{
	StateManager_.Update();

	if (true == GetLevel()->IsDebugCheck())
	{
		if (true == Collision->IsUpdate())
		{
			GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
		}

		if (true == ViewCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(ViewCollision->GetTransform(), CollisionType::Rect);
		}

		if (HP <= 0)
		{
			StateManager_.ChangeState("Death");
		}

		if (true == GetDamage)
		{
			ImmuneTime -= _DeltaTime;

			if (ImmuneTime <= 0.0f)
			{
				GetDamage = false;
				Collision->On();
			}
		}

		if (false == GetDamage)
		{
			Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::ATTACK,
				[&](GameEngineCollision* _OtherCollision)
				{
					HP -= 1;
					GetDamage = true;
					ImmuneTime = 0.3f;
					Collision->Off();
				}
			);
		}
	}
}

void DashBug::Idle()
{
	ImageRenderer->SetChangeAnimation("Idle");

	ViewCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
		{
			StateManager_.ChangeState("Walk");
		}
	);

}

void DashBug::Walk()
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MonsterPos = Collision->GetTransform()->GetWorldPosition();
	LeftRight PostDirection = Direction;

	ImageRenderer->SetChangeAnimation("Walk");


	if (PlayerPos.x >= MonsterPos.x)
	{
		Direction = LeftRight::RIGHT;
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
	}
	else if (PlayerPos.x < MonsterPos.x)
	{
		Direction = LeftRight::LEFT;
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}



	RangeCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
		{
			//StateManager_.ChangeState("JumpReady");
		}
	);

	if (-2.0f <= (PlayerPos.x - MonsterPos.x) &&
		2.0f >= (PlayerPos.x - MonsterPos.x)
		)
	{
		Direction = PostDirection;
	}

	DirectionCheck();
}


void DashBug::Death()
{
	ImageRenderer->SetChangeAnimation("Death");


	Collision->Off();
	ViewCollision->Off();
	RangeCollision->Off();

}

void DashBug::Dash()
{

}

void DashBug::SetCallBackFunc()
{

}

void DashBug::DirectionCheck()
{
	if (Direction == LeftRight::RIGHT)
	{
		//ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f });
	}
	else
	{
		//ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f } *= float4::XFLIP);
	}
}