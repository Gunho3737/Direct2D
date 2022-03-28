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

	GameEngineFSM StateManager_;

	bool Immune;


protected:

	int HP;

	float ImmuneTime;
	
private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Die();
	void ImmuneOff();
};

