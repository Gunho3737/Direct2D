#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Attack.h"



Player::Player()
	: Speed(300.0f)
{
}

Player::~Player()
{
}


void Player::Start()
{
	{
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
		PlayerImageRenderer->SetStartCallBack("Slash", std::bind(&Player::Slash, this));
		PlayerImageRenderer->SetEndCallBack("Slash", [this]() {PlayerImageRenderer->SetChangeAnimation("Idle");});
	}
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
		PlayerImageRenderer->SetChangeAnimation("Run");

	
	}
	if (true == GameEngineInput::GetInst().Press("MoveRight"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * Speed);
		PlayerImageRenderer->SetChangeAnimation("Run");
	}
	if (true == GameEngineInput::GetInst().Press("MoveUp"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * Speed);
	}
	if (true == GameEngineInput::GetInst().Press("MoveDown"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * Speed);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ+"))
	{
		PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, 1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ-"))
	{
		PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, -1.0f } *100.0f);
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
	}
	

	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

}

void Player::Slash()
{
	Attack* NewAttack = GetLevel()->CreateActor<Attack>();
	NewAttack->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() += {-70.0f, 0.0f, -1.0f});
	//공격은 새로운 오브젝트를 만들게 아니라, 플레이어에게 종속된 또다른 충돌/렌더러를 만들게 하자
	//NewAttack->GetTransform()->AttachTransform(GetTransform());
}