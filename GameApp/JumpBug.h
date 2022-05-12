#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// �з� : 
// �뵵 : 
// ���� : 
class JumpBug : public GameEngineActor
{
private:	// member Var

public:
	JumpBug(); // default constructer ����Ʈ ������
	~JumpBug(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* ImageRenderer;

	//������ü���ݸ���
	GameEngineCollision* Collision;

	//�÷��̾� �ν��ݸ���
	GameEngineCollision* ViewCollision;

	//���� �������� �νİŸ� �ݸ���
	GameEngineCollision* RangeCollision;
	GameEngineFSM StateManager_;
	LeftRight Direction;

protected:		// delete constructer
	JumpBug(const JumpBug& _other) = delete; // default Copy constructer ����Ʈ ���������
	JumpBug(JumpBug&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	JumpBug& operator=(const JumpBug& _other) = delete; // default Copy operator ����Ʈ ���� ������
	JumpBug& operator=(const JumpBug&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Idle();
	void Walk();
	void JumpReady();
	void Jump();
	void Death();


	void SetCallBackFunc();

	void DirectionCheck();
public:
	bool GetDamage;

	int HP;

	float ImmuneTime;
	float JumpReadyTime;
	float Speed;
};

