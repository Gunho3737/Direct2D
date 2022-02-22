#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineImageRenderer;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	GameEngineImageRenderer* PlayerImageRenderer;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

