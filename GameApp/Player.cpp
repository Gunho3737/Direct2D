#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}



void Player::Start()
{
	// ���� ����������Ұ� ���� �༮�Դϴ�.
	// �������μ� ������ �� �׸����ִ� ���ɼ��� ������ �ִ� �༮.
	{
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("ColorRendering");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
	}

	{
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("ColorRendering");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
		Renderer->GetTransform()->SetLocalPosition({ 0.0f, 150.0f, 0.0f });
	}


}

void Player::Update(float _DeltaTime)
{

}