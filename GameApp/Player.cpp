#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"




Player::Player()
	: Speed(300.0f)
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
		PlayerImageRenderer->CreateAnimationFolder("Run", "Run", 0.05f);
		PlayerImageRenderer->CreateAnimationFolder("Slash", "Slash", 0.05f, false);
		PlayerImageRenderer->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, 1.0f });
		PlayerImageRenderer->SetChangeAnimation("Idle");
	}

	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PLAYER);

		PlayerCollision->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, 1.0f });
		PlayerCollision->GetTransform()->SetLocalPosition(float4{0.0f, 0.0f, -10.0f});
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
	//	PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f, 114.0f, 1.0f });
	//	PlayerSlashCollision->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
	}

	SetCallBackFunc();

}

void Player::Update(float _DeltaTime)
{

	if (true == GameEngineInput::GetInst().Up("MoveLeft"))
	{
		PlayerImageRenderer->SetChangeAnimation("Idle");
	}

	if (true == GameEngineInput::GetInst().Up("MoveRight"))
	{
		PlayerImageRenderer->SetChangeAnimation("Idle");
	}

	if (true == GameEngineInput::GetInst().Press("MoveLeft"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * Speed);
		if ("Idle" == PlayerImageRenderer->GetCurrentAnimationName())
		{
			if (PlayerDirection == LeftRight::RIGHT)
			{
				PlayerDirection = LeftRight::LEFT;
				PlayerImageRenderer->GetTransform()->SetLocalScaleFilp(PlayerImageRenderer->GetTransform()->GetLocalScaling());
			}
			PlayerImageRenderer->SetChangeAnimation("Run");
		}
	}

	if (true == GameEngineInput::GetInst().Press("MoveRight"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		if ("Idle" == PlayerImageRenderer->GetCurrentAnimationName())
		{
			PlayerImageRenderer->SetChangeAnimation("Run");
			if (PlayerDirection == LeftRight::LEFT)
			{
				PlayerDirection = LeftRight::RIGHT;
				PlayerImageRenderer->GetTransform()->SetLocalScaleFilp(PlayerImageRenderer->GetTransform()->GetLocalScaling());
			}
		}
	}
	if (true == GameEngineInput::GetInst().Press("MoveUp"))
	{
		//GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed);
	}
	if (true == GameEngineInput::GetInst().Press("MoveDown"))
	{
		//GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ+"))
	{
		//PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, 1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ-"))
	{
		//PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, -1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Down("Attack"))
	{
		PlayerImageRenderer->SetChangeAnimation("Slash");
	}


	//PlayerCollision->Collision(CollisionType::Rect, CollisionType::Rect, (int)ActorCollisionType::PLAYER,
	//	[](GameEngineCollision* _OtherCollision)
	//	{
	//		_OtherCollision->GetActor()->Death();
	//	}
	//);


	if (true == GetLevel()->IsDebugCheck())
	{
		GetLevel()->PushDebugRender(PlayerCollision->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(PlayerSlashCollision->GetTransform(), CollisionType::Rect);
	}
	

	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

}

void Player::SetCallBackFunc()
{
	{
		//PlayerImageRenderer->SetStartCallBack("Slash", std::bind(&Player::Slash, this));
		PlayerImageRenderer->SetStartCallBack("Slash", [this]()
			{
				PlayerSlashRenderer->SetChangeAnimation("SlashEffect", true);
				if (PlayerDirection == LeftRight::LEFT)
				{
					PlayerSlashRenderer->GetTransform()->SetLocalScaling({ 157.0f,114.0f, 1.0f });
					PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-70.0f, 0.0f, -1.0f});
					PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ 157.0f, 114.0f, 1.0f });
					PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {-70.0f, 0.0f, -1.0f});
				}
				else
				{
					PlayerSlashRenderer->GetTransform()->SetLocalScaling({ -157.0f,114.0f, 1.0f });
					PlayerSlashRenderer->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
					PlayerSlashCollision->GetTransform()->SetLocalScaling(float4{ -157.0f, 114.0f, 1.0f });
					PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerImageRenderer->GetTransform()->GetLocalPosition() += {70.0f, 0.0f, -1.0f});
				}
			}
		);

		PlayerSlashRenderer->SetEndCallBack("SlashEffect", [this]()
			{
				PlayerSlashRenderer->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashRenderer->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
				PlayerSlashCollision->GetTransform()->SetLocalScaling({ 0.0f,0.0f, 1.0f });
				PlayerSlashCollision->GetTransform()->SetLocalPosition(PlayerCollision->GetTransform()->GetLocalPosition());
			}
		);


		PlayerImageRenderer->SetEndCallBack("Slash", [this]()
			{
				PlayerImageRenderer->SetChangeAnimation("Idle");
			}
		);
	}
}