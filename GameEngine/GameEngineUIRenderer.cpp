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
	// Push Render�� ��
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);
	SetRenderingPipeLine("Texture");
}





void GameEngineUIRenderer::SetRenderGroup(int _Order)
{
	GetLevel()->GetUICamera()->ChangeRendererGroup(_Order, this);;
}