#include "PreCompile.h"
#include "GameEngine/GameEngineRenderer.h"
#include "Attack.h"

Attack::Attack()
{
}

Attack::~Attack()
{
}



void Attack::Start()
{
	// ���� ����������Ұ� ���� �༮�Դϴ�.
	// �������μ� ������ �� �׸����ִ� ���ɼ��� ������ �ִ� �༮.
	{
		GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		Renderer->SetRenderingPipeLine("Color");
		Renderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
		Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 1.0f, 1.0f));
	}
}

void Attack::Update(float _DeltaTime)
{
	GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 200.0f);
}