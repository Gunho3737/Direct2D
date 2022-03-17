#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Monster.h"
#include "Attack.h"



Player::Player()
	: Speed(300.0f)
{
}

Player::~Player()
{
}

void Player::TestFunction()
{
	//PlayerImageRenderer->SetIndex(4);
}

void Player::Start()
{
	// ���� ����������Ұ� ���� �༮�Դϴ�.
	// �������μ� ������ �� �׸����ִ� ���ɼ��� ������ �ִ� �༮.
	{
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->CreateAnimationFolder("Idle", "Idle", 0.2f);
		PlayerImageRenderer->CreateAnimationFolder("Run", "Run", 0.05f);
		PlayerImageRenderer->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, 1.0f });
		PlayerImageRenderer->SetChangeAnimation("Idle");
	}

	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>((int)ActorCollisionType::PLAYER);

		PlayerCollision->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, 1.0f });
		PlayerCollision->GetTransform()->SetLocalPosition(float4{0.0f, 0.0f, -10.0f});
	}

//	{	�÷��̾� ���� ������������������ �̿��� ������ �����
//		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
//		Renderer->SetRenderingPipeLine("Color");
//		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 20.0f, 1.0f });
//		Renderer->GetTransform()->SetLocalPosition({ 0.0f, 80.0f, 0.0f });
//		Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));
//}

	if (false == GameEngineInput::GetInst().IsKey("PlayerMove"))
	{
		GameEngineInput::GetInst().CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst().CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst().CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst().CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst().CreateKey("RotZ+", 'Q');
		GameEngineInput::GetInst().CreateKey("RotZ-", 'E');
		GameEngineInput::GetInst().CreateKey("Attack", 'X');
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
		Attack* NewBullet = GetLevel()->CreateActor<Attack>();
		NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		//NewBullet->Release(1.0f);
	}


	//PlayerCollision->Collision(CollisionType::Rect, CollisionType::Rect, (int)ActorCollisionType::PLAYER,
	//	[](GameEngineCollision* _OtherCollision)
	//	{
	//		_OtherCollision->GetActor()->Death();
	//	}
	//);

	//GetLevel()->DebugOff();

	GetLevel()->PushDebugRender(PlayerCollision->GetTransform(), CollisionType::Rect);

	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	//PlayerImageRenderer->SetFrameCallBack("Run", 4, std::bind(&Player::TestFunction, this));
	PlayerImageRenderer->SetEndCallBack("Run", std::bind(&Player::TestFunction, this));

}