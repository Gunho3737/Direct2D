#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "BitMap.h"
#include <GameEngine\PostFade.h>
#include "UserGame.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
	: Speed(600.0f), JumpPower(float4::ZERO), BasicJumpPower(float4::UP * 1000.0f), FallDownPower(float4::DOWN * 700.0f), TimeCheck(0.0f),ImmuneTime(0.0f), LevelMoveOn(false), Impact(false), Immune(false)
{
}

Player::~Player()
{
}


void Player::Start()
{

	{
		// Scale에 마이너스를 곱하면 대칭이 가능해진다
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->CreateAnimationFolder("Idle", "Idle", 0.2f);
		PlayerImageRenderer->CreateAnimationFolder("IdleToRun", "IdleToRun", 0.07f);
		PlayerImageRenderer->CreateAnimationFolder("Run", "Run", 0.1f);
		PlayerImageRenderer->CreateAnimationFolder("Slash", "Attack", 0.05f, false);
		PlayerImageRenderer->CreateAnimationFolder("RunToIdle", "RunToIdle", 0.07f);
		PlayerImageRenderer->CreateAnimationFolder("Airborne", "Airborne", 0.07f);
		PlayerImageRenderer->CreateAnimationFolder("Jump", "Jump", 0.07f, false);
		PlayerImageRenderer->CreateAnimationFolder("UpSlash", "UpAttack", 0.05f, false);
		PlayerImageRenderer->CreateAnimationFolder("DownSlash", "DownAttack", 0.05f, false);
		PlayerImageRenderer->CreateAnimationFolder("Run", "MapMove", 0.1f);
		PlayerImageRenderer->CreateAnimationFolder("Damage", "Damage", 0.1f, false);
		PlayerImageRenderer->CreateAnimationFolder("DeathDamage", "DeathDamage", 0.1f, false);
		PlayerImageRenderer->CreateAnimationFolder("Death", "Death", 0.1f, false);
		PlayerImageRenderer->CreateAnimationFolder("DeathHead", "DeathHead", 0.1f, false);

		PlayerImageRenderer->SetChangeAnimation("Idle");
		PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetFolderTextureImageSize());
		//렌더러가 그려지는곳을 봇으로 설정
		PlayerImageRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot());
	}


	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PLAYER);
		PlayerCollision->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, 1.0f });
		PlayerCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot() += {0.0f, 0.0f, -2.0f});
	}


	{
		PlayerSlashRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerSlashRenderer->CreateAnimationFolder("SlashEffect", "SlashEffect", 0.02f);
		PlayerSlashRenderer->CreateAnimationFolder("UpSlashEffect", "UpSlashEffect", 0.02f);
		PlayerSlashRenderer->CreateAnimationFolder("DownSlashEffect", "DownSlashEffect", 0.02f);
	}

	{
		PlayerSlashCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::ATTACK));
		PlayerSlashCollision->Off();
	}

	{
		PlayerEffectRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerEffectRenderer->CreateAnimationFolder("DamageEffect", "DamageEffect", 0.02f);
		PlayerEffectRenderer->SetChangeAnimation("DamageEffect");
		PlayerEffectRenderer->GetTransform()->SetLocalScaling(PlayerEffectRenderer->GetFolderTextureImageSize());
		//플레이어렌더러 보다 앞에 나와야함
		PlayerEffectRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot() += {0.0f, 0.0f, -1.0f});
		PlayerEffectRenderer->Off();
	}

	{
		PlayerEffectRenderer2 = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerEffectRenderer2->CreateAnimationFolder("StunEffect", "StunEffect", 0.02f);
		PlayerEffectRenderer2->SetChangeAnimation("StunEffect");
		PlayerEffectRenderer2->GetTransform()->SetLocalScaling(PlayerEffectRenderer2->GetFolderTextureImageSize());
		PlayerEffectRenderer2->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot());
		PlayerEffectRenderer2->Off();
	}

	{
		PlayerSlashEffectRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerSlashEffectRenderer->CreateAnimationFolder("AttackEffect", "AttackEffect", 0.02f);
		PlayerSlashEffectRenderer->SetChangeAnimation("AttackEffect");
		PlayerSlashEffectRenderer->GetTransform()->SetLocalScaling(PlayerEffectRenderer2->GetFolderTextureImageSize());
		PlayerSlashEffectRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot() += {0.0f, 0.0f, -1.0f});
		PlayerSlashEffectRenderer->Off();
	}

	StateManager_.CreateState("Idle", std::bind(&Player::Idle, this));
	StateManager_.CreateState("IdleToRun", std::bind(&Player::IdleToRun, this));
	StateManager_.CreateState("Run", std::bind(&Player::Run, this));
	StateManager_.CreateState("RunToIdle", std::bind(&Player::RunToIdle, this));
	StateManager_.CreateState("Attack", std::bind(&Player::Attack, this));
	StateManager_.CreateState("Jump", std::bind(&Player::Jump, this));
	StateManager_.CreateState("Airborne", std::bind(&Player::Airborne, this));
	StateManager_.CreateState("UpAttack", std::bind(&Player::UpAttack, this));
	StateManager_.CreateState("DownAttack", std::bind(&Player::DownAttack, this));
	StateManager_.CreateState("MapMove", std::bind(&Player::MapMove, this));
	StateManager_.CreateState("MapPrev", std::bind(&Player::MapPrev, this));
	StateManager_.CreateState("Damage", std::bind(&Player::Damage, this));


	StateManager_.ChangeState("Idle");
	
	SetCallBackFunc();

}

void Player::Update(float _DeltaTime)
{
	//좌우를 바꿔줘야함
	if (PlayerDirection == LeftRight::LEFT)
	{
		PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetFolderTextureImageSize());
	}
	else
	{
		PlayerImageRenderer->GetTransform()->SetLocalScaling((PlayerImageRenderer->GetFolderTextureImageSize() *= float4::XFLIP));
	}


	//플레이어의 Transform = 렌더러의 발에있다
	MapBotCollisionColor = BitMap::GetColor(GetTransform());

	//그러므로 머리와 접촉하는 곳은 이미지의 높이만큼
	MapTopCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 120.0f, 0.0f});
	MapLeftCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {-30.0f, 60.0f, 0.0f});
	MapRightCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {30.0f, 60.0f, 0.0f});

	//대각선 방향 충돌
	MapTopLeftCollisionColor  = BitMap::GetColor(GetTransform()->GetWorldPosition() += {-30.0f, 120.0f, 0.0f});
	MapTopRightCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {30.0f, 120.0f, 0.0f});



	StateManager_.Update();

	//콜리전만이 꺼진거로는 충돌상태가 꺼지지 않음
	if (Immune == true)
	{
		PlayerCollision->Off();
	}
	else if (Immune == false)
	{
		PlayerCollision->On();
	}
	
	if (Immune == true)
	{
		ImmuneTime -= _DeltaTime;

		if (ImmuneTime <= 0)
		{
			Immune = false;
		}
	}

	if (true == GetLevel()->IsDebugCheck())
	{
		if (true == PlayerCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(PlayerCollision->GetTransform(), CollisionType::Rect);
		}

		if (true == PlayerSlashCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(PlayerSlashCollision->GetTransform(), CollisionType::Rect);
		}
	}

	//맵 이동 충돌체크
	{
		PlayerCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::NEXTMAP,
			[&](GameEngineCollision* _OtherCollision)
			{
				if (LevelMoveOn == false)
				{
					LevelMoveOn = true;
					TimeCheck = 1.0f;
					StateManager_.ChangeState("MapMove");
					GetLevel()->FadeOff();
				}
			}
		);

		PlayerCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::PREVMAP,
			[&](GameEngineCollision* _OtherCollision)
			{
				if (LevelMoveOn == false)
				{
					LevelMoveOn = true;
					TimeCheck = 1.0f;
					StateManager_.ChangeState("MapPrev");
					GetLevel()->FadeOff();
				}
			}
		);
	}


	PlayerSlashCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::MONSTER,
		[&](GameEngineCollision* _OtherCollision)
		{
			if (true == _OtherCollision->IsUpdate() && true == PlayerSlashCollision->IsUpdate())
			{
				PlayerSlashEffectRenderer->On();
				PlayerSlashEffectRenderer->SetChangeAnimation("AttackEffect", true);
			}
		}
	);

	//내가 데미지 상태가 아니고, 플레이어콜리전이 업데이트 중일때만 충돌체크
	if (false == (StateManager_.IsCurrentState("Damage")) && true == PlayerCollision->IsUpdate())
	{
		PlayerCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::MONSTER,
			[&](GameEngineCollision* _OtherCollision)
			{
				if (false == _OtherCollision->IsUpdate())
				{
					return;
					//상대 몬스터의 콜리전이 꺼져있으면 바로 리턴, 충돌체크 안함
				}

				StateManager_.ChangeState("Damage");
				Impact = true;
			}
		);
	}
	
	
}

void Player::Idle()
{
	PlayerImageRenderer->SetChangeAnimation("Idle");

	if (true == GameEngineInput::GetInst().Press("MoveLeft") || GameEngineInput::GetInst().Press("MoveRight"))
	{
		StateManager_.ChangeState("IdleToRun");
	}


	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		if (true == GameEngineInput::GetInst().Press("AimUp"))
		{
			StateManager_.ChangeState("UpAttack");
			return;
		}
		else
		{
			StateManager_.ChangeState("Attack");
		}
	}

	if (true == GameEngineInput::GetInst().Down("Jump"))
	{
		JumpPower = BasicJumpPower;
		StateManager_.ChangeState("Jump");
	}

	if (MapBotCollisionColor != float4::BLACK)
	{
		StateManager_.ChangeState("Airborne");
	}

	//디버그용 강제 위로 이동
	if (true == GameEngineInput::GetInst().Press("SuperUp"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed);
	}
}

void Player::IdleToRun()
{
	PlayerImageRenderer->SetChangeAnimation("IdleToRun");

	if (
		MapLeftCollisionColor != float4::BLACK &&
		MapTopLeftCollisionColor != float4::BLACK
		)
	{
		if (true == GameEngineInput::GetInst().Press("MoveLeft"))
		{
			if (PlayerDirection == LeftRight::RIGHT)
			{
				PlayerDirection = LeftRight::LEFT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		}
	}

	if (MapRightCollisionColor != float4::BLACK &&
		MapTopRightCollisionColor != float4::BLACK
		)
	{
		if (GameEngineInput::GetInst().Press("MoveRight"))
		{
			if (PlayerDirection == LeftRight::LEFT)
			{
				PlayerDirection = LeftRight::RIGHT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		}
	}

	if (
		true == GameEngineInput::GetInst().Free("MoveLeft") &&
		true == GameEngineInput::GetInst().Free("MoveRight")
		)
	{
		StateManager_.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		if (true == GameEngineInput::GetInst().Press("AimUp"))
		{
			StateManager_.ChangeState("UpAttack");
			return;
		}
		else
		{
			StateManager_.ChangeState("Attack");
		}
	}

	PlayerImageRenderer->SetEndCallBack("IdleToRun", [&]()
		{
			StateManager_.ChangeState("Run");
		}
	);

	if (true == GameEngineInput::GetInst().Down("Jump"))
	{
		JumpPower = BasicJumpPower;
		StateManager_.ChangeState("Jump");
	}

	if (MapBotCollisionColor != float4::BLACK)
	{
		StateManager_.ChangeState("Airborne");
	}

}

void Player::Run()
{
	PlayerImageRenderer->SetChangeAnimation("Run");

	if (MapLeftCollisionColor != float4::BLACK &&
		MapTopLeftCollisionColor != float4::BLACK
		)
	{
		if (true == GameEngineInput::GetInst().Press("MoveLeft"))
		{
			if (PlayerDirection == LeftRight::RIGHT)
			{
				PlayerDirection = LeftRight::LEFT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		}
	}

	if (MapRightCollisionColor != float4::BLACK &&
		MapTopRightCollisionColor != float4::BLACK
		)
	{
		if (GameEngineInput::GetInst().Press("MoveRight"))
		{
			if (PlayerDirection == LeftRight::LEFT)
			{
				PlayerDirection = LeftRight::RIGHT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		}
	}

	if (
		true == GameEngineInput::GetInst().Free("MoveLeft") &&
		true == GameEngineInput::GetInst().Free("MoveRight")
		)
	{
		StateManager_.ChangeState("RunToIdle");
		return;
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		if (true == GameEngineInput::GetInst().Press("AimUp"))
		{
			StateManager_.ChangeState("UpAttack");
			return;
		}
		else
		{
			StateManager_.ChangeState("Attack");
		}
	}

	if (true == GameEngineInput::GetInst().Down("Jump"))
	{
		JumpPower = BasicJumpPower;
		StateManager_.ChangeState("Jump");
	}

	if (MapBotCollisionColor != float4::BLACK)
	{
		StateManager_.ChangeState("Airborne");
	}

}

void Player::RunToIdle()
{
	PlayerImageRenderer->SetChangeAnimation("RunToIdle");

	if (true == GameEngineInput::GetInst().Press("MoveLeft") || GameEngineInput::GetInst().Press("MoveRight"))
	{
		StateManager_.ChangeState("IdleToRun");
	}

	PlayerImageRenderer->SetEndCallBack("RunToIdle", [&]()
		{
			StateManager_.ChangeState("Idle");
		}
	);

	if (true == GameEngineInput::GetInst().Down("Jump"))
	{
		JumpPower = BasicJumpPower;
		StateManager_.ChangeState("Jump");
	}

	if (MapBotCollisionColor != float4::BLACK)
	{
		StateManager_.ChangeState("Airborne");
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		if (true == GameEngineInput::GetInst().Press("AimUp"))
		{
			StateManager_.ChangeState("UpAttack");
			return;
		}
		else
		{
			StateManager_.ChangeState("Attack");
		}
	}

}

void Player::Attack()
{
	PlayerImageRenderer->SetChangeAnimation("Attack");

	if (0 <= JumpPower.y)
	{
		JumpPower += float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 1500.0f;
		if (MapTopCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);
		}
	}

	if (0 > JumpPower.y)
	{
		if (
			MapBotCollisionColor != float4::BLACK
			)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 500.0f);
		}		
	}

	if (
		MapLeftCollisionColor != float4::BLACK &&
		MapTopLeftCollisionColor != float4::BLACK
		)
	{
		if (true == GameEngineInput::GetInst().Press("MoveLeft"))
		{
			if (PlayerDirection == LeftRight::RIGHT)
			{
				PlayerDirection = LeftRight::LEFT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		}
	}

	if (
		MapRightCollisionColor != float4::BLACK &&
		MapTopRightCollisionColor != float4::BLACK
		)
	{
		if (GameEngineInput::GetInst().Press("MoveRight"))
		{
			if (PlayerDirection == LeftRight::LEFT)
			{
				PlayerDirection = LeftRight::RIGHT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		}
	}

	PlayerImageRenderer->SetEndCallBack("Attack", [&]()
		{
			if (true == GameEngineInput::GetInst().Press("MoveLeft") || GameEngineInput::GetInst().Press("MoveRight"))
			{
				StateManager_.ChangeState("Run");
			}

			if (
				true == GameEngineInput::GetInst().Free("MoveLeft") &&
				true == GameEngineInput::GetInst().Free("MoveRight")
				)
			{
				StateManager_.ChangeState("Idle");
				return;
			}
		}
	);

	

}

void Player::Airborne()
{
	GetTransform()->SetLocalDeltaTimeMove(FallDownPower);

	PlayerImageRenderer->SetChangeAnimation("Airborne");

	if (
		MapLeftCollisionColor != float4::BLACK &&
		MapTopLeftCollisionColor != float4::BLACK
		)
	{
		if (true == GameEngineInput::GetInst().Press("MoveLeft"))
		{
			if (PlayerDirection == LeftRight::RIGHT)
			{
				PlayerDirection = LeftRight::LEFT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		}
	}

	if (
		MapRightCollisionColor != float4::BLACK &&
		MapTopRightCollisionColor != float4::BLACK
		)
	{
		if (GameEngineInput::GetInst().Press("MoveRight"))
		{
			if (PlayerDirection == LeftRight::LEFT)
			{
				PlayerDirection = LeftRight::RIGHT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		}
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		if (true == GameEngineInput::GetInst().Press("AimUp"))
		{
			StateManager_.ChangeState("UpAttack");
			return;
		}
		else if (true == GameEngineInput::GetInst().Press("AimDown"))
		{
			StateManager_.ChangeState("DownAttack");
			return;
		}
		else
		{
			StateManager_.ChangeState("Attack");
		}
	}

	if (MapBotCollisionColor == float4::BLACK)
	{
		StateManager_.ChangeState("Idle");
	}



}

void Player::Jump()
{
	PlayerImageRenderer->SetChangeAnimation("Jump");
	if (0 <= JumpPower.y)
	{
		JumpPower += float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 1500.0f;
		if (MapTopCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);
		}

		if (0 > JumpPower.y)
		{
			StateManager_.ChangeState("Airborne");
		}
	}

	if (
		MapLeftCollisionColor != float4::BLACK &&
		MapTopLeftCollisionColor != float4::BLACK
		)
	{
		if (true == GameEngineInput::GetInst().Press("MoveLeft"))
		{
			if (PlayerDirection == LeftRight::RIGHT)
			{
				PlayerDirection = LeftRight::LEFT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		}
	}

	if (
		MapRightCollisionColor != float4::BLACK &&
		MapTopRightCollisionColor != float4::BLACK
		)
	{
		if (GameEngineInput::GetInst().Press("MoveRight"))
		{
			if (PlayerDirection == LeftRight::LEFT)
			{
				PlayerDirection = LeftRight::RIGHT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		}
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		if (true == GameEngineInput::GetInst().Press("AimUp"))
		{
			StateManager_.ChangeState("UpAttack");
			return;
		}
		else if (true == GameEngineInput::GetInst().Press("AimDown"))
		{
			StateManager_.ChangeState("DownAttack");
			return;
		}
		else
		{
			StateManager_.ChangeState("Attack");
		}
	}

}

void Player::UpAttack()
{
	PlayerImageRenderer->SetChangeAnimation("UpAttack");

	if (0 <= JumpPower.y)
	{
		JumpPower += float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 1500.0f;
		if (MapTopCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);
		}
	}

	if (0 > JumpPower.y)
	{
		if (MapBotCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(FallDownPower);
		}
	}

	if (
		MapLeftCollisionColor != float4::BLACK &&
		MapTopLeftCollisionColor != float4::BLACK
		)
	{
		if (true == GameEngineInput::GetInst().Press("MoveLeft"))
		{
			if (PlayerDirection == LeftRight::RIGHT)
			{
				PlayerDirection = LeftRight::LEFT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		}
	}

	if (
		MapRightCollisionColor != float4::BLACK &&
		MapTopRightCollisionColor != float4::BLACK
		)
	{
		if (GameEngineInput::GetInst().Press("MoveRight"))
		{
			if (PlayerDirection == LeftRight::LEFT)
			{
				PlayerDirection = LeftRight::RIGHT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		}
	}

	PlayerImageRenderer->SetEndCallBack("UpAttack", [&]()
		{
			if (true == GameEngineInput::GetInst().Press("MoveLeft") || GameEngineInput::GetInst().Press("MoveRight"))
			{
				StateManager_.ChangeState("Run");
				return;
			}

			if (
				true == GameEngineInput::GetInst().Free("MoveLeft") &&
				true == GameEngineInput::GetInst().Free("MoveRight")
				)
			{
				StateManager_.ChangeState("Idle");
				return;
			}
		}
	);

}

void Player::DownAttack()
{
	PlayerImageRenderer->SetChangeAnimation("DownAttack");

	if (0 <= JumpPower.y)
	{
		JumpPower += float4::DOWN * GameEngineTime::GetInst().GetDeltaTime() * 1500.0f;
		if (MapTopCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);
		}
	}

	if (0 > JumpPower.y)
	{
		if (MapBotCollisionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(FallDownPower);
		}
	}

	if (
		MapLeftCollisionColor != float4::BLACK &&
		MapTopLeftCollisionColor != float4::BLACK
		)
	{
		if (true == GameEngineInput::GetInst().Press("MoveLeft"))
		{
			if (PlayerDirection == LeftRight::RIGHT)
			{
				PlayerDirection = LeftRight::LEFT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		}
	}

	if (
		MapRightCollisionColor != float4::BLACK &&
		MapTopRightCollisionColor != float4::BLACK
		)
	{
		if (GameEngineInput::GetInst().Press("MoveRight"))
		{
			if (PlayerDirection == LeftRight::LEFT)
			{
				PlayerDirection = LeftRight::RIGHT;
			}
			GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		}
	}

	PlayerImageRenderer->SetEndCallBack("DownAttack", [&]()
		{
			if (true == GameEngineInput::GetInst().Press("MoveLeft") || GameEngineInput::GetInst().Press("MoveRight"))
			{
				StateManager_.ChangeState("Run");
				return;
			}

			if (
				true == GameEngineInput::GetInst().Free("MoveLeft") &&
				true == GameEngineInput::GetInst().Free("MoveRight")
				)
			{
				StateManager_.ChangeState("Idle");
				return;
			}
		}
	);

	PlayerSlashCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::MONSTER,
		[&](GameEngineCollision* _OtherCollision)
		{
			JumpPower = float4::UP*700.0f;
		}
	);
}

void Player::MapMove()
{

	PlayerImageRenderer->SetChangeAnimation("MapMove");

	TimeCheck -= GameEngineTime::GetInst().GetDeltaTime();

	if (MapBotCollisionColor != float4::BLACK)
	{
		GetTransform()->SetLocalDeltaTimeMove(FallDownPower);
	}

	if (PlayerDirection == LeftRight::LEFT)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}
	else if (PlayerDirection == LeftRight::RIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
	}


	if (TimeCheck <= 0)
	{
		LevelMoveOn = false;
		StateManager_.ChangeState("Idle");

		if (GetLevel()->GetName() == "BenchRoom")
		{
		UserGame::LevelChange("MiddleRoom");
		}

		if (GetLevel()->GetName() == "MiddleRoom")
		{
			UserGame::LevelChange("MiddleBossRoom");
		}

		if (GetLevel()->GetName() == "MiddleBossRoom")
		{
			UserGame::LevelChange("FinalBossRoom");
		}
	}
}

void Player::MapPrev()
{
	PlayerImageRenderer->SetChangeAnimation("MapMove");

	TimeCheck -= GameEngineTime::GetInst().GetDeltaTime();

	if (MapBotCollisionColor != float4::BLACK)
	{
		GetTransform()->SetLocalDeltaTimeMove(FallDownPower);
	}

	if (PlayerDirection == LeftRight::LEFT)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}
	else if (PlayerDirection == LeftRight::RIGHT)
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
	}


	if (TimeCheck <= 0)
	{
		LevelMoveOn = false;
		StateManager_.ChangeState("Idle");

		if (GetLevel()->GetName() == "MiddleRoom")
		{
			UserGame::LevelChange("BenchRoom");
		}

		if (GetLevel()->GetName() == "MiddleBossRoom")
		{
			UserGame::LevelChange("MiddleRoom");
		}

		if (GetLevel()->GetName() == "FinalBossRoom")
		{
			UserGame::LevelChange("MiddleBossRoom");
		}
	}
}

void Player::Damage()
{
	PlayerImageRenderer->SetChangeAnimation("Damage");
	PlayerEffectRenderer->SetChangeAnimation("DamageEffect", true);
	PlayerEffectRenderer2->SetChangeAnimation("StunEffect", true);

	//첫순간에만 일어난다
	if (true == Impact)
	{
	PlayerEffectRenderer->On();
	PlayerEffectRenderer2->On();
	TimeCheck = 1.0f;
	GameEngineTime::GetInst().SetTimeScale(0, 0.0f);
	Impact = false;

	}

	

	TimeCheck -= GameEngineTime::GetInst().GetDeltaTime();

	if (TimeCheck <= 0.0f)
	{
		GameEngineTime::GetInst().SetTimeScale(0, 1.0f);
		Immune = true;
		ImmuneTime = 3.0f;
		StateManager_.ChangeState("Idle");
	}
}

void Player::Death()
{
}

void Player::SetCallBackFunc()
{
	//기본Slash
	{
		PlayerImageRenderer->SetStartCallBack("Attack", [&]()
			{
				PlayerSlashRenderer->On();
				PlayerSlashCollision->On();

				PlayerSlashRenderer->SetChangeAnimation("SlashEffect", true);
				if (PlayerDirection == LeftRight::LEFT)
				{
					PlayerSlashRenderer->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
					PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-70.0f, 0.0f, -1.0f});
					PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
					PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-70.0f, 0.0f, -1.0f});
					PlayerSlashEffectRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-120.0f, 0.0f, -2.0f});
				}
				else if (PlayerDirection == LeftRight::RIGHT)
				{
					{
						PlayerSlashRenderer->GetTransform()->SetLocalScaling(float4{ -157.0f,114.0f, 1.0f });
						PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
						PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
						PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
						PlayerSlashEffectRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {120.0f, 0.0f, -2.0f});
					}
				}

			}
		);


		PlayerSlashRenderer->SetEndCallBack("SlashEffect", [&]()
			{
				PlayerSlashRenderer->Off();
				PlayerSlashCollision->Off();
			}
		);
	}

	//UpSlash
	{
		PlayerImageRenderer->SetStartCallBack("UpAttack", [&]()
			{
				PlayerSlashRenderer->On();
				PlayerSlashCollision->On();

				PlayerSlashRenderer->SetChangeAnimation("UpSlashEffect", true);
				PlayerSlashRenderer->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, 100.0f, -1.0f});
				PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, 100.0f, -1.0f});
				PlayerSlashEffectRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, 100.0f, -2.0f});
			}
		);

		PlayerSlashRenderer->SetEndCallBack("UpSlashEffect", [&]()
			{

				PlayerSlashRenderer->Off();
				PlayerSlashCollision->Off();
			}
		);
	}

	//DownSlash
	{
		PlayerImageRenderer->SetStartCallBack("DownAttack", [&]()
			{
				PlayerSlashRenderer->On();
				PlayerSlashCollision->On();

				PlayerSlashRenderer->SetChangeAnimation("DownSlashEffect", true);
				PlayerSlashRenderer->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, -100.0f, -1.0f});
				PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, -100.0f, -1.0f});
				PlayerSlashEffectRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, -100.0f, -2.0f});
			}
		);

		PlayerSlashRenderer->SetEndCallBack("DownSlashEffect", [&]()
			{
				PlayerSlashRenderer->Off();
				PlayerSlashCollision->Off();
			}
		);
	}

	{
		PlayerEffectRenderer->SetStartCallBack("DamageEffect", [&]()
		{
			
		}
		);

		PlayerEffectRenderer->SetEndCallBack("DamageEffect", [&]()
			{
				PlayerEffectRenderer->Off();
			}
		);

		PlayerEffectRenderer2->SetStartCallBack("StunEffect", [&]()
			{

			}
		);

		PlayerEffectRenderer2->SetEndCallBack("StunEffect", [&]()
			{
				PlayerEffectRenderer2->Off();
			}
		);

		PlayerSlashEffectRenderer->SetStartCallBack("AttackEffect", [&]()
			{
				if (PlayerDirection == LeftRight::RIGHT)
				{
					PlayerSlashEffectRenderer->GetTransform()->SetLocalScaling(PlayerEffectRenderer2->GetFolderTextureImageSize() *= float4::XFLIP);
				}
				else
				{
					PlayerSlashEffectRenderer->GetTransform()->SetLocalScaling(PlayerEffectRenderer2->GetFolderTextureImageSize());
				}
			}
		);

		PlayerSlashEffectRenderer->SetEndCallBack("AttackEffect", [&]()
			{
				PlayerSlashEffectRenderer->Off();
			}
		);
	}
}