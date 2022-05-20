#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>

#include <GameApp/BitMap.h>
#include "MiddleBoss.h"
#include "Player.h"
#include "GroundWave.h"


MiddleBoss::MiddleBoss() // default constructer 디폴트 생성자
	: HP(10), Speed(300.0f), GetDamage(false), ImmuneTime(0.0f), TurnOn(false), GroundAttackCount(0), JumpReadyTime(0.0f), TurnTime(0.0f)
{

}

MiddleBoss::~MiddleBoss() // default destructer 디폴트 소멸자
{

}

void MiddleBoss::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("MiddleBoss.png", "Idle", 6, 12, 0.1f);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "Wait", 6, 12, 0.1f);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "Walk", 15, 24, 0.05f);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "Attack", 39, 48, 0.1f,false);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "Death", 64, 74, 0.1f, false);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "JumpReady", 51, 54, 0.05f, false);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "Jump", 55, 57, 0.07f, false);
	ImageRenderer->CreateAnimation("MiddleBoss.png", "GetUp", 58, 63, 0.07f, false);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 1200.0f, 1200.0f, 1.0f });


	AttackEffectRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AttackEffectRenderer->CreateAnimation("MiddleBoss.png", "SmashEffectBack", 49, 49, 0.05f);
	AttackEffectRenderer->CreateAnimation("MiddleBoss.png", "SmashEffectFront", 50, 50, 0.05f);
	AttackEffectRenderer->SetChangeAnimation("SmashEffectBack");

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 270.0f, 270.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 0.0f, 175.0f, -10.0f });

	RangeCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	RangeCollision->GetTransform()->SetLocalScaling(float4{ 500.0f, 500.0f, 1.0f });
	RangeCollision->GetTransform()->SetLocalPosition({ 0.0f, 130.0f, -10.0f });

	ViewCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	ViewCollision->GetTransform()->SetLocalScaling(float4{ 1000.0f, 700.0f, 1.0f });
	ViewCollision->GetTransform()->SetLocalPosition({ 0.0f, 130.0f, -10.0f });

	TurnCheckCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));

	AttackCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));

	TurnCheckCollision->Off();
	AttackEffectRenderer->Off();
	AttackCollision->Off();


	StateManager_.CreateState("Wait", std::bind(&MiddleBoss::Wait, this));
	StateManager_.CreateState("Idle", std::bind(&MiddleBoss::Idle, this));
	StateManager_.CreateState("Walk", std::bind(&MiddleBoss::Walk, this));
	StateManager_.CreateState("Attack", std::bind(&MiddleBoss::Attack, this));
	StateManager_.CreateState("Death", std::bind(&MiddleBoss::Death, this));
	StateManager_.CreateState("JumpReady", std::bind(&MiddleBoss::JumpReady, this));
	StateManager_.CreateState("Jump", std::bind(&MiddleBoss::Jump, this));
	StateManager_.CreateState("GetUp", std::bind(&MiddleBoss::GetUp, this));
	

	StateManager_.ChangeState("Idle");

	SetCallBackFunc();
}

void MiddleBoss::Update(float _DeltaTime)
{
	StateManager_.Update();

	if (true == GetLevel()->IsDebugCheck())
	{
		if (true == Collision->IsUpdate())
		{
			GetLevel()->PushDebugRender(Collision->GetTransform(), CollisionType::Rect);
		}

		if (true == RangeCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(RangeCollision->GetTransform(), CollisionType::Rect);
		}

		if (true == ViewCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(ViewCollision->GetTransform(), CollisionType::Rect);
		}

		if (true == AttackCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(AttackCollision->GetTransform(), CollisionType::Rect);
		}

		if (true == TurnCheckCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(TurnCheckCollision->GetTransform(), CollisionType::Rect);
		}
	}

	if (TurnOn == true)
	{
		TurnTime -= _DeltaTime;

		if (TurnTime <= 0.0f)
		{
			TurnOn = false;
		}
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

void MiddleBoss::Wait()
{
	ImageRenderer->SetChangeAnimation("Wait");


	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MonsterPos = Collision->GetTransform()->GetWorldPosition();

	switch (Direction)
	{
	case LeftRight::LEFT:
	{
	TurnCheckCollision->GetTransform()->SetLocalScaling(float4{ 500.0f, 700.0f, 1.0f });
	TurnCheckCollision->GetTransform()->SetLocalPosition({ 250.0f, 130.0f, -10.0f });
	}
		break;
	case LeftRight::RIGHT:
	{
		TurnCheckCollision->GetTransform()->SetLocalScaling(float4{ 500.0f, 700.0f, 1.0f });
		TurnCheckCollision->GetTransform()->SetLocalPosition({ -250.0f, 130.0f, -10.0f });
	}
		break;
	default:
		break;
	}


	TurnCheckCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
			{
			TurnTime = 0.5f;
			TurnOn = true;
			
			if (Direction == LeftRight::RIGHT)
			{
				Direction = LeftRight::LEFT;
			}
			else
			{
				Direction = LeftRight::RIGHT;
			}
			
			StateManager_.ChangeState("Walk");
			}
		);
	
}

void MiddleBoss::Idle()
{
	ImageRenderer->SetChangeAnimation("Idle");


	ViewCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
		{
			StateManager_.ChangeState("Walk");
		}
	);


}

void  MiddleBoss::Walk()
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
			StateManager_.ChangeState("Attack");
		}
	);

	//회전후 일정 시간이 지나서 TurnOn이 꺼진 상태에서만 막힌다
	if (TurnOn == false)
	{
		RangeCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::MONSTERMOVESTOP,
			[this](GameEngineCollision* _OtherCollision)
			{
				TurnCheckCollision->On();
				StateManager_.ChangeState("Wait");
			}
		);
	}

	if (-2.0f <= (PlayerPos.x - MonsterPos.x) &&
		2.0f >= (PlayerPos.x - MonsterPos.x)
		)
	{
		Direction = PostDirection;
	}

	DirectionCheck();
}

void  MiddleBoss::Attack()
{
	ImageRenderer->SetChangeAnimation("Attack");
}

void  MiddleBoss::JumpReady()
{
	ImageRenderer->SetChangeAnimation("JumpReady");

	JumpReadyTime -= GameEngineTime::GetInst().GetDeltaTime();

	if (JumpReadyTime <= 0.0f)
	{
		StateManager_.ChangeState("Jump");
	}


}

void  MiddleBoss::Jump()
{
	ImageRenderer->SetChangeAnimation("Jump");

	if (Direction == LeftRight::RIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 400.0f);
	}
	else
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 400.0f);
	}
}

void  MiddleBoss::GetUp()
{
	ImageRenderer->SetChangeAnimation("GetUp");
}

void  MiddleBoss::Death()
{
	ImageRenderer->SetChangeAnimation("Death");


	Collision->Off();
	ViewCollision->Off();
	RangeCollision->Off();
	AttackCollision->Off();
	TurnCheckCollision->Off();

}

void MiddleBoss::SetCallBackFunc()
{
	//Attack 관련 콜백함수
	{
		ImageRenderer->SetFrameCallBack("Attack", 43, [&]()
			{
				AttackEffectRenderer->On();

				AttackEffectRenderer->SetChangeAnimation("SmashEffectBack");

				if (Direction == LeftRight::LEFT)
				{
					AttackEffectRenderer->GetTransform()->SetLocalScaling(float4{ -1200.0f, 1200.0f, 1.0f });
					AttackEffectRenderer->GetTransform()->SetLocalPosition(ImageRenderer->GetTransform()->GetLocalPosition() += {200.0f, 0.0f, 10.0f});
				}
				else if (Direction == LeftRight::RIGHT)
				{
					{
						AttackEffectRenderer->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f });
						AttackEffectRenderer->GetTransform()->SetLocalPosition(ImageRenderer->GetTransform()->GetLocalPosition() += {-200.0f, 0.0f, 10.0f});
					}
				}
			}
		);

		ImageRenderer->SetFrameCallBack("Attack", 44, [&]()
			{

				AttackEffectRenderer->SetChangeAnimation("SmashEffectFront");

				if (Direction == LeftRight::LEFT)
				{
					AttackEffectRenderer->GetTransform()->SetLocalScaling(float4{ -1200.0f, 1200.0f, 1.0f });
					AttackEffectRenderer->GetTransform()->SetLocalPosition(ImageRenderer->GetTransform()->GetLocalPosition() += {-200.0f, 0.0f, 10.0f});
				}
				else if (Direction == LeftRight::RIGHT)
				{
					{
						AttackEffectRenderer->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f });
						AttackEffectRenderer->GetTransform()->SetLocalPosition(ImageRenderer->GetTransform()->GetLocalPosition() += {200.0f, 0.0f, 10.0f});
					}
				}

				AttackCollision->On();

				if (Direction == LeftRight::LEFT)
				{
					AttackCollision->GetTransform()->SetLocalScaling(float4{ 300.0f, 600.0f, 1.0f });
					AttackCollision->GetTransform()->SetLocalPosition(ImageRenderer->GetTransform()->GetLocalPosition() += {-200.0f, 0.0f, -1.0f});
				}
				else if (Direction == LeftRight::RIGHT)
				{
					AttackCollision->GetTransform()->SetLocalScaling(float4{ 300.0f,600.0f, 1.0f });
					AttackCollision->GetTransform()->SetLocalPosition(ImageRenderer->GetTransform()->GetLocalPosition() += {200.0f, 0.0f, -1.0f});
				}
			}
		);

		ImageRenderer->SetFrameCallBack("Attack", 45, [&]()
			{
				AttackEffectRenderer->Off();
				AttackCollision->Off();
			}
		);

		ImageRenderer->SetEndCallBack("Attack", [&]()
			{
				StateManager_.ChangeState("Walk");
				GroundAttackCount += 1;

				if (GroundAttackCount >= 2)
				{
					JumpReadyTime = 0.5f;
					StateManager_.ChangeState("JumpReady");
				}
			}
		);
	}

		ImageRenderer->SetEndCallBack("Jump", [&]()
			{
				StateManager_.ChangeState("GetUp");
				GroundWave* WaveAttackLeft = GetLevel()->CreateActor<GroundWave>();
				WaveAttackLeft->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() += {0.0f, 55.0f, -2.0f});
				WaveAttackLeft->Direction = LeftRight::LEFT;

				GroundWave* WaveAttackRight = GetLevel()->CreateActor<GroundWave>();
				WaveAttackRight->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() += {0.0f, 55.0f, -2.0f});
				WaveAttackRight->Direction = LeftRight::RIGHT;

			}
		);

		ImageRenderer->SetEndCallBack("GetUp", [&]()
			{
				GroundAttackCount = 0;
				StateManager_.ChangeState("Walk");
			}
		);
}

void MiddleBoss::DirectionCheck()
{
	if (Direction == LeftRight::RIGHT)
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f });
	}
	else
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1200.0f, 1200.0f, 1.0f } *= float4::XFLIP);
	}
}