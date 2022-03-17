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
	// 정말 세팅해줘야할게 많은 녀석입니다.
	// 랜더러로서 뭐든지 다 그릴수있는 가능성을 가지고 있는 녀석.
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