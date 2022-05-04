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
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;

	float4 MapBotCollisionColor;
	float4 MapTopCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

	float StartX;
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
	void Wake();
	void Walk();
	void Turn();
	void Attack();

	void JumpReady();
	void Jump();
	void GetUp();

	void Death();

public:
	bool GetDamage;
	int HP;

	float MoveDistance;
	float ImmuneTime;
	float SpinTime;
	float Speed;
};

