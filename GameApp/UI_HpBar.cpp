#include "PreCompile.h"
#include "UI_HpBar.h"
#include "GameEngine/GameEngineUIRenderer.h"


UI_HpBar::UI_HpBar()
{
}

UI_HpBar::~UI_HpBar()
{
}

void UI_HpBar::Start()
{
	GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
	HPBarRenderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	HPBarRenderer->SetImage("hpbar.png");
	HPBarRenderer->GetTransform()->SetLocalScaling({ 250.0f, 150.0f, 1.0f } );
	HPBarRenderer->GetTransform()->SetLocalPosition({ -630.0f, 350.0f, -20.0f });

	float4 HPIconPosition = { { -630.0f + 50.0f, 360.0f, -21.0f } };
	float4 HPIconScale = { { 57.0f, 70.0f, 1.0f } }; 
	float4 HPIconSpace = { 75.0f, 0.0f, 0.0f, 0.0f };

	HPIconRenderer1 = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	HPIconRenderer1 ->CreateAnimationFolder("HealthIdle", "HealthIdle", 0.03f);
	HPIconRenderer1 ->GetTransform()->SetLocalScaling(HPIconScale);
	HPIconRenderer1 ->GetTransform()->SetLocalPosition(HPIconPosition);
	HPIconRenderer1 ->SetChangeAnimation("HealthIdle");

	HPIconRenderer2 = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	HPIconRenderer2->CreateAnimationFolder("HealthIdle", "HealthIdle", 0.03f);
	HPIconRenderer2->GetTransform()->SetLocalScaling(HPIconScale);
	HPIconRenderer2->GetTransform()->SetLocalPosition(HPIconPosition + HPIconSpace);
	HPIconRenderer2->SetChangeAnimation("HealthIdle");

	HPIconRenderer3 = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	HPIconRenderer3->CreateAnimationFolder("HealthIdle", "HealthIdle", 0.03f);
	HPIconRenderer3->GetTransform()->SetLocalScaling(HPIconScale);
	HPIconRenderer3->GetTransform()->SetLocalPosition(HPIconPosition + HPIconSpace + HPIconSpace);
	HPIconRenderer3->SetChangeAnimation("HealthIdle");

	HPIconRenderer4 = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	HPIconRenderer4->CreateAnimationFolder("HealthIdle", "HealthIdle", 0.03f);
	HPIconRenderer4->GetTransform()->SetLocalScaling(HPIconScale);
	HPIconRenderer4->GetTransform()->SetLocalPosition(HPIconPosition + HPIconSpace + HPIconSpace + HPIconSpace);
	HPIconRenderer4->SetChangeAnimation("HealthIdle");

	HPIconRenderer5 = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	HPIconRenderer5->CreateAnimationFolder("HealthIdle", "HealthIdle", 0.03f);
	HPIconRenderer5->GetTransform()->SetLocalScaling(HPIconScale);
	HPIconRenderer5->GetTransform()->SetLocalPosition(HPIconPosition + HPIconSpace + HPIconSpace + HPIconSpace + HPIconSpace);
	HPIconRenderer5->SetChangeAnimation("HealthIdle");
	

}

void  UI_HpBar::Update(float _DeltaTime)
{
	
}