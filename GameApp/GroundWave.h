#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>


// �з� : 
// �뵵 : 
// ���� : 
class GroundWave : public GameEngineActor
{
private:	// member Var

public:
	GroundWave(); // default constructer ����Ʈ ������
	~GroundWave(); // default destructer ����Ʈ �Ҹ���

	GameEngineImageRenderer* ImageRenderer;
	GameEngineCollision* Collision;
	GameEngineFSM StateManager_;

	LeftRight Direction;

protected:		// delete constructer
	GroundWave(const GroundWave& _other) = delete; // default Copy constructer ����Ʈ ���������
	GroundWave(GroundWave&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GroundWave& operator=(const GroundWave& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GroundWave& operator=(const GroundWave&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

