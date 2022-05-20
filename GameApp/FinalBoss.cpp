#include "PreCompile.h"
#include "FinalBoss.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>

#include <GameApp/BitMap.h>
#include "Player.h"
#include "GroundWave.h"



FinalBoss::FinalBoss() // default constructer 디폴트 생성자
	: HP(10), Speed(400.0f), GetDamage(false), ImmuneTime(0.0f), GroundAttackCount(0), AttackReadyTime(0.0f), TurnTime(0.0f), JumpPower({ 0.0f,0.0f,0.0f }), FloorCheck(false)
{

}

FinalBoss::~FinalBoss() // default destructer 디폴트 소멸자
{

}

void FinalBoss::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("FinalBoss.png", "Idle", 0, 4, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Walk", 10, 13, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "AttackReady", 24, 29, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Attack", 30, 32, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "AttackRecover", 33, 37, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Jump", 38, 42, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttack", 43, 44, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttackRecover", 45, 48, 0.1f, false);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 1400.0f, 1400.0f, 1.0f });

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 300.0f, 300.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });

	RangeCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	RangeCollision->GetTransform()->SetLocalScaling(float4{ 500.0f, 500.0f, 1.0f });
	RangeCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });

	ViewCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	ViewCollision->GetTransform()->SetLocalScaling(float4{ 1200.0f, 700.0f, 1.0f });
	ViewCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });

	AttackCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	AttackCollision->Off();


	StateManager_.CreateState("Idle", std::bind(&FinalBoss::Idle, this));
	StateManager_.CreateState("Walk", std::bind(&FinalBoss::Walk, this));
	StateManager_.CreateState("Jump", std::bind(&FinalBoss::Jump, this));
	StateManager_.CreateState("JumpAttack", std::bind(&FinalBoss::JumpAttack, this));
	StateManager_.CreateState("JumpAttackRecover", std::bind(&FinalBoss::JumpAttackRecover, this));
	StateManager_.ChangeState("Idle");

	SetCallBackFunc();
}

void FinalBoss::Update(float _DeltaTime)
{
	StateManager_.Update();

	MapBotCollisionColor = BitMap::GetColor(GetTransform());


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
	}
}

void FinalBoss::Idle() 
{
	ImageRenderer->SetChangeAnimation("Idle");

	ViewCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
		{
			StateManager_.ChangeState("Walk");
		}
	);
}

void FinalBoss::Walk() 
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
			JumpPower = float4::UP * 1000.0f;
			GroundAttackCount += 1;
			StateManager_.ChangeState("Jump");
			//if (GroundAttackCount < 3)
			//{
			//	StateManager_.ChangeState("Jump");
			//}
			//else if (GroundAttackCount >= 3)
			//{
			//	StateManager_.ChangeState("AttackReady");
			//}
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

void FinalBoss::AttackReady()
{}

void FinalBoss::Attack() 
{}

void FinalBoss::AttackRecover()
{}


void FinalBoss::Jump()
{
	ImageRenderer->SetChangeAnimation("Jump");

	FloorCollisionCheck();

	JumpPower += float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 1500.0f;

	GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);

	//if (MapTopCollisionColor == float4::BLACK)
	//{
	//	JumpPower = float4::ZERO;
	//}

	if (Direction == LeftRight::RIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 100.0f);
	}
	else
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 100.0f);
	}

	if (0 > JumpPower.y)
	{
		if (MapBotCollisionColor == float4::BLACK || FloorCheck == true)
		{
			StateManager_.ChangeState("JumpAttack");
		}
	}
}

void FinalBoss::JumpAttack()
{
	ImageRenderer->SetChangeAnimation("JumpAttack");
}

void FinalBoss::JumpAttackRecover()
{
	ImageRenderer->SetChangeAnimation("JumpAttackRecover");
}

void FinalBoss::GetUp() 
{}

void FinalBoss::Death() 
{}

void FinalBoss::DirectionCheck()
{
	if (Direction == LeftRight::RIGHT)
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f });
		Collision->GetTransform()->SetLocalPosition({ 50.0f, 160.0f, -10.0f });
		RangeCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });
		ViewCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });
	}
	else
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f } *= float4::XFLIP);
		Collision->GetTransform()->SetLocalPosition({ -50.0f, 160.0f, -10.0f });
		RangeCollision->GetTransform()->SetLocalPosition({ -50.0f, 130.0f, -10.0f });
		ViewCollision->GetTransform()->SetLocalPosition({ -50.0f, 130.0f, -10.0f });
	}
}

void FinalBoss::FloorCollisionCheck()
{
	FloorCheck = false;
	Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::FLOOR,
		[&](GameEngineCollision* _OtherCollision)
		{
			FloorCheck = true;
		}
	);
}

void FinalBoss::SetCallBackFunc()
{

	ImageRenderer->SetFrameCallBack("JumpAttack", 44, [&]() 
		{
			AttackCollision->On();

			if (Direction == LeftRight::LEFT)
			{
				AttackCollision->GetTransform()->SetLocalScaling(float4{ 400.0f, 600.0f, 1.0f });
				AttackCollision->GetTransform()->SetLocalPosition(ImageRenderer->GetTransform()->GetLocalPosition() += {-200.0f, 0.0f, -1.0f});
			}
			else if (Direction == LeftRight::RIGHT)
			{
				AttackCollision->GetTransform()->SetLocalScaling(float4{ 400.0f,600.0f, 1.0f });
				AttackCollision->GetTransform()->SetLocalPosition(ImageRenderer->GetTransform()->GetLocalPosition() += {200.0f, 0.0f, -1.0f});
			}

		
		}
	);

	ImageRenderer->SetEndCallBack("JumpAttack", [&]()
		{
			StateManager_.ChangeState("JumpAttackRecover");
		}
	);

	ImageRenderer->SetStartCallBack("JumpAttackRecover", [&]()
		{
			AttackCollision->Off();
		}
	);

	ImageRenderer->SetEndCallBack("JumpAttackRecover", [&]()
		{
			StateManager_.ChangeState("Idle");
		}
	);
}