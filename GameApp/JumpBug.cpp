#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>

#include <GameApp/BitMap.h>
#include "JumpBug.h"
#include "Player.h"


JumpBug::JumpBug() // default constructer 디폴트 생성자
	: HP(1), Speed(150.0f), GetDamage(false), ImmuneTime(0.0f), JumpReadyTime(0.0f)
{

}

JumpBug::~JumpBug() // default destructer 디폴트 소멸자
{

}

void JumpBug::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("JumpBug.png", "Idle", 0, 5, 0.1f);
	ImageRenderer->CreateAnimation("JumpBug.png", "Walk", 6, 12, 0.1f);
	ImageRenderer->CreateAnimation("JumpBug.png", "Death", 28, 36, 0.1f, false);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 500.0f, 500.0f, 1.0f });

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 90.0f, 200.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 0.0f, 100.0f, -10.0f });

	ViewCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	ViewCollision->GetTransform()->SetLocalScaling(float4{ 700.0f, 350.0f, 1.0f });
	ViewCollision->GetTransform()->SetLocalPosition({ 0.0f, 100.0f, -10.0f });

	RangeCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	RangeCollision->GetTransform()->SetLocalScaling(float4{ 300.0f, 300.0f, 1.0f });
	RangeCollision->GetTransform()->SetLocalPosition({ 0.0f, 100.0f, -10.0f });



	StateManager_.CreateState("Idle", std::bind(&JumpBug::Idle, this));
	StateManager_.CreateState("Walk", std::bind(&JumpBug::Walk, this));
	StateManager_.CreateState("Death", std::bind(&JumpBug::Death, this));
	StateManager_.CreateState("JumpReady", std::bind(&JumpBug::JumpReady, this));
	StateManager_.CreateState("Jump", std::bind(&JumpBug::Jump, this));
	

	StateManager_.ChangeState("Idle");

	SetCallBackFunc();
}

void JumpBug::Update(float _DeltaTime)
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

		if (true == RangeCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(RangeCollision->GetTransform(), CollisionType::Rect);
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

void JumpBug::Idle()
{
	ImageRenderer->SetChangeAnimation("Idle");

	ViewCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
		{
			StateManager_.ChangeState("Walk");
		}
	);

}

void JumpBug::Walk()
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

void JumpBug::JumpReady()
{
	ImageRenderer->SetChangeAnimation("JumpReady");

	JumpReadyTime -= GameEngineTime::GetInst().GetDeltaTime();

	if (JumpReadyTime <= 0.0f)
	{
		StateManager_.ChangeState("Jump");
	}


}

void JumpBug::Jump()
{
	ImageRenderer->SetChangeAnimation("Jump");

	if (Direction == LeftRight::RIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 400.0f);
	}
	else
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 400.0f);
	}
}

void JumpBug::Death()
{
	ImageRenderer->SetChangeAnimation("Death");


	Collision->Off();
	ViewCollision->Off();
	RangeCollision->Off();

}

void JumpBug::SetCallBackFunc()
{

}

void JumpBug::DirectionCheck()
{
	if (Direction == LeftRight::LEFT)
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 500.0f, 500.0f, 1.0f } );
	}
	else
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 500.0f, 500.0f, 1.0f } *= float4::XFLIP);
	}
}