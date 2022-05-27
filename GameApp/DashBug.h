#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// �з� : 
// �뵵 : 
// ���� : 
class DashBug : public GameEngineActor
{
private:	// member Var

public:
	DashBug(); // default constructer ����Ʈ ������
	~DashBug(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* ImageRenderer;
	GameEngineImageRenderer* DeathEffectRenderer;

	//������ü���ݸ���
	GameEngineCollision* Collision;

	//�÷��̾� �ν��ݸ���
	GameEngineCollision* ViewCollision;

	//���� �������� �νİŸ� �ݸ���
	GameEngineCollision* RangeCollision;
	GameEngineFSM StateManager_;
	LeftRight Direction;

	float4 MapBotCollisionColor;
	float4 MapLeftCollisionColor;
	float4 MapRightCollisionColor;

protected:		// delete constructer
	DashBug(const DashBug& _other) = delete; // default Copy constructer ����Ʈ ���������
	DashBug(DashBug&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	DashBug& operator=(const DashBug& _other) = delete; // default Copy operator ����Ʈ ���� ������
	DashBug& operator=(const DashBug&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Walk();
	void DashReady();
	void Dash();
	void DashCoolDown();
	void Death();


	void SetCallBackFunc();

	void DirectionCheck();
public:
	bool GetDamage;

	int HP;

	float ImmuneTime;
	float DashTime;
	float Speed;
};

