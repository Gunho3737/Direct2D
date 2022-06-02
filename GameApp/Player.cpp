#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "BitMap.h"
#include <GameEngine\PostFade.h>
#include "UserGame.h"
#include "GameEngineBase/GameEngineSoundPlayer.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
	: Speed(600.0f), JumpPower(float4::ZERO), BasicJumpPower(float4::UP * 1000.0f), FallDownPower(float4::DOWN * 700.0f), TimeCheck(0.0f),ImmuneTime(0.0f), LevelMoveOn(false), Impact(false), Immune(false), FloorCheck(false)
{
}

Player::~Player()
{
}


void Player::Start()
{

	{
		MoveSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();
		DamageSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();
		AttackSoundPlayer = GameEngineSoundManager::GetInst().CreateSoundPlayer();
	}


	{
		// Scale�� ���̳ʽ��� ���ϸ� ��Ī�� ����������
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
		//�������� �׷����°��� ������ ����
		PlayerImageRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot());
		//PlayerImageRenderer->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	}


	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PLAYER);
		PlayerCollision->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, 1.0f });
		PlayerCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot() += {0.0f, 0.0f, -2.0f});
	}

	{
		PlayerLeftRightCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PLAYER);
		PlayerLeftRightCollision->GetTransform()->SetLocalScaling(float4{ 30.0f, 100.0f, 1.0f });
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
		//�÷��̾���� ���� �տ� ���;���
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
		PlayerSlashEffectRenderer->CreateAnimationFolder("AttackEffect", "AttackEffect", 0.015f);
		PlayerSlashEffectRenderer->SetChangeAnimation("AttackEffect");
		PlayerSlashEffectRenderer->GetTransform()->SetLocalScaling(PlayerEffectRenderer2->GetFolderTextureImageSize());
		PlayerSlashEffectRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot() += {0.0f, 0.0f, -1.0f});
		PlayerSlashEffectRenderer->Off();
	}

	{
		PlayerShotImpactRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
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
	//�¿츦 �ٲ������
	if (PlayerDirection == LeftRight::LEFT)
	{
		PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetFolderTextureImageSize());
	}
	else
	{
		PlayerImageRenderer->GetTransform()->SetLocalScaling((PlayerImageRenderer->GetFolderTextureImageSize() *= float4::XFLIP));
	}


	//�÷��̾��� Transform = �������� �߿��ִ�
	MapBotCollisionColor = BitMap::GetColor(GetTransform());

	//�׷��Ƿ� �Ӹ��� �����ϴ� ���� �̹����� ���̸�ŭ
	MapTopCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 120.0f, 0.0f});
	MapLeftCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {-30.0f, 60.0f, 0.0f});
	MapRightCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {30.0f, 60.0f, 0.0f});

	//�밢�� ���� �浹
	MapTopLeftCollisionColor  = BitMap::GetColor(GetTransform()->GetWorldPosition() += {-30.0f, 120.0f, 0.0f});
	MapTopRightCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {30.0f, 120.0f, 0.0f});



	StateManager_.Update(_DeltaTime);

	//�ݸ������� �����ŷδ� �浹���°� ������ ����
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

		if (true == PlayerLeftRightCollision->IsUpdate())
		{
			GetLevel()->PushDebugRender(PlayerLeftRightCollision->GetTransform(), CollisionType::Rect);
		}
	}

	//�� �̵� �浹üũ
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

	//���� ������ ���°� �ƴϰ�, �÷��̾��ݸ����� ������Ʈ ���϶��� �浹üũ
	if (false == (StateManager_.IsCurrentState("Damage")) && true == PlayerCollision->IsUpdate())
	{
		PlayerCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::MONSTER,
			[&](GameEngineCollision* _OtherCollision)
			{
				if (false == _OtherCollision->IsUpdate())
				{
					return;
					//��� ������ �ݸ����� ���������� �ٷ� ����, �浹üũ ����
				}
				MoveSoundPlayer->Stop();
				AttackSoundPlayer->Stop();
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

	FloorCollisionCheck();


	if (MapBotCollisionColor != float4::BLACK)
	{
		if (FloorCheck == false)
		{
		StateManager_.ChangeState("Airborne");
		}
	}

	//����׿� ���� ���� �̵�
	if (true == GameEngineInput::GetInst().Press("SuperUp"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed);
	}
}

void Player::IdleToRun()
{
	PlayerImageRenderer->SetChangeAnimation("IdleToRun");

	FloorCollisionCheck();
	WallCollisionCheck();

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

			if (WallCheck == false)
			{
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
			}

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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
			}
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
		if (FloorCheck == false)
		{
			StateManager_.ChangeState("Airborne");
		}
	}

}

void Player::Run()
{

	MoveSoundPlayer->PlayAlone("run.wav");

	PlayerImageRenderer->SetChangeAnimation("Run");

	FloorCollisionCheck();
	WallCollisionCheck();

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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
			}
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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
			}
		}
	}

	if (
		true == GameEngineInput::GetInst().Free("MoveLeft") &&
		true == GameEngineInput::GetInst().Free("MoveRight")
		)
	{
		MoveSoundPlayer->Stop();
		StateManager_.ChangeState("RunToIdle");
		return;
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		if (true == GameEngineInput::GetInst().Press("AimUp"))
		{
			MoveSoundPlayer->Stop();
			StateManager_.ChangeState("UpAttack");
			return;
		}
		else
		{
			MoveSoundPlayer->Stop();
			StateManager_.ChangeState("Attack");
		}
	}

	if (true == GameEngineInput::GetInst().Down("Jump"))
	{
		JumpPower = BasicJumpPower;
		MoveSoundPlayer->Stop();
		StateManager_.ChangeState("Jump");
	}

	if (MapBotCollisionColor != float4::BLACK)
	{
		if (FloorCheck == false)
		{
		MoveSoundPlayer->Stop();
		StateManager_.ChangeState("Airborne");
		}
	}

}

void Player::RunToIdle()
{
	PlayerImageRenderer->SetChangeAnimation("RunToIdle");

	FloorCollisionCheck();

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
		if (FloorCheck == false)
		{
			StateManager_.ChangeState("Airborne");
		}
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

	FloorCollisionCheck();
	WallCollisionCheck();

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
			if (FloorCheck == false)
			{
			GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 500.0f);
			}
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

			if (WallCheck == false)
			{
			GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
			}
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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
			}
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

	FloorCollisionCheck();
	WallCollisionCheck();

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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
			}
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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
			}
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

	if (MapBotCollisionColor == float4::BLACK || FloorCheck == true)
	{
		StateManager_.ChangeState("Idle");
	}



}

void Player::Jump()
{
	WallCollisionCheck();

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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
			}
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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
			}
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
	FloorCollisionCheck();
	WallCollisionCheck();

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
			if (FloorCheck == false)
			{
			GetTransform()->SetLocalDeltaTimeMove(FallDownPower);
			}
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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
			}
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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
			}
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

	FloorCollisionCheck();
	WallCollisionCheck();

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
			if (FloorCheck == true)
			{
			GetTransform()->SetLocalDeltaTimeMove(FallDownPower);
			}
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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
			}
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
			if (WallCheck == false)
			{
				GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
			}
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

		if (GetLevel()->GetName() == "FinalBossRoom")
		{
			UserGame::LevelChange("Ending");
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

	//ù�������� �Ͼ��
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

	{
		PlayerImageRenderer->SetStartCallBack("Jump", [&]()
			{
				MoveSoundPlayer->PlayAlone("jump.wav", 0);
			}
		);
	}

	//�⺻Slash
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
					PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 137.0f,114.0f, 1.0f });
					PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-70.0f, 0.0f, -1.0f});
					PlayerSlashEffectRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-120.0f, 0.0f, -2.0f});
				}
				else if (PlayerDirection == LeftRight::RIGHT)
				{
					{
						PlayerSlashRenderer->GetTransform()->SetLocalScaling(float4{ -157.0f,114.0f, 1.0f });
						PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
						PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 137.0f,114.0f, 1.0f });
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

void Player::FloorCollisionCheck()
{
	FloorCheck = false;
	PlayerCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::FLOOR,
		[&](GameEngineCollision* _OtherCollision)
		{
			FloorCheck = true;
		}
	);
}

void Player::WallCollisionCheck()
{
	WallCheck = false;

	switch (PlayerDirection)
	{
	case LeftRight::LEFT:
	{
		PlayerLeftRightCollision->GetTransform()->SetLocalPosition({ -15.0f, 60.0f, 0.0f});
	}
		break;
	case LeftRight::RIGHT:
	{
		PlayerLeftRightCollision->GetTransform()->SetLocalPosition({ 15.0f, 60.0f, 0.0f });
	}
		break;
	default:
		break;
	}

	PlayerLeftRightCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::WALL,
		[&](GameEngineCollision* _OtherCollision)
		{
			WallCheck = true;
		}
	);
}

void Player::Blink(float _DeltaTime)
{}