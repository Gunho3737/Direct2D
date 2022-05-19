#include "PreCompile.h"
#include "FinalBoss.h"
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineImageRenderer.h"
#include <GameEngine\GameEngineCollision.h>

#include <GameApp/BitMap.h>
#include "Player.h"
#include "GroundWave.h"



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
	ImageRenderer->CreateAnimation("FinalBoss.png", "Walk", 10, 13, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "AttackReady", 24, 29, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Attack", 30, 32, 0.1f, false);
	ImageRenderer->CreateAnimation("FinalBoss.png", "AttackRecover", 33, 37, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "Jump", 38, 42, 0.1f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttack", 43, 44, 0.2f);
	ImageRenderer->CreateAnimation("FinalBoss.png", "JumpAttackRecover", 45, 48, 0.1f);
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

void FinalBoss::Walk() 
{}

void FinalBoss::AttackReady()
{}

void FinalBoss::Attack() 
{}

void FinalBoss::AttackRecover()
{}


void FinalBoss::Jump()
{}

void FinalBoss::JumpAttack()
{}

void FinalBoss::JumpAttackRecover()
{}

void FinalBoss::GetUp() 
{}

void FinalBoss::Death() 
{}