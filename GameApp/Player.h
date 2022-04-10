#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

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

	LeftRight PlayerDirection;
	GameEngineFSM StateManager_;
	
protected:
	GameEngineImageRenderer* PlayerImageRenderer;
	GameEngineCollision* PlayerCollision;
	GameEngineImageRenderer* PlayerSlashRenderer;
	GameEngineCollision* PlayerSlashCollision;


	float Speed;
	float TimeCheck;

	float4 JumpPower;
	float4 BasicJumpPower;
	float4 FallDownPower;

	float4 MapBotCollsionColor;
	float4 MapTopCollsionColor;
	float4 MapLeftCollsionColor;
	float4 MapRightCollsionColor;

	bool LevelMoveOn;

private:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	void SetCallBackFunc();

private:
	void Idle();
	void IdleToRun();
	void Run();
	void RunToIdle();
	void Attack();
	void Jump();
	void Airborne();
	void UpAttack();
	void DownAttack();
	void MapMove();
};

