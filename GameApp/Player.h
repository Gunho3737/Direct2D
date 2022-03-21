#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// Ό³Έν :
class Attack;
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
	GameEngineCollision* PlayerCollision;
	GameEngineImageRenderer* PlayerSlashRenderer;
	GameEngineCollision* PlayerSlashCollision;
	LeftRight PlayerDirection;

	GameEngineFSM StateManager_;

	float Speed;

private:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	void SetCallBackFunc();
	void PlayerImageSizeUpdate();

	//void TestTimeEvent();

private:
	void Idle();
	void IdleToRun();
	void Run();
	void RunToIdle();
	void Attack();
};

