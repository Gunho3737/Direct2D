#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// Ό³Έν :
class FlyBug : public GameEngineActor
{
public:
	// constrcuter destructer
	FlyBug();
	~FlyBug();

	// delete Function
	FlyBug(const FlyBug& _Other) = delete;
	FlyBug(FlyBug&& _Other) noexcept = delete;
	FlyBug& operator=(const FlyBug& _Other) = delete;
	FlyBug& operator=(FlyBug&& _Other) noexcept = delete;

	GameEngineImageRenderer* PlayerImageRenderer;

	GameEngineCollision* Collision;
	GameEngineCollision* RangeCollision;

	LeftRight Direction;
	GameEngineFSM StateManager_;

	bool Immune;
	bool GetDamage;

	float4 MapBotCollisionColor;
	float4 MapTopCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

protected:

	int HP;

	float ImmuneTime;
	float Speed;
	
private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Die();
	void Startle();
	void Chase();
};

