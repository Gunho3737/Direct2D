#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>
#include "GameEngineBase/GameEngineSoundPlayer.h"

#include <GameApp/BitMap.h>
#include "JumpBug.h"
#include "Player.h"


JumpBug::JumpBug() // default constructer 디폴트 생성자
	: HP(5), Speed(150.0f), GetDamage(false), ImmuneTime(0.0f), JumpPower({0.0f,0.0f,0.0f})
{

}

JumpBug::~JumpBug() // default destructer 디폴트 소멸자
{

}

void JumpBug::Start()
{
	MoveSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();

	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("JumpBug.png", "Idle", 0, 5, 0.1f);
	ImageRenderer->CreateAnimation("JumpBug.png", "Walk", 6, 12, 0.1f);
	ImageRenderer->CreateAnimation("JumpBug.png", "Death", 28, 36, 0.1f, false);
	ImageRenderer->CreateAnimation("JumpBug.png", "JumpReady", 15, 17, 0.1f, false);
	ImageRenderer->CreateAnimation("JumpBug.png", "Jump", 18, 25, 0.1f, false);
	ImageRenderer->CreateAnimation("JumpBug.png", "JumpAttack", 26, 27, 0.07f, false);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 500.0f, 500.0f, 1.0f });

	DeathEffectRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	DeathEffectRenderer->CreateAnimationFolder("MonsterStunEffect", "JumpBugStun", 0.08f, false);
	DeathEffectRenderer->SetChangeAnimation("JumpBugStun");
	DeathEffectRenderer->GetTransform()->SetLocalScaling(DeathEffectRenderer->GetFolderTextureImageSize());
	DeathEffectRenderer->GetTransform()->SetLocalPosition(float4{0.0f, 50.0f, 0.0f});
	DeathEffectRenderer->Off();

	Collision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTER));
	Collision->GetTransform()->SetLocalScaling(float4{ 80.0f, 180.0f, 1.0f });
	Collision->GetTransform()->SetLocalPosition({ 0.0f, 100.0f, -10.0f });

	ViewCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	ViewCollision->GetTransform()->SetLocalScaling(float4{ 800.0f, 350.0f, 1.0f });
	ViewCollision->GetTransform()->SetLocalPosition({ 0.0f, 100.0f, -10.0f });

	RangeCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::MONSTERVIEW));
	RangeCollision->GetTransform()->SetLocalScaling(float4{ 300.0f, 300.0f, 1.0f });
	RangeCollision->GetTransform()->SetLocalPosition({ 0.0f, 100.0f, -10.0f });



	StateManager_.CreateState("Idle", std::bind(&JumpBug::Idle, this));
	StateManager_.CreateState("Walk", std::bind(&JumpBug::Walk, this));
	StateManager_.CreateState("Death", std::bind(&JumpBug::Death, this));
	StateManager_.CreateState("JumpReady", std::bind(&JumpBug::JumpReady, this));
	StateManager_.CreateState("Jump", std::bind(&JumpBug::Jump, this));
	StateManager_.CreateState("JumpAttack", std::bind(&JumpBug::JumpAttack, this));
	

	StateManager_.ChangeState("Idle");

	SetCallBackFunc();
}

void JumpBug::Update(float _DeltaTime)
{
	StateManager_.Update(_DeltaTime);

	MapBotCollisionColor = BitMap::GetColor(GetTransform());

	MapTopCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 200.0f, 0.0f});
	MapLeftCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {-45.0f, 100.0f, 0.0f});
	MapRightCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {45.0f, 100.0f, 0.0f});

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
	}
		if (HP <= 0)
		{
			HP = 99;
			DeathEffectRenderer->On();
			DeathEffectRenderer->SetChangeAnimation("JumpBugStun", true);
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
	MoveSoundPlayer->PlayAlone("BugWalk.wav");
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
			MoveSoundPlayer->Stop();
			StateManager_.ChangeState("JumpReady");
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
}

void JumpBug::Jump()
{
	ImageRenderer->SetChangeAnimation("Jump");

	JumpPower += float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 1500.0f;

	GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);

	if (MapTopCollisionColor == float4::BLACK)
	{
		JumpPower = float4::ZERO;
	}

	if (Direction == LeftRight::RIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
	}
	else
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}

	if (0 > JumpPower.y)
	{
		if (MapBotCollisionColor == float4::BLACK)
		{
			MoveSoundPlayer->Stop();
			StateManager_.ChangeState("JumpAttack");
		}
	}
}

void JumpBug::JumpAttack()
{
	ImageRenderer->SetChangeAnimation("JumpAttack");
}

void JumpBug::Death()
{
	ImageRenderer->SetChangeAnimation("Death");


	if (MapBotCollisionColor != float4::BLACK)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed);
	}

	Collision->Off();
	ViewCollision->Off();
	RangeCollision->Off();

}

void JumpBug::SetCallBackFunc()
{

	ImageRenderer->SetEndCallBack("JumpReady", [&]()
		{
			JumpPower = float4::UP * 700.0f;
			StateManager_.ChangeState("Jump");
		}
	);

	ImageRenderer->SetStartCallBack("Jump", [&]()
		{
			MoveSoundPlayer->PlayAlone("JumpBugAttack.wav");
		}
	);

	ImageRenderer->SetEndCallBack("JumpAttack", [&]()
		{
			StateManager_.ChangeState("Walk");
		}
	);

	DeathEffectRenderer->SetEndCallBack("JumpBugStun", [&]()
		{
			DeathEffectRenderer->Off();
		}
	);
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