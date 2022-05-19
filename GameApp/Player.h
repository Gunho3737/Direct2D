#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// 설명 :
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
	
	static Player* MainPlayer;

protected:
	GameEngineImageRenderer* PlayerImageRenderer;
	GameEngineCollision* PlayerCollision;
	GameEngineImageRenderer* PlayerSlashRenderer;
	GameEngineCollision* PlayerSlashCollision;

	GameEngineImageRenderer* PlayerEffectRenderer;
	GameEngineImageRenderer* PlayerEffectRenderer2;

	//몬스터와 공격이 닿을시 나오는 이펙트를 위한 렌더러

	//칼이 부딪히는 이펙트
	GameEngineImageRenderer* PlayerSlashEffectRenderer;

	//오렌지 이펙트가 피처럼 튀는 이펙트, 플레이어의 공격위치를 받아야 하기때문에 플레이어에서 생성
	GameEngineImageRenderer* PlayerShotImpactRenderer;

	float Speed;
	float TimeCheck;
	float ImmuneTime;

	float4 JumpPower;
	float4 BasicJumpPower;
	float4 FallDownPower;


	//4방향 맵충돌
	float4 MapBotCollisionColor;
	float4 MapTopCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

	//대각선방향 맵충돌
	float4 MapTopLeftCollisionColor;
	float4 MapTopRightCollisionColor;


	//레벨 이동 상태냐?
	bool LevelMoveOn;
	
	//데미지를 받은 상태냐?
	bool Impact;

	//일정시간 무적상태를 위한 bool
	bool Immune;

	//보스전 바닥꺼짐을 위한 bool
	bool BossFight;

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
	void MapPrev();
	void Damage();
	void Death();
};

