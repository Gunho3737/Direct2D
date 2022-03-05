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
	UIRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	UIRenderer->SetImage("hpbar.png");
	UIRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
}

void  UI_HpBar::Update(float _DeltaTime)
{
	
}