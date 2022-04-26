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
	}


	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PLAYER);
		PlayerCollision->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, 1.0f });
		PlayerCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot() += {0.0f, 0.0f, -1.0f});
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
		PlayerEffectRenderer->CreateAnimationFolder("StunEffect", "StunEffect", 0.02f);
		PlayerEffectRenderer->SetChangeAnimation("DamageEffect");
		PlayerEffectRenderer->GetTransform()->SetLocalScaling(PlayerEffectRenderer->GetFolderTextureImageSize());
		PlayerEffectRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot());
		PlayerEffectRenderer->Off();
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
	MapBotCollsionColor = BitMap::GetColor(GetTransform());

	//�׷��Ƿ� �Ӹ��� �����ϴ� ���� �̹����� ���̸�ŭ
	MapTopCollsionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 120.0f, 0.0f});
	MapLeftCollsionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {-30.0f, 60.0f, 0.0f});
	MapRightCollsionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {30.0f, 60.0f, 0.0f});


	StateManager_.Update();

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

	//���� ������ ���°� �ƴϰ�, �÷��̾��ݸ����� ������Ʈ ���϶��� �浹üũ
	if (false == (StateManager_.IsCurrentState("Damage")) && true == PlayerCollision->IsUpdate())
	{
		PlayerCollision->Collision(CollisionType::Rect, CollisionType::Rect, ActorCollisionType::MONSTER,
			[&](GameEngineCollision* _OtherCollision)
			{
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

	if (MapBotCollsionColor != float4::BLACK)
	{
		StateManager_.ChangeState("Airborne");
	}

}

void Player::IdleToRun()
{
	PlayerImageRenderer->SetChangeAnimation("IdleToRun");

	if (MapLeftCollsionColor != float4::BLACK)
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

	if (MapRightCollsionColor != float4::BLACK)
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

	if (MapBotCollsionColor != float4::BLACK)
	{
		StateManager_.ChangeState("Airborne");
	}

}

void Player::Run()
{
	PlayerImageRenderer->SetChangeAnimation("Run");

	if (MapLeftCollsionColor != float4::BLACK)
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

	if (MapRightCollsionColor != float4::BLACK)
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

	if (MapBotCollsionColor != float4::BLACK)
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

	if (MapBotCollsionColor != float4::BLACK)
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
		if (MapTopCollsionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);
		}
	}

	if (0 > JumpPower.y)
	{
		if (MapBotCollsionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 500.0f);
		}		
	}

	if (MapLeftCollsionColor != float4::BLACK)
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

	if (MapRightCollsionColor != float4::BLACK)
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

	if (MapLeftCollsionColor != float4::BLACK)
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

	if (MapRightCollsionColor != float4::BLACK)
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

	if (MapBotCollsionColor == float4::BLACK)
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
		if (MapTopCollsionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);
		}

		if (0 > JumpPower.y)
		{
			StateManager_.ChangeState("Airborne");
		}
	}

	if (MapLeftCollsionColor != float4::BLACK)
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

	if (MapRightCollsionColor != float4::BLACK)
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
		if (MapTopCollsionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);
		}
	}

	if (0 > JumpPower.y)
	{
		if (MapBotCollsionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(FallDownPower);
		}
	}

	if (MapLeftCollsionColor != float4::BLACK)
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

	if (MapRightCollsionColor != float4::BLACK)
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
		if (MapTopCollsionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(float4::UP * JumpPower);
		}
	}

	if (0 > JumpPower.y)
	{
		if (MapBotCollsionColor != float4::BLACK)
		{
			GetTransform()->SetLocalDeltaTimeMove(FallDownPower);
		}
	}

	if (MapLeftCollsionColor != float4::BLACK)
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

	if (MapRightCollsionColor != float4::BLACK)
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

	if (MapBotCollsionColor != float4::BLACK)
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

	if (MapBotCollsionColor != float4::BLACK)
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


	//ù�������� �Ͼ��
	if (true == Impact)
	{
	PlayerEffectRenderer->On();
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
		//PlayerEffectRenderer->Off();
		StateManager_.ChangeState("Idle");
	}
}

void Player::Death()
{
}

void Player::SetCallBackFunc()
{
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
					PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
					PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-70.0f, 0.0f, -1.0f});
				}
				else if (PlayerDirection == LeftRight::RIGHT)
				{
					{
						PlayerSlashRenderer->GetTransform()->SetLocalScaling(float4{ -157.0f,114.0f, 1.0f });
						PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
						PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
						PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
					}
				}

			}
		);


		PlayerSlashRenderer->SetEndCallBack("SlashEffect", [&]()
			{
				PlayerSlashRenderer->Off();
				PlayerSlashCollision->Off();

				//PlayerSlashRenderer->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				//PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition());
				//PlayerSlashCollision->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				//PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerCollision->GetTransform()->GetLocalPosition());
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
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, 70.0f, -1.0f});
				PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, 70.0f, -1.0f});
			}
		);

		PlayerSlashRenderer->SetEndCallBack("UpSlashEffect", [&]()
			{

				PlayerSlashRenderer->Off();
				PlayerSlashCollision->Off();

			//	PlayerSlashRenderer->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
			//	PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition());
			//	PlayerSlashCollision->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
			//	PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerCollision->GetTransform()->GetLocalPosition());
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
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, -70.0f, -1.0f});
				PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, -70.0f, -1.0f});
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
	}
}