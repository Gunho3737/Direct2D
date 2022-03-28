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
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;

protected:		// delete constructer
	FinalBoss(const FinalBoss& _other) = delete; // default Copy constructer ����Ʈ ���������
	FinalBoss(FinalBoss&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	FinalBoss& operator=(const FinalBoss& _other) = delete; // default Copy operator ����Ʈ ���� ������
	FinalBoss& operator=(const FinalBoss&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

