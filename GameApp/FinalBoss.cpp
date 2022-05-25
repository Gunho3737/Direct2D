#include "PreCompile.h"
#include "FinalBoss.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "CollapseFloor.h"
#include "FinalBossRoomLevel.h"


#include <GameApp/BitMap.h>
#include "Player.h"
#include "GroundWave.h"



FinalBoss::FinalBoss() // default constructer 디폴트 생성자
	: HP(1),BodyHP(10), DeathOn(false), Speed(400.0f), GetDamage(false), ImmuneTime(0.0f), GroundAttackCount(0), TurnTime(0.0f), JumpPower({ 0.0f,0.0f,0.0f }), FloorCheck(false)
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
	ImageRenderer->CreateAnimation("FinalBoss.png", "AttackRecover", 33, 37, 0.15f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Jump", 38, 42, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttack", 43, 44, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttackRecover", 45, 48, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Damage", 49, 58, 0.07f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "FaceOff", 59, 62, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Faint", 63, 65, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss_2.png", "GetUp", 0, 4, 0.07f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "RampagePosition", 38, 42, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "RampageReady", 24, 29, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss_2.png", "Rampage", 5, 12, 0.07f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "DeathReady", 38, 42, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "DeathFallDown", 66, 68, 0.1f, false);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 1400.0f, 1400.0f, 1.0f });

	RealBodyRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	RealBodyRenderer->CreateAnimation("FinalBoss.png", "FaceBlow", 75, 78, 0.1f, false);
	RealBodyRenderer->CreateAnimation("FinalBoss.png", "FaceIdle", 79, 83, 0.1f, false);
	RealBodyRenderer->CreateAnimation("FinalBoss.png", "FaceHit", 84, 86, 0.1f, false);
	RealBodyRenderer->GetTransform()->SetLocalScaling({ 1400.0f, 1400.0f, 1.0f });
	RealBodyRenderer->SetChangeAnimation("FaceIdle");
	RealBodyRenderer->Off();

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
	StateManager_.CreateState("AttackReady", std::bind(&FinalBoss::AttackReady, this));
	StateManager_.CreateState("Attack", std::bind(&FinalBoss::Attack, this));
	StateManager_.CreateState("AttackRecover", std::bind(&FinalBoss::AttackRecover, this));
	StateManager_.CreateState("Damage", std::bind(&FinalBoss::Damage, this));
	StateManager_.CreateState("FaceOff", std::bind(&FinalBoss::FaceOff, this));
	StateManager_.CreateState("Faint", std::bind(&FinalBoss::Faint, this));
	StateManager_.CreateState("GetUp", std::bind(&FinalBoss::GetUp, this));
	StateManager_.CreateState("RampagePosition", std::bind(&FinalBoss::RampagePosition, this));
	StateManager_.CreateState("RampageReady", std::bind(&FinalBoss::RampageReady, this));
	StateManager_.CreateState("Rampage", std::bind(&FinalBoss::Rampage, this));
	StateManager_.CreateState("DeathReady", std::bind(&FinalBoss::DeathReady, this));
	StateManager_.CreateState("DeathFallDown", std::bind(&FinalBoss::DeathFallDown, this));
	StateManager_.ChangeState("Idle");

	SetCallBackFunc();
}

void FinalBoss::Update(float _DeltaTime)
{
	StateManager_.Update(_DeltaTime);

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

	if (HP <= 0)
	{
		JumpPower = float4::ZERO;
		BodyHP = 10;
		HP = 99;
		StateManager_.ChangeState("Damage");
	}

	if (true == GetDamage)
	{
		ImmuneTime -= _DeltaTime;

		if (ImmuneTime <= 0.0f)
		{
			GetDamage = false;
			Collision->On();
			RealBodyRenderer->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
			ImageRenderer->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
			
		}
	}

	if (false == GetDamage)
	{
		Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::ATTACK,
			[&](GameEngineCollision* _OtherCollision)
			{
				GetDamage = true;
				ImmuneTime = 0.2f;
				Collision->Off();
				if ("Death" != ImageRenderer->GetCurrentAnimationName())
				{
					if (StateManager_.IsCurrentState("Faint"))
					{
						BodyHP -= 1;
						RealBodyRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
					}
					else
					{
						HP -= 1;
						ImageRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
					}
				}

			}
		);
	}

}

void FinalBoss::Idle() 
{
	ImageRenderer->SetChangeAnimation("Idle");

	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MonsterPos = Collision->GetTransform()->GetWorldPosition();
	LeftRight PostDirection = Direction;

	if (PlayerPos.x >= MonsterPos.x)
	{
		Direction = LeftRight::RIGHT;
	}
	else if (PlayerPos.x < MonsterPos.x)
	{
		Direction = LeftRight::LEFT;
	}

	if (-3.0f <= (PlayerPos.x - MonsterPos.x) &&
		3.0f >= (PlayerPos.x - MonsterPos.x)
		)
	{
		Direction = PostDirection;
	}

	DirectionCheck();

	ViewCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PLAYER,
		[this](GameEngineCollision* _OtherCollision)
		{
			FinalBossRoomLevel::BossBattleOn = true;
			StateManager_.ChangeState("Walk");
		}
	);

	if (GroundAttackCount >= 3)
	{
		GroundAttackCount = 0;
		JumpPower = float4::ZERO;
		StateManager_.ChangeState("AttackReady");
	}
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
		[&](GameEngineCollision* _OtherCollision)
		{
			JumpPower = float4::UP * 1000.0f;
			GroundAttackCount += 1;
			StateManager_.ChangeState("Jump");
			if (GroundAttackCount < 3)
			{
				StateManager_.ChangeState("Jump");
			}
		}
	);

	if (-3.0f <= (PlayerPos.x - MonsterPos.x) &&
		3.0f >= (PlayerPos.x - MonsterPos.x)
		)
	{
		Direction = PostDirection;
	}

	DirectionCheck();

}

void FinalBoss::AttackReady()
{
	ImageRenderer->SetChangeAnimation("AttackReady");
}

void FinalBoss::Attack() 
{
	ImageRenderer->SetChangeAnimation("Attack");
}

void FinalBoss::AttackRecover()
{
	ImageRenderer->SetChangeAnimation("AttackRecover");
}


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

void FinalBoss::Damage()
{
	Collision->Off();
	AttackCollision->Off();

	ImageRenderer->SetChangeAnimation("Damage");

	float DropSpeed = 500.0f;

	FloorCollisionCheck();

	if (MapBotCollisionColor == float4::BLACK || FloorCheck == true)
	{
		DropSpeed = 0.0f;
	}

	GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * DropSpeed);

	float time = StateManager_.GetCurrentState()->Time;

	if (time >= 2.0f)
	{
		Collision->On();
		Collision->GetTransform()->SetLocalScaling(float4{ 100.0f, 100.0f, 1.0f });

		if (Direction == LeftRight::RIGHT)
		{
			Collision->GetTransform()->SetLocalPosition(float4{130.0f, 50.0f, -10.0f});
		}
		else if (Direction == LeftRight::LEFT)
		{
			Collision->GetTransform()->SetLocalPosition(float4{ -130.0f, 50.0f, -10.0f });
		}
		StateManager_.ChangeState("FaceOff");
	}
}

void FinalBoss::FaceOff()
{
	ImageRenderer->SetChangeAnimation("FaceOff");
}

void FinalBoss::Faint()
{
	ImageRenderer->SetChangeAnimation("Faint");

	Collision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::ATTACK,
		[&](GameEngineCollision* _OtherCollision)
		{
			RealBodyRenderer->SetChangeAnimation("FaceHit", true);
		}
	);
	
	if (BodyHP <= 0)
	{
		RealBodyRenderer->Off();
		if (DeathOn == true)
		{
			int a = 0;
		}
		else if (DeathOn == false)
		{
			StateManager_.ChangeState("GetUp");
		}
	}
}

void FinalBoss::GetUp() 
{
	ImageRenderer->SetChangeAnimation("GetUp");
}

void FinalBoss::RampagePosition()
{

	ImageRenderer->SetChangeAnimation("RampagePosition");

	JumpPower += float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 1500.0f;

	GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);

	switch (Direction)
	{
	case LeftRight::LEFT: 
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		break;
	}
	case LeftRight::RIGHT:
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		break;
	}
	default:
		break;
	}

	FloorCollisionCheck();


	if (0 > JumpPower.y)
	{
		if (MapBotCollisionColor == float4::BLACK || FloorCheck == true)
		{
			StateManager_.ChangeState("RampageReady");
		}
	}

}

void FinalBoss::RampageReady()
{
	ImageRenderer->SetChangeAnimation("RampageReady");

	float time = StateManager_.GetCurrentState()->Time;

	if (time >= 1.0f)
	{
		StateManager_.ChangeState("Rampage");
	}
}

void FinalBoss::Rampage()
{
	ImageRenderer->SetChangeAnimation("Rampage");

	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	float4 MonsterPos = Collision->GetTransform()->GetWorldPosition();

	float time = StateManager_.GetCurrentState()->Time;

	if (time >= 3.0f)
	{
		JumpPower = float4::UP * 1000.0f;

		if (PlayerPos.x > MonsterPos.x)
		{
			Direction = LeftRight::RIGHT;
			ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f });
			RealBodyRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f });
		}
		else
		{
			Direction = LeftRight::LEFT;
			ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f } *= float4::XFLIP);
			RealBodyRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f } *= float4::XFLIP);
		}
		StateManager_.ChangeState("DeathReady");
	}
}

void FinalBoss::DeathReady()
{
	ImageRenderer->SetChangeAnimation("DeathReady");

	JumpPower += float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 1500.0f;


	GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);

	FloorCollisionCheck();
	
	if (0 > JumpPower.y)
	{
		if (FloorCheck == true)
		{
			DeathOn = true;
			FinalBossRoomLevel::BossBattleOn = false;
			StateManager_.ChangeState("DeathFallDown");
		}
	}


}

void FinalBoss::DeathFallDown()
{
	ImageRenderer->SetChangeAnimation("DeathFallDown");

	JumpPower += float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 1500.0f;

	GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);

	if (MapBotCollisionColor == float4::BLACK)
	{
		BodyHP = 10;
		StateManager_.ChangeState("Damage");
	}
}

void FinalBoss::Death() 
{}

void FinalBoss::DirectionCheck()
{
	if (Direction == LeftRight::RIGHT)
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f });
		RealBodyRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f });
		Collision->GetTransform()->SetLocalPosition({ 50.0f, 160.0f, -10.0f });
		RangeCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });
		ViewCollision->GetTransform()->SetLocalPosition({ 50.0f, 130.0f, -10.0f });
	}
	else
	{
		ImageRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f } *= float4::XFLIP);
		RealBodyRenderer->GetTransform()->SetLocalScaling(float4{ 1400.0f, 1400.0f, 1.0f } *= float4::XFLIP);
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

	ImageRenderer->SetEndCallBack("AttackReady", [&]()
		{
			StateManager_.ChangeState("Attack");
		}
	);

	ImageRenderer->SetEndCallBack("Attack", [&]()
		{
			StateManager_.ChangeState("AttackRecover");
			if (Direction == LeftRight::RIGHT)
			{
				GroundWave* WaveAttackRight = GetLevel()->CreateActor<GroundWave>();
				WaveAttackRight->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() += {100.0f, 55.0f, -2.0f});
				WaveAttackRight->Direction = LeftRight::RIGHT;

			}
			else if (Direction == LeftRight::LEFT)
			{
				GroundWave* WaveAttackLeft = GetLevel()->CreateActor<GroundWave>();
				WaveAttackLeft->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() += {-100.0f, 55.0f, -2.0f});
				WaveAttackLeft->Direction = LeftRight::LEFT;
			}
		}
	);

	ImageRenderer->SetEndCallBack("AttackRecover", [&]()
		{
			StateManager_.ChangeState("Idle");
		}
	);

	ImageRenderer->SetEndCallBack("FaceOff", [&]()
		{
			StateManager_.ChangeState("Faint");
			BodyHP = 10;
			RealBodyRenderer->On();
			RealBodyRenderer->SetChangeAnimation("FaceIdle");
			if (Direction == LeftRight::RIGHT)
			{
				RealBodyRenderer->GetTransform()->SetLocalPosition(float4{ 150.0f, 0.0f });
			}
			else if (Direction == LeftRight::LEFT)
			{
				RealBodyRenderer->GetTransform()->SetLocalPosition(float4{ -150.0f, 0.0f });
			}
		}
	);

	RealBodyRenderer->SetEndCallBack("FaceHit", [&]()
		{
		}
	);

	ImageRenderer->SetEndCallBack("GetUp", [&]()
		{
			Collision->GetTransform()->SetLocalScaling(float4{ 300.0f, 300.0f, 1.0f });
			Collision->GetTransform()->SetLocalPosition({ 0.0f, 160.0f, -10.0f });
			
			JumpPower = float4::UP * 1000.0f;
			float MonsterPos = GetTransform()->GetLocalPosition().x;

			if (MonsterPos <= 1650.0f)
			{
				Direction = LeftRight::RIGHT;
			}
			else if (MonsterPos > 1650.0f)
			{
				Direction = LeftRight::LEFT;
			}

			StateManager_.ChangeState("RampagePosition");
		}
	);
}