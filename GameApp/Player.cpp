#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Map.h"



Player::Player()
	: Speed(400.0f)
{
}

Player::~Player()
{
}


void Player::Start()
{
	PlayerDirection = LeftRight::LEFT;

	GetTransform()->SetLocalPosition({720.0f,-300.0f});

	{
		// Scale에 마이너스를 곱하면 대칭이 가능해진다
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->CreateAnimationFolder("Idle", "Idle", 0.2f);
		PlayerImageRenderer->CreateAnimationFolder("IdleToRun", "IdleToRun", 0.07f);
		PlayerImageRenderer->CreateAnimationFolder("Run", "Run", 0.1f);
		PlayerImageRenderer->CreateAnimationFolder("Slash", "Slash", 0.05f, false);
		PlayerImageRenderer->CreateAnimationFolder("RunToIdle", "RunToIdle", 0.07f);
		PlayerImageRenderer->CreateAnimationFolder("Airborne", "Airborne", 0.07f);
		PlayerImageRenderer->CreateAnimationFolder("Jump", "Jump", 0.07f);
		PlayerImageRenderer->SetChangeAnimation("Idle");
		PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetFolderTextureImageSize());
		PlayerImageRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot());
	}


	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PLAYER);
		PlayerCollision->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, 1.0f });
		PlayerCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetFolderTextureBotPivot());
	}

	if (false == GameEngineInput::GetInst().IsKey("PlayerMove"))
	{
		GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst().CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst().CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst().CreateKey("RotZ+", 'Q');
		GameEngineInput::GetInst().CreateKey("RotZ-", 'E');
		GameEngineInput::GetInst().CreateKey("Attack", 'X');
		GameEngineInput::GetInst().CreateKey("DebugOn", 'R');
	}


	{
		PlayerSlashRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerSlashRenderer->CreateAnimationFolder("SlashEffect", "SlashEffect", 0.02f);
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

	StateManager_.ChangeState("Idle");
	
	SetCallBackFunc();

}

void Player::Update(float _DeltaTime)
{
	PlayerImageSizeUpdate();
	MapCollsionColor = Map::GetColor(GetTransform());
	StateManager_.Update();



	if (true == GameEngineInput::GetInst().Press("RotZ+"))
	{
		//PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, 1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ-"))
	{
		//PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, -1.0f } *100.0f);
	}


	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(PlayerCollision->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(PlayerSlashCollision->GetTransform(), CollisionType::Rect);
	}
	

	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

}

void Player::Idle()
{

	PlayerImageRenderer->SetChangeAnimation("Idle");

	if (true == GameEngineInput::GetInst().Press("MoveLeft") || GameEngineInput::GetInst().Press("MoveRight"))
	{
		StateManager_.ChangeState("IdleToRun");
	}


	if (true == GameEngineInput::GetInst().Press("MoveUp"))
	{
		//GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed);
	}
	if (true == GameEngineInput::GetInst().Press("MoveDown"))
	{
		//GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed);
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		StateManager_.ChangeState("Attack");
	}

	MapCollisionCheck();
}

void Player::IdleToRun()
{
	PlayerImageRenderer->SetChangeAnimation("IdleToRun");

	if (true == GameEngineInput::GetInst().Press("MoveLeft"))
	{
		if (PlayerDirection == LeftRight::RIGHT)
		{
			PlayerDirection = LeftRight::LEFT;
		}
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}

	if (GameEngineInput::GetInst().Press("MoveRight"))
	{
		if (PlayerDirection == LeftRight::LEFT)
		{
			PlayerDirection = LeftRight::RIGHT;
		}
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
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
		StateManager_.ChangeState("Attack");
	}

	PlayerImageRenderer->SetEndCallBack("IdleToRun", [&]()
		{
			StateManager_.ChangeState("Run");
		}
	);

	MapCollisionCheck();
}

void Player::Run()
{
	PlayerImageRenderer->SetChangeAnimation("Run");

	if (true == GameEngineInput::GetInst().Press("MoveLeft"))
	{
		if (PlayerDirection == LeftRight::RIGHT)
		{
			PlayerDirection = LeftRight::LEFT;
		}
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}

	if (GameEngineInput::GetInst().Press("MoveRight"))
	{
		if (PlayerDirection == LeftRight::LEFT)
		{
			PlayerDirection = LeftRight::RIGHT;
		}
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
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
		StateManager_.ChangeState("Attack");
	}

	MapCollisionCheck();
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

	MapCollisionCheck();
}

void Player::Attack()
{
	PlayerImageRenderer->SetChangeAnimation("Slash");

	if (true == GameEngineInput::GetInst().Press("MoveLeft"))
	{
		if (PlayerDirection == LeftRight::RIGHT)
		{
			PlayerDirection = LeftRight::LEFT;
		}
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}

	if (GameEngineInput::GetInst().Press("MoveRight"))
	{
		if (PlayerDirection == LeftRight::LEFT)
		{
			PlayerDirection = LeftRight::RIGHT;
		}
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
	}

	PlayerImageRenderer->SetEndCallBack("Slash", [&]()
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

	MapCollisionCheck();
}

void Player::Airborne()
{
	GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 200.0f);

	PlayerImageRenderer->SetChangeAnimation("Airborne");

	if (true == GameEngineInput::GetInst().Press("MoveLeft"))
	{
		if (PlayerDirection == LeftRight::RIGHT)
		{
			PlayerDirection = LeftRight::LEFT;
		}
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
	}

	if (GameEngineInput::GetInst().Press("MoveRight"))
	{
		if (PlayerDirection == LeftRight::LEFT)
		{
			PlayerDirection = LeftRight::RIGHT;
		}
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
	}

	if (MapCollsionColor == float4::BLACK)
	{
		StateManager_.ChangeState("Idle");
	}


}

void Player::Jump()
{}

void Player::SetCallBackFunc()
{
	{
		PlayerImageRenderer->SetStartCallBack("Slash", [&]()
			{
				PlayerSlashRenderer->SetChangeAnimation("SlashEffect", true);
				if (PlayerDirection == LeftRight::LEFT)
				{
					PlayerSlashRenderer->GetTransform()->SetLocalScaling({ 157.0f,114.0f, 1.0f });
					PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-70.0f, 0.0f, -1.0f});
					PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f, 114.0f, 1.0f });
					PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-70.0f, 0.0f, -1.0f});
				}
				else if (PlayerDirection == LeftRight::RIGHT)
				{
					{
						PlayerSlashRenderer->GetTransform()->SetLocalScaling({ -157.0f,114.0f, 1.0f });
						PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
						PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f, 114.0f, 1.0f });
						PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
					}
				}
				
			}
		);

		PlayerSlashRenderer->SetEndCallBack("SlashEffect", [&]()
			{
				PlayerSlashRenderer->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
				PlayerSlashCollision->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerCollision->GetTransform()->GetLocalPosition());
			}
		);
	}
}

void Player::PlayerImageSizeUpdate()
{
	//좌우를 바꿔줘야함
	if (PlayerDirection == LeftRight::LEFT)
	{
		PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetFolderTextureImageSize());
	}
	else
	{
		PlayerImageRenderer->GetTransform()->SetLocalScaling(PlayerImageRenderer->GetFolderTextureImageSize()*= float4::XFLIP);
	}

}

void Player::MapCollisionCheck() 
{
	if (MapCollsionColor != float4::BLACK)
	{
		StateManager_.ChangeState("Airborne");
	}

}