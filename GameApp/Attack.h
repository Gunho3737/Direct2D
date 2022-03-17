#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Attack : public GameEngineActor
{
public:
	// constrcuter destructer
	Attack();
	~Attack();

	// delete Function
	Attack(const Attack& _Other) = delete;
	Attack(Attack&& _Other) noexcept = delete;
	Attack& operator=(const Attack& _Other) = delete;
	Attack& operator=(Attack&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

