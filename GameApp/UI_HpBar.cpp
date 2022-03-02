#include "PreCompile.h"
#include "UI_HpBar.h"
#include "GameEngine/GameEngineImageRenderer.h"

UI_HpBar::UI_HpBar()
{
}

UI_HpBar::~UI_HpBar()
{
}

void UI_HpBar::Start()
{
	GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	Renderer->SetImage("hpbar.png", Renderer->GetTransform());
}
