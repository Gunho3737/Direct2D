#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>


// �з� : 
// �뵵 : 
// ���� : 
class MiddleBoss : public GameEngineActor
{
private:	// member Var

public:
	MiddleBoss(); // default constructer ����Ʈ ������
	~MiddleBoss(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* ImageRenderer;
	GameEngineImageRenderer* AttackEffectRenderer;
	GameEngineImageRenderer* DeathEffectRenderer;

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

protected:		// delete constructer
	MiddleBoss(const MiddleBoss& _other) = delete; // default Copy constructer ����Ʈ ���������
	MiddleBoss(MiddleBoss&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	MiddleBoss& operator=(const MiddleBoss& _other) = delete; // default Copy operator ����Ʈ ���� ������
	MiddleBoss& operator=(const MiddleBoss&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Wait(); // �ൿ �߰��߰��� ��⸦ ���� ����
	void Walk();
	void Attack();
	void JumpReady();
	void Jump();
	void GetUp();
	void Death();


	void SetCallBackFunc();

	void DirectionCheck();
public:
	bool GetDamage;

	//�̵������� ȸ�� ���θ� üũ�ϴ� bool
	bool TurnOn;

	int HP;

	//����ĸ� ����ϱ����� ����Ƚ��ī��Ʈ
	int GroundAttackCount;

	float TurnTime;
	float ImmuneTime;
	float JumpReadyTime;
	float Speed;
};

