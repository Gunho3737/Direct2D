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
	GameEngineUIRenderer::GameEngineImageRenderer::Start();
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);
}