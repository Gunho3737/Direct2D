#include "PreCompile.h"
#include "FinalBoss.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>


FinalBoss::FinalBoss() // default constructer 디폴트 생성자
{

}

FinalBoss::~FinalBoss() // default destructer 디폴트 소멸자
{

}

void FinalBoss::Start()
{
	ImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	ImageRenderer->CreateAnimation("FinalBoss.png", "Idle", 0, 4, 0.1f);
	ImageRenderer->SetChangeAnimation("Idle");
	ImageRenderer->GetTransform()->SetLocalScaling({ 1400.0f, 1400.0f, 1.0f });

	StateManager_.CreateState("Idle", std::bind(&FinalBoss::Idle, this));
	StateManager_.ChangeState("Idle");
}

void FinalBoss::Update(float _DeltaTime)
{
	StateManager_.Update();
}

void FinalBoss::Idle() 
{
	ImageRenderer->SetChangeAnimation("Idle");
}

void FinalBoss::Wait() 
{}

void FinalBoss::Walk() 
{}

void FinalBoss::Attack() 
{}

void FinalBoss::JumpReady() 
{}

void FinalBoss::Jump()
{}

void FinalBoss::GetUp() 
{}

void FinalBoss::Death() 
{}