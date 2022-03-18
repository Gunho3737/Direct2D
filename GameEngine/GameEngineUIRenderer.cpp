#include "PreCompile.h"
#include "GameEngineUIRenderer.h"
#include "GameEngineLevel.h"
#include "CameraComponent.h"

GameEngineUIRenderer::GameEngineUIRenderer()
{
}

GameEngineUIRenderer::~GameEngineUIRenderer()
{
}

void GameEngineUIRenderer::Start()
{
	// Push Render¸¦ ¸Þ
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);
	SetRenderingPipeLine("Texture");
	ImageRendererStart();
}





void GameEngineUIRenderer::SetRenderGroup(int _Order)
{
	GetLevel()->GetUICamera()->ChangeRendererGroup(_Order, this);;
}