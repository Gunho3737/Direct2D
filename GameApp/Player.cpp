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
	}


}

void Player::Update(float _DeltaTime)
{

}