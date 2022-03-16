#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"


Player::Player()
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
	// 정말 세팅해줘야할게 많은 녀석입니다.
	// 랜더러로서 뭐든지 다 그릴수있는 가능성을 가지고 있는 녀석.
	{
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->CreateAnimationFolder("Idle", "Idle", 0.2f);
		PlayerImageRenderer->CreateAnimationFolder("Run", "Run", 0.05f);
		PlayerImageRenderer->GetTransform()->SetLocalScaling(float4{ 60.0f, 130.0f, 1.0f });
		PlayerImageRenderer->SetChangeAnimation("Idle");
	}

	{
		PlayerCollision = CreateTransformComponent<GameEngineCollision>(10);

		PlayerCollision->GetTransform()->SetLocalScaling(float4{ 200.0f, 200.0f, 1.0f });

		PlayerCollision->SetCollisionGroup(30);
	}

//	{	플레이어 위에 렌더링파이프라인을 이용한 도형을 만든다
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
		GameEngineInput::GetInst().CreateKey("Fire", VK_SPACE);
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
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 100.0f);
		PlayerImageRenderer->SetChangeAnimation("Run");

	
	}
	if (true == GameEngineInput::GetInst().Press("MoveRight"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 100.0f);
		PlayerImageRenderer->SetChangeAnimation("Run");
	}
	if (true == GameEngineInput::GetInst().Press("MoveUp"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * 100.0f);
	}
	if (true == GameEngineInput::GetInst().Press("MoveDown"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ+"))
	{
		PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, 1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ-"))
	{
		PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, -1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Down("Fire"))
	{
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
		NewBullet->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		NewBullet->Release(1.0f);
	}

	// 그냥 원하는 순간 20
	PlayerCollision->Collision(CollisionType::CirCle, CollisionType::CirCle, 20,
		[](GameEngineCollision* _OtherCollision)
		{
			_OtherCollision->GetActor()->Death();
		}
	);

	GetLevel()->PushDebugRender(PlayerCollision->GetTransform(), CollisionType::Rect);

	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	//PlayerImageRenderer->SetFrameCallBack("Run", 4, std::bind(&Player::TestFunction, this));
	PlayerImageRenderer->SetEndCallBack("Run", std::bind(&Player::TestFunction, this));

}