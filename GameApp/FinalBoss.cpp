#include "PreCompile.h"
#include "FinalBoss.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "CollapseFloor.h"
#include "FinalBossRoomLevel.h"
#include "Door.h"
#include "GameEngineBase/GameEngineSoundPlayer.h"

#include <GameApp/BitMap.h>
#include "Player.h"
#include "GroundWave.h"
#include <GameApp/BenchRoomLevel.h>
#include "GameEngineBase/GameEngineSoundPlayer.h"


FinalBoss::FinalBoss() // default constructer 디폴트 생성자
	: HP(10),BodyHP(10), DeathOn(false), Speed(400.0f), GetDamage(false), ImmuneTime(0.0f), GroundAttackCount(0), TurnTime(0.0f), JumpPower({ 0.0f,0.0f,0.0f }), FloorCheck(false), DeathRoll(true)
{

}

FinalBoss::~FinalBoss() // default destructer 디폴트 소멸자
{

}

void FinalBoss::Start()
{
	MoveSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();
	DamageSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();
	AttackEffectSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();
	AttackVoiceSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();


	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("FinalBoss.png", "Idle", 0, 4, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Walk", 10, 13, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "AttackReady", 24, 29, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Attack", 30, 32, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "AttackRecover", 33, 37, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Jump", 38, 42, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttack", 43, 44, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttackRecover", 45, 48, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Damage", 49, 58, 0.07f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "FaceOff", 59, 62, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Faint", 63, 65, 0.07f, false);
	ImageRenderer->CreateAnimation("FinalBoss_2.png", "GetUp", 0, 4, 0.07f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "RampagePosition", 38, 42, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "RampageReady", 24, 29, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss_2.png", "Rampage", 5, 12, 0.07f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "DeathReady", 38, 42, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "DeathFallDown", 66, 68, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Death", 63, 65, 0.1f, false);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 1400.0f, 1400.0f, 1.0f });

	{
		DeathEffectRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

		DeathEffectRenderer->CreateAnimationFolder("MonsterStunEffect", "FinalBossStun", 0.07f, false);
		DeathEffectRenderer->SetChangeAnimation("FinalBossStun");
		DeathEffectRenderer->GetTransform()->SetLocalScaling(DeathEffectRenderer->GetFolderTextureImageSize());
		DeathEffectRenderer->GetTransform()->SetLocalPosition(float4{ 0.0f, 50.0f, 0.0f });
		DeathEffectRenderer->Off();


		DeathEffectRenderer->SetEndCallBack("FinalBossStun", [&]()
			{
				DeathEffectRenderer->Off();
			}
		);
	}

	RealBodyRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	RealBodyRenderer->CreateAnimation("FinalBoss.png", "FaceBlow", 87, 99, 0.03f, false);
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
	StateManager_.CreateState("Death", std::bind(&FinalBoss::Death, this));
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
		AttackEffectSoundPlayer->PlayAlone("FinalBoss_Roll.wav", 0);
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
						DamageSoundPlayer->PlayAlone("FinalBoss_RealBodyHit.wav", 0);
						BodyHP -= 1;
						RealBodyRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
					}
					else
					{
						HP -= 1;
						DamageSoundPlayer->PlayAlone("FinalBoss_ArmourDamage.wav", 0);
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
	MoveSoundPlayer->PlayAlone("MiddleBoss_Walk.wav");

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
				AttackVoiceSoundPlayer->PlayAlone("FinalBoss_AttackShout.wav", 0);
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
		AttackEffectSoundPlayer->Stop();
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
			ImageRenderer->SetChangeAnimation("Faint", true);
			RealBodyRenderer->SetChangeAnimation("FaceHit", true);
		}
	);
	
	if (BodyHP <= 0)
	{
		DeathEffectRenderer->On();
		switch (Direction)
		{
		case LeftRight::LEFT:
		{	
			DeathEffectRenderer->GetTransform()->SetLocalPosition(float4{-150.0f, 60.0f});
		}
			break;
		case LeftRight::RIGHT:
		{	
			DeathEffectRenderer->GetTransform()->SetLocalPosition(float4{150.0f, 60.0f });
		}
			break;
		default:
			break;
		}
		DeathEffectRenderer->SetChangeAnimation("FinalBossStun", true);

		if (DeathOn == true)
		{
			AttackVoiceSoundPlayer->Stop();
			AttackVoiceSoundPlayer->PlayAlone("FinalBoss_Death.wav",0);
			FinalBossRoomLevel::EndingBlockDoor->DoorOn = false;
			StateManager_.ChangeState("Death");
		}
		else if (DeathOn == false)
		{
			RealBodyRenderer->Off();
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
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 300.0f);
		break;
	}
	case LeftRight::RIGHT:
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 350.0f);
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
			MoveSoundPlayer->PlayAlone("FinalBoss_Land.wav", 0);
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
	AttackVoiceSoundPlayer->PlayAlone("FinalBoss_RamPage.wav",0);

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
		AttackVoiceSoundPlayer->Stop();
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
			CollapseFloor::CollapseOn = true;
			MoveSoundPlayer->PlayAlone("CollapseFloor.wav", 0);
			AttackVoiceSoundPlayer->PlayAlone("FinalBoss_FallDown.wav", 0);
			StateManager_.ChangeState("DeathFallDown");
			BenchRoomLevel::PlayLevelBackGroundSoundPlayer->Stop();
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
{
	ImageRenderer->SetChangeAnimation("Death");
	RealBodyRenderer->SetChangeAnimation("FaceBlow");
	Collision->Off();

	if (DeathRoll == true)
	{
		switch (Direction)
		{
			case LeftRight::LEFT:
			{
				RealBodyRenderer->GetTransform()->SetLocalScaling(float4{ 1050.0f, 1050.0f, 1.0f } *= float4::XFLIP);
				RealBodyRenderer->GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
				break;
			}
			case LeftRight::RIGHT:
			{
				RealBodyRenderer->GetTransform()->SetLocalScaling(float4{ 1050.0f, 1050.0f, 1.0f });
				RealBodyRenderer->GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
				break;
			}
		}
	}
}

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
			AttackEffectSoundPlayer->PlayAlone("FinalBoss_Attack.wav", 0);
			MoveSoundPlayer->PlayAlone("FinalBoss_Land.wav", 0);

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
			AttackVoiceSoundPlayer->PlayAlone("FinalBoss_AttackShout.wav", 0);
			StateManager_.ChangeState("Attack");
		}
	);

	ImageRenderer->SetEndCallBack("Attack", [&]()
		{
			StateManager_.ChangeState("AttackRecover");
			MoveSoundPlayer->PlayAlone("FinalBoss_Land.wav", 0);
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

			if (MonsterPos <= 1600.0f)
			{
				Direction = LeftRight::RIGHT;
			}
			else if (MonsterPos > 1600.0f)
			{
				Direction = LeftRight::LEFT;
			}

			StateManager_.ChangeState("RampagePosition");
		}
	);

	RealBodyRenderer->SetEndCallBack("FaceBlow", [&]()
		{
			DeathRoll = false;
		}
	);

}