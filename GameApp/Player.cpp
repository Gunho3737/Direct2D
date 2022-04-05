#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "BitMap.h"



Player::Player()
	: Speed(600.0f), JumpPower(float4::ZERO), BasicJumpPower(float4::UP * 950.0f), FallDownPower(float4::DOWN * 700.0f)
{
}

Player::~Player()
{
}


void Player::Start()
{
	PlayerDirection = LeftRight::LEFT;

	{
		// Scale에 마이너스를 곱하면 대칭이 가능해진다
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->CreateAnimationFolder("Idle", "Idle", 0.2f);
		PlayerImageRenderer->CreateAnimationFolder("IdleToRun", "IdleToRun", 0.07f);
		PlayerImageRenderer->CreateAnimationFolder("Run", "Run", 0.1f);
		PlayerImageRenderer->CreateAnimationFolder("Attack", "Slash", 0.05f, false);
		PlayerImageRenderer->CreateAnimationFolder("RunToIdle", "RunToIdle", 0.07f);
		PlayerImageRenderer->CreateAnimationFolder("Airborne", "Airborne", 0.07f);
		PlayerImageRenderer->CreateAnimationFolder("Jump", "Jump", 0.07f, false);
		PlayerImageRenderer->CreateAnimationFolder("UpAttack", "UpSlash", 0.05f, false);
		PlayerImageRenderer->CreateAnimationFolder("DownAttack", "DownSlash", 0.05f, false);

		PlayerImageRenderer->SetChangeAnimation("Idle");
		PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetFolderTextureImageSize());
		//렌더러가 그려지는곳을 봇으로 설정
		PlayerImageRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot());
	}


	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PLAYER);
		PlayerCollision->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, -10.0f });
		PlayerCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot());
	}


	{
		PlayerSlashRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerSlashRenderer->CreateAnimationFolder("SlashEffect", "SlashEffect", 0.02f);
		PlayerSlashRenderer->CreateAnimationFolder("UpSlashEffect", "UpSlashEffect", 0.02f);
		PlayerSlashRenderer->CreateAnimationFolder("DownSlashEffect", "DownSlashEffect", 0.02f);
	}

	{
		PlayerSlashCollision = CreateTransformComponent<GameEngineCollision>(int(ActorCollisionType::ATTACK));
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
	MapBotCollsionColor = BitMap::GetColor(GetTransform());

	//그러므로 머리와 접촉하는 곳은 이미지의 높이만큼
	MapTopCollsionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 120.0f, 0.0f});
	MapLeftCollsionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {-30.0f, 60.0f, 0.0f});
	MapRightCollsionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {30.0f, 60.0f, 0.0f});

	//카메라 이동을 통제하기 위한 몸 한가운데의 색콜리전
	CameraMovementCollisionColor = BitMap::GetColor(GetTransform()->GetWorldPosition() += {0.0f, 60.0f * 0.75f, 0.0f});

	StateManager_.Update();


	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(PlayerCollision->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(PlayerSlashCollision->GetTransform(), CollisionType::Rect);
	}

	//카메라를 레벨에서 직접 관리하게 만드는중
	//GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
	
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
		[this](GameEngineCollision* _OtherCollision)
		{
			JumpPower = float4::UP*700.0f;
		}
	);
}

void Player::SetCallBackFunc()
{
	//기본Slash
	{
		PlayerImageRenderer->SetStartCallBack("Attack", [&]()
			{
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
						PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ -157.0f,114.0f, 1.0f });
						PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
					}
				}

			}
		);


		PlayerSlashRenderer->SetEndCallBack("SlashEffect", [&]()
			{
				PlayerSlashRenderer->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition());
				PlayerSlashCollision->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerCollision->GetTransform()->GetLocalPosition());
			}
		);
	}

	//UpSlash
	{
		PlayerImageRenderer->SetStartCallBack("UpAttack", [&]()
			{
				PlayerSlashRenderer->SetChangeAnimation("UpSlashEffect", true);
				PlayerSlashRenderer->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, 70.0f, -1.0f});
				PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, 70.0f, -1.0f});
			}
		);

		PlayerSlashRenderer->SetEndCallBack("UpSlashEffect", [&]()
			{
				PlayerSlashRenderer->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition());
				PlayerSlashCollision->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerCollision->GetTransform()->GetLocalPosition());
			}
		);
	}

	//DownSlash
	{
		PlayerImageRenderer->SetStartCallBack("DownAttack", [&]()
			{
				PlayerSlashRenderer->SetChangeAnimation("DownSlashEffect", true);
				PlayerSlashRenderer->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, -70.0f, -1.0f});
				PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f,114.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {0.0f, -70.0f, -1.0f});
			}
		);

		PlayerSlashRenderer->SetEndCallBack("DownSlashEffect", [&]()
			{
				PlayerSlashRenderer->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition());
				PlayerSlashCollision->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerCollision->GetTransform()->GetLocalPosition());
			}
		);
	}
}