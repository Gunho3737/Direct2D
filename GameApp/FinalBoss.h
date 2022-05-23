#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>


// �з� : 
// �뵵 : 
// ���� : 
class FinalBoss : public GameEngineActor
{
private:	// member Var

public:
	FinalBoss(); // default constructer ����Ʈ ������
	~FinalBoss(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* ImageRenderer;
	GameEngineImageRenderer* RealBodyRenderer;

	//������ü���ݸ���
	GameEngineCollision* Collision;

	//�÷��̾� �ν��ݸ���
	GameEngineCollision* ViewCollision;

	//�̵�������, ���� ��ȯ�� ���� �ν� �ݸ���
	GameEngineCollision* TurnCheckCollision;

	//�÷��̾���� �Ÿ��� ������� �ݸ���
	GameEngineCollision* RangeCollision;

	//������ü�� �ݸ���
	GameEngineCollision* AttackCollision;

	GameEngineFSM StateManager_;
	LeftRight Direction;

	float4 MapBotCollisionColor;
	float4 MapTopCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

protected:		// delete constructer
	FinalBoss(const FinalBoss& _other) = delete; // default Copy constructer ����Ʈ ���������
	FinalBoss(FinalBoss&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	FinalBoss& operator=(const FinalBoss& _other) = delete; // default Copy operator ����Ʈ ���� ������
	FinalBoss& operator=(const FinalBoss&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Walk();
	void AttackReady();
	void Attack();
	void AttackRecover();
	void Jump();
	void JumpAttack();
	void JumpAttackRecover();
	void Damage();
	void FaceOff();
	void Faint();
	void GetUp();
	void Death();
	void DirectionCheck();

	void FloorCollisionCheck();
	void SetCallBackFunc();

public:
	bool GetDamage;
	bool FloorCheck;

	//���� HP
	int HP;

	//��ü HP
	int BodyHP;

	//�ٴڲ����� ������ ���� bool
	bool DeathOn;

	//����ĸ� ����ϱ����� ����Ƚ��ī��Ʈ
	int GroundAttackCount;

	float4 JumpPower;
	float TurnTime;
	float ImmuneTime;
	float Speed;
};

