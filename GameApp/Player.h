#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// ���� :
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

	//���Ϳ� ������ ������ ������ ����Ʈ�� ���� ������

	//Į�� �ε����� ����Ʈ
	GameEngineImageRenderer* PlayerSlashEffectRenderer;

	//������ ����Ʈ�� ��ó�� Ƣ�� ����Ʈ, �÷��̾��� ������ġ�� �޾ƾ� �ϱ⶧���� �÷��̾�� ����
	GameEngineImageRenderer* PlayerShotImpactRenderer;

	float Speed;
	float TimeCheck;
	float ImmuneTime;

	float4 JumpPower;
	float4 BasicJumpPower;
	float4 FallDownPower;


	//4���� ���浹
	float4 MapBotCollisionColor;
	float4 MapTopCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

	//�밢������ ���浹
	float4 MapTopLeftCollisionColor;
	float4 MapTopRightCollisionColor;


	//���� �̵� ���³�?
	bool LevelMoveOn;
	
	//�������� ���� ���³�?
	bool Impact;

	//�����ð� �������¸� ���� bool
	bool Immune;

	//������ �ٴڲ����� ���� bool
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

